#ifndef VERTEX_H
#define VERTEX_H
#include "edge.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

class Edge;

// Represents a vertex in a graph with an associated unique identifier
class Vertex {
  friend class Edge;
  friend class Graph;

public:
  // Destructor
  ~Vertex();

  // Initializes a Vertex by copying the properties of another Vertex.
  Vertex(const Vertex &otherVertex);

  // Initializes a Vertex with a unique identifier (vertexID).
  explicit Vertex(const string &vertexID);

  //  Disallowed move constructor for Vertex.
  Vertex(Vertex &&other) = delete;

  // Disallowed copy assignment for Vertex.
  Vertex &operator=(const Vertex &other) = delete;

   // Add an edge to the vertex. Returns true if the edge was added successfully,
  // or false if the edge already exists.
  bool addingEdge(Edge *addingToEdge);

  // Disallowed move assignment for Vertex.
  Vertex &operator=(Vertex &&otherVertex) = delete;

  // Search for an edge connecting this vertex to another vertex (findingEdge).
  // Returns true if the edge is found, otherwise returns false.
  bool searchingEdge(Vertex *findingEdge);


private:
  vector<Edge *> vectorOfEdges; // Stores the edges connecting this vertex to
                                // other vertices
  string vertexID;              // Unique identifier for the vertex
};

#endif
