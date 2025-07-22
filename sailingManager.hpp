//================================================================
//================================================================

/*
 * Filename: sailingManager.hpp
 * 
 * Description: Sailing manager module of the Ferry Reservation System,
 *              manages all functions and commands relating to sailings. 
 * 
 */

//================================================================

#pragma once
#include <iostream>
#include <string>
using std::endl; 
using std::cout;
using std::string;

//================================================================

// Function getVessel displays all available vessels for sailings
// and prompts the user to select a vessel
// Returns a string containing the user selected vessel's name
// Throws an exception if no vessels exist
//----------------------------------------------------------------
std::string getVessel(); 

// Function getVesselLength
// Returns the total lane length of the specified vessel (irrespective of high/low) 
// as an int value
// Throws an exception if vessel does not exist
//----------------------------------------------------------------
int getVesselLength(std::string vesselName); 

// Function checkSailingExists checks if a sailing with the provided 
// sailing ID exists.
// Returns 1 if sailing exists, otherwise throw exception
//----------------------------------------------------------------
int checkSailingExists(std::string sailingID); 

// Function accessSailingManagerUpdate accesses the Reservation Manager module
// to view the total number reservations on
// a sailing
//----------------------------------------------------------------
void accessReservationManager(std::string sailingID); 

// Function createSailing creates a sailing on a vessel
// Throws an exception if a vessel with the corresponding name already exists
//----------------------------------------------------------------
void createSailing(std::string vesselName); 

// Function updateSailing updates the total space available on a sailing
// vehicleLen is the length of the vehicle being added/removed, measured in meters
// Throws an exception if space on sailing cannot be added to/subtracted from,
// in the case that the sailing is full or empty respectively
//----------------------------------------------------------------
void updateSailing(std::string sailingID, int vehicleLen); 

// Function checkInReservation calculates and prompts user to collect the appropriate
// fare from the customer, then calls the appropriate functions in the 
// ReservationManager module to register the reservation as checked in
// Throw an exception if vehicleLicence is invalid
//----------------------------------------------------------------
void checkInReservation(std::string sailingID, std::string vehicleLicence); 

// Function querySailing displays all available sailings,
// and prompts the user to select a sailing
// Displays information on the sailing and 
// returns a string containing the user selected sailingID
//----------------------------------------------------------------
std::string querySailing(); 

// Function removeReservations calls the appropriate functions in the 
// ReservationManager module to remove all reservations from a sailing
//----------------------------------------------------------------
void removeReservations(std::string sailingID); 

// Function printSailingReport sends a sailing report to a printer to be printed
void printSailingReport(std::string printerName);