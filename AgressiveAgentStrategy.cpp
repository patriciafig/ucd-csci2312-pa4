//  AggressiveAgentStrategy.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/09/16.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"
using namespace std;

namespace Gaming {
    const double Gaming::AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;


    Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy=(agentEnergy);

    }
    AggressiveAgentStrategy::~AggressiveAgentStrategy(){}

    //  If the Agent's energy has an >= aggressiveness threshold AND there are any adjacent Agent-s,
    //      challenge one of them.
    //   Else if adjacent Advantage-s, move onto an Advantage.
    //   Else if STAY

    //strategy for agressive agent

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const
    {
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
                empty.push_back(i);
            else if (s.array[i] == SIMPLE)
                simple.push_back(i);
            else if (s.array[i] == STRATEGIC)
                strategic.push_back(i);
        }

        if (simple.size() > 0 && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
            return Game::reachSurroundings(piecePos, Game::randomPosition(simple));
        else if(advantage.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(advantage));
        else if (food.size() > 0)
            return Game::reachSurroundings(piecePos, Game::randomPosition(food));
        else
            return STAY;
    }
}



/*
vector<int> positions;
default_random_engine gen;
if (__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD)
{
    for (int i = 0;
         i < 9;
         ++i)
    {
        if (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC)
        {
            positions.push_back(i);
        }
    }
}
//vector <ActionType> positions; //positions
//vector <int> positionIndex;

vector<int> advantage;
vector<int> food;
vector<int> empty;
vector<int> simple;
vector<int> strategic;
Position positionIndex(1, 1);


for(unsigned int i= 0; i < s.array.size(); ++i)
{
    //check for advantage

    if(s.array[i] == ADVANTAGE )
    {
        advantage.push_back(i);
        //check for food
    }
    else if(s.array[i] == FOOD)
    {
        for (int i = 0; i < 9; ++i)
        {
            if(s.array[i] == PieceType::ADVANTAGE) // for Gaming::PieceType
            {
                food.push_back(i);
            }

            //check for empty

            else if(s.array[i] == EMPTY)

                for (int i = 0; i < 9; ++i)

                    if(s.array[i] == EMPTY) // for Gaming::PieceType
                    {
                        empty.push_back(i);
                    }





            //check for simple

                    else if(s.array[i] == SIMPLE)
                        simple.push_back(i);

            //check for strategic

                    else if(s.array [i] == STRATEGIC )
                        strategic.push_back(i);


            for (unsigned int count = 0; count < s.array.size(); ++count)
            {
                if (s.array[count] == ADVANTAGE)
                    advantage.push_back(count);
                else if (s.array[count] == FOOD)
                    food.push_back(count);
                else if (s.array[count] == EMPTY)
                    food.push_back(count);
                else if (s.array[count] == SIMPLE)
                    simple.push_back(count);
                else if (s.array[count] == STRATEGIC)
                    strategic.push_back(count);

            }

            if (positions.size() > 0)
            {
                int index = positions[gen() % positions.size()];
                if (positions.size() == 1) index = positions[0];
                ActionType moveDirection;
                switch (index)
                {
                    case 0:
                        moveDirection = NW;
                        break;
                    case 1:
                        moveDirection = N;
                        break;
                    case 2:
                        moveDirection = NE;
                        break;
                    case 3:
                        moveDirection = W;
                        break;
                    case 4:
                        moveDirection = STAY;
                        break;
                    case 5:
                        moveDirection = E;
                        break;
                    case 6:
                        moveDirection = SW;
                        break;
                    case 7:
                        moveDirection = S;
                        break;
                    case 8:
                        moveDirection = SE;
                        break;
                    default:
                        moveDirection = STAY;
                }
                return (moveDirection);
            }

            return STAY;
        }

    }
}
// TODO
return STAY;
}
}
*/




   
        
