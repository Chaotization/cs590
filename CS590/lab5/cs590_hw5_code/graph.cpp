#include "graph.h"
#include <set>
#include <iostream>
#include <queue>

Graph::Graph(int nodes) {
    if(nodes == 0){
        cout<< "Node should be at least 1" << endl;
        return;
    }
    this->nodes = nodes;
    this->matrix = new int* [nodes];

    for(int i = 0; i < nodes; i++){
        (this->matrix)[i] = new int[nodes];
        for(int j = 0; j < nodes; j++){
            this->matrix[i][j] = 0;
        }
    }
}

Graph::Graph(int** matrix, int nodes) {
    if(nodes == 0){
        cout<< "Node should be at least 1" << endl;
        return;
    }
    this->nodes = nodes;
    this->matrix = new int* [nodes];
    for(int i = 0; i < nodes; i++){
        (this -> matrix)[i] = new int[nodes];
        for(int j = 0; j < nodes; j++){
            matrix[i][j] = matrix[i][j];
        }
    }
}

Graph::~Graph() {
    for(int i = 0; i < nodes; i++){
        delete[] (this->matrix)[i];
    }
    delete[] this->matrix;
}

bool Graph::set_edge(int i, int j, int edge) {
    if(i < this -> nodes && j < this -> nodes && i >= 0 && j >= 0){
        (this -> matrix)[i][j] = edge;
        return true;
    }
    return false;
}

void Graph::dfs() {
    set<int> *visited = new set<int>;
    int head = 0;
    for(int i = 0; i < nodes; i++){
        if(visited->count(i) == 0){
            dfs(i , visited);
        }
    }
    delete visited;
}

void Graph::dfs(int node, set<int>* visited) {
    cout << " " << node << " " << endl;
    visited -> insert(node);
    for(int i = 0; i < nodes; i++){
        if(matrix[node][i] != 0 && visited -> count(i) == 0){
            dfs(i, visited);
        }
    }
}

void Graph::bfs(int node) {
    set<int> *visited = new set<int>;
    bfs(node, visited);
    delete visited;
}

void Graph::bfs(int node, set<int>* visited) {
    visited = new set<int>;
    queue<int> queue;
    visited -> insert(node);
    queue.push(node);
    while(!queue.empty()){
        int head = queue.front();
        cout<< " " << head << " ";
        queue.pop();
        for(int i = 0; i < nodes; i++){
            if(matrix[head][i] > 0 && visited -> count(i) == 0){
                visited->insert(i);
                queue.push(i);
            }
        }
    }
    delete visited;
}

