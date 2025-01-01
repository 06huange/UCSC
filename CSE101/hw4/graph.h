#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<string>
#include<cstdlib>
#include<utility>
#include<unordered_map>


using namespace std;

class Node{
  public:
  string actor;
  unordered_map<string,string> neighbor;
  Node(string N) : actor(N){};
  void add_edge(string, string);
};

class Graph{
  public:
  vector<Node> actors;
  unordered_map<string,int> label;
    Graph(){};
    int add_node(string);
    void print();
    int size(){ return actors.size(); }
    void coActors(string);
    void BFS(string,string,ofstream &out);
    int search(string);
};

#endif
