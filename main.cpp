#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include "Item.h"
using namespace std;

int greedyKnapsack(const Item* list, const int n, const int w);
void quickSort(Item* items, const int start, const int end);
int partition(Item* items, const int start, const int end);
int dynamicKnapsack(const Item* items, const int n, const int w);
int bruteForceKnapsack(Item* items, int n, int w);
int getcombos(Item* arr,int n, vector<Item> s, int w, int cw, int v, int vh);
void initItems(Item* items, int w, normal_distribution<float>* rng, default_random_engine &randEngine);

const int NUM_OF_INPUTS = 340, NUM_OF_LOOPS_EACH = 15, STARTING_INPUT_SIZE = 1525, CAPACITY = 10000, ARBITRARY_N = 100;
const float ARBITRARY_MEAN = CAPACITY / 2.0, ARBITRARY_VARIANCE = ARBITRARY_MEAN,
        STARTING_VARIANCE = ARBITRARY_MEAN / static_cast<float>(NUM_OF_INPUTS), MS_PER_SEC = 1000;
const string FILENAME = "C:\\Users\\Jordan\\Documents\\Github Repos\\CS2500Knapsack\\fullTestingSuiteGreedy10000.txt";

int main()
{
    ofstream outputFile;
    chrono::high_resolution_clock::time_point start, end, elapsed;
    int n = STARTING_INPUT_SIZE, greedySolution, dynamicSolution, bruteSolution;
    double variance = STARTING_VARIANCE, greedyDuration = 0, greedyTotalDuration = 0, dynamicDuration = 0,
            dynamicTotalDuration = 0, bruteDuration = 0, bruteTotalDuration = 0, greedyValue = 0, totalGreedyValue = 0;
    Item* wares = NULL;
    default_random_engine randEngine(time(NULL));

    normal_distribution<float>* rng = new normal_distribution<float>(ARBITRARY_MEAN, sqrt(ARBITRARY_VARIANCE));
    outputFile.open(FILENAME.c_str());

    auto totalStart = chrono::high_resolution_clock::now();
    outputFile << "VARYING SIZE OF INPUT\n"
            "*********************\nCapacity: " << CAPACITY << " Starting Input: " << n
            << " Mean: " << ARBITRARY_MEAN << " Variance: " << ARBITRARY_VARIANCE << endl << endl;
    for(int y = 0; y < NUM_OF_INPUTS; y++)
    {
        for(int x = 0; x < NUM_OF_LOOPS_EACH; x++)
        {
            wares = new Item[n];
            initItems(wares, n, rng, randEngine);

            cout << "Size of input: " << n << " elements. Run #" << (x + 1) << "/" << NUM_OF_LOOPS_EACH << endl;

            start = chrono::high_resolution_clock::now();
            dynamicSolution = dynamicKnapsack(wares, n, CAPACITY);
            end = chrono::high_resolution_clock::now();
            dynamicDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            start = chrono::high_resolution_clock::now();
            greedySolution = greedyKnapsack(wares, n, CAPACITY);
            end = chrono::high_resolution_clock::now();
            greedyDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            if(n <= 1500)
            {
                start = chrono::high_resolution_clock::now();
                bruteSolution = bruteForceKnapsack(wares, n, CAPACITY);
                end = chrono::high_resolution_clock::now();
                bruteDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            greedyValue = (static_cast<float>(greedySolution) / dynamicSolution);
            totalGreedyValue += greedyValue;

            greedyTotalDuration += greedyDuration;
            dynamicTotalDuration += dynamicDuration;
            bruteTotalDuration += bruteDuration;

            delete[] wares;
            wares = NULL;
        }

        outputFile << "Size of Input: " << n << endl;
        outputFile << "The Greedy method had an average execution time of " << (greedyTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The Dynamic method had an average execution time of " << (dynamicTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The Brute-Force method had an average execution time of " << (bruteTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The average value of the greedy solution is " << 100 * (totalGreedyValue / NUM_OF_LOOPS_EACH) << "%.\n" << endl;

        greedyTotalDuration = 0;
        dynamicTotalDuration = 0;
        bruteTotalDuration = 0;
        totalGreedyValue = 0;

        n += 25;
    }

    delete rng;

    outputFile << "\nVARYING VARIANCE"
            "\n****************\nCapacity: " << CAPACITY << " Input Size: " << ARBITRARY_N << " Mean: " << ARBITRARY_MEAN
            << " Starting Variance: " << variance << endl;
    for(int y = 0; y < NUM_OF_INPUTS; y++)
    {
        rng = new normal_distribution<float>(ARBITRARY_MEAN, sqrt(variance));
        for(int x = 0; x < NUM_OF_LOOPS_EACH; x++)
        {
            n = ARBITRARY_N;
            wares = new Item[n];
            initItems(wares, n, rng, randEngine);

            cout << "Variance: " << variance << " Run #" << (x + 1) << "/" << NUM_OF_LOOPS_EACH << endl;
            start = chrono::high_resolution_clock::now();
            dynamicSolution = dynamicKnapsack(wares, n, CAPACITY);
            end = chrono::high_resolution_clock::now();
            dynamicDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            start = chrono::high_resolution_clock::now();
            greedySolution = greedyKnapsack(wares, n, CAPACITY);
            end = chrono::high_resolution_clock::now();
            greedyDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            if(n <= 1500)
            {
                start = chrono::high_resolution_clock::now();
                bruteSolution = bruteForceKnapsack(wares, n, CAPACITY);
                end = chrono::high_resolution_clock::now();
                bruteDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            }

            greedyValue = (static_cast<float>(greedySolution) / bruteSolution);
            totalGreedyValue += greedyValue;

            greedyTotalDuration += greedyDuration;
            dynamicTotalDuration += dynamicDuration;
            bruteTotalDuration += bruteDuration;

            delete[] wares;
            wares = NULL;
        }

        outputFile << "Variance: " << variance << endl;
        outputFile << "The Greedy method had an average execution time of " << (greedyTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The Dynamic method had an average execution time of " << (dynamicTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The Brute-Force method had an average execution time of " << (bruteTotalDuration / NUM_OF_LOOPS_EACH) << " ms." << endl;
        outputFile << "The average value of the greedy solution is " << 100 * (totalGreedyValue / NUM_OF_LOOPS_EACH) << "%.\n" << endl;

        greedyTotalDuration = 0;
        dynamicTotalDuration = 0;
        bruteTotalDuration = 0;
        totalGreedyValue = 0;

        variance += STARTING_VARIANCE;
    }

    auto totalEnd = chrono::high_resolution_clock::now();
    auto totalElapsed = totalEnd - totalStart;
    outputFile << "Total Execution Time: " << chrono::duration_cast<std::chrono::milliseconds>(totalElapsed).count() << " ms." << endl;
    outputFile.close();
    return 0;
}

void initItems(Item* wares, int n, normal_distribution<float>* rng, default_random_engine &randEngine)
{
    //Make an array of size 2n to hold both the weight and value
    int* values = new int[2 * n];
    float temp;

    for (int i = 0; i < 2 * n; i++)
    {
        //Do-while to ensure that the values can't be negative
        do
        {
            //Generate an integer
            temp = static_cast<int>((*rng)(randEngine));
        }
        while (temp <= 0);
        values[i] = temp;
    }

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        //Assign first to the value
        wares[i].value = values[j];
        //Assign the second to the weight
        wares[i].weight = values[j + 1];
        wares[i].id = j;
        wares[i].ratio = wares[i].value / static_cast<float>(wares[i].weight);
        j += 2;
    }

    delete[] values;

    values = NULL;
}

int bruteForceKnapsack(Item* items, const int n, const int w)
{
    //In brute force knapsack, lists are implemented as vectors.
    //Declare ints to judge lists( and an create solution, which will be a list of all possible lists.

    vector<Item> solution;
    return getcombos(items,n,solution, w, 0, 0,0);

}

int getcombos(Item* arr,int n, vector<Item> s, int w, int cw, int v, int vh)
{

	if(n == s.size())
    {
        //FINAL CHECK
        if(v > vh)
        {
            vh = v;
        }
    }
    else
    {
        //Continue to add remaining items to the list.
		for(int i = 0; i < n; i++)
		{
			bool test1 = false;
			bool test2 = false;

			for(int j = 0; j < s.size(); j++)
            {
                Item x = s.at(j);
                Item y = arr[i];

                if(x == y)
                {
                    test1 = true;
                }
            }

            if(!test1)
            {
                //make a new list, add the state of the old list too it, //then add the new item and calls the function on it.
                if(arr[i].weight <= w - cw)
                {
                    cw += arr[i].weight;
                    v += arr[i].value;
                    vector<Item> startlist;
                    startlist.insert(startlist.end(),s.begin(),s.end());
                    startlist.push_back(arr[i]);
                    vh = getcombos(arr,n,startlist,w,cw,v, vh);

                    cw -= arr[i].weight;
                    v -= arr[i].value;

                    test2 = true;
                }
            }

            if(!test2)
            {
                //FINAL CHECK
                if(v > vh)
                {
                    vh = v;
                }
            }
		}
    }

    //This will return all combination of the array and the list after the //recursive call.
	return vh;
}

int partition(Item* items, int start, int end)
{
    int pivot, i = start - 1;
    Item pivotItem = items[end], temp;

    for(int j = start; j < end; j++)
    {
        if(items[j].ratio >= pivotItem.ratio)
        {
            i++;
            temp = items[j];
            items[j] = items[i];
            items[i] = temp;
        }
    }
    pivot = i + 1;

    temp = items[end];
    items[end] = items[pivot];
    items[pivot] = temp;

    return pivot;
}

void quickSort(Item* items, const int start, const int end)
{
    int p;
    if(start < end)
    {
        p = partition(items, start, end);
        quickSort(items, start, p - 1);
        quickSort(items, p + 1, end);
    }
}

int greedyKnapsack(const Item* list, const int n, const int w)
{
    Item* items = new Item[n];

    //Don't want to change the source list, copy it into another one
    for(int i = 0; i < n; i++)
    {
        items[i] = list[i];
    }

    int weight = 0, value = 0;

    //This quicksort will sort the items from largest to smallest
    quickSort(items, 0, n - 1);

    for(int i = 0; i < n; i++)
    {
       //Take as many items off the top as will fit
       if(weight + items[i].weight <= w)
       {
           weight += items[i].weight;
           value += items[i].value;
       }
    }

    return value;
}

int dynamicKnapsack(const Item* items, const int n, const int w)
{
    //Make a table if [n+1] x [w+1] to account for the row and column of zeros
    int** table = new int*[n + 1], answer;

    //Initialize rows and set first to zero
    for(int i = 0; i <= n; i++)
    {
        table[i] = new int[w + 1];
        table[i][0] = 0;
    }

    //Initialize columns and set first to zero
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
                //Take the larger option between (cell directly above, or the cell directly above and to the left weight[i] spacees.
                //Add value[i] to that number
                table[i][j] = max(table[i-1][j], table[i-1][j - items[i-1].weight] + items[i-1].value);
            }
            else
            {
                //Take value above
                table[i][j] = table[i-1][j];
            }
        }
    }

    //Answer will be bottom-right cell
    answer = table[n][w];

    for(int i = 0; i <= n; i++)
    {
        delete [] table[i];
    }
    delete [] table;
    table = NULL;

    return answer;
}
