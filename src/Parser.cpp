#include "Parser.hpp"

#include <iostream>

void Parser::parse() {
    while (std::cin.good()) {
        MyString input = MyString::readString(",\n");
        input.trim();
        if (input.equals("????")) {
            parseCommands();
        } else {
            Section s = parseSection(input);
            sections.append(s);
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

Section Parser::parseSection(MyString firstInput) {
    if (firstInput.equals("{")) {
        // global section
        return Section(nullptr, parseAttributes());
    }

    List<Selector>* selectors = parseSelectors(firstInput);
    List<Attribute>* attributes = parseAttributes();
    return Section(selectors, attributes);
}

List<Selector>* Parser::parseSelectors(MyString firstInput) {
    List<Selector>* selectors = new List<Selector>();
    selectors->append(Selector(firstInput));
    while (std::cin.good()) {
        MyString name = MyString::readString(",\n");
        name.trim();
        if (name.equals("{")) {
            break;
        }

        selectors->append(Selector(name));
    }
    return selectors;
}

List<Attribute>* Parser::parseAttributes() {
    List<Attribute>* attributes = new List<Attribute>();
    while (std::cin.good()) {
        MyString property = MyString::readString(":");
        property.trim();
        if (property.equals("}")) {
            break;
        }

        MyString value = MyString::readString(";\n");
        value.trim();

        attributes->append(Attribute(property, value));
    }
    return attributes;
}
