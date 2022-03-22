/**
 * @file bus_depot.cc
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#include "src/bus_depot.h"

/*******************************************************************************
 * Static Variable Initialization
 ******************************************************************************/
BusFactory * Strategy::small_bus_factory_ = new BusFactory("Small");
BusFactory * Strategy::medium_bus_factory_ = new BusFactory("Medium");
BusFactory * Strategy::large_bus_factory_ = new BusFactory("Large");
int StrategyA::state_ = 0;
int StrategyB::state_ = 1;
int StrategyC::state_ = 0;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BusDepot::SetStrategy(int type) {
  // Delete the existing strategy_ to avoid memory leak
  delete strategy_;

  // Check which type of strategy to set
  if (type == 1) {
    strategy_ = new StrategyA();
  } else if (type == 2) {
    strategy_ = new StrategyB();
  } else if (type == 3) {
    strategy_ = new StrategyC();
  } else {
    // Only get here by default (non of the above values are specified)
    strategy_ = new StrategyD();
  }
}

Bus * BusDepot::Generate(std::string name,
  Route * outbound, Route * inbound, double speed) {
  // Invoke the method from a specific strategy to generate a bus
  return strategy_->GenerateBus(name, outbound, inbound, speed);
}

// Implementation of strategy A for generating bus
// generate small and regular bus alternatively
Bus * StrategyA::GenerateBus(std::string name,
  Route * outbound, Route * inbound, double speed) {
  Bus * new_bus = NULL;

  // Check global state to decide to generate which type of bus
  if (state_ % 2 == 0) {
    std::cout << "Deploying strategy 1, "
              << "bus size Small"
              << std::endl;
    new_bus = small_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 1;  // switch the global state to generate another bus next time
  } else if (state_ % 2 == 1) {
    std::cout << "Deploying strategy 1, "
              << "bus size Medium"
              << std::endl;
    new_bus = medium_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 0;  // switch the global state to generate another bus next time
  }

  return new_bus;
}

// Implementation of strategy B for generating bus
// generate regualr and large bus alternatively
Bus * StrategyB::GenerateBus(std::string name,
  Route * outbound, Route * inbound, double speed) {
  Bus * new_bus = NULL;

  // Check global state to decide to generate which type of bus
  if (state_ % 3 == 1) {
    std::cout << "Deploying strategy 2, "
              << "bus size Medium"
              << std::endl;
    new_bus = medium_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 2;  // switch the global state to generate another bus next time
  } else if (state_ % 3 == 2) {
    std::cout << "Deploying strategy 2, "
              << "bus size Large"
              << std::endl;
    new_bus = large_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 1;  // switch the global state to generate another bus next time
  }

  return new_bus;
}

// Implementation of strategy C for generating bus
// generate small, regualr and large bus alternatively
Bus * StrategyC::GenerateBus(std::string name,
  Route * outbound, Route * inbound, double speed) {
  Bus * new_bus = NULL;

  // Check global state to decide to generate which type of bus
  if (state_ % 3 == 0) {
    std::cout << "Deploying strategy 3, "
              << "bus size Small"
              << std::endl;
    new_bus = small_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 1;  // switch the global state to generate another bus next time
  } else if (state_ % 3 == 1) {
    std::cout << "Deploying strategy 3, "
              << "bus size Medium"
              << std::endl;
    new_bus = medium_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 2;  // switch the global state to generate another bus next time
  } else if (state_ % 3 == 2) {
    std::cout << "Deploying strategy 3, "
              << "bus size large"
              << std::endl;
    new_bus = large_bus_factory_->Generate(name, outbound, inbound, speed);
    state_ = 0;  // switch the global state to generate another bus next time
  }

  return new_bus;
}

// Implementation of strategy D for generating bus
// generate small bus only
Bus * StrategyD::GenerateBus(std::string name,
  Route * outbound, Route * inbound, double speed) {
  std::cout << "Deploying small bus strategy, "
            << "bus size Small"
            << std::endl;

  Bus * new_bus = small_bus_factory_->Generate(name, outbound, inbound, speed);

  return new_bus;
}
