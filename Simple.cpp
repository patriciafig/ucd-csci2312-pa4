//
//  Simple.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/11/16.
//

#include "Simple.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace Gaming;

const char Simple::SIMPLE_ID = 'S';

Simple::Simple(const Game &g, const Position &p, double energy):Agent(g, p, energy)
{

}

Simple::~Simple()
{

}

void Simple::print(std::ostream &os) const
{
    stringstream ss;
    ss << SIMPLE_ID << __id;
    string s;
    getline(ss,s);
    os << s;


}


ActionType Simple::takeTurn(const Surroundings &s) const
{
    /*
    vector <ActionType> action
    vector <int> pieceIndex;
    int numDir = 0;
    vector<int>resource;
    vector<int>empty;
    random_device rd;
    Position currentPosition(1, 1);
   for (int i = 0; i < s.array.size(); ++i)
    {
        if(s.array[i] == FOOD || s.array[i] == ADVANTAGE)
        {
            resource.push_back(i);
            else if (s.array[i] == EMPTY)
                empty.push_back(i);
        }
    }
*/

    vector<int> resource;
    vector<int> empty;
    Position currentPosition(1, 1);
    for (int i = 0; i < s.array.size(); ++i) {
        if (s.array[i] == FOOD || s.array[i] == ADVANTAGE)
            resource.push_back(i);
        else if (s.array[i] == EMPTY)
            empty.push_back(i);

    }



    if (resource.size() > 0)
        return __game.reachSurroundings(currentPosition, Game::randomPosition(resource));
    else if (empty.size() > 0)
        return __game.reachSurroundings(currentPosition, Game::randomPosition(empty));
    else
        return STAY;
/*
    if(numDir > 0)
    {
        uniform_int_distribution<> dis(0, numDir - 1);
        return action[pieceIndex[dis(gen)]];
    }

    for (int i = 0; i < s.array.size(); ++i)
    {
        if(s.array[i]==EMPTY)
        {
            pieceIndex.push_back(i);
            numDir++;
        }
    }

    if(numDir > 0)
    {
        uniform_int_distribution<> dis(0, numDir - 1);
        return action[pieceIndex[dis(gen)]];
    }

}
*/

    return STAY;

}
