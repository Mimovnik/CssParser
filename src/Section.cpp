#include "Section.hpp"

Section::Section() {}

Section::~Section() {
    delete selectors;
    delete attributes;
}

Section::Section(const Section& other) {
    delete selectors;
    selectors = other.selectors;
    delete attributes;
    attributes = other.attributes;
}

Section& Section::operator=(const Section& other) {
    delete selectors;
    selectors = other.selectors;
    delete attributes;
    attributes = other.attributes;
    return *this;
}

List<Selector>* Section::getSelectors() { return selectors; }

List<Attribute>* Section::getAttributes() { return attributes; }

Section::Section(List<Selector>* selectors, List<Attribute>* attributes) {
    this->selectors = selectors;
    this->attributes = attributes;
}