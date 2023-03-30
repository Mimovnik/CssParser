#include "Parser.hpp"

#include <iostream>

#include "MyString.hpp"

void Parser::parse() {
    while (std::cin.good()) {
        MyString input = MyString::readString(",\n");
        input.trim();
        if (input.equals("????")) {
            parseCommands();
        } else {
            // sections.add(parseSection(input));
        }
    }
}

void Parser::parseCommands() {
    std::cout << "Parsing commands" << std::endl;
    while (std::cin.good()) {
        MyString input = MyString::readString("\n");
        input.trim();
        if (input.equals("****")) {
            return;
        }
        std::cout << "Command" << std::endl;
    }
    return;
}

// Section* Parser::parseSection(MyString firstInput) {
void Parser::parseSection(MyString firstInput) {
    if (firstInput.equals("{")) {
        // global section
        // return new Section(nullptr, parseAttributes());
    }

    // return new Section(parseSelectors(firstInput), parseAttributes());
    return;
}

// List<Selector>* Parser::parseSelectors() {
void Parser::parseSelectors(MyString firstInput) {
    // List<Selector>* selectors = new List<Selector>();
    // selectors->add(new Selector(firstInput));
    while (std::cin.good()) {
        MyString name = MyString::readString(",\n");
        name.trim();
        if (name.equals("{")) {
            break;
        }

        // selectors->add(new Selector(name));
    }
    // return selectors;
}

// List<Attribute>* Parser::parseAttributes() {
void Parser::parseAttributes() {
    // List<Attribute>* attributes = new List<Attributes>();
    while (std::cin.good()) {
        MyString property = MyString::readString(":");
        property.trim();
        if (property.equals("}")) {
            break;
        }

        MyString value = MyString::readString(";\n");
        value.trim();

        // attributes->add(new Attribute(property, value));
    }
    // return attributes;
}
