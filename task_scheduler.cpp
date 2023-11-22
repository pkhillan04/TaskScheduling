// ---------------------------------------------------------------------------
// Name: Parth, Gagan, Gungun
// Course-Section: CS255-1
// Assignment: Group Project 3
// Date due: 11/19/2023
// Description: Finding shortest path based on duration and cost using Dijkstra 
// algorithm.
// ---------------------------------------------------------------------------

#include "task_scheduler.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Structure to represent a node in the graph.
struct Node {
    int taskIndex;
    int distance;
    int totalCost;
    vector<int> predecessors;
};

//Author's name: Gungun
//---------------------------------------------------------------------------
/* operator< overload function, custom comparison for the priority queue in Dijkstra's algorithm.
*    This overload prioritizes nodes with a lower total cost.
*
*    INCOMING DATA: two objects of the Node structure.
*    OUTGOING DATA: boolean result of the comparison.
*/
bool operator<(const Node& a, const Node& b) {
    return a.totalCost > b.totalCost; // Minimize total cost
}

//Author's name: Gungun
//Tester's name: Gagan
//---------------------------------------------------------------------------
/* dijkstra function, implements Dijkstra's algorithm for task scheduling.
*    It calculates the shortest path in terms of either duration or cost from the source task to all others.
*    This function updates the given vector of tasks with the calculated path information.
*
*    INCOMING DATA: vector of Task objects, source task index (integer), prioritizeCost (boolean).
*    OUTGOING DATA: none, but it prints the task schedule for each task.
*/
void dijkstra(vector<Task>& tasks, int source, bool prioritizeCost) {
    int n = tasks.size();
    // Initialize distances and total costs to maximum value.
    vector<int> distance(n, INT_MAX);
    vector<int> totalCost(n, INT_MAX);
    vector<bool> visited(n, false);
    unordered_map<int, vector<int>> predecessors;

    // Priority queue for the Dijkstra algorithm.
    priority_queue<Node> pq;
    // Set distance and totalCost for source node.
    distance[source] = 0;
    totalCost[source] = tasks[source].cost;
    pq.push({source, 0, totalCost[source]});

    while (!pq.empty()) {
        Node currentNode = pq.top();
        pq.pop();

        // If node has been visited, skip it.
        if (visited[currentNode.taskIndex]) continue;

        visited[currentNode.taskIndex] = true;

        // Check all dependencies of the current task.
        for (int neighbor : tasks[currentNode.taskIndex].dependencies) {
            if (!visited[neighbor]) {
                int newDistance = distance[currentNode.taskIndex] + tasks[neighbor].duration;
                int newTotalCost = totalCost[currentNode.taskIndex] + tasks[neighbor].cost;

                // Update distance and cost if a better path is found.
                if ((prioritizeCost && newTotalCost < totalCost[neighbor]) ||
                    (!prioritizeCost && newDistance < distance[neighbor])) {
                    distance[neighbor] = newDistance;
                    totalCost[neighbor] = newTotalCost;
                    predecessors[neighbor] = currentNode.predecessors;
                    predecessors[neighbor].push_back(currentNode.taskIndex);

                    pq.push({neighbor, newDistance, newTotalCost});
                }
            }
        }
    }

    // Print out task schedules for each task.
    for (int i = 0; i < n; i++) {
        vector<string> taskPath;
        int currentTask = i;

        // Build the path for the task.
        while (!predecessors[currentTask].empty()) {
            taskPath.push_back(tasks[currentTask].name);
            currentTask = predecessors[currentTask][0];
        }

        taskPath.push_back(tasks[source].name);
        reverse(taskPath.begin(), taskPath.end());

        // Calculate total duration for the task path.
        int totalDuration = tasks[i].duration;
        for (int j = taskPath.size() - 2; j >= 0; j--) {
            totalDuration += tasks[predecessors[i][j]].duration;
        }

        // Print the task schedule details.
        cout << "Task Schedule for " << tasks[i].name << ":" << endl;
        cout << "    Total Duration: " << totalDuration << endl;
        cout << "    Total Cost: " << totalCost[i] << endl;
        cout << "    Task Path: ";

        for (int j = 0; j < taskPath.size(); j++) {
            if (j != 0) {
                cout << " -> ";
            }

            cout << taskPath[j];
        }

        cout << endl << endl;
    }
}