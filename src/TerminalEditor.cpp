#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

class TerminalEditor {
    public:
        int terminal_bg_color = -1;
        void run();
    private:
        
        void colorBG();
        void createWindow();
        void displayKeyPress(const std::string& keyPres);
};


void TerminalEditor::run() {
    createWindow();
    colorBG();
    displayKeyPress("Shift+Ctrl+Alt+A");
}

void TerminalEditor::colorBG() {
    if (terminal_bg_color == -1) return;
    // Extract RGB components from the hex color
    int r = (terminal_bg_color >> 16) & 0xFF;
    int g = (terminal_bg_color >> 8) & 0xFF;
    int b = terminal_bg_color & 0xFF;

    // Set the terminal background color using ANSI escape codes
    std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";

    // Clear the screen to apply the background color to the entire terminal
    std::cout << "\033[2J\033[H";
}

void TerminalEditor::createWindow() {
    // Save the current terminal state
    std::cout << "\033[?1049h\033[H";

    // Your code to create and manage the terminal window goes here

    // Register a function to restore the terminal state on exit
    atexit([]() {
        // Restore the terminal state
        std::cout << "\033[?1049l";
    });
}

void TerminalEditor::displayKeyPress(const std::string& keyPress) {
    // Get the terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Move cursor to bottom right corner and display the key press
    std::cout << "\033[" << w.ws_row << ";" << w.ws_col - keyPress.length() + 1 << "H" << keyPress << std::flush;
}