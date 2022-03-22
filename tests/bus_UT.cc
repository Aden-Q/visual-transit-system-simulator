/**
 * @file bus_UT.cc
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"
#include "../src/route.h"
#include "../src/stop.h"
#include "../src/bus.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BusTests : public ::testing::Test {
 protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  PassengerGenerator* pass_generator;
  Passenger * passenger;
  Bus *bus, *bus1, *bus2;
  Route *out, *in;
  list<double> generator_probs;
  list<Stop *> generator_stops;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
    pass_generator =
      new RandomPassengerGenerator(generator_probs, generator_stops);
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;

    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BusTests, ConstructorTests) {
  // supposing 6 stops there
  string route_name_out = "MyOutRoute";
  int num_stops_out = 6;
  double distances_out[5] = {0.5, 0.3, 0.7, 0.3, 1.4};
  Stop **stops_out = NULL;
  stops_out = new Stop*[num_stops_out];
  for (int i=0; i < num_stops_out; i++) {
      stops_out[i] = new Stop(i+5);
  }
  out = new Route
    (route_name_out, stops_out, distances_out, num_stops_out, pass_generator);

  // support 5 stops there
  string route_name_in = "MyInRoute";
  int num_stops_in = 5;
  double distances_in[4] = {1.3, 2.5, 0.8, 0.5};
  Stop **stops_in = NULL;
  stops_in = new Stop*[num_stops_in];
  for (int i=0; i < num_stops_in; i++) {
      stops_in[i] = new Stop(i);
  }
  in = new Route
    (route_name_in, stops_in, distances_in, num_stops_in, pass_generator);

  bus = new Bus("MyBus", out, in);
  // test GetBusData
  BusData bus_data = bus->GetBusData();
  EXPECT_EQ(bus_data.id, "");
  EXPECT_EQ(bus_data.num_passengers, 0);
  EXPECT_EQ(bus_data.capacity, 0);
  EXPECT_EQ(bus_data.position.x-0 < 1e-6, true);
  EXPECT_EQ(bus_data.position.y-0 < 1e-6, true);
  // test GetName
  EXPECT_EQ(bus->GetName(), "MyBus");
  // test GetNextStop
  Stop * next_stop = bus->GetNextStop();
  EXPECT_EQ(next_stop, stops_out[0]);
  // test GetNumPassengers
  EXPECT_EQ((int)bus->GetNumPassengers(), 0);
  // test GetCapacity
  EXPECT_EQ(bus->GetCapacity(), 60);

  // free memory
  delete in;
  delete out;
  for (int i=0; i < num_stops_out; i++) {
      delete stops_out[i];
  }
  delete [] stops_out;
  for (int i=0; i < num_stops_in; i++) {
      delete stops_in[i];
  }
  delete [] stops_in;
}

// test IsTripComplete
TEST_F(BusTests, IsTripCompleteTests) {
  // supposing 6 stops there
  string route_name_out = "MyOutRoute";
  int num_stops_out = 4;
  double distances_out[3] = {0.9, 0.95, 0.9};
  Stop **stops_out = NULL;
  stops_out = new Stop*[num_stops_out];
  for (int i=0; i < num_stops_out; i++) {
      stops_out[i] = new Stop(i+3);
  }
  out = new Route
    (route_name_out, stops_out, distances_out, num_stops_out, pass_generator);

  // support 5 stops there
  string route_name_in = "MyInRoute";
  int num_stops_in = 3;
  double distances_in[2] = {0.85, 0.95};
  Stop **stops_in = NULL;
  stops_in = new Stop*[num_stops_in];
  for (int i=0; i < num_stops_in; i++) {
      stops_in[i] = new Stop(i);
  }

  in = new Route
    (route_name_in, stops_in, distances_in, num_stops_in, pass_generator);

  bus = new Bus("MyBus", out, in);
  // test IsTripComplete
  // originally the trip is not complete
  EXPECT_EQ(bus->IsTripComplete(), false);
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // out route stop 1
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // out route stop 2
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // out route stop 3
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // in route stop 3
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // in route stop 2
  cout << bus->Move() << endl;
  EXPECT_EQ(bus->IsTripComplete(), false);  // in route stop 1
  cout << bus->Move() << endl;
  // in route stop 2, complete the trip
  EXPECT_EQ(bus->IsTripComplete(), true);

  // free memory
  delete in;
  delete out;
  for (int i=0; i < num_stops_out; i++) {
      delete stops_out[i];
  }
  delete [] stops_out;
  for (int i=0; i < num_stops_in; i++) {
      delete stops_in[i];
  }
  delete [] stops_in;
}

// test Move
TEST_F(BusTests, MoveTests) {
  // supposing 6 stops there
  string route_name_out = "MyOutRoute";
  int num_stops_out = 4;
  double distances_out[3] = {0.5, 0.3, 0.7};
  Stop **stops_out = NULL;
  stops_out = new Stop*[num_stops_out];
  for (int i=0; i < num_stops_out; i++) {
      stops_out[i] = new Stop(i+3);
  }
  out = new Route
    (route_name_out, stops_out, distances_out, num_stops_out, pass_generator);

  // support 5 stops there
  string route_name_in = "MyInRoute";
  int num_stops_in = 3;
  double distances_in[2] = {2.5, 0.8};
  Stop **stops_in = NULL;
  stops_in = new Stop*[num_stops_in];
  for (int i=0; i < num_stops_in; i++) {
      stops_in[i] = new Stop(i);
  }
  in = new Route
    (route_name_in, stops_in, distances_in, num_stops_in, pass_generator);

  bus = new Bus("MyBus", out, in);
  bus1 = new Bus("MyBus1", out, in, 60, -1);  // negative speed
  // test Move
  EXPECT_EQ(bus1->Move(), false);  // always false for negative speed

  // free memory
  delete in;
  delete out;
  for (int i=0; i < num_stops_out; i++) {
      delete stops_out[i];
  }
  delete [] stops_out;
  for (int i=0; i < num_stops_in; i++) {
      delete stops_in[i];
  }
  delete [] stops_in;
}

// test LoadPassenger
TEST_F(BusTests, LoadPassengerTests) {
  // supposing 6 stops there
  string route_name_out = "MyOutRoute";
  int num_stops_out = 4;
  double distances_out[3] = {0.5, 0.3, 0.7};
  Stop **stops_out = NULL;
  stops_out = new Stop*[num_stops_out];
  for (int i=0; i < num_stops_out; i++) {
      stops_out[i] = new Stop(i+3);
  }
  out = new Route
    (route_name_out, stops_out, distances_out, num_stops_out, pass_generator);

  // support 5 stops there
  string route_name_in = "MyInRoute";
  int num_stops_in = 3;
  double distances_in[2] = {2.5, 0.8};
  Stop **stops_in = NULL;
  stops_in = new Stop*[num_stops_in];
  for (int i=0; i < num_stops_in; i++) {
      stops_in[i] = new Stop(i);
  }
  in = new Route
    (route_name_in, stops_in, distances_in, num_stops_in, pass_generator);

  bus = new Bus("MyBus", out, in, 3);

  passenger = new Passenger();

  // test LoadPassenger
  EXPECT_EQ(bus->LoadPassenger(passenger), true);
  EXPECT_EQ(bus->LoadPassenger(passenger), true);
  EXPECT_EQ(bus->LoadPassenger(passenger), true);
  EXPECT_EQ(bus->LoadPassenger(passenger), false);

  // free memory
  delete in;
  delete out;
  for (int i=0; i < num_stops_out; i++) {
      delete stops_out[i];
  }
  delete [] stops_out;
  for (int i=0; i < num_stops_in; i++) {
      delete stops_in[i];
  }
  delete [] stops_in;
}
