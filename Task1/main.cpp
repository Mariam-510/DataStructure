#include <iostream>
#include <string>
#include "BigInt.h"
using namespace std;

void test_case_1()
{
    BigInt bigInt1("123456789012345678901234567890");
    BigInt bibInt2("113456789011345678901134567890");
    BigInt add;
    add=bigInt1+bibInt2;    //236913578023691357802369135780
    cout<<bigInt1;
    cout<<" + ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<add;
    cout<<endl;
}

void test_case_2()
{
    BigInt bigInt1("-966");
    BigInt bibInt2("-952");
    BigInt add;
    add=bigInt1+bibInt2;    //-1918
    cout<<bigInt1;
    cout<<" + ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<add;
    cout<<endl;
}

void test_case_3()
{
    BigInt bigInt1("1230000000000000001");
    BigInt bibInt2("30000000000000001");
    BigInt sub;
        sub=bigInt1-bibInt2;    //1200000000000000000
    cout<<bigInt1;
    cout<<" - ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<sub;
    cout<<endl;
}

void test_case_4()
{
    BigInt bigInt1("452");
    BigInt bibInt2("271");
    BigInt sub;
    sub=bigInt1-bibInt2;    //181
    cout<<bigInt1;
    cout<<" - ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<sub;
    cout<<endl;
}

void test_case_5()
{
    BigInt bigInt1("234");
    BigInt bibInt2("9176");
    BigInt sub;
    sub=bigInt1-bibInt2;    //-8942
    cout<<bigInt1;
    cout<<" - ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<sub;
    cout<<endl;
}

void test_case_6()
{
    BigInt bigInt1("-529");
    BigInt bibInt2("-435");
    BigInt sub;
    sub=bigInt1-bibInt2;    //-94
    cout<<bigInt1;
    cout<<" - ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<sub;
    cout<<endl;
}

void test_case_7()
{
    BigInt bigInt1("-435");
    BigInt bibInt2("-529");
    BigInt sub;
    sub=bigInt1-bibInt2;    //94
    cout<<bigInt1;
    cout<<" - ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<sub;
    cout<<endl;
}

void test_case_8()
{
    BigInt bigInt1("-2");
    BigInt bibInt2("3");
    BigInt add;
    add=bigInt1+bibInt2;    //1
    cout<<bigInt1;
    cout<<" + ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<add;
    cout<<endl;
}

void test_case_9()
{
    BigInt bigInt1("-1230000000000000001");
    BigInt bibInt2("30000000000000001");
    BigInt add;
    add=bigInt1+bibInt2;    //-1200000000000000000
    cout<<bigInt1;
    cout<<" + ";
    cout<<bibInt2;
    cout<<" = ";
    cout<<add;
    cout<<endl;
}


int main()
{
    cout<<"Test Case 1\n";
    test_case_1();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 2\n";
    test_case_2();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 3\n";
    test_case_3();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 4\n";
    test_case_4();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 5\n";
    test_case_5();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 6\n";
    test_case_6();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 7\n";
    test_case_7();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 8\n";
    test_case_8();
    cout<<"------------------------------------------------\n";
    cout<<"Test Case 9\n";
    test_case_9();

    return 0;
}