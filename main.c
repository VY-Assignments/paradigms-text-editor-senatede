#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

char* console_input() {
    u_int32_t size = 256;
    u_int32_t len = 0;
    char* buffer = calloc(size, sizeof(char));
    char c;
    while ((c = getchar()) != '\n') {
        buffer[len++] = c;
        if (len == size) {
            size *= 2; //
            buffer = (char *)realloc(buffer, size);
        }
    }
    buffer[len] = '\0';
    return buffer;
}
int int_input() {
    char* str = console_input();
    const int num = atoi(str);
    free(str);
    return num;
}


int main() {
    void* handle = dlopen("caesar.so", RTLD_LAZY);
    if (!handle) {
        printf("Library could not be loaded.\n"); return 1;
    }
    printf("Library loaded.\n");

    char * (*encrypt)(const char *, int) = dlsym(handle, "encrypt");
    char * (*decrypt)(const char *, int) = dlsym(handle, "decrypt");
    if (!encrypt || !decrypt) {
        printf("Functions could be loaded.\n"); return 1;
    }

    printf("Commands:\n  1 - Encrypt\n  2 - Decrypt\n -1 - Exit\n");
    char *text, *rawText; int key;
    while (1) {
        printf("Choose command: ");
        switch (int_input()) {
            case 1:
                printf("Text to encrypt: "); rawText = console_input();
                printf("Key: "); key = int_input();
                if (key == 0) {
                    printf("Key is invalid.\n"); break;
                }
                text = encrypt(rawText, key);
                printf("Encrypted text:\n%s\n", text);
                free(rawText); free(text);
                break;
            case 2:
                printf("Text to decrypt: "); rawText = console_input();
                printf("Key: "); key = int_input();
                if (key == 0) {
                    printf("Key is invalid.\n"); break;
                }
                text = decrypt(rawText, key);
                printf("Decrypted text:\n%s\n", text);
                free(rawText); free(text);
                break;
            case -1:
                printf("Exiting.\n");
                dlclose(handle);
                return 0;
            default:
                printf("Invalid command.\n"); break;
        }
    }
}