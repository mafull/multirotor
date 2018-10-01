import bodyParser   from "body-parser";
import express      from "express";
import expressWs    from "express-ws";

import comms        from "./comms";

import routes       from "./routes";


// Create an express application instance
const app = express();


// Configure body-parser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Declare routes
app.use("/api", routes);


// Initialise the comms module
comms.init();


// Initialise express web sockets
expressWs(app);
app.ws("/api/ws/logger", (ws, req) => {
    // Add the ws handle to the comms module
    comms.setWSHandle(ws);
    ws.on("close", () => {
        comms.setWSHandle(null);
    });

    
    ws.send("Hi friend!");


});


// Start the server
app.listen(
    3001,
    "localhost",
    () => console.log("Express server started")
);
