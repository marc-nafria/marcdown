#include <iostream>
#include "colors.h"

using namespace std;

struct state {
    bool N1 = false;
    bool N2 = false;

    bool C = false;
    
    bool CC = false;

    bool T = false;

    bool IC = false;

    bool backslash = false;
};

class Block {
    public:
        Block (const string &inputLine, int width);
        void write() const;
        int getHeight() const;
    private:
        int height;
        void inline_format(string &line);
        string check_inline_format (char &c);
        string content;
        state blockState;
};
