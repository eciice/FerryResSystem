//================================================================
//================================================================

/*
 * Filename: ui.hpp
 * 
 * Description: UI module of the Ferry Reservation System,
 *              manages menu/submenu traversal and calls on appropriate 
 *              functions and modules to execute user commands.
 * 
 */

//================================================================

#pragma once
#include <iostream>
#include "reservationManager.hpp"
#include "sailingManager.hpp"
#include "vessel.hpp"
using std::endl; 
using std::cout;
using std::cin;

//================================================================


// Function creates a new vessel according to user input.
// Throw exception if user input is invalid.
//----------------------------------------------------------------
void createVessel();


// Function sailingManagement moves user to the sailingManagment submenu.
//----------------------------------------------------------------
void sailingManagement();


// Function reservation moves user to the reservations submenu.
//----------------------------------------------------------------
void reservation();