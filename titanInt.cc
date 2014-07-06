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

/*titanInt::titanInt(const titanInt &original) // copy constructor
{
	for(int i = 0; i <= original.getSize(); ++i)
	{
		digits[i] = original.digits[i];
	}
}*/

//DESTRUCTOR
titanInt::~titanInt()
{

}

//MEMBER FUNCTIONS

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
		std::cout << "setDigit() error: int val out of bounds of 0 to 9";
	}
}

//The function setSize() initializes the digits vector to the number of digits passed
//Use vector::resize() instead?
void titanInt::setSize(int numDigits)
{
	for(int i = 0; i < numDigits; ++i)
	{
		this->digits.insert(this->digits.begin()+1, 0);
	}
}

//The function toConstChar() returns the titanInt object as a const char*.
const char* titanInt::toConstChar() const // REMOVE IF UNUSED
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

//stream insertion
std::ostream& operator<<(std::ostream& output, const titanInt& x)
{
	output << x.toString();
	return output;
}

//less than
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

//greater than
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

//equality
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

//addition function for reuse in operator+()
titanInt helper(const titanInt& x, const titanInt& y)
{
	titanInt res;
	int carry = 0;
	int sum = 0;
	int max = std::max(x.getSize(), y.getSize());
	int min = std::min(x.getSize(), y.getSize());	
	char larger;

	std::cout << "x = " << x << '\n'; //REMOVE AFTER TESTING
	std::cout << "y = " << y << '\n'; //REMOVE AFTER TESTING

	//std::cout << "max = " << max << '\n'; //REMOVE AFTER TESTING
	//std::cout << "min = " << min << '\n'; //REMOVE AFTER TESTING

	//std::cout << x.getDigit(max-1)*x.getDigit(0) << '\n'; //REMOVE AFTER TESTING
	//std::cout << y.getDigit(max-1)*y.getDigit(0) << '\n'; //REMOVE AFTER TESTING

	if(x.getSize() > y.getSize()) //which titanInt has more digits
	{
		larger = 'x';
	}
	else if(x.getSize() == y.getSize())
	{
		larger = '\0';
	}
	else
	{
		larger = 'y';
	}

	if((x.getDigit(x.getSize()-1)*x.getDigit(0)) + //will res have more digits than x and y?
	   (y.getDigit(y.getSize()-1)*y.getDigit(0)) > 9) 
	{
		res.setSize(max); // set size of res to 1 digit more than x and y
	}
	else
	{
		res.setSize(max-1); // set size to same num of digits as max of x and y
	}

	for(int i = 1; i < max; ++i)
	{
		std::cout << x.getDigit(i)*x.getDigit(0) << '\n'; //REMOVE AFTER TESTING
		std::cout << y.getDigit(i)*y.getDigit(0) << '\n'; //REMOVE AFTER TESTING
		
		if(i > min-1) // we are past the smaller numbers digits
		{	
			if(larger == 'x')
			{
				sum = x.getDigit(i)*x.getDigit(0) + carry; // ignore the nonsense elements of y
			}
			else if(larger == 'y')
			{
				sum = y.getDigit(i)*y.getDigit(0) + carry; // ignore the nonsense elements of x
			}
			if(carry == -1) // prevent error from "overcalculating" the sum
			{
				if(i == max-1)
				{
					res.setDigit(i, sum);
				}
				return res;
			}
		}
		else // standard case
		{
			sum = x.getDigit(i)*x.getDigit(0) + y.getDigit(i)*y.getDigit(0) + carry;
		}
	
		if(sum > 9)
		{
			sum -= 10;
			carry = 1;
		}
		else if(sum < 0)
		{
			sum += 10;
			carry = -1;
		}
		else
		{
			carry = 0;
		}

		std::cout << "sum: " << sum << '\n'; //REMOVE AFTER TESTING
		
		res.setDigit(i, sum);
	}

	if(carry == 1)
	{
		std::cout << max << '\n'; // REMOVE AFTER TESTING
		std::cout << res.getSize() << '\n'; // REMOVE AFTER TESTING
		res.setDigit(max, 1);
		std::cout << res.getDigit(max) << '\n'; //REMOVE AFTER TESTING
	}
	
	return res;
} // end helper() function

//addition
titanInt operator+(const titanInt& x, const titanInt& y)
{
	titanInt tempX = x; // a titanInt to store a transform of x if necessary
	titanInt tempY = y; // a titanInt to store a transform of y if necessary
	titanInt result; // a titanInt to store the result of the computation

	if(x.getDigit(0) == 1 && y.getDigit(0) == 1) // pos x, pos y
	{
		result = helper(x,y);
		//std::cout << result << '\n'; // REMOVE AFTER TESTING
		result.setDigit(0,1); // make result pos
		result.trimZeros();
		return result;
	}
	else if (x.getDigit(0) == 1 && y.getDigit(0) == -1) // pos x, neg y
	{
		if(x.getAbs() > y.getAbs()) // x is more pos than y is neg -> pos result
		{
			result = helper(x,y);
			result.setDigit(0,1); // make result pos
			result.trimZeros();
			return result;
		}
		else if(x.getAbs() == y.getAbs()) // 0 result
		{
			result = 0;
			return result;
		}
		else if(x.getAbs() < y.getAbs()) // x is less pos than y is neg -> neg result
		{
			tempX.setDigit(0,-1); // make tempX a neg version of x
			tempY.setDigit(0,1); // make tempY a pos version of y
			result = helper(tempX,tempY);
			result.setDigit(0,-1); // make result neg
			result.trimZeros();
			return result;
		}
	}
	else if (x.getDigit(0) == -1 && y.getDigit(0) == 1) // neg x, pos y
	{
		if(x.getAbs() > y.getAbs()) // x is more neg than y is pos -> neg result
		{
			tempX.setDigit(0,1); // make tempX a pos version of x
			tempY.setDigit(0,-1); // make tempY a neg version of y
			result = helper(tempX,tempY);
			result.setDigit(0,-1); // make result neg
			result.trimZeros();
			return result;
		}
		else if(x.getAbs() == y.getAbs()) // 0 result
		{
			result = 0;
			return result;
		}
		else if(x.getAbs() < y.getAbs()) // x is less neg than y is pos -> pos result
		{
			result = helper(x,y);
			result.setDigit(0,1); // make result pos
			result.trimZeros();
			return result;
		}
	}
	else if (x.getDigit(0) == -1 && y.getDigit(0) == -1) // neg x, neg y
	{
		tempX.setDigit(0, 1); // make tempX a pos version of x
		tempY.setDigit(0, 1); // make tempY a pos version of y
		result = helper(tempX,tempY);
		result.setDigit(0,-1); // make result neg
		result.trimZeros();
		return result;
	}
} // end operator+()

//subtraction
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

//multiplication
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

//division
titanInt operator/(const titanInt& x, const titanInt& y)
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

/*//compound assignment: addition
titanInt operator+=(const titanInt& y)
{
	*this = *this + y;
	return *this;
}

//compound assignment: subtraction
titanInt operator-=(const titanInt& y)
{
	*this = *this - y;
	return *this;
}

//compound assignment: multiplication
titanInt operator*=(const titanInt& y)
{
	*this = *this * y;
	return *this;
}

//compound assignment: division
titanInt operator/=(const titanInt& y)
{
	*this = *this / y;
	return *this;
}
*/
