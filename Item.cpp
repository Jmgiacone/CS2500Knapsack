#include "Item.h"

Item::Item()
{
    std::string name = "";
    int weight = 0, value = 0;
    float ratio = -1;
}

std::ostream& operator << (std::ostream& out, Item i)
{
    out << "[" << i.name << ": Value $" << i.value << ", Weight " << i.weight << "lb, Ratio " << i.ratio << " $/lb]";
    return out;
}