import SerialPort from "serialport";

const BAUD_RATE = 115200;

let multirotorSerialPort;

let leftoverStr = "";

SerialPort.list((err, avaialblePorts) => {
    console.log("Available serial ports:");
    console.log(avaialblePorts);

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
            //process.stdout.write(receivedData); // Doesn't add a new line, unlike console.log

            // Regular expression to match log message
            const regExp = /#\s*(\S*)\|(\d+)\|(.*)\n([^]*)/; // @todo: Make global + caps

            // Combine data leftover from previous reads and the recently received data
            let remainingStr = leftoverStr + receivedData.toString();
            leftoverStr = "";

            // Search the combined data for log messages
            do {
                // See if the remaining string contains a log message
                const matchResult = regExp.exec(remainingStr);
                if (!matchResult) {
                    // No log message found; retain the data and break
                    leftoverStr = remainingStr;
                    break;
                }

                // Parse the match result into a log message object
                const logMessage = {
                    sender: matchResult[1],
                    severity: parseInt(matchResult[2]),
                    message: matchResult[3]
                };

                // Process the parsed log message
                console.log(logMessage.sender + "|" + logMessage.severity + "|" + logMessage.message);

                // Continue searching for log messages if any data remains
                remainingStr = matchResult[4];
            } while (remainingStr != "");
        });
    });
});

