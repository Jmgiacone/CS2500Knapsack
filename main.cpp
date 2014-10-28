#include <random>
#include <ctime>
#include "Item.h"
using namespace std;

int greedyKnapsack(Item* items, int n, int w);
int dynamicKnapsack(const Item* items, const int n, const int w);
int bruteForceKnapsack(Item* items, int n, int w);

int main()
{
    int n, w, temp, numRepetitions;
    float mean, variance, duration, totalDuration = 0;
    clock_t start, end;
    Item* wares = NULL;
    int* values = NULL;
    default_random_engine randEngine(time(NULL));


    cout << "What is the capacity of the knapsack? ";
    cin >> w;
    cout << "How many elements in the array? ";
    cin >> n;
    cout << "What should the mean of the values be? ";
    cin >> mean;
    cout << "What should the variance of the values be? ";
    cin >> variance;
    cout << "How many repetitions should be performed? ";
    cin >> numRepetitions;

    normal_distribution<float> rng(mean, sqrt(variance));
    for(int x = 0; x < numRepetitions; x++)
    {
        wares = new Item[n];
        values = new int[2 * n];

        for (int i = 0; i < 2 * n; i++)
        {
            do
            {
                temp = static_cast<int>(rng(randEngine));
            }
            while (temp <= 0);

            values[i] = temp;
        }

        int j = 0;
        for (int i = 0; i < n; i++)
        {
            wares[i].value = values[j];
            wares[i].weight = values[j + 1];
            wares[i].ratio = wares[i].value / static_cast<float>(wares[i].weight);
            j += 2;
        }

        start = clock();
        for(int i = 0; i < n; i++)
        {
            cout << wares[i] << endl;
        }
        cout << "The answer via the dynamic method is: " << dynamicKnapsack(wares, n, w) << endl;
        end = clock();
        duration = (end - start) / static_cast<float>(CLOCKS_PER_SEC);
        cout << "This operation took " << duration << "ms" << endl;
        totalDuration += duration;

        delete [] wares;
        delete [] values;

        wares = NULL;
        values = NULL;
    }

    cout << "The average execution time is: " << (duration / numRepetitions) << "ms" << endl;
    return 0;
}

int dynamicKnapsack(const Item* items, const int n, const int w)
{
    int** table = new int*[n + 1], answer;

    for(int i = 0; i <= n; i++)
    {
        table[i] = new int[w + 1];
        table[i][0] = 0;
    }

    for(int i = 0; i <= w; i++)
    {
        table[0][i] = 0;
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= w; j++)
        {
            if(items[i-1].weight <= j)
            {
                table[i][j] = max(table[i-1][j], table[i-1][j - items[i-1].weight] + items[i-1].value);
            }
            else
            {
                table[i][j] = table[i][j-1];
            }
        }
    }

    answer = table[n][w];

    for(int i = 0; i <= n; i++)
    {
        delete [] table[i];
    }
    delete [] table;

    return answer;
}
