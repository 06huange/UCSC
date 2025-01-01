#include<vector>
#include<string>
#include<cstdlib>
#include<iostream>
#include<utility>
#include<queue>
#include<fstream>
#include "graph.h"
#include<list>
using namespace std;


int Graph::add_node(string a){
    auto i = label.find(a);
    if(i == label.end()){
        Node A(a);
        actors.push_back(A);
        int s = actors.size() - 1;
        label.insert({a, s});
        return s;
    }
    else return i->second;
}

void Node::add_edge(string a, string movie){
    //cout<<"Inserting neighbor to "<<actor<<endl;
    if(neighbor.find(a) == neighbor.end())
    neighbor.insert({a,movie});
}

//go to each node and add the other coactors

void Graph::BFS(string a, string b, ofstream &out){
    auto i = label.find(a);
    auto j = label.find(b);
    //One or both actor not in any movies
    if(i == label.end() || j == label.end()){
        //cout<<"One of the actors not found - ";
        out<<"Not present\n";
        return;
    }
    //Actors are the same
    if(i == j){
        cout<<i->first<<endl;
        return;
    }
    //BFS
    int found = 0;
    int end;
    int nIndex;
    queue<string> Q;
    //int visited[actors.size()];
    vector<int> visited(actors.size(),0);
    int pred[actors.size()];
    Q.push(a);
    while(!Q.empty()){
        //cout<<" --- 1 ---"<<endl;
        int index = label.find(Q.front())->second;
        Q.pop();
        for(auto x : actors[index].neighbor){
            nIndex = label.find(x.first)->second;
            if(visited[nIndex] == 1) {
                //cout<<"Node already visited\n";
                continue;
            }
            else{
                pred[nIndex] = index;
                visited[nIndex] = 1;
                if(x.first != b){
                    Q.push(x.first);
                    continue;
                }
                else{
                    //cout<<"FOUND! "<<x.first<<endl;
                    //cout<<actors[nIndex].actor<<endl;
                    end = nIndex;
                    found = 1;
                    break;
                }
            }
        }
    }
    if(found == 0){
        out<<"Not present\n";
        return;
    }
    else{
        int targetIndex = end;
        //cout<<"nIndex: "<<actors[end].actor<<endl;
        vector<string> ans;
        int aIndex = label.find(a)->second;
        //cout<<"Tracing Path"<<endl;
        while(targetIndex != aIndex){
            ans.insert(ans.begin(),actors[targetIndex].actor);
            //cout<<actors[targetIndex].actor<<endl;
            targetIndex = pred[targetIndex];
        }
        out << a;
        Node curr = actors[aIndex];
        for(int i = 0; i < ans.size(); i++){
            string movie = curr.neighbor.find(ans[i])->second;
            out<<" -("<<movie<<")- ";
            out <<ans[i];
            curr = actors[label.find(ans[i])->second];
        }
        out<<endl;
    }
    //print link from target index
}

void Graph::print(){
    for(auto i : actors){
        cout << i.actor<<" -- ";
        for(auto j : i.neighbor){
            cout << j.first << " " << j.second << " | "; 
        }
        cout<<endl;
    }
}

void Graph::coActors(string a){
    cout<<"Finding neighbors of "<<a<<endl;
    auto i = label.find(a);
    int index = i->second;
    for(auto j : actors[index].neighbor){
        cout<<j.first<<" "<<j.second<<" | ";
    }
    cout<<endl;
}

int Graph::search(string a){
    int hi = actors.size()-1;
    int lo = 0;
    while(hi != lo){
        int mid = lo + (hi+1)/2;
        if(actors[mid].actor == a) return mid;
        if(actors[mid].actor < a){
            lo = mid + 1;
            continue;
        }
        if(actors[mid].actor > a){
            hi = mid - 1;
            continue;
        }
    }
    return lo;
}


