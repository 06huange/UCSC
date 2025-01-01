//Implementation of BST data structure
#include <iostream>
using namespace std;


// node struct to hold data
class Node
{
	public:
        string key;
        int subsize;
        int height;
	    Node *left, *right, *parent;

        Node() // default constructor
        {
            left = right = parent = NULL; // setting everything to NULL
            subsize = 1;
            height = 1;
        }

        Node(string val) // constructor that sets key to val
        {
            key = val;
            left = right = parent = NULL; // setting everything to NULL
            subsize = 1;
            height = 1;
        }
};

class BST 
{
    private:
		Node *root; // Stores root of tree
    public:
        // Default constructor.
        BST();

        // Insert function.
        void insert(string);
    
        int insert(Node*, string);
        
        Node* find(string);
        
        Node* findrecur(Node*, string);
        
        int range(string, string);
        
        int rangerecur(Node*, string, string);
        
        int rangeL(Node*, string, string);
        
        int rangeR(Node*, string, string);
    
        void print();
    
        void printrecur(Node*);
        
        void balance(Node *);
        
        void rotateLeft(Node*);
        void rotateRight(Node*);
        
        void print2D();
};

int greaterHeight(Node*, Node*);
void print2DUtil(Node*, int);
int height(Node*);
int subsize(Node*);
//AVL TREE
//left, right, left-right and right-left rotations.