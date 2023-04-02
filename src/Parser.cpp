#include "Parser.hpp"

#include <iostream>

Parser::FlagString Parser::FlagString::readString(const char* endChars,
                                                  const char* flagChars,
                                                  int defaultReadLength) {
    char* input = new char[defaultReadLength];
    int readLength = defaultReadLength;
    char c;
    bool flag = false;
    for (int i = 0; std::cin.good(); i++) {
        if (i >= readLength) {
            readLength *= 2;
            char* biggerInput = new char[readLength];
            String::copy(input, biggerInput, i);
            delete[] input;
            input = biggerInput;
        }

        c = getchar();
        if (String::containsChar(flagChars, c)) {
            flag = true;
        }
        if (String::containsChar(endChars, c)) {
            input[i] = '\0';
            break;
        }
        input[i] = c;
    }
    String s = String(input);
    delete[] input;
    return FlagString(s, flag);
}

void Parser::parse() {
    while (std::cin.good()) {
        FlagString input = FlagString::readString(",{\n", "{");

        bool endedOnBlockStart = input.getFlag();

        String& inputString = input.getString();
        inputString.trim();

        bool globalBlock = inputString.equals("") && endedOnBlockStart;
        if (inputString.equals("") && !globalBlock) {
            continue;
        } else if (inputString.equals("????")) {
            parseCommands();
        } else {
            Section s = parseSection(inputString, globalBlock);
            sections.append(s);
        }
    }
}

void Parser::parseCommands() {
    std::cout << "Parsing commands" << std::endl;
    while (std::cin.good()) {
        String input = String::readString("\n");
        input.trim();
        if (input.equals("****")) {
            return;
        }
        std::cout << "Command" << std::endl;
    }
    return;
}

Section Parser::parseSection(String firstInput, bool globalBlock) {
    if (globalBlock) {
        return Section(nullptr, parseAttributes());
    }

    List<Selector>* selectors = parseSelectors(firstInput);
    List<Attribute>* attributes = parseAttributes();
    return Section(selectors, attributes);
}

List<Selector>* Parser::parseSelectors(String firstInput) {
    List<Selector>* selectors = new List<Selector>();
    selectors->append(Selector(firstInput));
    while (std::cin.good()) {
        FlagString input = FlagString::readString(",{", "{");
        bool endParsing = input.getFlag();

        String& name = input.getString();
        name.trim();
        if (!name.equals("")) {
            selectors->append(Selector(name));
        }

        if (endParsing) {
            break;
        }
    }
    return selectors;
}

List<Attribute>* Parser::parseAttributes() {
    List<Attribute>* attributes = new List<Attribute>();
    while (std::cin.good()) {
        String property = String::readString(":}");
        property.trim();
        if (property.equals("")) {
            break;
        }

        String value = String::readString(";\n");
        value.trim();

        attributes->append(Attribute(property, value));
    }
    return attributes;
}

Parser::FlagString::FlagString(FlagString&& other) {
    string = std::move(other.string);
    flag = other.flag;
}

Parser::FlagString& Parser::FlagString::operator=(FlagString&& other) {
    string = std::move(other.string);
    flag = other.flag;
    return *this;
}

Parser::FlagString::FlagString(String string, bool flag) {
    this->string = string;
    this->flag = flag;
}

String& Parser::FlagString::getString() { return string; }

bool Parser::FlagString::getFlag() { return flag; }
