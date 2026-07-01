#include <inventory.hpp>
#include <iostream>

constexpr const char* Inventory::itemName(Item i) {
    constexpr const char* names[] = {"None", "Key", "Nike Jordans", "TBD", "TBD"};
    return names[i];
}

void Inventory::add(Item i) {
    items.push_back(i);
    std::cout << "Acquired an item: " << itemName(i) << std::endl;
}
void Inventory::remove(Item item, int count) { // valjda radi, mozda i ne
    // int indices[count]; int n=0;
    for (int i=0; i<items.size(); i++) {
        if (count<=0) return;
        if (items[i] == item) {
            items.erase(items.begin()+i);
            i--;
            count--;
        }
    }
}
void Inventory::removeAll(Item item) {
    for (int i=0; i<items.size(); i++) {
        if (items[i] == item) {
            items.erase(items.begin()+i);
            i--;
        }
    }
}
bool Inventory::contains(Item item) const {
    for (Item i : items) {
        if (i==item) return true;
    }
    return false;
}