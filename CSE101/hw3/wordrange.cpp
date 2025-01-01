#include <iostream>
#include "BST.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cstdlib>

using namespace std;


int main(int argc, char** argv){
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    string command;
    
    BST tree;
    //cout<<"looping through file\n";
    while(getline(input,command)) // get next line of input, store as repeat
    {
        vector <string> tokens; 
        
        // stringstream class check1 
        stringstream check1(command); 

        string intermediate; 

        // Tokenizing w.r.t. space ' ' 
        while(getline(check1, intermediate, ' ')) 
        { 
            tokens.push_back(intermediate); 
        } 
        //cout<<tokens[0]<<"     "<<tokens[1]<<"\n";
        if(tokens.size()==2){
            //cout<<"inserting: \n";
            tree.insert(tokens[1]);
        }
        if(tokens.size()==3){
            //cout<<"finding range: ";
            output<<tree.range(tokens[1],tokens[2])<<"\n";
        }
        /*
        cout<<"---------------------------------\n";
        cout<<"inorder tree: \n";
        tree.print2D();
        cout<<"\n";
        cout<<"---------------------------------\n";
        */
    
    }
    //tree.print2D();
    
}