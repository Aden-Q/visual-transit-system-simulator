/**
 * @file iobserver.h
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */
#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/data_structs.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The Observer Abstract Interface Class in Observer Pattern.
 *
 * Calls to \ref Notify to notify all observers.
 */
template <typename T>
class IObserver {
 public:
 /**
  * @brief Notify an observer.
  *
  * Pure vitural function, abstract interface.
  *
  * @param[in] info BusData or StopData information, pointer type
  */
  virtual void Notify(T info) = 0;
};

#endif  // SRC_IOBSERVER_H_
