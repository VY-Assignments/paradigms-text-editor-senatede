#include "TextState.cpp"

class TextStateStack {
    TextState* data;
    int capacity = 3;
    int top;

public:
    TextStateStack() {
        top = -1;
        data = static_cast<TextState*>(calloc(capacity, sizeof(TextState)));
    }

    ~TextStateStack() {
        free(data);
    }

    void push(char** value, u_int8_t row_count, u_int8_t line_count) {
        if (top == capacity - 1) {
            for (int i = 1; i < capacity; ++i) {
                data[i-1] = data[i];
            }
            top--;
        }
        data[++top] = TextState(value, row_count, line_count);
    }

    TextState pop() {
        return data[top--];
    }

    bool is_empty() const {
        return top == -1;
    }

    void clear() {
        top = -1;
    }
};