#include "Line.h"

class ContactLine final : public Line {
    String name, surname, email;
public:
    ContactLine(const String& n, const String& s, const String& e) : name(n), surname(s), email(e) {}
    ContactLine(const ContactLine& other) {
        name = other.name;
        surname = other.surname;
        email = other.email;
    }
    ContactLine& operator=(const ContactLine& other) {
        if (this == &other) return *this;
        name = other.name;
        surname = other.surname;
        email = other.email;
        return *this;
    }
    Line* clone() const override {
        return new ContactLine(*this);
    }
    void add_text(const String& str) override {}
    void insert_text(const String& temp, const uint32_t pos, const bool replacement) override {}
    std::vector<int> substring_search(const String& temp) override { return {}; };
    int delete_text(int pos, int number) override {return 1;}
    char* copy_text(int pos, int number) override {return nullptr;}
    int change_state() override { return 1; }
    void print() const override {
        printf("Contact - %s %s, E-mail: %s\n", name.c_str(), surname.c_str(), email.c_str());
    }
};