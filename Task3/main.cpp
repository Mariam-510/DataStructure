#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PhoneDirectory
{
private:
    string first_name,last_name,phone_number;
public:
    void add_to_directory()
    {
        cout<<"Enter first name: ";
        cin>>first_name;
        cout<<"Enter last name: ";
        cin>>last_name;
        cout<<"Enter phone number: ";
        cin>>phone_number;

    }

    bool lookup_phone_number(string phone)
    {
        if(phone_number==phone)
            return true;

        return false;
    }

    bool lookup_first_name_linear_search(string name)
    {
        if(first_name==name)
            return true;

        return false;
    }

    void print()
    {
        cout << "First name: ";
        cout<<first_name<<endl;
        cout << "Last name: ";
        cout<<last_name<<endl;
        cout << "Phone number: ";
        cout<<phone_number<<endl;
    }

    string get_first_name () {
        return first_name;
    }
    string get_phone_number () {
        return phone_number;
    }


};

void swap(PhoneDirectory & pd1,PhoneDirectory & pd2)
{
    PhoneDirectory temp;
    temp=pd1;
    pd1=pd2;
    pd2=temp;
}

void selection_sort(vector<PhoneDirectory> & vec)
{
    for(int i=0,j;i<vec.size()-1;i++)
    {
        int least=i;
        for(j=i+1;j<vec.size();j++)
        {

            if((vec[j].get_first_name())<(vec[least].get_first_name()))
            {
                least=j;
            }
        }

        swap(vec[least],vec[i]);
    }
}

void bubble_sort(vector<PhoneDirectory> & vec)
{
    bool flag= false;
    for (int i = 0; i < vec.size()-1; i++)
    {
        for (int j = 0; j < vec.size()-i-1; j++)
        {
            if (vec[j].get_first_name() > vec[j + 1].get_first_name())
            {
                swap(vec[j + 1], vec[j]);
                flag = true;
            }
        }
        if (flag== false)
            break;
    }
}

void insertion_sort(vector<PhoneDirectory> & vec)
{
    PhoneDirectory temp;
    for (int i = 1,j; i < vec.size(); i++)
    {
        temp = vec[i];

        for (j=i-1;j >= 0 && vec[j].get_first_name() > temp.get_first_name();j--)
        {
            vec[j+1] = vec[j];
        }
        vec[j + 1] = temp;
    }
}

void merge(vector<PhoneDirectory> & vec, int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    vector<PhoneDirectory> left;
    vector<PhoneDirectory> right;

    for (int i = 0; i < n1; i++) {
        left.push_back(vec[l + i]);
    }

    for (int j = 0; j < n2; j++) {
        right.push_back(vec[mid +1+ j]);
    }

    int i=0, j=0, k=l;


    while (i < n1 && j < n2)
    {
        if (left[i].get_first_name() < right[j].get_first_name())
        {
            vec[k]=left[i];
            i++;
        }
        else
        {
            vec[k]=right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vec[k]=left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vec[k]=right[j];
        j++;
        k++;
    }
}


void merge_sort(vector<PhoneDirectory> & vec, int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;

        merge_sort(vec, l, mid);
        merge_sort(vec, mid + 1, r);

        merge(vec, l, mid, r);
    }
}


vector<PhoneDirectory> sort_method(vector<PhoneDirectory> & vec)
{
    int num;
    cout<<"Which sorting algorithm do you want to apply?\n";
    cout<<"1) Selection Sort\n";
    cout<<"2) Bubble Sort\n";
    cout<<"3) Insertion Sort\n";
    cout<<"4) Merge Sort\n";
    cout<<"Enter its number: ";
    cin>>num;
    while (num!=1 && num!=2 && num!=3 && num!=4)
    {
        cout<<"Invalid option. Enter number again: ";
        cin >> num;
    }
    if (num==1) {
        selection_sort(vec);
        cout<<"Sorted With Selection Sort\n";
    }
    else if (num==2) {
        bubble_sort(vec);
        cout<<"Sorted With Bubble Sort\n";
    }
    else if (num==3) {
        insertion_sort(vec);
        cout<<"Sorted With Insertion Sort\n";
    }
    else if (num==4) {
        merge_sort(vec,0,vec.size()-1);
        cout<<"Sorted With Merge Sort\n";
    }
    return vec;
}

void delete_entry(vector<PhoneDirectory> & vec,string name)
{
    vec = sort_method(vec);

    int x=0;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i].get_first_name() > name) {
            break;
        }
        else
        {
            if (vec[i].lookup_first_name_linear_search(name))
            {
                vec.erase(vec.begin()+i);
                x = 1;
                i--;
            }
        }
    }

    if (x==0)
        cout<<"Entry Not Found\n";
    else
        cout<<"Entry Deleted Successfully\n";
}

// return only one entry
int binary_search(vector<PhoneDirectory> & vec, int left, int right, string name)
{
    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (vec[middle].get_first_name() == name)
        {
            return middle;
        }

        if (vec[middle].get_first_name() > name)
        {
            right = middle - 1;
        }

        else
        {
            left = middle + 1;
        }
    }

    return -1;
}

int main()
{
    vector<PhoneDirectory> phone_directory;

    cout<<"Enter an option: \n";
    cout<<"1.Add an entry to the director\n";
    cout<<"2.Look up a phone number\n";
    cout<<"3.Look up by first name\n";
    cout<<"4.Delete an entry from the directory\n";
    cout<<"5.List All entries in phone directory\n";
    cout<<"6.Exit form this program\n";

    int num;
    cin>>num;
    while (num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6)
    {
        cout<<"Invalid option. Enter number again: ";
        cin >> num;
    }

    while(num!=6)
    {
        if(num==1)
        {
            PhoneDirectory p_d;
            p_d.add_to_directory();
            int x=0;
            for (int i = 0; i < phone_directory.size(); ++i)
            {
                if (phone_directory[i].lookup_phone_number(p_d.get_phone_number()))
                {
                    cout<<"This phone number already exists with this information \n";
                    cout <<"Entry: \n";
                    phone_directory[i].print();
                    x=1;
                }
            }
            if (x==0)
                phone_directory.push_back(p_d);
        }

        else if(num==2)
        {
            string phone;
            cout<<"Enter the phone number you want to lookup with: ";
            cin>>phone;
            int x=0;
            for (int i = 0; i < phone_directory.size(); i++)
            {
                if (phone_directory[i].lookup_phone_number(phone))
                {
                    cout <<"Entry: \n";
                    phone_directory[i].print();
                    x=1;
                    break;
                }
            }
            if (x==0)
                cout<<"Entry Not Found\n";
        }

        else if(num==3)
        {
            string name;
            cout<<"Enter the first name you want to lookup with: ";
            cin>>name;
            phone_directory = sort_method(phone_directory);
            int x=0;
            for (int i = 0; i < phone_directory.size(); ++i)
            {
                if (phone_directory[i].get_first_name() > name) {
                    break;
                }
                else
                {
                    if (phone_directory[i].lookup_first_name_linear_search(name))
                    {
                        cout <<"Entry: \n";
                        phone_directory[i].print();
                        x=1;
                    }
                }
            }
            if (x==0)
                cout<<"Entry Not Found\n";

//            phone_directory = sort_method(phone_directory);
//            int index = binary_search(phone_directory,0,phone_directory.size(),name);
//            if (index!=-1)
//            {
//                cout <<"Entry: \n";
//                phone_directory[index].print();
//            }
//            else
//            {
//                cout<<"Entry Not Found\n";
//            }
        }

        else if(num==4)
        {
            string name;
            cout<<"Enter the first name you want to delete its entry: ";
            cin>>name;
            delete_entry(phone_directory,name);
        }

        else if (num==5)
        {
            if (phone_directory.size()==0)
                cout<<"Phone Directory is Empty\n";
            else
            {
                phone_directory= sort_method(phone_directory);
                for (int i = 0; i < phone_directory.size(); i++)
                {
                    cout << i + 1 << ") Entry: \n";
                    phone_directory[i].print();
                }
            }
        }

        cout<<"\nEnter an option: \n";
        cout<<"1.Add an entry to the director\n";
        cout<<"2.Look up a phone number\n";
        cout<<"3.Look up by first name\n";
        cout<<"4.Delete an entry from the directory\n";
        cout<<"5.List All entries in phone directory\n";
        cout<<"6.Exit form this program\n";

        cin>>num;
        while (num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=6)
        {
            cout<<"Invalid option. Enter number again: ";
            cin >> num;
        }
    }
    return 0;
}
