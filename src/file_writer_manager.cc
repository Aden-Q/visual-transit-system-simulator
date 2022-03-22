/**
 * @file file_writer_manager.cc
 *
 * @copyright Zecheng Qian. All rights reserved.
 */
#include "src/file_writer_manager.h"
#include "src/file_writer.h"

/*******************************************************************************
 * Static Variable Initialization
 ******************************************************************************/
// Initialize pointer to zero so that it can be initialized
// in first call to getInstance
FileWriter * FileWriterManager::file_writer = 0;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
FileWriter * FileWriterManager::GetInstance() {
  if (!file_writer) {
    file_writer = new FileWriter();
  }

  return file_writer;
}
