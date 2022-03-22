/**
 * @file util.cc
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#include "src/util.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::vector<std::string> Util::ProcessOutput(const std::ostringstream &ss) {
  std::vector<std::string> csv_vec;
  std::string s = ss.str();
  s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());  // delete all tabs
  s.erase(std::remove(s.begin(), s.end(), ':'), s.end());  // delete all ':'s
  std::replace(s.begin(), s.end(), ' ', ',');  // replace all ' ' to ','
  std::replace(s.begin(), s.end(), '\n', ',');  // replace all newlines to ','
  csv_vec.push_back(s);

  return csv_vec;
}
