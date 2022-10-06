#include <iostream>
#include <string.h>
#include "headers/Block.h"
using namespace std;

string comment (string line, int w, int &height);

Block::Block(const string &inputLine, int width, const options &outputOptions) {
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
        inline_format(content, outputOptions);
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
        inline_format(content, outputOptions);
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
        inline_format(line, outputOptions);
        height = line.length() / width + 1;
        content = line;
    }
}

void Block::write() const {
    cout << content;
    resetOutputFormat();
    cout << endl;
}

int Block::getHeight() const {
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

void Block::inline_format(string &line, const options &outputOptions) {
    string result = "";
    for (int i = 0; i < line.length(); ++i) {
        result += check_inline_format(line[i], outputOptions);
    }
    line = result;
}

string Block::check_inline_format (char &c, const options &outputOptions) {
    // mirem si s'ha de analitzar o no
    if (blockState.backslash) {
        blockState.backslash = false;
        return string(1, c);
    }

    // pel que fa a caracter especial 
    if (c == '\\') {
        blockState.backslash = true;
        return "";
    }

    // pel que fa a la negreta
    if (c == '*') {
        if (!blockState.N1) blockState.N1 = true;
        else if (!blockState.N2) {
            blockState.N1 = false;
            blockState.N2 = true;
            if (outputOptions.boldAsColor)
                return outColorFG(orange);
            return outBold();
        }
        else {
            blockState.N1 = false;
            blockState.N2 = false;
            return outNormal();
        }
        return "";
    }
    else blockState.N1 = false;

    // pel que fa a codi
    if (c == '`') {
        blockState.IC = !blockState.IC;
        if (blockState.IC) return outCode();
        return " " + outColorBG(bg);
    }

    return string(1, c);
}
