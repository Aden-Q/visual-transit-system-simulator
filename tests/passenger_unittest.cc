/**
 * @file passenger_unittest.cc
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
 protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Passenger *passenger, *passenger1, *passenger2;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete passenger;
    passenger = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
// test constructor
TEST_F(PassengerTests, ConstructorTests) {
  passenger = new Passenger();
  passenger1 = new Passenger(-5, "Somebody");
  passenger2 = new Passenger(5);

  // test IsOnBus
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
  // test GetDestination
  EXPECT_EQ(passenger->GetDestination(), -1);
  EXPECT_EQ(passenger1->GetDestination(), -5);
  EXPECT_EQ(passenger2->GetDestination(), 5);
  // test GetTotalWait
  EXPECT_EQ(passenger->GetTotalWait(), 1);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 2);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 3);
  EXPECT_EQ(passenger1->GetTotalWait(), 0);
  passenger1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 1);
  passenger1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 2);
  passenger1->GetOnBus();
  EXPECT_EQ(passenger1->GetTotalWait(), 3);
  passenger1->Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 4);
  // test IsOnBus again
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);

  delete passenger1;
  delete passenger2;
  passenger1 = NULL;
  passenger2 = NULL;
}

// test GetOnBus
TEST_F(PassengerTests, GetOnBusTests) {
  passenger = new Passenger();
  passenger1 = new Passenger(-5, "Somebody");
  passenger2 = new Passenger(5);

  // test GetOnBus function
  EXPECT_EQ(passenger->GetTotalWait(), 0);
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->GetTotalWait(), 1);
  EXPECT_EQ(passenger->IsOnBus(), true);

  delete passenger1;
  delete passenger2;
  passenger1 = NULL;
  passenger2 = NULL;
}

// test Update
TEST_F(PassengerTests, UpdateTests) {
  passenger = new Passenger();
  EXPECT_EQ(passenger->GetTotalWait(), 0);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 1);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 2);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->GetTotalWait(), 3);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 4);
  passenger->Update();
  EXPECT_EQ(passenger->GetTotalWait(), 5);
}

// test Report
TEST_F(PassengerTests, ReportTests) {
  passenger = new Passenger();
  passenger1 = new Passenger(5);
  passenger2 = new Passenger(10, "Bob");

  testing::internal::CaptureStdout();
  passenger->Report(cout);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  passenger1->Report(cout);
  std::string output2 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  passenger2->Report(cout);
  std::string output3 = testing::internal::GetCapturedStdout();

  // passenger
  string expected_out_1 = "Name: Nobody";
  string expected_out_2 = "Name: Nobody";
  string expected_out_3 = "Name: Bob";

  EXPECT_EQ(output1.find(expected_out_1), 0);
  EXPECT_EQ(output2.find(expected_out_2), 0);
  EXPECT_EQ(output3.find(expected_out_3), 0);

  delete passenger1;
  delete passenger2;
  passenger1 = NULL;
  passenger2 = NULL;
}

