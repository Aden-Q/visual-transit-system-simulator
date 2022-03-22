/**
 * @file bus_types.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_TYPES_H_
#define SRC_BUS_TYPES_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/bus.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for small buses.
 *
 */
class SmallBus : public Bus {
 public:
  SmallBus(std::string name, Route* out, Route* in, double speed):
      Bus(name, out, in, 30, speed, "Small") { }
};

/**
 * @brief The main class for small buses.
 *
 */
class MediumBus : public Bus {
 public:
  MediumBus(std::string name, Route* out, Route* in, double speed):
      Bus(name, out, in, 60, speed, "Medium") { }
};

/**
 * @brief The main class for small buses.
 *
 */
class LargeBus : public Bus {
 public:
  LargeBus(std::string name, Route* out, Route* in, double speed):
      Bus(name, out, in, 90, speed, "Large") { }
};

#endif  // SRC_BUS_TYPES_H_
