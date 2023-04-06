#pragma once
#include "Attribute.hpp"
#include "List.hpp"
#include "Section.hpp"
#include "Selector.hpp"
#include "String.hpp"

class Parser {
   private:
    List<Section> sections;

    void parseCommands();

    void parseOperations(String& firstArg, String& secondArg, String& thirdArg);

    Section* parseSection(String firstInput, bool endedOnBlockStart);

    List<Selector>* parseSelectors(String firstSelector);

    List<Attribute>* parseAttributes();

    class FlagString {
       private:
        String string;

        bool flag = false;

       public:
        FlagString(FlagString&& other);

        FlagString& operator=(FlagString&& other);

        FlagString(String string, bool flag);

        String& getString();

        bool getFlag();

        static FlagString readString(const char* endChars,
                                      const char* flagChars,
                                      int defaultReadLength = 64);
    };

   public:
    void parse();
};