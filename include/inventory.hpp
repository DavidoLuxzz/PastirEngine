#pragma once
#ifndef __inventory_hpp
#define __inventory_hpp

#include <vector>

enum Item {
    NONE,
    KEY,
    NIKES
};

class Inventory {
public:
    std::vector<Item> items;

    void add(Item);
    void remove(Item, int count);
    void removeAll(Item);
    bool contains(Item) const;
};


#endif
