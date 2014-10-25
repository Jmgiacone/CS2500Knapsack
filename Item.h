#ifndef ITEM_H
#define ITEM_H

#include <iostream>
struct Item
{
  std::string name;
  float weight, value, ratio;

};

std::ostream& operator << (std::ostream& out, Item i)
{
  out << "[" << i.name << ": Value $" << i.value << ", Weight " << i.weight << "lb, Ratio " << i.ratio << " $/lb]";
  return out;
}
#endif // ITEM_H
