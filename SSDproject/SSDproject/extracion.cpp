/**
 * \file extraction.cpp
 *
 * \brief Functions for parameter value extraction.
 *
 * \details This file includes definitions of functions allowing for conversion of AIS message to binary format and extraction of values of parameters included inside.
 *
 * \author  Krystian Chorab
 * \date    08/05/2019
 */
#include "pch.h"
#include <string>
#include <map>
#include "extraction.hpp"

 /**
  *    \var      map<char,byte> ASCIItoBytes
  *    \brief    Container mapping ASCII chars to binary values
  */
map<char, byte> ASCIItoBytes;

/**
 *    \fn           void initASCIIToBytesMap()
 *    \brief        Assigns binary values to ASCII characters
 *    \note         Used for decoding AIS messages
 *    \warning      This function must be run before using ASCIItoBytes map
 */
void initASCIIToBytesMap()
{
	ASCIItoBytes['0'] = 0b000000;
	ASCIItoBytes['1'] = 0b000001;
	ASCIItoBytes['2'] = 0b000010;
	ASCIItoBytes['3'] = 0b000011;
	ASCIItoBytes['4'] = 0b000100;
	ASCIItoBytes['5'] = 0b000101;
	ASCIItoBytes['6'] = 0b000110;
	ASCIItoBytes['7'] = 0b000111;
	ASCIItoBytes['8'] = 0b001000;
	ASCIItoBytes['9'] = 0b001001;
	ASCIItoBytes[':'] = 0b001010;
	ASCIItoBytes[';'] = 0b001011;
	ASCIItoBytes['<'] = 0b001100;
	ASCIItoBytes['='] = 0b001101;
	ASCIItoBytes['>'] = 0b001110;
	ASCIItoBytes['?'] = 0b001111;
	ASCIItoBytes['@'] = 0b010000;
	ASCIItoBytes['A'] = 0b010001;
	ASCIItoBytes['B'] = 0b010010;
	ASCIItoBytes['C'] = 0b010011;
	ASCIItoBytes['D'] = 0b010100;
	ASCIItoBytes['E'] = 0b010101;
	ASCIItoBytes['F'] = 0b010110;
	ASCIItoBytes['G'] = 0b010111;
	ASCIItoBytes['H'] = 0b011000;
	ASCIItoBytes['I'] = 0b011001;
	ASCIItoBytes['J'] = 0b011010;
	ASCIItoBytes['K'] = 0b011011;
	ASCIItoBytes['L'] = 0b011100;
	ASCIItoBytes['M'] = 0b011101;
	ASCIItoBytes['N'] = 0b011110;
	ASCIItoBytes['O'] = 0b011111;
	ASCIItoBytes['P'] = 0b100000;
	ASCIItoBytes['Q'] = 0b100001;
	ASCIItoBytes['R'] = 0b100010;
	ASCIItoBytes['S'] = 0b100011;
	ASCIItoBytes['T'] = 0b100100;
	ASCIItoBytes['U'] = 0b100101;
	ASCIItoBytes['V'] = 0b100110;
	ASCIItoBytes['W'] = 0b100111;
	ASCIItoBytes['\''] = 0b101000;
	ASCIItoBytes['a'] = 0b101001;
	ASCIItoBytes['b'] = 0b101010;
	ASCIItoBytes['c'] = 0b101011;
	ASCIItoBytes['d'] = 0b101100;
	ASCIItoBytes['e'] = 0b101101;
	ASCIItoBytes['f'] = 0b101101;
	ASCIItoBytes['g'] = 0b101111;
	ASCIItoBytes['h'] = 0b110000;
	ASCIItoBytes['i'] = 0b110001;
	ASCIItoBytes['j'] = 0b110010;
	ASCIItoBytes['k'] = 0b110011;
	ASCIItoBytes['l'] = 0b110100;
	ASCIItoBytes['m'] = 0b110101;
	ASCIItoBytes['n'] = 0b110110;
	ASCIItoBytes['o'] = 0b110111;
	ASCIItoBytes['p'] = 0b111000;
	ASCIItoBytes['q'] = 0b111001;
	ASCIItoBytes['r'] = 0b111010;
	ASCIItoBytes['s'] = 0b111011;
	ASCIItoBytes['t'] = 0b111100;
	ASCIItoBytes['u'] = 0b111101;
	ASCIItoBytes['v'] = 0b111110;
	ASCIItoBytes['w'] = 0b111111;
}

/**
 *    \fn           void convertAISMsgStringToBinaryFormat(string& msgString, byte* msgBin)
 *    \brief        Converts AIS message string into byte array
 *    \param[in]    msgString
 *                    AIS message string
 *    \param[out]    msgBin
 *                    Pointer to byte array
 *    \warning      msgBin must point to already allocated memory
 */
void convertAISMsgStringToBinaryFormat(string& msgString, byte* msgBin)
{
	for (int i = 0; i < msgString.length(); i++) {
		msgBin[i] = ASCIItoBytes[msgString.at(i)];
	}
}

/**
 *    \fn           unsigned getFieldValue(byte* msg, byte idx, byte len)
 *    \brief        Extracts value from byte array given starting bit index and lenght of bit field
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \param[in]    idx
 *                    Index of the starting bit
 *    \param[in]    len
 *                    Length of bit fied
 *    \return       Value included in bit field
 */
unsigned getFieldValue(byte* msg, byte idx, byte len)
{
	unsigned value = 0x0000;

	for (int i = 0; i < len; i++) {

		byte byteIdx = (idx + i) / 6;
		byte byteMask = 0b00100000 >> ((idx + i) % 6);
		byte outputBitShift = len - i - 1;
		byte outputBitValue = (msg[byteIdx] & byteMask) ? 1 : 0;
		/*
		 cout << "ByteIdx: " <<(unsigned short)byteIdx << " ByteVal: " << bitset<8>(msg[byteIdx]) << " ByteMask: " << bitset<8>(byteMask) << " Extracted: " << bitset<8>(msg[byteIdx] & byteMask) << " BitValue: " << (unsigned short)outputBitValue << " BitShift: " << (unsigned short)outputBitShift << endl;
		 */
		value |= (outputBitValue << outputBitShift);
	}
	//cout << "Final output value: " << bitset<32>(value) << " = " << (unsigned)value << endl;

	return value;
}

/**
 *    \fn           unsigned extractMessageType(byte* msg)
 *    \brief        Extracts value of parameter 'Message Type' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Message Type'
 */
unsigned extractMessageType(byte* msg)
{
	return getFieldValue(msg, 0, 6);
}

/**
 *    \fn           unsigned extractRepeatIndicator(byte* msg)
 *    \brief        Extracts value of parameter 'Repeat Indicator' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Repeat Indicator'
 */
unsigned extractRepeatIndicator(byte* msg)
{
	return getFieldValue(msg, 6, 2);
}

/**
 *    \fn           unsigned extractMMSI(byte* msg)
 *    \brief        Extracts value of parameter 'MMSI' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'MMSI'
 */
unsigned extractMMSI(byte* msg)
{
	return getFieldValue(msg, 8, 30);
}

/**
 *    \fn           unsigned extractNavigationStatus(byte* msg)
 *    \brief        Extracts value of parameter 'Navigation Status' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Navigation Status'
 */
unsigned extractNavigationStatus(byte* msg)
{
	return getFieldValue(msg, 38, 4);
}

/**
 *    \fn           unsigned extractRateOfTurn(byte* msg)
 *    \brief        Extracts value of parameter 'Rate Of Turn' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Rate Of Turn'
 */
unsigned extractRateOfTurn(byte* msg)
{
	return getFieldValue(msg, 42, 8);
}

/**
 *    \fn           unsigned extractSpeedOverGround(byte* msg)
 *    \brief        Extracts value of parameter 'Speed Over Ground' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Speed Over Ground'
 */
unsigned extractSpeedOverGround(byte* msg)
{
	return getFieldValue(msg, 50, 10);
}

/**
 *    \fn           unsigned extractPositionAccuracy(byte* msg)
 *    \brief        Extracts value of parameter 'Position Accuracy' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Position Accuracy'
 */
unsigned extractPositionAccuracy(byte* msg)
{
	return getFieldValue(msg, 60, 1);
}

/**
 *    \fn           unsigned extractLongitude(byte* msg)
 *    \brief        Extracts value of parameter 'Longitude' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Longitude'
 */
unsigned extractLongitude(byte* msg)
{
	return getFieldValue(msg, 61, 28);
}

/**
 *    \fn           unsigned extractLatitude(byte* msg)
 *    \brief        Extracts value of parameter 'Latitude' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Latitude'
 */
unsigned extractLatitude(byte* msg)
{
	return getFieldValue(msg, 89, 27);
}

/**
 *    \fn           unsigned extractCourseOverGround(byte* msg)
 *    \brief        Extracts value of parameter 'Course Over Ground' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Course Over Ground'
 */
unsigned extractCourseOverGround(byte* msg)
{
	return getFieldValue(msg, 116, 12);
}

/**
 *    \fn           unsigned extractTrueHeading(byte* msg)
 *    \brief        Extracts value of parameter 'True Heading' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'True Heading'
 */
unsigned extractTrueHeading(byte* msg)
{
	return getFieldValue(msg, 128, 9);
}

/**
 *    \fn           unsigned extractTimeStamp(byte* msg)
 *    \brief        Extracts value of parameter 'Time Stamp' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Time Stamp'
 */
unsigned extractTimeStamp(byte* msg)
{
	return getFieldValue(msg, 137, 6);
}

/**
 *    \fn           unsigned extractManeuverIndicator(byte* msg)
 *    \brief        Extracts value of parameter 'Maneuver Indicator' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Maneuver Indicator'
 */
unsigned extractManeuverIndicator(byte* msg)
{
	return getFieldValue(msg, 143, 2);
}

/**
 *    \fn           unsigned extractRAIMFlag(byte* msg)
 *    \brief        Extracts value of parameter 'RAIM Flag' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'RAIM Flag'
 */
unsigned extractRAIMFlag(byte* msg)
{
	return getFieldValue(msg, 148, 1);
}

/**
 *    \fn           unsigned extractRadioStatus(byte* msg)
 *    \brief        Extracts value of parameter 'Radio Status' from AIS message in binary format
 *    \param[in]    msg
 *                    AIS message in binary format
 *    \return       Value of parameter 'Radio Status'
 */
unsigned extractRadioStatus(byte* msg)
{
	return getFieldValue(msg, 149, 19);
}
