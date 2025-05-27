#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <cstdlib>

class TextEditor {
public:
    TextEditor(uint32_t INITIAL_BUFFER_SIZE, uint32_t INITIAL_ROW_COUNT);
    ~TextEditor();

    int command_input() const;

    static void print_help();
    void add_text() const;
    void new_line();
    void save_to_file() const;
    void load_from_file();
    void print_text() const;
    void insert_text();
    void substring_search() const;

private:
    char* console_input() const;
    void cleanup() const;

    char** text;
    uint32_t BufferSize;
    uint32_t RowCount;
    uint32_t LastLine;
};



#endif //TEXTEDITOR_H
