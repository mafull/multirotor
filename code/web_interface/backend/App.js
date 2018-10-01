import bodyParser   from "body-parser";
import express      from "express";

import comms        from "./comms";

import routes       from "./routes";


// Create an express application instance
const app = express();


// Configure body-parser
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Declare routes
app.use("/api", routes);


// Initialsie comms module
comms.init();


// Start the server
app.listen(
    3001,
    "localhost",
    () => console.log("Express server started")
);