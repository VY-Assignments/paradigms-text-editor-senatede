#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 128
#define INITIAL_ROW_COUNT 10

void print_help();
char* console_input();
void func1(char** text);
void func2(char*** text);
void func3(char** text);
char** func4(char** text);
void func5(char** text);
void func6(char*** text);
void func7(char** text);

char command[3];
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
        scanf("%2s", command);
        while (getchar() != '\n');
        system("clear");
        if (strlen(command) != 1) {printf("Command is not implemented.\n"); continue;}

        switch (*command) {
            case '1': func1(text); break;
            case '2': func2(&text); break;
            case '3': func3(text); break;
            case '4': text = func4(text); break;
            case '5': func5(text); break;
            case '6': func6(&text); break;
            case '7': func7(text); break;
            case 'e': exit(0);
            case 'h': print_help(); break;
            default: printf("Command is not implemented.\n"); break;
        }
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
    while ((c = getchar()) != '\n') {
        buffer[len++] = c;
        if (len == size) {
            size *= 2;
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
        text[LastLine] = realloc(text[LastLine], new_len);
    }
    strcat(text[LastLine], str);
    free(str);
}
void func2(char*** text) { // New line
    if (LastLine >= N_rows) {
        N_rows *= 2;
        *text = realloc(*text, N_rows * sizeof(char*));
    }
    LastLine++;
    (*text)[LastLine] = malloc(1);
    (*text)[LastLine][0] = '\0';
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
char** func4(char** text) { // Load from file
    LastLine = 0;
    N_rows = INITIAL_ROW_COUNT;

    printf("Enter the file name for loading: ");
    const char* file_name = console_input();
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return text;
    }
    free(text);
    char **text = calloc(N_rows, sizeof(char*));
    char c;
    size_t size = INITIAL_BUFFER_SIZE;
    text[LastLine] = malloc(size);
    size_t len = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c != '\n') {
            text[LastLine][len++] = c;
            if (len == size) {
                size *= 2;
                text[LastLine] = realloc(text[LastLine], size);
            }
        }
        else {
            text[LastLine][len] = '\0';
            text[LastLine] = realloc(text[LastLine], len + 1);
            size = INITIAL_BUFFER_SIZE;
            len = 0;
            if (LastLine >= N_rows) {
                N_rows *= 2;
                *text = realloc(*text, N_rows * sizeof(char*));
            }
            LastLine++;
            text[LastLine] = malloc(size);
        }
    }
    printf("Text has been loaded successfully\n");
    return text;
}
void func5(char** text) { // Print text
    for (int i = 0; i <= LastLine; i++) printf("%s\n", text[i]);
}
void func6(char*** text) { // Insert text by row and symbol index
    int row, col;
    printf("Choose line and index: ");
    if (scanf("%d %d", &row, &col) != 2 || row < 0 || col < 0) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    printf("Enter text to insert: ");
    char* str = console_input();
    if (row > LastLine) {
        if (row >= N_rows) {
            N_rows = row + 1;
            *text = realloc(*text, N_rows * sizeof(char*));
        }
        for (int i = LastLine+1; i < row; i++) {
            (*text)[i] = malloc(1);
            (*text)[i][0] = '\0';
        }
        (*text)[row] = malloc(col + strlen(str) + 1);
        for (int i = 0; i < col; i++) (*text)[row][i] = ' ';
        strcat((*text)[row], str);
        LastLine = row;
    }
    else {
        int new_len = (col > strlen((*text)[row])) ? col + strlen(str) + 1: strlen((*text)[row]) + strlen(str) + 1;
        (*text)[row] = realloc((*text)[row], new_len);
        for (int i = strlen((*text)[row]); i > col; i--) (*text)[row][i-1+strlen(str)] = (*text)[row][i-1];
        for (int i = strlen((*text)[row]); i < col; i++) (*text)[row][i] = ' ';
        for (int i = 0; i < strlen(str); i++) (*text)[row][col+i] = str[i];
    }
    free(str);
}
void func7(char** text) { // Substring search mechanism
    printf("Enter text to search: ");
    char* str = console_input();
    int row_index = 0; int col_index = 0;
    int match = 0;
    int count = 0;
    printf("Text is present in this positions: ");
    for (int row = 0; row <= LastLine; row++) {
        for (int index = 0; index < strlen(text[row]); index++) {
            if (text[row][index] == str[match]) {
                if (match == 0) {
                    row_index = row;
                    col_index = index;
                }
                match++;
                if (match == strlen(str)) {
                    printf("%d %d; ", row_index, col_index);
                    row_index = col_index = match = 0;
                    count++;
                }
            }
            else {
                index = index - match;
                match = 0;
            }
        }
    }
    printf("\nTotal matches: %d\n", count);
    free(str);
}