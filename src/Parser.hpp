#pragma once

#include "MyString.hpp"

class Parser {
   private:
    void parseCommands();

    void parseSection(MyString string);

    void parseSelectors(MyString firstSelector);

    void parseAttributes();

   public:
    void parse();
};