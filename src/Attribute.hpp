#pragma once

#include "String.hpp"

class Attribute {
   private:
    String property;

    String value;

   public:
    Attribute();

    Attribute(String property, String value);
};