#include "Line.h"

class ChecklistLine final : public Line {
    String item;
    bool checked;
public:
    ChecklistLine(const String& i, bool c) : item(i), checked(c) {}
    ChecklistLine(const ChecklistLine& other) {
        item = other.item;
        checked = other.checked;
    }
    ChecklistLine& operator=(const ChecklistLine& other) {
        if (this == &other) return *this;
        item = other.item;
        checked = other.checked;
        return *this;
    }
    Line* clone() const override {
        return new ChecklistLine(*this);
    }
    int change_state() override {
        checked = !checked;
        return 0;
    }
    void add_text(const String& str) override {}
    void insert_text(const String& temp, const uint32_t pos, const bool replacement) override {}
    std::vector<int> substring_search(const String& temp) override { return {}; };
    int delete_text(int pos, int number) override {return 1;}
    char* copy_text(int pos, int number) override {return nullptr;}
    void print() const override {
        printf("[ %c ] %s\n", (checked ? 'x' : ' '), item.c_str());
    };
    String serialize() override {
        char* temp = new char[14 + 1 + 1 + item.len() + 1];
        strcat(temp, "ChecklistLine\n");
        strcat(temp, checked ? "1" : "0");
        strcat(temp, "\n");
        strcat(temp, item);
        return {temp};
    }
    void encrypt(const int key) override {
        item = CaesarCipher::encrypt(item, key);
    }
    void decrypt(const int key) override {
        item = CaesarCipher::decrypt(item, key);
    }
};