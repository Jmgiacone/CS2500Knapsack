#include <random>
#include <ctime>
#include "Item.h"
using namespace std;

int main()
{
    int n;
    float mean, stdev, temp;
    cout << "How many elements in the array? ";
    cin >> n;
    cout << "What should the mean of the values be? ";
    cin >> mean;
    cout << "What should the standard deviation of the values be? ";
    cin >> stdev;

    Item* wares = new Item[n];
    float* values = new float[2*n];
    normal_distribution<float> rng(mean, stdev);
    default_random_engine randEngine(time(NULL));

    for(int i = 0; i < 2*n; i++)
    {
        do
        {
            temp = rng(randEngine);
        }
        while(temp <= 0);

        values[i] = temp;
    }

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        wares[i].name = "Item";
        wares[i].value = values[j];
        wares[i].weight = values[j + 1];
        wares[i].ratio = wares[i].value / wares[i].weight;
        j+= 2;
    }

    for(int i = 0; i < n; i++)
    {
        cout << wares[i] << endl;
    }
    
    return 0;
}
