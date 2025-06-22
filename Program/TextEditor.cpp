#include "TextEditor.h"
#include <cstdio>
#include <cstring>
#include "LineTypes/TextLine.cpp"
#include "LineTypes/EmptyLine.cpp"
#include "LineTypes/ChecklistLine.cpp"
#include "LineTypes/ContactLine.cpp"

TextEditor::TextEditor(const uint32_t INITIAL_BUFFER_SIZE, const uint32_t INITIAL_ROW_COUNT) {
    LastLine = 0;
    BufferSize = INITIAL_BUFFER_SIZE;
    RowCount = INITIAL_ROW_COUNT;

    lines = static_cast<Line **>(calloc(RowCount, sizeof(Line*)));
    lines[LastLine] = new EmptyLine();

    Cursor.first = Cursor.second = 0;
    String Clipboard;
    TextStateStack UndoStack;
    TextStateStack RedoStack;
}
TextEditor::~TextEditor() {
    cleanup();
}

void TextEditor::cleanup() const {
    for (uint32_t i = 0; i < RowCount; ++i)
        delete lines[i];
}
String TextEditor::console_input() const { // Text input
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
    return String(buffer);
}
int TextEditor::command_input() const {
    printf("Choose the command:\n");
    const int cmd = std::atoi(console_input());
    return cmd;
}
void TextEditor::print_help() {
    printf("Welcome to the Simple Text Editor!\nAvailable commands:\n"
           " -2 → Help\n"
           " -1 → Exit\n"
           " 33 → Set cursor\n"
           "  1 → Append text symbols to the end\n"
           "  2 → Start the new line\n"
           "  3 → Save to file\n"
           "  4 → Load from file\n"
           "  5 → Print the current text to console\n"
           "  6 → Insert the text by line and symbol index\n"
           "  7 → Search substring\n"
           "  8 → Delete part of text\n"
           "  9 → Undo\n"
           " 10 → Redo\n"
           " 11 → Cut\n"
           " 12 → Paste\n"
           " 13 → Copy\n"
           " 14 → Insert and replace\n"
           " 15 → Add a checkpoint\n"
           " 16 → Check/Uncheck a checkpoint\n"
           " 17 → Add contact information\n"
           " 18 → Empty a whole line\n"
           " 19 → Encrypt\n"
           " 20 → Decrypt\n");
}
void TextEditor::set_cursor(const int row, const int col) {
    Cursor.first = row;
    Cursor.second = col;
}

void TextEditor::print_with_cursor(const char* temp) const {
    printf("[Cur: %d, %d]   %s", Cursor.first, Cursor.second, temp);
}

void TextEditor::add_text(const String& temp) {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    if (dynamic_cast<TextLine*>(lines[LastLine]) == nullptr) lines[LastLine] = new TextLine();
    lines[LastLine]->add_text(temp);
}
void TextEditor::new_line() {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    if (LastLine >= RowCount) {
        RowCount *= 2; // doubling number of rows
        lines = static_cast<Line**>(realloc(lines, RowCount * sizeof(Line *)));
    }
    LastLine++;
    lines[LastLine] = new EmptyLine();
}
int TextEditor::save_to_file(const String& file_name) {
    UndoStack.clear();
    RedoStack.clear();
    // FILE* file = fopen(file_name, "w");
    // if (file == NULL) return 1;
    // for (int i = 0; i <= LastLine; i++) fprintf(file, (i != LastLine) ? "%s\n" : "%s", text[i]);
    // fclose(file);
    return 0;
}
int TextEditor::load_from_file(const String& file_name) {
    UndoStack.clear();
    RedoStack.clear();
    // FILE* file = fopen(file_name, "r");
    // if (file == NULL) return 1;
    // cleanup();
    // LastLine = 0;
    // RowCount = 10;
    // text = static_cast<char **>(calloc(RowCount, sizeof(char *)));
    // char c;
    // uint32_t LineLength = 0; uint32_t size = BufferSize;
    // char* buffer = static_cast<char *>(calloc(size, sizeof(char)));
    //
    // while ((c = fgetc(file)) != EOF) {
    //     if (c != '\n') {
    //         buffer[LineLength++] = c;
    //         if (LineLength == size) {
    //             size *= 2; // doubling size of bugger
    //             buffer = static_cast<char *>(realloc(buffer, size));
    //         }
    //     }
    //     else {
    //         buffer = static_cast<char *>(realloc(buffer, LineLength));
    //         text[LastLine] = strdup(buffer);
    //
    //         free(buffer), buffer = static_cast<char *>(calloc(size, sizeof(char)));
    //
    //         size = BufferSize; LineLength = 0;
    //         if (LastLine >= RowCount-1) {
    //             RowCount *= 2; // doubling the number of lines
    //             text = static_cast<char **>(realloc(text, RowCount * sizeof(char *)));
    //         }
    //         LastLine++;
    //     }
    // }
    // text[LastLine] = strdup(buffer);
    // free(buffer);
    return 0;
}
void TextEditor::print_text() const {
    for (int i = 0; i <= LastLine; i++) lines[i]->print();
}
void TextEditor::insert_text(const String& temp, const bool replacement) {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first; const int col = Cursor.second;

    if (row > LastLine || dynamic_cast<TextLine*>(lines[row]) == nullptr) {
        if (row >= RowCount) {
            RowCount = row + 1; // changing the number of lines
            lines = static_cast<Line**>(realloc(lines, RowCount * sizeof(Line *)));
        }
        for (uint32_t i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
            lines[i] = new EmptyLine();
        }
        const auto text = static_cast<char *>(calloc(col + strlen(temp) + 1, sizeof(char)));
        for (int i = 0; i < col; i++) text[i] = ' '; // fitting spaces
        strcat(text, temp);
        lines[row] = new TextLine(String(text));
        if (row > LastLine) LastLine = row;
    }
    else {
        if (dynamic_cast<TextLine*>(lines[LastLine]) == nullptr) lines[LastLine] = new TextLine();
        lines[row]->insert_text(temp, col, replacement);
    }
}
std::vector<std::pair<int, int>> TextEditor::substring_search(const String& temp) const {
    std::vector<std::pair<int, int>> matches;

    for (int row = 0; row <= LastLine; row++) {
        if (dynamic_cast<TextLine*>(lines[row]) != nullptr)
            for (int col : lines[row]->substring_search(temp))
                matches.emplace_back(row, col);
    }
    return matches;
}
int TextEditor::delete_text(const int number) {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first; const int col = Cursor.second;
    if (row > LastLine) return 1;
    return lines[row]->delete_text(col, number);
}
int TextEditor::copy(const int number) {
    const int row = Cursor.first; const int col = Cursor.second;
    if (row > LastLine) return 1;
    char* temp = lines[row]->copy_text(col, number);
    if (temp == nullptr) return 1;
    Clipboard.text = temp;
    return 0;
}
int TextEditor::cut(const int number) {
    if (copy(number)) return 1;
    return delete_text(number);
}
void TextEditor::paste() {
    insert_text(Clipboard, false);
}
int TextEditor::undo() {
    if (UndoStack.is_empty()) return 1;
    RedoStack.push(lines, RowCount, LastLine);
    cleanup();
    Text textState = UndoStack.pop();
    RowCount = textState.RowCount;
    LastLine = textState.LastLine;
    lines = static_cast<Line **>(calloc(RowCount, sizeof(Line *)));
    for (int i = 0; i <= LastLine; i++) {
        if (textState.lines[i])
            lines[i] = textState.lines[i]->clone();
        else
            lines[i] = nullptr;
    }
    return 0;
}
int TextEditor::redo() {
    if (RedoStack.is_empty()) return 1;
    UndoStack.push(lines, RowCount, LastLine);
    cleanup();
    Text textState = RedoStack.pop();
    RowCount = textState.RowCount;
    LastLine = textState.LastLine;
    lines = static_cast<Line **>(calloc(RowCount, sizeof(Line *)));
    for (int i = 0; i <= LastLine; i++) {
        if (textState.lines[i])
            lines[i] = textState.lines[i]->clone();
        else
            lines[i] = nullptr;
    }
    return 0;
}
void TextEditor::add_checkpoint(const String& item, const bool checked) {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first;
    if (row >= RowCount) {
        RowCount = row + 1; // changing the number of lines
        lines = static_cast<Line**>(realloc(lines, RowCount * sizeof(Line *)));
    }
    for (uint32_t i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
        lines[i] = new EmptyLine();
    }
    lines[row] = new ChecklistLine(item, checked);
    if (row > LastLine) LastLine = row;
}
int TextEditor::check_uncheck() {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first;
    if (row > LastLine) return 2;
    return lines[row]->change_state();
}
void TextEditor::add_contact(const String& name, const String& surname, const String& email) {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first;
    if (row >= RowCount) {
        RowCount = row + 1; // changing the number of lines
        lines = static_cast<Line**>(realloc(lines, RowCount * sizeof(Line *)));
    }
    for (uint32_t i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
        lines[i] = new EmptyLine();
    }
    lines[row] = new ContactLine(name, surname, email);
    if (row > LastLine) LastLine = row;
}
int TextEditor::empty_line() {
    UndoStack.push(lines, RowCount, LastLine);
    RedoStack.clear();
    const int row = Cursor.first;
    if (row > LastLine) return 1;
    lines[row] = new EmptyLine();
    return 0;
}
