#pragma once

#include <iostream>
#include "String.cpp"

class Line {
public:
    virtual void print() const = 0;
    virtual void add_text(const String& str) = 0;
    virtual void insert_text(const String& temp, uint32_t pos, bool replacement) = 0;
    virtual std::vector<int> substring_search(const String& temp) = 0;
    virtual int delete_text(int pos, int number) = 0;
    virtual char* copy_text(int pos, int number) = 0;
    virtual int change_state() = 0;
    virtual Line* clone() const = 0;
    virtual ~Line() = default;
    virtual String serialize() = 0;
};