//
//  Agent.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/10/16.
//  Copyright © 2016 Patricia Figueroa. All rights reserved.
//

#include "Agent.h"
#include "Advantage.h"

using namespace std;
namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p)
    {
        this ->__energy -= AGENT_FATIGUE_RATE;
    }
    //destructor
    Agent::~Agent() {

    }

    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other)
    {
        return other.interact(this);

    }

    Piece &Agent::interact(Agent *agent)
    {
        if (this ->__energy < agent ->__energy)
        {
            this ->finish();

        }
        else {
            if (this->__energy > agent ->__energy)
            {
                this -> __energy -= agent->__energy;
                agent->finish();
            }
            else {
                agent->__energy -= __energy;
                finish();
            }
        }
        this -> finish();
        agent ->finish();
        return *this;
    }

    Piece &Agent::interact(Resource *other)
    {
        this-> __energy += other ->consume();
        return *this;
    }

}
