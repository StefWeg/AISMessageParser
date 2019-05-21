/**
 * \file write.cpp
 *
 * \brief Functions for writing to files.
 *
 * This file includes definitions of functions allowing for writing
 * output content to files named after MMSI numbers of senders.
 *
 * Created by Adam Penczek on 10/05/2019.
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "write.hpp"

using namespace std;

/**
 *    \var      vector<string> writeFiles
 *    \brief    Container storing names of files that program writes to
 */
vector<string> writeFiles;

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
void writeToFile(string& content, ofstream& file_writer, ios_base::openmode mode, string outputFilePath)
{
    file_writer.open(outputFilePath, mode);
    if (file_writer.is_open()) {
        file_writer << content;
        file_writer.close();
    } else {
        cout << "(WARNING) Could not open file: " << outputFilePath << endl;
    }
}

/**
 *    \fn           void putMessageInFile(string& MMSI, string& content, ofstream& file_writer, string outputDirPath)
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
void putMessageInFile(string& MMSI, string& content, ofstream& file_writer, string outputDirPath)
{
    bool MMSImatch = false;
    
    // Search for matching MMSI among writeFiles to append new message
    for(int j = 0; j < writeFiles.size(); j++) {
        if(writeFiles.at(j) == MMSI) {
            writeToFile(content, file_writer, ios::app, outputDirPath + MMSI + ".txt");
            MMSImatch = true;
            break;
        }
    }
    
    // If matching MMSI was not found add new file to writeFiles and write first message to it
    if(!MMSImatch) {
        writeToFile(content, file_writer, ios::trunc, outputDirPath + MMSI + ".txt");
        writeFiles.push_back(MMSI);
    }
}
