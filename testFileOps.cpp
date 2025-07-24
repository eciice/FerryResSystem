//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//============================================================
//============================================================
/*
* Filename: testFileOps.cpp
*
* Revision History:
* Rev. 1 - 25/07/23 Original by L. Xu
*
* Unit Test: Vessel file low-level functionality
* Writes three Vessel records, then reads them back and checks
* if they are written correctly. Will verify that
* getNextVessel() returns false if failed.
* Check end-of-file behaviour
*
* Test Type: Bottom-up integration
* Preconditions:
* - The Vessel file is not used by another module
* - The file may or may not already exist
* - If the file alreaady exists, it must be empty
* Test Steps:
* 1. Call vesselOpen()
* 2. Write 3 vessel records with writeVessel()
* 3. Just in case reset file using vesselReset()
* 4. Create 3 new vessel objects and read 3 vessel records into
* them using getNextVessel()
* 5. Compare result data fields to the expected
* 6. Check that getNextVessel returns false at the end of file
* 7. Print "Pass" or "Fail"
*/
//============================================================

#include "vessel.hpp"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <string>

//============================================================
// Function main creates instances of vessels and makes sure
// they are read and written properly
// Throws an exception if the file cannot be opened
//------------------------------------------------------------
int main()
{

    bool pass=true; // Boolean to check if written = read values

    try 
    {
        // Make a binary file or open if one already exists
        vesselOpen();

        // Write 3 vessels to the binary file
        Vessel v1;
        strncpy(v1.name, "CANADIANVESSEL7", sizeof(v1.name) - 1);
        v1.name[sizeof(v1.name) - 1] = '\0';
        v1.HCLL = 1000.0f; 
        v1.LCLL = 2500.0f;
        writeVessel(v1);

        Vessel v2;
        strncpy(v2.name, "NEWSFUVESSEL", sizeof(v2.name) - 1);
        v2.name[sizeof(v2.name) - 1] = '\0';
        v2.HCLL = 1500.0f;
        v2.LCLL = 2000.0f;
        writeVessel(v2);

        Vessel v3;
        strncpy(v3.name, "B.C._VESSEL", sizeof(v3.name) - 1);
        v3.name[sizeof(v3.name) - 1] = '\0';
        v3.HCLL = 1250.0f;
        v3.LCLL = 1750.0f;
        writeVessel(v3);

        Vessel v4, v5, v6; // Vessels that will take in the read values
        Vessel v7; // Vessel to test that the system will not read at the end of file
        vesselReset();
        
        // Read the vessel records  
        if (!getNextVessel(v4))
        {
            std::cout << "Vessel 1 has NOT been read successfully\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 1 has been read successfully\n";
        }
        
        // Check if the vessel attributes are the same as was written
        if (std::strcmp(v1.name, v4.name) != 0 ||
            v4.HCLL != v1.HCLL || v4.LCLL != v1.LCLL)
        {
            std::cout << "Vessel 1 attributes are not correct\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 1 attributes are correct\n";
        }
        
        // Read the vessel records  
        if (!getNextVessel(v5))
        {
            std::cout << "Vessel 2 has NOT been read successfully\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 2 has been read successfully\n";
        }
        // Check if the vessel attributes are the same as was written
        if (std::strcmp(v2.name, v5.name) != 0 ||
            v5.HCLL != v2.HCLL || v5.LCLL != v2.LCLL)
        {
            std::cout << "Vessel 2 attributes are not correct\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 2 attributes are correct\n";
        }

        // Read the vessel records  
        if (!getNextVessel(v6))
        {
            std::cout << "Vessel 3 has NOT been read successfully\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 3 has been read successfully\n";
        }
        // Check if the vessel attributes are the same as was written
        if (std::strcmp(v3.name, v6.name) != 0 ||
            v6.HCLL != v3.HCLL || v6.LCLL != v3.LCLL)
        {
            std::cout << "Vessel 3 attributes are not correct\n";
            pass = false;
        }
        else
        {
            std::cout << "Vessel 3 attributes are correct\n";
        }

        // Check the read data values
        std::cout << "Format: vesselName HCLL LCLL\n";
        std::cout << "Expected: " << v1.name << " " << v1.HCLL << " " << v1.LCLL <<"\n";
        std::cout << "Result: " << v4.name << " " << v4.HCLL << " " << v4.LCLL <<"\n";
        std::cout << "Expected: " << v2.name << " " << v2.HCLL << " " << v2.LCLL <<"\n";
        std::cout << "Result: " << v5.name << " " << v5.HCLL << " " << v5.LCLL <<"\n";
        std::cout << "Expected: " << v3.name << " " << v3.HCLL << " " << v3.LCLL <<"\n";
        std::cout << "Result: " << v6.name << " " << v6.HCLL << " " << v6.LCLL <<"\n";

        // Check for reading at end of file
        std::cout << "Results of reading at end of file (should not read data): ";
        if (!getNextVessel(v7))
        {
            std::cout << "System did not read at the end of file\n";
        }
        else
        {
            std::cout << "System did read at the end of file\n";
            std::cout << v7.name << " " << v7.HCLL << " " << v7.LCLL << "\n";
            pass = false;
        }
        // Close the vehicle file
        vesselClose();
        
    }
    // Print out errors with reading/writing binary file data
    catch (const std::exception& e)
    {
        std::cout << "Problem with test: " << e.what();
        return 1;
    }
    // Check if the test passed
    if (pass)
    {
        std::cout << "Pass" << '\n';
    }
    else
    {
        std::cout << "Fail" << '\n';
    }

    std::cout << "---Vessel File Complete---";
    return 0;

}