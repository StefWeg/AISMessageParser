/**
 * \file write.hpp
 *
 * \brief Header file of 'write.cpp'
 *
 * \details This file includes declarations of functions allowing for writing output content to files named after MMSI numbers of senders.
 *
 * \author  Adam Penczek
 * \date    10/05/2019
 */

#ifndef write_hpp
#define write_hpp

#include <fstream>

using namespace std;

/**
 *    \fn           void writeToFile(string& content, ofstream& file_writer, ios_base::openmode mode, string outputFilePath)
 *    \brief        Writes content to file
 *    \param[in]    content
 *                    String containing data to be written to file
 *    \param[in]    file_writer
 *                    Writer used for writing content to files
 *    \param[in]    mode
 *                    Mode determining operations performed on the file
 *    \param[in]    outputFilePath
 *                    Path of the output file
 */
void writeToFile(string& content, ofstream& file_writer, ios_base::openmode mode, string outputFilePath);

/**
 *    \fn           putMessageInFile(string& MMSI, string& content, ofstream& file_writer, string outputDirPath)
 *    \brief        Writes content to the file named with given MMSI number
 *    \param[in]    MMSI
 *                    MMSI number of sender (name of the file to be written to)
 *    \param[in]    content
 *                    String containing data to be written to file
 *    \param[in]    file_writer
 *                    Writer used for writing content to files
 *    \param[in]    outputDirPath
 *                    Path of the output directory
 *    \note         If program hasn't written to the file named after given MMSI number before
 *                  than new file is created and content is written to it. Otherwise, the content
 *                  is appended to the existing file crated earlier.
 *    \warning      Function uses global variable 'writeFiles'
 */
void putMessageInFile(string& MMSI, string& content, ofstream& file_writer, string outputDirPath);

#endif /* write_hpp */
