/**
 * @file file_writer.cc
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#include "src/file_writer.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
FileWriter::FileWriter() {
  // Open the output file stream
  bus_logfile.open("BusData.csv");
  pass_logfile.open("PassData.csv");
}

FileWriter::~FileWriter() {
  // Close the output file stream
  bus_logfile.close();
  pass_logfile.close();
}

void FileWriter::Write(std::string file_name,
  const std::vector<std::string>& data) {
  // log the data into different files depending on the given file name
  if (file_name == "BusData.csv") {
    for (int i = static_cast<int>(data.size()) - 1; i >= 0; i--) {
      bus_logfile << data[i];
    }
    bus_logfile << std::endl << std::flush;
  } else if (file_name == "PassData.csv") {
    for (int i = static_cast<int>(data.size()) - 1; i >= 0; i--) {
      pass_logfile << data[i];
    }
    pass_logfile << std::endl << std::flush;
  }
}
