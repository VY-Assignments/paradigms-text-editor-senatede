#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <iostream>
#include "History/TextStateStack.cpp"
#include "LineTypes/Line.h"


class TextEditor {
public:
    TextEditor(uint32_t INITIAL_BUFFER_SIZE, uint32_t INITIAL_ROW_COUNT);
    ~TextEditor();

    int command_input() const;
    String console_input() const;
    static void print_help();
    void set_cursor(int row, int col);
    void print_with_cursor(const char* temp) const;
    void add_text(const String& temp);
    void new_line();
    int save_to_file(const String& file_name);
    int load_from_file(const String& file_name);
    void print_text() const;
    void insert_text(const String& temp, bool replacement);
    std::vector<std::pair<int, int> > substring_search(const String& temp) const;
    int delete_text(int number);
    int copy(int number);
    int cut(int number);
    void paste();
    int undo();
    int redo();
    void add_checkpoint(const String& item, bool checked);
    int check_uncheck();
    void add_contact(const String& name, const String& surname, const String& email);
    int empty_line();

private:
    void cleanup() const;

    // char** text;
    Line** lines;
    uint32_t BufferSize;
    uint32_t RowCount;
    uint32_t LastLine;
    std::pair<int, int> Cursor;
    String Clipboard;
    TextStateStack UndoStack;
    TextStateStack RedoStack;
};



#endif //TEXTEDITOR_H
