// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
    public:
        ScaffoldImpl(int nColumns, int nLevels); 
        int cols() const;
        int levels() const;
        int numberEmpty() const;
        int checkerAt(int column, int level) const; 
        void display() const; 
        bool makeMove(int column, int color); 
        int undoMove(); 
    private:
        int m_levels;
        int m_cols;
        vector<vector<char>> m_grid;
        int m_gridLevels;
        int m_gridCols;
        stack<int> m_moveColor; //CONSIDER GETTING RID OF THIS ONE IM NOT USING IT ATM
        stack<int> m_moveColumn;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    //check valid scaffold
    if (nColumns < 0 || nLevels < 0) {
        cerr << "Cannot have negative number of columns/levels" << endl;
        //exit(0);
    }

    //set member vars
    m_cols = nColumns;
    m_levels = nLevels;
    m_gridCols = m_cols * 2 + 1;
    m_gridLevels = m_levels + 1;

    //resize grid
    //if scaffold is 4 cols 3 levels, the grid has 0-8 cols and 0-3 levels, cols + 1 and levels + 1
    m_grid.resize(m_gridLevels);  // grid now has M empty rows
    for (int i = 0; i < m_gridLevels; i++) {
        m_grid[i].resize(m_gridCols);  // row i now has N columns
    }

    //populate grid
    //bottom row
    for (int i = 0; i < m_gridCols; i++) {
        if (i % 2 == 0) {
            m_grid[0][i] = '+';
        }
        else {
            m_grid[0][i] = '-';
        }
    }
    
    //rest of the rows
    for (int i = 1; i < m_gridLevels; i++) {
        for (int j = 0; j < m_gridCols; j++) {
            if (j % 2 == 0) {
                m_grid[i][j] = '|';
            }
            else {
                m_grid[i][j] = ' ';
            }
        }
    }

    //cerr << "scaffold made" << endl;

}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    int numEmpty = 0;

    //go through grid. if there is a space, it is empty, add to numEmpty
    for (int i = 1; i < m_gridLevels; i++) {
        for (int j = 0; j < m_gridCols; j++) {
            if (m_grid[i][j] == ' ') {
                numEmpty++;
            }
        }
    }

    return numEmpty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    //check valid coordinate
    if (column < 0 || column > m_cols || level < 0 || level > m_levels) {
        return VACANT;
    }

    //if red return red
    if (m_grid[level][column * 2 - 1] == 'R') {
        return RED;
    }

    //if black return black
    if (m_grid[level][column * 2 - 1] == 'B') {
        return BLACK;
    }

    //empty return vacant
    return VACANT; 
}

void ScaffoldImpl::display() const
{
    //prints grid level by level from the top down
    for (int i = m_levels; i >= 0; i--) {
        
        //print columns from left to right
        for (int j = 0; j < m_gridCols; j++) {
            cout << m_grid[i][j];
        }
        
        cout << endl;
    }
}

//use a stack of moves to track moves
bool ScaffoldImpl::makeMove(int column, int color)
{
    //if column is valid range
    if (column < 1 || column > m_cols) {
        return false;
    }

    //check if column is full
    bool colFull = true;
    int levelAdd = -1;

    //start at the bottom of grid where checkers can be and go up
    for (int i = 1; i < m_levels; i++) {
        //if there isn't a checker at that level
        if (m_grid[i][column*2 - 1] == ' ') {
            //column is not full
            colFull = false;
            //the empty level is now i
            levelAdd = i;
            break;
        }
    }

    //if the column is full
    if (colFull) {
        return false;
    }

    //if color is valid
    if (color != RED && color != BLACK) {
        return false;
    }

    //update the grid
    if (color == RED) {
        m_grid[levelAdd][column * 2 - 1] = 'R';
    } 

    if (color == BLACK) {
        m_grid[levelAdd][column * 2 - 1] = 'B';
    }

    //push to stack
    m_moveColor.push(color);
    m_moveColumn.push(column);

    return true;  
}

//use a stack of moves to track moves
int ScaffoldImpl::undoMove()
{
    //if the stack is not empty
    if (!m_moveColumn.empty()) {
        //get the top of the column stack
        int col = m_moveColumn.top();

        //remove the top of the color and column stacks
        m_moveColumn.pop();
        m_moveColor.pop();

        //start at the top of levels and go down from there
        for (int i = m_levels; i >= 1; i--) {
            //if there is a checker at that row and and column
            if (m_grid[i][col*2 - 1] != ' ') {
                //make the space blank to undo move
                m_grid[i][col * 2 - 1] = ' ';
            }
        }

        return col;
    }
    
    //if stack is empty, return 0
    return 0; 
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code. 

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels); //maybe add code to terminate if its not postive
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
