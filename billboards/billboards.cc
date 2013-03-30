#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(int argc, char **argv)
{

    int n,k;
    cin >> n;
    cin >> k;
    vector<int> C(n+1);
    long long sum=0;
    for (int i=0; i<n; i++)
    {
        cin >> C[i];
        sum+=C[i];
    }
    if (k>=n)
    {
        cout << sum << endl;
        return 0;
    }
    C[n]=0;
    deque<long long> minQ;
    vector<long long> dp(n+1);
    for (int i=0; i<k+1; i++)
    {
        dp[i]=C[i];
        while(!minQ.empty() && dp[i] <= dp[minQ.back()])
            minQ.pop_back();
        minQ.push_back(i);
    }
    for (int i=k+1; i< n; i++)
    {
        dp[i]=dp[minQ.front()]+C[i];
        while(!minQ.empty() && dp[i] <= dp[minQ.back()])
            minQ.pop_back();
        while(!minQ.empty() && minQ.front() <= i-k-1)
            minQ.pop_front();
        minQ.push_back(i);
    }
    dp[n]=dp[minQ.front()];
    cout << sum-dp[n] << endl;
    return 0;
}
