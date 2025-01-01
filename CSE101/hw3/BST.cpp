//Implementation of BST data structure
#include <iostream>
#include "BST.h"
using namespace std;

#define COUNT 10
//constructor
BST :: BST(){
    root = NULL;
}

//insert
void BST::insert(string x){
    if(root == NULL){
        Node *newNode = new Node(x);
        root = newNode;
        return;
    }
    insert(root, x);
}

int BST::insert(Node* node, string x){
    int stat = 1;
    if(x != node->key){
        if(x<node->key){
            if(node->left == NULL){
                //cout<<"parent of new node: "<<node->key<<"\n";
                Node *newNode = new Node(x);
                newNode->parent = node;
                node->left = newNode;
                node->subsize++;
                //update height of each node
                if(node->right == NULL){
                    node->height++;
                }
                return 0; 
            }
            else{
            //cout<<"going left\n";
                stat = insert(node->left, x);
            }
        }
        else if(x>node->key){
            if(node->right == NULL){
                //cout<<"parent of new node: "<<node->key<<"\n";
                Node *newNode = new Node(x);
                newNode->parent = node;
                node->right = newNode;
                node->subsize++;
                //update height of each node
                if(node->left == NULL){
                    node->height++;
                }
                return 0; 
            }
            else{
            //cout<<"going right\n";
                stat = insert(node->right, x);
            }
        }
        if(stat == 0){
            node->subsize++;
            node->height = greaterHeight(node->left, node->right)+1;
            //print2DUtil(node,0);
            //cout<<"\n";
            balance(node);
            //print2DUtil(node,0);
            //cout<<"------------------------------\n";
            return 0;
        }
    }
    //else cout<<"DUPLICATE\n";
    return 1;
}

Node* BST::find(string x){
    if(root==NULL){
        return NULL;
    }
    return findrecur(root,x);
}

Node* BST::findrecur(Node* node, string x){
    if(node==NULL){
        return NULL;
    }
    if(node->key != x){
        if(x < node->key){
            return findrecur(node->left, x);
        }
        else{
            return findrecur(node->right, x);
        }
    }
    return node;
}

int BST::range(string x, string y){
    if(root==NULL){
        return 0;
    }
    //cout<<"range = 0";
    return rangerecur(root, x, y);
}

int BST::rangerecur(Node* node, string x, string y){
    int range = 0;
    if(node==NULL){
        return 0;
    }
    if(node->key >= x && node->key <= y){
        //cout<<"root: "<<node->key<<"\n";
        range += rangeL(node, x, y);
        range += rangeR(node, x, y);
        range++;
    }
    else{
        if(node->key < x){
            range += rangerecur(node->right, x, y);
        }
        else if(node->key > y){
            range += rangerecur(node->left, x, y);
        }
    }
    return range;
}

int BST::rangeL(Node* node, string x, string y){
    int range = 0;
    if(node->left == NULL){
        return 0;
    }
    if(node->left->key >= x){
        if(node->left->right != NULL){
            range += node->left->right->subsize;
            //cout<<" +"<<node->left->right->subsize<<" ";
            if(node->left->key == x){
                range++;
                return range;
            }
        }
        range += rangeL(node->left, x, y);
        range++;
    }
    else{
        if(node->key == x) return 0;
        if(node->key >= x) {
            range += rangeL(node->left, x, y);
        }
        else{
            range += rangerecur(node, x, y);
        }
    }
    return range;
}

int BST::rangeR(Node* node, string x, string y){
    int range = 0;
    if(node->right == NULL){
        return 0;
    }
    if(node->right->key <= y){
        if(node->right->left != NULL){
            range += node->right->left->subsize;
            //cout<<" +"<<node->right->left->subsize<<" ";
            if(node->right->key == y){
                range++;
                return range;
            }
        }
        range++;
        range += rangeR(node->right, x, y);
    }
    else{
        if(node->key == y) return 0;
        if(node->key <= y){ 
            range += rangeR(node->right,x, y);
        }
        else{
            range += rangerecur(node, x, y);
        }
    }
    return range;
}


void BST::print(){
    if(root == NULL){
        cout<<"Tree is empty\n";
        return;
    }
    printrecur(root);
}

void BST::printrecur(Node* node){
    if(node->left == NULL && node->right == NULL){
        cout<<node->key<<" size: "<<node->subsize<<" height: "<<node->height<<"\n";
        return;
    }
    if(node->left != NULL){
        printrecur(node->left);
    }
    cout<<node->key<<" size: "<<node->subsize<<" height: "<<node->height<<"\n";
    if(node->right != NULL){
        printrecur(node->right);
    }
}

void BST::balance(Node* node){
    if(node->left == NULL && node->right == NULL) return;
    
    int balance = height(node->left) - height(node->right);
    //cout<<"lheight: "<<lheight<<" rheight: "<<rheight<<"\n";
    if (balance > 1){
        if(height(node->left->left) - height(node->left->right) == -1){
            rotateLeft(node->left);
        }
        rotateRight(node);
        return;
    }
    // Right Right Case  
    
    if (balance < -1){
        if(height(node->right->left) - height(node->right->right) == 1){
            rotateRight(node->right);
        }
        rotateLeft(node);  
        return;
    }
    
}

void BST::rotateRight(Node* node){
    //cout<<"ROTATING: "<<node->key;
    Node* pivot = node->left;
    if(node != root){
        //cout<<" PARENT: "<<node->parent->key<<"\n";
        Node* p = node->parent;
        if(p->right == NULL || p->left == NULL){
            if(p->right == NULL){
                p->left = pivot;
            }
            if(p->left == NULL){
                p->right = pivot;
            }
        }
        else{
            if(p->left->key == node->key){
                p->left = pivot;
            }
            else{
                p->right = pivot;
            }
        }
    }
    else{
        root = node->left;
    }
    pivot->parent = node->parent;
    node->left = pivot->right;

    if(pivot->right != NULL){
        pivot->right->parent = node;
        node->subsize += pivot->right->subsize;
    }
    pivot->right = node;
    node->parent = pivot;
    node->subsize -= pivot->subsize;
    //pivot->subsize += node->subsize;
    pivot->subsize = subsize(pivot->left) + subsize(pivot->right) + 1;
    node->height = greaterHeight(node->left,node->right) + 1;
    pivot->height = greaterHeight(pivot->left,pivot->right) + 1;
    //print2D();
    return;
}

void BST::rotateLeft(Node* node){
    //cout<<"ROTATING: "<<node->key;
    Node* pivot = node->right;
    if(node != root){
        //cout<<" PARENT: "<<node->parent->key<<"\n";
        Node* p = node->parent;
        if(p->right == NULL || p->left == NULL){
            if(p->right == NULL){
                p->left = pivot;
            }
            if(p->left == NULL){
                p->right = pivot;
            }
        }
        else{
            if(p->left->key == node->key){
                p->left = pivot;
            }
            else{
                p->right = pivot;
            }
        }
    }
    else{
        root = pivot;
    }
    pivot->parent = node->parent;
    node->right = pivot->left;
    if(pivot->left != NULL){
        pivot->left->parent = node;
        node->subsize += pivot->left->subsize;
        
    }
    pivot->left = node;
    node->parent = pivot;
    node->subsize -= pivot->subsize;
    //pivot->subsize += node->subsize;
    pivot->subsize = subsize(pivot->left) + subsize(pivot->right) + 1;
    node->height = greaterHeight(node->left,node->right) + 1;
    pivot->height = greaterHeight(pivot->left,pivot->right) + 1;
    //print2D();
    return;
}

//helper

int greaterHeight(Node* a, Node* b){
    if(a == NULL && b == NULL) return 0;
    
    if(a == NULL){
        return b->height;
    }
    if(b == NULL){
        return a->height;
    }
    else{
        if(a->height >= b->height) return a->height;
        if(b->height > a->height) return b->height;
    }
    return 1;
}

// Function to print binary tree in 2D  
// It does reverse inorder traversal  
void print2DUtil(Node *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->right, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->key<<"/";
    //cout<<root->height<<"\n";
    //if(root->parent!=NULL) cout<<root->parent->key<<"\n";
    cout<<root->subsize<<"\n";
  
    // Process left child  
    print2DUtil(root->left, space);  
}  
  
// Wrapper over print2DUtil()  

void BST::print2D()  
{  
    // Pass initial space count as 0  
    print2DUtil(root, 0);  
}  

int height(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int subsize(Node* node){
    if(node == NULL){
        return 0;
    }
    return node->subsize;
}
