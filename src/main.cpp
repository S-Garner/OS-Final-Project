#include <string>
#include <fstream>
#include <iostream>

/**
 * @brief Read a single line from the
 * 
 * @param filename The name of the file to read from
 */

std::string readLineFromFile(const char *filename) {    // Function header
    std::ifstream in(filename);                         // Open file for reading
    if (!in) {                                          // Check if file is open
        std::cerr << "Cannot open input file.\n";       // Print error message
        std::exit(1);                                   // Exit with 1 which indicates error
    }                                                   // End if statement

    std::string line;                                   // Declare string variable to hold the line
    if (!std::getline(in, line)) {                      // Read a single line from the file
        std::cerr << "Input file is empty.\n";          // Print error message
        std::exit(1);                                   // Exit with 1 which indicates error
    }                                                   // End if statement

    return line;                                        // Return the line
}

/**
 * @brief Parse the input line and store the values in the given variables.
 * 
 * @param line The input line to parse.
 * @param algo The selected algorithm.
 * @param frameCount The number of frames in the cache.
 * @param refs An array to store the reference values.
 * @param refCount The number of references in the input line.
 */

void parseInputLine(const std::string &line,            // The input line to parse
                    char &algo,                         // The selected algorithm
                    int &frameCount,                    // Number of frames that can be used
                    int refs[],                         // Reference to the string value from the file
                    int &refCount)                      // Number of references in the input line
{
    algo = 0;                                           // Set the algorithm to 0
    frameCount = 0;                                     // Set the number of frames to 0
    refCount = 0;                                       // Set the number of references to 0

    int i = 0;                                          // Index for the input line, set to 0
    int n = line.size();                                // Size of the input line

    while (i < n &&                                     // While index is less than the size of the input line
           (line[i] == ' ' ||                           // If the character is a space
            line[i] == '\t'))                           // Or if the character is a tab
        i++;                                            // Increment the index

    if (i < n)                                          // If the index is less than the size of the input line
        algo = line[i++];                               // Set the algorithm to the character at index
    else                                                // else
        return;                                         // Return

    while (i < n &&                                     // While index is less than the size of the input line
           line[i] != ',')                              // And the character is not a comma
        i++;                                            // Increment the index

    if (i < n &&                                        // If the index is less than the size of the input line
        line[i] == ',')                                 // And the character is a comma
        i++;                                            // Increment the index

    while (i < n &&                                     // While index is less than the size of the input line
           line[i] >= '0' &&                            // And character is greater than or equal to 0
           line[i] <= '9') {                            // And character is less than or equal to 9
        frameCount =                                    // frameCount is equal to
        frameCount * 10 +                               // frameCount * 10 multi digit numbers
        (line[i] - '0');                                // subtract the character from '0' to convert to numeric value
        i++;                                            // Increment the index
    }                                                   // End of while loop

    if (i < n &&                                        // If the index is less than the size of
        line[i] == ',')                                 // And line is a comma
        i++;                                            // Increment the index

    while (i < n) {                                     // While index is less than the size of the input line

        while (i < n &&                                 // While index is less than the size of the input line
               (line[i] == ',' ||                       // And line is a comma
                line[i] == ' ' ||                       // Or line is a space
                line[i] == '\t'))                       // Or line is a tab
            i++;                                        // Increment the index

        if (i >= n) break;                              // Break the loop if index is greater than or equal to the size of the input line

        int val = 0;                                    // Initialize val to 0
        bool hasDigit = false;                          // Initialize hasDigit to false

        while (i < n &&                                 // While index is less than the size of the input line
               line[i] >= '0' &&                        // And character is greater than or equal to 0
               line[i] <= '9') {                        // And character is less than or equal to 9 

            val =                                       // Set val to
            val * 10 +                                  // val * 10
            (line[i] - '0');                            // Character minus '0'
            hasDigit = true;                            // Set hasDigit to true

            i++;                                        // Increment the index
        }                                               // End of while loop

        if (hasDigit)                                   // If hadDigit is true
            refs[refCount++] = val;                     // Add val to ref at refCount and increment refCount
    }                                                   // End while loop
}                                                       // End of function readInputLine

/**
 * @brief Wipe the view table
 * 
 * @param table the view table
 * @param frameCount the number frames that can be used
 * @param refCount the number of references in the input line
 */

void wipeTable(int table[][1000],                       // The view table
               int &frameCount,                         // The number of frames that can be used
               int &refCount)                           // The number of references in the input line
{
    for (int i = 0;                                     // Start of for loop
         i < frameCount;                                // While i is less than frameCount
         i++) {                                         // Increment the index

        for (int j = 0;                                 // Start of for loop
             j < refCount;                              // While j is less than refCount
             j++) {                                     // Increment the index

            table[i][j] = -1;                           // Set table[i][j] to -1

        }                                               // End nested for loop
    }                                                   // End for loop
}                                                       // End of function wipeTable

/**
 * @brief Find a page in the view
 * 
 * @param frames the frames to search
 * @param frameCount the number of frames that can be used
 * @param page the page to find
 */

int findPage(int frames[],                              // The frames
             int frameCount,                            // The number of frames that can be used
             int page)                                  // The page to find
{
    for (int i = 0;                                     // Start of for loop
        i < frameCount;                                 // While i is less than frameCount
        i++) {                                          // Increment the index

        if (frames[i] == page)                          // If the page is found
            return i;                                   // Return index
    }                                                   // End for loop

    return -1;                                          // Return -1 if page not found
}                                                       // End of function findPage

/**
 * @brief Tester function for testing the program functions
 */

void testers()
{
    std::string testLine =                              // The input line
        readLineFromFile("data/TESTER_CORRECT.txt");    // Read the input line from test file
    
    std::cout << "Input Line: " <<                      // Print the input line
        testLine << "\n";                               // Print the string from the file

    int frameCount, refCount;                           // The number of frames that can be used and the reference count
    char algo;                                          // The algorithm to use
    int refs[100];                                      // The reference string

    int displayTable[50][1000];                         // Test display table

    parseInputLine(testLine,                            // Testing the parseInputLine function
                   algo,                                // Algorithm to use
                   frameCount,                          // Number of frames that can be used
                   refs,                                // References from input file
                   refCount);                           // Number of references from input file

    std::cout << "Algorithm: " <<                       // Display algorithm line
        algo << "\n";                                   // The algorithm used
    std::cout << "Frame Count: " <<                     // The number of frames that can be used
        frameCount << "\n";                             // The number of frames that can be used
    std::cout << "Reference String: ";                  // Start of displaying the reference string

    for (int i = 0;                                     // Start for loop
         i < refCount;                                  // Number of references in the file
         i++) {                                         // Increment the index
        std::cout << refs[i] << " ";                    // Display the reference string
    }                                                   // End for loop

    std::cout << "\n";                                  // Insert next line

    wipeTable(displayTable,                             // Wipe the displayTable
              frameCount,                               // Number of frames that can be used
              refCount);                                // Number of references from input file

    for (int i = 0;                                     // Start for loop
         i < frameCount;                                // While index is less than the number of frames that can be used
         i++) {                                         // Increment the index

        for (int j = 0;                                 // Start for loop 
             j < refCount;                              // While index is less than the number of references from input file
             j++) {                                     // Increment the index

            std::cout << displayTable[i][j] << " ";     // Display the table results
        }                                               // End for loop
        std::cout << "\n";                              // Insert next line
    }                                                   // End for loop
    
    std::cout << "\n";                                  // Insert next line

}                                                       // End testers function

/**
 * @brief Runs the FIFO algorithm that removes oldest loaded page
 *        when new page fault occurs and no free frame is available
 *
 * @param frameCount Number of frames that can be used
 * @param refs[]     Array of page references from the input
 * @param refCount   Number of page references in the input
 * @param table[][]  Table used to record the frame contents over time
 *
 * @return Number of page faults that occurred while running FIFO
 */

int FIFO(int frameCount,                                // Number of frames that can be used
         int refs[],                                    // Array of page references from input
         int refCount,                                  // Number of page references in the input
         int table[][1000])                             // Table used to record all frame states
{
    std::cout << "Running FIFO" << std::endl;           // Display that the program is running FIFO

    // Frames[i] = page in frame i, or -1 if empty
    int frames[50];                                     // Array to hold the current pages in each frame

    // Initialize all frames as empty                   // Start of for loop
    for (int i = 0; i < frameCount; i++)                // While index is less than the number of frames
    {                                                   // Increment index by one
        frames[i] = -1;                                 // Set frame to -1 (empty)
    }                                                   // End for loop

    int pageFaults = 0;                                 // Store number of page faults

    int fifoIndex = 0;                                  // Index of the next frame to replace/FIFO queue pointer

    // t for time
    for (int t = 0; t < refCount; t++)                  // Start of for loop over all references (time steps)
    {                                                   // While index is less than the number of references, increment by one
        int page = refs[t];                             // Get the current page reference

        int position = findPage(frames, frameCount, page);  // Check if the page is already in one of the frames, number of frames that can be used, page to find

        bool fault = false;                             // Track whether a page fault occurred at this step

        if (position == -1)                             // If the page is not currently in any frame
        {
            fault = true;                               // This is a page fault
            pageFaults++;                               // Increment page fault counter

            // Search for free frame first
            int freeIndex = -1;                         // Index of a free (empty) frame if any exists

            for (int i = 0; i < frameCount; i++)        // Start of for loop, while index is less than the number of frames, increment index by one
            {
                if (frames[i] == -1)                    // If this frame is empty
                {
                    freeIndex = i;                      // Mark this frame as free
                    break;                              // Break out of loop once a free frame is found
                }                                       // End if statement
            }                                           // End for loop

            if (freeIndex != -1)                        // If a free frame was found
            {
                // Still space, use first free frame
                frames[freeIndex] = page;               // Place the new page into the free frame
            } else {                                    // Else there is no free frame available
                // No free frame, replace using FIFO
                frames[fifoIndex] = page;               // Replace the page at fifoIndex
                fifoIndex = (fifoIndex + 1) % frameCount; // Move FIFO pointer to the next frame
            }                                           // End if statement
        }                                               // End for loop

        // Only write frames into table when a fault occurs
        // Else the column stays blank when printed
        // f for frame
        if (fault)                                      // If a page fault occurred at this time step
        {
            for (int f = 0; f < frameCount; f++)        // Start of for loop, while index is less than the number of frames, increment index by one
            {
                table[f][t] = frames[f];                // Store the current content of each frame in the table
            }                                           // End for loop
        }                                               // End if statement

    }

    return pageFaults;                                  // Return the number of page faults that occurred
}                                                       // End FIFO function

int OPT(int frameCount,                                 // Number 
        int refs[],                                     // References from file
        int refCount,                                   // Number of references
        int table[][1000])                              // Table to store frames
{
    std::cout << "Running OPT" << std::endl;            // Display that the program is running OPT

    int frames[50];                                     // Initialize frames array

    for (int i = 0;                                     // Start of for loop
         i < frameCount;                                // While index is less than the number of frames
         i++) {                                         // Increment index

        frames[i] = -1;                                 // Set frame to -1; Zeroize frames
    }                                                   // End for loop

    int pageFaults = 0;                                 // Initialize page faults to zero

    for (int t = 0;                                     // Start for loop 
         t < refCount;                                  // While the index is less than the number of references in the input file
         t++) {                                         // Increment index       

        int page = refs[t];                             // Get the current reference

        int pos = findPage(frames,                      // Find the position of the current reference in the frames array
                           frameCount,                  // Number of frames we can use
                           page);                       // What page we are currently on

        bool fault = false;                             // Initialize fault to false

        if (pos == -1) {                                // If position is zeroed
            fault = true;                               // Set fault to true
            pageFaults++;                               // Increment page faults

            int freeIndex = -1;                         // Initialize free index to zeroed value

            for (int i = 0;                             // Start for loop
                 i < frameCount;                        // While the index is less than the number of frames we can use
                 i++) {                                 // Increment index

                if (frames[i] == -1) {                  // If the current frame is empty
                    freeIndex = i;                      // Set free index to current frame
                    break;                              // Break out of loop
                }                                       // End if statement

            }

            if (freeIndex != -1) {                      // If there is an empty frame

                frames[freeIndex] = page;               // Set the frame to the current page

            } else {                                    // Else

                int replaceIndex = 0;                   // Initialize replace index to zeroed value
                int farthestUse = -1;                   // Initialize farthest use to zeroed value

                for (int i = 0;                         // Start for loop
                     i < frameCount;                    // While the index is less than the number of frames we can use
                     i++) {                             // Increment index

                    int currentPage = frames[i];        // Get the current page
                    int nextUse = -1;                   // Initialize next use to zeroed value


                    for (int j = t + 1;                 // Start for loop
                         j < refCount;                  // While the index is less than the number of references
                         j++) {                         // Increment index

                        if (refs[j] == currentPage) {   // If the current reference is equal to the current page
                            nextUse = j;                // Set next use to the current index
                            break;                      // Break the loop
                        }                               // End if statement
                    }                                   // End for loop

                    if (nextUse == -1) {                // If next use is equal to -1

                        replaceIndex = i;               // Set replace index to i
                        farthestUse = refCount + 1;     // Set farthest use to ref count + 1
                        break;                          // Break the loop

                    } else if (nextUse > farthestUse) { // Else if next is greatest than farthest use

                        farthestUse = nextUse;          // Set farthest use to next use
                        replaceIndex = i;               // Set replace index to i
                    }                                   // End if statement
                }                                       // End for loop

                frames[replaceIndex] = page;            // Set frame at replace index to page
            }                                           // End if statement
        }                                               // End for loop

        if (fault) {                                    // If fault is true
            for (int f = 0; f < frameCount; f++) {      // While f is less than frame count
                table[f][t] = frames[f];                // Set table at f to frames[f]
            }                                           // End for loop
        }                                               // End if statement
    }                                                   // End for statement

    return pageFaults;                                  // Return page faults
}                                                       // End OPT function


/**
 * @brief Runs the LRU algorithm, which will remove the least recently used page from memory when a new page fault occurs
 */

int LRU(int frameCount,
        int refs[],
        int refCount,
        int table[][1000])
{
    std::cout << "Running LRU" << std::endl;            // Display that the program is running LRU

    int frames[50];                                     // Array to hold the frames
    int lastUsed[50];                                   // Array to hold the last used time of each frame
                                                        // Clear frames and lastUsed to -1
    for (int i = 0;                                     // Start of for loop
         i < frameCount;                                // As long as index is less than the number of frames
         i++) {                                         // Increment index by one

        frames[i] = -1;                                 // Set the value of frames to -1
        lastUsed[i] = -1;                               // Set the value of lastUsed to -1
    }                                                   // End of for loop

    int pageFaults = 0;                                 // Store number of page faults

    for (int t = 0;                                     // Start of for loop
         t < refCount;                                  // As long as index is less than the number of references
         t++) {                                         // Increment index by one

        int page = refs[t];                             // Store the current reference in page
                                                        // Check if the current reference is in the frames
        int position = findPage(frames,                 // Frames array
                                frameCount,             // How many frames we use
                                page);                  // Page to find

        bool fault = false;                             // Default fault to false

        if (position != -1) {                           // If the current position does not equal -1
            lastUsed[position] = t;                     // Set last used at this position to current index
        } else {                                        // Else if the current position does equal -1
            fault = true;                               // Set fault to true
            pageFaults++;                               // Increment page faults

            int freeIndex = -1;                         // Set the index to -1

            for (int i = 0;                             // Start of for loop
                 i < frameCount;                        // As long as index is less than the number of frames we can use
                 i++) {                                 // Increment index by one

                if (frames[i] == -1) {                  // If this frame is equal to -1
                    freeIndex = i;                      // Set the free index to this index to show this is available
                    break;                              // Break
                }                                       // End if statement
            }

            if (freeIndex != -1) {                      // If the free index is not -1
                frames[freeIndex] = page;               // Set this frames index to the current page
                lastUsed[freeIndex] = t;                // Set the last used to current current index
            } else {                                    // Else if
                int lruIndex = 0;                       // Set the LRU index 
                int oldest = lastUsed[0];               // Set the the oldest to the first element in the array

                for (int i = 1;                         // Start of for loop
                     i < frameCount;                    // As long as index is less than the number of frames we can use
                     i++) {                             // Increment index by one
                    if (lastUsed[i] < oldest) {         // If the last used is less than the oldest
                        oldest = lastUsed[i];           // Set the oldest to this index
                        lruIndex = i;                   // Set the lru index to this index
                    }                                   // End if statement
                }                                       // End for loop

                frames[lruIndex] = page;                // Set the frame at the lru index to this page
                lastUsed[lruIndex] = t;                 // Set the last used at the lru index to this index
            }                                           // End else statement
        }                                               // End else statement

        if (fault) {                                    // If the fault is true
            for (int f = 0;                             // Start of for loop
                 f < frameCount;                        // As long as index is less than the number of frames we can use
                 f++) {                                 // Increment index by one
                table[f][t] = frames[f];                // Set the table at this index to this frame
            }                                           // End for loop
        }                                               // End if statement
    }                                                   // End for loop

    return pageFaults;                                  // Return the number of page faults that occurred
}                                                       // End of LRU function

/**
 * @brief Prints the table to stdout
 * 
 * @param refs[] Array of references from input file
 * @param refCount Number of references in input file
 * @param frameCount Number of frames allowed to be used per
 * @param table[][] Table to print
 * @param pageFaults Number of page faults that occurred
 */

void printTable(int refs[],
                int refCount,
                int frameCount,
                int table[][1000],
                int pageFaults)
{

    for (int t = 0;                                     // Start for loop
         t < refCount;                                  // While the index is less than the number of references in the input file
         t++) {                                         // Increment the index by one

        std::cout << refs[t] << " ";                    // Add space at current index
    }                                                   // End for loop        

    std::cout << "\n";                                  // Add new line

    for (int t = 0;                                     // Start for loop
         t < refCount * 2;                              // While the index is less than twice the number of references in the input file
         t++) {                                         // Increment the index by one
        std::cout << "-";                               // Add dash at current index
    }                                                   // End for loop

    std::cout << "\n";                                  // Add new line
    
    for (int f = 0;                                     // Start for loop
         f < frameCount;                                // While the index is less than the number of frames that can be used in the frame
         f++) {                                         // Increment the index by one

        for (int t = 0;                                 // Start for loop 
             t < refCount;                              // While the index is less than the number of references in the input file
             t++) {                                     // Increment the index by one

            if (table[f][t] == -1)                      // If table is equal to -1 (blank)
                std::cout << "  ";                      // Display space
            else                                        // Else
                std::cout << table[f][t] << " ";        // Display the value at this point

        }                                               // End for loop

        std::cout << "\n";                              // Add new line

    }                                                   // End for loop

    std::cout << "Total page faults = " <<              // Display the message for the total number of faults
        pageFaults << "\n";                             // Display total number of page faults
}                                                       // End of printTable function

/**
 * @brief Main function
 */

int main(int argc, char *argv[]) {                      // Main function
    
    if (argc != 2) {                                    // If the number of arguments is not equal to 2
        std::cerr << "Usage: " <<                       // Throw an error message
            argv[0] << " <input_file>\n";               // Display the usage message

        return 1;                                       // Return 1
    }                                                   // End if statement

    std::string line = readLineFromFile(argv[1]);       // Run readLineFromFile function using argv[1] as an argument
    
    int frameCount, refCount;                           // Declare frame count and reference count variables
    char algo;                                          // Declare algorithm variable
    int refs[100];                                      // Declare reference count array

    int displayTable[50][1000];

    parseInputLine(line,                                // Parse the input line
                   algo,                                // Algorithm to be used
                   frameCount,                          // Frame count that can be used
                   refs,                                // Reference count array
                   refCount);                           // Number of references from the input line

    wipeTable(displayTable, frameCount, refCount);      // Wipe display table

    int pageFaults;                                     // Declare number of page faults

    switch (algo)                                       // Start switch statement
    {
        case 'F': case 'f':                             // If file contains f or F
            pageFaults = FIFO(frameCount,               // Run FIFO with frameCount
                              refs,                     // Reference array
                              refCount,                 // Number of refs from the input line
                              displayTable);            // The table for displaying
            break;                                      // Break out of switch statement

        case 'O': case 'o':                             // If file contains o or O
            pageFaults = OPT(frameCount,                // Run OPT with frameCount
                             refs,                      // Reference array
                             refCount,                  // Number of refs from the input line
                             displayTable);             // The table for displaying
            break;                                      // Break out of switch statement

        case 'L': case 'l':                             // If file contains l or L
            pageFaults = LRU(frameCount,                // Run LRU with frameCount
                             refs,                      // Reference array
                             refCount,                  // Number of refs from the input line
                             displayTable);             // The table for displaying
            break;                                      // Break out of switch statement
    }

    printTable(refs,                                    // Reference array
               refCount,                                // Number of refs from the input line
               frameCount,                              // Frame count
               displayTable,                            // The table for displaying
               pageFaults);                             // Number of page faults
    
}                                                       // End main statement