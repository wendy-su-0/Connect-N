// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col = 0;

    //check if the grid is empty
    if (s.numberEmpty() != 0) {
        //ask user for column
        cout << "Choose your column:" << endl;
        int testCol;
        cin >> testCol;

        //ceck to see if the prompted col is inbounds and able to take in another checker
        while (testCol < 1 || testCol > s.cols() || s.checkerAt(testCol, s.levels()) != VACANT) {
            cout << "Invalid column. Choose again" << endl;
            cin >> testCol;
        }

        col = testCol;
    }

    return col;  //  This is not always correct; it's just here to compile
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col = 0;

    //go through the grid left to right, bottom to top
    for (int i = 1; i <= s.levels(); i++) {
        for (int j = 1; j <= s.cols(); j++) {
            //once it encounters first empty, choose to add a checker in that col
            if (s.checkerAt(j, i) == VACANT) {
                col = j;
                break;
            }
        }

        if (col != 0) {
            break;
        }
    }

    return col;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    return 0;  //  This is not always correct; it's just here to compile
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code. 

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
