import React, { Component } from "react";

import {
    Container
}                           from "semantic-ui-react";

import Logger               from "./logger/Index";


class MainComponent extends Component {
    render() {
        return(
            <div>
                Main
                <Container>
                    <Logger />
                </Container>
            </div>
        );
    }
}


export default MainComponent;
