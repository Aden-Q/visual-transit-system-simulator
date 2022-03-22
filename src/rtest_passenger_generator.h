/**
 * @file rtest_passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_RTEST_PASSENGER_GENERATOR_H_
#define SRC_RTEST_PASSENGER_GENERATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <random>
#include <ctime>

#include "src/passenger_generator.h"
#include "src/stop.h"

class Stop;  // forward declaration

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The Generator Class for regression test.
 *
 * Calls to \ref GeneratePassengers to generate passengers.
 */
class RtestPassengerGenerator : public PassengerGenerator{
 public:
  RtestPassengerGenerator(std::list<double>, std::list<Stop *>);
 /**
  * @brief Notify an observer.
  *
  * Pure vitural function, abstract interface.
  *
  * @param[in] info BusData information
  */
  int GeneratePassengers() override;

 private:
  static std:: minstd_rand0 my_rand;
};

#endif  // SRC_RTEST_PASSENGER_GENERATOR_H_
