#include "Attribute.hpp"

Attribute::Attribute() {}

Attribute::Attribute(MyString property, MyString value) {
    this->property = property;
    this->value = value;
}