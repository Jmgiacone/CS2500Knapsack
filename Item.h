#ifndef ITEM_H
#define ITEM_H

#include <iostream>
struct Item
{
    int weight = 0, value = 0, id = 0;
    float ratio = -1;

    const int GetMember() const
    {
        return(this->id);
    }


    //bool operator== (const Item &L, Item &R);
};

bool operator== (const Item &L, Item &R)
{
    return(L.GetMember() == R.GetMember());
}

#endif // ITEM_H
