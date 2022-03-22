/**
 * @file stop_UT.cc
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
#include "../src/stop.h"
#include "../src/bus.h"
#include "../src/route.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class StopTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Stop *stop, *stop1, *stop2;
  // Bus *bus;
  // Route *out, *in;
  // Passenger *passenger;
  // PassengerGenerator *passGenerator;
    
  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete stop;
    
    stop = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(StopTests, ConstructorTests) {
  stop = new Stop(5);
  stop1 = new Stop(10, 50.0);
  stop2 = new Stop(-1, 35.5, -34.7);
  // test GetId
  EXPECT_EQ(stop->GetId(), 5);
  EXPECT_EQ(stop1->GetId(), 10);
  EXPECT_EQ(stop2->GetId(), -1);
  // test GetLongitude
  EXPECT_EQ(stop->GetLongitude()-44.973723 < 1e-6, true);
  EXPECT_EQ(stop1->GetLongitude()-50.0 < 1e-6, true);
  EXPECT_EQ(stop2->GetLongitude()-35.5 < 1e-6, true);
  // test GetLatitude
  EXPECT_EQ(stop->GetLatitude()+93.235365 < 1e-6, true);
  EXPECT_EQ(stop1->GetLatitude()+93.235365 < 1e-6, true);
  EXPECT_EQ(stop2->GetLatitude()+34.7 < 1e-6, true);
  // test GetNumPassengerPresent
  EXPECT_EQ((int)stop->GetNumPassengersPresent(), 0);

  delete stop1;
  delete stop2;
  stop1 = NULL;
  stop2 = NULL;
};

