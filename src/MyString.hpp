#pragma once
#include <iostream>

class MyString {
   private:
    static const int MAX_READ_LENGTH = 128;

    char* content = nullptr;

    int length = 0;

    static bool containsChar(const char* array, char contained);

    char* trimmed(const char* array);

   public:
    MyString();

    MyString(const char* s);

    ~MyString();

    MyString operator+(MyString const& other);

    MyString& operator=(const char* s);

    MyString& operator=(MyString const& other);

    void trim();

    bool equals(const char* s);

    static MyString readString(const char* endChars);

    friend std::ostream& operator<<(std::ostream& stream, const MyString& str);
};