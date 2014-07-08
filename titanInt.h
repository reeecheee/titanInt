/*! 
 *	 titanInt.h
 * 
 *  titanInt class header file: The titanInt class provides a representation of
 *  very large integers, both positive and negative.  The class stores a vector 
 *  of ints (named digits) that represent the digits of the very large number. 
 *  The zeroth element will take a value of 0 upon initialization, and then a
 *  value of either 1 or -1 to denote the sign of the titanInt.  Overloaded
 *  operators are provided to support comparison, arithmetic, and stream 
 *  insertion.
 * 
 *  Author: Mike Ricci
 *  Date: 20140629
 */

#ifndef _TITANINT_H_
#define _TITANINT_H_

#include <vector>

class titanInt;

//Bitwise Operators
std::ostream& operator<<(std::ostream& output, const titanInt& x);

//Comparison Operators
bool operator<(const titanInt&x, const titanInt& y);
bool operator>(const titanInt&x, const titanInt& y);
bool operator==(const titanInt&x, const titanInt& y);

//Arithmetic Operators
titanInt operator+(const titanInt& x, const titanInt& y);
titanInt operator-(const titanInt& x, const titanInt& y);
titanInt operator*(const titanInt& x, const titanInt& y);
titanInt operator/(const titanInt& x, const titanInt& y);

class titanInt
{
public:
	//Constructors
	titanInt(); // default constructor
	titanInt(std::string str); //conversion constructor
	titanInt(int x) : titanInt(std::to_string(x)){}; // delegating constructor

	//Virtual Destructor
	virtual ~titanInt();

	//Member Functions
	void addDigit();
	titanInt getAbs() const;
	int getDigit(int i) const;
	int getSize() const;
	void setDigit(int i, int val);
	void setSize(int numDigits);
	const char* toConstChar() const;
	std::string toString() const;
	void trimZeros();

protected:

private:
	std::vector<int> digits = std::vector<int>(1);
	
}; // end class titanInt

#endif // _TITANINT_H_

