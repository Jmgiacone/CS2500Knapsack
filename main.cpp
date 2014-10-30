#include <random>
#include <ctime>
#include "Item.h"
using namespace std;

const int MS_PER_SEC = 1000;
int greedyKnapsack(Item* items, const int n, const int w);
int quickSort(Item* items, const int start, const int end);
int partition(Item* items, const int start, const int end);
int dynamicKnapsack(const Item* items, const int n, const int w);
int bruteForceKnapsack(Item* items, int n, int w);
vector<vector<Item>> getcombos(Item* arr,int n, vector<Item> s, int w);

int main()
{
    int n, w, temp, numRepetitions, greedySolution, dynamicSolution, bruteSolution;
    float mean, variance, greedyDuration, greedyTotalDuration, dynamicDuration = 0, dynamicTotalDuration, bruteDuration, bruteTotalDuration = 0;
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
            wares[i].id = j;
            wares[i].ratio = wares[i].value / static_cast<float>(wares[i].weight);
            j += 2;
        }

        start = clock();
        greedySolution = greedyKnapsack(wares, n, w);
        end = clock();
        greedyDuration = MS_PER_SEC * ((end - start) / static_cast<float>(CLOCKS_PER_SEC));
        start = clock();
        dynamicSolution = dynamicKnapsack(wares, n, w);
        end = clock();
        dynamicDuration = MS_PER_SEC * ((end - start) / static_cast<float>(CLOCKS_PER_SEC));
        start = clock();
        bruteSolution = bruteForceKnapsack(wares, n, w);
        end = clock();
        bruteDuration = MS_PER_SEC * ((end - start) / static_cast<float>(CLOCKS_PER_SEC));

        cout << "The Greedy Method calculated an answer of " << greedySolution << " in " << greedyDuration << " ms." << endl;
        cout << "The Dynamic Method calculated an answer of " << dynamicSolution << " in " << dynamicDuration << " ms." << endl;
        cout << "The Brute-Force Method calculated an answer of " << bruteSolution << " in " << bruteDuration << " ms." << endl;

        greedyTotalDuration += greedyDuration;
        dynamicTotalDuration += dynamicDuration;
        bruteTotalDuration += bruteDuration;

        delete [] wares;
        delete [] values;

        wares = NULL;
        values = NULL;
    }

    cout << "The Greedy method had an average execution time of " << (greedyTotalDuration / numRepetitions) << " ms." << endl;
    cout << "The Dynamic method had an average execution time of " << (dynamicTotalDuration / numRepetitions) << " ms." << endl;
    cout << "The Brute-Force method had an average execution time of " << (bruteTotalDuration / numRepetitions) << " ms." << endl;
    cout << "The total execution time is "
            << (greedyTotalDuration + dynamicTotalDuration + bruteTotalDuration)
            << " ms." << endl;
    return 0;
}

int bruteForceKnapsack(Item* items, const int n, const int w)
{
    //In brute force knapsack, lists are implemented as vectors.
    //Declare ints to judge lists( and an create solution, which will be a list of all possible lists.

    int currentweight = 0;
	int currenthighvalue = 0;
	int currenthighvalueplace = 0;

    vector<vector<Item>> solution;

    for(int i = 0; i < n; i++)
    {
        if(items[i].weight <= w)
        {
            vector<Item> startlist;
            startlist.push_back(items[i]);
            vector<vector<Item>> subsolution = getcombos(items,n,startlist, w);
            solution.insert(solution.end(),subsolution.begin(),subsolution.end());
        }

        cout << "bFK in main loop " << i << ".\n";
    }

    int* value = new int[solution.size()];

    for(int j = 0; j < solution.size(); j++)
	{
        value[j] = 0;
	}


	for(int j = 0; j < solution.size(); j++)
	{
	    int c = 0;
	    for(int i = 0; i < solution[j].size(); i++)
	    {
            if(solution[j][c].weight <= w - currentweight)
            {
                value[j] += solution[j][c].value; //If it does, add value
                currentweight += solution[j][c].weight; // if it does add weight
            }
            else
            {
                cout << "Critical Error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                solution[j].erase(solution[j].begin()+c); // If it doesn’t fit, remove it.
                c--;
            }
            c++;
	    }
		//If the current list’s value is greater than the highest list so far, update the highest list to the current list.
        if(currenthighvalue < value[j])
	    {
  	      currenthighvalue = value[j];
	      currenthighvalueplace = j;
  	    }

		//Reset the weight for the next list
	    currentweight = 0;
	}
    delete [] value;
    return currenthighvalue;
}


vector<vector<Item>> getcombos(Item* arr,int n, vector<Item> s, int w)
{
//Creates a new list of lists of items to store all lists possible of the //remaining combinations of the item array and the current list.
	int currentweight = 0;

	for(int i = 0; i < s.size();i++)
    {
        currentweight += s[i].weight;
    }

	vector<vector<Item>> subsolution;

	if(n == s.size())
    {
        //Adds current list to the set of all possible lists, if it is a final //combination.
        subsolution.push_back(s);
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

            if(test1 == false)
            {
                //make a new list, add the state of the old list too it, //then add the new item and calls the function on it.
                if(arr[i].weight <= w - currentweight)
                {


                    vector<Item> startlist;
                    startlist.insert(startlist.end(),s.begin(),s.end());
                    startlist.push_back(arr[i]);
                    vector<vector<Item>> recsolution = getcombos(arr,n,startlist,w);
                    subsolution.insert(subsolution.end(),recsolution.begin(),recsolution.end());

                    test2 = true;
                }
            }

            if(test2 == false)
            {
                subsolution.push_back(s);
            }
		}
    }
    //This will return all combination of the array and the list after the //recursive call.
	return subsolution;
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

int quickSort(Item* items, const int start, const int end)
{
    int p;
    if(start < end)
    {
        p = partition(items, start, end);
        quickSort(items, start, p - 1);
        quickSort(items, p + 1, end);
    }
}

int greedyKnapsack(Item* items, const int n, const int w)
{
    int weight = 0, value = 0;
    quickSort(items, 0, n - 1);

    for(int i = 0; i < n; i++)
    {
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
                table[i][j] = table[i-1][j];
            }
        }
    }

    answer = table[n][w];

    for(int i = 0; i <= n; i++)
    {
        delete [] table[i];
    }
    delete [] table;
    table = NULL;

    return answer;
}
