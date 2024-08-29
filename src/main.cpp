#include <iostream>
#include "TerminalEditor.cpp"
void Focus(TerminalEditor &editor) {
    std::cout << "Testing Key press\n";
}
int main() {
    TerminalEditor editor;
    // editor.terminal_bg_color = 0x0000ff;
    editor.run();

    Focus(editor);

    // wait for user input before exiting
    std::cin.get();
    return 0;
}