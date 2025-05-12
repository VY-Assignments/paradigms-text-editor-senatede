#include <stdio.h>
#include <string.h>

void func1(char text[][100], unsigned int NumberOfLines);
void func2(unsigned int *NumberOfLines);
void func3();
void func4();
void func5(char text[][100], unsigned int NumberOfLines);
void func6();
void func7();

char command[2];
unsigned int NumberOfLines = 1;
char text[10][100] = { 0 };

int main(void) {
    printf("Welcome to the Simple Text Editor!\n Available commands:\n 1 - Append text symbols to the end\n 2 - Start the new line\n 5 - Print the current text to console\n");
    while(1) {
        printf("Choose the command:\n");
        scanf("%2s", command);
        while (getchar() != '\n');
        if (strlen(command) != 1) {printf("Command is not implemented.\n"); continue;}

        switch (*command) {
            case '1': func1(text, NumberOfLines); break;
            case '2': func2(&NumberOfLines); break;
            case '5': func5(text, NumberOfLines); break;
            default: printf("Command is not implemented.\n"); break;
        }
    }
}

void func1(char text[][100], const unsigned int NumberOfLines) {
    char new_text[100];
    printf("Enter text to append: ");
    fgets(new_text, sizeof(new_text), stdin);
    new_text[strlen(new_text)-1] = 0; // removing \n at the end
    strcat(text[NumberOfLines-1], new_text);
}
void func2(unsigned int *NumberOfLines) {
    (*NumberOfLines) = (*NumberOfLines) + 1;
    printf("New line is started\n");
}
void func5(char text[][100], const unsigned int NumberOfLines) {
    for (int i = 0; i < NumberOfLines; i++) printf("%s\n", text[i]);
}