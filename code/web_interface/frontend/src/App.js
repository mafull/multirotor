import React, { Component }   from 'react';


class App extends Component {
    componentDidMount() {
        this.wsConnection = new WebSocket("ws://localhost:3001/api/ws/logger");
        this.wsConnection.onopen = () => {
            console.log("Opened ws connection to backend");
        }
        this.wsConnection.onmessage = message => {
            console.log(`Received: ${message.data}`);
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
