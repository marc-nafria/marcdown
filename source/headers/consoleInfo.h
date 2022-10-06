#include <sys/ioctl.h>

void getConsoleBufferSize(int &width, int &height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    height = w.ws_row, width = w.ws_col;
}