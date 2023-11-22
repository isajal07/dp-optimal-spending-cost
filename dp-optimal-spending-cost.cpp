#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

const int MAX_N = 100;

int F = 200;  // fuel cost
int Da = 500; // discount for city A
int Db = 400; // discount for city B

vector<int> A = {3500, 1500, 2000, 1500}; // City A salaries
vector<int> B = {2500, 1000, 3500, 2000}; // City B salaries

int n = A.size(); // Size of the vector array

// Recursive function to compute the optimal spending cost
int OPT(int week, int city, vector<vector<int>> &memo)
{
    // Base case
    if (week == 1)
    {
        return (city == 0) ? A[0] : B[0];
    }

    // Check if the result is already memoized
    if (memo[week][city] != -1)
    {
        return memo[week][city];
    }

    int diffCity = (city == 0) ? 1 : 0;

    // Recursive cases
    int sameCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, city, memo) - Da) : (B[week - 1] + OPT(week - 1, city, memo) - Db);
    int diffCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, diffCity, memo) + F) : (B[week - 1] + OPT(week - 1, diffCity, memo) + F);

    // Memoize the result
    memo[week][city] = min(sameCityCost, diffCityCost);

    return memo[week][city];
}

int main()
{
    // Memoization table
    vector<vector<int>> memo(n + 1, vector<int>(2, -1));

    // Find the optimal spending cost
    int minCost = min(OPT(n, 0, memo), OPT(n, 1, memo));

    cout << "Table with Optimal Values for Subproblems:" << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Week " << i << ": City A - $" << OPT(i, 0, memo) << ", City B - $" << OPT(i, 1, memo) << endl;
    }

    cout << endl
         << "Optimal Spending Cost: $" << minCost << endl;

    return 0;
}
