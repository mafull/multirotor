import React, { Component } from "react";

import {
    Table
}                           from "semantic-ui-react";

import LogElement           from "./LogElement";


class Logger extends Component {
    state = {
        logMessages: [],

        messageLimit: 20
    }

    componentDidMount() {
        this.wsConnection = new WebSocket("ws://localhost:3001/api/ws/logger");
        this.wsConnection.onopen = () => {
            console.log("Opened ws connection to backend");
        }
        this.wsConnection.onmessage = message => {
            // Attempt to parse the message data into a JSON object
            try {
                const logMessage = JSON.parse(message.data);

                const updatedLogMessageArray = this.state.logMessages.concat(logMessage);
                this.setState({ logMessages: updatedLogMessageArray });


            } catch (e) {
                // Failed to parse - the data is not an object
                console.log(message.data);
            } finally {
                // Do nothing
            }
        }
    }

    render() {
        const {
            logMessages,
            messageLimit
        } = this.state;

        const idInc = Math.max(0, (logMessages.length - messageLimit));
        const logElements = logMessages.slice(-messageLimit)
                                       .map((m, i) => <LogElement key={i} timestamp={(idInc + i)} /* @todo: change this*/ {...m} />);

        return(
            <Table
                celled
                sortable
                compact
                textAlign="center"
                color="blue">
                <Table.Header>
                    <Table.Row>
                        <Table.HeaderCell>Timestamp</Table.HeaderCell>
                        <Table.HeaderCell>Sender</Table.HeaderCell>
                        <Table.HeaderCell>Severity</Table.HeaderCell>
                        <Table.HeaderCell>Message</Table.HeaderCell>
                    </Table.Row>
                </Table.Header>
                <Table.Body>
                    {logElements}
                </Table.Body>
            </Table>
        );
    }
}


export default Logger;
