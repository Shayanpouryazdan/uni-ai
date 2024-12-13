function [bestScore, bestSolution] = AntLionOptimizer(maxIter, popSize, initialState, goalState)
    % Initialize random number generator
    rng('shuffle');

    % Initialize population
    population = repmat(initialState, popSize, 1);
    for i = 1:popSize
        population(i, :) = population(i, randperm(numel(initialState)));
    end

    bestScore = inf;
    bestSolution = [];

    solutionFound = false;
    while ~solutionFound
        for iter = 1:maxIter
            scores = zeros(popSize, 1);

            % Calculate scores for the population
            for i = 1:popSize
                scores(i) = calculateManhattanDistance(population(i, :), goalState);
                if scores(i) < bestScore
                    bestScore = scores(i);
                    bestSolution = population(i, :);
                end
            end

            % Check if the solution is found
            if bestScore == 0
                fprintf('Solution found at iteration %d\n', iter);
                solutionFound = true;
                break;
            end

            % Log the current best state
            fprintf('Iteration %d: Best Score = %d\n', iter, bestScore);
            disp('Current Best State:');
            printPuzzle(bestSolution);

            % Generate new solutions by shuffling population
            for i = 1:popSize
                population(i, :) = population(i, randperm(numel(initialState)));
            end
        end

        if ~solutionFound
            fprintf('No solution found in %d iterations. Increasing iterations...\n', maxIter);
            maxIter = maxIter + 100;
        end
    end
end

function distance = calculateManhattanDistance(state, goal)
    % Calculate Manhattan Distance between current state and goal state
    distance = 0;
    for i = 1:numel(state)
        if state(i) == 0
            continue; % Skip empty tile
        end
        [goalRow, goalCol] = find(goal == state(i));
        currentRow = ceil(i / 3);
        currentCol = mod(i - 1, 3) + 1;
        distance = distance + abs(goalRow - currentRow) + abs(goalCol - currentCol);
    end
end

function printPuzzle(state)
    % Print the puzzle state in a 3x3 format
    for i = 1:numel(state)
        fprintf('%d ', state(i));
        if mod(i, 3) == 0
            fprintf('\n');
        end
    end
    fprintf('-----------\n');
end

% Main script
initialState = [1, 2, 3, 5, 0, 6, 4, 7, 8];
goalState = [1, 2, 3, 4, 5, 6, 7, 8, 0];

fprintf('Initial State:\n');
printPuzzle(initialState);

fprintf('Goal State:\n');
printPuzzle(goalState);

maxIter = 100;
popSize = 50;

[bestScore, bestSolution] = AntLionOptimizer(maxIter, popSize, initialState, goalState);

fprintf('Final Best Score: %d\n', bestScore);
fprintf('Final Best State:\n');
printPuzzle(bestSolution);
