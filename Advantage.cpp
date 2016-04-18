//
//  Advantage.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/09/16.
//

#include "Advantage.h"

namespace Gaming

{                                                   //from Advantage.h
    const char Advantage::ADVANTAGE_ID = 'D';   //static const char
    const double  Advantage::ADVANTAGE_MULT_FACTOR = 2.0; //static const double
    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {

    }
    //destructor
    Advantage::~Advantage()
    {

    }

    void Advantage::print(std::ostream &os) const
    {
        os<<ADVANTAGE_ID<<this->__id;
    }

    double Advantage::getCapacity() const
    {
        return __capacity;
    }

    double Advantage::consume()
    {
        finish();
        return __capacity* ADVANTAGE_MULT_FACTOR;
    }

}


