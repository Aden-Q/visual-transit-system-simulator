/**
 * @file ibus.h
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */
#ifndef SRC_IBUS_H_
#define SRC_IBUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/iobservable.h"
#include "src/data_structs.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The abstract interface for Decorator Pattern.
 * 
 */
class IBus : public IObservable<BusData *> {
 public:
  virtual ~IBus() { }
  /**
  * @brief Different implementation for decorator and concrete component,
  * the implementation for decorator will change the color or intensity.
  *
  */
  virtual void UpdateBusData() = 0;
  /**
  * @brief Change the bus color.
  *
  */
  virtual void SetColor(int red, int green, int blue) = 0;
  /**
  * @brief Change the bus color intensity.
  *
  */
  virtual void SetIntensity(int alpha) = 0;
};

#endif  // SRC_IBUS_H_
