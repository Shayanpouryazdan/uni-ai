#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

using namespace std;

// Calculate Manhattan Distance
int calculateManhattanDistance(const vector<int>& state, const vector<int>& goal) {
    int distance = 0;
    for (size_t i = 0; i < state.size(); i++) {
        if (state[i] == 0) continue; // Skip the empty tile
        int goalIndex = find(goal.begin(), goal.end(), state[i]) - goal.begin();
        int targetRow = goalIndex / 3;
        int targetCol = goalIndex % 3;
        int currentRow = i / 3;
        int currentCol = i % 3;
        distance += abs(targetRow - currentRow) + abs(targetCol - currentCol);
    }
    return distance;
}

// Print the puzzle state
void printPuzzle(const vector<int>& state) {
    for (size_t i = 0; i < state.size(); i++) {
        cout << state[i] << " ";
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << "-----------" << endl;
}

// Ant Lion Optimizer
pair<int, vector<int>> AntLionOptimizer(int& maxIter, int popSize, const vector<int>& initialState, const vector<int>& goalState) {
    random_device rd;
    mt19937 g(rd());

    vector<vector<int>> population(popSize, initialState);
    for (int i = 0; i < popSize; i++) {
        shuffle(population[i].begin(), population[i].end(), g);
    }

    int bestScore = INT_MAX;
    vector<int> bestSolution;

    bool solutionFound = false;
    while (!solutionFound) {
        for (int iter = 1; iter <= maxIter; iter++) {
            vector<int> scores(popSize);
            for (int i = 0; i < popSize; i++) {
                scores[i] = calculateManhattanDistance(population[i], goalState);
                if (scores[i] < bestScore) {
                    bestScore = scores[i];
                    bestSolution = population[i];
                }
            }

            if (bestScore == 0) {
                cout << "Solution found at iteration " << iter << endl;
                solutionFound = true;
                break;
            }

            // Log current state
            cout << "Iteration " << iter << ": Best Score = " << bestScore << endl;
            cout << "Current Best State:" << endl;
            printPuzzle(bestSolution);

            // Generate new solutions
            for (int i = 0; i < popSize; i++) {
                shuffle(population[i].begin(), population[i].end(), g);
            }
        }

        if (!solutionFound) {
            cout << "No solution found in " << maxIter << " iterations. Increasing iterations..." << endl;
            maxIter += 100; // Increase iterations
        }
    }

    return {bestScore, bestSolution};
}

int main() {
    // Define a hard initial state and goal state
    vector<int> initialState = {1, 2, 3, 5, 0, 6, 4, 7, 8};
    vector<int> goalState = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    cout << "Initial State: " << endl;
    printPuzzle(initialState);

    cout << "Goal State: " << endl;
    printPuzzle(goalState);

    int maxIter = 100;
    int popSize = 50;

    auto result = AntLionOptimizer(maxIter, popSize, initialState, goalState);

    cout << "Final Best Score: " << result.first << endl;
    cout << "Final Best State: " << endl;
    printPuzzle(result.second);

    return 0;
}
