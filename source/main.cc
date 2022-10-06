#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <cstring>

#include "headers/Block.h"
#include "headers/consoleInfo.h"

#define defaultFilePath "Examples/help"

using namespace std;

// variables used in a program


void printPage(const vector<vector<Block> > &pages, const int &num_page,
 const string &filename, const int &width, const int &height) {
    system("clear");
    
    colorFG(bg), colorBG(fg);
    cout << " Marcdown: " << filename;
    for (int i = filename.length() + 11; i < width; ++i)
        cout << " ";
    cout << endl << endl;
    
    int current_row = 2;
    for (int i = 0; i < pages[num_page].size(); ++i) {
        pages[num_page][i].write(); // write block
        current_row += pages[num_page][i].getHeight(); // increment current_row by block height
    }
    
    // go to line height - 2
    for (;current_row < height - 2; ++current_row)
        cout << endl;
    
    // bottom status line
    colorFG(bg), colorBG(fg);
    cout << endl <<  " Page " << num_page + 1 << " of " << pages.size() << " ";
    cout << "n(ext), p(revious), q(uit): ";
    colorFG(fg), colorBG(bg);
}

vector<vector<Block> > readFile(string filename, vector<vector<Block> > &pages, int &total_pages,
 int width, int height,
 options outputOptions) {
    fstream file;
    file.open(filename);
    // if file not open return mk block saying something happened

    // variables needes for reading
    string line;
    total_pages = 0;
    int row_count = 0;
    
    // we create a page and start reading
    pages.push_back(vector<Block>());
    while(getline(file, line)) {
        // new block for the line we read
        Block new_block = Block(line, width, outputOptions);
        
        // increment row_count by the height of the block
        row_count += new_block.getHeight();

        // check if the block fits in the page
        if (row_count > height - 4) {
            // doesn't fit, we create a new page
            row_count = new_block.getHeight();
            pages.push_back(vector<Block>());
            ++total_pages;
        }

        // add the block to the page
        pages[total_pages].push_back(new_block);
    }
    return pages;
}
void printUsage() {
    cout << "Usage: ./marcdown <path_to_file> [options]" << endl;
    cout << "Options" << endl;
    cout << "   -bC (blodColor): prints the bold format as a color" << endl;
    exit(0);
}

int main (int argc, char* argv[]) {
     // VARIABLES needed
    string filename;                // PATH of the FILE
    int width, height;              // DIMENSIONS of the CONSOLE in characters
    vector<vector<Block> > pages;   // processed content of the file
    options outputOptions;
    int current_page = 0;           // current page of the viewer
    int total_pages = 0;            // total number of pages

    // VARIABLES for OPTIONS
    bool boldAsColor = false;

    // decide if FILENAME or USAGE
    if (argc <= 1 or !strcmp(argv[1], "-h"))
        printUsage();
    else filename = argv[1];
    
    // read the OPTIONS
    for (int i = 2; i < argc; ++i) {
        if (!strcmp(argv[i], "-bC"))
            outputOptions.boldAsColor = true;
    }

    // get CONSOLE BUFFER SIZE
    getConsoleBufferSize(width, height);
    
    // READ and PROCESS the file
    readFile(filename, pages, total_pages,
     width, height,
     outputOptions);

    // at the end PRINT the FIRST PAGE
    printPage(pages, current_page, filename, width, height);
      
    // now we check for COMMANDS
    string ins;
    while (cin >> ins) {
        // NEXT PAGE
        if (ins[0] == 'n' and current_page < total_pages)
            ++current_page;
        // PREVIOUS PAGE
        else if (ins[0] == 'p' and current_page > 0)
            --current_page;
        // QUIT PROGRAM
        else if (ins[0] == 'q')
            exit(0);
        
        // at the end of a command we PRINT the CURRENT PAGE again
        printPage(pages, current_page, filename, width, height);
    }
} 
