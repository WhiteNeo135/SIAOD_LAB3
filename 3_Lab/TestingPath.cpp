#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef vector <int> Vertex;

class Graph
{
public:
    Graph(vector<int>& StartCondition);
    bool HasASolution();
    void GetNextVert(Vertex& v, vector<Vertex>& next);
    void AStar();
    void PrintAns();
    char WhichMove(Vertex from, Vertex to);
    int CountTheHeuristic(Vertex v);

private:
    Vertex Start;
    Vertex Final;
    map<Vertex, int> f;
    map<Vertex, int> g;
    map<Vertex, Vertex> parents;
};

char Graph::WhichMove(Vertex from, Vertex to)
{
    int FirstSpacePosition = 0;
    int SecSpacePosition = 0;
    for (int i = 0; i < 16; i++)
    {
        if (from[i] == 0)
        {
            FirstSpacePosition = i;
            break;
        }
    }
    for (int i = 0; i < 16; i++)
    {
        if (to[i] == 0)
        {
            SecSpacePosition = i;
            break;
        }
    }

    switch (SecSpacePosition - FirstSpacePosition)
    {
        case 1:
            return 'R';
            break;
        case -1:
            return 'L';
            break;
        case 4:
            return 'D';
            break;
        case -4:
            return 'U';
        default:
            break;
    }
    return 0;
}

void Graph::PrintAns()
{
    int NumOfMoves = 0;
    string ReverseWay;
    Vertex tmp = Final;
    while (tmp != Start)
    {
        NumOfMoves++;
        Vertex prev = parents[tmp];
        ReverseWay += WhichMove(tmp, prev);
        tmp = prev;
    }

    cout << NumOfMoves << endl;
    for (int i = (int)ReverseWay.length() - 1; i >= 0; i--)
    {
        cout << ReverseWay[i];
    }

}

void Graph::AStar()
{
    if (!HasASolution())
    {
        cout << -1;
        exit(0);
    }
    set<pair<int, Vertex>> queue;
    set<Vertex> used;

    g.insert(pair<Vertex, int>(Start, 0));
    f.insert(pair<Vertex, int>(Start, g[Start] + CountTheHeuristic(Start)));
    queue.insert(pair<int, Vertex>(f[Start], Start));

    while (!queue.empty())
    {
        Vertex tmp = queue.begin()->second;
        queue.erase(queue.begin());

        if (tmp == Final)
        {
            PrintAns();
            exit(0);
        }

        used.insert(tmp);
        vector<Vertex> NextVert;
        GetNextVert(tmp, NextVert);
        for (auto v : NextVert)
        {
            int TentScore = g[tmp] + 1;
            if (used.find(v) != used.end() && TentScore >= g[v])
            {
                continue;
            }
            if (used.find(v) == used.end() || TentScore < g[v])
            {
                parents.insert(pair<Vertex, Vertex>(v, tmp));
                g.insert(pair<Vertex, int>(v, TentScore));
                f.insert(pair<Vertex, int>(v, g[v] + CountTheHeuristic(v)));
                if (queue.find({ f[v] - g[v],v }) == queue.end())
                    queue.insert(pair<int, Vertex>(f[v] - g[v], v));
            }
        }
    }
}

int Graph::CountTheHeuristic(Vertex v)
{
    int Heuristic = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int elem = v[i];
        if (elem == 0)
        {
            Heuristic += abs(3 - i / 4) + abs(3 - i % 4);
        }
        else
        {
            Heuristic += abs((elem - 1) / 4 - i / 4) + abs((elem - 1) % 4 - i % 4);
        }
    }
    return Heuristic;
}

void Graph::GetNextVert(Vertex& v, vector<Vertex>& next)
{
    int SpacePosition = 0;
    for (int i = 0; i < 16; i++)
    {
        if (v[i] == 0)
        {
            SpacePosition = i;
            break;
        }
    }
    int i = 0;
    if (SpacePosition < 15 && SpacePosition % 4 != 3)
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition + 1]);
        i++;
    }

    if (SpacePosition > 0 && SpacePosition % 4 != 0)
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition - 1]);
        i++;
    }

    if (SpacePosition >= 4)
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition - 4]);
        i++;
    }

    if (SpacePosition <= 11)
    {
        next.push_back(v);
        swap(next[i][SpacePosition], next[i][SpacePosition + 4]);
    }

}

Graph::Graph(vector<int>& g)
{
    int j = 1;
    for (auto i : g)
    {
        Start.push_back(i);
        Final.push_back(j);
        j++;
    }
    Final[15] = 0;
}

bool Graph::HasASolution()
{
    int inv = 0;
    for (int i = 0; i < 16; ++i)
        if (Start[i] != 0)
        {
            for (int j = 0; j < i; ++j)
            {
                if (Start[j] > Start[i])
                    ++inv;
            }
        }
    else
        {
            inv += 1 + i / 4;
        }
    if ((inv & 1) == 1)
    {
        return false;
    } else
    {
        return true;
    }
}