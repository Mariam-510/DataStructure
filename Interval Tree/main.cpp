#include <iostream>
using namespace std;
//interval struct
struct Interval{
    //has low,high
    int low,high;
    //setter
    void setLH(int l,int h){
        low=l;
        high=h;
    }
};
//class node
class Node{
public:
    //has max,interval,left,right child
    int max;
    Interval interval;
    Node*left,*right;
    //constructor set initial values
    Node(){
        max=-1;
        interval.low=-1;
        interval.high=-1;
        left=NULL;
        right=NULL;
    }
};
//IntervalTree Class
class IntervalTree {
public:
    Node *root;//root of tree
    int nodeNum;//num of nodes in tree
    //constructor
    IntervalTree(){
        //set root with null, num with 0
        root=NULL;
        nodeNum=0;
    }
    //insert interval with unbalanced BST roles(takes parameters node,interval)
    Node* InsertInterval(Node* node,Interval in){
        //find interval place
        if (node==NULL){
            Node* newNode=new Node();//make new node
            newNode->interval.low=in.low;//set low
            newNode->interval.high=in.high;//set high
            node = newNode;//make this node=newNode
        }
        //if interval's low is less than node's low,go to left subtree of node
        else if (in.low<node->interval.low)
            node->left=InsertInterval(node->left,in);
        //if interval's low is greater than or equal node's low,go to right subtree of node
        else
            node->right=InsertInterval(node->right,in);
        return node;
    }
    //insert interval with unbalanced BST roles(takes parameter interval only)
    void InsertInterval(Interval in){
        //call InsertInterval and give it root and interval
        root=InsertInterval(root,in);
        //increase num of nodes
        nodeNum++;
        //update max for all nodes
        updateMax(root);
    }
    //predecessor(max value in left subtree of parameter node)
    Node* finMax(Node* node){
        Node* temp=node;
        //predecessor is the last right node
        while (temp!=NULL&&temp->right!=NULL)
            temp=temp->right;
        return temp;
    }
    //delete interval with unbalanced BST roles(takes parameters node,interval)
    Node* DeleteInterval(Node* node,Interval in){
        if (node==NULL)
            return node;
        //interval's low is less than node's low,go to left subtree of node
        if (in.low<node->interval.low)
            node->left=DeleteInterval(node->left,in);
        //interval's low is greater than node's low,go to right subtree of node
        else if (in.low>node->interval.low)
            node->right=DeleteInterval(node->right,in);
        // compare high
        else if (in.low==node->interval.low&&in.high!=node->interval.high)
            node->right=DeleteInterval(node->right,in);
        //interval's low,high is equal node's low,high
        else{
            //leaf node,just delete it
            if (node->left==NULL&&node->right==NULL)
                return NULL;
            //has only right child
            else if (node->left==NULL){
                Node* temp=node->right;
                delete node;
                return temp;
            }
            //has only left child
            else if (node->right==NULL){
                Node* temp=node->left;
                delete node;
                return temp;
            }
            //has right and left children
            //find predecessor
            Node* temp=finMax(node->left);
            //set node value with predecessor value
            node->interval.low=temp->interval.low;
            node->interval.high=temp->interval.high;
            //delete predecessor
            node->left=DeleteInterval(node->left, temp->interval);
        }
        return node;
    }
    //delete interval with unbalanced BST roles(takes parameter interval only)
    void DeleteInterval(Interval in){
        //call DeleteInterval and give it root and interval
        root = DeleteInterval(root,in);
        //decrease num of nodes
        nodeNum--;
        //update max for all nodes
        updateMax(root);
    }
    //update max value for all nodes
    int updateMax(Node* &node){
        //leaf node,set max with high
        if(node->left==NULL&&node->right==NULL){
            node->max=node->interval.high;
            return node->max;
        }
        //has only left
        else if(node->left!=NULL&&node->right==NULL){
            //find max of left subtree,compare with high of node
            int maxL = updateMax(node->left);
            if (node->interval.high> maxL)
                node->max=node->interval.high;
            else
                node->max = maxL;
        }
        //has only right
        else if(node->left==NULL&&node->right!=NULL){
            //find max of right subtree,compare with high of node
            int maxR=updateMax(node->right);
            if (node->interval.high>maxR)
                node->max=node->interval.high;
            else
                node->max=maxR;
        }
        //has right,left subtrees
        else{
            //find max of left and right subtree,compare them with high of node
            int maxL=updateMax(node->left);
            int maxR=updateMax(node->right);
            int Max=node->interval.high;
            if(Max<maxL)
                Max=maxL;
            if(Max<maxR)
                Max=maxR;
            node->max=Max;
        }
        return node->max;
    }
    //print tree in inorder way(left subtree,root,right subtree)
    void inorder(Node* node){
        if (node==NULL)
            return;
        inorder(node->left);
        cout <<"["<< node->interval.low<<","<<node->interval.high<<"] max = "<<node->max<<"\n";
        inorder(node->right);
    }
    void inorder()
    {
        inorder(root);
    }
    //check node's interval overlap with parameter interval
    bool checkOverlap(Node *node,Interval in){
        bool o=false;
        //overlap condition
        if(node->interval.low<=in.high&&in.low<=node->interval.high)
            o=true;
        return o;
    }
    //search for one overlapping interval
    Node* SearchInterval(Node* node,Interval in){
        //loop until node=null
        while (node!=NULL)
        {
            //node doesn't overlap
            if (!checkOverlap(node,in)){
                //if has left child,check low of parameter interval <= left child's max
                if (node->left!=NULL&&in.low<=node->left->max)
                    node=node->left;
                else
                    node=node->right;
            }
            //node overlap with the parameter interval,break,return node
            else
                break;
        }
        return node;
    }
    //search for all overlapping interval
    void SearchInterval(Interval in){
        //array restore low and high of overlapping intervals,has max size(num of nodes in tree)
        int arr[2*nodeNum];
        int ind=0;
        Node *temp=SearchInterval(root,in);
        //return all intervals overlapping with parameter interval
        while (temp!=NULL){
            //add overlapping interval's low and high to be inserted again
            arr[ind++]=temp->interval.low;
            arr[ind++]=temp->interval.high;
            //print overlapping interval
            cout<<"["<<temp->interval.low<<","<<temp->interval.high<<"] max = "<<temp->max<<"\n";
            //delete overlapping interval
            DeleteInterval(temp->interval);
            temp=SearchInterval(root,in);
        }
        //no overlapping interval found
        if (ind==0)
            cout<<"No intervals overlapping with the parameter interval\n";
        //insert all intervals again in tree to restore its status
        for (int i = 0; i <ind ; i+=2){
            Interval iN;//make new interval
            iN.low=arr[i];
            iN.high=arr[i+1];
            InsertInterval(iN);//insert interval
        }
    }
};
//4 search
void testCase1(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(17,19);
    inT.InsertInterval(in);
    in.setLH(5,11);
    inT.InsertInterval(in);
    in.setLH(4,8);
    inT.InsertInterval(in);
    in.setLH(15,18);
    inT.InsertInterval(in);
    in.setLH(22,23);
    inT.InsertInterval(in);
    in.setLH(7,10);
    inT.InsertInterval(in);
    //search
    cout<<"1)Tree\n";
    inT.inorder();
    in.setLH(12,14);
    cout<<"\n1)Search[12,14]\n";
    inT.SearchInterval(in);
    cout<<"\n2)Tree\n";
    inT.inorder();
    in.setLH(14,16);
    cout<<"\n2)Search[14,16]\n";
    inT.SearchInterval(in);
    cout<<"\n3)Tree\n";
    inT.inorder();
    in.setLH(6,7);
    cout<<"\n3)Search[6,7]\n";
    inT.SearchInterval(in);
    cout<<"\n4)Tree\n";
    inT.inorder();
    in.setLH(14,26);
    cout<<"\n4)Search[14,26]\n";
    inT.SearchInterval(in);
}
//6 search
void testCase2(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(30,60);
    inT.InsertInterval(in);
    in.setLH(15,25);
    inT.InsertInterval(in);
    in.setLH(5,45);
    inT.InsertInterval(in);
    in.setLH(70,80);
    inT.InsertInterval(in);
    in.setLH(60,90);
    inT.InsertInterval(in);
    in.setLH(85,95);
    inT.InsertInterval(in);
    in.setLH(40,58);
    inT.InsertInterval(in);
    in.setLH(90,99);
    inT.InsertInterval(in);
    //search
    cout<<"\n5)Tree\n";
    inT.inorder();
    in.setLH(80,82);
    cout<<"\n5)Search[80,82]\n";
    inT.SearchInterval(in);
    cout<<"\n6)Tree\n";
    inT.inorder();
    in.setLH(40,50);
    cout<<"\n6)Search[40,50]\n";
    inT.SearchInterval(in);
    cout<<"\n7)Tree\n";
    inT.inorder();
    in.setLH(6,10);
    cout<<"\n7)Search[6,10]\n";
    inT.SearchInterval(in);
    cout<<"\n8)Tree\n";
    inT.inorder();
    in.setLH(100,200);
    cout<<"\n8)Search[100,200]:\n";
    inT.SearchInterval(in);
    cout<<"\n9)Tree\n";
    inT.inorder();
    in.setLH(50,70);
    cout<<"\n9)Search[50,70]\n";
    inT.SearchInterval(in);
    cout<<"\n10)Tree\n";
    inT.inorder();
    in.setLH(25,28);
    cout<<"\n10)Search[25,28]\n";
    inT.SearchInterval(in);
}
//5 search
void testCase3(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(55,70);
    inT.InsertInterval(in);
    in.setLH(0,30);
    inT.InsertInterval(in);
    in.setLH(5,10);
    inT.InsertInterval(in);
    in.setLH(100,120);
    inT.InsertInterval(in);
    in.setLH(2,3);
    inT.InsertInterval(in);
    in.setLH(130,160);
    inT.InsertInterval(in);
    in.setLH(140,180);
    inT.InsertInterval(in);
    in.setLH(205,230);
    inT.InsertInterval(in);
    //search
    cout<<"\n11)Tree\n";
    inT.inorder();
    in.setLH(55,70);
    cout<<"\n11)Search[55,70]\n";
    inT.SearchInterval(in);
    cout<<"\n12)Tree\n";
    inT.inorder();
    in.setLH(5,10);
    cout<<"\n12)Search[5,10]\n";
    inT.SearchInterval(in);
    cout<<"\n13)Tree\n";
    inT.inorder();
    in.setLH(125,150);
    cout<<"\n13)Search[125,150]\n";
    inT.SearchInterval(in);
    cout<<"\n14)Tree\n";
    inT.inorder();
    in.setLH(101,121);
    cout<<"\n14)Search[101,121]\n";
    inT.SearchInterval(in);
    cout<<"\n15)Tree\n";
    inT.inorder();
    in.setLH(207,209);
    cout<<"\n15)Search[207,209]\n";
    inT.SearchInterval(in);
}
//5 search
void testCase4(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(15,40);
    inT.InsertInterval(in);
    in.setLH(10,28);
    inT.InsertInterval(in);
    in.setLH(16,23);
    inT.InsertInterval(in);
    in.setLH(5,24);
    inT.InsertInterval(in);
    in.setLH(11,16);
    inT.InsertInterval(in);
    in.setLH(18,60);
    inT.InsertInterval(in);
    //search
    cout<<"\n16)Tree\n";
    inT.inorder();
    in.setLH(0,5);
    cout<<"\n16)Search[0,5]\n";
    inT.SearchInterval(in);
    cout<<"\n17)Tree\n";
    inT.inorder();
    in.setLH(40,60);
    cout<<"\n17)Search[40,60]\n";
    inT.SearchInterval(in);
    cout<<"\n18)Tree\n";
    inT.inorder();
    in.setLH(80,99);
    cout<<"\n18)Search[80,99]\n";
    inT.SearchInterval(in);
    cout<<"\n19)Tree\n";
    inT.inorder();
    in.setLH(27,35);
    cout<<"\n19)Search[27,35]\n";
    inT.SearchInterval(in);
    cout<<"\n20)Tree\n";
    inT.inorder();
    in.setLH(29,39);
    cout<<"\n20)Search[29,39]\n";
    inT.SearchInterval(in);
}
//4 search
void testCase5(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(20,36);
    inT.InsertInterval(in);
    in.setLH(3,41);
    inT.InsertInterval(in);
    in.setLH(0,1);
    inT.InsertInterval(in);
    in.setLH(10,15);
    inT.InsertInterval(in);
    in.setLH(29,89);
    inT.InsertInterval(in);
    //search
    cout<<"\n21)Tree\n";
    inT.inorder();
    in.setLH(1,3);
    cout<<"\n21)Search[1,3]\n";
    inT.SearchInterval(in);
    cout<<"\n22)Tree\n";
    inT.inorder();
    in.setLH(25,60);
    cout<<"\n22)Search[25,60]\n";
    inT.SearchInterval(in);
    cout<<"\n23)Tree\n";
    inT.inorder();
    in.setLH(77,88);
    cout<<"\n23)Search[77,88]\n";
    inT.SearchInterval(in);
    cout<<"\n24)Tree\n";
    inT.inorder();
    in.setLH(36,97);
    cout<<"\n24)Search[36,97]\n";
    inT.SearchInterval(in);
}
//6 search
void testCase6(){
    //insert
    IntervalTree inT;
    Interval in;
    in.setLH(0,4);
    inT.InsertInterval(in);
    in.setLH(100,120);
    inT.InsertInterval(in);
    in.setLH(6,8);
    inT.InsertInterval(in);
    in.setLH(5,10);
    inT.InsertInterval(in);
    in.setLH(130,160);
    inT.InsertInterval(in);
    in.setLH(29,35);
    inT.InsertInterval(in);
    in.setLH(35,40);
    inT.InsertInterval(in);
    in.setLH(190,200);
    inT.InsertInterval(in);
    in.setLH(205,230);
    inT.InsertInterval(in);
    //search
    cout<<"\n25)Tree\n";
    inT.inorder();
    in.setLH(6,8);
    cout<<"\n25)Search[6,8]\n";
    inT.SearchInterval(in);
    cout<<"\n26)Tree\n";
    inT.inorder();
    in.setLH(240,280);
    cout<<"\n26)Search[240,280]\n";
    inT.SearchInterval(in);
    cout<<"\n27)Tree\n";
    inT.inorder();
    in.setLH(30,50);
    cout<<"\n27)Search[30,50]\n";
    inT.SearchInterval(in);
    cout<<"\n28)Tree\n";
    inT.inorder();
    in.setLH(100,120);
    cout<<"\n28)Search[100,120]\n";
    inT.SearchInterval(in);
    cout<<"\n29)Tree\n";
    inT.inorder();
    in.setLH(30,50);
    cout<<"\n29)Search[30,50]\n";
    inT.SearchInterval(in);
    cout<<"\n30)Tree\n";
    inT.inorder();
    in.setLH(300,310);
    cout<<"\n30)Search[300,310]\n";
    inT.SearchInterval(in);
}
int main(){
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    return 0;
}