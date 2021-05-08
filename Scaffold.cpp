// Scaffold.cpp

#include "provided.h"
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
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
}

int ScaffoldImpl::cols() const
{
    return 1;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::levels() const
{
    return 1;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::numberEmpty() const
{
    return 1;  //  This is not always correct; it's just here to compile
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    return VACANT;  //  This is not always correct; it's just here to compile
}

void ScaffoldImpl::display() const
{
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
    m_impl = new ScaffoldImpl(nColumns, nLevels);
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
