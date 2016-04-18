//
//  DefaultAgentStrategy.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/08/16.
//


#include "DefaultAgentStrategy.h"
#include "Game.h"
#include <random>
using namespace std;
namespace Gaming {


    DefaultAgentStrategy::DefaultAgentStrategy(){}

    DefaultAgentStrategy::~DefaultAgentStrategy(){}

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        vector<int> positions;
        default_random_engine gen;
        vector<int> advantages;
        vector<int> foods;
        vector<int> empties;
        vector<int> simples;
        vector<int> strategics;
        Position pieceIndex(1, 1);


        //check for advantage

        for (unsigned int i = 0; i < 9 ; ++i)
        {
            if(s.array[i] == ADVANTAGE)
                advantages.push_back(i);
        //check for food

       else if(s.array[i] == FOOD)
           foods.push_back(i);

        //check for empty

        else if(s.array[i] == EMPTY)
        foods.push_back(i);

        //check for simple

       else if(s.array[i] == SIMPLE)
           simples.push_back(i);


            if (advantages.size() > 0)
                return Game::reachSurroundings(pieceIndex, Game::randomPosition(advantages));
            else if (foods.size() > 0)
                return Game::reachSurroundings(pieceIndex, Game::randomPosition(foods));
            else if (empties.size() > 0)
                return Game::reachSurroundings(pieceIndex, Game::randomPosition(empties));
            if (simples.size() > 0)
                return Game::reachSurroundings(pieceIndex, Game::randomPosition(simples));
            else
                return STAY;
        }
        return STAY;
    }
}
