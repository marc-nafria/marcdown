#include <iostream>
#include "colors.h"

using namespace std;

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
