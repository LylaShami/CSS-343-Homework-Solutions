// Edge class represents an edge in a graph.
// In a graph data structure, edges connect vertices (nodes) and typically have associated weights.
// This class defines the properties and behavior of an edge, including its starting point,
// ending point, weight, and whether it is directed or undirected.
// Directed edges have a specific direction, while undirected edges do not.
#include "edge.h"
using namespace std;

// Default constructor for Edge
Edge::Edge() {
  this->sPoint = {};
  this->ePoint = {};
  weight = 0;
  isDirected = false; // Set to false by default
}

// Destructor for Edge
Edge::~Edge() {}

// Parametrized constructor for Edge that takes starting point, ending point, weight, and direction
Edge::Edge(Vertex *sPoint, Vertex *ePoint, int weight, bool isDirected) {
  this->sPoint = sPoint;
  this->ePoint = ePoint;
  this->weight = weight;
  this->isDirected = isDirected; 
}


