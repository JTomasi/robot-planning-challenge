#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <iostream>

struct HeapNode
{
    int node{};
    float weight{};
};

class MinHeap
{
private:
    int m_size{};
    std::vector<HeapNode*> A;
    std::vector<int> position;

    int getParent(int i) const
    {
        return (i-1)/2;
    }

    int getChildLeft(int i)
    {
        return 2*i+1;
    }

    int getChildRight(int i)
    {
        return 2*i+2;
    }

    void bubbledown(int i)
    {
        // Recursively compare the current node weight with its children, bubble down with the smallest value. Also check to see if children are actually in heap (less than size of heap)
        int leftChild = getChildLeft(i);
        int rightChild = getChildRight(i);

        int minimum = i;

        if (leftChild < m_size)
        {
            if (A[leftChild]->weight < A[i]->weight)
            {
                minimum = leftChild;
            }
        }
        
        if (rightChild < m_size)
        {
            if (A[rightChild]->weight < A[minimum]->weight)
            {
                minimum = rightChild;
            }
        }
        
        // swap i with the smallest value
        if (minimum != i)
        {
            std::swap(A[i], A[minimum]);
            position[A[i]->node] = i;
            position[A[minimum]->node] = minimum;
            bubbledown(minimum);
        }
    }

    void bubbleup(int i)
    {   
        // Recursively compare node i to its parent, swap if child < parent
        int parent = getParent(i);
        
        if (A[i]->weight < A[parent]->weight)
        {
            std::swap(A[i], A[parent]);
            position[A[i]->node] = i;
            position[A[parent]->node] = parent;
            bubbleup(parent);
        }
    }    
    
public:
    MinHeap(int size) { m_size = size; }

    HeapNode* getMin() const { return A[0]; }

    bool empty() const { return (m_size == 0); }

    void push(int nodeIndex, float nodeWeight);

    void pop();

    void updateNode(int index, float value);

    float getNodeWeight(int index) const;

    void printHeap() const;

    void printPosition() const;
};

#endif