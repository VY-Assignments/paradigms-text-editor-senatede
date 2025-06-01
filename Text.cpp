#include <cstdlib>

class Text {
public:
    char* text;
    Text() {text = NULL;}
    explicit Text (char* string) {
        text = string;
    }
    ~Text() {
        free(text);
    }
    operator char*() const {
        return text;
    }
};
