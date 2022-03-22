/**
 * @file util.h
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for parsing the output to csv format.
 *
 * Calls to \ref ProcessOutput function to parse the output to csv format.
 */
class Util {
 public:  // public reporter
 /**
  * @brief Parse the output to csv format.
  * 
  * This function will be used for logging in Singleton Pattern.
  *
  * @param[in] ss ostringstream to be parsed
  * @return vector string to store the parsed output
  */
  static std::vector<std::string> ProcessOutput(const std::ostringstream &ss);
};

#endif  // SRC_UTIL_H_
