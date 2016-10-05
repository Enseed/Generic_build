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
#ifndef __GENERIC_MATH_RATIONAL_INLINE__
#define __GENERIC_MATH_RATIONAL_INLINE__

//==============================================================================
//	EXTERNAL DECLARATIONS
//==============================================================================
#include "../Rational.h"
#include "../Float.h"
#include "../Integer.h"
#include <cstdio>

namespace seed {

//==============================================================================
// FREE FUNCTION
//==============================================================================

Rational operator + (int lhs, const Rational& rhs)
{
	return Rational(lhs, 1) + rhs;
}

//------------------------------------------------------------------------------
//
Rational operator - (int lhs, const Rational& rhs)
{
	return Rational(lhs, 1) - rhs;
}

//------------------------------------------------------------------------------
//
Rational operator / (int lhs, const Rational& rhs)
{
	return Rational(lhs, 1) / rhs;
}

//------------------------------------------------------------------------------
//
Rational operator * (int lhs, const Rational& rhs)
{
	return Rational(lhs, 1) * rhs;
}

//------------------------------------------------------------------------------
//
inline static void getLCDValues(const Rational &a, const Rational &b, int *outNumA, int *outNumB, int *outLCD)
{
	int denomA = a.denominator();
	int denomB = b.denominator();

	int lcm = *outLCD = Integer::lcm(denomA, denomB);
	int mult;

	if (lcm != denomA)
	{
		mult = lcm / denomA;

#ifdef MK_DEBUG
		*outNumA = IntOps::safeInt32Mult(a.numerator(), mult);
#else
		*outNumA = a.numerator() * mult;
#endif
	}
	else
		*outNumA = a.numerator();

	if (lcm != denomB)
	{
		mult = lcm / denomB;

#ifdef MK_DEBUG
		*outNumB = IntOps::safeInt32Mult(b.numerator(), mult);
#else
		*outNumB = b.numerator() * mult;
#endif
	}
	else
		*outNumB = b.numerator();
}

//==============================================================================
//	CLASS Rational
//==============================================================================

//------------------------------------------------------------------------------
//
Rational::Rational()
:
	mNum(),
	mDenom()
{}

//------------------------------------------------------------------------------
//
Rational::Rational(int numerator)
:
	mNum(numerator),
	mDenom(1)
{}

//------------------------------------------------------------------------------
//
Rational::Rational(int numerator, int denominator)
:
	mNum(numerator),
	mDenom(denominator)
{
	simplify();
}

//------------------------------------------------------------------------------
//
Rational::Rational(const Rational& rhs)
:
	mNum(rhs.numerator()),
	mDenom(rhs.denominator())
{
	//	no need to simplify - it's already been done by the other Rational
}

//------------------------------------------------------------------------------
//
Rational Rational::fromFloat(float floatVal)
{
	int intVal = static_cast<int>(floatVal);

	if (static_cast<float>(intVal) == floatVal)
		return Rational(intVal, 1);

	int exp, num, denom;
	double mant = Float::frexp(floatVal, &exp);
 
	num = static_cast<int>(mant * (1 << Float::kNumberOfMantissaDigits));

	denom = 1 << (Float::kNumberOfMantissaDigits - exp);
	
	while ((float(num/2) / float(denom/2) > floatVal-0.0001) &&
		   (float(num/2) / float(denom/2) < floatVal+0.0001) && (denom > 1))
	{
		num >>= 1;
		denom >>= 1;
	}
	
	return Rational(num, denom);
}

//------------------------------------------------------------------------------
//
Rational Rational::operator + (const Rational &rhs) const
{
	int numA, numB, lcd;
	getLCDValues(*this, rhs, &numA, &numB, &lcd);

#ifdef MK_DEBUG
	return Rational(IntOps::safeInt32Add(numA, numB), lcd);
#else
	return Rational(numA + numB, lcd);
#endif
}

//------------------------------------------------------------------------------
//
Rational Rational::operator - (const Rational &rhs) const
{
	int numA, numB, lcd;
	getLCDValues(*this, rhs, &numA, &numB, &lcd);

	return Rational(numA - numB, lcd);
}

//------------------------------------------------------------------------------
//
Rational Rational::operator * (const Rational &rhs) const
{
#ifdef MK_DEBUG
	return Rational(IntOps::safeInt32Mult(mNum, rhs.mNum),
					IntOps::safeInt32Mult(mDenom, rhs.mDenom));
#else
	return Rational(mNum * rhs.mNum, mDenom * rhs.mDenom);
#endif
}

//------------------------------------------------------------------------------
//
Rational Rational::operator / (const Rational &rhs) const
{
#ifdef MK_DEBUG
	return Rational(IntOps::safeInt32Mult(mNum, rhs.mDenom),
					IntOps::safeInt32Mult(mDenom, rhs.mNum));
#else
	return Rational(mNum * rhs.mDenom, mDenom * rhs.mNum);
#endif
}

//------------------------------------------------------------------------------
//
Rational Rational::inversed() const
{
	return Rational(denominator(), numerator());
}

//------------------------------------------------------------------------------
//
void Rational::inverse()
{
	*this = inversed();
}

//------------------------------------------------------------------------------
//
Rational Rational::operator ~ () const
{
	return inversed();
}

//------------------------------------------------------------------------------
//
Rational Rational::operator + (int rhs) const
{
	return *this + Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational Rational::operator - (int rhs) const
{
	return *this - Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational Rational::operator * (int rhs) const
{
	return *this * Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational Rational::operator / (int rhs) const
{
	return *this / Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator += (const Rational &rhs)
{
	int numA, numB, lcd;
	getLCDValues(*this, rhs, &numA, &numB, &lcd);

#ifdef MK_DEBUG
	*this = Rational(IntOps::safeInt32Add(numA, numB), lcd);
#else
	*this = Rational(numA + numB, lcd);
#endif

	return *this;
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator -= (const Rational &rhs)
{
	int numA, numB, lcd;
	getLCDValues(*this, rhs, &numA, &numB, &lcd);

	*this = Rational(numA - numB, lcd);
	return *this;
}

// CONTINUE HERE

//------------------------------------------------------------------------------
//
Rational& Rational::operator *= (const Rational &rhs)
{
#ifdef MK_DEBUG
	*this = Rational(IntOps::safeInt32Mult(mNum, rhs.mNum),
					IntOps::safeInt32Mult(mDenom, rhs.mDenom));
#else
	*this = Rational(mNum * rhs.mNum, mDenom * rhs.mDenom);
#endif
	return *this;
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator /= (const Rational &rhs)
{
#ifdef MK_DEBUG
	*this = Rational(IntOps::safeInt32Mult(mNum, rhs.mDenom),
					IntOps::safeInt32Mult(mDenom, rhs.mNum));
#else
	*this = Rational(mNum * rhs.mDenom, mDenom * rhs.mNum);
#endif
	return *this;
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator += (int rhs)
{
	return *this += Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator -= (int rhs)
{
	return *this -= Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator *= (int rhs)
{
	return *this *= Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
Rational& Rational::operator /= (int rhs)
{
	return *this /= Rational(rhs, 1);
}

//------------------------------------------------------------------------------
//
float Rational::toFloat() const
{
	return static_cast<float>(mNum) / static_cast<float>(mDenom);
}

//------------------------------------------------------------------------------
//
double Rational::toDouble() const
{
	return static_cast<double>(mNum) / static_cast<double>(mDenom);
}

//------------------------------------------------------------------------------
//
int Rational::numerator() const
{
	return mNum;
}

//------------------------------------------------------------------------------
//
int Rational::denominator() const
{
	return mDenom;
}

//------------------------------------------------------------------------------
//
void Rational::simplify()
{
	if (mDenom == 0) return;

	if (mNum == 0)
	{
		mDenom = 1;
		return;
	}

	if (mDenom < 0)
	{
		mDenom = -mDenom;
		mNum = -mNum;
	}

	int gcd = Integer::gcd(mNum, mDenom);
	
	mNum /= gcd;
	mDenom /= gcd;
}

//------------------------------------------------------------------------------
//
void Rational::putOnLCD(Rational * const a, Rational * const b) 
{
	int lcm = Integer::lcm(a->mDenom, b->mDenom);

	int mult;

	if (lcm != a->mDenom)
	{
		mult = lcm / a->mDenom;

#ifdef MK_DEBUG
		a->mNum = IntOps::safeInt32Mult(a->mNum, mult);
		a->mDenom = IntOps::safeInt32Mult(a->mDenom, mult);
#else
		a->mNum *= mult;
		a->mDenom *= mult;
#endif
	}

	if (lcm != b->mDenom)
	{
		mult = lcm / b->mDenom;

#ifdef MK_DEBUG
		b->mNum = IntOps::safeInt32Mult(b->mNum, mult);
		b->mDenom = IntOps::safeInt32Mult(b->mDenom, mult);
#else
		b->mNum *= mult;
		b->mDenom *= mult;
#endif
	}
}



//------------------------------------------------------------------------------
//
bool Rational::operator > (const Rational &rhs) const
{
	return mNum * rhs.mDenom > rhs.mNum * mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator >= (const Rational &rhs) const
{
	return mNum * rhs.mDenom >= rhs.mNum * mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator < (const Rational &rhs) const
{
	return mNum * rhs.mDenom < rhs.mNum * mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator <= (const Rational &rhs) const
{
	return mNum * rhs.mDenom <= rhs.mNum * mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator == (const Rational &rhs) const
{
	return ((mNum == rhs.mNum) && (mDenom == rhs.mDenom));
}

//------------------------------------------------------------------------------
//
bool Rational::operator != (const Rational &rhs) const
{
	return ((mNum != rhs.mNum) || (mDenom != rhs.mDenom));
}

//------------------------------------------------------------------------------
//
bool Rational::operator < (const double &rhs) const
{
	return toDouble() < rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator <= (const double &rhs) const
{
	return toDouble() <= rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator > (const double &rhs) const
{
	return toDouble() > rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator >= (const double &rhs) const
{
	return toDouble() >= rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator == (const double &rhs) const
{
	return toDouble() == rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator != (const double &rhs) const
{
	return toDouble() != rhs;
}

//------------------------------------------------------------------------------
//
bool Rational::operator < (const int &rhs) const
{
	return mNum < rhs*mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator <= (const int &rhs) const
{
	return mNum <= rhs*mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator > (const int &rhs) const
{
	return mNum > rhs*mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator >= (const int &rhs) const
{
	return mNum >= rhs*mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator == (const int &rhs) const
{
	return mNum == rhs*mDenom;
}

//------------------------------------------------------------------------------
//
bool Rational::operator != (const int &rhs) const
{
	return mNum != rhs*mDenom;
}

//------------------------------------------------------------------------------
//
template<class T>
T Rational::valueForBase(T aBase) const
{
	Rational factor(aBase, mDenom); // put on lcd
	return static_cast<T>(mNum)*factor.numerator()/static_cast<T>(factor.denominator());
}

} // namespace seed



#endif // __MK_MATH_RATIONAL_INLINE__
