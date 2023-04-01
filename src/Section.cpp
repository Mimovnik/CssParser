#include "Section.hpp"

Section::Section() {}

Section::Section(const Section& other) {}

Section& Section::operator=(const Section& other) {
    return *this;
}

Section::Section(Section&& other) {}

Section& Section::operator=(Section&& other) {
    return *this;
}

Section::Section(List<Selector>* selectors, List<Attribute>* attributes) {
    this->selectors = selectors;
    this->attributes = attributes;
}