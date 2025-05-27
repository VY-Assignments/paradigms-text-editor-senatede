#include "TextEditor.h"
#include <cstdio>
#include <cstring>

TextEditor::TextEditor(const uint32_t INITIAL_BUFFER_SIZE, const uint32_t INITIAL_ROW_COUNT) {
    LastLine = 0;
    BufferSize = INITIAL_BUFFER_SIZE;
    RowCount = INITIAL_ROW_COUNT;
    text = static_cast<char **>(calloc(RowCount, sizeof(char *)));
    text[LastLine] = static_cast<char *>(calloc(1, sizeof(char)));
}
TextEditor::~TextEditor() {
    cleanup();
}

void TextEditor::cleanup() const {
    if (this->text != NULL) {
        for (uint32_t i = 0; i < RowCount; ++i)
            free(text[i]);
        free(text);
    }
}
char* TextEditor::console_input() const { // Text input
    uint32_t size = BufferSize;
    uint32_t len = 0;
    char* buffer = static_cast<char *>(calloc(size, sizeof(char)));
    char c;
    while ((c = static_cast<char>(getchar())) != '\n') { // getting each character
        buffer[len++] = c;
        if (len == size) {
            size *= 2; // doubling size of bugger
            buffer = static_cast<char *>(realloc(buffer, size));
        }
    }
    buffer[len] = '\0';
    return buffer;
}
int TextEditor::command_input() const {
    printf("Choose the command:\n");
    char* command = console_input();
    const int cmd = std::atoi(command);
    free(command);
    return cmd;
}
void TextEditor::print_help() {
    printf("Welcome to the Simple Text Editor!\nAvailable commands:\n"
           "  1 → Append text symbols to the end\n"
           "  2 → Start the new line\n"
           "  3 → Save to file\n"
           "  4 → Load from file\n"
           "  5 → Print the current text to console\n"
           "  6 → Insert the text by line and symbol index\n"
           "  7 → Search substring\n"
           " -1 → Exit\n"
           " -2 → Help\n");
}
void TextEditor::add_text() const {
    printf("Enter text to append: ");
    char* str = console_input();
    if (text[LastLine] != NULL) {
        uint32_t new_len = strlen(text[LastLine]) + strlen(str) + 1;
        text[LastLine] = static_cast<char *>(realloc(text[LastLine], new_len * sizeof(char))); // reallocating memory for new line length
    }
    strcat(text[LastLine], str);
    free(str);
}
void TextEditor::new_line() {
    if (LastLine >= RowCount) {
        RowCount *= 2; // doubling number of rows
        text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
    }
    LastLine++;
    text[LastLine] = static_cast<char *>(calloc(1, sizeof(char)));
    printf("New line is started\n");
}
void TextEditor::save_to_file() const {
    printf("Enter the file name for saving: ");
    char *file_name = console_input();
    FILE* file = fopen(file_name, "w");
    if (file != NULL) {
        for (int i = 0; i <= LastLine; i++) fprintf(file, (i != LastLine) ? "%s\n" : "%s", text[i]);
        fclose(file);
        printf("Text has been saved successfully\n");
        free(file_name);
    }
    else {
        printf("File name cannot be empty.\n");
    }
}
void TextEditor::load_from_file() {
    printf("Enter the file name for loading: ");
    char* file_name = console_input();
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file\n");
    }
    else {
        cleanup();
        LastLine = 0;
        RowCount = 10;
        text = static_cast<char **>(calloc(RowCount, sizeof(char *)));
        char c;
        uint32_t LineLength = 0; uint32_t size = BufferSize;
        char* buffer = static_cast<char *>(calloc(size, sizeof(char)));

        while ((c = fgetc(file)) != EOF) {
            if (c != '\n') {
                buffer[LineLength++] = c;
                if (LineLength == size) {
                    size *= 2; // doubling size of bugger
                    buffer = static_cast<char *>(realloc(buffer, size));
                }
            }
            else {
                buffer = static_cast<char *>(realloc(buffer, LineLength));
                text[LastLine] = strdup(buffer);

                free(buffer), buffer = static_cast<char *>(calloc(size, sizeof(char)));

                size = BufferSize; LineLength = 0;
                if (LastLine >= RowCount-1) {
                    RowCount *= 2; // doubling the number of lines
                    text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
                }
                LastLine++;
            }
        }
        text[LastLine] = strdup(buffer);

        free(buffer);
        printf("Text has been loaded successfully\n");
    }
    free(file_name);
}
void TextEditor::print_text() const {
    for (int i = 0; i <= LastLine; i++) printf("%s\n", text[i]);
}
void TextEditor::insert_text() {
    int row, col;
    printf("Choose line and index: ");
    if (scanf("%d %d", &row, &col) != 2 || row < 0 || col < 0) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); // clearing console buffer
    printf("Enter text to insert: ");
    char* str = console_input();
    if (row > LastLine) {
        if (row >= RowCount) {
            RowCount = row + 1; // changing the number of lines
            text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
        }
        for (uint32_t i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
            text[i] = static_cast<char *>(calloc(1, sizeof(char)));
        }
        text[row] = static_cast<char *>(calloc(col + strlen(str) + 1, sizeof(char)));
        for (int i = 0; i < col; i++) text[row][i] = ' '; // fitting spaces
        strcat(text[row], str);
        LastLine = row;
    }
    else {
        uint32_t new_len = (col > strlen(text[row])) ? col + strlen(str) + 1: strlen(text[row]) + strlen(str) + 1;
        text[row] = static_cast<char *>(realloc(text[row], new_len)); // reallocating for new len
        for (uint32_t i = strlen(text[row]); i > col; i--) text[row][i-1+strlen(str)] = text[row][i-1]; // moving characters after index to the right
        for (uint32_t i = strlen(text[row]); i < col; i++) text[row][i] = ' '; // if index is > than len of the line we fit empty space with spaces
        for (int i = 0; i < strlen(str); i++) text[row][col+i] = str[i];
    }
    free(str);
}
void TextEditor::substring_search() const {
    printf("Enter text to search: ");
    char* str = console_input();
    int row_index = 0; int col_index = 0;
    int match_count = 0;
    int matches = 0;
    printf("Text is present in this positions: ");
    for (int row = 0; row <= LastLine; row++) {
        for (int index = 0; index < strlen(text[row]); index++) {
            if (text[row][index] == str[match_count]) {
                if (match_count == 0) { // if it's the first match we set the index of the start
                    row_index = row;
                    col_index = index;
                }
                match_count++;
                if (match_count == strlen(str)) { // if the match_count == len of substring then we found a match
                    printf("%d %d; ", row_index, col_index);
                    row_index = col_index = match_count = 0;
                    matches++;
                }
            }
            else {
                index = index - match_count; // going back to the next index after the start of match
                match_count = 0;
            }
        }
    }
    printf("\nTotal matches: %d\n", matches);
    free(str);
}