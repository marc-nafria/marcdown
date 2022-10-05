#include <iostream>
using namespace std;

enum colors{bg=0, fg, blue,  red, orange};

// ouput---------------------
void colorFG(int color);

void colorBG(int color);

std::string outColorFG (int color);
std::string outColorBG (int color);

void bold();
void normal();

std::string outBold();

std::string outNormal();

void resetOutputFormat();

std::string outUnderline();
