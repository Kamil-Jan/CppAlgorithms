#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
using namespace std;

class Vertex
{
public:
    string id;
    unordered_map<string, int> adjacent;
    Vertex( string _id ) { id = _id; }

    void addNeighbor(string neighbor, int weight=1);
    vector<string> getConnections();
    vector<tuple<string, int>> getWeightedConnections();
};

void Vertex::addNeighbor(string neighbor, int weight)
{
    adjacent[neighbor] = weight;
}

vector<string> Vertex::getConnections()
{
    vector<string> connections;
    for (auto kv : adjacent) {
        connections.push_back(kv.first);
    }
    return connections;
}

vector<tuple<string, int>> Vertex::getWeightedConnections()
{
    vector<tuple<string, int>> connections;
    for (auto kv : adjacent) {
        connections.push_back(make_tuple(kv.first, kv.second));
    }
    return connections;
}


class Graph
{
public:
    bool directed;
    bool weighted;

    Graph(bool directed, bool weighted)
    {
        directed = directed;
        weighted = weighted;
    }

    void addVertex(string vertex);
    Vertex* getVertex(string vertex);
    vector<string> vertices();

    void addEdge(string from, string to, int weight=1);
    vector<tuple<string, string, int>> edges();
private:
    unordered_map<string, Vertex*> graphDict;
    vector<tuple<string, string, int>> generateEdgesDict();
};

void Graph::addVertex(string vertex)
{
    if (graphDict.find(vertex) == graphDict.end()) {
        graphDict[vertex] = new Vertex(vertex);
    }
}

Vertex* Graph::getVertex(string vertex)
{
    if (graphDict.find(vertex) != graphDict.end()) {
        return graphDict[vertex];
    }
    return NULL;
}

vector<string> Graph::vertices()
{
    vector<string> vertices;
    for (auto kv : graphDict) {
        vertices.push_back(kv.first);
    }
    return vertices;
}

void Graph::addEdge(string from, string to, int weight)
{
    if (!weighted) { weight = 1; }
    addVertex(from);
    addVertex(to);

    graphDict[from]->addNeighbor(to, weight);
    if (directed) {
        graphDict[to]->addNeighbor(from, weight);
    }
}

vector<tuple<string, string, int>> Graph::generateEdgesDict()
{
    vector<tuple<string, string, int>> edges;
    string vertex;
    string neighbor;
    int w;

    for ( auto kv : graphDict ) {
        vertex = kv.first;
        vector<tuple<string, int>> connections = graphDict[vertex]->getWeightedConnections();
        for (size_t i = 0; i < connections.size(); i++) {
            neighbor = get<0>(connections[i]);
            w = get<1>(connections[i]);
            edges.push_back(make_tuple(vertex, neighbor, w));
        }
    }
    return edges;
}

vector<tuple<string, string, int>> Graph::edges()
{
    return generateEdgesDict();
}


void printHashMap(unordered_map<string, Vertex*> map)
{
    cout << "{\n";
    for (auto kv : map) {
        cout << kv.first << ": ";
        cout << kv.second->id << ",\n";
    }
    cout << "}\n";
}

void printHashMap(unordered_map<string, int> map)
{
    cout << "{\n";
    for (auto kv : map) {
        cout << kv.first << ": ";
        cout << kv.second << ",\n";
    }
    cout << "}\n";
}

void printArray(vector<string> arr)
{
    cout << "{ ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "}\n";
}

void printArray(vector<tuple<string, int>> arr)
{
    cout << "{ ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << get<0>(arr[i]) << " : " << get<1>(arr[i]) << ", ";
    }
    cout << "}\n";
}

void printArray(vector<tuple<string, string, int>> arr)
{
    cout << "{\n";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << get<0>(arr[i])
             << " -> "
             << get<1>(arr[i])
             << ": "
             << get<2>(arr[i])
             << ",\n";
    }
    cout << "}\n";
}

int main()
{
    Graph g = Graph(false, true);
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);
    g.addEdge("C", "D", 3);
    g.addEdge("B", "D", 4);
    printArray(g.edges());
    return 0;
}
