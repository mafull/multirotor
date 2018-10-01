import SerialPort   from "serialport";

const BAUD_RATE = 115200;
const LOG_MESSAGE_REG_EXP = /#\s*(\S*)\|(\d+)\|(.*)\n([^]*)/;


let multirotorSerialPort;

let leftoverStr = "";

let logCountFromSenders = {};

var allLogMessages = [];


const init = () => {
    SerialPort.list((err, avaialblePorts) => {
        if (avaialblePorts.length == 0) {
            // No serial ports available - quit
            console.error("No serial ports avaialble!");
            process.exit();
        }

        // Display the available serial ports
        console.log("Available serial ports:");
        console.log(avaialblePorts.map(port => port.comName));

        // Create a new SerialPort object using the first available port
        const portName = avaialblePorts[0].comName;
        multirotorSerialPort = new SerialPort(
            portName,               // Port
            { baudRate: BAUD_RATE } // Options
        );

        // Define the "open" callback
        multirotorSerialPort.on("open", () => {
            console.log(`Multirotor serial port opened at ${portName}`);

            // Define the "data" callback
            multirotorSerialPort.on("data", (receivedData) => {
                // Print the raw received data
                //process.stdout.write(receivedData);

                // Process the data and print updated stats if there are new messages
                if (processReceivedData(receivedData)) {
                    printLogStats();
                }
            });
        });


        multirotorSerialPort.on("close", () => {
            console.log("\nMultirotor serial port closed");
            process.exit();
        });
    });
}


const getLogMessages = sender => {
    if (sender === "") {
        return allLogMessages;
    } else {
        return allLogMessages.filter(logMessage => logMessage.sender === sender);
    }
}


const getLogStatsString = () => {
    // Sort the keys present in the log count dictionary
    const keys = Object.keys(logCountFromSenders);
    keys.sort();

    // Append each key-value pair to the string
    let str = "";
    keys.forEach(key => {
        str += `${key}:${logCountFromSenders[key]}  `;
    });

    // Return the complete string
    return str;
}


const printLogStats = () => {
    process.stdout.write("\r" + getLogStatsString()); 
}


const storeLogMessage = (logMessage) => {
    // Store it in the combined array
    allLogMessages.push(logMessage);

    // Update the stats
    const sender = logMessage.sender;
    if (!(sender in logCountFromSenders)) {
        logCountFromSenders[sender] = 0;
    }
    logCountFromSenders[sender]++;
}


const processReceivedData = receivedData => {
    // Prepend data leftover from previous reads
    let remainingStr = leftoverStr + receivedData.toString();
    leftoverStr = "";

    let count = 0; // Counter for the number of parsed log messages

    // Search the combined data for log messages
    do {
        // See if the remaining string contains a log message
        const matchResult = LOG_MESSAGE_REG_EXP.exec(remainingStr);
        if (!matchResult) {
            // No log message found; retain the data and return
            leftoverStr = remainingStr;
            break;
        }

        // Increment the count
        count++;

        // Parse the match result into a log message object and store it
        const logMessage = {
            sender: matchResult[1],
            severity: parseInt(matchResult[2]), // Severity should be a number
            message: matchResult[3]
        };
        storeLogMessage(logMessage);

        // Continue searching for log messages if any data remains
        remainingStr = matchResult[4];
    } while (remainingStr != "");

    return count;
}


module.exports = {
    init: () => init(),

    getLogMessages: sender => getLogMessages(sender),

    stats: { logCountFromSenders }
};
