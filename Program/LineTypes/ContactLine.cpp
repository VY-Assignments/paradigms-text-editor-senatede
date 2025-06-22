#include "Line.h"

class ContactLine final : public Line {
    String ContactKeyWord = String("Contact");
    String EmailKeyWord = String("E-mail");
    String name, surname, email;
public:
    ContactLine(const String& n, const String& s, const String& e) : name(n), surname(s), email(e) {}
    ContactLine(const String& ckn, const String& n, const String& s, const String& ekn, const String& e) : ContactKeyWord(ckn), EmailKeyWord(ekn), name(n), surname(s), email(e) {}
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
        printf("%s - %s %s, %s: %s\n", ContactKeyWord.c_str(), name.c_str(), surname.c_str(), EmailKeyWord.c_str(), email.c_str());
    }
    String serialize() override {
        char* temp = new char[12 + 7 + 1 + name.len() + 1 + surname.len() + 6 + 1 + email.len() + 1];
        strcat(temp, "ContactLine\n");
        strcat(temp, ContactKeyWord.c_str());
        strcat(temp, "\n");
        strcat(temp, name);
        strcat(temp, "\n");
        strcat(temp, surname);
        strcat(temp, "\n");
        strcat(temp, EmailKeyWord.c_str());
        strcat(temp, "\n");
        strcat(temp, email);
        return String(temp);
    }
};