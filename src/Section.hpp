#pragma once

#include "Attribute.hpp"
#include "List.hpp"
#include "Selector.hpp"

class Section {
   private:
    List<Selector>* selectors = nullptr;

    List<Attribute>* attributes = nullptr;

   public:
    Section();

    ~Section();

    Section(const Section& other);

    Section& operator=(const Section& other);

    List<Selector>* getSelectors();

    List<Attribute>* getAttributes();

    Section(List<Selector>* selectors, List<Attribute>* attributes);
};