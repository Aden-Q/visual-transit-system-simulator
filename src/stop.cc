/**
 * @file stop.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <vector>
#include "src/stop.h"

// Defaults to Westbound Coffman Union stop
Stop::Stop(int id, double longitude,
        double latitude) : id_(id), longitude_(longitude), latitude_(latitude) {
  // no initialization of list of passengers necessary
  passengers_.clear();
}

int Stop::LoadPassengers(Bus * bus) {
  int passengers_added = 0;

  // Assumption: Stop is UNIQUE to route.
  //      All passengers at stop MUST
  //      be waiting for THIS bus
  // Consideration: Can we use remove_if here? Probably more useful
  // if the stops had passengers for more than just this unique route
  while (!passengers_.empty() &&   // still passengers waiting to get on the bus
         bus->LoadPassenger(passengers_.front())) {  // AND they are ON the bus
    passengers_.pop_front();                    // THEN they have left the stop
    passengers_added++;
  }
  return passengers_added;
}

int Stop::AddPassengers(Passenger * pass) {
  // we're using int here to aid potential future work:
  //  we may modify this to allow more multiple adds
  //  in a single call. For the moment, the var is
  //  used as a flag: 0 - fail; 1 - pass
  int passengers_added_to_stop = 0;

  passengers_.push_back(pass);
  passengers_added_to_stop++;

  return passengers_added_to_stop;
}

void Stop::Update() {
  // Update all passengers at this stop
  for (std::list<Passenger *>::iterator it = passengers_.begin();
                                    it != passengers_.end(); it++) {
    (*it)->Update();
  }

  UpdateStopData();
  NotifyObservers(&stop_data_);
}

int Stop::GetId() const {
  return id_;
}

void Stop::Report(std::ostream& out) const {
  out << "ID: " << id_ << std::endl;
  out << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
                                        it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

// Update the stop_data_ variable
void Stop::UpdateStopData() {
  // Due to type mismatch, we need to convert explicitly
  stop_data_.id = std::to_string(id_);

  // Get the stop position, which is fixed
  Position p;
  p.x = GetLongitude();
  p.y = GetLatitude();
  stop_data_.position = p;

  // Number of passengers waiting at the stop
  stop_data_.num_people = static_cast<int>(passengers_.size());
}

StopData Stop::GetStopData() const {
  return stop_data_;
}
