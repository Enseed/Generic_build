/*******************************************************************************
 Copyright 2008 Enseed inc.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

 Author: Gaspard Petit
*******************************************************************************/
#ifndef __GENERIC_MATH_RATIONAL__
#define __GENERIC_MATH_RATIONAL__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
namespace seed {

//==============================================================================
//	CLASS Rational
//==============================================================================
class Rational
{
public:
	inline Rational(int numerator, int denominator);
	inline explicit Rational(int numerator);
	inline Rational();
	inline  Rational(const Rational& rhs);
		
	inline static Rational fromFloat(float floatVal);

	inline Rational operator + (const Rational &rhs) const;
	inline Rational operator - (const Rational &rhs) const;
	inline Rational operator * (const Rational &rhs) const;
	inline Rational operator / (const Rational &rhs) const;
	inline Rational operator ~ () const;

	inline Rational operator + (int rhs) const;
	inline Rational operator - (int rhs) const;
	inline Rational operator * (int rhs) const;
	inline Rational operator / (int rhs) const;

	inline Rational& operator += (const Rational &rhs);
	inline Rational& operator -= (const Rational &rhs);
	inline Rational& operator *= (const Rational &rhs);
	inline Rational& operator /= (const Rational &rhs);

	inline Rational& operator += (int rhs);
	inline Rational& operator -= (int rhs);
	inline Rational& operator *= (int rhs);
	inline Rational& operator /= (int rhs);

	inline bool operator > (const Rational &rhs) const;
	inline bool operator >= (const Rational &rhs) const;
	inline bool operator < (const Rational &rhs) const;
	inline bool operator <= (const Rational &rhs) const;
	inline bool operator == (const Rational &rhs) const;
	inline bool operator != (const Rational &rhs) const;

	inline bool operator < (const double &rhs) const;
	inline bool operator <= (const double &rhs) const;
	inline bool operator > (const double &rhs) const;
	inline bool operator >= (const double &rhs) const;
	inline bool operator == (const double &rhs) const;
	inline bool operator != (const double &rhs) const;

	inline bool operator < (const int &rhs) const;
	inline bool operator <= (const int &rhs) const;
	inline bool operator > (const int &rhs) const;
	inline bool operator >= (const int &rhs) const;
	inline bool operator == (const int &rhs) const;
	inline bool operator != (const int &rhs) const;


	inline float	toFloat() const;
	inline double	toDouble() const;
	inline Rational inversed() const;
	inline void inverse();

	inline int	numerator() const;
	inline int	denominator() const;

	template<class T>
	T valueForBase(T aBase) const;
	
public:
	inline static void putOnLCD(Rational * const a, Rational * const b);

protected:
	inline void simplify();

private:
	int mNum;
	int mDenom;
};

inline Rational operator + (int lhs, const Rational& rhs);
inline Rational operator - (int lhs, const Rational& rhs);
inline Rational operator / (int lhs, const Rational& rhs);
inline Rational operator * (int lhs, const Rational& rhs);


} // namespace seed



//==============================================================================
//	INLINED CODE
//==============================================================================
#include "src/Rational.inline.h"

#endif // __GENERIC_MATH_RATIONAL__
