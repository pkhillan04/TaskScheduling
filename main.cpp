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
#include <vector>
#include <string>

using namespace std;

//Author's name: Gagan
//Tester: Parth
//---------------------------------------------------------------------------
/* getTaskDetails() function, collects details for a set of tasks from the user.
*    These details include name, duration, cost, and dependencies of each task.
*
*    INCOMING DATA: none, user input is taken within the function.
*    OUTGOING DATA: returns a vector of Task objects filled with the user's input.
*/
vector<Task> getTaskDetails() {
    int n;
    cout << "Enter the number of tasks: ";
    cin >> n;

    vector<Task> tasks(n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i;
        cout << "Enter the name of task " << i + 1 << ": ";
        cin >> tasks[i].name;

        cout << "Enter the duration of task " << i + 1 << ": ";
        cin >> tasks[i].duration;

        cout << "Enter the cost of task " << i + 1 << ": ";
        cin >> tasks[i].cost;

        int numDependencies;
        cout << "Enter the number of dependencies for task " << i + 1 << ": ";
        cin >> numDependencies;

        for (int j = 0; j < numDependencies; j++) {
            int dependency;
            cout << "Enter dependency " << j + 1 << ": ";
            cin >> dependency;

            tasks[i].dependencies.push_back(dependency - 1);
        }

        cout << endl;
    }

    return tasks;
}

//Author's name: Parth
//Tester's name: Gungun
//---------------------------------------------------------------------------
/* getUserPreferences() function, gathers user preferences for the task scheduling process.
*    Preferences include the index of the starting task and choice between minimizing duration or cost.
*
*    INCOMING DATA: none, user input is taken within the function.
*    OUTGOING DATA: returns a pair containing the starting task index and a boolean indicating cost minimization preference.
*/
pair<int, bool> getUserPreferences() {
    int source;
    cout << "Enter the index of the starting task (0-based): ";
    cin >> source;

    string preference;
    cout << "Would you like to minimize duration (D) or minimize cost (C)? ";
    cin >> preference;

    bool prioritizeCost = (preference == "C" || preference == "c");

    return {source, prioritizeCost};
}

//Author's name: Parth
//---------------------------------------------------------------------------
/* main() function, the entry point of the program.
*    It calls functions to get task details and user preferences, and then runs the dijkstra algorithm for task scheduling.
*
*    INCOMING DATA: none.
*    OUTGOING DATA: returns an integer value, typically 0, to indicate successful program termination.
*/
int main() {
    vector<Task> tasks = getTaskDetails();
    auto preferences = getUserPreferences();

    dijkstra(tasks, preferences.first, preferences.second);

    return 0;
}