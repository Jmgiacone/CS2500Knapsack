#include "Item.h"

using namespace std;

int main()
{
  Item i;
  i.name = "Excalibur";
  i.value = 100000;
  i.weight = 1;
  i.ratio = i.value / i.weight;

  cout << i << endl;
  return 0;
}
