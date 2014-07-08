/*! 
 *	 titanInt.cc
 * 
 *  titanInt class source file.
 * 
 *  Author: Mike Ricci
 *  Date: 20140629
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "titanInt.h"

//CONSTRUCTORS

titanInt::titanInt() // default constructor
{

}

titanInt::titanInt(std::string str) //conversion constructor
{
	for(auto it = str.begin(); it != str.end(); ++it) 
	{
		if(it == str.begin())
		{
			if(*it == '-')
			{
				this->digits[0] = -1; // denotes a negative value
			}
			else
			{
				this->digits[0] = 1; // denotes a positive value
				this->digits.insert(this->digits.begin()+1,*it - 48); // subtract 48 to reflect int value
			}
		}
		else if(it > str.begin())
		{
			this->digits.insert(this->digits.begin()+1,*it - 48); // subtract 48 to reflect int value
		}
	}
}

//DESTRUCTOR
titanInt::~titanInt()
{

}

//MEMBER FUNCTIONS

//The function addDigit() provides a public setter for vector::push_back().
void titanInt::addDigit()
{
	this->digits.push_back(0);
}

//The function getAbs() returns the absolute value of the passed titanInt
titanInt titanInt::getAbs() const
{
	titanInt temp = *this;
	temp.setDigit(0, 1);
	return temp;
}

//The function getDigit() returns the integer digit at i
int titanInt::getDigit(int i) const
{
	return this->digits[i];
}

//The function getSize() returns the size of the titanInt's digits vector as an int.
int titanInt::getSize() const
{
	return this->digits.size();
}

//The function setDigit() sets the digit at i to the int val, provided val is 0-9
void titanInt::setDigit(int i, int val)
{
	if(val >= 0 && val <= 9) // setting a digit value?
	{
		this->digits[i] = val;
	}
	else if(val == -1 && i == 0) // setting the sign value?
	{
		this->digits[i] = val;
	}
	else // out of bounds?
	{
		std::cout << "setDigit() error: int val out of bounds of 0 to 9" << '\n';
	}
}

//The function setSize() initializes the digits vector to the number of digits passed
void titanInt::setSize(int numDigits)
{
	for(int i = 0; i < numDigits; ++i)
	{
		this->digits.insert(this->digits.begin()+1, 0);
	}
}

//The function toConstChar() returns the titanInt object as a const char*.
const char* titanInt::toConstChar() const
{
	std::stringstream ss;
	
	for(auto it = this->digits.end(); it!= this->digits.begin(); --it)
	{
		if(it == this->digits.begin())
		{
			if(*it == -1)
			{
				ss << '-';
				++it;
			}
			else
			{
				++it;
			}
		}

	ss << *it;
	}
	
	return (ss.str()).c_str();
}

//The function toString() returns the titanInt as a string
std::string titanInt::toString() const
{
	std::stringstream ss;
	int numDigits = this->getSize() - 1; // ignore int denoting sign
	if(this->getDigit(0) == -1) // is this titanInt negative?
	{
		ss << '-';
	}
	
	for(int i = numDigits; i > 0; --i) // walk through digits end to begin+1
	{
		ss << this->getDigit(i);
	}

	return ss.str();
}

//The function trimZeros() removes leading zeros, if any exist
void titanInt::trimZeros()
{
	bool cont = true;
	
	do
	{
		if(this->getDigit(this->getSize()-1) == 0) // inspect last digit element
		{
			//trim extra element if it is a zero
			this->digits.resize(this->getSize()-1);
		}
		else
		{
			cont = false; //stop trimming if leading digit is nonzero
		}

	} while(cont == true);
}

//OVERLOADED OPERATORS

//Stream insertion
std::ostream& operator<<(std::ostream& output, const titanInt& x)
{
	output << x.toString();
	return output;
}

//Less than
bool operator<(const titanInt&x, const titanInt& y) // x < y ?
{
	if(x.getDigit(0) == -1 && y.getDigit(0) == 1) // x is neg and y is pos
	{
		return true;
	}
	else if(x.getDigit(0) == 1 && y.getDigit(0) == -1) // x is pos and y is neg
	{
		return false;
	}
	else if(x.getDigit(0) == -1 && y.getDigit(0) == -1) // both are neg
	{
		if(x.getSize() < y.getSize()) // x is a smaller neg num than y
		{
			return false;
		}
		else if(x.getSize() > y.getSize()) // x is a larger neg num than y
		{
			return true;
		}
		else if(x.getSize() == y.getSize())
		{
			for(int i = x.getSize()-1; i > 0; --i)
			{
				if(x.getDigit(i) < y.getDigit(i)) // x is a smaller neg num than y
				{
					return false;
				}
				else if(x.getDigit(i) > y.getDigit(i)) // x is a larger neg num than y
				{
					return true;
				}
			}
			return false; // x and y are equal
		}
	}
	else if(x.getDigit(0) == 1 && y.getDigit(0) == 1) // both are pos
	{
		if(x.getSize() < y.getSize()) // x is a smaller pos num than y
		{
			return true;
		}
		else if(x.getSize() > y.getSize()) // x is a larger pos num than y
		{
			return false;
		}
		else if(x.getSize() == y.getSize())
		{
			for(int i = x.getSize()-1; i > 0; --i)
			{
				if(x.getDigit(i) < y.getDigit(i)) // x is a smaller pos num than y
				{
					return true;
				}
				else if(x.getDigit(i) > y.getDigit(i)) // x is a larger pos num than y
				{
					return false;
				}
			}
			return false; // x and y are equal
		}
	}	
}

//Greater than
bool operator>(const titanInt&x, const titanInt& y) // x > y ?
{
	if(x < y)
	{
		return false;
	}
	else if(y < x)
	{
		return true;
	}
	else // x and y are equal
	{
		return false;
	}
}

//Equality
bool operator==(const titanInt&x, const titanInt& y) // x == y ?
{
	if(x < y)
	{
		return false;
	}
	else if(y < x)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//The non-member function helper() assists in operator+() calculations.
titanInt helper(const titanInt& x, const titanInt& y)
{
	//x.Abs() > y.Abs(), ensured by operator+
	
	titanInt res;
	res.setSize(x.getSize()-1);
	int carry = 0;
	int sum = 0;
	int i;
	
	for(i = 1; i <= x.getSize()-1; ++i)
	{
		sum = x.getDigit(i)*x.getDigit(0) + y.getDigit(i)*y.getDigit(0) + carry;
		
		if(i > y.getSize()-1)
		{
			sum = x.getDigit(i)*x.getDigit(0) + carry;
		}

		if(sum < 0)
		{
			sum += 10;
			carry = -1;
		}
		else if(sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}

		res.setDigit(i, sum);
	}

	if(carry == 1)
	{
		res.addDigit();
		res.setDigit(i, 1);
	}
	else if (carry == -1)
	{
		res.setDigit(i, res.getDigit(i)-1);
	}

	return res;

}

//Addition
titanInt operator+(const titanInt& x, const titanInt& y)
{
	titanInt tempX = x; // a titanInt to store a transform of x if necessary
	titanInt tempY = y; // a titanInt to store a transform of y if necessary
	titanInt result; // a titanInt to store the result of the computation

	if(x.getDigit(0) == 1 && y.getDigit(0) == 1) // pos x, pos y
	{
		if(x.getAbs() > y.getAbs())
		{
			result = helper(x,y);
			result.trimZeros();
		}
		else if(x.getAbs() == y.getAbs())
		{
			result = helper(x,y);
			result.trimZeros();
		}
		else if(x.getAbs() < y.getAbs())
		{
			result = helper(y,x);
			result.trimZeros();
		}

		result.setDigit(0,1);
	}
	else if(x.getDigit(0) == 1 && y.getDigit(0) == -1) // pos x, neg y
	{
		tempX.setDigit(0,-1);
		tempY.setDigit(0,1);
		
		if(x.getAbs() > y.getAbs())
		{
			result = helper(x,y);
			result.setDigit(0,1);
			result.trimZeros();
		}
		else if(x.getAbs() == y.getAbs())
		{
			result = 0;
			result.setDigit(0,1);
		}
		else if(x.getAbs() < y.getAbs())
		{
			result = helper(tempY,tempX);
			result.setDigit(0,-1);
			result.trimZeros();
		}
	}
	else if(x.getDigit(0) == -1 && y.getDigit(0) == 1) // neg x, pos y
	{
		tempX.setDigit(0,1);
		tempY.setDigit(0,-1);
		
		if(x.getAbs() > y.getAbs())
		{
			result = helper(tempX,tempY);
			result.setDigit(0,-1);
			result.trimZeros();
		}
		else if(x.getAbs() == y.getAbs())
		{
			result = 0;
			result.setDigit(0,1);
		}
		else if(x.getAbs() < y.getAbs())
		{
			result = helper(x,y);
			result.setDigit(0,1);
			result.trimZeros();
		}
	}
	else if (x.getDigit(0) == -1 && y.getDigit(0) == -1) // neg x, neg y
	{
		tempX.setDigit(0,1);
		tempY.setDigit(0,1);
		
		if(x.getAbs() > y.getAbs())
		{
			result = helper(tempX,tempY);
			result.trimZeros();
		}
		else if(x.getAbs() == y.getAbs())
		{
			result = helper(tempX,tempY);
			result.trimZeros();
		}
		else if(x.getAbs() < y.getAbs())
		{
			result = helper(tempY,tempX);
			result.trimZeros();
		}

		result.setDigit(0,-1);
	}
	return result;
}

//Subtraction
titanInt operator-(const titanInt& x, const titanInt& y) // x - y
{
	titanInt tempY = y;

	if(y.getDigit(0) == 1) // reverse sign of y
	{
		tempY.setDigit(0,-1);
	}
	else
	{
		tempY.setDigit(0,1);
	}

	return x+tempY;
}

//Multiplication
titanInt operator*(const titanInt& x, const titanInt& y)
{
	titanInt index = y.getAbs();
	titanInt res = 0;

	for(titanInt index = y.getAbs(); index > 0; index = index - 1)
	{
		res = res + x;
		std::cout << "res = " << res << '\n'; // REMOVE AFTER TESTING
	}

	res.setDigit(0, (x.getDigit(0)*y.getDigit(0)));

	return res;   
}

//Division
titanInt operator/(const titanInt& x, const titanInt& y)
{
	titanInt tempX = x.getAbs();
	titanInt res = 0;

	while(tempX - y.getAbs() + 1 > 0)
	{
		res = res + 1;
		tempX = tempX - y.getAbs();
	}

	res.setDigit(0, (x.getDigit(0)*y.getDigit(0)));

	return res;  
}