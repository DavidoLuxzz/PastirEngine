#pragma once
#ifndef __inventory_hpp
#define __inventory_hpp

#include <vector>

enum Item {
    NONE,
    KEY,
    NIKES
};

class Player;

class Inventory {
public:
    std::vector<Item> items;
    Player* bearer;

    Inventory() = default;
    Inventory(Player* bearer);

    void add(Item);
    void remove(Item, int count);
    void removeAll(Item);
    bool contains(Item) const;

    static constexpr const char* itemName(Item i);
};


#endif
