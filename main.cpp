//================================================================
//================================================================

/*
 * Filename: main.cpp
 * 
 * Revision History: 
 * Rev. 1 - 25/07/06 Original by A. Kong
 *
 * Description: Main module of the Ferry Reservation System,
 *              sends function calls to other modules to intialize/shutdown
 *              
 */

//================================================================

#include <iostream>
#include "ui.hpp" // include header files
#include "sailingManager.hpp"
#include "reservationManager.hpp"
#include "reservation.hpp"
#include "vessel.hpp"
#include "sailing.hpp"
#include "vehicle.hpp"
using std::endl; 
using std::cout;

//================================================================


// Function init initializes all the modules, excluding the UI module
//----------------------------------------------------------------
 void init()
 {
    std::cout << "I am starting up" << std::endl;
    return;
 }


// Function startAccepting initializes the UI module
//----------------------------------------------------------------
void startAccepting()
{
    std::cout << "UI is now accepting input" << std::endl;
}

// Function startAccepting shuts down the UI module
//----------------------------------------------------------------
void stopAccepting()
{
    std::cout << "UI is no longer accepting input" << std::endl;
}

// Function shutdown shuts down all modules, excluding the UI module
//----------------------------------------------------------------
 void shutdown()
 {
    std::cout << "I am shutting down" << std::endl;
    return;
 }

//----------------------------------------------------------------

int main()
{
    // initialize necessary modules
    init();
    // initialize UI module
    startAccepting();
    // shutdown UI module
    stopAccepting();
    // shutdown all modules, including UI module
    shutdown();
    return 0;
}      

/*
 * Coding Convention
 * 
 * Camel casing should be used for variable naming
 * 
 * Constants should be completely uppercase
 * 
 * Struct names should have their first letter capitalized
 * 
 * 4-character indenting of blocks is to be used
 * 
 * Commas, colons and semicolons should be followed by a space
 * 
 * "=" should be surrounded by spaces (example: "x = y")
 * 
 * Opening braces are to be put on a separate line by themselves
 * 
 * Each .h file should start with the indicated double dividing line:
 * //================================================================
 * //================================================================
 * 
 * Each .cpp module should start with a comment stating its filename, followed
 * by a Revision History section and a description of the purpose of the module
 * 
 * Module name should be at the top of each module.h file
 * 
 * Code version history is to be written in the following format,
 * with latest revisions going first:
 * Revision History:
 * Rev. X - YY/MM/DD Modified by (name)
 *        - Description of changes
 * Rev. 2 - 25/07/12 Modified by J. Smith
 *        - Fixed an unintended bug in the main fuction
 * Rev. 1 - 25/07/06 Original by B. Bong
 * 
 * The indicated dividing line should go just above each function, with function comments
 * going above the dividing line, and function prototypes going below the line:
 * //----------------------------------------------------------------
 * 
 * Each major section of a listing should be separated by the indicated dividing line
 * //================================================================
 *
 * Function prototypes are to be written one parameter per line, with a comment
 * to the right of each, indicating its direction and unit of measure (if applicable)
 * 
 */