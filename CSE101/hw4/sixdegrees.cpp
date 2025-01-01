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
#include "graph.h"
using namespace std;
#define IT unordered_map<string,unordered_map<string,string>>::iterator

int main(int argc, char* argv[]){
  ifstream movieList;
  movieList.open("cleaned_movielist.txt");
  //movieList.open("test1.txt");
  ifstream input; // stream for input file
  ofstream output; // stream for output file

  input.open(argv[1]); // open input file
  output.open(argv[2]); // open output file
  
  string command;
  
  Graph g;
    
  //parse movielist
  while(getline(movieList,command)) // get next line of input, store as repeat
  {
    vector<string> tokens; 

    // stringstream class check1 
    stringstream check1(command); 

    string intermediate; 

    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    }
    //cout<<"Finished tokenizing file"<<endl;
    string movie = tokens[0]; 
    //insert node into graph
    for(size_t i = 1; i < tokens.size(); i++){
      //cout<<"Adding node..."<<endl;
        int j = g.add_node(tokens[i]);
        for(size_t k = 1; k < tokens.size(); k++){
          //cout<<"Adding edge..."<<endl;
            if(i != k)
            g.actors[j].add_edge(tokens[k],movie);
        }
      //g.print();
    }
  }
    string buffer;
    while(getline(input,buffer)){
        vector<string> tokens; 

        // stringstream class check1 
        stringstream check1(buffer); 

        string intermediate; 

        // Tokenizing w.r.t. space ' ' 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        }
        //cout<<tokens[0]<<" "<<tokens[1]<<endl;
        g.BFS(tokens[0],tokens[1],output);
    }
  
  //g.print();
  cout<<"size of graph: "<<g.size()<<endl;
  //g.coActors("Vin_Diesel");
  
  exit(0);
}