/*
mwstSolver.cpp
CSE102
Reads Input for Weighted Graph and provides mwst solution
using Kruskal's Algorithm
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <regex>
#include <iomanip>
using namespace std;


class Edge {
public:
    int src, dest, label;
    float weight;
};
  
class Graph {
public:
    // V = vertices
    // E = edges
    int V, E;
  
    Edge* edge;
};
  
// Initializes Graph with vertices and edges
Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
  
    graph->edge = new Edge[E];
  
    return graph;
}

// A structure to represent a subset for union-find
class subset {
public:
    int parent;
    int rank;
};
  
// A utility function to find set of an element i
// (uses path compression technique)
int find(subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
  
    return subsets[i].parent;
}
  
// A function that does union of two sets of x and y
// (uses union by rank)
// credit to geeksforgeeks Kruskal's Algorithm page
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
  
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
  
    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
  
// compare two edges by weight
int myComp(const void* first, const void* second)
{
    Edge* f = (Edge*)first;
    Edge* s = (Edge*)second;

    return f->weight - s->weight;
}
  
void KruskalMST(Graph* graph, ofstream& output)
{
    int V = graph->V;
  
    Edge result[V]; 
    // sort the edges by increasing weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
          myComp);

    subset* subsets = new subset[(V * sizeof(subset))];
  
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) 
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
  
    int j = 0; 
    int i = 0;

    // Number of edges to be taken is equal to V-1
    while (j < V - 1 && i < graph->E) 
    {
        // pick least weight
        Edge nextEdge = graph->edge[i++];
  
        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);
  
        // include edge if it doesn't create a cycle
        if (x != y) {
            result[j++] = nextEdge;
            Union(subsets, x, y);
        }

    }
  
    //print to output file
    //label: (source, destination) weight, left justified by 4
    float minCost = 0;
    for (i = 0; i < j; ++i) 
    {
       output.width(4);
       output << result[i].label << ": (" << result[i].src << ", " << result[i].dest 
       << ") " << fixed << setprecision(1) << result[i].weight << endl;
        minCost = minCost + result[i].weight;
    }

    //Total Weight = minCost
    output << "Total Weight = " << fixed << setprecision(2) << minCost
         << endl;
}

int main(int argc, char* argv[]){
    ifstream input;
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]);
    //output.open(argv[2]); // open output file

    string line;
    int vertices;
    int edges;
    int count = 0;

    //set # vertices
    getline(input,line);
    vertices = stoi(line);
    //set # edges
    getline(input,line);
    edges = stoi(line);
    
    Graph* graph = createGraph(vertices,edges);

    for(int i=0; i<edges; i++){
        getline(input,line);

        vector<string> tokens; 

        stringstream check1(line); 

        string intermediate; 

        // Tokenizing w.r.t. space ' ' 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        }
        
        graph->edge[count].src = stoi(tokens[0]);
        graph->edge[count].dest = stoi(tokens[1]);
        graph->edge[count].weight = stof(tokens[2]);
        graph->edge[count].label = count + 1;
        count++;
        

    }

    KruskalMST(graph, output);
  
    return 0;

}