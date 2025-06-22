#include <cstdlib>
#include <cstring>

class String {
public:
    char* text;
    String() {text = static_cast<char*>(calloc(1, sizeof(char)));}
    String (char* string) {
        if (string != nullptr) {
            text = static_cast<char*>(calloc(strlen(string) + 1, sizeof(char)));
            strcpy(text, string);
        }
        else text = nullptr;
    }
    String(const String& other) {
        text = static_cast<char*>(calloc(other.len() + 1, sizeof(char)));
        strcpy(text, other.text);
    }
    String& operator=(const String& other) {
        if (this == &other) return *this;
        free(text);
        text = static_cast<char*>(calloc(other.len() + 1, sizeof(char)));
        strcpy(text, other.text);
        return *this;
    }
    bool operator==(const char* other) const {
        return strcmp(text, other) == 0;
    }
    ~String(){
        if (text != nullptr) free(text);
    }
    operator char*() const{
        return text;
    }
    const char* c_str() const{
        return text;
    }
    size_t len() const{
        return strlen(text);
    }
};
