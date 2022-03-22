/**
 * @file route_UT.cc
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
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include <../src/route.h>

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RouteTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  PassengerGenerator* pass_generator;
  Route* route;
  list<double> generator_probs;
  list<Stop *> generator_stops;
    
  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
    pass_generator = new RandomPassengerGenerator(generator_probs, generator_stops);
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete pass_generator;
    delete route;
    
    pass_loader = NULL;
    pass_unloader = NULL;
    pass_generator = NULL;
    route = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(RouteTests, ConstructorTests) {
  // supposing 6 stops there
  string route_name = "MyRoute";
  int num_stops = 6;
  double distances[5] = {5.0, 10.0, 13.5, 14.3, 16.4};
  Stop **stops = NULL;
  stops = new Stop*[num_stops];
  for (int i=0; i<num_stops; i++) {
      stops[i] = new Stop(i);
  }
  route = new Route(route_name, stops, distances, num_stops, pass_generator);
  // test PrevStop
  Stop * prev = route->PrevStop();
  EXPECT_EQ(prev, stops[0]);
  // test GetDestinationStop
  EXPECT_EQ(route->GetDestinationStop(), stops[0]);  
  // test GetTotalRouteDistance
  EXPECT_EQ(route->GetTotalRouteDistance()-59.2 < 1e-6, true);
  // test GetNextStopDistance
  EXPECT_EQ(route->GetNextStopDistance(), 0);
  // test GetName
  EXPECT_EQ(route->GetName(), route_name);
  // test GetStops
  list<Stop *> stops_;
  stops_ = route->GetStops();
  bool check_flag = true;
  int i = 0;
  for (list<Stop *>::iterator it = stops_.begin();
       it != stops_.end();
       it++, i++) {
      if (*it != stops[i]) {
          check_flag = false;
          break;
      }
  }
  EXPECT_EQ(check_flag, true);
  // GetRouteData
  RouteData route_data = route->GetRouteData();
  RouteData expected_route_data = RouteData();
  bool flag = true;
  if (expected_route_data.id != route_data.id) {
      flag = false;
  }
  else if (route_data.stops.size() != expected_route_data.stops.size()) {
      flag = false;
  }
  EXPECT_EQ(flag, true);
  // free memory
  for (int i=0; i<num_stops; i++) {
      delete stops[i];
  }
  delete [] stops;
};

// tset IsAtEnd
TEST_F(RouteTests, IsAtEndTests) {
   // supposing 6 stops there
  string route_name = "MyRoute";
  int num_stops = 4;
  double distances[3] = {13.5, 14.3, 16.4};
  Stop **stops = NULL;
  stops = new Stop*[num_stops];
  for (int i=0; i<num_stops; i++) {
      stops[i] = new Stop(i);
  }
  route = new Route(route_name, stops, distances, num_stops, pass_generator); 
  //test IsAtEnd
  EXPECT_EQ(route->IsAtEnd(), false);
  route->ToNextStop();
  EXPECT_EQ(route->IsAtEnd(), false);
  route->ToNextStop();
  EXPECT_EQ(route->IsAtEnd(), false);
  route->ToNextStop(); 
  EXPECT_EQ(route->IsAtEnd(), false);
  route->ToNextStop();
  EXPECT_EQ(route->IsAtEnd(), true);
  // free memory
  for (int i=0; i<num_stops; i++) {
      delete stops[i];
  }
  delete [] stops;
}

