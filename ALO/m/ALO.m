function [Best_score, Best_pos, Convergence_curve] = ALO(SearchAgents_no, Max_iter, lb, ub, dim, fobj)

% Initialization
Antlions = initialization(SearchAgents_no, dim, ub, lb);
Convergence_curve = zeros(1, Max_iter);

% Initialize best solution
Best_antlion_score = inf;
Best_antlion_pos = zeros(1, dim);

% Main loop
for iter = 1:Max_iter
    % Normalize Antlions
    Antlions_normalized = normalization(Antlions, ub, lb);
    
    % Select antlions as elite
    for i = 1:SearchAgents_no
        % Roulette Wheel Selection
        selected_antlion = RouletteWheelSelection(1 ./ fitness(Antlions_normalized, fobj));
        
        % Perform random walks
        random_walk_ant = RandomWalk(dim, iter, Max_iter, lb, ub, Antlions(selected_antlion, :));
        
        % Update ant's position
        Ant_pos = (random_walk_ant + Antlions(selected_antlion, :)) / 2;
        
        % Apply boundary constraints
        Ant_pos = max(Ant_pos, lb);
        Ant_pos = min(Ant_pos, ub);
        
        % Calculate fitness
        Ant_fitness = fobj(Ant_pos);
        
        % Update best antlion
        if Ant_fitness < Best_antlion_score
            Best_antlion_score = Ant_fitness;
            Best_antlion_pos = Ant_pos;
        end
    end
    
    % Update positions
    Antlions = updateAntlionPositions(Antlions, Best_antlion_pos, lb, ub, dim);
    
    % Update convergence curve
    Convergence_curve(iter) = Best_antlion_score;
    
    % Display iteration details
    disp(['Iteration: ', num2str(iter), ' Best Score: ', num2str(Best_antlion_score)]);
end

Best_score = Best_antlion_score;
Best_pos = Best_antlion_pos;

end

% Helper functions:
% 1. initialization()
% 2. normalization()
% 3. RouletteWheelSelection()
% 4. RandomWalk()
% 5. fitness()
% 6. updateAntlionPositions()

% Please implement these helper functions or ask if you need more details!
