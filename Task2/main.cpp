#include <iostream>
#include <string>
#include "Fraction.h"
using namespace std;

class FractionCalculator : public Fraction
{
private:
    Fraction frac1,frac2;
public:

    FractionCalculator ()
    {
        cout<<"Enter First Fraction(num1/num2): ";
        cin>>frac1;
        cout<<"Enter Second Fraction(num1/num2): ";
        cin>>frac2;
        menu();
        int number;
        cin>>number;
        while (number!=1 && number!=2 && number!=3 && number!=4 && number!=5 && number!=6 && number!=7 && number!=8 )
        {
            cout<<"Invalid option. Enter number again: ";
            cin >> number;
        }
        while (number!=8)
        {
            if (number==1)
            {
                cout<<frac1<<" + "<<frac2<<" = "<<adding();
                if (adding().get_numerator() != adding().reducing_fractions().get_numerator())
                {
                    cout << " = " << adding().reducing_fractions() << endl;
                }
                else if (adding().get_numerator() == 0)
                {
                    cout << " = "<<adding().get_numerator()<<endl;
                }
                else
                    cout<<endl;
            }
            else if (number==2)
            {
                cout<<frac1<<" - "<<frac2<<" = "<<subtracting();
                if (subtracting().get_numerator() != subtracting().reducing_fractions().get_numerator())
                {
                    cout <<" = "<<subtracting().reducing_fractions()<<endl;
                }
                else if (subtracting().get_numerator() == 0)
                {
                    cout << " = "<<subtracting().get_numerator()<<endl;
                }
                else
                    cout<<endl;
            }
            else if (number==3)
            {
                cout<<frac1<<" * "<<frac2<<" = "<<multiplying();
                if (multiplying().get_numerator() != multiplying().reducing_fractions().get_numerator())
                {
                    cout <<" = "<<multiplying().reducing_fractions()<<endl;
                }
                else if (multiplying().get_numerator() == 0)
                {
                    cout << " = "<<multiplying().get_numerator()<<endl;
                }
                else
                    cout<<endl;
            }
            else if (number==4)
            {
                if (dividing().get_numerator()==0 && dividing().get_denominator()==0)
                    cout<<frac1<<" / "<<frac2<<" = Math Error\n";
                else
                {
                    cout << frac1 << " / " << frac2 << " = " << dividing();
                    if (dividing().get_numerator() != dividing().reducing_fractions().get_numerator())
                    {
                        cout << " = " << dividing().reducing_fractions()<< endl;
                    }
                    else if (dividing().get_numerator() == 0)
                    {
                        cout << " = "<<dividing().get_numerator()<<endl;
                    }
                    else
                        cout<<endl;
                }
            }
            else if (number==5)
            {
                int frac_num;
                cout<<"Enter which Fraction you want to reduce (1 or 2): ";
                cin>>frac_num;
                if (frac_num==1)
                {
                    cout << frac1.reducing_fractions();
                    if (frac1.get_numerator() == 0)
                    {
                        cout << " = "<<frac1.get_numerator()<<endl;
                    }
                    else
                        cout<<endl;
                }
                if (frac_num==2)
                {
                    cout << frac2.reducing_fractions();
                    if (frac2.get_numerator() == 0)
                    {
                        cout << " = "<<frac2.get_numerator()<<endl;
                    }
                    else
                        cout<<endl;
                }
            }

            else if (number==6)
            {
                string comparison_mark;
                cout<<"Enter which comparison you want (<, >, =, <= and >=): ";
                cin>>comparison_mark;
                while (comparison_mark!="<" && comparison_mark !=">" && comparison_mark !="="
                && comparison_mark !="<=" && comparison_mark !=">=")
                {
                    cout<<"Invalid option. Enter comparison mark again: ";
                    cin >> comparison_mark;
                }

                if (comparison_mark =="<")
                {
                    if (frac1<frac2)
                        cout<<"Yes, First Fraction is smaller than Second Fraction\n";
                    else
                        cout<<"No, First Fraction is not smaller than Second Fraction\n";
                }
                else if (comparison_mark ==">")
                {
                    if (frac1>frac2)
                        cout<<"Yes, First Fraction is greater than Second Fraction\n";
                    else
                        cout<<"No, First Fraction is not greater than Second Fraction\n";
                }
                else if (comparison_mark =="=")
                {
                    if (frac1==frac2)
                        cout<<"Yes, First Fraction is equal Second Fraction\n";
                    else
                        cout<<"No, First Fraction is not equal Second Fraction\n";
                }
                else if (comparison_mark =="<=")
                {
                    if (frac1<=frac2)
                        cout<<"Yes, First Fraction is smaller than or equal Second Fraction\n";
                    else
                        cout<<"No, First Fraction is not smaller than or equal Second Fraction\n";
                }
                else if (comparison_mark ==">=")
                {
                    if (frac1>=frac2)
                        cout<<"Yes, First Fraction is greater than or equal Second Fraction\n";
                    else
                        cout<<"No, First Fraction is not greater than or equal Second Fraction\n";
                }
            }

            else if (number==7)
            {
                cout<<"Enter First Fraction(num1/num2): ";
                cin>>frac1;
                cout<<"Enter Second Fraction(num1/num2): ";
                cin>>frac2;
            }
            menu();
            cin>>number;
            while (number!=1 && number!=2 && number!=3 && number!=4 && number!=5 && number!=6 && number!=7 && number!=8 )
            {
                cout<<"Invalid option. Enter number again: ";
                cin >> number;
            }
        }
    }

    Fraction adding ()
    {
        return frac1+frac2;
    }
    Fraction subtracting ()
    {
        return frac1-frac2;
    }
    Fraction multiplying ()
    {
        return frac1*frac2;
    }
    Fraction dividing ()
    {
        return frac1/frac2;
    }
    void menu()
    {
        cout<<"Enter the option do you want to calculate:\n";
        cout<<"1) Adding\n";
        cout<<"2) Subtracting\n";
        cout<<"3) Multiplying\n";
        cout<<"4) Dividing\n";
        cout<<"5) Reducing\n";
        cout<<"6) Comparison\n";
        cout<<"7) Input other Fractions\n";
        cout<<"8) Exit\n";
    }

};

int main()
{
    FractionCalculator f_c;

    return 0;
}
