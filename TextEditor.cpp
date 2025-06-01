#include "TextEditor.h"
#include <cstdio>
#include <cstring>

TextEditor::TextEditor(const uint32_t INITIAL_BUFFER_SIZE, const uint32_t INITIAL_ROW_COUNT) {
    LastLine = 0;
    BufferSize = INITIAL_BUFFER_SIZE;
    RowCount = INITIAL_ROW_COUNT;
    text = static_cast<char **>(calloc(RowCount, sizeof(char *)));
    text[LastLine] = static_cast<char *>(calloc(1, sizeof(char)));
    Cursor.first = Cursor.second = 0;
    Text Clipboard;
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
Text TextEditor::console_input() const { // Text input
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
    return Text(buffer);
}
int TextEditor::command_input() const {
    printf("Choose the command:\n");
    const int cmd = std::atoi(console_input());
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
void TextEditor::set_cursor(const int row, const int col) {
    Cursor.first = row;
    Cursor.second = col;
}

void TextEditor::add_text(const Text& temp) const {
    const uint32_t new_len = strlen(text[LastLine]) + strlen(temp) + 1;
    text[LastLine] = static_cast<char *>(realloc(text[LastLine], new_len * sizeof(char))); // reallocating memory for new line length
    strcat(text[LastLine], temp);
}
void TextEditor::new_line() {
    if (LastLine >= RowCount) {
        RowCount *= 2; // doubling number of rows
        text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
    }
    LastLine++;
    text[LastLine] = static_cast<char *>(calloc(1, sizeof(char)));
}
int TextEditor::save_to_file(const Text& file_name) const {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) return 1;
    for (int i = 0; i <= LastLine; i++) fprintf(file, (i != LastLine) ? "%s\n" : "%s", text[i]);
    fclose(file);
    return 0;
}
int TextEditor::load_from_file(const Text& file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) return 1;
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
    return 0;
}
void TextEditor::print_text() const {
    for (int i = 0; i <= LastLine; i++) printf("%s\n", text[i]);
}
void TextEditor::insert_text(const Text& temp, const bool replacement) {
    const int row = Cursor.first; const int col = Cursor.second;
    if (row > LastLine) {
        if (row >= RowCount) {
            RowCount = row + 1; // changing the number of lines
            text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
        }
        for (uint32_t i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
            text[i] = static_cast<char *>(calloc(1, sizeof(char)));
        }
        text[row] = static_cast<char *>(calloc(col + strlen(temp) + 1, sizeof(char)));
        for (int i = 0; i < col; i++) text[row][i] = ' '; // fitting spaces
        strcat(text[row], temp);
        LastLine = row;
    }
    else {
        uint32_t new_len = (col > strlen(text[row])) ? col + strlen(temp) + 1: strlen(text[row]) + strlen(temp) + 1;
        text[row] = static_cast<char *>(realloc(text[row], new_len)); // reallocating for new len
        if (!replacement)for (uint32_t i = strlen(text[row]); i > col; i--) text[row][i-1+strlen(temp)] = text[row][i-1]; // moving characters after index to the right
        for (uint32_t i = strlen(text[row]); i < col; i++) text[row][i] = ' '; // if index is > than len of the line we fit empty space with spaces
        for (int i = 0; i < strlen(temp); i++) text[row][col+i] = temp[i];
    }
}
std::vector<std::pair<int, int>> TextEditor::substring_search(const Text& temp) const {
    int row_index = 0; int col_index = 0;
    int match_count = 0;
    std::vector<std::pair<int, int>> matches;

    for (int row = 0; row <= LastLine; row++) {
        for (int index = 0; index < strlen(text[row]); index++) {
            if (text[row][index] == temp[match_count]) {
                if (match_count == 0) { // if it's the first match we set the index of the start
                    row_index = row;
                    col_index = index;
                }
                match_count++;
                if (match_count == strlen(temp)) { // if the match_count == len of substring then we found a match
                    matches.emplace_back(row_index, col_index);
                    row_index = col_index = match_count = 0;
                }
            }
            else {
                index = index - match_count; // going back to the next index after the start of match
                match_count = 0;
            }
        }
    }
    return matches;
}
int TextEditor::delete_text(const int number) const {
    const int row = Cursor.first; const int col = Cursor.second;
    const uint8_t old_len = strlen(text[row]);
    if (row > LastLine || col > old_len) return 1;

    for (size_t i = col; i < old_len; i++) text[row][i] = (i+number < old_len) ?  text[row][i+number] : '\0';
    const uint8_t new_len = (col > old_len - number) ? col: old_len - number;
    text[row] = static_cast<char *>(realloc(text[row], new_len));
    return 0;
}
int TextEditor::copy(int number) {
    const int row = Cursor.first; const int col = Cursor.second;
    if (row > LastLine || col >= strlen(text[row])) return 1;
    char* temp = static_cast<char*>(calloc(number + 1, sizeof(char)));
    for (int i = 0; i < number & i < strlen(text[row]) - col; i++) temp[i] = text[row][col+i];
    Clipboard.text = temp;
    return 0;
}
int TextEditor::cut(int number) {
    if (copy(number)) return 1;
    return delete_text(number);
}
void TextEditor::paste() {
    insert_text(Clipboard, false);
}