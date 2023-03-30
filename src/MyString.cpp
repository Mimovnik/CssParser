#include "MyString.hpp"

#include <cstring>

bool MyString::containsChar(const char* array, char contained) {
    for (int i = 0; i < strlen(array); i++) {
        if (array[i] == contained) {
            return true;
        }
    }
    return false;
}

char* MyString::trimmed(const char* array) { return nullptr; }

MyString::MyString() : MyString("") {}

MyString::MyString(const char* s) {
    length = strlen(s);
    content = new char[length + 1];
    strcpy(content, s);
    content[length] = '\0';
}

MyString::~MyString() { delete[] content; }

MyString MyString::operator+(MyString const& other) {
    return MyString(strcat(this->content, other.content));
}
MyString& MyString::operator=(const char* s) {
    int sLen = strlen(s);
    if (length != sLen) {
        delete[] content;
        length = sLen;
        content = new char[length + 1];
    }
    std::copy(s, s + length, content);
    content[length] = '\0';
    return *this;
}

MyString& MyString::operator=(MyString const& other) {
    int sLen = strlen(other.content);
    if (length != sLen) {
        delete[] content;
        length = sLen;
        content = new char[length + 1];
    }
    std::copy(other.content, other.content + length, content);
    content[length] = '\0';
    return *this;
}

void MyString::trim() {
    int frontWhitespaces = 0;
    for (int i = 0; i < length; i++) {
        if (isspace(content[i])) {
            frontWhitespaces++;
        } else {
            break;
        }
    }

    int backWhitespaces = 0;
    for (int i = length - 1; i >= 0; i++) {
        if (isspace(content[i])) {
            backWhitespaces++;
        } else {
            break;
        }
    }

    int newLength = length - frontWhitespaces - backWhitespaces;
    char* newContent = new char[newLength + 1];
    for (int i = 0; i < newLength; i++) {
        newContent[i] = content[frontWhitespaces + i];
    }
    length = newLength;
    delete[] content;
    content = newContent;
    content[length] = '\0';
}

bool MyString::equals(const char* s) { return strcmp(content, s) == 0; }

MyString MyString::readString(const char* endChars) {
    char input[MAX_READ_LENGTH];
    char c;
    for (int i = 0; std::cin.good() && i < MAX_READ_LENGTH; i++) {
        c = getchar();
        if (containsChar(endChars, c)) {
            input[i] = '\0';
            break;
        }
        input[i] = c;
    }
    MyString s = MyString(input);
    return s;
}

std::ostream& operator<<(std::ostream& stream, const MyString& str) {
    stream << str.content;
    return stream;
}