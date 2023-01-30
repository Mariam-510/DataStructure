#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Sorter
{
public:
    virtual void sort(vector<int> & v, int size){}
};

class SelectionSorter : public Sorter
{
public:
    void sort(vector<int> & v, int size)
    {
        for (int i = 0, j, least; i < size - 1; i++)
        {
            for (j = i + 1, least = i; j < size; j++)
            {
                if (v[j] < v[least])
                {
                    least = j;
                }

            }
            swap(v[least], v[i]);
        }
    }

};


class QuickSorter : public Sorter
{
public:
    int partition(vector<int> & v, int left, int right)
    {
        int p = v[left];
        int counter = 0;

        for (int i = left + 1; i <= right; i++)
        {
            if (v[i] <= p)
                counter++;
        }
        int pivot = left + counter;
        swap(v[pivot], v[left]);

        int i = left, j = right;

        while (i < pivot && j > pivot)
        {
            while (v[i] <= p)
            {
                i++;
            }

            while (v[j] > p)
            {
                j--;
            }

            if (i < pivot && j > pivot)
            {
                swap(v[i++], v[j--]);
            }
        }

        return pivot;
    }



    void quick_sort(vector<int> & v, int left, int right)
    {
        if (left < right)
        {
            int p = partition(v, left, right);

            quick_sort(v, left, p - 1);

            quick_sort(v, p + 1, right);
        }
    }


    void sort(vector<int> & v, int size)
    {
        quick_sort(v,0,size-1);
    }
};

class Testbed
{
private:
    vector<int> v;
    void ReverseOrdered(vector<int> &v)
    {
        vector<int> temp;
        for (int i = v.size()-1; i >=0 ; i--)
        {
            temp.push_back(v[i]);
        }
        v=temp;
    }
public:
    void GenerateRandomList(int min, int max, int size)
    {
        v.clear();
        for(int i=0;i<size;i++)
        {
            v.push_back((rand()%(max-min+1))+min);
        }
    }

    void GenerateReverseOrderedList(int min, int max, int size)
    {
        GenerateRandomList(min,max,size);
//        SelectionSorter selection;
//        selection.sort(v,size);
        QuickSorter quick;
        quick.sort(v,size);
//        ReverseOrdered(v);
        reverse(v.begin(), v.end());
    }

    int RunOnce(Sorter *s, vector<int> v, int size)
    {
        auto start = high_resolution_clock::now();
        s->sort(v,size);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        return duration.count();
    }

    int RunAndAverage(Sorter *s, int type, int min, int max, int size, int sets_num)
    {
        int average=0;
        for(int i=0;i<sets_num;i++)
        {
            if (type == 0)
            {
                GenerateRandomList(min,max,size);
            }
            else if (type == 1)
            {
                GenerateReverseOrderedList(min, max, size);
            }
            average += RunOnce(s,v,size);
        }
        average/=sets_num;
        return average;
    }

    void RunExperient (Sorter *s, int type, int min, int max, int min_val, int max_val, int sets_num, int step)
    {
        if (type == 0)
        {
            cout<<"\t   Random\n";
        }
        else if (type == 1)
        {
            cout<<"\t   Reversed\n";
        }
        cout<<"Size\t\t\tAverage Time \n";
        cout<<"--------------------------------------\n";
        while (min_val<=max_val)
        {
            cout<<min_val<<"\t\t\t ";
            cout<<RunAndAverage(s,type,min,max,min_val,sets_num)<<endl;
            min_val+=step;
        }
    }


};

int main()
{
    Testbed test;

    Sorter *sorter1 = new SelectionSorter();
    cout<<"\tSelection Sort:\n";
    cout<<"\t---------------\n";
    test.RunExperient(sorter1,0,100,1000000,1000,30000,5,5000);

    cout<<endl;

    Sorter *sorter2 = new QuickSorter();
    cout<<"\t Quick Sort:\n";
    cout<<"\t-------------\n";
    test.RunExperient(sorter2,0,100,1000000,1000,30000,5,5000);

    return 0;
}
