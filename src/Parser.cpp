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
            sections.append(*parseSection(inputString, globalBlock));
        }
    }
}

void Parser::parseCommands() {
    while (std::cin.good()) {
        String input = String::readString(",\n");
        input.trim();
        if (input.equals("****")) {
            return;
        } else if (input.equals("?")) {
            std::cout << "? == " << sections.getSize() << std::endl;
        } else {
            String& firstArgument = input;
            String secondArgument = String::readString(",");
            String thirdArgument = String::readString(",\n");
            parseOperations(firstArgument, secondArgument, thirdArgument);
        }
    }
    return;
}

void Parser::parseOperations(String& firstArg, String& secondArg,
                             String& thirdArg) {
    if (thirdArg.equals("?")) {
        try {
            int num = firstArg.toInt();
            if (secondArg.equals("S")) {
                // i,S,?
                Section& s = sections.getAt(num - 1);
                List<Selector>* sels = s.getSelectors();
                int size = sels->getSize();
                std::cout << num << ",S,? == " << size << std::endl;
            } else if (secondArg.equals("A")) {
                // i,A,?
                int size = sections.getAt(num - 1).getAttributes()->getSize();
                std::cout << num << ",A,? == " << size << std::endl;
            }
        } catch (const char*) {
            if (secondArg.equals("S")) {
                // z,S,?
            } else if (secondArg.equals("A")) {
                // n,A,?
            }
        }
    }
}

Section* Parser::parseSection(String firstInput, bool globalBlock) {
    if (globalBlock) {
        return new Section(nullptr, parseAttributes());
    }

    List<Selector>* selectors = parseSelectors(firstInput);
    List<Attribute>* attributes = parseAttributes();
    return new Section(selectors, attributes);
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
