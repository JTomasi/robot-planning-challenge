
#include "MinHeap.h"

void MinHeap::push(int nodeIndex, float nodeWeight)
    {
        HeapNode* newNode = (HeapNode*) malloc(sizeof(HeapNode));
        newNode->node = nodeIndex;
        newNode->weight = nodeWeight;
        A.push_back(newNode);
        position.push_back(nodeIndex);

        // bubble-up the new node
        int newIndex = A.size()-1;
        bubbleup(newIndex);
    }

void MinHeap::pop()
{
    // Swap the root with the end of the heap, and then bubble down the new root.
    position[A[0]->node] = position.size();
    A[0] = A[m_size-1];
    position[A[m_size-1]->node] = 0;
    A.pop_back();
    --m_size;
    bubbledown(0);
}

void MinHeap::updateNode(int index, float value)
{
    int node = position[index];
    A[node]->weight = value;
    bubbleup(node);
}

float MinHeap::getNodeWeight(int index) const
{
    int pos = position[index];
    return A[pos]->weight;
}

void MinHeap::printHeap() const
{
    for (auto node : A)
    {
        std::cout << node->weight << " ";
    }
    std::cout << '\n';
}

void MinHeap::printPosition() const
{
    for (int i = 0; i < position.size(); ++i)
    {
        std::cout << i << ":" << position[i] << " ";
    }
    std::cout << '\n';
}

