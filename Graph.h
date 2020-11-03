#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <cmath>

// Struct that defines a waypoint
struct WayPoint
{
    int x;
    int y;
    int p;
};

// Struct that defines a waypoint node in our adjacency lists
struct WayPointNode
{
    int index;
    float edgeWeight;
    WayPointNode* next;
};

// A struct for an adjacency lists - it points to the head of the list
struct AdjacencyList
{
    WayPointNode* listhead;
};

//Our graph is an adjacency list (an array of N linked lists) representing N waypoints
class Graph
{
private:
    int m_N;
    std::vector<AdjacencyList> m_adjList;

public:
    //Constructor
    Graph(int N);

    float wayPointDistanceCost(const WayPoint& a, const WayPoint& b);

    void addWayPointEdge(int a, int b, float weight);

    void buildAdjList(std::vector<WayPoint>& wayPointList, int numWayPoints);

    WayPointNode* getWayPointValue(int index) const;

    // Test functions:
    void printsize() const;

    void printGraph() const;

};

#endif