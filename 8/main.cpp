#include <bits/stdc++.h>

using namespace std;

vector<pair<long long, long long>> v;
set<pair<long long, long long>> s;

int main()
{
    long long n, c, k;

    cin>>n>>c;

    cin.ignore();

    string line;
    getline(cin, line);
    stringstream ss(line);
    long long x;

    while (ss >> x)
        v.push_back(make_pair(0, x));

    k=v.size();

    getline(cin, line);

    stringstream ss1(line);

    for(auto i=0; i<k; i++)
    {
        ss1>>x;
        v[i].first=x;
        v[i].second-=x;
    }

    sort(v.begin(), v.end());

    long long cl=0;

    for(auto i=0; i<n; i++)
    {
        while(cl<k&&v[cl].first<=c)
        {
            s.insert(make_pair(v[cl].second, v[cl].first));
            cl++;
        }

        if(s.empty())
        {
            cout<<c;
            cin.get();
            return 0;
        }

        auto it=s.end();
        it--;

        if(it->first<=0)
        {
            cout<<c;
            cin.get();
            return 0;
        }

        c+=it->first;
        s.erase(it);
    }

    cout<<c;
    cin.get();

    return 0;
}