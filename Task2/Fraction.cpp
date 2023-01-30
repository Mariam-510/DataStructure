#include "Fraction.h"
#include <iostream>
#include <cmath>

using namespace std;

//operator overloading + Function
Fraction Fraction::operator+(const Fraction &f)
{
    Fraction temp;
    if (numerator==0)
    {
        temp.numerator = f.numerator;
        temp.denominator = f.denominator;
    }
    else if (f.numerator==0)
    {
        temp.numerator = numerator;
        temp.denominator = denominator;
    }
    else
    {
        temp.numerator = numerator * f.denominator + f.numerator * denominator;
        temp.denominator = denominator * f.denominator;
    }
    return temp;
}

//operator overloading - Function
Fraction Fraction::operator-(const Fraction &f)
{
    Fraction temp;
    if (numerator==0)
    {
        temp.numerator = -f.numerator;
        temp.denominator = f.denominator;
    }
    else if (f.numerator==0)
    {
        temp.numerator = numerator;
        temp.denominator = denominator;
    }
    else
    {
        temp.numerator = numerator * f.denominator - f.numerator * denominator;
        temp.denominator = denominator * f.denominator;
    }
    return temp;
}

//operator overloading * Function
Fraction Fraction::operator*(const Fraction &f)
{
    Fraction temp;
    temp.numerator = numerator * f.numerator;
    temp.denominator = denominator * f.denominator;
    return temp;
}

//operator overloading / Function
Fraction Fraction::operator/(const Fraction &f)
{
    Fraction temp;
    if (f.numerator!=0)
    {
        temp.numerator = numerator * f.denominator;
        temp.denominator = denominator * f.numerator;
    }
    else
    {
       temp.numerator=0;
       temp.denominator=0;
    }
    return temp;
}

//operator overloading < Function
bool Fraction::operator<(const Fraction &f)
{
    if (numerator*f.denominator<f.numerator*denominator)
        return true;
    else
        return false;
}

//operator overloading > Function
bool Fraction::operator>(const Fraction &f)
{
    if (numerator*f.denominator>f.numerator*denominator)
        return true;
    else
        return false;
}

//operator overloading == Function
bool Fraction::operator==(const Fraction &f)
{
    if (numerator*f.denominator==f.numerator*denominator)
        return true;
    else
        return false;
}

//operator overloading == Function
bool Fraction::operator<=(const Fraction &f)
{
    if (numerator*f.denominator<=f.numerator*denominator)
        return true;
    else
        return false;
}

//operator overloading == Function
bool Fraction::operator>=(const Fraction &f)
{
    if (numerator*f.denominator>=f.numerator*denominator)
        return true;
    else
        return false;
}

//GCD Function
int Fraction::GCD()
{
    int gcd=1;
    if (numerator<denominator)
    {
        for (int i = abs(numerator); i >1 ; i--)
        {
            if (numerator % i == 0 && denominator % i == 0)
            {
                gcd =i;
                return gcd;
            }
        }
    }
    else
    {
        for (int i = abs(denominator); i >1 ; i--)
        {
            if (numerator % i == 0 && denominator % i == 0)
            {
                gcd =i;
                return gcd;
            }
        }
    }
    return gcd;
}

//reducing_fractions Function
Fraction Fraction::reducing_fractions()
{
    int reduced_by=GCD();
    if (reduced_by!=1)
    {
        numerator /= reduced_by;
        denominator /= reduced_by;
    }
    return *this;
}

//negative_sign Function
void Fraction::negative_sign()
{
    if (denominator<0)
    {
        numerator=-(numerator);
        denominator=-(denominator);
    }
}

//operator overloading >> Function
istream &operator>>(istream &is, Fraction &f)
{
    is>>f.numerator>>f.fraction_sign>>f.denominator;
    while (f.denominator==0)
    {
        cout<<"Math Error. Denominator can not be 0\n Enter the number again \n";
        is>>f.numerator>>f.fraction_sign>>f.denominator;
    }
    f.negative_sign();
    return is;
}

//operator overloading << Function
ostream &operator<<(ostream &os, const Fraction &f)
{
    os << f.numerator << f.fraction_sign << f.denominator;
    return os;
}

int Fraction::get_numerator()
{
    return numerator;
}

int Fraction::get_denominator()
{
    return denominator;
}

