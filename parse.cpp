//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

//#define DO_OUTPUT(str) std::cout << str << std::endl
#define DO_OUTPUT(str)

//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
    DO_OUTPUT("FindPROG");
    
    if (!FindSTMTS()) return false;
    
    DO_OUTPUT("CHECKING FOR END");
    
    int token = PeekToken();
    AdvanceToken();

    if (token == END)
    {
        return true;
    }
    else
    {
        Error("end");
    }

    return false;
}
//*******************************************
bool FindSTMTS()
{
    DO_OUTPUT("FindSTMTS");
    
    while (FindSTMT()) {}
    return true;
}
//*******************************************
bool FindSTMT()
{
    DO_OUTPUT("FindSTMT");
    
    bool wasValid = FindEXPR();
    
    int token = PeekToken();
    if (token == END)
    {
        return false;
    }
    else if (token != ';')
    {
        if (wasValid)
            Error(";");
        
        while (token != ';') 
        {
            //std::cout << "JunkToken: " << token << ":" << char(token) << std::endl;
            AdvanceToken();
            token = PeekToken();
        }
    }
    else
    {
        std::cout << "Found a statement" << std::endl;
    }
    
    //std::cout << "EOL Token: " << char(token) << std::endl << std::endl;
    
    AdvanceToken();
    return true;
}
//*******************************************
bool FindEXPR()
{
    DO_OUTPUT("FindEXPR");
    
    int token = PeekToken();
    if (token == '(')
    {
        AdvanceToken();
        
        if(!FindEXPR()) return false;
        
        token = PeekToken();
        
        if (token == ')')
        {
            AdvanceToken();
            if (FindEXPR_P()) return true;
        }
        else
        {
            Error(")");
        }
        
    }
    else
    {
        if (FindTERM()) return true;
    }
    return false;
}
//*******************************************
bool FindEXPR_P()
{
    DO_OUTPUT("FindEXPR_P");

    if (FindPLUSOP())
    {
        int token = PeekToken();
        if (token == '(')
        {
            AdvanceToken();
            
            if(!FindEXPR()) return false;

            token = PeekToken();
            if (token == ')')
            {
                AdvanceToken();
                return FindEXPR_P();
            }
            else
            {
                Error(")");
                return false;
            }
        }
        else
        {
            Error("(");
            return false;
        }
    }
    return true;
}
//*******************************************
bool FindPLUSOP()
{
    DO_OUTPUT("FindPLUSOP");
    
    int token = PeekToken();
    if (token == '+' || token == '-')
    {
        AdvanceToken();
        return true;
    }
    return false;
}
//*******************************************
bool FindTERM()
{
    DO_OUTPUT("FindTERM");
    
    int token = PeekToken();
    if (token == '[')
    {
        AdvanceToken();
        
        if(!FindEXPR()) return false;
        
        token = PeekToken();
        
        if (token == ']')
        {
            AdvanceToken();
            if (FindTERM_P()) return true;
        }
        else
        {
            Error("]");
        }
        
    }
    else
    {
        if (token == INT_VAL)
        {
            AdvanceToken();
            return true;
        }
    }
    
    return false;
}
//*******************************************
bool FindTERM_P()
{
    DO_OUTPUT("FindTERM_P");
    
    if (FindTIMESOP())
    {
        int token = PeekToken();
        if (token == '[')
        {
            AdvanceToken();
            
            if(!FindEXPR()) return false;

            token = PeekToken();
            if (token == ']')
            {
                AdvanceToken();
                return FindTERM_P();
            }
            else
            {
                Error("]");
                return false;
            }
        }
        else
        {
            Error("[");
            return false;
        }
    }
    return true;
}
//*******************************************
bool FindTIMESOP()
{
    DO_OUTPUT("FindTIMESOP");
    
    int token = PeekToken();
    if (token == '*' || token == '/')
    {
        AdvanceToken();
        return true;
    }
    return false;
}

