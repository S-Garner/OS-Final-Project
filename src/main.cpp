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

void parseInputLine(const std::string &line,
                    char &algo,
                    int &frameCount,
                    int refs[],
                    int &refCount)
{
    // Reset output variables before parsing begins.
    algo = 0;
    frameCount = 0;
    refCount = 0;

    int i = 0;
    int n = line.size();

    // Skip leading whitespace before reading the algorithm code.
    while (i < n && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // First non-space character is the algorithm identifier (F, O, or L).
    if (i < n)
        algo = line[i++];
    else
        return;   // Empty or malformed line.

    // Move forward to the comma after the algorithm character.
    while (i < n && line[i] != ',')
        i++;
    if (i < n) i++;   // Skip comma

    // Parse the frame count (may contain multiple digits).
    // Convert characters to an integer until hitting a non-digit.
    while (i < n && line[i] >= '0' && line[i] <= '9') {
        frameCount = frameCount * 10 + (line[i] - '0');
        i++;
    }

    // Skip the comma separating frame count from the reference string.
    if (i < n && line[i] == ',')
        i++;

    // Parse the rest of the line as the page-reference sequence.
    // Skip commas/whitespace, then read each multi-digit number into refs[].
    while (i < n) {

        // Skip separators between numbers.
        while (i < n &&
              (line[i] == ',' || line[i] == ' ' || line[i] == '\t'))
            i++;

        if (i >= n) break;

        int val = 0;
        bool hasDigit = false;

        // Convert continuous digits into an integer value.
        while (i < n && line[i] >= '0' && line[i] <= '9') {
            val = val * 10 + (line[i] - '0');
            hasDigit = true;
            i++;
        }

        // Store parsed page reference in the refs array.
        if (hasDigit)
            refs[refCount++] = val;
    }
}


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

int FIFO(int frameCount,
         int refs[],
         int refCount,
         int table[][1000])
{
    std::cout << "Running FIFO" << std::endl;

    int frames[50];     // The memory frames currently holding pages

    // Initialize all frames as empty (-1 means no page loaded yet)
    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    int pageFaults = 0;     // Count how many misses occur
    int fifoIndex = 0;      // Points to the next frame to evict (oldest loaded page)

    // Walk through each page request one at a time
    for (int t = 0; t < refCount; t++)
    {
        int page = refs[t];

        // Check whether the page is already in memory
        int position = findPage(frames, frameCount, page);

        bool fault = false;

        // If not present, FIFO must load it
        if (position == -1)
        {
            fault = true;
            pageFaults++;

            // Look for an unused spot before replacing anything
            int freeIndex = -1;
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    freeIndex = i;
                    break;
                }
            }

            if (freeIndex != -1) {
                // There is still empty space then load page into the first empty frame
                frames[freeIndex] = page;
            }
            else {
                // No empty frame then move the oldest page 
                frames[fifoIndex] = page;

                // Move the FIFO pointer so the next eviction replaces the next oldest frame
                fifoIndex = (fifoIndex + 1) % frameCount;
            }
        }

        // Only record the table state when the memory actually changed,
        // on page faults
        if (fault) {
            for (int f = 0; f < frameCount; f++)
                table[f][t] = frames[f];
        }
    }

    return pageFaults;
}


int OPT(int frameCount,
        int refs[],
        int refCount,
        int table[][1000])
{
    std::cout << "Running OPT" << std::endl;

    int frames[50];
    
    // Initialize all memory frames as empty
    // Each entry represents which page is currently stored in that frame
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    int pageFaults = 0;

    // Step through each page request in order
    // At each step, check if the requested page is already loaded
    // If not loaded, OPT decides which page to evict based on future use
    for (int t = 0; t < refCount; t++) {

        int page = refs[t];

        // Determine whether the page is already in memory
        int pos = findPage(frames, frameCount, page);

        bool fault = false;

        if (pos == -1) {

            fault = true;
            pageFaults++;

            int freeIndex = -1;

            // Look for an unused frame first
            // If one exists, load the page into that slot and continue
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    freeIndex = i;
                    break;
                }
            }

            // Case 1: There is an empty frame then load page there
            if (freeIndex != -1) {
                frames[freeIndex] = page;
            }

            // Case 2: No empty frame then choose a victim using OPT logic
            else {

                int replaceIndex = 0;
                int farthestUse = -1;

                // For every page currently loaded, determine when it will next be used
                // The page whose next use is farthest in the future (or never used again)
                // is the optimal page to evict
                for (int i = 0; i < frameCount; i++) {

                    int currentPage = frames[i];
                    int nextUse = -1;

                    // Scan forward in the reference string to find when this page is next referenced
                    for (int j = t + 1; j < refCount; j++) {
                        if (refs[j] == currentPage) {
                            nextUse = j;
                            break;
                        }
                    }

                    // If a page is never used again it is the optimal eviction target immediately
                    if (nextUse == -1) {
                        replaceIndex = i;
                        farthestUse = refCount + 1;  // Marker meaning "never used again"
                        break;
                    }

                    // Otherwise track the page with the farthest next occurrence
                    else if (nextUse > farthestUse) {
                        farthestUse = nextUse;
                        replaceIndex = i;
                    }
                }

                // Evict the chosen page and load the requested one
                frames[replaceIndex] = page;
            }
        }

        // Only record table state when a fault occurred
        // This captures the "visual" of how frames changed due to OPT decisions
        if (fault) {
            for (int f = 0; f < frameCount; f++) {
                table[f][t] = frames[f];
            }
        }
    }

    return pageFaults;
}

/**
 * @brief Runs the LRU algorithm, which will remove the least recently used page from memory when a new page fault occurs
 */

int LRU(int frameCount,
        int refs[],
        int refCount,
        int table[][1000])
{
    std::cout << "Running LRU" << std::endl;

    int frames[50];     
    int lastUsed[50];  

    // Initialize all frames as empty and mark every frame as never used
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    // Process each page reference in order
    // At each time step t, decide whether the page exists
    // or must be brought into memory
    for (int t = 0; t < refCount; t++) {

        int page = refs[t];

        // Check whether the requested page is already loaded
        int position = findPage(frames, frameCount, page);

        bool fault = false;

        if (position != -1) {
            // Page is already in memory
            // Update the "last used" timestamp to reflect recent access
            lastUsed[position] = t;
        } 
        else {
            // Page is missing then this is a page fault
            fault = true;
            pageFaults++;

            // First try to find an unused empty frame
            int freeIndex = -1;
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    freeIndex = i;
                    break;
                }
            }

            if (freeIndex != -1) {
                // If an empty frame exists, load the page there
                frames[freeIndex] = page;
                lastUsed[freeIndex] = t;
            } 
            else {
                // No empty frames then choose the least recently used page
                // Scan all frames and pick the one with the oldest timestamp
                int lruIndex = 0;
                int oldest = lastUsed[0];

                for (int i = 1; i < frameCount; i++) {
                    if (lastUsed[i] < oldest) {
                        oldest = lastUsed[i];
                        lruIndex = i;
                    }
                }

                // Replace the LRU page with the new page
                // and update its usage timestamp
                frames[lruIndex] = page;
                lastUsed[lruIndex] = t;
            }
        }

        // If a fault occurred this step,
        // record the current frame contents in the display table
        if (fault) {
            for (int f = 0; f < frameCount; f++) {
                table[f][t] = frames[f];
            }
        }
    }

    // Return the total number of faults observed
    return pageFaults;
}


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