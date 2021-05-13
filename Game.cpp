// Game.cpp

#include "provided.h"
#include <string>
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
    m_winner = BLACK;
}

bool GameImpl::completed(int& winner) const
{
    cerr << winner << endl;
    //cout << "test completion" << endl;
    //if N of the game is less than 1 it is a tie game because invalid
    if (nToWin < 1) {
        cout << "invalid n" << endl;
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
        cout << "n too large" << endl;
        winner = TIE_GAME;
        //if it is full return true
        if (s->numberEmpty() == 0) {
            return true;
        }

        return false;
    } //standard checking the other ones because there is potential to be a win
    
    //if there is a win, return true
    //chck horizontal
    int count = 1;
    for (int i = 1; i <= s->levels(); i++) {
        //< because we will always access the j + 1 until j + 1 + n is the edge of cols  so don't want to go off edge
        for (int j = 1; j <= s->cols() - nToWin + 1; j++) {

            for (int n = 0; n < nToWin; n++) {
                //check to see if there is a checker otherwise, go to next column
                if (checkerAt(j + n, i) != VACANT) {
                    if (checkerAt(j + n, i) == checkerAt(j + 1 + n, i)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = checkerAt(j + n, i);
                            return true;
                        }
                    }
                    else {
                        count = 1;
                    }
                }
                else {
                    count = 1;
                    break;
                }
            }
        }
    }

    count = 1;

    //check vertical
    //j are cols, i are levels
    for (int j = 1; j <= s->cols(); j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s->levels() - nToWin + 1; i++) {
            //check to see if there is a checker otherwise, go to next column
            for (int n = 0; n < nToWin; n++) {
                if (checkerAt(j, i + n) != VACANT) {
                    if (checkerAt(j, i + n) == checkerAt(j, i + 1 + n)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j, i + n);
                            return true;
                        }
                    }
                    else {
                        count = 1;
                    }
                }
                else {
                    count = 1;
                    break;
                }
            }
            
        }
    }

    count = 1;

    //check diagonal from bottom left to top right
    for (int j = 1; j <= s->cols() - nToWin + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s->levels() - nToWin + 1; i++) {
            
            for (int n = 0; n < nToWin; n++) {
                //check to see if there is a checker otherwise, go to next column
                if (s->checkerAt(j + n, i + n) != VACANT) {
                    if (s->checkerAt(j + n, i + n) == s->checkerAt(j + n + 1, i + n + 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == nToWin) {
                            winner = s->checkerAt(j + n, i + n);
                            return true;
                        }
                    }
                    else {
                        count = 1;
                    }
                }
                else {
                    count = 1;
                    break;
                }
            }
        }
    }

    count = 1;

    //check diagonal from top left to bottom right
    for (int j = 1; j <= s->cols() - nToWin + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = s->levels(); i >= nToWin; i--) {
            for (int n = 0; n < nToWin; n++) {
                cerr << "print count: " << count << endl;
                cerr << "j is: " << j + n << ". i is: " << i - n << endl;
                cerr << "checker at is: " << checkerAt(j + n, i - n) << endl;
                //check to see if there is a checker otherwise, go to next column
                if (s->checkerAt(j + n, i - n) != VACANT) {
                    //check to see if they are consecutive checker colors for a count of N
                    if (s->checkerAt(j + n, i - n) == s->checkerAt(j + n + 1, i - n - 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return true
                        if (count == nToWin) {
                            winner = s->checkerAt(j + n, i - n);
                            cout << "winner is" << winner << endl;
                            return true;
                        }
                    }
                    else {
                        count = 1;
                    }

                }
                else {
                    count = 1;
                    break;
                }
            }
        }
    }

    //if the scaffold is full, game over and tie because no winner was decalred earlier
    if (s->numberEmpty() == 0) {
        cout << "scaffold full" << endl;
        winner = TIE_GAME;
        return true;
    }

    cerr << winner << endl;
    return false;  //  This is not always correct; it's just here to compile
}

bool GameImpl::takeTurn()
{
    /*if (completed(m_winner)) {
        return false;
    }*/

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
        }

        takeTurn();
        s->display();
        //play steps: take turn, display grid

    }


    //when game is complete, check who is winner
    switch (m_winner) {
        case RED:
            cout << "Red is the winner! Played by " << m_red->name() << endl;
            break;
        case BLACK:
            cout << "Black is the winner! Played by " << m_black->name() << endl;
            break;
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
