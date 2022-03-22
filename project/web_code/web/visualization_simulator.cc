/**
 * @file visualization_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <ctime>

#include "web_code/web/visualization_simulator.h"
#include "src/bus.h"
#include "src/route.h"
#include "src/bus_depot.h"

VisualizationSimulator::VisualizationSimulator
  (WebInterface* webI, ConfigManager* configM, std::ostream* out) {
  webInterface_ = webI;
  configManager_ = configM;
  paused_ = false;  // global status for pause button
  out_ = out;  // output stream
  bus_stats_file_name = "BusData.csv";
  bus_stat_ss.str("");
  instance = FileWriterManager::GetInstance();
}

VisualizationSimulator::~VisualizationSimulator() {}

void VisualizationSimulator::TogglePause() {
  std::cout << "Toggling Pause" << std::endl;
  paused_ = !paused_;  // swith the global paused_ status
}

void VisualizationSimulator::Start
  (const std::vector<int>& busStartTimings, const int& numTimeSteps) {
  busStartTimings_ = busStartTimings;
  numTimeSteps_ = numTimeSteps;

  timeSinceLastBus_.resize(busStartTimings_.size());
  for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
    timeSinceLastBus_[i] = 0;
  }

  simulationTimeElapsed_ = 0;

  prototypeRoutes_ = configManager_->GetRoutes();
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
    prototypeRoutes_[i]->Report(*out_);

  prototypeRoutes_[i]->UpdateRouteData();
  webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
  }
}

bool VisualizationSimulator::Update() {
  // Code called to update simulator. Will first check if
  // we are in a state where we can update (e.g., not paused, not finished)
  // then call ExecuteUpdate() to actually call update if possible
  // return whether or not ExecuteUpdate() was called
  bool can_update = CanUpdate();
  if (can_update) {
    ExecuteUpdate();
  }

  return can_update;
}

bool VisualizationSimulator::CanUpdate() {
  // Check whether or not simulator can update
  // maybe unable to update because paused, terminated, etcetra
  // only cares about whether or not it is paused right now
  return !paused_;
}

void VisualizationSimulator::ExecuteUpdate() {
  // This function has the same text as what Update() used to have
  // I added a gating mechanism for pause functionality
  simulationTimeElapsed_++;

  std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
  std::cout << "~~~~~~~~~~" << std::endl;

  std::cout << "~~~~~~~~~~ Generating new busses if needed ";
  std::cout << "~~~~~~~~~~" << std::endl;

  // Check if we need to generate new busses
  for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
    // Check if we need to make a new bus
    if (0 >= timeSinceLastBus_[i]) {
      Route * outbound = prototypeRoutes_[2 * i];
      Route * inbound = prototypeRoutes_[2 * i + 1];

      // Create a bus depot for deploying bus
      BusDepot * bus_depot = new BusDepot();
      time_t timer;
      struct tm timeinfo;
      char buf[50];

      time(&timer);  // get the current time
      localtime_r(&timer, &timeinfo);  // convert it to local time

      std::cout << "Current local time is: "
                << asctime_r(&timeinfo, buf);

      // Check the range of total distance to check which
      // strategy to apply
      if (timeinfo.tm_hour >= 6 && timeinfo.tm_hour < 8) {
        // Depoly strategy 1
        bus_depot->SetStrategy(1);
      } else if (timeinfo.tm_hour >= 8 && timeinfo.tm_hour < 15) {
      // Depoly strategy 2
        bus_depot->SetStrategy(2);
      } else if (timeinfo.tm_hour >= 15 && timeinfo.tm_hour < 20) {
        // Depoly strategy 3
        bus_depot->SetStrategy(3);
      } else {
        // Set it to the default strategy
        bus_depot->SetStrategy(4);
      }

      // Generate a bus using a specific strategy
      busses_.push_back(bus_depot->Generate(std::to_string(busId),
        outbound->Clone(), inbound->Clone(), 1));
      busId++;

      // Delete the bus depot instance
      delete bus_depot;

      timeSinceLastBus_[i] = busStartTimings_[i];
      } else {
      timeSinceLastBus_[i]--;
      }
  }

  std::cout << "~~~~~~~~~ Updating busses ";
  std::cout << "~~~~~~~~~" << std::endl;

  // Update busses
  for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
    busses_[i]->Update();

    if (busses_[i]->IsTripComplete()) {
      bus_stat_ss.str("");  // empty the ostringstream
      busses_[i]->Report(bus_stat_ss);
      // Passing the information and write to the log file
      // for BusData
      instance->Write(bus_stats_file_name, Util::ProcessOutput(bus_stat_ss));
      webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
      busses_.erase(busses_.begin() + i);
      continue;
    }

    webInterface_->UpdateBus(busses_[i]->GetBusData());

    busses_[i]->Report(*out_);
  }

  std::cout << "~~~~~~~~~ Updating routes ";
  std::cout << "~~~~~~~~~" << std::endl;
  // Update routes
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
    prototypeRoutes_[i]->Update();
    webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
    prototypeRoutes_[i]->Report(*out_);
  }
}

void VisualizationSimulator::ClearBusListeners() {
  // Remove all observers for all buses
  for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
    busses_[i]->ClearObservers();
  }
}

void VisualizationSimulator::ClearStopListeners() {
  // Iterate for all routes
  for (int i = static_cast<int>(prototypeRoutes_.size()) - 1; i >= 0; i--) {
    // For a single route, query information for all stops
    std::list<Stop *> stops_ = prototypeRoutes_[i]->GetStops();
    for (std::list<Stop *>::iterator it = stops_.begin();
      it != stops_.end();
      it++) {
      // Remove all observers for all stops on this route
      (*it)->ClearObservers();
    }
  }
}
