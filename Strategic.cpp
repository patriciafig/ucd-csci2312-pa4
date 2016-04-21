//
//  Strategic.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/11/16.


#include "Strategic.h"
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Gaming;

const char Strategic::STRATEGIC_ID = 'T';

Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s):Agent(g, p, energy)
{
    __strategy = s;
}

Strategic::~Strategic()
{
    delete __strategy;
}

void Strategic::print(std::ostream &os) const {
    std::string str;
    str = std::to_string(__id);


    std::stringstream ss;
    ss << Strategic::STRATEGIC_ID;
    ss << str;
    std::getline(ss, str);
    for (int i = 0; i < str.length(); ++i) {
        os << str[i];
    }
}

ActionType Strategic::takeTurn(const Surroundings &s) const
{
    return (*this->__strategy)(s);
}
