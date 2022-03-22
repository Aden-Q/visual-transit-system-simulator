/**
 * @file file_writer_manager.h
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#ifndef SRC_FILE_WRITER_MANAGER_H_
#define SRC_FILE_WRITER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/file_writer.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Singleton Pattern for instantiation control
 *
 * Calls to \ref GetInstance function to instantiate an object for logging.
 */
class FileWriterManager {
 public:  // public reporter
  FileWriterManager() {}
 /**
  * @brief Instantiate an object for logging.
  * 
  * This function will be used for logging in Singleton Pattern.
  *
  * @return FileWriter An object for writing purpose.
  */
  static FileWriter * GetInstance();

 private:  // private reporter
  static FileWriter * file_writer;
};

#endif  // SRC_FILE_WRITER_MANAGER_H_
