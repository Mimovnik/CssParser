#pragma once

#include "MyString.hpp"

class Attribute {
   private:
    MyString property;

    MyString value;

   public:
    Attribute();

    Attribute(MyString property, MyString value);
};