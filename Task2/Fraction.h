#ifndef PROBLEM2_DS_FRACTION_H
#define PROBLEM2_DS_FRACTION_H
#include <iostream>
using namespace std;

class Fraction {
protected:
    int numerator;
    int denominator;
    char fraction_sign='/';
    int GCD ();
    void negative_sign ();

public:
    Fraction operator+(const Fraction &f);
    Fraction operator-(const Fraction &f);
    Fraction operator*(const Fraction &f);
    Fraction operator/(const Fraction &f);
    bool operator<(const Fraction &f);
    bool operator>(const Fraction &f);
    bool operator==(const Fraction &f);
    bool operator<=(const Fraction &f);
    bool operator>=(const Fraction &f);
    Fraction reducing_fractions ();
    friend istream& operator>>(istream &is, Fraction &f);
    friend ostream& operator<<(ostream &os, const Fraction &f);
    int get_numerator();
    int get_denominator();

};


#endif //PROBLEM2_DS_FRACTION_H
