//
//  Food.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/10/16.
//  Copyright © 2016 Patricia Figueroa. All rights reserved.
//



#include "Food.h"

namespace Gaming {
    
    const char Food::FOOD_ID = 'F';
    
    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {
    
        
    }
    
    Food::~Food() {
        
    }
    
    void Food::print(std::ostream &os) const {
        os <<FOOD_ID;
    }
}

