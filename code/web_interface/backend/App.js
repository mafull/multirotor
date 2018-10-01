import SerialPort from "serialport";

const BAUD_RATE = 115200;
const LOG_MESSAGE_REG_EXP = /#\s*(\S*)\|(\d+)\|(.*)\n([^]*)/;


let multirotorSerialPort;

let leftoverStr = "";

let logCountFromSenders = {};

var logMessages = [];


const printLogCountFromSenders = () => {
    // Start the string off by overwriting the previous line
    let str = "\r";

    // Sort the keys present in the dictionary
    const keys = Object.keys(logCountFromSenders);
    keys.sort();

    // Append each key-value pair to the string
    keys.forEach(key => {
        str += `${key}:${logCountFromSenders[key]}  `;
    });

    // Print the complete string
    process.stdout.write(str); 
}


const storeLogMessage = (logMessage) => {
    // Store it in the combined array
    logMessages.push(logMessage);

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
            severity: parseInt(matchResult[2]),
            message: matchResult[3]
        };
        storeLogMessage(logMessage);

        // Continue searching for log messages if any data remains
        remainingStr = matchResult[4];
    } while (remainingStr != "");

    return count;
}


SerialPort.list((err, avaialblePorts) => {
    if (avaialblePorts.length == 0) {
        console.error("No serial ports avaialble!");
        return;
    }

    console.log("Available serial ports:");
    console.log(avaialblePorts.map(port => port.comName));

    multirotorSerialPort = new SerialPort(
        avaialblePorts[0].comName,
        {
            baudRate: BAUD_RATE
        }
    );

    multirotorSerialPort.on("open", () => {
        console.log("Multirotor serial port opened");

        multirotorSerialPort.on("data", (receivedData) => {
            // Print the raw received data
            //process.stdout.write(receivedData);

            if (processReceivedData(receivedData)) {
                printLogCountFromSenders();
            }
        });
    });
});

