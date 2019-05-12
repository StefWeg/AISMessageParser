/**
 * \file read.hpp
 *
 * \brief Header file of 'read.cpp'.
 *
 * This file includes definitions of structures and declarations of functions used for reading data from text file.
 *
 * Created by Paweł Świąder on 07/05/2019.
 *
 */

#ifndef read_hpp
#define read_hpp

#include <string>
#include <fstream>

using namespace std;

//! Number of elements in AISMessage structure
#define AIS_MSG_ELEMENTS_NUM 7

/**
 *    \struct       AISMessage
 *    \brief        Structure for storing AIS message components
 */
struct AISMessage {
    string format;
    string msgCnt;
    string msgNum;
    string seqID;
    string channel;
    string payload;
    string size;
};

/**
 *    \struct       lineContent
 *    \brief        Structure for storing components of text line read from file
 */
struct lineContent {
    string date;
    string time;
    AISMessage AISMsg;
};

/**
 *    \fn           splitElementsOfAISMessage
 *    \brief        Splits comma separated elements of AIS message
 *    \param[in]    AISString
 *                    AIS message string
 *    \param[out]    AISMsg
 *                    Structure for storing extracted substrings
 */
void splitElementsOfAISMessage(string& AISString, AISMessage& AISMsg);

/**
 *    \fn           readLineFromFile
 *    \brief        Main program performing AIS messages processing
 *    \param[out]    line
 *                    Structure for storing line components
 *    \param[in]    file_reader
 *                    Reader used for file reading
 *    \return       Boolean value determining if reading was successful
 *    \note         Return value can be used to detect EOF
 *    \warning      Reader must be initialized before being passed to the function
 */
bool readLineFromFile(lineContent& line, ifstream& file_reader);

#endif /* read_hpp */
