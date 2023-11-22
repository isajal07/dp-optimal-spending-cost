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

// Recursive function to compute the optimal spending cost and store choices
int OPT(int week, int city, vector<vector<int>> &memo, vector<vector<int>> &choices)
{
    // Base case
    if (week == 1)
    {
        choices[week][city] = city;
        return (city == 0) ? A[0] : B[0];
    }

    // Check if the result is already memoized
    if (memo[week][city] != -1)
    {
        return memo[week][city];
    }

    int diffCity = (city == 0) ? 1 : 0;

    // Recursive cases
    int sameCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, city, memo, choices) - Da) : (B[week - 1] + OPT(week - 1, city, memo, choices) - Db);
    int diffCityCost = (city == 0) ? (A[week - 1] + OPT(week - 1, diffCity, memo, choices) + F) : (B[week - 1] + OPT(week - 1, diffCity, memo, choices) + F);

    // Store choices for reconstruction
    if (sameCityCost < diffCityCost)
    {
        choices[week][city] = city;
    }
    else
    {
        choices[week][city] = diffCity;
    }

    // Memoize the result
    memo[week][city] = min(sameCityCost, diffCityCost);

    return memo[week][city];
}

int main()
{
    // Memoization table
    vector<vector<int>> memo(n + 1, vector<int>(2, -1));

    // Table to store choices for optimal solution reconstruction
    vector<vector<int>> choices(n + 1, vector<int>(2, -1));

    // Find the optimal spending cost
    int min_cost = min(OPT(n, 0, memo, choices), OPT(n, 1, memo, choices));

    // Write results to output file
    ofstream outFile("spendcost_pc_out.txt");
    if (!outFile.is_open())
    {
        cerr << "Unable to open output file." << endl;
        return 1;
    }

    outFile << "Table with Optimal Values for Subproblems and Choices:" << endl;
    cout << "Table with Optimal Values for Subproblems and Choices:" << endl;

    for (int i = 1; i <= n; ++i)
    {
        string cho0 = choices[i][0] == 0 ? "A" : "B";
        string cho1 = choices[i][1] == 0 ? "A" : "B";
        outFile << "Week " << i << ": City A - $" << OPT(i, 0, memo, choices) << " (Choice: " << cho0 << "), City B - $" << OPT(i, 1, memo, choices) << " (Choice: " << cho1 << ")" << endl;
        cout << "Week " << i << ": City A - $" << OPT(i, 0, memo, choices) << " (Choice: " << cho0 << "), City B - $" << OPT(i, 1, memo, choices) << " (Choice: " << cho1 << ")" << endl;
    }

    outFile << endl
            << "Optimal Spending Cost: $" << min_cost << endl;
    cout << endl
         << "Optimal Spending Cost: $" << min_cost << endl;

    outFile.close();

    return 0;
}
