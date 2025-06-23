#include "Line.h"

class TextLine final : public Line {
    String TextKeyWord = String("Text");
    char* text;
    uint32_t len;
    public:
    TextLine() {
        text = static_cast<char *>(calloc(1, sizeof(char)));
        text[0] = '\0';
        len = 0;
    }
    explicit TextLine(const String& temp) {
        len = strlen(temp);
        text = static_cast<char*>(calloc(len + 1, sizeof(char)));
        strcpy(text, temp);
    }
    explicit TextLine(const String& temp, const String& textKeyWord) {
        TextKeyWord = textKeyWord;
        len = strlen(temp);
        text = static_cast<char*>(calloc(len + 1, sizeof(char)));
        strcpy(text, temp);
    }
    TextLine(const TextLine& other) {
        len = other.len;
        TextKeyWord = other.TextKeyWord;
        text = static_cast<char*>(calloc(len + 1, sizeof(char)));
        strcpy(text, other.text);
    }
    TextLine& operator=(const TextLine& other) {
        if (this == &other) return *this;
        free(text);
        len = other.len;
        TextKeyWord = other.TextKeyWord;
        text = static_cast<char*>(calloc(len + 1, sizeof(char)));
        strcpy(text, other.text);
        return *this;
    }
    Line* clone() const override {
        return new TextLine(*this);
    }
    ~TextLine() override {
        free(text);
    }
    void add_text(const String& temp) override {
        len += strlen(temp) + 1;
        text = static_cast<char *>(realloc(text, len * sizeof(char))); // reallocating memory for new line length
        strcat(text, temp);
    }
    void insert_text(const String& temp, const uint32_t pos, const bool replacement) override {
        uint32_t new_len = (pos > len) ? pos + strlen(temp) + 1: len + strlen(temp) + 1;
        text = static_cast<char *>(realloc(text, new_len)); // reallocating for new len
        if (!replacement) for (uint32_t i = len; i > pos; i--) text[i-1+strlen(temp)] = text[i-1]; // moving characters after index to the right
        for (uint32_t i = len; i < pos; i++) text[i] = ' '; // if index is > than len of the line we fit empty space with spaces
        for (int i = 0; i < strlen(temp); i++) text[pos+i] = temp[i];
        len = new_len;
    }
    std::vector<int> substring_search(const String& temp) override {
        int pos = 0;
        int match_count = 0;
        std::vector<int> matches;

        for (int index = 0; index < strlen(text); index++) {
            if (text[index] == temp[match_count]) {
                if (match_count == 0) pos = index; // if it's the first match we set the index of the start
                match_count++;
                if (match_count == strlen(temp)) { // if the match_count == len of substring then we found a match
                    matches.emplace_back(pos);
                    pos = match_count = 0;
                }
            }
            else {
                index = index - match_count; // going back to the next index after the start of match
                match_count = 0;
            }
        }
        return matches;
    }
    int delete_text(int pos, int number) override {
        if (pos > len) return 1;
        for (size_t i = pos; i < len; i++) text[i] = (i+number < len) ?  text[i+number] : '\0';
        const uint8_t new_len = (pos > len - number) ? pos: len - number;
        text = static_cast<char *>(realloc(text, new_len));
        return 0;
    }
    char* copy_text(int pos, int number) override {
        if (pos >= strlen(text)) return nullptr;
        char* temp = static_cast<char*>(calloc(number + 1, sizeof(char)));
        for (int i = 0; i < number & i < strlen(text) - pos; i++) temp[i] = text[pos+i];
        return temp;
    }
    int change_state() override { return 1; }
    void print() const override { printf("%s: %s\n", TextKeyWord.c_str(), text); }
    String serialize() override {
        auto temp = new char[9 + 4 + 1 + len + 1];
        temp[0] = '\0';
        strcat(temp, "TextLine\n");
        strcat(temp, TextKeyWord.c_str());
        strcat(temp, "\n");
        strcat(temp, text);
        return {temp};
    }
    void encrypt(const int key) override {
        text = CaesarCipher::encrypt(text, key);
        TextKeyWord = CaesarCipher::encrypt(TextKeyWord, key);
    }
    void decrypt(const int key) override {
        text = CaesarCipher::decrypt(text, key);
        TextKeyWord = CaesarCipher::decrypt(TextKeyWord, key);
    }
};
