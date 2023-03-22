#include <iostream>
#include <cstring>
using namespace std;
/*class node has array of pointers to children nodes
startIndex refers to starting index of the characters
endIndex refers to the starting index of the suffix ending at this node,used for leaf nodes only, else it will be -1*/
class Node
{
public:
    Node *children[27];
    long long startIndex;
    long long endIndex;
    Node()
    {
        for (int i = 0; i <26 ; ++i)
            children[i]=NULL;
        startIndex=-1;
        endIndex=-1;
    }
    //destructor
    ~Node()
    {
        for (int i = 0; i <26 ; ++i)
            delete children[i];
    }
};
//class Suffix Tree has root of tree,text,its size
class SuffixTree
{
private:
    char *text;//entered string
    long long size;//size of string
    Node *root;
public:
    SuffixTree(char *ptr)//parametrized constructor takes entered string as pointer to char array
    {
        size=strlen(ptr);//find size of entered string by strlen
        text=ptr;
        root=new Node();
    }
    //insert as suffix trie
    void insertTries()
    {
        //loop from end of text to start
        for (long long i=size-1;i>-1;i--)
        {
            int index;
            //alphabet order of char
            if ((int)text[i]-(int)'a'>=0)
                index=(int)text[i]-(int)'a';//lower case
            else
                index=(int)text[i]-(int)'A';//upper case
            //put node refers to $ at end of nodes array
            if (text[i]=='$')
            {
                Node *newNode=new Node();//create new node
                newNode->startIndex=i;//start=index of char in text
                newNode->endIndex=i;//end=index of char in text
                root->children[26]=newNode;
            }
                //check if alphabet num is null in root children (first time) or not
                //if this char not found in root children
            else if (root->children[index]==NULL)
            {
                Node *newNode=new Node();//create new node
                newNode->startIndex=i;//start=index of char in text
                root->children[index]=newNode;
                Node* temp=root->children[index];
                //insert all chars from this char to end of text
                for (long long j=i+1;j<size;j++)
                {
                    Node *newNode1=new Node();//create new node
                    newNode1->startIndex=j;
                    if (j==size-1)//insert $
                    {
                        newNode1->endIndex=i;
                        temp->children[26]=newNode1;
                    }
                    else
                    {
                        int index1;
                        //alphabet order of char
                        if ((int)text[j]-(int)'a'>=0)
                            index1=(int)text[j]-(int)'a';//lower case
                        else
                            index1=(int)text[j]-(int)'A';//upper case
                        temp->children[index1]=newNode1;
                        temp=temp->children[index1];
                    }
                }
            }
                //if this char found in children of root
            else
            {
                //update startIndex with new num
                root->children[index]->startIndex=i;
                Node* temp=root->children[index];
                //insert all chars from this char to end of text
                for (long long j=i+1;j<size;j++)
                {
                    int index1;
                    if (j!=size-1)//not $
                    {
                        //alphabet order of char
                        if ((int)text[j]-(int)'a'>=0)
                            index1=(int)text[j]-(int)'a';//lower case
                        else
                            index1=(int)text[j]-(int)'A';//upper case
                    }
                    else
                        index1=26;

                    //if this node has children with same char
                    if (temp->children[index1]!=NULL)
                    {
                        temp->children[index1]->startIndex=j;//update startIndex
                        temp=temp->children[index1];
                    }
                        //this node hasn't children with same char
                    else
                    {
                        Node *newNode1=new Node();//create new node
                        newNode1->startIndex=j;//start=index of char in text
                        if (j==size-1)//insert $
                        {
                            newNode1->endIndex=i;
                            temp->children[26]=newNode1;
                        }
                        else
                        {
                            temp->children[index1]=newNode1;
                            temp=temp->children[index1];
                        }
                    }
                }
            }
        }
    }
    //convert suffix tries to suffix tree
    void change()
    {
        Node *temp=root;
        //loop for all root children and merge each branch
        for(int i=0;i<27;i++)
        {
            if(temp->children[i]!=NULL)
                changeTries(temp->children[i]);
        }
    }
    //merge all nodes have one child in entered node
    void changeTries(Node *temp)
    {
        //check num of children in node
        //if node has 0 or more than 1 child
        if(checkNum(temp)==-1&&temp->endIndex!=-1)
            return;
            //if node more than 1 child
        else if(checkNum(temp)==-1)
        {
            //recursion for its children
            for(int i=0;i<27;i++)
            {
                if(temp->children[i]!=NULL)
                    changeTries(temp->children[i]);
            }
        }
            //if node 1 child
        else
        {
            //return index of this child
            int ind=checkNum(temp);
            //take copy of this child
            Node *node=temp->children[ind];
            //take copy of its end
            long long end = node->endIndex;
            //update temp endIndex with child endIndex
            temp->endIndex=end;
            //update temp children array with child children array
            for(int i=0;i<27;i++)
                temp->children[i]=node->children[i];
            //recursion for this temp again
            for(int a=0;a<27;a++)
            {
                if(temp->children[a]!=NULL)
                    changeTries(temp);
            }
        }
    }
    //find num of children for entered node
    int checkNum(Node *node)
    {
        int counter=0;//num of children
        int ind=0;//index of children
        int n=0;//for while loop
        //loop for children array of node
        while (n<27)
        {
            //find child
            if (node->children[n]!=NULL)
            {
                counter++;//increase counter
                ind=n;//make index=order of this child in array
            }
            n++;
        }
        if (counter==1)//has child
            return ind;//return its index
        else
            return -1;//has 0 or more 1 child
    }
    //find length of chars in this node
    long long getNodeLen(Node* node)
    {
        //this node is leaf node
        if(node->endIndex!=-1)
        {
            //length=size of text - statIndex of node
            return size-(node->startIndex);
        }
            //not leaf node
        else
        {
            //find minimum startIndex of its children
            long long minLen;
            int first=0;
            //loop in children
            for(int i=0;i< 27;i++)
            {
                //set initial value to minLen with first child found
                if(node->children[i]!=NULL && first==0)
                {
                    first++;
                    minLen=node->children[i]->startIndex;
                }
                    //compare min value with other children
                else if(node->children[i]!=NULL&& node->children[i]->startIndex<minLen)
                    minLen=node->children[i]->startIndex;
            }
            return minLen-node->startIndex;
        }
    }

    void insert()
    {
        insertTries();//make suffix tries
        change();//convert to suffix tree
    }
    //takes substring and checks whether the substring (its prefix or the whole substring)
    //found at any of the root children node or not
    void search(char *subs)
    {
        //corresponding index of the 1st char in substring in the pointers Node array (initially 26 '$' )
        int idx=26;
        //setting index value if 1st char in sunstring is not $
        if(subs[0]!='$')
        {
            if (subs[0]-'a'>=0)
                idx=subs[0]-'a';
            else
                idx=subs[0]-'A';
        }
        //non of the root children is prefix in the substring
        if(root->children[idx]==NULL)
            cout<<"-1";
            //one of the root children found as prefix in the substring
        else
            check(root->children[idx],subs,0);
    }
    //checks whether the whole substring found in the suffix tree or not
    void check(Node* node,char *subs,long long subsIdx)
    {
        int f=0;
        long long prefixIdx=node->startIndex;//  start index of node
        long long prefixLen=getNodeLen(node);//  length of the substring assigned to node
        // loops as long as we don't reach substring and node's substring end
        while(subsIdx<strlen(subs)&&prefixLen>0)
        {
            if(text[prefixIdx]!=subs[subsIdx])
            {
                f=1;
                break;
            }
            subsIdx++;
            prefixIdx++;
            prefixLen--;
        }
        //the substring differs form the node string
        if(f==1)
            cout<<"-1";
            //a prefix of the substring = the node string
        else
        {
            //corresponding index of the current char in  substring in the pointers Node array (initially 26 '$' )
            int subCurrChrIdx=26;
            ////setting subCurrChrIdx value if current char in substring is not $
            if(subs[subsIdx]!='$')
            {
                if (subs[subsIdx]-'a'>=0)
                    subCurrChrIdx=subs[subsIdx]-'a';
                else
                    subCurrChrIdx=subs[subsIdx]-'A';
            }
            // the whole substring found in the tree
            if(subsIdx==strlen(subs))
                traversal(node);
                // a prefix of current substring = node string
            else if(node->children[subCurrChrIdx]!=NULL)
                //check for the rest of  substring
                check(node->children[subCurrChrIdx],subs,subsIdx);
                // the current substring differs form the node string
            else
                cout<<"-1";
        }
    }
    //print all endIndex of leaf nodes of found node
    void traversal (Node*node)
    {
        //base case is this node is leaf node
        if (node->endIndex!=-1)
        {
            cout<<node->endIndex<<" ";
            return;
        }
        else
        {
            //loop for its children
            for(int i=0;i<27;++i)
            {
                //recursion for children
                if (node->children[i]!=NULL)
                    traversal(node->children[i]);
            }
        }
    }
};
//test case 1,string=banana$
void testCase1()
{
    SuffixTree suffixTree("banana$");
    suffixTree.insert();//insert suffix tree
    suffixTree.search("anc");//-1 not found
    cout<<endl;
    suffixTree.search("ana");//1 3
    cout<<endl;
    suffixTree.search("nan");//2
}
//test case 2,string=papatpappa$
void testCase2()
{
    SuffixTree suffixTree("papatpappa$");
    suffixTree.insert();
    suffixTree.search("pa");//0 5 2 8
    cout<<endl;
    suffixTree.search("appap");//-1 not found
    cout<<endl;
    suffixTree.search("papa");//0
    cout<<endl;
    suffixTree.search("patc");//-1 not found
}
//test case 3,string=nonsense$
void testCase3()
{
    SuffixTree suffixTree("nonsense$");
    suffixTree.insert();
    suffixTree.search("nonsense$");//0
    cout<<endl;
    suffixTree.search("e$s");//-1 not found
    cout<<endl;
    suffixTree.search("se");//3 6
}
//test case 4,string=cagtcagg$
void testCase4()
{
    SuffixTree suffixTree("cagtcagg$");
    suffixTree.insert();
    suffixTree.search("acg");//-1 not found
    cout<<endl;
    suffixTree.search("tc");//3
    cout<<endl;
    suffixTree.search("$");//8
}
//test case 5,string=acacag$
void testCase5()
{
    SuffixTree suffixTree("acacag$");
    suffixTree.insert();
    suffixTree.search("cag");//3
    cout<<endl;
    suffixTree.search("a");//0 2 4
    cout<<endl;
    suffixTree.search("acacag");//0
}
//test case 6,string=bananabanaba$
void testCase6()
{
    SuffixTree suffixTree("bananabanaba$");
    suffixTree.insert();
    suffixTree.search("ana");//3 7 1
    cout<<endl;
    suffixTree.search("naba");//4 8
    cout<<endl;
    suffixTree.search("ba$");//10
}
//test case 7,string=papatpaptpa$
void testCase7()
{
    SuffixTree suffixTree("papatpaptpa$");
    suffixTree.insert();
    suffixTree.search("pat");//2
    cout<<endl;
    suffixTree.search("ba");//-1 not found
    cout<<endl;
    suffixTree.search("apa");//1
}
//test case 8,string=acacbacbacc$
void testCase8()
{
    SuffixTree suffixTree("acacbacbacc$");
    suffixTree.insert();
    suffixTree.search("acb");//2 5
    cout<<endl;
    suffixTree.search("c");//1 3 6 9 10
    cout<<endl;
    suffixTree.search("bacbac$");//-1 not found
}
//test case 9,string=HELLOHELLO$
void testCase9()
{
    SuffixTree suffixTree("HELLOHELLO$");
    suffixTree.insert();
    suffixTree.search("L");//7 2 8 3
    cout<<endl;
    suffixTree.search("HELLO");//0 5
    cout<<endl;
    suffixTree.search("O$");//9
}
//test case 10,string=TREETREE$
void testCase10()
{
    SuffixTree suffixTree("TREETREE$");
    suffixTree.insert();
    suffixTree.search("REE");//1 5
    cout<<endl;
    suffixTree.search("ER");//-1 not found
    cout<<endl;
    suffixTree.search("TR");//0 4
}

int main()
{
    //test cases
    testCase1();
    cout<<"\n\n";
    testCase2();
    cout<<"\n\n";
    testCase3();
    cout<<"\n\n";
    testCase4();
    cout<<"\n\n";
    testCase5();
    cout<<"\n\n";
    testCase6();
    cout<<"\n\n";
    testCase7();
    cout<<"\n\n";
    testCase8();
    cout<<"\n\n";
    testCase9();
    cout<<"\n\n";
    testCase10();
    return 0;
}