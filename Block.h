#include <iostream>
#include "colors.h"
using namespace std;

class Block {
    public:
        Block (const string &inputLine, int width);
        void write();
        int getHeight();
    private:
        int height;
        string content;
};
