#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <cstdlib>
#include <iostream>
#include <Text.cpp>

class TextEditor {
public:
    TextEditor(uint32_t INITIAL_BUFFER_SIZE, uint32_t INITIAL_ROW_COUNT);
    ~TextEditor();

    int command_input() const;
    Text console_input() const;
    static void print_help();
    void set_cursor(int row, int col);
    void add_text(const Text& temp) const;
    void new_line();
    int save_to_file(const Text& file_name) const;
    int load_from_file(const Text& file_name);
    void print_text() const;
    void insert_text(const Text& temp, bool replacement);
    std::vector<std::pair<int, int>> substring_search(const Text& temp) const;
    int delete_text(int number) const;
    int copy(int number);
    int cut(int number);
    void paste();

private:
    void cleanup() const;

    char** text;
    uint32_t BufferSize;
    uint32_t RowCount;
    uint32_t LastLine;
    std::pair<int, int> Cursor;
    Text Clipboard;
};



#endif //TEXTEDITOR_H
