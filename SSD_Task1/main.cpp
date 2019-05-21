/**
 * \file main.cpp
 *
 * \brief Main program source file
 *
 * This file contains program code that reads raw AIS messages from file and writes
 * decoded messages of type 1 and 2 into files named after MMSI number of the sender.
 *
 * Created by Stefan Węgrzyn on 11/05/2019.
 *
 */

#include <iostream>
#include <fstream>

#include "main.hpp"
#include "read.hpp"
#include "extraction.hpp"
#include "decoding.hpp"
#include "write.hpp"

using namespace std;

/**
 *    \fn           string decodeAISMsg(byte* AISMsg)
 *    \brief        Creates output string that can be written to file
 *    \param[in]    AISMsg
 *                    Pointer to byte array containing AIS message in binary format
 *    \return       Output string
 */
string decodeAISMsg(byte* AISMsg)
{
    string line =
    "Message type: " + getMessageType(extractMessageType(AISMsg)) +
    "\n\tCount: " + getRepeatIndicator(extractRepeatIndicator(AISMsg)) +
    "\n\tMMSI: " + getMMSI(extractMMSI(AISMsg)) +
    "\n\tStatus: " + getNavigationStatus(extractNavigationStatus(AISMsg)) +
    "\n\tROT: " + getRateOfTurn(extractRateOfTurn(AISMsg)) +
    "\n\tSOG: " + getSpeedOverGround(extractSpeedOverGround(AISMsg)) +
    "\n\tAccuracy: " + getPositionAccuracy(extractPositionAccuracy(AISMsg)) +
    "\n\tLON: " + getLongitude(extractLongitude(AISMsg)) +
    "\n\tLAT: " + getLatitude(extractLatitude(AISMsg)) +
    "\n\tCOG: " + getCourseOverGround(extractCourseOverGround(AISMsg)) +
    "\n\tHDG: " + getTrueHeading(extractTrueHeading(AISMsg)) +
    "\n\tTimestamp: " + getTimeStamp(extractTimeStamp(AISMsg)) +
    "\n\tManeuver: " + getManeuverIndicator(extractManeuverIndicator(AISMsg)) +
    "\n";
    
    return line;
}

/**
 *    \fn           int main(int argc, const char * argv[])
 *    \brief        Main program performing AIS messages processing
 *    \param[in]    argc
 *                    Parameters count
 *    \param[in]    argv
 *                    Array of pointers to parameters passed to the program
 *    \return       Return value of the program
 */
int main(int argc, const char * argv[])
{
    // Display user guide on request
    string parameter;
    if (argc == 1 || (parameter.assign(argv[1]) == "--help" && argc == 2)) {
        cout << "----------------------------------------------------------" << endl;
        cout << "USER GUIDE:" << endl;
        cout << "\t[1st parmeter]: relative input file path" << endl;
        cout << "\t[2nd parameter]: relative output folder file path" << endl;
        cout << "EXAMPLE:" << endl;
        cout << "\t'./SSD_Task1 ./AIS_messages.txt ./'" << endl;
        cout << "----------------------------------------------------------" << endl;
        cin.get();
        return 0;
    }
    
    // Detect wrong number of arguments
    if (argc != 3) {
        cout << "(ERROR) Wrong number of arguments" << endl;
        cin.get();
        return -1;
    }
    
    // Initialize STL maps
    initASCIIToBytesMap();
    initMessageTypesMap();
    initNavigationStatusMap();
    
    // Prepare file reader and writer
    string readFilePath(argv[1]);
    ifstream file_reader(readFilePath);
    if ( !file_reader.is_open() ) {
        cout << "(ERROR) Could not open input file: " << readFilePath << endl;
        cin.get();
        return -1;
    }
    string outputDirPath(argv[2]);
    ofstream file_writer;
    
    // Read input file line by line
    cout << "Processing data" << endl;
    lineContent line;
    unsigned lineCnt = 0;
    while (readLineFromFile(line,file_reader)) {
        
        // Convert message to binary format
        byte* msgBin = new byte[line.AISMsg.payload.length()];
        convertAISMsgStringToBinaryFormat(line.AISMsg.payload,msgBin);
        
        // Extract  messages of type 1 and 3
        if (extractMessageType(msgBin) == 1 || extractMessageType(msgBin) == 3) {
            
            // Define output content
            string content = line.date + " " + line.time + "\n" + decodeAISMsg(msgBin) + "\n";
            string MMSI = getMMSI(extractMMSI(msgBin));
            
            // Put message info in proper file
            putMessageInFile(MMSI, content, file_writer, outputDirPath);
            
            // Print out content of each write
            //cout << content;
        }
        
        // Free the dynamically allocated memory
        delete[] msgBin;
        
        // Inform user about the progress
        if(lineCnt%1000 == 0) cout << ".";
        lineCnt++;
    }
    
    cout << endl << "Processing finished successfully" << endl;
    cin.get();

    return 0;
}
