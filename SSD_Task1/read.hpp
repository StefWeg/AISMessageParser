/**
 * \file read.hpp
 *
 * \brief Header file of 'read.cpp'.
 *
 * \details This file includes definitions of structures and declarations of functions used for reading data from text file.
 *
 * \author  Paweł Świąder
 * \date    07/05/2019
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
    string format;  /*!< Contains format information */
    string msgCnt;  /*!< Contains message counter */
    string msgNum;  /*!< Contains message number */
    string seqID;   /*!< Contains sequence ID */
    string channel; /*!< Contains channel number */
    string payload; /*!< Contains message payload */
    string size;    /*!< Contains size information */
};

/**
 *    \struct       lineContent
 *    \brief        Structure for storing components of text line read from file
 */
struct lineContent {
    string date;        /*!< Contains date information */
    string time;        /*!< Contains time information */
    AISMessage AISMsg;  /*!< Contains AIS message structure */
};

/**
 *    \fn           void splitElementsOfAISMessage(string& AISString, AISMessage& AISMsg)
 *    \brief        Splits comma separated elements of AIS message
 *    \param[in]    AISString
 *                    AIS message string
 *    \param[out]    AISMsg
 *                    Structure for storing extracted substrings
 */
void splitElementsOfAISMessage(string& AISString, AISMessage& AISMsg);

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
bool readLineFromFile(lineContent& line, ifstream& file_reader);

#endif /* read_hpp */
