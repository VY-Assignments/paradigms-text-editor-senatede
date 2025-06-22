#include <cstdlib>
#include <cstring>

class String {
public:
    char* text;
    String() {text = NULL;};
    explicit String (char* string) {
        text = string;
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
    ~String(){
        free(text);
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
