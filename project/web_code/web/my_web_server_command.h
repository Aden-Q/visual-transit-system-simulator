/**
 * @file visualization_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_
#define WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "src/config_manager.h"
#include "src/data_structs.h"
#include "web_code/web/visualization_simulator.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server.h"


class MyWebServerSession;
class MyWebServerSessionState;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for web server commands in Command Pattern.
 *
 * Calls to \ref execute function to invoke a registered callback.
 */
class MyWebServerCommand {
 public:
  virtual ~MyWebServerCommand() {}
  virtual void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) = 0;  // NOLINT
};

/**
 * @brief The main class for GetRoutes command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback to
 * get route information.
 */
class GetRoutesCommand : public MyWebServerCommand {
 public:
  explicit GetRoutesCommand(MyWebServer* ws);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  MyWebServer* myWS;
};

/**
 * @brief The main class for GetBuses command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback to
 * get bus information.
 */
class GetBussesCommand : public MyWebServerCommand {
 public:
  explicit GetBussesCommand(MyWebServer* ws);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  MyWebServer* myWS;
};

/**
 * @brief The main class for Start command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback to start the simulation.
 */
class StartCommand : public MyWebServerCommand {
 public:
  explicit StartCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
  std::vector<int> timeBetweenBusses;
  int numTimeSteps;
};

/**
 * @brief The main class for Update command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback to update the simulation.
 */
class UpdateCommand : public MyWebServerCommand {
 public:
  explicit UpdateCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

/**
 * @brief The main class for Pause command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback once the button is pressed.
 */
class PauseCommand : public MyWebServerCommand {
 public:
  explicit PauseCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

/**
 * @brief The main class for listener command in Observer Pattern to
 * observer Bus data.
 *
 * Calls to \ref execute function to invoke the callback once the mouse event
 * is detected.
 */
class AddBusListenerCommand: public MyWebServerCommand {
 public:
  explicit AddBusListenerCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

/**
 * @brief The main class for listener command in Observer Pattern to
 * observer Stop data.
 *
 * Calls to \ref execute function to invoke the callback once the mouse event
 * is detected.
 */
class AddStopListenerCommand: public MyWebServerCommand {
 public:
  explicit AddStopListenerCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

/**
 * @brief The main class for InitRoutes command in Command Pattern.
 *
 * Calls to \ref execute function to invoke the callback to
 * initialize the routes.
 */
class InitRoutesCommand : public MyWebServerCommand {
 public:
  explicit InitRoutesCommand(ConfigManager* cm);
  void execute(MyWebServerSession* session,
    picojson::value& command, MyWebServerSessionState* state) override;
 private:
  ConfigManager* cm;
};

#endif  // WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_
