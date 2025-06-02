#include <cstdlib>

class TextState {
public:
    char** text;
    uint32_t RowCount;
    uint32_t LastLine;

    TextState(char** value, uint32_t rowCount, uint32_t lastLine) {
        text = static_cast<char **>(calloc(rowCount, sizeof(char *)));
        for (uint32_t i = 0; i <= lastLine; i++) {
            text[i] = strdup(value[i]);
        }
        RowCount = rowCount;
        LastLine = lastLine;
    }
};
