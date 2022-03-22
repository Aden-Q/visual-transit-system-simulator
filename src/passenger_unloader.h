/**
 * @file passenger_unloader.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_UNLOADER_H_
#define SRC_PASSENGER_UNLOADER_H_
#include <list>
#include <string>
#include "src/passenger.h"
#include "src/stop.h"
#include "src/file_writer.h"
#include "src/file_writer_manager.h"
#include "src/util.h"

class Stop;
class Passenger;
class FileWriterManager;
class Util;

class PassengerUnloader {
 public:
  PassengerUnloader() : passenger_file_name("PassData.csv") {
    pass_ss.str("");
    instance = FileWriterManager::GetInstance();
  }
  // UnloadPassengers returns the number of passengers removed from the bus.
  int UnloadPassengers(std::list<Passenger*>* passengers, Stop * current_stop);

 private:
  // Stringstream for logging purpose
  std::string passenger_file_name;
  std::ostringstream pass_ss;
  FileWriter * instance;
};
#endif  // SRC_PASSENGER_UNLOADER_H_
