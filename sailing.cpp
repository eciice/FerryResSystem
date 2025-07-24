//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//================================================================
//================================================================
/*
 * Filename: Sailing.cpp
 *
 * Description: Implementing sailing moduel file I/O with fixed
 * length binary records, checks read, write and opens the file 
 * at start up, checking queries that shows all records. 
 */

//================================================================
#include "sailing.hpp"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#ifdef _WIN32
	#include <io.h>      
#else
	#include <unistd.h>  
	#include <fcntl.h>
#endif
static std::fstream sailingFile;
static const std::string sailingFileName = "sailings.dat";

//================================================================

// Function open creates and opens the Sailing file
// Throws an exception if the file cannot be opened
//----------------------------------------------------------------
void sailingOpen()
{
	// Try to open the sailing file without overwriting the contents
	sailingFile.open(sailingFileName, std::ios::in | std::ios::out | std::ios::binary);
	if (!sailingFile.is_open())
	{
		// Try to create a sailing file if it does not exist
		sailingFile.clear();
		sailingFile.open(sailingFileName, std::ios::out | std::ios::binary);
		
		if (!sailingFile.is_open())
		{
			// Throw an exception if the file cannot be created
			throw std::runtime_error("Cannot create " + sailingFileName);
		}
		sailingFile.close();

		// Try to now re-open the file for reading and writing
		sailingFile.open(sailingFileName, std::ios::in | std::ios::out | std::ios::binary);
		if (!sailingFile.is_open())
		{
			// Throw an exception if the file cannot be opened
			throw std::runtime_error("Cannot open " + sailingFileName);
		} 
	}
}

// Function close closes the Sailing file
//----------------------------------------------------------------
void sailingClose()
{
	if (!sailingFile.is_open())
	{
		throw std::runtime_error("Close: " + sailingFileName + " File not open.");
	}
	sailingFile.close();
}

// Function reset seeks to the beginning of the Sailing file
// Throws an exception if the file is not open
//----------------------------------------------------------------
void sailingReset()
{
	if (!sailingFile.is_open())
	{
		throw std::runtime_error("Reset: " + sailingFileName + " File not open.");
	}
	sailingFile.clear();
	sailingFile.seekg(0, std::ios::beg); // Set get position to the start of the file
	sailingFile.seekp(0, std::ios::beg); // Set put position to the start of the file
}

// Function getNextSailing obtains a line from the Sailing file
// Returns a boolean if retrieving all the data was successful
// Throws an exception if the read operation fails
//----------------------------------------------------------------
bool getNextSailing(Sailing& s)
{
	if (!sailingFile.is_open())
	{
		throw std::runtime_error("getNextSailing: File not open.");
	}
	sailingFile.read(reinterpret_cast<char*>(&s), sizeof(Sailing));
	if (static_cast<std::size_t>(sailingFile.gcount()) < sizeof(Sailing))
	{
		// if it reaches end of file or partial, then reset the flags 
		sailingFile.clear();
		return false;
	}
	return true;
}

// Function writeSailing writes a sailing record to the Sailing file
// Throws an exception if the write operation fails
//----------------------------------------------------------------
void writeSailing(const Sailing& s)
{
	if (!sailingFile.is_open())
	{
		throw std::runtime_error("writeSailing: File not open.");
	}
	sailingFile.write(reinterpret_cast<const char*>(&s), sizeof(Sailing));
	if (sailingFile.fail() || sailingFile.bad())
	{
		throw std::runtime_error("writeSailing: Failed to write record");
	}
	sailingFile.flush();
}

// Function checkSailingExists checks if a sailing with the provided
// sailingID exists. Returns sailingID, otherwise throws exception.
//----------------------------------------------------------------
int checkSailingExists(const char sailingID[])
{
	sailingReset();
	Sailing temp;
	int index = 0;
	while (getNextSailing(temp))
	{
		if (std::strncmp(temp.sailingID,sailingID,sizeof(temp.sailingID)) == 0)
		{
			return index;
		}
	index++;
	}
	throw std::runtime_error("checkSailingExists: ID not found");
}

// Function deleteSailing deletes a sailing record with the provided
// sailingID. Throws an exception if the record is not found.
//----------------------------------------------------------------
void deleteSailing(const char sailingID[])
{
	if (!sailingFile.is_open())
	{
		throw std::runtime_error("deleteSailing: File not open.");
	}
	//total record
	sailingFile.clear();
	sailingFile.seekg(0, std::ios::end);
	std::streampos size = sailingFile.tellg();
	int total = static_cast<int>(size / sizeof(Sailing));
	if (total == 0)
	{
		throw std::runtime_error("deleteSailing: No records to delete");
	}

	// FInd target index
	sailingFile.seekg(0, std::ios::beg);
	int target = -1;
	Sailing temp;
	Sailing lastRecord;
	for (int i = 0; i < total; ++i)
	{
		sailingFile.read(reinterpret_cast<char*>(&temp), sizeof(Sailing));
		if (std::strncmp(temp.sailingID, sailingID, sizeof(temp.sailingID)) == 0)
		{
			target = i;
			break;
		}
	}
	sailingFile.seekg((total - 1) * sizeof(Sailing), std::ios::beg);
	sailingFile.read(reinterpret_cast<char*>(&lastRecord), sizeof(Sailing));

	if (target < 0)
	{
		throw std::runtime_error(std::string("deleteSailing: '") + sailingID + "' not found");
	}

	// read record
	if (sailingFile.fail())
	{
		throw std::runtime_error("deleteSailing: Failed reading last record");
	}

	// overwirte target slot
	sailingFile.seekp(target * sizeof(Sailing), std::ios::beg);
	sailingFile.write(reinterpret_cast<const char*>(&lastRecord), sizeof(Sailing));
	if (sailingFile.fail())
	{
		throw std::runtime_error("deleteSailing: Overwrite failed");
	}

//Truncate 
#ifdef _WIN32
    {
        // flush and close c++ stream
        sailingFile.flush();
        sailingFile.close();

        // open FILE*
        FILE* f = std::fopen(sailingFileName.c_str(), "r+b");
        if (!f)
		{
            throw std::runtime_error("deleteSailing: fopen failed");
        }
        int fd = _fileno(f);

        // trunctate
        long newSize = static_cast<long>((total - 1) * sizeof(Sailing));
        if (_chsize_s(fd, newSize) != 0)
		{
            std::fclose(f);
            throw std::runtime_error("deleteSailing: truncate failed");
        }
        std::fclose(f);

        sailingFile.open(sailingFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!sailingFile.is_open()) 
		{
            throw std::runtime_error("deleteSailing: re-open failed");
        }
    }
#else
    {
        // close c++ stream
        sailingFile.close();

        // open file descriptor 
        int fd = ::open(sailingFileName.c_str(), O_RDWR);
        if (fd < 0)
		{
            throw std::runtime_error("deleteSailing: open failed");
        }

        // truncation
        off_t newSize = static_cast<off_t>((total - 1) * sizeof(Sailing));
        if (ftruncate(fd, newSize) != 0)
		{
            close(fd);
            throw std::runtime_error("deleteSailing: truncate failed");
        }
        close(fd);

        sailingFile.open(sailingFileName, std::ios::in | std::ios::out | std::ios::binary);
        if (!sailingFile.is_open())
		{
            throw std::runtime_error("deleteSailing: re-open failed");
        }
    }
#endif
}