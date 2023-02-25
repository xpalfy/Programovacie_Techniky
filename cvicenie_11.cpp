#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>

using namespace std;

struct EdgeTo;

struct Vertex {
    string name;
    list<EdgeTo> edges;
};

struct EdgeTo {
    Vertex *end_vertex;
    unsigned int length;
};

struct Graph {
    list<Vertex> vertices;
};


Vertex *getVertex(Graph *g, const string &name) {
    list<Vertex>::iterator it = find_if(g->vertices.begin(), g->vertices.end(), [&name](Vertex& v) {
        return v.name == name;
    });
    if (it != g->vertices.end()) {
        return &(*it);
    }
    return nullptr;
}

EdgeTo *getEdge(Graph *g, const string &from, const string &to) {
    Vertex *v = getVertex(g, from);
    if (!v) return nullptr;
    for (EdgeTo &e: v->edges) {
        if (e.end_vertex->name == to) {
            return &e;
        }
    }
    return nullptr;
}

Vertex* addVertex(Graph *g, const string &name) {
    Vertex* v = getVertex(g, name);
    if (v) return v;
    g->vertices.push_back({name, {}});
    return &g->vertices.back();
}

EdgeTo* addEdge(Graph *g, const string &from, const string &to, const unsigned length) {
    EdgeTo* e = getEdge(g, from, to);
    if (e) return e;
    Vertex* v1 = addVertex(g,from);
    Vertex* v2 = addVertex(g,to);
    v1->edges.push_back({v2, length});
    return &v1->edges.back();
}

bool removeVertex(Graph *g, const string &name) {
    Vertex *v = getVertex(g, name);
    if (!v) return false;
    for (Vertex &vert: g->vertices) {
        vert.edges.remove_if([v](const EdgeTo &e) { return v == e.end_vertex; });
    }
    g->vertices.remove_if([v](Vertex &vert) { return &vert == v; });
    return true;
}

bool removeEdge(Graph *g, const string &from, const string &to) {
    EdgeTo *e = getEdge(g, from, to);
    if (e) {
        Vertex *v = getVertex(g, from);
        v->edges.remove_if([e](EdgeTo &edge) { return &edge == e; });
        return true;
    }
    return false;
}

vector<string> getNeighbors(Graph *g, const string &name) {
    Vertex *v = getVertex(g, name);
    if (!v) return {};
    vector<string> vs;
    for (EdgeTo &e: v->edges) {
        vs.push_back(e.end_vertex->name);
    }
    return vs;
}

int inDegree(Graph *g, const string &name) {
    if(!getVertex(g,name)) return -1;
    int cnt = count_if(g->vertices.begin(), g->vertices.end(), [name](Vertex &v) {
        return find_if(v.edges.begin(), v.edges.end(), [name](EdgeTo &e) {
            return e.end_vertex->name == name;
        }) != v.edges.end();
    });
    return cnt;
}

int outDegree(Graph *g, const string &name) {
    Vertex* v= getVertex(g, name);
    if(!v) return -1;
    return v->edges.size();
}

void bfs(Graph *g, const string &name) {
    Vertex* v = getVertex(g,name);
    if(!v) return;
    queue<Vertex*> q;
    map<Vertex*,bool> visited;
    for(Vertex& vv : g->vertices){
        visited[&vv] = false;
    }
    visited[v] = true;
    cout << v->name << " ";
    q.push(v);
    while(!q.empty()){
        for(EdgeTo& e : q.front()->edges){
            if(!visited[e.end_vertex]){
                visited[e.end_vertex] = true;
                cout << e.end_vertex->name << " ";
                q.push(e.end_vertex);
            }
        }
        q.pop();
    }
    cout << endl;
}

void dfs(Graph *g, const string &name) {
    Vertex* v = getVertex(g,name);
    if(!v) return;
    stack<Vertex*> s;
    map<Vertex*,bool> visited;
    for(Vertex& vv : g->vertices){
        visited[&vv] = false;
    }
    s.push(v);
    while(!s.empty()){
        v = s.top();
        s.pop();
        if(!visited[v]){
            visited[v] = true;
            cout << v->name << " ";
            for(EdgeTo& e : v->edges){
                s.push(e.end_vertex);
            }
        }
    }
    cout << endl;
}

int main() {
    Graph* g{new Graph};

    addEdge(g, "a", "c", 4);
    addEdge(g, "a", "d", 11);
    addEdge(g, "a", "e", 1);
    addEdge(g, "b", "a", 7);
    addEdge(g, "b", "c", 1);
    addEdge(g, "b", "e", 9);
    addEdge(g, "c", "b", 10);
    addEdge(g, "c", "d", 30);
    addEdge(g, "d", "a", 2);
    addEdge(g, "d", "c", 20);
    addEdge(g, "f", "g", 10);
    addEdge(g, "g", "f", 5);

//    removeVertex(g,"a");
//    removeEdge(g,"c","d");
//    removeEdge(g,"c","x");

    vector<string> n1 = getNeighbors(g,"a");
    vector<string> n2 = getNeighbors(g,"b");
    vector<string> n3 = getNeighbors(g,"c");

    int i1 = inDegree(g,"c");
    int o1 = outDegree(g,"d");

    bfs(g,"a");
    bfs(g,"b");
    bfs(g,"c");

    dfs(g,"a");
    dfs(g,"b");
    dfs(g,"c");

    return 0;
}
