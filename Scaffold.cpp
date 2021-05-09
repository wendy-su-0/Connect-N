// Scaffold.cpp

#include "provided.h"
#include <vector>
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
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    //check valid scaffold
    if (nColumns < 1 || nLevels < 1) {
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

    cerr << "scaffold made" << endl;

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
    return VACANT;  //  This is not always correct; it's just here to compile
}

void ScaffoldImpl::display() const
{
    for (int i = m_levels; i >= 0; i--) {
        
        for (int j = 0; j < m_gridCols; j++) {
            cout << m_grid[i][j];
        }
        
        cout << endl;
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    return false;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::undoMove()
{
    return 0;  //  This is not always correct; it's just here to compile
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
