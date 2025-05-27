#include "TextEditor.h"
#include <cstdio>


int main() {
    TextEditor text_editor(256, 10);

    while (true) {
        int command = text_editor.command_input();
        system("clear"); // Clearing console

        switch (command) {
            case 1: text_editor.add_text(); break;
            case 2: text_editor.new_line(); break;
            case 3: text_editor.save_to_file(); break;
            case 4: text_editor.load_from_file(); break;
            case 5: text_editor.print_text(); break;
            case 6: text_editor.insert_text(); break;
            case 7: text_editor.substring_search(); break;
            case -1: printf("Exiting.."); return 0;
            case -2: TextEditor::print_help(); break;
            default: printf("Command is not implemented.\n"); break;
        }
    }
}