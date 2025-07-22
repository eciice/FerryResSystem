//============================================================
//============================================================
/*
* Filename: vehicle.cpp
*
* Description: Header file of the Vehicle module of the Ferry
* Reservation System, being the only module able
* to modify the file i/o containing information
* about vehicles
* Is a data storage only module
* Should call the init() function before any
* operations
*
* Revision History:
* Rev. 1 - 25/07/20 Original by L. Xu
*/
//============================================================

#include "vehicle.hpp"
#include <fstream>
#include <stdexcept>
#include <cstring> 

static std::fstream vehicleFile;
static const std::string vehicleFileName = "vehicles.txt";

//============================================================
// Function open creates and opens the Vehicle file
// Throws an exception if the file cannot be opened
//------------------------------------------------------------
void open()
{
    // Try to open the vehicle file without overwriting the contents
    vehicleFile.open(vehicleFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
    if (!vehicleFile.is_open())
    {
        // Try to create a vehicle file if it does not exist
        vehicleFile.clear();
        vehicleFile.open(vehicleFileName, std::ios::out | std::ios::binary);
        
        if (!vehicleFile.is_open())
        {
            // Throw an exception if the file cannot be created
            throw std::runtime_error("Cannot create " + vehicleFileName + ".");
        }
        vehicleFile.close();

        // Try to now re-open the file for reading and writing
        vehicleFile.open(vehicleFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
        if (!vehicleFile.is_open())
        {
            // Throw an exception if the file cannot be opened
            throw std::runtime_error("Cannot open " + vehicleFileName + ".");
        } 
    }
}

// Function reset seeks to the beginning of the Vehicle file
// Throws an exception if the file is not open
//------------------------------------------------------------
void reset()
{
    if (!vehicleFile.is_open())
    {
        // Throw an exception if the file could not be opened
        throw std::runtime_error("File " + vehicleFileName + "is not open.");
    }
    vehicleFile.clear();
    vehicleFile.seekg(0, std::ios::beg); // Set get position to the start of the file
    vehicleFile.seekp(0, std::ios::beg); // Set put position to the start of the file
}

// Function getNextVehicle obtains a line from the Vehicle file
// Returns a boolean if retrieving all the data was successful
// Throws an exception if the read operation fails
//------------------------------------------------------------
bool getNextVehicle(Vehicle& v)
{
    if (!vehicleFile.is_open())
    {
        // Throw an exception if the file is not open
        throw std::runtime_error("File " + vehicleFileName + "is not open.");
    }

    // Read information of the next vehicle object in the file
    vehicleFile.read(reinterpret_cast<char *>(&v), sizeof(Vehicle));

    if (vehicleFile.eof())
    {
        // Return false if there is no more data to read
        return false;
    }

    if (!vehicleFile)
    {
        // Throw an exception if the file could not be read from
        throw std::runtime_error("Error reading from file " + vehicleFileName + ".");
    }

    return true;
}

// Function writeVehicle writes to the Vehicle file
// Throws an exception if the write operation fails
//------------------------------------------------------------
void writeVehicle(const Vehicle& v)
{
    if (!vehicleFile.is_open())
    {
        // Throw an exception if the file is not open
        throw std::runtime_error("File " + vehicleFileName + "is not open.");
    }

    // Write information of the vehicle object at the end 
    vehicleFile.clear();
    vehicleFile.seekp(0, std::ios::end); // Move to the end of the file
    vehicleFile.write(reinterpret_cast<const char *>(&v), sizeof(Vehicle));
    
    if (!vehicleFile)
    {
        // Throw an exception if the file could not be written to
        throw std::runtime_error("Error writing to file " + vehicleFileName + ".");
    }
}

// Function close closes the Vehicle file
//------------------------------------------------------------
void close()
{
    if (vehicleFile.is_open())
    {
        vehicleFile.close();
    }
    else
    {
        // Throw an exception if the file was already closed
        throw std::runtime_error("File " + vehicleFileName + "was already closed.");
    }
}