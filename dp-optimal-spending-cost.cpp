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
int OPT(int week, int city, const vector<int> &A, const vector<int> &B, vector<vector<int>> &memo, int F, int Da, int Db)
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
    int sameCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, city, A, B, memo, F, Da, Db) - Da) : (B[week - 1] + OPT(week - 1, city, A, B, memo, F, Da, Db) - Db);
    int diffCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, diffCity, A, B, memo, F, Da, Db) + F) : (B[week - 1] + OPT(week - 1, diffCity, A, B, memo, F, Da, Db) + F);

    // Memoize the result
    memo[week][city] = min(sameCityCost, diffCityCost);

    return memo[week][city];
}

// Function to print the optimal solution
void printOPTs(int week, int city, const vector<int> &A, const vector<int> &B, vector<vector<int>> &memo, int F, int Da, int Db)
{
    if (week == 1)
    {
        cout << "Week 1: City " << (city == 0 ? 'A' : 'B') << endl;
        return;
    }

    int diffCity = (city == 0) ? 1 : 0;
    int sameCityCost = (city == 0) ? (A[week - 1] + memo[week - 1][city] - Da) : (B[week - 1] + memo[week - 1][city] - Db);
    int diffCityCost = (city == 0) ? (A[week - 1] + memo[week - 1][diffCity] + F) : (B[week - 1] + memo[week - 1][diffCity] + F);

    if (memo[week][city] == sameCityCost)
    {
        printOPTs(week - 1, city, A, B, memo, F, Da, Db);
        cout << "Week " << week << ": City " << (city == 0 ? 'A' : 'B') << endl;
    }
    else
    {
        printOPTs(week - 1, diffCity, A, B, memo, F, Da, Db);
        cout << "Week " << week << ": City " << (diffCity == 0 ? 'A' : 'B') << endl;
    }
}

int main()
{
    // Memoization table
    vector<vector<int>> memo(n + 1, vector<int>(2, -1));

    // Find the optimal spending cost
    int min_cost = min(OPT(n, 0, A, B, memo, F, Da, Db), OPT(n, 1, A, B, memo, F, Da, Db));

    // Print the optimal solution
    cout << "Optimal Delivery Plan:" << endl;
    printOPTs(n, (min_cost == memo[n][0]) ? 0 : 1, A, B, memo, F, Da, Db);

    // Write results to output file
    ofstream outFile("spendcost_pd_out.txt");
    if (!outFile.is_open())
    {
        cerr << "Unable to open output file." << endl;
        return 1;
    }

    outFile << "Table with Optimal Values for Subproblems:" << endl;
    cout << "Table with Optimal Values for Subproblems:" << endl;
    for (int i = 1; i <= n; ++i)
    {
        outFile << "Week " << i << ": City A - $" << OPT(i, 0, A, B, memo, F, Da, Db) << ", City B - $" << OPT(i, 1, A, B, memo, F, Da, Db) << endl;
        cout << "Week " << i << ": City A - $" << OPT(i, 0, A, B, memo, F, Da, Db) << ", City B - $" << OPT(i, 1, A, B, memo, F, Da, Db) << endl;
    }

    outFile << endl
            << "Optimal Spending Cost: $" << min_cost << endl;
    cout << endl
         << "Optimal Spending Cost: $" << min_cost << endl;

    outFile.close();

    return 0;
}
