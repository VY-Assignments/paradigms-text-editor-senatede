#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 128
#define INITIAL_ROW_COUNT 10

void print_help();
char* console_input();
void func1(char** text);
void func2(char*** text_pointer);
void func3(char** text);
void func4(char*** text_pointer);
void func5(char** text);
void func6(char*** text_pointer);
void func7(char** text);

int LastLine = 0;
unsigned int N_rows = INITIAL_ROW_COUNT;
unsigned int BufferSize = INITIAL_BUFFER_SIZE;
FILE* file;

int main(void) {
    char **text = calloc(N_rows, sizeof(char*));
    text[LastLine] = malloc(1);
    text[LastLine][0] = '\0'; // creating first empty line

    system("clear");
    print_help();
    while(1) {
        printf("Choose the command:\n");
        char* command = console_input();
        system("clear"); // Clearing console
        if (strlen(command) != 1) {printf("Command is not implemented.\n"); continue;}

        switch (*command) {
            case '1': func1(text); break;
            case '2': func2(&text); break;
            case '3': func3(text); break;
            case '4': func4(&text); break;
            case '5': func5(text); break;
            case '6': func6(&text); break;
            case '7': func7(text); break;
            case 'e': exit(0);
            case 'h': print_help(); break;
            default: printf("Command is not implemented.\n"); break;
        }
        free(command);
    }
}

void print_help() {
    printf("Welcome to the Simple Text Editor!\n Available commands:\n"
           " 1 - Append text symbols to the end\n"
           " 2 - Start the new line\n"
           " 3 - Save to file\n"
           " 4 - Load from file\n"
           " 5 - Print the current text to console\n"
           " 6 - Insert the text by line and symbol index\n"
           " 7 - Search substring\n"
           " e - Exit\n"
           " h - Help\n");
}
char* console_input() { // Text input
    size_t size = INITIAL_BUFFER_SIZE;
    size_t len = 0;
    char* buffer = malloc(size);
    char c;
    while ((c = getchar()) != '\n') { // getting each character
        buffer[len++] = c;
        if (len == size) {
            size *= 2; // doubling size of bugger
            buffer = realloc(buffer, size);
        }
    }
    buffer[len] = '\0';
    return buffer;
}
void func1(char** text) { // Adding text
    printf("Enter text to append: ");
    char* str = console_input();
    if (text[LastLine] == NULL) text[LastLine] = malloc(strlen(str) + 1);
    else {
        size_t new_len = strlen(text[LastLine]) + strlen(str) + 1;
        text[LastLine] = realloc(text[LastLine], new_len); // reallocating memory for new line length
    }
    strcat(text[LastLine], str);
    free(str);
}
void func2(char*** text_pointer) { // New line
    if (LastLine >= N_rows) {
        N_rows *= 2; // doubling number of rows
        *text_pointer = realloc(*text_pointer, N_rows * sizeof(char*));
    }
    LastLine++;
    (*text_pointer)[LastLine] = malloc(1);
    (*text_pointer)[LastLine][0] = '\0';
    printf("New line is started\n");
}
void func3(char** text) { // Save to file
    printf("Enter the file name for saving: ");
    char *file_name = console_input();
    file = fopen(file_name, "w");
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
void func4(char*** text_pointer) { // Load from file
    printf("Enter the file name for loading: ");
    char* file_name = console_input();
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file\n");
    }
    else {
        LastLine = 0;
        N_rows = INITIAL_ROW_COUNT;
        free(*text_pointer);
        *text_pointer = calloc(N_rows, sizeof(char*));
        char c;
        size_t size = INITIAL_BUFFER_SIZE;
        (*text_pointer)[LastLine] = malloc(size);
        size_t len = 0;
        while ((c = fgetc(file)) != EOF) {
            if (c != '\n') {
                (*text_pointer)[LastLine][len++] = c;
                if (len == size) {
                    size *= 2; // doubling size for now
                    (*text_pointer)[LastLine] = realloc((*text_pointer)[LastLine], size);
                }
            }
            else {
                (*text_pointer)[LastLine][len] = '\0';
                (*text_pointer)[LastLine] = realloc((*text_pointer)[LastLine], len + 1); // reallocating for the exact line length
                size = INITIAL_BUFFER_SIZE;
                len = 0;
                if (LastLine >= N_rows-1) {
                    N_rows *= 2; // doubling the number of lines
                    *text_pointer = realloc(*text_pointer, N_rows * sizeof(char*));
                }
                LastLine++;
                (*text_pointer)[LastLine] = malloc(size); // allocating memory for the next line
            }
        }
        printf("Text has been loaded successfully\n");
    }
    free(file_name);
}
void func5(char** text) { // Print text
    for (int i = 0; i <= LastLine; i++) printf("%s\n", text[i]);
}
void func6(char*** text_pointer) { // Insert text by row and symbol index
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
        if (row >= N_rows) {
            N_rows = row + 1; // changing the number of lines
            *text_pointer = realloc(*text_pointer, N_rows * sizeof(char*));
        }
        for (int i = LastLine+1; i < row; i++) { // creating empty lines between last one and the one we want
            (*text_pointer)[i] = malloc(1);
            (*text_pointer)[i][0] = '\0';
        }
        (*text_pointer)[row] = malloc(col + strlen(str) + 1); // allocating memory for our line
        for (int i = 0; i < col; i++) (*text_pointer)[row][i] = ' '; // fitting spaces
        strcat((*text_pointer)[row], str);
        LastLine = row;
    }
    else {
        int new_len = (col > strlen((*text_pointer)[row])) ? col + strlen(str) + 1: strlen((*text_pointer)[row]) + strlen(str) + 1;
        (*text_pointer)[row] = realloc((*text_pointer)[row], new_len); // reallocating for new len
        for (int i = strlen((*text_pointer)[row]); i > col; i--) (*text_pointer)[row][i-1+strlen(str)] = (*text_pointer)[row][i-1]; // moving characters after index to the right
        for (int i = strlen((*text_pointer)[row]); i < col; i++) (*text_pointer)[row][i] = ' '; // if index is > than len of the line we fit empty space with spaces
        for (int i = 0; i < strlen(str); i++) (*text_pointer)[row][col+i] = str[i];
    }
    free(str);
}
void func7(char** text) { // Substring search mechanism
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