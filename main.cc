#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>

#include "Block.h"

using namespace std;

string filename;
int width, height;

vector<vector<Block> > pages;
int current_page = 0;
void getConsoleBufferSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    height = w.ws_row, width = w.ws_col;
}

void printPage(int num_page) {
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
    colorFG(fg), colorBG(bg);
}

int main (int argc, char* argv[]) {
    // decide if filename or default file
    filename = "hola";
    if (argc > 1)
        filename = argv[1];
    
    // get console buffer size
    getConsoleBufferSize();

    // open the file
    fstream file;
    file.open(filename);
    
    // variables needes for reading
    string line;
    int page_count = 0;
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
            ++page_count;
        }

        // add the block to the page
        pages[page_count].push_back(new_block);
    }

    // at the end print the first page
    printPage(current_page);
      
    // now we check for commands
    char ch;
    while (cin >> ch) {
        if (ch == 'n' and current_page < page_count)
            ++current_page;
        else if (ch == 'p' and current_page > 0)
            --current_page;
        else if (ch == 'q')
            exit(0);
        
        // at the end of a command we print the current page again
        printPage(current_page);
    }
} 
