/**
 * \file read.cpp
 *
 * \brief Functions for file reading.
 *
 * \details This file includes definitions of functions allowing for reading subsequent lines from text file and preparing data to further processing.
 *
 * \author  Paweł Świąder
 * \date    07/05/2019
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "read.hpp"

/**
 *    \fn           void splitElementsOfAISMessage(string& AISString, AISMessage& AISMsg)
 *    \brief        Splits comma separated elements of AIS message
 *    \param[in]    AISString
 *                    AIS message string
 *    \param[out]    AISMsg
 *                    Structure for storing extracted substrings
 */
void splitElementsOfAISMessage(string& AISString, AISMessage& AISMsg)
{    
    // Split comma separated elements of AIS message
    stringstream ss(AISString);
    vector<string> AISMsgElements(AIS_MSG_ELEMENTS_NUM);
    int k = 0;
    while (getline(ss, AISMsgElements.at(k), ',')) {
        if(++k == AIS_MSG_ELEMENTS_NUM) break;
    }
    AISMsg.format = AISMsgElements.at(0);
    AISMsg.msgCnt = AISMsgElements.at(1);
    AISMsg.msgNum = AISMsgElements.at(2);
    AISMsg.seqID = AISMsgElements.at(3);
    AISMsg.channel = AISMsgElements.at(4);
    AISMsg.payload = AISMsgElements.at(5);
    AISMsg.size = AISMsgElements.at(6);
}

/**
 *    \fn           bool readLineFromFile(lineContent& line, ifstream& file_reader)
 *    \brief        Main program performing AIS messages processing
 *    \param[out]    line
 *                    Structure for storing line components
 *    \param[in]    file_reader
 *                    Reader used for file reading
 *    \return       Boolean value determining if reading was successful
 *    \note         Return value can be used to detect EOF
 *    \warning      Reader must be initialized before being passed to the function
 */
bool readLineFromFile(lineContent& line, ifstream& file_reader)
{
    string AISString = "";
    
    // Reading from file
    if (!(file_reader >> line.date)) return false; // on file end
    file_reader >> line.time;
    file_reader >> AISString;
    
    splitElementsOfAISMessage(AISString, line.AISMsg);
    
    return true;
}
