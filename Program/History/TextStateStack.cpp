#include "Text.cpp"

class TextStateStack {
    Text* data;
    int capacity = 3;
    int top;

public:
    TextStateStack() {
        top = -1;
        data = static_cast<Text*>(calloc(capacity, sizeof(Text)));
    }

    ~TextStateStack() {
        for (int i = 0; i <= top; ++i) {
            data[i].~Text();
        }
        free(data);
    }

    void push(Line** value, const u_int32_t row_count, const u_int32_t line_count) {
        if (top == capacity - 1) {
            for (int i = 1; i < capacity; ++i) {
                data[i-1] = data[i];
            }
            top--;
        }
        data[++top] = Text(value, row_count, line_count);
    }

    Text pop() {
        return data[top--];
    }

    bool is_empty() const {
        return top == -1;
    }

    void clear() {
        for (int i = 0; i <= top; ++i) {
            data[i].~Text();
        }
        top = -1;
    }
};