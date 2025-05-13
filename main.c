#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 32
#define INITIAL_ROW_COUNT 10

char* console_input();
void func1(char** text);
void func2(char*** text);
void func3(char** text);
char** func4();
void func5(char** text);
void func6();
void func7();

char command[3];
unsigned int LastLine = 0;
unsigned int N_rows = INITIAL_ROW_COUNT;
unsigned int BufferSize = INITIAL_BUFFER_SIZE;
FILE* file;

int main(void) {
    char **text = calloc(N_rows, sizeof(char*));
    text[LastLine] = malloc(1);
    text[LastLine][0] = '\0'; // creating first empty line

    printf("Welcome to the Simple Text Editor!\n Available commands:\n 1 - Append text symbols to the end\n 2 - Start the new line\n 3 - Save to file\n 4 - Load from file\n 5 - Print the current text to console\n");
    while(1) {
        printf("Choose the command:\n");
        scanf("%2s", command);
        while (getchar() != '\n');
        if (strlen(command) != 1) {printf("Command is not implemented.\n"); continue;}

        switch (*command) {
            case '1': func1(text); break;
            case '2': func2(&text); break;
            case '3': func3(text); break;
            case '4': text = func4(); break;
            case '5': func5(text); break;
            default: printf("Command is not implemented.\n"); break;
        }
    }
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
char** func4() { // Load from file
    LastLine = 0;
    N_rows = INITIAL_ROW_COUNT;

    printf("Enter the file name for loading: ");
    const char* file_name = console_input();
    file = fopen(file_name, "r");
    if (file == NULL) printf("Error opening file\n");
    else
    {
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
        return text;
    }
}
void func5(char** text) { // Print text
    for (int i = 0; i <= LastLine; i++) printf("%s\n", text[i]);
}