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

void testers()
{
    std::string testLine = readLineFromFile("data/TESTER_CORRECT.txt");
    
    std::cout << "Input Line: " << testLine << "\n";

    int frameCount, refCount;
    char algo;
    int refs[100];

    int displayTable[50][1000];

    parseInputLine(testLine, 
                   algo, 
                   frameCount, 
                   refs, 
                   refCount);

    std::cout << "Algorithm: " << algo << "\n";
    std::cout << "Frame Count: " << frameCount << "\n";
    std::cout << "Reference String: ";

    for (int i = 0; i < refCount; i++) {
        std::cout << refs[i] << " ";
    }

    std::cout << "\n";

    wipeTable(displayTable, 
              frameCount, 
              refCount);

    for (int i = 0; 
         i < frameCount; 
         i++) {
        for (int j = 0; 
             j < refCount; 
             j++) {
            std::cout << displayTable[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n";

}

int FIFO(int frameCount,
         int refs[],
         int refCount,
         int table[][1000])
{
    std::cout << "Running FIFO" << std::endl;

    // Frames[i] = page in frame i, or -1 if empty
    int frames[50];

    // Initialize all frames as empty
    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    int pageFaults = 0;

    // FIFO queue pointer/ next frame to replace
    int fifoIndex = 0;

    // t for time
    for (int t = 0; t < refCount; t++)
    {
        int page = refs[t];

        int position = findPage(frames, frameCount, page);

        bool fault = false;

        if (position == -1)
        {
            fault = true;
            pageFaults++;

            // Search for free frame first
            int freeIndex = -1;

            for (int i = 0; i < frameCount; i++)
            {
                if (frames[i] == -1)
                {
                    freeIndex = i;
                    break;
                }
            }

            if (freeIndex != -1)
            {
                // Still space, use first free frame
                frames[freeIndex] = page;
            } else {
                // No free frame, replace using FIFO
                frames[fifoIndex] = page;
                fifoIndex = (fifoIndex + 1) % frameCount;
            }
        }

        // Only write frames into table when a fault occurs
        // Else the column stays blank when printed
        // f for frame
        if (fault)
        {
            for (int f = 0; f < frameCount; f++)
            {
                table[f][t] = frames[f];
            }
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
    return 0;
}

int LRU(int frameCount,
        int refs[],
        int refCount,
        int table[][1000])
{
    std::cout << "Running LRU" << std::endl;

    int frames[50];
    int lastUsed[50];

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    for (int t = 0; t < refCount; t++) {
        int page = refs[t];
        int pos = findPage(frames, frameCount, page);
        bool fault = false;

        if (pos != -1) {
            lastUsed[pos] = t;
        } else {
            fault = true;
            pageFaults++;

            int freeIndex = -1;
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    freeIndex = i;
                    break;
                }
            }

            if (freeIndex != -1) {
                frames[freeIndex] = page;
                lastUsed[freeIndex] = t;
            } else {
                int lruIndex = 0;
                int oldest = lastUsed[0];

                for (int i = 1; i < frameCount; i++) {
                    if (lastUsed[i] < oldest) {
                        oldest = lastUsed[i];
                        lruIndex = i;
                    }
                }

                frames[lruIndex] = page;
                lastUsed[lruIndex] = t;
            }
        }

        if (fault) {
            for (int f = 0; f < frameCount; f++) {
                table[f][t] = frames[f];
            }
        }
    }

    return pageFaults;
}


void printTable(int refs[],
                int refCount,
                int frameCount,
                int table[][1000],
                int pageFaults)
{

    for (int t = 0; t < refCount; t++) {
        std::cout << refs[t] << " ";
    }
    std::cout << "\n";


    for (int t = 0; t < refCount * 2; t++) {
        std::cout << "-";
    }
    std::cout << "\n";

    
    for (int f = 0; f < frameCount; f++) {
        for (int t = 0; t < refCount; t++) {
            if (table[f][t] == -1)
                std::cout << "  "; 
            else
                std::cout << table[f][t] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Total page faults = " << pageFaults << "\n";
}
         
int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::string line = readLineFromFile(argv[1]);
    
    int frameCount, refCount;
    char algo;
    int refs[100];

    int displayTable[50][1000];

    parseInputLine(line, algo, frameCount, refs, refCount);

    wipeTable(displayTable, frameCount, refCount);

    int pageFaults;

    switch (algo)
    {
        case 'F': case 'f':
            pageFaults = FIFO(frameCount, refs, refCount, displayTable);
            break;
        case 'O': case 'o':
            pageFaults = OPT(frameCount, refs, refCount, displayTable);
            break;
        case 'L': case 'l':
            pageFaults = LRU(frameCount, refs, refCount, displayTable);
            break;
    }

    printTable(refs, refCount, frameCount, displayTable, pageFaults);
    
}