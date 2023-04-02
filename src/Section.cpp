#include "Section.hpp"

Section::Section() {}

Section::Section(List<Selector>* selectors, List<Attribute>* attributes) {
    this->selectors = selectors;
    this->attributes = attributes;
}