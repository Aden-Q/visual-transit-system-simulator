/**
 * @file bus_decorator.h
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */
#ifndef SRC_BUS_DECORATOR_H_
#define SRC_BUS_DECORATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/ibus.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The decorator class for Decorator Pattern.
 *
 * Calls to \ref UpdateBusData function to decorator a bus using
 * default values.
 */
class BusDecorator : public IBus {
 public:
  explicit BusDecorator(IBus * bus_to_decorate) :
  bus_to_decorate_(bus_to_decorate) {}
  /**
  * @brief Decorate the color and intensity using default values.
  *
  * This function will be used for simulation purposes.
  *
  */
  void UpdateBusData() {
    SetColor(196, 34, 74);  // set the default color to be maroon
    SetIntensity(255);  // set the default intensity to be maximum
  }
  /**
  * @brief Change the bus color. Set it to the default marron.
  *
  * This function will be used for simulation purposes.
  *
  */
  void SetColor(int red, int green, int blue) {
    bus_to_decorate_->SetColor(red, green, blue);
  }
  /**
  * @brief Change the bus color intensity. Set it to the default value.
  *
  * This function will be used for simulation purposes.
  *
  */
  void SetIntensity(int alpha) {
    bus_to_decorate_->SetIntensity(alpha);
  }

 protected:
  IBus * bus_to_decorate_;
};

/**
 * @brief Concrete decorator for decorating bus color to be maroon.
 *
 * Calls to \ref UpdateBusData function to decorator a bus using
 * color maroon.
 */
class BusColorMaroonDecorator : public BusDecorator {
 public:
  explicit BusColorMaroonDecorator(IBus * bus_to_decorate)
    : BusDecorator(bus_to_decorate) {}
  /**
  * @brief Decorate the bus color to be maroon.
  *
  * This function will be used for simulation purposes.
  *
  */
  void UpdateBusData() {
    SetColor(196, 34, 74);  // set the color to be maroon
  }
};


/**
 * @brief Concrete decorator for decorating bus color to be gold.
 *
 * Calls to \ref UpdateBusData function to decorator a bus using
 * color gold.
 */
class BusColorGoldDecorator : public BusDecorator {
 public:
  explicit BusColorGoldDecorator(IBus * bus_to_decorate)
    : BusDecorator(bus_to_decorate) {}
  /**
  * @brief Decorate the bus color to be gold.
  *
  * This function will be used for simulation purposes.
  *
  */
  void UpdateBusData() {
    SetColor(206, 163, 53);  // set the color to be gold
  }
};

/**
 * @brief Concrete decorator for decorating intensity.
 *
 * Calls to \ref SetIntensity function to decorator a bus's color intensity.
 */
class BusIntensityDecorator : public BusDecorator {
 public:
  explicit BusIntensityDecorator(IBus * bus_to_decorate)
    : BusDecorator(bus_to_decorate) {}
  /**
  * @brief Decorate the bus color intensity based on the number of
  * passengers on the bus.
  *
  * This function will be used for simulation purposes.
  *
  * @param[in] alpha Intensity value to be set
  */
  void SetIntensity(int alpha) {
    bus_to_decorate_->SetIntensity(alpha);
  }
};

#endif  // SRC_BUS_DECORATOR_H_
