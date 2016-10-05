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
#include <Generic/Math/Rational.h>

#include <iostream>
using namespace std;

ostream& operator << (ostream& os, const Rational &r)
{
	os << r.numerator() << '/' << r.denominator();
	return os;
}

int main(int argc, const char *argv[])
{
	/***************************************************************************
	 *	Today, we test the Rational object.
	 *
	 *	The Rational object represends a number as A/B.  A is the numerator
	 *	while B is the denominator.  This is convenient, because you can
	 *	keep exact representation of numbers that cannot be correctly
	 *	represented as floats or doubles (for example, 1/3).
	 *
	 **************************************************************************/
	 
	/***************************************************************************
	 *	INITIALISATION
	 *
	 *	A Rational object can be initialized in two ways:
	 */
	 
	 Rational rat1(1, 2);	//	1/2
	 Rational rat2 = Rational::fromFloat(0.75);
	 
	/*
	 *	Great, now we have two rationals, let's see what they are:
	 */
	 
	cout << "rat1 = " << rat1 << endl;
	cout << "rat2 = " << rat2 << endl;

	/*
	 *	You can also express them as floats if you prefer...
	 */
	 
	cout << "rat1 = " << rat1.toFloat() << endl;
	cout << "rat2 = " << rat2.toFloat() << endl;

	/*
	 *	... or as doubles
	 */
	
	cout << "rat1 = " << rat1.toDouble() << endl;
	cout << "rat2 = " << rat2.toDouble() << endl;

	/*
	 *	You have to be careful with the Rational::fromFloat function - some
	 *	numbers, though very simple in base 10, cannot be expressed correctly
	 *	in base 2. For example:
	 */
	 
	Rational rat3 = Rational::fromFloat(1.9);
	cout << "this is nasty: 1.9 = " << rat3 << " = " << rat3.toDouble() << endl;

	/*
	 *	You can also do all kinds of operations with rationals:
	 */
	 
	cout << rat1 << " + " << rat2 << " = " << rat1 + rat2 << endl;
	cout << rat1 << " - " << rat2 << " = " << rat1 - rat2 << endl;
	cout << rat1 << " * " << rat2 << " = " << rat1 * rat2 << endl;
	cout << rat1 << " / " << rat2 << " = " << rat1 / rat2 << endl;

	cout << rat1 << " + " << "3" << " = " << rat1 + 3 << endl;
	cout << rat1 << " - " << "3" << " = " << rat1 - 3 << endl;
	cout << rat1 << " * " << "3" << " = " << rat1 * 3 << endl;
	cout << rat1 << " / " << "3" << " = " << rat1 / 3 << endl;

	cout << "3" << " + " << rat1 << " = " << 3 + rat1 << endl;
	cout << "3" << " - " << rat1 << " = " << 3 - rat1 << endl;
	cout << "3" << " * " << rat1 << " = " << 3 * rat1 << endl;
	cout << "3" << " / " << rat1 << " = " << 3 / rat1 << endl;

	cout << "~" << rat1 << " = " << ~rat1 << endl;

	return 0;
}

