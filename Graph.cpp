#include "Graph.h"

//Constructor
Graph::Graph(int N)
{
    m_N = N;
    m_adjList.resize(m_N);

    // Initialize list with N-NULL pointers
    for (int i = 0; i < N; ++i)
    {
        m_adjList[i].listhead = NULL;
    }
}

float Graph::wayPointDistanceCost(const WayPoint& a, const WayPoint& b)
{
    /* 
    Calculate edge cost between two waypoint, accounting for OTTO speed and the 10 second wait time at each waypoint.
    */
    return ((sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))/2) + 10);
}

void Graph::addWayPointEdge(int a, int b, float weight)
{
    /* 
    Create a new waypoint b that a is connected to a, assign 'next' to the waypoint at the head of the linked list, replace head with new waypoint.
    */
    WayPointNode* newWayPoint = (WayPointNode*) malloc(sizeof(WayPointNode));
    newWayPoint->index = b;
    newWayPoint->edgeWeight = weight;
    newWayPoint->next = m_adjList[a].listhead;
    m_adjList[a].listhead = newWayPoint;
}

void Graph::buildAdjList(std::vector<WayPoint>& wayPointList, int numWayPoints)
{
    /*
        Loop through waypoint list to construct adjacency list
        for each node i = 0 ... N, there are N-i edges
                for each N-1 edge:
                calcualte the cost by summing:
                            1. the cost from i to each N-i node
                            2. the penalty of all the nodes that are skipped
    */
    float edgeWeight{};
    float distanceCost{};
    
    for (int i = 0; i < numWayPoints; ++i)
    {
        // Keep track of the penalty for skipping waypoints
        int runningPenalty{};
        for (int j = i+1; j < numWayPoints; ++j)
        {
            distanceCost = wayPointDistanceCost(wayPointList.at(i), wayPointList.at(j));
            if (j == (i+1))
            {
                edgeWeight = distanceCost;
            }
            else
            {
                runningPenalty += wayPointList.at(j-1).p;
                edgeWeight = distanceCost + runningPenalty;
            }
            addWayPointEdge(i, j, edgeWeight);
        }
    }
}

WayPointNode* Graph::getWayPointValue(int index) const
{
    return m_adjList[index].listhead;
}

// Test functions:
void Graph::printsize() const
{
    std::cout << "The size of the graph is " << m_N << '\n';
}

void Graph::printGraph() const
{
    for (auto node : m_adjList)
    {
        WayPointNode* current {node.listhead};
        while (current != nullptr)
        {
            std::cout << current->index << ": " << current->edgeWeight << " ";
            current = current->next;
        }
        std::cout << '\n';
    }
}