#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <map>
#include <queue>
#include <list>

using namespace std;

vector<vector<int>> graph(6000,vector<int>(6000));
vector<int> visited(6000);
vector<string> string_input; 
int connected = 0;
bool comare();
void read_graph();
void explore();
void dfs();
void bfs();
int main()
{
    read_graph();
	dfs();
    bfs();
}

bool compare(string a, string b)
{
    int count = 0;
    for (int i = 0; i < 5;i++)
    {
        if (a[i] != b[i]) count++;
    }
    return count == 1;
}
void read_graph()
{
    ifstream in;
    in.open("C:/Users/ACER/Downloads/sgb-words.txt"); 
    string s;
    while (in >> s) string_input.push_back(s);
    for (int i = 0; i < string_input.size();i++)
    {
        for (int j = i + 1; j < string_input.size();j++)
        {
            if (compare(string_input[i],string_input[j]))
            {
                graph[i][j] = 1;
                graph[j][i] = 1; 
            } 
        }
    }
}
void explore(int node)
{
    visited[node] = 1;
    for (int i = 0; i < string_input.size(); i++)
    {
        if (graph[node][i] == 1)
            if (visited[i]!=1) {
                explore(i);
            }
    }
}
void dfs()
{
    for (int i = 0; i < string_input.size(); i++)
    {
        if (visited[i] == 0) 
        {
            connected++;
            explore(i);
        } 
    }
    cout << "So thanh phan lien thong cua do thi : "<< connected << endl;
}
int find (string s)
{
    for (int i = 0; i < string_input.size();i++)
    {
        if (s == string_input[i]) return i;
    }
    return -1;
}
void bfs()
{
    cout << "Vui long nhap vao 2 xau : ";
    string a, b; cin >> a >> b;
    queue<int> nodes;
    vector<int> father_nodes(6000);
    vector<int> dist(6000);
    bool check = true;
    int u = find(a), v = find(b);
    for (int i = 0; i < visited.size();i++) visited[i] = 0;
    nodes.push(u);
    while (nodes.size() != 0)
    {
        int node = nodes.front();
        visited[node] = 1;
        nodes.pop();
        for (int i = 0; i < 6000;i++)
        {
            if (graph[node][i] == 1 && visited[i] == 0) 
            {
                visited[i] = 1;
                nodes.push(i);
                father_nodes[i] = node;
                dist[i] = dist[u] + 1;
                if (i == v) 
                {   
                    while(nodes.size() != 0) nodes.pop();
                    check = false;
                    break;
                } 
            }
        }
    }
    if (check == true)
    {
        cout << "Khong the tim thay duong di!";
    }
    else 
    {
        cout << "Duong di tim duoc la : ";
        int next_node = father_nodes[v];
        vector<string> result;
        while (next_node != u) 
        {
            result.push_back(string_input[next_node]);
            next_node = father_nodes[next_node];
        } 
        cout << a << " ";
        for (int i = result.size() - 1; i >= 0;i--) cout << result[i] << " ";
        cout << b << endl; 
    } 
}
