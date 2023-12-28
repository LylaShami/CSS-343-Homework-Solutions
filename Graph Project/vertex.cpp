#include "vertex.h"
#include <algorithm> 
#include <string>
#include <vector>

using namespace std;

// Destructor 
Vertex::~Vertex() {}

// Search for an edge connecting this vertex to another vertex (findingEdge).
bool Vertex::searchingEdge(Vertex *findingEdge) {
  // Use find_if to search for the edge in the vector of edges
  auto edgeFound = find_if(vectorOfEdges.begin(), vectorOfEdges.end(),
    [this, findingEdge](const Edge* edge) {
      return edge->sPoint == this && edge->ePoint == findingEdge;
    });

  // Return true if the edge is found, otherwise return false
  return edgeFound != vectorOfEdges.end();
}

// Constructor for the Vertex class, taking a unique identifier for the vertex.
// Initializes the vector of edges.
Vertex::Vertex(const string &vertexID) {
  this->vertexID = vertexID;
  this->vectorOfEdges = {}; // Initialize the vector of edges for this vertex
}


// Add an edge to the vertex. Returns true if the edge was added successfully,
// or false if the edge already exists.
bool Vertex::addingEdge(Edge *addingToEdge) {
  // Use lower_bound to find the position to insert the edge in sorted order
  auto insertPosition = lower_bound(
    vectorOfEdges.begin(), vectorOfEdges.end(), addingToEdge,
    [](const Edge *edge1, const Edge *edge2) {
      return edge1->ePoint->vertexID < edge2->ePoint->vertexID;
    });

  // Check if the edge already exists by comparing vertexID of the endpoint
  if (insertPosition != vectorOfEdges.end() &&
      (*insertPosition)->ePoint->vertexID == addingToEdge->ePoint->vertexID) {
    return false; // Edge already exists
  }

  // Insert the edge at the found position to maintain sorted order
  vectorOfEdges.insert(insertPosition, addingToEdge);
  return true; // Edge added successfully
}