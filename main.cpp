#include <iostream>
#include <limits>
#include <iomanip>

#include "MinHeap.h"
#include "Graph.h"


// Function for getting input data - store each test case in a vector
void getInputs(std::vector<std::vector<WayPoint>>& testCases)
{
    int numTest{};
    while (true)
    {
        int numWayPoints{};
        std::cout << "Number of waypoints: ";
        std::cin >> numWayPoints;

        if (numWayPoints == 0)
            break;

        ++numTest;

        std::vector<WayPoint> waypoints;

        // Resize based on the number of waypoints (+2 for initial/final position)
        waypoints.resize(numWayPoints+2);
        waypoints.at(0).x = 0; waypoints.at(0).y = 0; waypoints.at(0).p = 0;

        for (int i = 1; i <= numWayPoints; ++i)
        {
            std::cout << "Enter waypoint " << i << ": ";
            std::cin >> waypoints[i].x >> waypoints[i].y >> waypoints[i].p;
        }

        // Add final waypoint (which has no penalty as we cannot skip it)
        waypoints.back().x = 100; waypoints.back().y = 100; waypoints.back().p = 0;

        testCases.push_back(waypoints);
    }
}

void runDijkstra(MinHeap& heap, Graph& graph, float* pathCosts)
{
    // Run Dijkstra's algo until the minheap is empty
    while(!heap.empty())
    {   
        int u = heap.getMin()->node;
        heap.pop();

        // Loop through adjacency list of min node, and update Heap with weight values
        WayPointNode* currentWayPointEdges = graph.getWayPointValue(u);
        while (currentWayPointEdges != NULL)
        {
            int v = currentWayPointEdges->index;

            if (currentWayPointEdges->edgeWeight + pathCosts[u] < heap.getNodeWeight(v))
            {
                pathCosts[v] = currentWayPointEdges->edgeWeight + pathCosts[u];
                heap.updateNode(v, pathCosts[v]);
            }

            currentWayPointEdges = currentWayPointEdges->next;
        }
        // check if the current min is a previous node, delete if so (in doing so, re-heap)
        while (heap.getMin()->node < u)
        {
            heap.pop();
        }
    }
}

void printPathLengths(float* array, int numWayPoints)
{
    // Only rounding value output to screen, not the actual number, thus we can use std::setprecision
    std::cout << std::setprecision(3) << std::fixed;
    std::cout << array[numWayPoints-1] << '\n';
}

int main()
{

    // Get input and create graph (adjacency lists):
    std::vector< std::vector<WayPoint> > testCases;
    getInputs(testCases);

    // Loop through all test cases and compute minimum path cost
    for (auto wayPointList : testCases)
    {
        // Build the adjacency list/graph
        int numWayPoints = wayPointList.size();
        class Graph graph(numWayPoints);
        graph.buildAdjList(wayPointList, numWayPoints);

        // Build the heap
        // - initialize with infinity for all values
        // - set the souce vertex cost to zero
        MinHeap heap{numWayPoints};

        // Use an array to track the shortest path to each vertex - initialize with INF  
        float pathCosts[numWayPoints];
        std::fill_n(pathCosts, numWayPoints, std::numeric_limits<float>::infinity());

        // Initialize Heap with N nodes set to infinity
        for (int i = 0; i < numWayPoints; ++i)
        {
            heap.push(i, std::numeric_limits<float>::infinity());
        }

        // Set value of source vertex to zero:
        pathCosts[0] = 0;
        heap.updateNode(0, pathCosts[0]);

        // Run Dijkstra's algorithm to update the shortest path to each node using the adjacency list
        runDijkstra(heap, graph, pathCosts);

        // Print the length of the shortest time to the end (to three decimal places)
        printPathLengths(pathCosts, numWayPoints);

    }  
 
    return 0;

}