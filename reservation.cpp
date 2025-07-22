//================================================================
//================================================================

/*
 * Filename: reservation.cpp
 * 
 * Description: Reservation module of the Ferry Reservation System,
 *              checks if information already exists for reservation.
 * 
 */

//================================================================

#include "reservation.hpp"
#include <fstream>
#include <stdexcept>
static Reservation* head = nullptr;
static Reservation* current = nullptr;
static const std::string reservationFileName = "reservations.txt";
//================================================================

// Function creates and opens reservation file.
// Throw an exception if it cannot be opened.
//----------------------------------------------------------------
void reservationOpen()
{
    // Open the input file for reading
    std::ifstream file(reservationFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file.");
    }

    // Variables to temporarily store data read from the file
    std::string sailingID, vehicleLicence;
    bool onBoard, isLRL;

    // tail pointer helps in appending new nodes to the end of the list
    Reservation* tail = nullptr;

    // Read each line from the file until EOF
    while (file >> sailingID >> vehicleLicence >> onBoard >> isLRL) {
        // Create a new node with the read data
        Reservation* node = new Reservation{sailingID, vehicleLicence, onBoard, isLRL, nullptr};

        // If the list is empty, set both head and tail to the new node
        if (!head) {
            head = tail = node;
        } 
        // Otherwise, append the new node to the end and update tail
        else {
            tail->next = node;
            tail = node;
        }
    }

    // Close the file after reading
    file.close();

    // Reset the 'current' pointer to the head of the list (for traversal)
    current = head;
}

// Function resets to the beginning of the list.
// Throw an exception if it cannot be opened.
//----------------------------------------------------------------
void reservationReset()
{
    //resets to beginning
    if (!head) {
        throw std::runtime_error("File not found.");
    }
    current = head;
}

// Function getNextReservation returns a line from the data
// Returns a boolean if the data is successfully read
// Throws an exception if there is an error with reading the files
//----------------------------------------------------------------
bool getNextReservation(std::string sailingID, std::string vehicleLicence)
{
    Reservation* node = head;
    //loops and finds matching
    while (node) {
        if (node->sailingID == sailingID && node->vehicleLicence == vehicleLicence) {
            return true;
        }
        //go next
        node = node->next;
    }
    return false;

}
// Function writeReservation writes to reservation file
// Throws an exception if it fails
// Returns true if more reservations exist, false if we've shown all
//----------------------------------------------------------------
void writeReservation()
{
//throw exception if file not opened
   std::ofstream file(reservationFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing.");
    }

    // If current is null, start from head (first call)
    if (!current) {
        current = head;
    }
    //puts all the variables into the file
    while (current) {
        file << current->sailingID << " " 
             << current->vehicleLicence << " " 
             << current->isLRL << " " 
             << current->onBoard << "\n";
        current = current->next;
    }

    file.close();
}

// Function closes reservation file
//----------------------------------------------------------------
void reservationClose()
{
    if (!head) {
        throw std::runtime_error("File not found.");
    }
    Reservation* node = head;
    while (node) {
        Reservation* temp = node;
        node = node->next;
        delete temp;
    }
    head = nullptr;
    current = nullptr;
}

// Function deleteReservation deletes a reservation with the provided
// sailingID and vehicleLicence. Throws an exception if the record is not found.
//----------------------------------------------------------------
void deleteReservation(std::string sailingID, std::string vehicleLicence)
{
    //initialize head and prev for deletion
Reservation* node = head;
    Reservation* prev = nullptr;

    //loops through the linked list
    while (node) {
        //if found
        if (node->sailingID == sailingID && node->vehicleLicence == vehicleLicence) {
            //if the value is found at the head
            if (prev == nullptr) {
                head = node->next;
                //disconnects the node
            } else {
                prev->next = node->next;
            }
            //
            if (current == node) {
                current = node->next;
            }
            //deletes the found node
            delete node;
            return;
        }
        //
        prev = node;
        node = node->next;
    }

    throw std::runtime_error("Reservation not found for deletion.");
}