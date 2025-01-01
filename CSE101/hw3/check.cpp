#include <iostream>
#include "BST.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <cctype>
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

    ifstream file1;
    ifstream file2; 

    if(true){
        file1.open(argv[1]);
        file2.open(argv[2]);
        string test;
        getline(file1,test);
        int key = stoi(test);
        int count = 0;
        int line = 1;
        string a;
        while(getline(file2,a) && count != key){
            if(a[0] == 'r') count++;
            line++;
        }
        cout<<"Found at line: "<<line<<endl;
    }
    else{
        file1.open(argv[1]); // open input file
        file2.open(argv[2]); // open output file
        
        int status = 0;
        string a,b;
        string err1, err2;
        
        int line = 1;
        while(getline(file1,a) && getline(file2,b)){
            if(a != b) {
                status = 1;
                err1 = a;
                err2 = b;
                break;
            }
            line++;
        }
        if(status == 0){
            cout<<"All Good! Files are the same.\n";
        }
        else
        {
            cout<<"Files are different!\n";
            cout<<"At line: "<<line<<"    file 1: "<<err1<<" file 2: "<<err2<<"\n";
        }
        file1.close();
        file2.close();
    }
}