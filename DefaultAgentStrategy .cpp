//
//  DefaultAgentStrategy.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/09/16.
//
//


#include "DefaultAgentStrategy.h"
#include "Game.h"
using namespace std;

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {}

    DefaultAgentStrategy::~DefaultAgentStrategy() {}

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        vector<int> advantage;
        vector<int> food;
        vector<int> empty;
        vector<int> simple;
        vector<int> strategic;
        Position piecePos(1, 1);

        for (unsigned int i = 0; i < s.array.size(); ++i) {
            if (s.array[i] == ADVANTAGE)
                advantage.push_back(i);
            else if (s.array[i] == FOOD)
                food.push_back(i);
            else if (s.array[i] == EMPTY)
                food.push_back(i);
            else if (s.array[i] == SIMPLE)
                simple.push_back(i);
            else if (s.array[i] == STRATEGIC)
                strategic.push_back(i);
        }

        if (advantage.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(advantage));
        else if (food.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(food));
        else if (empty.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(empty));
        if (simple.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(simple));
        else
            return STAY;
    }
}




