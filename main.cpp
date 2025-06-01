#include "TextEditor.h"


int main() {
    TextEditor text_editor(256, 10);

    while (true) {
        int command = text_editor.command_input();
        system("clear"); // Clearing console
        int row, col, number;

        switch (command) {
            case 1:
                printf("Enter text to append: ");
                text_editor.add_text(text_editor.console_input());
                break;
            case 2:
                text_editor.new_line();
                printf("New line is started\n");
                break;
            case 3:
                printf("Enter the file name for saving: ");
                if (text_editor.save_to_file(text_editor.console_input())) printf("File name cannot be empty.\n");
                else printf("Text has been saved successfully\n");
                break;
            case 4:
                printf("Enter the file name for loading: ");
                if (text_editor.load_from_file(text_editor.console_input())) printf("Error opening file\n");
                else printf("Text has been loaded successfully\n");
                break;
            case 5: text_editor.print_text(); break;
            case 6:
                printf("Choose line and index: ");
                if (sscanf(text_editor.console_input(), "%d %d", &row, &col) != 2  || row < 0 || col < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Enter text to insert: ");
                text_editor.set_cursor(row, col);
                text_editor.insert_text(text_editor.console_input(), false);
                break;
            case 7:
                printf("Enter text to search: ");
                std::vector<std::pair<int, int>> matches;
                matches = text_editor.substring_search(Text(text_editor.console_input()));
                printf("Text is present in this positions: ");
                for (const auto& p : matches) {
                    printf("%d %d; ", p.first, p.second);
                }
                printf("\nTotal matches: %lu\n", matches.size());
                break;
            case 8:
                printf("Choose line, index and number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d %d %d", &row, &col, &number) != 3 || row < 0 || col < 0 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                text_editor.set_cursor(row, col);
                if (text_editor.delete_text(number)) printf("Nothing to delete.\n");
                break;
            case 11:
                printf("Choose line and index and number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d %d %d", &row, &col, &number) != 3 || row < 0 || col < 0 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                text_editor.set_cursor(row, col);
                if (text_editor.cut(number)) printf("Nothing to cut.\n");
                else printf("Cut.\n");
                break;
            case 12:
                printf("Choose line and index: ");
                if (sscanf(text_editor.console_input(), "%d %d", &row, &col) != 2  || row < 0 || col < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                text_editor.set_cursor(row, col);
                text_editor.paste();
                break;
            case 13:
                printf("Choose line and index and number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d %d %d", &row, &col, &number) != 3 || row < 0 || col < 0 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                text_editor.set_cursor(row, col);
                if (text_editor.copy(number)) printf("Nothing to copy.\n");
                else printf("Copied.\n");
                break;
            case 14: printf("Choose line and index: ");
                if (sscanf(text_editor.console_input(), "%d %d", &row, &col) != 2  || row < 0 || col < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                printf("Enter text to insert: ");
                text_editor.set_cursor(row, col);
                text_editor.insert_text(text_editor.console_input(), true);
                break;
            case -1: printf("Exiting.."); return 0;
            case -2: TextEditor::print_help(); break;
            default: printf("Command is not implemented.\n"); break;
        }
    }
}