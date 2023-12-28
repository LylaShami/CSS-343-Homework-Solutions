#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

// Forward Declaration of Class Vertex
class Vertex;

// Class Declaration: Edge
class Edge {
  friend class Graph;
  friend class Vertex;

public:
  Edge(); // Default constructor for Edge

  ~Edge(); // Destructor for Edge

  // Parametrized constructor for Edge that takes starting point, ending point,
  // weight, and a flag indicating if it's directed or undirected
  Edge(Vertex *sPoint, Vertex *ePoint, int weight, bool isDirected);
  // move assignment for an Edge
  Edge &operator=(Edge &&other);
  
  // copying an Edge (copy constructor)
  Edge(const Edge &edge);

  // moving an Edge (move constructor)
  Edge(Edge &&other);
  
  // copy assignment for an Edge
  Edge &operator=(const Edge &other);

private:
  bool isDirected; // whether the edge is directed (true) or undirected (false)

  int weight; // Weight associated with the edge

  Vertex *ePoint; // Ending point (Vertex) of the edge

  Vertex *sPoint; // Starting point (Vertex) of the edge
};

#endif