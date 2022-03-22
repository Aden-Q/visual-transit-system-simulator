/**
 * @file bus_types.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <random>

#include "src/bus.h"
#include "src/bus_types.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for bus factories.
 *
 * Calls to \ref Generate function to generate a certain type of bus.
 */
class BusFactory {
 public:  // public reporter
  explicit BusFactory(std::string type) : type_(type) {}
 /**
  * @brief Generate a certain type of bus with some speed on a certain route
  * specified by the parameters.
  * 
  * This function will be used for simulation purposes.
  */
  Bus * Generate(std::string name, Route * outbound, Route * inbound,
                  double speed = 1);

 private:  // private reporter
  int GetRandomInteger();
  std::string type_;
};

#endif  // SRC_BUS_FACTORY_H_
