#pragma once

#include "List.hpp"
#include "MyString.hpp"
#include "Section.hpp"
#include "Selector.hpp"
#include "Attribute.hpp"

class Parser {
   private:
    List<Section> sections;

    void parseCommands();

    Section parseSection(MyString firstInput);
    
    List<Selector>* parseSelectors(MyString firstSelector);

    List<Attribute>* parseAttributes();

   public:
    void parse();
};