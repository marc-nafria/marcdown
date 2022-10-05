#include "headers/colors.h"

// ouput---------------------
void colorFG(int color) {
    if (color == bg)
        std::cout << "\033[38;2;46;52;64m";
    else if (color == fg)
        std::cout << "\033[38;2;216;222;233m";
    else if (color == blue)
        std::cout << "\033[38;2;129;161;193m";
    else if (color == red)
        std::cout << "\033[38;2;191;97;106m";
    else if (color == orange)
        std::cout << "\033[38;2;208;125;112m";
}

void colorBG(int color) {
    if (color == bg)
        std::cout << "\033[49m";
    else if (color == fg)
        std::cout << "\033[48;2;216;222;233m";
    else if (color == blue)
        std::cout << "\033[48;2;129;161;193m";
    else if (color == red)
        std::cout << "\033[48;2;191;97;106m";
    else if (color == orange)
        std::cout << "\033[48;2;208;125;112m";
}

std::string outColorFG (int color) {
    if (color == bg)
        return "\033[30m";
    else if (color == fg)
        return "\033[37m";
    else if (color == blue)
        return "\033[34m";
    else if (color == red)
        return "\033[31m";
    else if (color == orange)
        return "\033[91m";
    return "";
}
std::string outColorBG (int color) {
    if (color == bg)
        return "\033[49m";
    else if (color == fg)
        return "\033[47m";
    else if (color == blue)
        return "\033[44m";
    else if (color == red)
        return "\033[41m";
    else if (color == orange)
        return "\033[101m";
    return "";
}

void bold() {
    cout << "\033[1m";
}
void normal() {
    cout << "\033[22m";
}

std::string outBold() {
    return "\033[1m";
}

std::string outNormal() {
    return "\033[22m";
}

std::string outCode() {
    return "\033[100m";
}

void resetOutputFormat() {
    colorFG(fg), colorBG(bg);
    normal();
}

std::string outUnderline() {
    return "";
}
