#ifndef ITEM_H
#define ITEM_H

#include <iostream>
struct Item
{
  int weight = 0, value = 0;
  float ratio = -1;

};

std::ostream& operator << (std::ostream& out, Item i)
{
  out << "[" << i.name << ": Value $" << i.value << ", Weight " << i.weight << "lb, Ratio " << i.ratio << " $/lb]";
  return out;
}
#endif // ITEM_H
