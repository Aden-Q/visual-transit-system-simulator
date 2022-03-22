/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>

#include "src/data_structs.h"
#include "src/passenger.h"
#include "src/passenger_loader.h"
#include "src/passenger_unloader.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/ibus.h"
#include "src/bus_decorator.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Bus.
 *
 * Implement the Subject Interface in Observer Pattern.
 */
class Bus : public IBus {
 public:
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                      double speed = 1, std::string type = "Medium");
  bool IsTripComplete();
  bool LoadPassenger(Passenger *);  // returning revenue delta
  bool Move();
  void Update();
  void Report(std::ostream&);

  // Vis Getters
  void UpdateBusData();
  BusData GetBusData() const;
  void SetColor(int red, int green, int clue);
  void SetIntensity(int alpha);
  std::string GetName() const { return name_; }
  Stop * GetNextStop() const { return next_stop_; }
  size_t GetNumPassengers() const { return passengers_.size(); }
  int GetCapacity() const { return passenger_max_capacity_; }

 protected:
  int total_passenger_;  // total number of passengers riding the bus

 private:
  int UnloadPassengers();  // returning revenue delta
  int HandleBusStop();
  void ToNextStop();
  double UpdateDistance();
  Route * CurrentRoute();
  // bool Refuel();
  PassengerUnloader * unloader_;
  PassengerLoader * loader_;
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  // double revenue_; // revenue collected from passengers, doesn't include
                     // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  std::string name_;
  std::string type_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  Stop * next_stop_;
  // bool trip_complete_;  // [DERIVED data] when BOTH routes are at end, trip
  // is complete

  // Vis data for bus
  BusData bus_data_;
};

#endif  // SRC_BUS_H_
