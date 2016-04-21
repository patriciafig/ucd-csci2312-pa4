//
//  Game.cpp
//  ProgrammingAssignment#4
//
//  Created by Patricia Figueroa on 4/11/16.
//
#include <iomanip>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"

using namespace std;

namespace Gaming{

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();
    const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned int Game::MIN_WIDTH = 3;
    const unsigned int Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    //Private
// to populate the grid (used in automatic random initialization of a Game)
    void Game::populate()
    {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        default_random_engine gen;
        uniform_int_distribution<int> d(0, __width * __height - 1);

        while (numStrategic > 0)
        {
            int i = d(gen);

            //if ( i!= nullptr)
            if (i !=(__width * __height)&&__grid[i] == nullptr )
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic --;
            }
        }

        while (numSimple > 0)
        {
            int i = d(gen);

            //if ( == nullptr)
            if (i != (__width* __height)&&__grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple --;
            }
        }

        while (numFoods > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
    }

    //Public

    //CONSTRUCTOR

    Game::Game(): __width(3), __height(3)
    {
        __numInitAgents = 0;
        __numInitResources = 0;
        __width = 3;
        __height = 3;
        __round = 0;
        __status = NOT_STARTED ;
        __verbose = false;

        for (int i = 0; i < __width*__height; ++i)
        {
            __grid.push_back(nullptr) ;
        }

    }

    Game::Game(unsigned width, unsigned height, bool manual): __width(width), __height(height)
    // note: manual population by default
    {
        if (height < MIN_HEIGHT || width < MIN_WIDTH)
        {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }


        __numInitAgents = 0;
        __numInitResources = 0;             //__grid.resize(__width * __height);
        __width = width;
        __height = height;
        __verbose = false;
        __status = NOT_STARTED;
        __round = 0;

        for (int i = 0; i < __width*__height; ++i)
        {
            __grid.push_back(nullptr) ;
        }

        if(!manual)
        {
            populate();
        }
    }

    Game::~Game()
    {
        for (int i = 0; i < __grid.size(); ++i)
        {
            if (__grid[i] != nullptr)
            {
                delete __grid[i];
            }
        }
    }

// accessors / getters

    //unsigned int getWidth() const { return __width; }
    //unsigned int getHeight() const { return __height; }

    unsigned int Game::getNumPieces() const
    {
        return getNumAgents()+getNumResources();
    }

    unsigned int Game::getNumAgents() const
    {
        return getNumSimple()+getNumStrategic();
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int numAgents = 0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == SIMPLE)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    unsigned int Game::getNumStrategic() const
    {
        unsigned int numAgents = 0;
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == STRATEGIC)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    unsigned int Game::getNumResources() const
    {
        unsigned int numAgents=0;

        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i]!= nullptr)
            {
                if (__grid[i]->getType() == FOOD || __grid[i]->getType() == ADVANTAGE)
                {
                    numAgents++;
                }
            }
        }
        return numAgents;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {

        if(__grid[((x*__width)+y)] != nullptr)
        {
            return __grid[((x*__width)+y)];
        }

        throw PositionEmptyEx(x,y);
    }

// grid population methods
    void Game::addSimple(const Position &position)
    {

        if ((position.x*__width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }
        if (__grid[position.x * __width + position.y] != nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
        }

        __grid[position.x * __width + position.y] = new Simple(*this, position,STARTING_AGENT_ENERGY);

    }

// used for testing only
    void Game::addSimple(const Position &position, double energy)
    {
        Simple *s = new Simple(*this,position,energy);

        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = s;
    }

    void Game::addSimple(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addSimple(p);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        Position p(x,y);
        this->addSimple(p,energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {
        Strategic *t = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);

        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x, position.y);
        }

        __grid[position.x*__width + position.y] = t;
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        Position p(x,y);
        this->addStrategic(p,s);
    }

    void Game::addFood(const Position &position)
    {
        Food *f = new Food(*this, position, STARTING_RESOURCE_CAPACITY);

        if((position.x*__width + position.y) > __grid.size())
        {
            throw OutOfBoundsEx(__width, __height, position.x, position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = f;
    }

    void Game::addFood(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addFood(p);
    }

    void Game::addAdvantage(const Position &position)
    {
        Advantage *a = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

        if((position.x*__width + position.y)>__grid.size())
        {
            throw OutOfBoundsEx(__width,__height,position.x,position.y);
        }

        if((__grid[position.x*__width + position.y])!=nullptr)
        {
            throw PositionNonemptyEx(position.x,position.y);
        }

        __grid[position.x*__width + position.y] = a;
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        Position p(x,y);
        this->addAdvantage(p);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings temp;
        int tempX = pos.x-1;

        for (int count = 0; count < 3; ++count)
        {
            int tempY = pos.y-1;
            for (int i = 0; i < 3; ++i)
            {
                if(((tempX * __width) + tempY)==((pos.x*__width)+pos.y))
                {
                    temp.array[(count * 3) + i] = SELF;
                }

                else if(tempX < 0 ||tempX >__height-1 || tempY<0 || tempY > __width-1)
                {
                    temp.array[(count * 3) + i] = INACCESSIBLE;
                }

                else if (__grid[(tempX * __width) + tempY] == nullptr)
                {
                    temp.array[(count * 3) + i] = EMPTY;
                }

                else
                {
                    temp.array[(count * 3) + i] = __grid[(tempX * __width) + tempY]->getType();
                }
                tempY++;
            }
            tempX++;

        }
        return temp;
    }

// gameplay methods

    const ActionType Game::reachSurroundings(const Position &from, const Position &to)
    {

        ActionType temp =STAY;
        int xDiff = to.x-from.x;
        int yDiff = to.y-from.y;

        if(xDiff == - 1 && yDiff == - 1)
        {
            temp = NW;
        }
        else if(xDiff == - 1 && yDiff == 0)
        {
            temp = N;
        }
        else if(xDiff == - 1 && yDiff == 1)
        {
            temp =NE;
        }
        else if(xDiff == 0 && yDiff == - 1)
        {
            temp =W;
        }
        else if(xDiff == 0 && yDiff == 0)
        {
            temp =STAY;
        }
        else if(xDiff == 0 && yDiff == 1)
        {
            temp =E;
        }
        else if(xDiff == 1 && yDiff == - 1)
        {
            temp =SW;
        }
        else if(xDiff == 1 && yDiff == 0)
        {
            temp =S;
        }
        else if(xDiff == 1 && yDiff == 1)
        {
            temp =SE;
        }

        return temp;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x, y;
        x = pos.x;
        y = pos.y;
        switch (ac)
        {
            case E: y++;
                break;
            case NE: y++;
                x--;
                break;
            case N: x--;
                break;
            case NW: y--;
                x--;
                break;
            case W: y--;
                break;
            case SW: y--;
                x++;
                break;
            case S: x++;
                break;
            case SE: x++;
                y++;
                break;
            default:
                break;
        }
        Position p((unsigned )x, (unsigned)y);
        if (p.y < __width  && p.x < __height )
            return true;
        return false;
    }

// note: assumes legal, use with isLegal()

    const Position Game::move(const Position &pos, const ActionType &ac) const // note: assumes legal, use with isLegal()
    {

        if (isLegal(ac, pos)) {
            int x, y;
            x = pos.x;
            y = pos.y;
            switch (ac) {
                case E: y++;
                    break;
                case NE: y++;
                    x--;
                    break;
                case N: x--;
                    break;
                case NW: y--;
                    x--;
                    break;
                case W: y--;
                    break;
                case SW: y--;
                    x++;
                    break;
                case S: x++;
                    break;
                case SE: x++;
                    y++;
                    break;
                default:
                    break;
            }
            Position p((unsigned )x, (unsigned)y);
            return p;

        }
        return pos;

    }

// play a single round
    void Game::round() {

        if(__round == 0 && __verbose)
        {
            __status = PLAYING;
            std::cout << std::endl << *this;
        }
        for (int count = 0; count < __grid.size(); ++count)
        {
            if(__grid[count]!= nullptr)
            {
                if(__grid[count]->isViable())
                {
                    if (! __grid[count]->getTurned())
                    {
                        Agent * agent = dynamic_cast<Agent*>(__grid[count]);
                        if(agent)
                        {
                            __grid[count]->setTurned(true);
                            Position currentPos = __grid[count]->getPosition();
                            Surroundings s = getSurroundings(currentPos);
                            ActionType aT = __grid[count]->takeTurn(s);

                            if (aT != STAY)
                            {
                                Position newPos = move(currentPos, aT);
                                int newPosIndx = (newPos.x * __width + newPos.y);
                                (*__grid[count]) * (*__grid[newPosIndx]);

                                if(! __grid[count]->isViable())
                                {
                                    delete __grid[count];
                                    __grid[count]= nullptr;
                                }

                                else
                                {
                                    __grid[count]->setPosition(newPos);

                                    if (__grid[newPosIndx] != nullptr)
                                    {
                                        delete __grid[newPosIndx];
                                        __grid[newPosIndx] = __grid[count];
                                        __grid[count] = nullptr;
                                    }

                                    else
                                    {
                                        __grid[newPosIndx] = __grid[count];
                                        __grid[count] = nullptr;
                                    }
                                }

                                if(! __grid[newPosIndx]->isViable())
                                {
                                    delete __grid[newPosIndx];
                                    __grid[newPosIndx]= nullptr;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < __grid.size(); ++i)
        {
            if(__grid[i] != nullptr)
            {
                if (!__grid[i]->isViable())
                {
                    delete __grid[i];
                    __grid[i] = nullptr;
                }
                else
                {
                    __grid[i]->setTurned(false);
                    __grid[i]->age();
                }
            }
        }
        if(getNumPieces()< 2 || getNumResources() < 1)
        {
            __status = OVER;
        }
        ++__round; //

        if(__verbose)
        {
            std::cout << std::endl << *this;
        }

    }

// play game until over
    void Game::play(bool verbose)
    {
        __verbose = verbose;
        round();

        if(getNumPieces()>1 && getNumResources() > 0)
        {
            play(verbose);
        }
    }

    // Print as follows the state of the game after the last round:
    //
    // Round 1:
    // [F0   ][     ][T1   ]
    // [W2   ][     ][F3   ]
    // [     ][S4   ][     ]
    // Status: Playing...
    //
    // Round 5:
    // [     ][     ][     ]
    // [     ][T1   ][     ]
    // [     ][     ][     ]
    // Status: Over!
    //

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << std::endl;
        for (int count = 0; count < game.__height; ++count)
        {
            for (int i = 0; i < game.__width; ++i)
            {
                os << '[' << std::setw(5) <<std::left << *game.__grid[count*game.__width+i] << ']';
            }
            os << std::endl;
        }
        if(game.__status == Game::NOT_STARTED)
        {
            os << "Status: Not Started...";
        }
        else if(game.__status == Game::PLAYING)
        {
            os << "Status: Playing...";
        }
        else
        {
            os << "Status: Over!";
        }
        return os;
    }

}
