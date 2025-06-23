#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

class CaesarCipher {
public:
    CaesarCipher();
    static void init();
    static char* (*encrypt)(const char*, int);
    static char* (*decrypt)(const char*, int);
};

#endif //CAESARCIPHER_H
