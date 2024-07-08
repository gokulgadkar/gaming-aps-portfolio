#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int optimizedBundle(int W, const vector<int>& wt, const vector<int>& val, const vector<int>& qty, int n)
{
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; ++i)
    {
        vector<int> new_dp(dp);

        for (int w = wt[i]; w <= W; ++w)
        {
            for (int k = 1; k <= qty[i] && k * wt[i] <= w; ++k)
            {
                new_dp[w] = max(new_dp[w], dp[w - k * wt[i]] + k * val[i]);
            }
        }

        dp = new_dp;
    }

    return dp[W];
}


vector<int> ratioSpending(vector<int> &spend)
{

    vector<int> result;
    int sum=0;

    for(int i: spend)
    {
        sum+=i;
    }
    for(int i: spend)
    {
        result.push_back((i*10)/sum);
    }

    return result;



}
int main()
{
    int W = 10;
    vector<int> wt = {2, 3, 4}; //real world values of item
    vector<int> spending = {3000, 4000, 5000};
    vector<int> qty = {3, 2, 1};
    int n = wt.size();

    vector<int> val = ratioSpending(spending);
    int maxVal = boundedKnapsack(W, wt, val, qty, n);

    cout << "Maximum value in Knapsack = " << maxVal << endl;

    return 0;
}

