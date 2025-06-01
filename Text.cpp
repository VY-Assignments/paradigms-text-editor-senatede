#include <cstdlib>

class Text {
public:
    char* text;
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
