//============================================================
//============================================================
/*
* Filename: vessel.cpp
*
* Description: Implementation file of the Vessel module of the Ferry
* Reservation System, being the only module able
* to modify the file i/o containing information
* about vessels
* Is a data storage only module
* Should call the init() function before any
* operations
*
* Revision History:
* Rev. 1 - 25/07/20 Original by L. Xu
*/
//============================================================

#include "vessel.hpp"
#include <fstream>
#include <stdexcept>
#include <cstring> 

static std::fstream vesselFile;
static const std::string vesselFileName = "vessels.txt";

//============================================================
// Function open creates and opens the Vessel file
// Throws an exception if the file cannot be opened
//------------------------------------------------------------
void open()
{
    // Try to open the vessel file without overwriting the contents
    vesselFile.open(vesselFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!vesselFile.is_open())
    {
        // Try to create a vessel file if it does not exist
        vesselFile.clear();
        vesselFile.open(vesselFileName, std::ios::out | std::ios::binary);
        
        if (!vesselFile.is_open())
        {
            // Throw an exception if the file cannot be created
            throw std::runtime_error("Cannot create " + vesselFileName + ".");
        }
        vesselFile.close();

        // Try to now re-open the file for reading and writing
        vesselFile.open(vesselFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
        if (!vesselFile.is_open())
        {
            // Throw an exception if the file cannot be opened
            throw std::runtime_error("Cannot open " + vesselFileName + ".");
        } 
    }
}

// Function reset seeks to the beginning of the Vessel file
// Throws an exception if the file is not open
//------------------------------------------------------------
void reset()
{
    if (!vesselFile.is_open())
    {
        // Throw an exception if the file could not be opened
        throw std::runtime_error("File " + vesselFileName + "is not open.");
    }
    vesselFile.clear();
    vesselFile.seekg(0, std::ios::beg); // Set get position to the start of the file
    vesselFile.seekp(0, std::ios::beg); // Set put position to the start of the file
}

// Function getNextVessel obtains a line from the Vessel file
// Returns a boolean if retrieving all the data was successful
// Throws an exception if the read operation fails
//------------------------------------------------------------
bool getNextVessel(Vessel& v)
{
    if (!vesselFile.is_open())
    {
        // Throw an exception if the file is not open
        throw std::runtime_error("File " + vesselFileName + "is not open.");
    }

    // Read information of the next vessel object in the file
    vesselFile.read(reinterpret_cast<char *>(&v), sizeof(Vessel));

    if (vesselFile.eof())
    {
        // Return false if there is no more data to read
        return false;
    }

    if (!vesselFile)
    {
        // Throw an exception if the file could not be read from
        throw std::runtime_error("Error reading from file " + vesselFileName + ".");
    }

    return true;
}

// Function writeVessel writes to the Vessel file
// Throws an exception if the write operation fails
//------------------------------------------------------------
void writeVessel(const Vessel& v)
{
    if (!vesselFile.is_open())
    {
        // Throw an exception if the file is not open
        throw std::runtime_error("File " + vesselFileName + "is not open.");
    }

    // Write information of the vessel object at the end 
    vesselFile.clear();
    vesselFile.seekp(0, std::ios::end); // Move to the end of the file
    vesselFile.write(reinterpret_cast<const char *>(&v), sizeof(Vessel));
    
    if (!vesselFile)
    {
        // Throw an exception if the file could not be written to
        throw std::runtime_error("Error writing to file " + vesselFileName + ".");
    }
}

// Function close closes the Vessel file
//------------------------------------------------------------
void close()
{
    if (vesselFile.is_open())
    {
        vesselFile.close();
    }
    else
    {
        // Throw an exception if the file was already closed
        throw std::runtime_error("File " + vesselFileName + "was already closed.");
    }
}