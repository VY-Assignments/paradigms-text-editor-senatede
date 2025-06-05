#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* encrypt(const char* rawText, const int key) {
    const u_int8_t len = strlen(rawText);
    char* text = calloc(len + 1, sizeof(char));

    for (int i = 0; i < len; i++) {
        char a = islower(rawText[i]) ? 'a' : 'A';
        text[i] = isalpha(rawText[i]) ? a + (rawText[i] - a + key) % 26 : rawText[i];
    }
    return text;
}

char* decrypt(const char* rawText, const int key) {
    const u_int8_t len = strlen(rawText);
    char* text = calloc(len + 1, sizeof(char));

    for (int i = 0; i < len; i++) {
        char z = islower(rawText[i]) ? 'z' : 'Z';
        text[i] = isalpha(rawText[i]) ? z - (z - rawText[i] + key) % 26 : rawText[i];
    }
    return text;
}