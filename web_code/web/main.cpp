/**
 * @file main.cpp
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cerrno>

#include "src/config_manager.h"
#include "web_code/web/visualization_simulator.h"

#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server_command.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server.h"

// #define _USE_MATH_DEFINES
// #include <cmath>
// #include <libwebsockets.h>


int main(int argc, char**argv) {
    // Print how to run the simulator
    std::cout << "Usage: ./build/bin/ExampleServer 8081" << std::endl;

    // Check whether received arguments is legal
    if (argc > 1) {
        int port = std::atoi(argv[1]);
        std::streambuf* buffer;
        std::ofstream of;

        if (argc > 2) {
            // Only get here if a second parameter is being specified
            // which is a filename for output redirection.
            std::string filename = argv[2];
            of.open(filename.c_str(), std::fstream::out);
            buffer = of.rdbuf();
            std::cout << "got here" << std::endl;

        } else {
            std::cout << "got here instead" << std::endl;
            buffer = std::cout.rdbuf();
        }

        std::ostream out(buffer);
        out << "Writing" << std::endl;

        MyWebServerSessionState state;

        MyWebServer* myWS = new MyWebServer();
        ConfigManager* cm = new ConfigManager();

        // Read in configuration file for the routes
        cm->ReadConfig("config.txt");
        std::cout << "Using default config file: config.txt" << std::endl;

        VisualizationSimulator* mySim =
          new VisualizationSimulator(myWS, cm, &out);

        // Initialize commands for interaction
        state.commands["getRoutes"] = new GetRoutesCommand(myWS);
        state.commands["getBusses"] = new GetBussesCommand(myWS);
        state.commands["start"] = new StartCommand(mySim);
        state.commands["pause"] = new PauseCommand(mySim);
        state.commands["update"] = new UpdateCommand(mySim);
        state.commands["initRoutes"] = new InitRoutesCommand(cm);
        state.commands["listenBus"] = new AddBusListenerCommand(mySim);
        state.commands["listenStop"] = new AddStopListenerCommand(mySim);

        WebServerWithState<MyWebServerSession,
                           MyWebServerSessionState> server(state, port);
        while (true) {
            server.service();
        }
    }

    return 0;
}
