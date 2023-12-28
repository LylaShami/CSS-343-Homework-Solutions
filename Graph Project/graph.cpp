#include "graph.h"
#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// constructor, empty graph
// directionalEdges defaults to true
Graph::Graph(bool directionalEdges) {
  this->directionalEdges = directionalEdges;
}

// destructor
Graph::~Graph() {}

// @return total number of vertices
int Graph::verticesSize() const { return static_cast<int>(graph.size()); }

/** return true if vertex already in graph */
bool Graph::contains(const string &label) const {
  return graph.find(label) != graph.end();
}

// @return total number of edges
// Returns the total number of edges in the graph.
// It counts the number of edges for each vertex in the graph and accumulates
// them. The total number of edges in the graph.
int Graph::edgesSize() const {
  return accumulate(graph.begin(), graph.end(), 0,
                    [](int sumAllTogether, const pair<const string, Vertex*>& pair) {
                      return sumAllTogether + pair.second->vectorOfEdges.size();
                    });
}

// @return true if vertex added, false if it already is in the graph
// Adds a new vertex with the given label to the graph if it doesn't already
// exist. True if the vertex is added successfully, false if the vertex already
// exists.
bool Graph::add(const string &label) {
  // Check if the graph already contains a vertex with the given label
  if (this->contains(label)) {
    // If the vertex with the same label already exists, return false (not
    // added)
    return false;
  }

  // Create a new vertex with the given label and add it to the graph
  Vertex *newVertex = new Vertex(label);
  graph[label] = newVertex;

  // Return true to indicate that the vertex was added successfully
  return true;
}
// @return number of edges from given vertex, -1 if vertex not found
// Calculates the degree (number of edges) of a vertex with the given label.
// The label of the vertex for which the degree is calculated.
// The degree of the vertex, or -1 if the vertex does not exist in the graph.
int Graph::vertexDegree(const string &label) const {
  // Check if the graph contains a vertex with the given label
  while (graph.find(label) != graph.end()) {
    // Retrieve the vertex with the given label and calculate its degree
    return static_cast<int>(graph.find(label)->second->vectorOfEdges.size());
  }

  // If the vertex does not exist in the graph, return -1 to indicate its
  // absence
  return -1;
}

// @return true if successfully connected
// Creates a connection (edge) between two vertices with the specified labels
// and weight.
// The label of the starting vertex for the edge.
// The label of the ending vertex for the edge.
// The weight of the edge connecting the two vertices.
// True if the connection was successfully created, or false if the connection
// failed.
bool Graph::connect(const string &sPoint, const string &ePoint, int weight) {
  // Ensure that the starting and ending points are not the same vertex
  if (sPoint == ePoint) {
    return false;
  }

  // Check if the ending vertex does not exist in the graph and add it
  if (graph.find(ePoint) == graph.end()) {
    add(ePoint);
  }

  // Check if the starting vertex does not exist in the graph and add it
  if (graph.find(sPoint) == graph.end()) {
    add(sPoint);
  }

  // Find iterators for the starting and ending vertices
  auto startVertexIt = graph.find(sPoint);
  auto endVertexIt = graph.find(ePoint);

  // If directional edges are enabled, check if an edge from start to end
  // already exists
  if (directionalEdges &&
      startVertexIt->second->searchingEdge(endVertexIt->second)) {
    return false;
  }

  // Create a new edge from start to end and add it to the starting vertex
  auto* edgeAdded =
      new Edge(startVertexIt->second, endVertexIt->second, weight, false);
  startVertexIt->second->  addingEdge(edgeAdded);

  // If directional edges are disabled, check if an edge from end to start
  // already exists
  if (!directionalEdges &&
      !endVertexIt->second->searchingEdge(startVertexIt->second)) {
    // Create a new edge from end to start and add it to the ending vertex
    endVertexIt->second->  addingEdge(
        new Edge(endVertexIt->second, startVertexIt->second, weight, false));
  }

  return true;
}

// @return string representing edges and weights, "" if vertex not found
// A-3->B, A-5->C should return B(3),C(5)
// Retrieves a string representation of the edges connected to the vertex with
// the specified label. The label of the vertex to retrieve the edges from.
//  A string containing a representation of the edges connected to the specified
//  vertex.
string Graph::getEdgesAsString(const string &label) const {
  // Find the vertex in the graph
  auto iterator = graph.find(label);
  string result;

  if (iterator != graph.end()) {
    int i = 0;
    // Iterate through the edges connected to the vertex
    for (const auto &edgePointer : iterator->second->vectorOfEdges) {
      Edge *edge = edgePointer;
      // Add the ending vertex's label and edge weight to the result
      result += edge->ePoint->vertexID + "(" + to_string(edge->weight) + ")";
      i++;
      if (i < iterator->second->vectorOfEdges.size()) {
        // Add a comma if there are more edges to include
        result += ",";
      }
    }
  }

  return result;
}
//  Disconnects an edge between two vertices with specified labels.
// The label of the starting vertex of the edge.
// The label of the ending vertex of the edge.
// True if the edge was successfully disconnected, false otherwise.
bool Graph::disconnect(const string &sPoint, const string &ePoint) {
  // Find the vertices with the specified labels
  auto startVertexIt = graph.find(sPoint);
  auto endVertexIt = graph.find(ePoint);

  // Check if either of the vertices doesn't exist in the graph
  if (startVertexIt == graph.end() || endVertexIt == graph.end()) {
    return false;
  }

  Vertex *startVertex = startVertexIt->second;
  Vertex *endVertex = endVertexIt->second;
  bool edgeExists = false;

  // Iterate through the edges of the starting vertex
  for (auto it = startVertex->vectorOfEdges.begin();
       it != startVertex->vectorOfEdges.end(); ++it) {
    if ((*it)->ePoint == endVertex) {
      // Delete the edge and erase it from the vector
      delete *it;
      it = startVertex->vectorOfEdges.erase(it);
      edgeExists = true;

      // If it's an undirected graph, also disconnect the edge in the other
      // direction
      if (!directionalEdges) {
        for (auto it2 = endVertex->vectorOfEdges.begin();
             it2 != endVertex->vectorOfEdges.end(); ++it2) {
          if ((*it2)->ePoint == startVertex) {
            delete *it2;
            it2 = endVertex->vectorOfEdges.erase(it2);
            break;
          }
        }
      }

      break;
    }
  }

  return edgeExists;
}

// breadth-first traversal starting from startLabel
// Performs a Breadth-First Search (BFS) traversal starting from a specified
// vertex.
//  The label of the starting vertex for the BFS traversal.
// A function that is called for each visited vertex during the BFS traversal.
void Graph::bfs(const string &startLabel, void visit(const string &label)) {
  // Find the vertex corresponding to the provided startLabel
  auto startVertexIt = graph.find(startLabel);

  // If the starting vertex doesn't exist, return.
  if (startVertexIt == graph.end()) {
    return;
  }

  // Create a queue for BFS traversal, a set to track visited vertices, and
  // enqueue the starting vertex.
  queue<string> bfsQueue;
  unordered_set<string> visited;
  bfsQueue.push(startLabel);
  visited.insert(startLabel);

  // Perform BFS traversal
  while (!bfsQueue.empty()) {
    string u = bfsQueue.front();
    bfsQueue.pop();

    // Call the 'visit' function for the visited vertex.
    visit(u);

    // Get the current vertex from the graph.
    Vertex *currentVertex = graph[u];

    // Explore neighboring vertices connected by edges.
    for (const Edge *edgePtr : currentVertex->vectorOfEdges) {
      string nextLabel = edgePtr->ePoint->vertexID;

      // If the neighbor vertex has not been visited, enqueue it and mark it as
      // visited.
      if (visited.find(nextLabel) == visited.end()) {
        bfsQueue.push(nextLabel);
        visited.insert(nextLabel);
      }
    }
  }
}

// depth-first traversal starting from given startLabel
//  Performs a Depth-First Search (DFS) traversal starting from a specified
//  vertex.
// The label of the starting vertex for the DFS traversal.
// A function that is called for each visited vertex during the DFS traversal.
void Graph::dfs(const string &startLabel, void visit(const string &label)) {
  // Find the vertex corresponding to the provided startLabel
  auto startVertexIt = graph.find(startLabel);

  // If the starting vertex doesn't exist, return.
  if (startVertexIt == graph.end()) {
    return;
  }

  // Create a stack for DFS traversal, a set to track visited vertices, and push
  // the starting vertex onto the stack.
  stack<string> dfsStack;
  unordered_set<string> visited;
  dfsStack.push(startLabel);
  visited.insert(startLabel);

  // Perform DFS traversal using a recursive helper function.
  dfsRecursive(dfsStack, visited, visit);
}

// Recursively performs Depth-First Search (DFS) traversal starting from the
// current vertex on the stack. The label of the current vertex being visited.
//  The stack used for DFS traversal.
// A set to track visited vertices.
// The visitor function called for each visited vertex.
void Graph::dfsRecursive(stack<string> &dfsStack,
                         unordered_set<string> &visited,
                         void visit(const string &label)) {
  // Continue DFS traversal while the stack is not empty.
  while (!dfsStack.empty()) {
    string stackTop = dfsStack.top();
    dfsStack.pop();

    // Call the 'visit' function for the visited vertex.
    visit(stackTop);

    // Get the current vertex from the graph.
    Vertex *poppedVertex = graph[stackTop];

    // Explore neighboring vertices connected by edges.
    for (auto iterator = poppedVertex->vectorOfEdges.rbegin();
         iterator != poppedVertex->vectorOfEdges.rend(); iterator++) {
      string nextLabel = (*iterator)->ePoint->vertexID;

      // If the neighbor vertex has not been visited, push it onto the stack and
      // mark it as visited.
      if (visited.find(nextLabel) == visited.end()) {
        dfsStack.push(nextLabel);
        visited.insert(nextLabel);
      }
    }
  }
}

// store the weights in a map
// store the previous label in a map
// Perform Dijkstra's algorithm to find the shortest paths from the starting
// vertex to all other vertices.
// The label of the starting vertex for the Dijkstra's algorithm.
// A pair of maps containing vertex weights and previous vertices in the
// shortest paths.
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &startLabel) const {
  // Initialize maps to store vertex weights and previous vertices.
  map<string, int> vertexWeights;
  map<string, string> prevVertex;

  // Check if the starting vertex is in the graph.
  if (graph.find(startLabel) == graph.end()) {
    // If not, return empty maps.
    return make_pair(vertexWeights, prevVertex);
  }

  // Perform Dijkstra's algorithm to calculate vertex weights and shortest
  // paths.
  dijkstraHelper(startLabel, vertexWeights, prevVertex);

  // Remove the starting vertex from the vertexWeights map.
  vertexWeights.erase(startLabel);

  // Return the maps containing vertex weights and previous vertices in the
  // shortest paths.
  return make_pair(vertexWeights, prevVertex);
}

// Helper function for Dijkstra's algorithm. Finds the shortest paths and vertex
// weights from a starting vertex. The label of the starting vertex for the
// Dijkstra's algorithm.
//  Reference to a map to store vertex weights.
// Reference to a map to store previous vertices in the shortest paths.
void Graph::dijkstraHelper(const string &startLabel,
                           map<string, int> &vertexWeights,
                           map<string, string> &prevVertex) const {
  // Priority queue to process vertices with the smallest weights first.
  priority_queue<pair<int, Vertex *>, vector<pair<int, Vertex *>>,
                 greater<pair<int, Vertex *>>>
      pQueue;

  // Initialize with the starting vertex.
  pQueue.push({0, graph.find(startLabel)->second});
  vertexWeights[startLabel] = 0;

  while (!pQueue.empty()) {
    // Get the vertex with the smallest weight.
    Vertex *popVertex = pQueue.top().second;
    pQueue.pop();

    for (auto &edge : popVertex->vectorOfEdges) {
      // Calculate the new weight through the current path.
      int nWeight = vertexWeights[popVertex->vertexID] + edge->weight;
      int oWeight = numeric_limits<int>::max();

      if (vertexWeights.find(edge->ePoint->vertexID) != vertexWeights.end()) {
        oWeight = vertexWeights[edge->ePoint->vertexID];
      }

      // Update vertex weights and previous vertices if a shorter path is found.
      if (nWeight < oWeight) {
        vertexWeights[edge->ePoint->vertexID] = nWeight;
        prevVertex[edge->ePoint->vertexID] = popVertex->vertexID;
        pQueue.push({nWeight, edge->ePoint});
      }
    }
  }
}

// minimum spanning tree using Prim's algorithm
// Computes the Minimum Spanning Tree (MST) using Prim's algorithm, starting
// from the given vertex. Only works for NON-DIRECTED graphs and assumes edges
// [P->Q] have the same weight as [Q->P].
// The label of the starting vertex for the MST.
// A function to be called when an edge is included in the MST.
// The length of the Minimum Spanning Tree (MST) or -1 if the start vertex is
// not found.
int Graph::mstPrim(const string &startLabel,
                   void visit(const string &sPoint, const string &ePoint,
                              int weight)) const {
  // Check if the start vertex exists in the graph.
  if (graph.find(startLabel) == graph.end()) {
    return -1;
  }

  // Ensure that the graph contains only non-directed edges.
  for (const auto &pairedVertex : graph) {
    for (const auto &edge : pairedVertex.second->vectorOfEdges) {
      if (edge->isDirected) {
        return -1;
      }
    }
  }

  // Check for an empty graph.
  if (graph.empty()) {
    return -1;
  }

  // Create a set to keep track of visited vertices.
  set<string> visited;

  // Call the MST helper function to compute the MST and return its length.
  return mstPrimHelper(startLabel, visited, visit);
}

//  A helper function for computing the Minimum Spanning Tree (MST) using Prim's
//  algorithm, starting from the given vertex. The label of the starting vertex
//  for the MST.
// A set to keep track of visited vertices.
//  A function to be called when an edge is included in the MST.
// - The length of the Minimum Spanning Tree (MST) computed from the given start
// vertex.
int Graph::mstPrimHelper(const string &startLabel, set<string> &visited,
                         void visit(const string &sPoint, const string &ePoint,
                                    int weight)) const {
  int answer = 0;
  using IE = pair<int, Edge *>;
  priority_queue<IE, vector<IE>, greater<IE>> queue;
  Vertex *popVertex = graph.find(startLabel)->second;

  // Initialize the priority queue with edges from the starting vertex.
  for (auto &iterator : popVertex->vectorOfEdges) {
    queue.push({iterator->weight, iterator});
  }
  visited.insert(startLabel);

  while (!queue.empty()) {
    IE current = queue.top();
    queue.pop();
    int currentWeight = current.first;

    Edge *edgePointer = current.second;
    string labelFromEdge = edgePointer->sPoint->vertexID;
    string labelToEdge = edgePointer->ePoint->vertexID;
    visited.insert(labelFromEdge);

    if (visited.find(labelToEdge) == visited.end()) {
      visited.insert(labelToEdge);
      answer += currentWeight;
      visit(labelFromEdge, labelToEdge, currentWeight);

      // Explore the edges of the newly visited vertex.
      for (auto &edge : graph.find(labelToEdge)->second->vectorOfEdges) {
        if (visited.find(edge->ePoint->vertexID) == visited.end()) {
          queue.push({edge->weight, edge});
        }
      }
    }
  }
  return answer;
}

// read a text file and create the graph
bool Graph::readFile(const string &filename) {
  ifstream myfile(filename);
  if (!myfile.is_open()) {
    cerr << "Failed to open " << filename << endl;
    return false;
  }
  int edges = 0;
  int weight = 0;
  string fromVertex;
  string toVertex;
  myfile >> edges;
  for (int i = 0; i < edges; ++i) {
    myfile >> fromVertex >> toVertex >> weight;
    connect(fromVertex, toVertex, weight);
  }
  myfile.close();
  return true;
}