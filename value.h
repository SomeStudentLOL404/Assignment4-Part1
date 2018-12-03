/*
 * value.h
 */

#ifndef VALUE_H_
#define VALUE_H_
#include "parsetree.h"
#include <string>
#include <iostream>
using namespace std;

// object holds boolean, integer, or string, and remembers which it holds
class Value {
	bool		bval;
	int		ival;
	string	sval;
	enum VT { isBool, isInt, isString, isTypeError } type;

public:
	Value() : bval(false), ival(0), type(isTypeError) {}
	Value(bool bval) : bval(bval), ival(0), type(isBool) {}
	Value(int ival) : bval(false), ival(ival), type(isInt) {}
	Value(string sval) : bval(false), ival(0), sval(sval), type(isString) {}

	// in the case of an error, I use the value to hold the error message
	Value(string sval, bool isError) : bval(false), ival(0), sval(sval), type(isTypeError) {}

	bool isBoolType() const { return type == VT::isBool; }
	bool isIntType() const { return type == VT::isInt; }
	bool isStringType() const { return type == VT::isString; }
	bool isError() const { return type == VT::isTypeError; }
	bool hasMessage() const { return isError() && sval.size() > 0; }

	bool isTrue() const { return isBoolType() && bval; }
	bool getBoolean() const {
		if( !isBoolType() )
			throw "Not boolean valued";
		return bval;
	}

	int getInteger() const {
		if( !isIntType() )
			throw "Not integer valued";
		return ival;
	}

	string getString() const {
		if( !isStringType() )
			throw "Not string valued";
		return sval;
	}

	string getMessage() const {
		if( !hasMessage() )
			throw "No message";
		return sval;
	}

	friend ostream& operator<<(ostream& out, const Value& v) {
		if( v.type == VT::isBool ) out << (v.bval ? "True" : "False");
		else if( v.type == VT::isInt ) out << v.ival;
		else if( v.type == VT::isString ) out << v.sval;
		else if( v.sval.size() > 0 ) out << "RUNTIME ERROR " << v.sval;
		else out << "TYPE ERROR";
		return out;
	}
    //this == left & v == right
    
    //
    //Operator +
	Value operator+(const Value& v)
    {
     if(this->isIntType() && v.isIntType())
     {
      int response = this->getInteger() + v.getInteger();
      return response;
     }
    if(this->isStringType() && v.isStringType())
    {
       string responser = this->getString() + v.getString();
       return responser;
    }
     else
     {
       Value errorMessage = Value("These arent two integers (value.h file - operator+)", true);
       return errorMessage;
     }   
    }
    //Operator -
	Value operator-(const Value& v)
    {
     if(this->isIntType() && v.isIntType())
     {
      int response = this->getInteger() - v.getInteger();
      return response;
     }
     else
     {
      Value errorMessage = Value("These arent two integers (value.h file - operator-)", true);
      return errorMessage;
     }   
    }
    //Check PDF - We can multiply numbers or even strings .e.g 2*hello
    //Operator *
	Value operator*(const Value& v)
    {   
        //2*hello - hellohello
        if(this->isIntType() && v.isStringType())
        {
            /*
            Check to see if were multiplying a string by a positive number
            e.g. hello*2 and not hello*-2
            If its positive, loop and add it to a string
            */
            if(this->getInteger() > 0)
            {
                string addit;
                for(int i = 0; i < this->getInteger(); i++)
                {
                 addit = addit + v.getString();
                }
                return addit;
            }
            else
            {
             Value errorMessage = Value("You cant use a negative integer! (operator* p1)", true);
             return errorMessage;
            }
        }
        //hello*2
        //hellohello
        else if(this->isStringType() && v.isIntType())
        {
            /*
            Check to see if were multiplying a string by a positive number
            e.g. hello*2 and not hello*-2
            If its positive, loop and add it to a string
            */
            if(v.getInteger() > 0)
            {
                string addit;
                for(int i = 0; i < v.getInteger(); i++)
                {
                 addit = addit + this->getString();
                }
                return addit;
            }
            else
            {
              Value errorMessage = Value("You cant use a negative integer! (operator* p2)", true);
             return errorMessage;   
            }
        }
        else
        {
         Value errorMessage = Value("These arent two integers (value.h file - operator '/' )", true);
         return errorMessage;
        } 
    }   
    //Operator / (Division)
	Value operator/(const Value& v)
    {
     if(this->isIntType() && v.isIntType())
     {
      int response = this->getInteger() / v.getInteger();
      return response;
     }
     else
     {
      Value errorMessage = Value("These arent two integers (value.h file - operator '/' )", true);
      return errorMessage;
     }   
    }
    //Operator < 
	Value operator<(const Value& v)
    {
       if(this->isIntType() && v.isIntType())
       {
         bool response = this->getInteger() < v.getInteger();
         return response;
       }
       else if (this->isStringType() && v.isStringType())
       {
         bool response = this->getString() < v.getString();
         return response;
       }
       else
       {
       Value errorMessage = Value("You cant compare these two (value.h file - operator '<' )", true);
       return errorMessage;  
       }
    }
    //Operator <=
	Value operator<=(const Value& v)
    {
     if(this->isIntType && v.isIntType())
     {
      bool response = this->getInteger() <= v.getInteger();
      return response;
     }
     else if(this->isStringType && v.isStringType())
     {
      bool response = this->getString() <= v.getString();
      return response;   
     }
      else
      {
       Value errorMessage = Value("You cant compare these two (value.h file - operator '<=' )", true);
       return errorMessage;     
      }
    }
    //Operator >
	Value operator>(const Value& v)
    {
         if(this->isIntType && v.isIntType())
         {
          bool response = this->getInteger() > v.getInteger();
          return response;
         }
         else if(this->isStringType && v.isStringType())
         {
          bool response = this->getString() > v.getString();
          return response;   
         }
       else
       {
       Value errorMessage = Value("You cant compare these two (value.h file - operator '>' )", true);
       return errorMessage;  
       }
    }
    //Operator >=
	Value operator>=(const Value& v)
    {
     if(this->isIntType && v.isIntType())
     {
      bool response = this->getInteger() >= v.getInteger();
      return response;
     }
     else if(this->isStringType && v.isStringType())
     {
      bool response = this->getString() >= v.getString();
      return response;   
     }
      else
      {
       Value errorMessage = Value("You cant compare these two (value.h file - operator '<=' )", true);
       return errorMessage;     
      }      
    }
    //Operator ==
	Value operator==(const Value& v)
    {
     if(this->isIntType && v.isIntType())
     {
      bool response = this->getInteger() == v.getInteger();
      return response;
     }
     else if(this->isStringType && v.isStringType())
     {
      bool response = this->getString() == v.getString();
      return response;   
     }
     else if(this->isBoolType && v.isBoolType())
     {
      bool response = this->getString() == v.getString();
      return response;   
     }
      else
      {
       Value errorMessage = Value("You cant compare these two (value.h file - operator '==' )", true);
       return errorMessage;     
      }    
    }
    //Operator !=
	Value operator!=(const Value& v) {
		Value ans = this->operator==(v);
		ans.bval = !ans.bval;
		return ans;
	}
};

#endif /* VALUE_H_ */
