//================================================================
//================================================================

/*
 * Filename: reservation.hpp
 * 
 * Description: Reservation module of the Ferry Reservation System,
 *              checks if information already exists for reservation.
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
// Struct: Reservation
// Purpose: Represents a vessel with its name, and capacity
//----------------------------------------------------------------
struct Reservation
{

std::string sailingID; // 9 digit sailing id
std::string vehicleLicence; // Unique vehicle licence, consisting of 6-10 characters
bool onBoard; // Specifies if a reservation has checked in
bool isLRL; // Specifies which section of the sailing the vehicle is to be parked
Reservation* next; 
};

//================================================================

// Function creates and opens reservation file.
// Throw an exception if it cannot be opened.
//----------------------------------------------------------------
void open();

// Function resets to the beginning of the list.
// Throw an exception if it cannot be opened.
//----------------------------------------------------------------
void reset();

// Function getNextReservation returns a line from the data
// Returns a boolean if the data is successfully read
// Throws an exception if there is an error with reading the files
//----------------------------------------------------------------
bool getNextReservation(std::string sailingID, std::string vehicleLicence);

// Function writeReservation writes to reservation file
// Throws an exception if it fails
//----------------------------------------------------------------
void writeReservation();


// Function closes reservation file
//----------------------------------------------------------------
void close();

// Function deleteReservation deletes a reservation with the provided
// sailingID and vehicleLicence. Throws an exception if the record is not found.
//----------------------------------------------------------------
void deleteReservation(std::string sailingID, std::string vehicleLicence);