#include "String.hpp"

bool String::containsChar(const char* cstring, char contained) {
    for (int i = 0; i < getLength(cstring); i++) {
        if (cstring[i] == contained) {
            return true;
        }
    }
    return false;
}

unsigned int String::getLength(const char* cstring) {
    unsigned int length = 0;
    while (*cstring != '\0') {
        length++;
        cstring++;
    }
    return length;
}

void String::copy(const char* source, char* destination, unsigned int length) {
    for (int i = 0; i < length; i++) {
        *destination = *source;
        destination++;
        source++;
    }
}

bool String::equals(const char* first, const char* second) {
    unsigned int firstLength = getLength(first);
    unsigned int secondLength = getLength(second);
    if (firstLength != secondLength) {
        return false;
    }
    for (int i = 0; i < firstLength; i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

String::String() {
    length = 0;
    content = new char[length + 1];
    content[0] = '\0';
}

String::~String() {
    length = 0;
    delete[] content;
}

String::String(const String& other) {
    if (length != other.length || other.length == 0) {
        delete[] content;
        length = other.length;
        content = new char[length + 1];
    }
    copy(other.content, content, length + 1);
}

String& String::operator=(const String& other) {
    if (length != other.length || other.length == 0) {
        delete[] content;
        length = other.length;
        content = new char[length + 1];
    }
    copy(other.content, content, length + 1);
    return *this;
}

String::String(String&& other) {
    char* tmp = content;
    content = other.content;
    other.content = tmp;
}

String& String::operator=(String&& other) {
    char* tmp = content;
    content = other.content;
    other.content = tmp;
    return *this;
}

String::String(const char* cstring) {
    length = getLength(cstring);
    content = new char[length + 1];
    copy(cstring, content, length + 1);
}

String& String::operator=(const char* cstring) {
    unsigned int cstringLength = getLength(cstring);
    if (length != cstringLength) {
        delete[] content;
        length = cstringLength;
        content = new char[length + 1];
    }
    copy(cstring, content, length + 1);
    return *this;
}

void String::trim() {
    int frontWhitespaces = 0;
    for (int i = 0; i < length; i++) {
        if (isspace(content[i])) {
            frontWhitespaces++;
        } else {
            break;
        }
    }

    int backWhitespaces = 0;
    for (int i = length - 1; i >= frontWhitespaces; i--) {
        if (isspace(content[i])) {
            backWhitespaces++;
        } else {
            break;
        }
    }

    unsigned int newLength = length - frontWhitespaces - backWhitespaces;
    if (length == newLength) {
        return;
    }
    char* newContent = new char[newLength + 1];
    copy(content + frontWhitespaces, newContent, newLength);
    newContent[newLength] = '\0';

    length = newLength;
    delete[] content;
    content = newContent;
}

bool String::equals(const char* cstring) { return equals(content, cstring); }

String String::readString(const char* endChars, int defaultReadLength) {
    char* input = new char[defaultReadLength];
    int readLength = defaultReadLength;
    char c;
    for (int i = 0; std::cin.good(); i++) {
        if (i >= readLength) {
            readLength *= 2;
            char* biggerInput = new char[readLength];
            copy(input, biggerInput, i);
            delete[] input;
            input = biggerInput;
        }
        c = getchar();
        if (containsChar(endChars, c)) {
            input[i] = '\0';
            break;
        }
        input[i] = c;
    }
    String s = String(input);
    delete[] input;
    return s;
}

std::ostream& operator<<(std::ostream& stream, const String& str) {
    stream << str.content;
    return stream;
}