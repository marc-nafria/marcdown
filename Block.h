#include <iostream>
using namespace std;
#include "colors.h"

class Block {
    public:
        Block (const string &inputLine, int width);
        void write();
        int getHeight();
    private:
        int height;
        string content;
};
