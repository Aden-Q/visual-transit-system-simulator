/**
 * @file passenger_loader.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/passenger_loader.h"

bool PassengerLoader::LoadPassenger(Passenger * new_passenger, int max_pass,
                                   std::list<Passenger *> * passengers) {
  // Normally would use a boolean, but for extensibility,
  // using count of those added_passenger
  // Currently, only one could be added, so possible values are 0 or 1.
  bool added_passenger = false;
  // Check whether space permitted to load more passengers
  if (static_cast<int>((*passengers).size()) < max_pass) {
    (*passengers).push_back(new_passenger);
    new_passenger->GetOnBus();
    added_passenger = true;
  }

  return added_passenger;
}
