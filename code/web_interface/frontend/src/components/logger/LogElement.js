import React, { Component } from "react";

import {
    Table
}                           from "semantic-ui-react";


const severityStrings = [
    "Error",
    "Warning",
    "Info",
    "Debug"
];

class LogElement extends Component {
    state = {

    }

    static defaultProps = {
        id: 0,

        timestamp: -1,
        sender: "",
        severity: -1,
        message: ""
    };

    render() {
        const {
            key,

            id,

            timestamp,
            sender,
            severity,
            message
        } = this.props;

        return(
            <Table.Row
                error={severity === 0}
                warning={severity === 1}>
                <Table.Cell width="1" textAlign="center">{timestamp}</Table.Cell>
                <Table.Cell width="2" textAlign="center">{sender}</Table.Cell>
                <Table.Cell width="1" textAlign="center">{severityStrings[severity]}</Table.Cell>
                <Table.Cell width="12" textAlign="left">{message}</Table.Cell>
            </Table.Row>
        );
    }
}


export default LogElement;
