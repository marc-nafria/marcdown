#include <iostream>
#include <string.h>
#include "headers/Block.h"
using namespace std;

string comment (string line, int w, int &height);

Block::Block(const string &inputLine, int width) {
    string line = inputLine;
    int len = 0;

    // detect header
    if (inputLine[0] == '#') {
        content = outColorFG(blue) + outBold();
        line = line.substr(1, line.length() - 1);
        while (line[0] == '#') {
            line = line.substr(1, line.length() - 1);
            content += "  ";
            len += 2;
        }
        line = line.substr(1, line.length() - 1);
        len += line.length();
        content += line;
        height = len / width + 1;
    }
    // detect comment
    else if (inputLine[0] == '>') {
        line = line.substr(2, line.length() - 2);
        content = comment(line, width, height);
        // line = line.substr(2, line.length() - 2);
        // content = outColorFG(orange) + line;
        // height = line.length() / width + 1;
    }
    // detect list
    else if (inputLine[0] == '+') {
        line = line.substr(1, line.length() - 1);
        content = "    ";
        len += 4;
        while (line[0] == '+') {
            line = line.substr(1, line.length() - 1);
            content += "    ";
            len += 2;
        }
        content += "·" + line;
        len += line.length() + 1;
        height = len / width + 1;
    }
    
    // detect separator
    else if (inputLine == "---") {
        height = 1;
        content = " ";
        for (int i = 0; i < width - 2; ++i)
            content += "-";
        content += " ";
    }
    // detect paragraf
    else {
        content = line;
        height = line.length() / width + 1;
    }
}

void Block::write() {
    resetOutputFormat();
    cout << content;
    resetOutputFormat();
    cout << endl;
}

int Block::getHeight() {
    return height;
}

// pre: line contents the string trimmed and w represent the buffer size
// post: print the comment to output
string comment (string line, int w, int &height) {
    string result = "";
    // recorrem els caracters de la linea i del buffer
    int len = line.length();
    int i = 0; // posicio de linea
    int j = 0; // posicio de buffer
               //
    while (i < len) {
        if (j == 0) {
            result += "    ";
            result += outColorBG(red);
            result += " ";
            result += outColorBG(bg);
            result += " ";
            j = 6;
            result += outColorFG(orange);
        }
        else if (j == w) {
            j = 0;
            result += outColorBG(bg);
            result += "\n";
        }
        else {
            result += line[i];
            ++j;
            ++i;
        }   
    }
    height = line.length() / (w - 8) + 1;
    return result;
}

