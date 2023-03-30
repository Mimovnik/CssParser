#include "Parser.hpp"

#include <iostream>

#include "MyString.hpp"

void Parser::parse() {
    while (std::cin.good()) {
        MyString input = MyString::readString(",{\n");

        input.trim();
        if (input.equals("????")) {
            std::cout << "Parsecommands" << std::endl;
            parseCommands();
        } else if (input.equals("{")) {
        }
    }
}

void Parser::parseCommands() {
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
