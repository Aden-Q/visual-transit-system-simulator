 /**
 * @file visualization_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_
#define WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>
#include <string>

#include "web_code/web/web_interface.h"
#include "src/config_manager.h"
#include "src/iobserver.h"
#include "src/file_writer.h"
#include "src/file_writer_manager.h"
#include "src/util.h"

class Route;
class Bus;
class Stop;
class FileWriterManager;
class Util;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for visualization simulators.
 *
 * Calls to \ref Pause function to pause or resume the simulation.
 * Calls to \ref ClearBusListeners function to clear all the observers for buses.
 * Calls to \ref AddBusListener to register an observer for a bus.
 * Calls to \ref ClearStopListeners function to clear all the observers for stops.
 * Calls to \ref AddStopListener to register an observer for a stop.
 */
class VisualizationSimulator {
 public:
  VisualizationSimulator(WebInterface*, ConfigManager*, std::ostream*);
  ~VisualizationSimulator();

  /**
   * @brief Start virsual simulation.
   *
   * This function will be used for simulation purposes.
   */
  void Start(const std::vector<int>&, const int&);
  /**
   * @brief Start virsual simulation.
   *
   * This function is invoked to update the simulation.
   * @return: bool indicator of success or not.
   */
  bool Update();
  /**
   * @brief Check whether update is allowed.
   *
   * This function is invoked to update the simulation.
   * @return: bool indicator.
   */
  bool CanUpdate();
  /**
   * @brief Invoked when the mouse taggle on the pause button.
   *
   * This function is invoked to update the simulation.
   */
  void TogglePause();
  /**
   * @brief Clear all the observers for all buses.
   *
   * This function will be used for simulation purposes.
   */
  void ClearBusListeners();
  /**
   * @brief Register an observers to a bus specified by bus name.
   *
   * This function will be used for simulation purposes.
   *
   * @param[in] id A string of Bus name
   * @param[in] observer Observer to be registered
   */
  template <typename T>
  void AddBusListener(std::string * id, IObserver<T> * observer);
  /**
   * @brief Clear all the observers for all stops.
   *
   * This function will be used for simulation purposes.
   */
  void ClearStopListeners();
  /**
   * @brief Register an observers to a stop specified by stop name.
   *
   * This function will be used for simulation purposes.
   *
   * @param[in] id A string of Stop ID
   * @param[in] observer Observer to be registered
   */
  template <typename T>
  void AddStopListener(std::string * id, IObserver<T> * observer);

 private:
  /**
   * @brief Execute the Update function once the callback function
   * is invoked.
   *
   * This function will be used for simulation purposes.
   */
  void ExecuteUpdate();
  WebInterface* webInterface_;
  ConfigManager* configManager_;

  std::vector<int> busStartTimings_;
  std::vector<int> timeSinceLastBus_;
  int numTimeSteps_;
  int simulationTimeElapsed_;

  std::vector<Route *> prototypeRoutes_;
  std::vector<Bus *> busses_;

  int busId = 1000;
  bool paused_;  // global state, indices pause or resume
  std::ostream* out_;
  std::string bus_stats_file_name;
  std::ostringstream bus_stat_ss;
  FileWriter * instance;
};

template <typename T>
void VisualizationSimulator::AddBusListener
  (std::string * id, IObserver<T> * observer) {
  // Iterate through the bus vector
  for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
    // Check whether the Bus id matches
    if (busses_[i]->GetName() == *id) {
      busses_[i]->RegisterObserver(observer);
    }
  }
}

template <typename T>
void VisualizationSimulator::AddStopListener
  (std::string * id, IObserver<T> * observer) {
  // Iterate for all routes
  for (int i = static_cast<int>(prototypeRoutes_.size()) - 1; i >= 0; i--) {
    // For a single route, query information for all stops
    std::list<Stop *> stops_ = prototypeRoutes_[i]->GetStops();
    for (std::list<Stop *>::iterator it = stops_.begin();
      it != stops_.end();
      it++) {
      // Check whether the Stop id matches
      if (std::to_string((*it)->GetId()) == *id) {
        (*it)->RegisterObserver(observer);
      }
    }
  }
}

#endif  // WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_
