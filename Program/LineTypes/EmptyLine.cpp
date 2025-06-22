#include "Line.h"

class EmptyLine final : public Line {
public:
    EmptyLine() = default;
    Line* clone() const override {
        return new EmptyLine(*this);
    }
    void add_text(const String& str) override {}
    void insert_text(const String& temp, const uint32_t pos, const bool replacement) override {}
    std::vector<int> substring_search(const String& temp) override { return {}; };
    int delete_text(int pos, int number) override {return 1;}
    char* copy_text(int pos, int number) override {return nullptr;}
    int change_state() override { return 1; }
    void print() const override { printf("\n"); }
    String serialize() override {
        return {};
    }
};