/**
 * @file bus_types.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */
#include "src/bus_factory.h"

/***********************
 * Member Functions
 ***********************/
// Code for generation of a bus
Bus * BusFactory::Generate(std::string name, Route * outbound,
    Route * inbound, double speed) {
    int rand_int = GetRandomInteger();

    // Check which type of bus needs to be create
    if (type_ == "Small" || (type_ == "Random" && rand_int == 1)) {
        return new SmallBus(name, outbound, inbound, speed);
    } else if (type_ == "Medium" || (type_ == "Random" && rand_int == 2)) {
        return new MediumBus(name, outbound, inbound, speed);
    } else if (type_ == "Large" || (type_ == "Random" && rand_int == 3)) {
        return new LargeBus(name, outbound, inbound, speed);
    } else {
        std::cout << "type_: " << type_ << std::endl;
        throw "Type must be Small, Medium, Large or Random";
    }
}

int BusFactory::GetRandomInteger() {
  // Random integer generation to determine the bus type.
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 3);
  int rand_int = dist1(rng);
  return rand_int;
}
