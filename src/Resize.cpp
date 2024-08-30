#include <sys/ioctl.h>
#include <iostream>
#include <vector>
#include <functional>
#include <csignal>
#include <unistd.h>

class Resize {
    private:
        static std::vector<std::function<void(int, int)>> listeners;
        static bool initialized;

        static void handleResize(int signal) {
            if (signal == SIGWINCH) {
                struct winsize w;
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
                int width = w.ws_col;
                int height = w.ws_row;

                // Loop through all functions that need to be called on resize
                for (const auto& func : listeners) {
                    func(width, height);
                }
            }
        }

    public:
        Resize() {
            // Initialize the signal handler
            if (!initialized) {
                initialized = true;
                // Set up the signal handler for SIGWINCH
                std::signal(SIGWINCH, Resize::handleResize);
            }
        }

        // Method to add a listener function
        void setListener(std::function<void(int, int)> func) {
            listeners.push_back(func);
        }
};

// Initialize the static member
std::vector<std::function<void(int, int)>> Resize::listeners;

// Initialize the static member
bool Resize::initialized = false;