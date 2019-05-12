/**
 * \file extraction.hpp
 *
 * \brief Header file of 'extraction.cpp'.
 *
 * This file includes declarations of functions allowing for conversion of AIS message
 * to binary format and extraction of values of parameters included inside.
 *
 * Created by Krystian Chorab on 08/05/2019.
 *
 */

#ifndef extraction_hpp
#define extraction_hpp

#include <string>
#include <map>
#include "main.hpp"

using namespace std;

/**
 *    \fn           initASCIIToBytesMap
 *    \brief        Assigns binary values to ASCII characters
 *    \note         Used for decoding AIS messages
 *    \warning      This function must be run before using ASCIItoBytes map
 */
void initASCIIToBytesMap();

/**
 *    \fn           convertAISMsgStringToBinaryFormat
 *    \brief        Converts AIS message string into byte array
 *    \param[in]    msgString
 *                    AIS message string
 *    \param[out]    msgBin
 *                    Pointer to byte array
 *    \warning      msgBin must point to already allocated memory
 */
void convertAISMsgStringToBinaryFormat(string& msgString, byte* msgBin);

/**
 *    \fn           getFieldValue
 *    \brief        Extracts value from byte array given starting bit index and lenght of bit field
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \param[in]    idx
 *                    Index of the starting bit
 *    \param[in]    len
 *                    Length of bit fied
 *    \return       Value included in bit field
 */
unsigned getFieldValue(byte* msg, byte idx, byte len);

/**
 *    \fn           extractMessageType
 *    \brief        Extracts value of parameter 'Message Type' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Message Type'
 */
unsigned extractMessageType(byte* msg);
/**
 *    \fn           extractRepeatIndicator
 *    \brief        Extracts value of parameter 'Repeat Indicator' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Repeat Indicator'
 */
unsigned extractRepeatIndicator(byte* msg);
/**
 *    \fn           extractMMSI
 *    \brief        Extracts value of parameter 'MMSI' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'MMSI'
 */
unsigned extractMMSI(byte* msg);
/**
 *    \fn           extractNavigationStatus
 *    \brief        Extracts value of parameter 'Navigation Status' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Navigation Status'
 */
unsigned extractNavigationStatus(byte* msg);
/**
 *    \fn           extractRateOfTurn
 *    \brief        Extracts value of parameter 'Rate Of Turn' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Rate Of Turn'
 */
unsigned extractRateOfTurn(byte* msg);
/**
 *    \fn           extractSpeedOverGround
 *    \brief        Extracts value of parameter 'Speed Over Ground' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Speed Over Ground'
 */
unsigned extractSpeedOverGround(byte* msg);
/**
 *    \fn           extractPositionAccuracy
 *    \brief        Extracts value of parameter 'Position Accuracy' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Position Accuracy'
 */
unsigned extractPositionAccuracy(byte* msg);
/**
 *    \fn           extractLongitude
 *    \brief        Extracts value of parameter 'Longitude' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Longitude'
 */
unsigned extractLongitude(byte* msg);
/**
 *    \fn           extractLatitude
 *    \brief        Extracts value of parameter 'Latitude' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Latitude'
 */
unsigned extractLatitude(byte* msg);
/**
 *    \fn           extractCourseOverGround
 *    \brief        Extracts value of parameter 'Course Over Ground' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Course Over Ground'
 */
unsigned extractCourseOverGround(byte* msg);
/**
 *    \fn           extractTrueHeading
 *    \brief        Extracts value of parameter 'True Heading' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'True Heading'
 */
unsigned extractTrueHeading(byte* msg);
/**
 *    \fn           extractTimeStamp
 *    \brief        Extracts value of parameter 'Time Stamp' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Time Stamp'
 */
unsigned extractTimeStamp(byte* msg);
/**
 *    \fn           extractManeuverIndicator
 *    \brief        Extracts value of parameter 'Maneuver Indicator' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Maneuver Indicator'
 */
unsigned extractManeuverIndicator(byte* msg);
/**
 *    \fn           extractRAIMFlag
 *    \brief        Extracts value of parameter 'RAIM Flag' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'RAIM Flag'
 */
unsigned extractRAIMFlag(byte* msg);
/**
 *    \fn           extractRadioStatus
 *    \brief        Extracts value of parameter 'Radio Status' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Radio Status'
 */
unsigned extractRadioStatus(byte* msg);


#endif /* extraction_hpp */
