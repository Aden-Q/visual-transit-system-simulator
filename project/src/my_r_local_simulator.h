/**
 * @file my_r_local_simulator.h
 *
 * @copyright 2020 Zecheng Qian, All rights reserved.
 */
#ifndef SRC_MY_R_LOCAL_SIMULATOR_H_
#define SRC_MY_R_LOCAL_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "src/simulator.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The simulator Class for regression test.
 *
 * Calls to \ref Start to set up the regression test.
 * Calls to \ref Update to execute the regression test.
 */
class MyrLocalSimulator : public Simulator {
 public:
 /**
  * @brief Start the regression test.
  *
  * @return boolean indicator for success or failure.
  */
  bool Start() override;
 /**
  * @brief Execute the regression test.
  *
  * @return boolean indicator for success or failure.
  */
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_MY_R_LOCAL_SIMULATOR_H_
