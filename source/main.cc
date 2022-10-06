#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>

#include "headers/Block.h"
#include "headers/consoleInfo.h"

using namespace std;

// variables used in a program


void printPage(const vector<vector<Block> > &pages, const int &num_page, const string &filename, const int &width, const int &height) {
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

vector<vector<Block> > readFile(string filename, vector<vector<Block> > &pages, int &total_pages, int width, int height) {
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
        Block new_block = Block(line, width);
        
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
    exit(0);
}

int main (int argc, char* argv[]) {
    // decide if filename or default file
    if (argc <= 1)
        printUsage();
    
    // variables needed
    string filename;                // path of the file
    int width, height;              // dimensions of the console in characters
    vector<vector<Block> > pages;   // processed content of the file
    int current_page = 0;           // current page of the viewer
    int total_pages = 0;            // total number of pages

    // get filename from input
    filename = argv[1];
    
    // get console buffer size
    getConsoleBufferSize(width, height);
    
    // READ AND PROCESS THE FILE
    readFile(filename, pages, total_pages, width, height);

    // at the end print the first page
    printPage(pages, current_page, filename, width, height);
      
    // now we check for commands
    char ch;
    while (cin >> ch) {
        if (ch == 'n' and current_page < total_pages)
            ++current_page;
        else if (ch == 'p' and current_page > 0)
            --current_page;
        else if (ch == 'q')
            exit(0);
        
        // at the end of a command we print the current page again
        printPage(pages, current_page, filename, width, height);
    }
} 
