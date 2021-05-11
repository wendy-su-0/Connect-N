// Game.cpp

#include "provided.h"
#include <iostream>
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    Scaffold* s;
    Player* m_red;
    Player* m_black;
    int nToWin;
    int m_winner;
    bool redTurn;
    int m_turn;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    s = new Scaffold(nColumns, nLevels);
    m_red = red;
    m_black = black;
    nToWin = N;
    redTurn = true;
    m_turn = 0;
}

bool GameImpl::completed(int& winner) const
{
    //if N of the game is less than 1 it is a tie game because invalid
    if (nToWin < 1) {
        winner = TIE_GAME;
        return true;
    }
    //if N of the game is 1, it is red winner 
    if (nToWin == 1 && m_turn == 1) {
        winner = RED;
        return true;
    }

    //if the board is empty, game is not complete
     
    //if N is more than either the columns or levels, game cannot be a win
    if (nToWin > s->cols() || nToWin > s->levels()) {
        winner = TIE_GAME;
        //if it is full return true
        if (s->numberEmpty() == 0) {
            return true;
        }

        return false;
    } //standard checking the other ones because there is potential to be a win
    
    //if there is a win, return true
    //chck horizontal
    int count = 0;

    //levels because we won't go off edge
    for (int i = 1; i <= s->levels(); i++) {
        //< because we will always access the j + 1 until j + 1 + n is the edge of cols  so don't want to go off edge
        for (int j = 1; j <= s->cols() - nToWin + 1; j++) {
            //check to see if there is a checker otherwise, go to next column
            if (s->checkerAt(j, i) != VACANT) {
                //check to see if they are consecutive checker colors for a count of N
                for (int n = 0; n <= nToWin; n++) {
                    if (s->checkerAt(j, i) == s->checkerAt(j + 1, i)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j, i);
                            return true;
                        }
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }
    }

    count = 0;

    //check vertical
    //j are cols, i are levels
    for (int j = 1; j <= s->cols(); j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s->levels() - nToWin + 1; i++) {
            //check to see if there is a checker otherwise, go to next column
            if (s->checkerAt(j, i) != VACANT) {
                //check to see if they are consecutive checker colors for a count of N
                for (int n = 0; n <= nToWin; n++) {
                    if (s->checkerAt(j, i) == s->checkerAt(j, i + 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j, i);
                            return true;
                        }
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }
    }

    count = 0;

    //check diagonal from bottom left to top right
    for (int j = 1; j <= s->cols() - nToWin + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s->levels() - nToWin + 1; i++) {
            //check to see if there is a checker otherwise, go to next column
            if (s->checkerAt(j, i) != VACANT) {
                //check to see if they are consecutive checker colors for a count of N
                for (int n = 0; n <= nToWin; n++) {
                    if (s->checkerAt(j, i) == s->checkerAt(j + 1, i + 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j, i);
                            return true;
                        }
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }
    }

    //check diagonal from top left to bottom right
    for (int j = 1; j <= s->cols() - nToWin + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = s->levels(); i >= s->levels() - nToWin + 1; i++) {
            //check to see if there is a checker otherwise, go to next column
            if (s->checkerAt(j, i) != VACANT) {
                //check to see if they are consecutive checker colors for a count of N
                for (int n = 0; n <= nToWin; n++) {
                    if (s->checkerAt(j, i) == s->checkerAt(j + 1, i - 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j, i);
                            return true;
                        }
                    }
                    else {
                        count = 0;
                    }
                }
            }
        }
    }

    //if the scaffold is full, game over and tie because no winner was decalred earlier
    if (s->numberEmpty() == 0) {
        winner = TIE_GAME;
        return true;
    }

    return false;  //  This is not always correct; it's just here to compile
}

bool GameImpl::takeTurn()
{
    if (completed(m_winner)) {
        return false;
    }

    //steps for red player turn
    if (redTurn) {
        //player move
        int col = m_red->chooseMove(*s, nToWin, RED);

        //update scaffold
        s->makeMove(col, RED);
    }

    //steps for black player truen
    if (!redTurn) {
        //player move
        int col = m_black->chooseMove(*s, nToWin, BLACK);

        //update scaffold
        s->makeMove(col, BLACK);
    }

    //switch player turn
    redTurn = !redTurn;

    //add to turn counter
    m_turn++;

    return true; 
}

void GameImpl::play()
{
    //when game isn't complete, continue play steps
    while (!completed(m_winner)) {
        //if neither is interactive,  time delay
        if (!m_red->isInteractive() && !m_black->isInteractive()) {
            cout << "Press ENTER to continue to next turn." << endl;
            cin.ignore(10000, '\n');
            takeTurn();
            s->display();
        }
        else {
            takeTurn();
            s->display();
        }
        //play steps: take turn, display grid

    }

    //when game is complete, check who is winner
    switch (m_winner) {
        case RED:
            cout << "Red is the winner! Played by " << m_red->name() << endl;
            break;
        case BLACK:
            break;
            cout << "Black is the winner! Payed by " << m_black->name() << endl;
        case TIE_GAME:
            cout << "This was a tie game" << endl;
            break;
    }
        
}

int GameImpl::checkerAt(int c, int r) const
{
    int sChecker = s->checkerAt(c, r);
    return sChecker; 
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
