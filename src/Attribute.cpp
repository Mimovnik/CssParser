#include "Attribute.hpp"

Attribute::Attribute() {}

Attribute::Attribute(String property, String value) {
    this->property = property;
    this->value = value;
}