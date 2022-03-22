/**
 * @file file_writer.h
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#ifndef SRC_FILE_WRITER_H_
#define SRC_FILE_WRITER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for writing the output to a file in Singleton Pattern
 *
 * Calls to \ref Write function to write the output to files in csv format.
 */
class FileWriter {
 public:  // public reporter
  FileWriter();
  ~FileWriter();
 /**
  * @brief Write the output to files in csv format.
  * 
  * This function will be used for logging in Singleton Pattern.
  *
  * @param[in] name Output file name
  * @param[in] data Data to be written
  */
  void Write(std::string file_name, const std::vector<std::string>& data);

 private:  // private reporter
  // Stringstream for logging purpose
  std::ofstream bus_logfile;
  std::ofstream pass_logfile;
};

#endif  // SRC_FILE_WRITER_H_
