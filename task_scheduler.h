// ---------------------------------------------------------------------------
// Name: Parth, Gagan, Gungun
// Course-Section: CS255-1
// Assignment: Group Project 3
// Date due: 11/19/2023
// Description: Finding shortest path based on duration and cost using Dijkstra
// algorithm.
// ---------------------------------------------------------------------------

#ifndef TASK_SCHEDULER_H 
#define TASK_SCHEDULER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Definition of the Task structure.
struct Task 
{
    int id; 
    string name; 
    int duration; 
    int cost; 
    vector<int> dependencies; 
};

// Declaration of the dijkstra function.
void dijkstra(vector<Task>& tasks, int source, bool prioritizeCost);

#endif 