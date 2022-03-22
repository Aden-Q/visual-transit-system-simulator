/**
 * @file bus_depot.h
 *
 * @copyright 2020 Zecheng Qian. All rights reserved.
 */
#ifndef SRC_BUS_DEPOT_H_
#define SRC_BUS_DEPOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <random>
#include <iostream>

#include "src/bus.h"
#include "src/bus_factory.h"

class Strategy;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for bus depot.
 *
 * Calls to \ref SetStrategy function to set a type of strategy.
 *
 * Calls to \ref GenerateBus function to generate a type of bus
 * using Strategy Pattern.
 */
class BusDepot {
 public:  // public Reporter
  BusDepot() : strategy_(NULL) {}
  ~BusDepot() {}
 /**
  * @brief Set a specific strategy for generating buses.
  *
  * This function will be used for simulation purposes.
  *
  * @param[in] type A type of strategy
  */
  void SetStrategy(int type);
 /**
  * @brief Generate a type of bus using a specific strategy.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] speed Bus speed
  * @return Bus object with name, route, type and speed.
  */
  Bus * Generate(std::string name, Route * outbound, Route * inbound,
                    double speed);

 private:
  Strategy * strategy_;
};

/**
 * @brief The Strategy Abstract Interface Class.
 *
 * Calls to \ref GenerateBus function to generate a type of bus
 * using a type of strategy.
 */
class Strategy {
 public:
  virtual ~Strategy() {}
 /**
  * @brief Generate a type of bus using a type of strategy.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] Bus speed
  * @return Bus object with name, route, type and speed.
  */
  virtual Bus * GenerateBus(std::string name,
    Route * outbound, Route * inbound, double speed) = 0;

 protected:
  static BusFactory * small_bus_factory_;
  static BusFactory * medium_bus_factory_;
  static BusFactory * large_bus_factory_;
};

/**
 * @brief One of the strategy implementations.
 *
 * Calls to \ref GenerateBus function to generate small and regular buses
 * alternatively.
 */
class StrategyA : public Strategy {
 public:
  StrategyA() {}
  ~StrategyA() {}
 /**
  * @brief Generate a type of bus using strategy 1.
  *
  * Generate small and regular buses alternatively.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] Bus speed
  * @return Bus object with name, route, type and speed.
  */
  Bus * GenerateBus(std::string name,
    Route * outbound, Route * inbound, double speed) override;

 private:
  static int state_;
};

/**
 * @brief One of the strategy implementations.
 *
 * Calls to \ref GenerateBus function to generate regular and large buses
 * alternatively.
 */
class StrategyB : public Strategy {
 public:
  StrategyB() {}
  ~StrategyB() {}
 /**
  * @brief Generate a type of bus using strategy 2.
  *
  * Generate regular and large buses alternatively.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] Bus speed
  * @return Bus object with name, route, type and speed.
  */
  Bus * GenerateBus(std::string name,
    Route * outbound, Route * inbound, double speed) override;

 private:
  static int state_;
};

/**
 * @brief One of the strategy implementations.
 *
 * Calls to \ref GenerateBus function to generate small, 
 * regular and large buses alternatively.
 */
class StrategyC : public Strategy {
 public:
  StrategyC() {}
  ~StrategyC() {}
 /**
  * @brief Generate a type of bus using strategy 3.
  *
  * Generate small, regular and large buses alternatively.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] Bus speed
  * @return Bus object with name, route, type and speed.
  */
  Bus * GenerateBus(std::string name,
    Route * outbound, Route * inbound, double speed) override;

 private:
  static int state_;
};

/**
 * @brief One of the strategy implementations.
 *
 * Calls to \ref GenerateBus function to generate small buses only.
 */
class StrategyD : public Strategy {
 public:
  StrategyD() {}
  ~StrategyD() {}
 /**
  * @brief Generate a type of bus using default strategy.
  *
  * Generate only small buses.
  *
  * @param[in] name Bus name
  * @param[in] outbound Outgoing route
  * @param[in] inbound Ingoing route
  * @param[in] Bus speed
  * @return Bus object with name, route, type and speed.
  */
  Bus * GenerateBus(std::string name,
    Route * outbound, Route * inbound, double speed) override;
};

#endif  // SRC_BUS_DEPOT_H_
