//================================================================
//================================================================
/*
* Filename: reservationManager.cpp
*
* Description: Reservation manager module of the Ferry Reservation System,
* manages all functions and commands relating to reservations.
*
*/
//================================================================
#include "reservationManager.hpp"
#include "vehicle.hpp"
#include "reservation.hpp"
#include "sailingManager.hpp"
Reservation* head;
//================================================================
// Function accessSailingManagerUpdate accesses the Sailing Manager module
// to update a sailing
//----------------------------------------------------------------
void accessSailingManagerUpdate(std::string sailingID) 
{
    try {
        // First verify the sailing exists
        if (checkSailingExists(sailingID) != 1) {
            throw std::runtime_error("Sailing does not exist.");
        }
        
        // Get updated sailing information
        updateSailing(sailingID, 0); // 0 indicates we just want to refresh data
        
        // Update reservation counts
        accessReservationManager(sailingID);
        
    } catch (const std::exception& e) {
        std::cerr << "Error updating sailing: " << e.what() << std::endl;
        throw; // Re-throw for calling function to handle
    }
}
// Function accessSailingManager accesses the Sailing Manager module
// to query a sailing
//----------------------------------------------------------------
void accessSailingManagerQuery(std::string sailingID)
{
    try {
        // Verify sailing exists
        if (checkSailingExists(sailingID)) {
            // Display sailing details
            std::string selectedSailing = querySailing();
            
            // Show reservation count
            int reservations = viewReservations(sailingID);
            std::cout << "Total reservations: " << reservations << std::endl;
            
            // Show vessel capacity
            std::string vessel = getVessel(); // Gets vessel for this sailing
            int capacity = getVesselLength(vessel);
            std::cout << "Vessel capacity: " << capacity << " meters" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error querying sailing: " << e.what() << std::endl;
        throw;
    }
}
// Function vehicleCheck checks to see if the vehicle with provided licence plate exists.
// If vehicle does not exist in the system, create a record for vehicle.
//----------------------------------------------------------------
void vehicleCheck(std::string vehicleLicence)
{
    //check if vehicle exists
    bool vehicleExists = false;
    Vehicle v;
    //resets vehicle to start of list
    reset();
    //find the vehicle
    while (getNextVehicle(v)) {
        if (v.vehicleLicence == vehicleLicence) {
            vehicleExists = true;
            break;
        }
    }
    if (!vehicleExists) {
        // Vehicle doesn't exist - create new record
        Vehicle newVehicle;
        newVehicle.vehicleLicence = vehicleLicence;
        
        // Get additional vehicle details from user
        std::cout << "Enter the customer phone number (Length: 14 char max.): ";
        std::cin >> newVehicle.phone;
        
        std::cout << "Enter the length of the vehicle in meters (Range: 7.1-99.9 max): ";
        std::cin >> newVehicle.vehicleLength;
        
        std::cout << "Enter the height of the vehicle in meters(Range: 2.1-9.9m max): 5.2";
;
        std::cin >> newVehicle.vehicleHeight;
        
        // Write the new vehicle to file
        writeVehicle(newVehicle);
        
        std::cout << "New vehicle record created." << std::endl;
    }
    else {
        std::cout << "Vehicle found in system." << std::endl;
    }

}
// Function createReservation creates a reservation for the vehicle
// with the corresponding licence plate on the specified sailing
//----------------------------------------------------------------
void createReservation(std::string sailingID, std::string vehicleLicence)
{
        string vehicleLicence, phoneNumber, sailingID;
    float length, height;
    char choice;

    cout << "Enter 1 to create a reservation. 0 to go back to the main menu\n";
    // Get input here...

    cout << "Enter the licence plate of the vehicle (Length: 10 char max.):\n";
    std::cin >> vehicleLicence;
    cout << "Vehicle verified\n";

    cout << "Enter the customer phone number (Length: 14 char max.):\n";
    std::cin >> phoneNumber;
    cout << "Customer verified\n";

    cout << "Enter the length of the vehicle in meters (Range: 7.1-99.9 max):\n";
   std::cin >> length;
    cout << "Valid length\n";

    cout << "Enter the height of the vehicle in meters(Range: 2.1-9.9m max):\n";
    std::cin >> height;
    cout << "Valid height\n";

    cout << "Enter the Sailing ID (Format: ttt-dd-hh):\n";
    std::cin >> sailingID;
    cout << "Remaining low lane space: 3600m\n"
         << "Remaining high lane space: 3600m\n"
         << "Sufficient space to proceed\n";

    // Create new reservation
    Reservation* newRes = new Reservation{sailingID, vehicleLicence, false, false, nullptr};
    //add to file
    writeReservation();
}
// Function deleteReservations with parameters sailingID, vehicleLicence
// deletes a reservation on the specified sailing
// for the vehicle with the corresponding licence plate
//----------------------------------------------------------------
void deleteReservations(std::string sailingID, std::string vehicleLicence)
{

    deleteReservation(sailingID, vehicleLicence);
}
// Function deleteReservations with single parameter sailingID
// deletes all reservations on the specified sailing
//----------------------------------------------------------------
void deleteReservations(std::string sailingID)
{
    
    Reservation* current = head;
    Reservation* prev = nullptr;
    
    while (current) {
        if (current->sailingID == sailingID) {
            if (prev == nullptr) {
    
                head = current->next;
                current = head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            
            delete current;
        } 
            prev = current;
            current = current->next;
        
    }
        throw std::runtime_error("No reservations found for this sailing.");
}
// Function viewReservations returns the number of reservations for a sailing
int viewReservations(std::string sailingID){
    Reservation* head;
    Reservation* current = head;
    int count = 0;
    //loops for all sailing and counts sailing
    while (current) {
        if (current->sailingID == sailingID) {
        count++;
         current = current->next;
    }
}
if (count == 0) {
        cout << "No reservations found for sailing " << sailingID << endl;
    }
return count;
    
}
// Function checkIn() sets the status of specified reservation as checked in
//----------------------------------------------------------------
void checkIn(std::string sailingID, std::string vehicleLicence)
{
    reset();
    //loops through the file, if it matches, return true, else it will automatically be false
    Reservation r;
    while (getNextReservation(r.sailingID, r.vehicleLicence)) {
        if (r.sailingID == sailingID && r.vehicleLicence == vehicleLicence) {
            r.onBoard = true;
            return;
        }
    }
    throw std::runtime_error("Reservation not found for check in.");
}