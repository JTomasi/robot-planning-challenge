# otto-challenge

This repository contains code for solving the minimum time of a 2D navigation problem for an indoor mobile robot in a 100x100 grid.

The user must input an ordered sequence of locations that the robot can visit. A location (node) is defined by three values (x, y, c) where x and y are the cartesian coordinates of the node of interest and c is the cost associated with skipping it. The cost incurred by visiting a node is 10, while the cost associated with skipping a node is the cost of the node defined by the user. The task is to determine the minimum cost (time) possible for a particular sequence of nodes. The robot may skip nodes but cannot choose to visit a node that has already been skipped. Additionally, the robot must visit nodes in their sequential order (skipping is permitted). The robot travels at 2 m/s, starts at location (0,0) and must finish at location (100,100).

The solution presented represents the sequence of nodes as a directed acyclic graph and makes use of a modified version of Dijkstra's algorithm for obtaining the minimum possible time.
