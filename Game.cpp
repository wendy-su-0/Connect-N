// Game.cpp

#include "provided.h"

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
}

bool GameImpl::completed(int& winner) const
{
    return true;  //  This is not always correct; it's just here to compile
}

bool GameImpl::takeTurn()
{
    return false;  //  This is not always correct; it's just here to compile
}

void GameImpl::play()
{
}

int GameImpl::checkerAt(int c, int r) const
{
    return VACANT;  //  This is not always correct; it's just here to compile
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
