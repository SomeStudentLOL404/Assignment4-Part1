/*
 * parsetree.h
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "value.h"
using namespace std;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE, BOOLTYPE, IDENTTYPE };


// a "forward declaration" for a class to hold values
class Value;


//--Added map called SYMBOLS
static map<string, Value> SYMBOLS;

class ParseTree {
	int			linenum;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLinenum() const { return linenum; }

	virtual NodeType GetType() const { return ERRTYPE; }

	int LeafCount() const {
		int lc = 0;
		if( left ) lc += left->LeafCount();
		if( right ) lc += right->LeafCount();
		if( left == 0 && right == 0 )
			lc++;
		return lc;
	}
    //Other Methods
    int StringCount() const {
        int sc = 0;
        if( left ) sc += left->StringCount();
        if( right ) sc += right->StringCount();
        if((*this).GetType() == STRTYPE)
            sc++;
        return sc;
    }
    int IdentCount() const {
        int id = 0;
        if( left ) id += left->IdentCount();
        if( right ) id += right->IdentCount();
        if((*this).GetType() == IDENTTYPE)
            id++;
        return id;
    }

    //--
    /*
    This function will evulate all valid inputs and attempt to compute them
    to get a valid result. E.g. If input is: 2 PLUS 2
    (The PLUS will refer to AddExpr)
    It would do 2+2=4
    */
    virtual Value Eval (map <string, Value> SYMBOLS) = 0;
};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
    
};

class IfStatement : public ParseTree {
public:
	IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class Assignment : public ParseTree {
public:
	Assignment(int line, ParseTree *lhs, ParseTree *rhs) : ParseTree(line, lhs, rhs) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class PrintStatement : public ParseTree {
public:
	PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class PlusExpr : public ParseTree {
public:
	PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class MinusExpr : public ParseTree {
public:
	MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class TimesExpr : public ParseTree {
public:
	TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class DivideExpr : public ParseTree {
public:
	DivideExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class LogicAndExpr : public ParseTree {
public:
	LogicAndExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class LogicOrExpr : public ParseTree {
public:
	LogicOrExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class EqExpr : public ParseTree {
public:
	EqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class NEqExpr : public ParseTree {
public:
	NEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class LtExpr : public ParseTree {
public:
	LtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0 ;}
};

class LEqExpr : public ParseTree {
public:
	LEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
   Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class GtExpr : public ParseTree {
public:
	GtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class GEqExpr : public ParseTree {
public:
	GEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class IConst : public ParseTree {
	int val;

public:
	IConst(int l, int i) : ParseTree(l), val(i) {}
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }
    //--
    /*
    Declaring the actual Evan function
    */
    //virtual Value Eval (map <string, Value> SYMBOLS) = 0;
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class BoolConst : public ParseTree {
	bool val;

public:
	BoolConst(Token& t, bool val) : ParseTree(t.GetLinenum()), val(val) {}

	NodeType GetType() const { return BOOLTYPE; }
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class SConst : public ParseTree {
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	NodeType GetType() const { return STRTYPE; }
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

class Ident : public ParseTree {
	string id;

public:
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}
    NodeType GetType() const { return IDENTTYPE; }
    
    //--
    Value Eval (map <string, Value> SYMBOLS) { return 0; }
};

#endif /* PARSETREE_H_ */



