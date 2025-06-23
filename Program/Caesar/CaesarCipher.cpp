#include "CaesarCipher.h"
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>

char* (*CaesarCipher::encrypt)(const char*, int) = nullptr;
char* (*CaesarCipher::decrypt)(const char*, int) = nullptr;

void CaesarCipher::init() {
    if (encrypt && decrypt) return;
    void* handle = dlopen("/Users/admin/CLionProjects/paradigms-text-editor-senatede/Program/Caesar/caesar.so", RTLD_LAZY);
    if (!handle) {
        printf("Library could not be loaded.\n");
        exit(1);
    }
    encrypt = (char* (*)(const char*, int)) dlsym(handle, "encrypt");
    decrypt = (char* (*)(const char*, int)) dlsym(handle, "decrypt");
    if (!encrypt || !decrypt) {
        printf("Functions could not be loaded.\n");
        exit(1);
    }
}

CaesarCipher::CaesarCipher() {
    init();
}