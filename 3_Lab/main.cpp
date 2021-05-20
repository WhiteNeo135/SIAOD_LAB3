#include <bits/stdc++.h>
#include "SearchString.cpp"
#include "FindPath.cpp"
#include "TestingPath.cpp"

int main()
{
    char txt[] = "AABAADABAA";
    char pat[] = "ABAAC";
    KMPSearch(pat, txt);

    cout<<endl;

    string text="ABABDABACDABABCABAB";
    string pattern="acdba";

    BM(text,pattern);

    int table[16]={12,6,9,1,5,15,8,2,7,10,14,11,13,4,3,0};

    cout<<endl;
    vector<int> g;
    for (auto i: table)
    {
        g.push_back(i);
    }
    Graph graph(g);
    graph.AStar();

    return 0;

}

