#ifndef PROBLEM1_DS_BIGINT_H
#define PROBLEM1_DS_BIGINT_H


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BigInt
{
private:
    vector<char> decStr;
    vector<int> decInt;
    bool convert_char_to_int ();
    BigInt convert_int_to_char (BigInt b,bool negative);
    int greater (BigInt b);
    char sign;
public:
    BigInt();
    BigInt(string num);
    BigInt operator + (BigInt anotherDec);
    BigInt operator - (BigInt anotherDec);
    BigInt operator = (BigInt anotherDec);
    int size();
    friend ostream& operator << (ostream& out, BigInt b);
};

#endif //PROBLEM1_DS_BIGINT_H
