#include <bits/stdc++.h>

using namespace std;

void ReadFile(unordered_map<unsigned long long, unordered_set<unsigned long long>>& info, FILE* file)
{
    unsigned long long userId, productId;
    char* time[256];

    while(fscanf(file, "%llu,%llu,%[^\n]\n", &userId, &productId, time)==3)
    {
        if(info.find(userId)==info.end())
            info.insert(make_pair(userId, unordered_set<unsigned long long>()));
        
        unordered_set<unsigned long long>& currentUser=info[userId];
        currentUser.insert(productId);
    }
}

int main()
{
    vector<unsigned long long> condition1Users, condition2Users;
    unordered_map<unsigned long long, unordered_set<unsigned long long>> day1, day2;

    ReadFile(day1, fopen("day1.csv", "r"));
    ReadFile(day2, fopen("day2.csv", "r"));

    for(auto currentUser:day2)
    {
        auto userDay1=day1.find(currentUser.first);

        if(userDay1!=day1.end())
        {
            bool condition1=0, condition2=0;

            for(auto currentProduct=currentUser.second.begin(); 
                currentProduct!=currentUser.second.end()&&(!condition1||!condition2); currentProduct++)
            {
                auto pg = userDay1->second.find(*currentProduct);
                
                condition1=condition1||pg!=userDay1->second.end();
                condition2=condition2||pg==userDay1->second.end();
            }

            if(condition1)
                condition1Users.push_back(currentUser.first);
            
            if(condition2)
                condition2Users.push_back(currentUser.first);
        }
    }

    cout<<"Visited something on both days:\n";

    for(auto cu:condition1Users)
        cout<<cu<<"\n";
    
    cout<<"Visited a page on the 2d day and didn't visit it on the 1st:\n";

    for(auto cu:condition2Users)
        cout<<cu<<"\n";

    cin.ignore();
    cin.get();

    return 0;
}