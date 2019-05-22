/**
 * \file decoding.cpp
 *
 * \brief Functions for information decoding.
 *
 * \details This file includes definitions of functions allowing for decoding of parameter's values according to AIVDM protocol.
 *
 * \author  Stefan Węgrzyn
 * \date    04/05/2019
 */
 /*
  * AIVDM protocol decoding: <a href="http://catb.org/gpsd/AIVDM.html#_type_12_addressed_safety_related_message">More info</a>
  */
#include "pch.h"
#include <string>
#include <map>
#include <math.h>
#include "decoding.hpp"

using namespace std;

/**
 *    \var      map<byte,string> MessageTypes
 *    \brief    Container mapping values of 'Message Type' parameter to proper names
 */
map<byte, string> MessageTypes;
/**
 *    \var      map<byte,string> NavigationStatus
 *    \brief    Container mapping values of 'Navigation Status' parameter to proper names
 */
map<byte, string> NavigationStatus;


/**
 *    \fn           void initMessageTypesMap()
 *    \brief        Assigns names to values of 'Message Type' parameter
 *    \note         Used for interpreting parameter values of AIS messages
 *    \warning      This function must be run before using MessageTypes map
 */
void initMessageTypesMap()
{
	MessageTypes[1] = "Position Report Class A";
	MessageTypes[2] = "Position Report Class A (Assigned schedule)";
	MessageTypes[3] = "Position Report Class A (Response to interrogation)";
	MessageTypes[4] = "Base Station Report";
	MessageTypes[5] = "Static and Voyage Related Data";
	MessageTypes[6] = "Binary Addressed Message";
	MessageTypes[7] = "Binary Acknowledge";
	MessageTypes[8] = "Binary Broadcast Message";
	MessageTypes[9] = "Standard SAR Aircraft Position Report";
	MessageTypes[10] = "UTC and Date Inquiry";
	MessageTypes[11] = "UTC and Date Response";
	MessageTypes[12] = "Addressed Safety Related Message";
	MessageTypes[13] = "Safety Related Acknowledgement";
	MessageTypes[14] = "Safety Related Broadcast Message";
	MessageTypes[15] = "Interrogation";
	MessageTypes[16] = "Assignment Mode Command";
	MessageTypes[17] = "DGNSS Binary Broadcast Message";
	MessageTypes[18] = "Standard Class B CS Position Report";
	MessageTypes[19] = "Extended Class B Equipment Position Report";
	MessageTypes[20] = "Data Link Management";
	MessageTypes[21] = "Aid-to-Navigation Report";
	MessageTypes[22] = "Channel Management";
	MessageTypes[23] = "Group Assignment Command";
	MessageTypes[24] = "Static Data Report";
	MessageTypes[25] = "Single Slot Binary Message";
	MessageTypes[26] = "Multiple Slot Binary Message With Communications State";
	MessageTypes[27] = "Position Report For Long-Range Applications";
}

/**
 *    \fn           void initNavigationStatusMap()
 *    \brief        Assigns names to values of 'Navigation Status' parameter
 *    \note         Used for interpreting parameter values of AIS messages
 *    \warning      This function must be run before using NavigationStatus map
 */
void initNavigationStatusMap()
{
	NavigationStatus[0] = "Under way using engine";
	NavigationStatus[1] = "At anchor";
	NavigationStatus[2] = "Not under command";
	NavigationStatus[3] = "Restricted manoeuverability";
	NavigationStatus[4] = "Constrained by her draught";
	NavigationStatus[5] = "Moored";
	NavigationStatus[6] = "Aground";
	NavigationStatus[7] = "Engaged in Fishing";
	NavigationStatus[8] = "Under way sailing";
	NavigationStatus[9] = "Reserved";
	NavigationStatus[10] = "Reserved";
	NavigationStatus[11] = "Reserverd";
	NavigationStatus[12] = "Reserved";
	NavigationStatus[13] = "Reserved";
	NavigationStatus[14] = "AIS-SART is active";
	NavigationStatus[15] = "Not defined";
}

/**
 *    \fn           string getMessageType(unsigned MsgType)
 *    \brief        Interprets value of the parameter 'Message Type' and returns textual description
 *    \param[in]    MsgType
 *                    Value of the parameter 'Message Type'
 *    \return       Textual description of the parameter value
 *    \warning      Requires presence of externally defined MessageTypes map container
 */
string getMessageType(unsigned MsgType)
{
	if (MsgType == 0 || MsgType > 27) return "error";
	return MessageTypes.at(MsgType);
}

/**
 *    \fn           string getRepeatIndicator(unsigned RepeatInd)
 *    \brief        Interprets value of the parameter 'Repeat Indicator' and returns textual description
 *    \param[in]    RepeatInd
 *                    Value of the parameter 'Repeat Indicator'
 *    \return       Textual description of the parameter value
 */
string getRepeatIndicator(unsigned RepeatInd)
{
	return to_string(RepeatInd);
}

/**
 *    \fn           string getMMSI(unsigned MMSI)
 *    \brief        Interprets value of the parameter 'MMSI' and returns textual description
 *    \param[in]    MMSI
 *                    Value of the parameter 'MMSI'
 *    \return       Textual description of the parameter value
 */
string getMMSI(unsigned MMSI)
{
	return to_string(MMSI);
}

/**
 *    \fn           string getNavigationStatus(unsigned NavStatus)
 *    \brief        Interprets value of the parameter 'Navigation Status' and returns textual description
 *    \param[in]    NavStatus
 *                    Value of the parameter 'Navigation Status'
 *    \return       Textual description of the parameter value
 *    \warning      Requires presence of externally defined NavigationStatus map container
 */
string getNavigationStatus(unsigned NavStatus)
{
	if (NavStatus > 15) return "error";
	return NavigationStatus.at(NavStatus);
}

/**
 *    \fn           string getRateOfTurn(unsigned RateOfTurn)
 *    \brief        Interprets value of the parameter 'Rate Of Turn' and returns textual description
 *    \param[in]    RateOfTurn
 *                    Value of the parameter 'Rate Of Turn'
 *    \return       Textual description of the parameter value
 */
string getRateOfTurn(unsigned RateOfTurn)
{
	// Convert to signed byte variable
	signed char ROT_AIS = (signed char)RateOfTurn;

	// Handle special case
	if (ROT_AIS == -128) return "not available";

	// Convert AIS bit value to value expressed in [deg/min]
	bool sign = (ROT_AIS >= 0) ? true : false;      // remember the sign
	double ROT_sensor = (static_cast<double>(ROT_AIS) / 4.773);
	ROT_sensor *= ROT_sensor;
	ROT_sensor = round(ROT_sensor);
	if (!sign) ROT_sensor = -ROT_sensor;             // recover the sign

	// Return value
	return to_string(static_cast<int>(ROT_sensor)) + " [deg/min]";
}

/**
 *    \fn           string getSpeedOverGround(unsigned SpeedOverGround)
 *    \brief        Interprets value of the parameter 'Speed Over Ground' and returns textual description
 *    \param[in]    SpeedOverGround
 *                    Value of the parameter 'Speed Over Ground'
 *    \return       Textual description of the parameter value
 */
string getSpeedOverGround(unsigned SpeedOverGround)
{
	// Handle special case
	if (SpeedOverGround == 1023) return "not available";

	// Convert AIS bit value to value expressed in [knots]
	double SOG = static_cast<double>(SpeedOverGround)*0.1;

	// Return value
	return to_string(SOG) + " [knots]";
}

/**
 *    \fn           string getPositionAccuracy(unsigned PositionAccuracy)
 *    \brief        Interprets value of the parameter 'Position Accuracy' and returns textual description
 *    \param[in]    PositionAccuracy
 *                    Value of the parameter 'Position Accuracy'
 *    \return       Textual description of the parameter value
 */
string getPositionAccuracy(unsigned PositionAccuracy)
{
	if (PositionAccuracy == 1) return "<10m";
	else if (PositionAccuracy == 0) return ">10m";
	else return "error";
}

/**
 *    \fn           string getLongitude(unsigned Longitude)
 *    \brief        Interprets value of the parameter 'Longitude' and returns textual description
 *    \param[in]    Longitude
 *                    Value of the parameter 'Longitude'
 *    \return       Textual description of the parameter value
 */
string getLongitude(unsigned Longitude)
{
	// Handle special case
	if (Longitude == 0x6791AC0) return "not available"; // value of 181 degrees

	// Convert AIS bit value to value expressed in [deg]
	int signedLongitude = 0;
	double LON = 0;

	if (Longitude & 0x08000000) {   // negative value
		signedLongitude = (Longitude & 0x07FFFFFF) - 0x08000000;
		LON = static_cast<double>(signedLongitude);
		LON /= 600000.0;
		if (LON < -180.0) return "error";
	}
	else {                          // positive value
		signedLongitude = Longitude & 0x07FFFFFF;
		LON = static_cast<double>(signedLongitude);
		LON /= 600000.0;
		if (LON > 180.0) return "error";
	}

	// Return value
	return to_string(LON) + " [deg]";
}

/**
 *    \fn           string getLatitude(unsigned Latitude)
 *    \brief        Interprets value of the parameter 'Latitude' and returns textual description
 *    \param[in]    Latitude
 *                    Value of the parameter 'Latitude'
 *    \return       Textual description of the parameter value
 */
string getLatitude(unsigned Latitude)
{
	// Handle special case
	if (Latitude == 0x3412140) return "not available"; // value of 91 degrees

	// Convert AIS bit value to value expressed in [deg]
	int signedLatitude = 0;
	double LAT = 0;

	if (Latitude & 0x04000000) {   // negative value
		signedLatitude = (Latitude & 0x03FFFFFF) - 0x04000000;
		LAT = static_cast<double>(signedLatitude);
		LAT /= 600000.0;
		if (LAT < -90.0) return "error";
	}
	else {                          // positive value
		signedLatitude = Latitude & 0x03FFFFFF;
		LAT = static_cast<double>(signedLatitude);
		LAT /= 600000.0;
		if (LAT > 90.0) return "error";
	}

	// Return value
	return to_string(LAT) + " [deg]";
}

/**
 *    \fn           string getCourseOverGround(unsigned CourseOverGround)
 *    \brief        Interprets value of the parameter 'Course Over Ground' and returns textual description
 *    \param[in]    CourseOverGround
 *                    Value of the parameter 'Course Over Ground'
 *    \return       Textual description of the parameter value
 */
string getCourseOverGround(unsigned CourseOverGround)
{
	// Handle special case
	if (CourseOverGround == 3600) return "not available";

	// Convert AIS bit value to value expressed in [deg]
	double COG = static_cast<double>(CourseOverGround)*0.1;
	if (COG > 360.0) return "error";

	// Return value
	return to_string(COG) + " [deg]";
}

/**
 *    \fn           string getTrueHeading(unsigned TrueHeading)
 *    \brief        Interprets value of the parameter 'True Heading' and returns textual description
 *    \param[in]    TrueHeading
 *                    Value of the parameter 'True Heading'
 *    \return       Textual description of the parameter value
 */
string getTrueHeading(unsigned TrueHeading)
{
	// Handle special case
	if (TrueHeading == 511) return "not available";

	// Convert AIS bit value to value expressed in [deg]
	unsigned short HDG = TrueHeading;
	if (HDG > 359) return "error";

	// Return value
	return to_string(HDG) + " [deg]";
}

/**
 *    \fn           string getTimeStamp(unsigned TimeStamp)
 *    \brief        Interprets value of the parameter 'Time Stamp' and returns textual description
 *    \param[in]    TimeStamp
 *                    Value of the parameter 'Time Stamp'
 *    \return       Textual description of the parameter value
 */
string getTimeStamp(unsigned TimeStamp)
{
	// Handle special cases
	if (TimeStamp == 60) return "not available";
	else if (TimeStamp == 61) return "system in manual input mode";
	else if (TimeStamp == 62) return "system in estimated mode";
	else if (TimeStamp == 63) return "system inoperative";

	// Return value
	return to_string(TimeStamp) + " [s]";
}

/**
 *    \fn           string getManeuverIndicator(unsigned ManeuverIndicator)
 *    \brief        Interprets value of the parameter 'Maneuver Indicator' and returns textual description
 *    \param[in]    ManeuverIndicator
 *                    Value of the parameter 'Maneuver Indicator'
 *    \return       Textual description of the parameter value
 */
string getManeuverIndicator(unsigned ManeuverIndicator)
{
	switch (ManeuverIndicator) {
	case 0:
		return "not available";
	case 1:
		return "no special maneuver";
	case 2:
		return "special maneuver";
	default:
		return "error";
	}
}

/**
 *    \fn           string getRAIMFlag(unsigned RAIMFlag)
 *    \brief        Interprets value of the parameter 'RAIM Flag' and returns textual description
 *    \param[in]    RAIMFlag
 *                    Value of the parameter 'RAIM Flag'
 *    \return       Textual description of the parameter value
 */
string getRAIMFlag(unsigned RAIMFlag)
{
	if (RAIMFlag == 1) return "in use";
	else if (RAIMFlag == 0) return "not in use";
	else return "error";
}
