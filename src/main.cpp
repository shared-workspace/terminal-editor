#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <csignal>

void SwitchToAlternateScreenBuffer() {
    std::cout << "\033[?1049h\033[H";
    atexit([]() {
        std::cout << "\033[?1049l";
    });
}

void IgnoreSignal(int signum) {
    // Do nothing, just ignore the signal
}

void SetupSignalAndTerminalHandling() {
    // Ignore SIGINT signal (Ctrl+C)
    signal(SIGINT, IgnoreSignal); 

    // Handle SIGTSTP signal (Ctrl+Z)
    struct sigaction sa;
    sa.sa_handler = IgnoreSignal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTSTP, &sa, nullptr);

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

void WaitForEscKey() {
    char ch;
    while (true) {
        ch = getchar();
        if (ch == 27) { // ASCII value of ESC key
            break;
        }
    }
}

int main() {
    SwitchToAlternateScreenBuffer();
    SetupSignalAndTerminalHandling();
    WaitForEscKey();
    return 0;
}