#include "TextEditor.h"


int main() {
    TextEditor text_editor(256, 10);

    while (true) {
        int command = text_editor.command_input();
        system("clear"); // Clearing console
        int row, col, number;

        switch (command) {
            case -2: TextEditor::print_help(); break;
            case -1: printf("Exiting.."); return 0;
            case 1:
                text_editor.print_with_cursor("Enter text to append: ");
                text_editor.add_text(text_editor.console_input());
                break;
            case 2:
                text_editor.new_line();
                text_editor.print_with_cursor("New line is started\n");
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
                text_editor.print_with_cursor("Enter text to insert: ");
                text_editor.insert_text(text_editor.console_input(), false);
                break;
            case 7: {
                printf("Enter text to search: ");
                std::vector<std::pair<int, int> > matches = text_editor.substring_search(String(text_editor.console_input()));
                printf("Text is present in this positions: ");
                for (const auto& p : matches) {
                    printf("%d %d; ", p.first, p.second);
                }
                printf("\nTotal matches: %lu\n", matches.size());
                break;
            }
            case 8:
                text_editor.print_with_cursor("Choose number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d", &number) != 1 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                if (text_editor.delete_text(number)) printf("Nothing to delete.\n");
                else text_editor.print_with_cursor("Text has been deleted.\n");
                break;
            case 9:
                if (text_editor.undo()) printf("Nothing to undo.\n");
                else text_editor.print_with_cursor("Undid.\n");
                break;
            case 10:
                if (text_editor.redo()) printf("Nothing to redo.\n");
                else text_editor.print_with_cursor("Redid.\n");
                break;
            case 11:
                text_editor.print_with_cursor("Choose number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d", &number) != 1 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                if (text_editor.cut(number)) printf("Nothing to cut.\n");
                else printf("Cut.\n");
                break;
            case 12:
                text_editor.paste();
                text_editor.print_with_cursor("Text pasted.\n");
                break;
            case 13:
                text_editor.print_with_cursor("Choose number of symbols: ");
                if (sscanf(text_editor.console_input(), "%d", &number) != 1 || number < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                if (text_editor.copy(number)) printf("Nothing to copy.\n");
                else printf("Copied.\n");
                break;
            case 14:
                text_editor.print_with_cursor("Enter text to insert: ");
                text_editor.insert_text(text_editor.console_input(), true);
                break;
            case 15: {
                text_editor.print_with_cursor("Enter text for checklist item: ");
                const String item = text_editor.console_input();
                printf("Checked? (Y/N): ");
                const String response = text_editor.console_input();
                const bool is_checked = response.len() == 1 & response[0] == 'Y';
                text_editor.add_checkpoint(item, is_checked);
                text_editor.print_with_cursor("Done.\n");
                break;
            }
            case 16:
                switch (text_editor.check_uncheck()) {
                    case 1: text_editor.print_with_cursor("Not a checkpoint.\n"); break;
                    case 2: text_editor.print_with_cursor("No such line.\n"); break;
                    default: text_editor.print_with_cursor("Done.\n"); break;;
                }
                break;
            case 17: {
                text_editor.print_with_cursor("Name: ");
                const String name = text_editor.console_input();
                printf("Surname: ");
                const String surname = text_editor.console_input();
                printf("Email: ");
                const String email = text_editor.console_input();
                text_editor.add_contact(name, surname, email);
                text_editor.print_with_cursor("Done.\n");
                break;
            }
            case 18:
                text_editor.print_with_cursor(text_editor.empty_line() ? "No such line.\n" : "Done.\n");
                break;
            case 33:
                text_editor.print_with_cursor("Choose line and index: ");
                if (sscanf(text_editor.console_input(), "%d %d", &row, &col) != 2  || row < 0 || col < 0) {
                    printf("Invalid input.\n");
                    break;
                }
                text_editor.set_cursor(row, col);
                printf("Cursor is set to (%d, %d)\n", row, col);
                break;
            default: printf("Command is not implemented.\n"); break;
        }
    }
}