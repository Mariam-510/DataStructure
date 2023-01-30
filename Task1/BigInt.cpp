#include "BigInt.h"
#include <iostream>
#include <string>
using namespace std;

BigInt::BigInt()
{}

BigInt::BigInt(string num)
{
    long long i = 0;
    int bad = 0;
    while (i < num.length())
    {
        if (i == 0)
        {
            if (num.length()==1)
            {
                if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                    num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
                {
                    cout << "Invalid Input. Enter the number again: ";
                    cin >> num;
                    bad = 1;
                    break;
                }
            }
            else
            {
                if (num[i] != '-' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                    num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
                {
                    cout << "Invalid Input. Enter the number again: ";
                    cin >> num;
                    bad = 1;
                    break;
                }
            }
        }
        else
        {
            if (num[0]=='-'&& num[1]=='0')
            {
                cout << "Invalid Input. Enter the number again: ";
                cin >> num;
                bad = 1;
                break;
            }
            if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
            {
                cout << "Invalid Input. Enter the number again: ";
                cin >> num;
                bad = 1;
                break;
            }
        }
        i++;
    }
    while (bad == 1)
    {
        i = 0;
        bad = 0;
        while (i < num.length())
        {
            if (i == 0)
            {
                if (num.length()==1)
                {
                    if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                        num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
                    {
                        cout << "Invalid Input. Enter the number again: ";
                        cin >> num;
                        bad = 1;
                        break;
                    }
                }
                else
                {
                    if (num[i] != '-' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                        num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
                    {
                        cout << "Invalid Input. Enter the number again: ";
                        cin >> num;
                        bad = 1;
                        break;
                    }
                }
            }
            else
            {
                if (num[0]=='-'&& num[1]=='0')
                {
                    cout << "Invalid Input. Enter the number again: ";
                    cin >> num;
                    bad = 1;
                    break;
                }
                if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
                    num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
                {
                    cout << "Invalid Input. Enter the number again: ";
                    cin >> num;
                    bad = 1;
                    break;
                }
            }
            i++;
        }
    }
    for (long long j = 0; j < num.length(); ++j)
    {
        decStr.push_back(num[j]);
    }
}

bool BigInt::convert_char_to_int()
{
    decInt.clear();
    bool negative= false;
    for (long long i = 0; i < decStr.size(); ++i)
    {
        if (i==0 && decStr[i]=='-')
        {
            negative= true;
            continue;
        }
        else
        {
            decInt.push_back(decStr[i] - '0');
        }
    }
    return negative;
}

BigInt BigInt::convert_int_to_char(BigInt b, bool negative)
{
    b.decStr.clear();
    if (negative)
        b.decStr.push_back('-');

    long long i = b.decInt.size()-1;
    while (b.decInt[i]==0 && i >0)
    {
        i--;
    }
    while ( i >=0)
    {
        b.decStr.push_back(b.decInt[i]+'0');
        i--;
    }
    return b;
}

BigInt BigInt::operator = (BigInt anotherDec)
{
    decStr.clear();
    for (long long i = 0; i <anotherDec.decStr.size() ; ++i)
    {
        decStr.push_back(anotherDec.decStr[i]);
    }

    return *this;
}

BigInt BigInt::operator + (BigInt anotherDec)
{
    bool negative= false;
    bool neg1 = convert_char_to_int();
    bool neg2 = anotherDec.convert_char_to_int();
    if (neg1 == true && neg2 == false && sign != '-') //-num + num
    {
        sign = '+';
        return operator-(anotherDec);
    }

    else
    {
        if (neg1 == true) // (-num1 + -num2) or (-num1 - num2)
            negative= true;
        BigInt addDes;
        long long i = decInt.size() - 1, j = anotherDec.decInt.size() - 1;
        int add = 0;

        while (i >= 0 && j >= 0)
        {
            add += decInt[i] + anotherDec.decInt[j];
            if (add > 9)
            {
                addDes.decInt.push_back(add % 10);
                add = add / 10;
            }
            else
            {
                addDes.decInt.push_back(add);
                add = 0;
            }
            i--;
            j--;
        }

        while (i >= 0)
        {
            addDes.decInt.push_back(add + decInt[i]);
            add = 0;
            i--;
        }

        while (j >= 0)
        {
            addDes.decInt.push_back(add + anotherDec.decInt[j]);
            add = 0;
            j--;
        }

        if (add != 0)
        {
            addDes.decInt.push_back(add);
        }
        sign = '-';
        addDes=convert_int_to_char(addDes,negative);
        return addDes;
    }
}

BigInt BigInt::operator-(BigInt anotherDec)
{
    bool negative= false;
    bool neg1 = convert_char_to_int();
    bool neg2 = anotherDec.convert_char_to_int();

    // (num1 - -num2) or (-num - num)
    if (neg1 == false && neg2 == true && sign !='+' || neg1== true && neg2 == false && sign !='+')
    {
        sign = '-';
        return operator+(anotherDec);
    }

    else
    {
        BigInt subDes;
        long long i = decInt.size() - 1, j = anotherDec.decInt.size() - 1;
        int sub;
        // first number is greater than second number or equal
        if (greater(anotherDec)==1 && neg1 == neg2 || greater(anotherDec)==1 && neg1== true && neg2== false)
        {
            if (neg1== true)
                negative= true;

            while (i >= 0 && j >= 0)
            {
                if (decInt[i] >= anotherDec.decInt[j])
                {
                    sub = decInt[i] - anotherDec.decInt[j];
                    subDes.decInt.push_back(sub);
                }
                else if (decInt[i] < anotherDec.decInt[j])
                {
                    decInt[i] += 10;
                    decInt[i - 1] -= 1;
                    sub = decInt[i] - anotherDec.decInt[j];
                    subDes.decInt.push_back(sub);
                }
                i--;
                j--;
            }
            while (i >= 0)
            {
                subDes.decInt.push_back(decInt[i]);
                i--;
            }
        }
        // second number is greater than first number
        else
        {
            if (neg1 == false)
                negative= true;

            while (i >= 0 && j >= 0)
            {
                if (anotherDec.decInt[j] >= decInt[i])
                {
                    sub =anotherDec.decInt[j] - decInt[i];
                    subDes.decInt.push_back(sub);
                }
                else if (anotherDec.decInt[j] < decInt[i])
                {
                    anotherDec.decInt[j] += 10;
                    anotherDec.decInt[j-1] -= 1;
                    sub =anotherDec.decInt[j] - decInt[i];
                    subDes.decInt.push_back(sub);
                }
                i--;
                j--;
            }
            while (j >= 0)
            {
                subDes.decInt.push_back(anotherDec.decInt[j]);
                j--;
            }
        }

        subDes=convert_int_to_char(subDes,negative);
        return subDes;
    }
}


int BigInt::size()
{
    return decStr.size();
}

ostream &operator<<(ostream &out, BigInt b)
{
    for (long long i = 0; i <b.size() ; ++i)
    {
        cout<<b.decStr[i];
    }
}

int BigInt::greater(BigInt b)
{
    int great=1;
    if (decInt.size()>b.decInt.size())
    {
        return great;
    }
    else if (decInt.size()<b.decInt.size())
    {
        great=2;
        return great;
    }
    else
    {
        for (int i = 0; i <decInt.size() ; ++i)
        {
            if (decInt[i]>b.decInt[i])
            {
                return great;
            }
            else if (decInt[i]<b.decInt[i])
            {
                great=2;
                return great;

            }
        }
        return great;
    }
}





