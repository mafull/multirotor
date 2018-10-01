import React, { Component }   from 'react';


class App extends Component {
    componentDidMount() {
        this.wsConnection = new WebSocket("ws://localhost:3001/api/ws/logger");
        this.wsConnection.onopen = () => {
            console.log("Opened ws connection to backend");
        }
        this.wsConnection.onmessage = message => {
            // Attempt to parse the message data into a JSON object
            try {
                const logMessage = JSON.parse(message.data);
                const logMessageStr = `${logMessage.sender}|${logMessage.severity}|${logMessage.message}`;
                console.log(logMessageStr);
            } catch (e) {
                // Failed to parse - the data is not an object
                console.log(message.data);
            } finally {
                // Do nothing
            }
        }
    }


    render() {
        return (
            <div className="App">
                <header className="App-header">
                    <h1 className="App-title">Welcome to React</h1>
                </header>
                <p className="App-intro">
                    To get started, edit <code>src/App.js</code> and save to reload.
                </p>
            </div>
        );
    }
}

export default App;
