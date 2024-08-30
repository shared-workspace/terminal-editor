
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

void SwitchToAlternateScreenBuffer() {
    std::cout << "\033[?1049h\033[H";
    atexit([]() {
        std::cout << "\033[?1049l";
    });
}

void DisableCanonicalModeAndEcho() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    atexit([]() {
        termios term;
        tcgetattr(STDIN_FILENO, &term);
        term.c_lflag |= ICANON | ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    });
}

void InitializeEditor() {
    SwitchToAlternateScreenBuffer();
    DisableCanonicalModeAndEcho();
}