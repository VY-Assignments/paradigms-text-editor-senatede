#include "../LineTypes/Line.h"

class Text {
public:
    Line** lines;
    uint32_t RowCount;
    uint32_t LastLine;

    Text(Line** value, const uint32_t rowCount, const uint32_t lastLine) {
        lines = new Line*[rowCount];
        for (uint32_t i = 0; i <= lastLine; i++) {
            if (value[i]) {
                lines[i] = value[i]->clone();
            } else {
                lines[i] = nullptr;
            }
        }
        RowCount = rowCount;
        LastLine = lastLine;
    }
};
