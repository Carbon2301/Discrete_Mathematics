#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <map>
#include <stack>
#include <queue>
#include <list>

using namespace std;

vector<vector<int>> graph(6000,vector<int>(6000));
vector<vector<int>> reverse_graph(6000,vector<int>(6000));
vector<vector<int>> connected_components;
vector<int> visited(6000);
vector<int> temp;
vector<string> string_input; 
stack<int> nodes;
int connected = 0;
bool comare();
void read_graph();
void explore();
void dfs();
void bfs();
void print_connected();
bool compare();
int main()
{
    read_graph();
	dfs();
    print_connected();
    bfs();
}
int count_char_in_string(char c, string s)
{
    int count = 0;
    for (auto i : s) if (i == c) count++;
    return count;
}
bool compare(string a, string b)
{
    int count = 0;
    map<char,int> count_char;
    for (int i = 1; i < 5;i++)
    {
        auto it = count_char.find(a[i]);
        if (it == count_char.end()) count_char[a[i]] = 1;
        else it->second = it->second + 1;
    }
    for (auto i : count_char) 
    {
        if (i.second > count_char_in_string(i.first,b)) return false;
    }
    return true;
}
void read_graph()
{
    //if (compare("dross","drooo")) cout << 1;
    //else cout << 0;
    int count = 0;
    ifstream in;
    in.open("C:/Users/ACER/Downloads/sgb-words.txt"); 
    string s;
    while (in >> s) string_input.push_back(s);
    cout << endl;
    for (int i = 0; i < string_input.size();i++)
    {
        for (int j = 0; j < string_input.size();j++)
        {
            if (i == j) continue;
            if (compare(string_input[i],string_input[j])) 
            {
                graph[i][j] = 1;
                reverse_graph[j][i] = 1;
                count++;
            }
        }
    }  
    cout << count << endl; 
}
int find (string s)
{
    for (int i = 0; i < string_input.size();i++)
    {
        if (s == string_input[i]) return i;
    }
    return -1;
}
void explore(int node)
{
    nodes.push(node);
    visited[node] = 1;
    for (int i = 0; i < string_input.size(); i++)
    {
        if (graph[node][i] == 1)
            if (visited[i]!=1) {
                explore(i);
            }
    }
}
void explore2(int node)
{
    temp.push_back(node);
    visited[node] = 1;
    for (int i = 0; i < string_input.size(); i++)
    {
        if (reverse_graph[node][i] == 1)
            if (visited[i]!=1) {
                explore2(i);
            }
    }
}
void dfs()
{
    for (int i = 0; i < string_input.size(); i++)
    {
        if (visited[i] == 0) explore(i);
    }
    for (int i = 0; i < visited.size();i++) visited[i] = 0;
    while (nodes.size() != 0)
    {
        int node = nodes.top();
        nodes.pop();
        for (int i = 0; i < string_input.size();i++)
        {
            if (visited[i] == 0)
            {
                connected++;
                explore2(i);
                if (temp.size() != 0) connected_components.push_back(temp);
                temp.clear();
            }
        }
    }
    cout << "So thanh phan lien thong cua do thi : "<< connected << endl;
}
void print_connected()
{
    string s;
    cout << "Nhap vao sau :" ; cin >> s;
    int location = find(s);
    cout << "Cac sau cung thanh phan lien thong manh voi sau dau vao la : ";
    for (int i = 0 ; i < connected_components.size();i++)
    {
        for (int j = 0; j < connected_components[i].size();j++) 
        {
            if (connected_components[i][j] == location)
            {
                for (int k = 0; k < connected_components[i].size();k++) cout << string_input[connected_components[i][k]] << " ";
                break;
            }
        }
    } 
    cout << endl;
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
    //cout << v;
    while (nodes.size() != 0)
    {
        int node = nodes.front();
        visited[node] = 1;
        nodes.pop();
        //cout << node << " ";
        for (int i = 0; i < 6000;i++)
        {
            if (graph[node][i] == 1 && visited[i] == 0) 
            {
                visited[i] = 1;
                nodes.push(i);
                father_nodes[i] = node;
                dist[i] = dist[u] + 1;
                //cout << node << " " << i << endl;
                //for (int i = 0; i < 5;i++) cout << father_nodes[i];
                //cout << endl;
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
