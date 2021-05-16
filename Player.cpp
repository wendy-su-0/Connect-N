// Player.cpp

#include "provided.h"
#include <utility>
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
    int bestMove(AlarmClock& ac, const Scaffold& s, int N, int color);
    int determineBestComputerMove(Scaffold& s, int N, const int color, int& col);
    int determineBestHumanMove(Scaffold& s, int N, const int color, int& col);
    int rateMove(int rating);
    bool checkCompletion(Scaffold& s, int N) const;
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

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color){
    AlarmClock ac(9900);  // will time out after 9.9 seconds
    return bestMove(ac, s, N, color); //someHelperFunction should return the col
}

int SmartPlayerImpl::bestMove(AlarmClock& ac, const Scaffold& s, int N, int color){
    int col = 0;

    Scaffold copy = s;

    //if there is one checker space left, return that col
    if (s.numberEmpty() == 1) {
        for (int i = 1; i <= s.cols(); i++) {
            if (!s.checkerAt(i, s.levels())) {
                return i;
            }
        }
    }

    //call determineBestComputerMove
    determineBestComputerMove(copy, N, color, col);

   /* ... This functionand maybe others that it calls does the
        ... real work.At various points, it can do tests like
        ...      if (ac.timedOut())
        ... to see if it should start wrapping up its work(e.g.,
            ... don't explore further down the game tree; just make a
            ... decision with what you know as far as you've gotten).*/
    return col;
}

int SmartPlayerImpl::determineBestComputerMove(Scaffold& s, int N, const int color, int& col) {
    vector<pair<int, int>> colAndRate;
    
    int rating = 0;
    int maxRating = INT_MIN;
    //first check for any immediate wins
    //add move
    //if game complete, return that move
    for (int i = 1; i <= s.cols(); i++) {
        if (s.makeMove(i, color)) {
            if (checkCompletion(s, N)) {
                col = i;
                return 1;
            }
        }
        
        s.undoMove();
    }
    
    //go through each row
    for (int i = 1; i <= s.cols(); i++) {
        //make move and update scaffold
        if (s.makeMove(i, color)) {
            //use rating function to rate resulting scaffold
            rating = rateMove(rating); //MAYBE CHANGE TO A PASS BY REFERENCE
            //if a win or a tie, remember result of move
            if (rating == 1 || rating == 0) {
                colAndRate.push_back(make_pair(col, rating));
            } //else, determine best human move, get return value, store result
            else {
                rating = determineBestHumanMove(s, N, color, col);
                colAndRate.push_back(make_pair(col, rating));
            }
            //undo trial move
            s.undoMove();
        } 
    }

    //pick best move from scaffold. return the rating. update the column
    for (unsigned int i = 0; i < colAndRate.size(); i++) {
        if (colAndRate[i].second > maxRating) {
            col = colAndRate[i].first;
            rating = colAndRate[i].second;
        }
    }

    //return the move and the score from the move
    return rating; //change just here to compile
}

int SmartPlayerImpl::determineBestHumanMove(Scaffold& s, int N, const int color, int& col) {

    vector<pair<int, int>> colAndRate;

    //flip the color since it is the other player's move
    if (color == RED) {
        color == BLACK;
    }
    else {
        color == RED;
    }

    int rating = 0;
    int minRating = INT_MAX;

    //go through each row
    for (int i = 1; i <= s.cols(); i++) {
        //make move and update scaffold
        if (s.makeMove(i, color)) {
            //use rating function to rate resulting scaffold
            rating = rateMove(rating); //MAYBE CHANGE TO A PASS BY REFERENCE
            //if a win or a tie, remember result of move
            if (rating == -1 || rating == 0) {
                colAndRate.push_back(make_pair(col, rating));
            } //else, determine best human move, get return value, store result
            else {
                rating = determineBestComputerMove(s, N, color, col);
                colAndRate.push_back(make_pair(col, rating));
            }
            //undo trial move
            s.undoMove();
        }
    }

    //pick best move from scaffold. return the rating. update the column
    for (unsigned int i = 0; i < colAndRate.size(); i++) {
        if (colAndRate[i].second < minRating) {
            col = colAndRate[i].first;
            rating = colAndRate[i].second;
        }
    }

    //return the move and the score from the move
    return rating; //change just here to compile
}

int SmartPlayerImpl::rateMove(int rating) {
    return 1;
}

bool SmartPlayerImpl::checkCompletion(Scaffold& s, int N) const {
    int count = 1;
    for (int i = 1; i <= s.levels(); i++) {
        //< because we will always access the j + 1 until j + 1 + n is the edge of cols  so don't want to go off edge
        for (int j = 1; j <= s.cols() - N + 1; j++) {

            for (int n = 0; n < N; n++) {
                //check to see if there is a checker otherwise, go to next column
                if (s.checkerAt(j + n, i) != VACANT) {
                    if (s.checkerAt(j + n, i) == s.checkerAt(j + 1 + n, i)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == N) {
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
    for (int j = 1; j <= s.cols(); j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s.levels() - N + 1; i++) {
            //check to see if there is a checker otherwise, go to next column
            for (int n = 0; n < N; n++) {
                if (s.checkerAt(j, i + n) != VACANT) {
                    if (s.checkerAt(j, i + n) == s.checkerAt(j, i + 1 + n)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == N) {
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
    for (int j = 1; j <= s.cols() - N + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = 1; i <= s.levels() - N + 1; i++) {

            for (int n = 0; n < N; n++) {
                //check to see if there is a checker otherwise, go to next column
                if (s.checkerAt(j + n, i + n) != VACANT) {
                    if (s.checkerAt(j + n, i + n) == s.checkerAt(j + n + 1, i + n + 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return trie
                        if (count == N) {
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
    for (int j = 1; j <= s.cols() - N + 1; j++) {
        //because we will always access the i + 1 until i + 1 + n is the top of levels so don't want to go off edge
        for (int i = s.levels(); i >= N; i--) {
            for (int n = 0; n < N; n++) {
                //check to see if there is a checker otherwise, go to next column
                if (s.checkerAt(j + n, i - n) != VACANT) {
                    //check to see if they are consecutive checker colors for a count of N
                    if (s.checkerAt(j + n, i - n) == s.checkerAt(j + n + 1, i - n - 1)) {
                        count++;

                        //if count is same as nToWin, set winner and return true
                        if (count == N) {return true;
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
