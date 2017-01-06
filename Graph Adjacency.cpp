//**************************************************************
//  Project2P1.cpp
//  Graphs
//
//  Created by Aniketh Sukhtankar on November 11, 2016.
//  Program to implement a graph data structure using an adjacency list
//  Implements a Graph class.
//**************************************************************
#include <iostream> //to use cout
#include <iomanip> //to format output
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>

using namespace std;

class AdjListNode		//AdjListNode class for defining node
{
public:
    string univName;
    int sc1,sc2;
    AdjListNode *AdjList;
    AdjListNode *myNext;

    AdjListNode(string univName,int sc1,int sc2)
    {
        this->univName=univName;
        this->sc1=sc1;
        this->sc2=sc2;
        this->AdjList=this->myNext=0;
    }
};


class Graph			//class Graph to define graph
{
public:
    AdjListNode * myHead;
    int *pi,*color,*d,*f,timeCnter;

    Graph()
    {
        myHead=0;
    }

    ~Graph()				//Destructor
    {
        if(myHead!= 0)
        {
            AdjListNode*n=myHead,*n1,*scrap,*scrap2;
            while((*n).myNext!=0)
            {
                n1=(*n).AdjList;
                if(n1!=0)
                {
                    while((*n1).myNext!=0)
                    {
                        scrap=n1;
                        n1=(*n1).myNext;
                        delete scrap;
                    }
                    delete n1;
                }
                scrap2=n;
                n=(*n).myNext;
                delete scrap2;
            }
            n1=(*n).AdjList;
            if(n1!=0)
            {
                while((*n1).myNext!=0)
                {
                    scrap=n1;
                    n1=(*n1).myNext;
                    delete scrap;
                }
                delete n1;
            }
            scrap2=n;
            delete scrap2;
        }
        myHead=0;
    }


    void graphInsertEdge(string univName1,int sc1,string univName2,int sc2)
    {
        if(myHead!=0)
        {
           AdjListNode*n;
            n=nodeExists(univName1);
            if(n==0)
            {
                n=new AdjListNode(univName1,0,0);
                AdjListNode*start=myHead,*prev=myHead;;
                while(start!=0)				//insert edge in graph
                {
                    if((*start).univName < univName1)
                    {
                        prev = start;
                        start=(*start).myNext;
                    }
                    else
                        break;
                }
                if(start!=prev)					//insert edge in graph
                {
                   (*n).myNext=start;
                    (*prev).myNext=n;
                    AdjListNode*n1=new AdjListNode(univName2,sc1,sc2);
                    (*n).AdjList=n1;


                }
                else						//insert edge in graph
                {
                    AdjListNode*n1=new AdjListNode(univName2,sc1,sc2);
                    (*n).myNext=myHead;
                    myHead=n;
                    (*myHead).AdjList=n1;
                }
                if(nodeExists(univName2)==0)
                {
                    n=new AdjListNode(univName2,0,0);
                    AdjListNode*start=myHead,*prev=myHead;;
                    while(start!=0)
                    {
                        if((*start).univName < univName2)
                        {
                            prev = start;
                            start=(*start).myNext;
                        }
                        else
                            break;
                    }
                    if(start!=prev)
                    {
                        (*n).myNext=start;
                        (*prev).myNext=n;


                    }
                    else
                    {
                        (*n).myNext=myHead;
                        myHead=n;
                    }
                }
            }
            else
            {
                AdjListNode*start=(*n).AdjList,*prev,*myHead1;
                AdjListNode*n1=new AdjListNode(univName2,sc1,sc2);
                prev=start;
                myHead1=start;
                if(start==0)
                {
                    (*n).AdjList=n1;
                }
                else
                {
                    while(start!=0)			//insert edge in graph
                    {
                        if((*start).univName < univName2)
                        {
                            prev = start;
                            start=(*start).myNext;
                        }
                        else
                            break;
                    }
                    if(start==prev)				//insert edge in graph
                    {
                        (*n1).myNext=(*n).AdjList;
                        (*n).AdjList=n1;
                    }
                    else
                    {
                        (*n1).myNext=start;
                        (*prev).myNext=n1;
                    }
                }
                if(nodeExists(univName2)==0)
                {
                    n=new AdjListNode(univName2,0,0);
                    AdjListNode*start=myHead,*prev=myHead;
                    while(start!=0)
                    {
                        if((*start).univName < univName2)
                        {
                            prev = start;
                            start=(*start).myNext;
                        }
                        else
                            break;
                    }
                    if(start==prev)
                    {
                        (*n).myNext=myHead;
                        myHead=n;
                    }
                    else
                    {
                        (*n).myNext=start;
                        (*prev).myNext=n;
                    }
                }
            }
        }
        else
        {
            AdjListNode* n=new AdjListNode(univName1,0,0);
            AdjListNode*n1=new AdjListNode(univName2,sc1,sc2);
            AdjListNode*n2=new AdjListNode(univName2,0,0);
            if(univName1 > univName2)
            {
                myHead=n2;
                (*myHead).myNext=n;
                (*n).AdjList=n1;
            }
            else
            {
                myHead=n;
                (*myHead).myNext=n2;
                (*n).AdjList=n1;
            }

        }
    }


    void graphInsertNode(string line)			//insert AdjListNode in graph
    {
        string univName1,s1,univName2,s2;
        int sc1,sc2;
        stringstream ss(line);
        getline(ss,univName1,',');
        getline(ss,s1,',');
        getline(ss,univName2,',');
        getline(ss,s2);
        sc1=atoi(s1.c_str());
        sc2=atoi(s2.c_str());

        graphInsertEdge(univName1,sc1,univName2,sc2);

    }


    void depthFirstSearch()		//depth_first_search alogorithm
    {
        AdjListNode*n=myHead;
        int cnter;
        while(n!=0)
        {
            cnter++;
            n=(*n).myNext;
        }
        pi=new int[cnter];
        color=new int[cnter];
        d=new int[cnter];
        f=new int[cnter];
        int i=0;
        while(i<cnter)
        {
            color[i]=0;
            pi[i]=-1;
            i++;
        }
        timeCnter=0;
        i=0;
        while(i<cnter)
        {
            if(color[i]==0)		//white
                visited(i);

            i++;

        }
        pi_util(cnter);
        printDiscoverTime(cnter);
        printFinishTime(cnter);

    }


    void visited(int u)			//Depth first search visit algorithm
    {
        AdjListNode*n,*myAdjList;
        int v;
        color[u]=1;		//gray
        timeCnter++;
        d[u]=timeCnter;
        n=findAdjListNode(u);
        myAdjList=(*n).AdjList;
        while(myAdjList!=0)
        {
            v=findindex(myAdjList);
            if(color[v]==0)
            {
                pi[v]=u;
                visited(v);
            }
            myAdjList=(*myAdjList).myNext;
        }
        color[u]=2;		//black
        timeCnter++;
        f[u]=timeCnter;
    }


    void print_graph()			//print graph
    {
        cout<<endl<<"Graph (Adjacency List) content"<<endl;
        if(myHead==0)
            cout<<"Graph is empty";
        else
        {
            AdjListNode*n =myHead;
            while(n!=0)
            {
                cout<<endl<<n->univName<<" beat: ";
                if((*n).AdjList!=0)
                {
                    AdjListNode* myAdjList=(*n).AdjList;
                    while((*myAdjList).myNext!=0)
                    {
                        cout<<(*myAdjList).univName<<"("<<(*myAdjList).sc1<<"-"<<(*myAdjList).sc2<<"), ";
                        myAdjList=(*myAdjList).myNext;
                    }
                    cout<<(*myAdjList).univName<<"("<<(*myAdjList).sc1<<"-"<<(*myAdjList).sc2<<")";
                }
                else
                {
                     cout<<"none";
                }
                n=(*n).myNext;
                cout<<endl;
            }
            cout<<endl;
        }
    }


    AdjListNode* nodeExists(string univName)
    {
        AdjListNode*n=myHead;
        while(n!=0)
        {
            if((*n).univName==univName)
                return n;
            n=(*n).myNext;
        }
        return 0;
    }


    AdjListNode* findAdjListNode(int u)
    {
        int cnter=0;
        AdjListNode*n=myHead;
        while(n!=0)
        {
            if(cnter==u)
                return n;
            n=(*n).myNext;
            cnter++;
        }
    }


    int findindex(AdjListNode*T)
    {
        int cnter=0;
        AdjListNode*n=myHead;
        while(n!=0)
        {
            if((*n).univName==(*T).univName)
                return cnter;
            cnter++;
            n=(*n).myNext;
        }
    }


    void pi_util(int cnter)			//To print pi values of AdjListNodes
    {
        cout<<"\nThe array pi content:\n";
        int i=0;
        while(i<cnter)
        {
            cout<<"\npi["<<(*(findAdjListNode(i))).univName<<"]=";
            if(pi[i]==-1)
                cout<<"none";
            else
                cout<<(*(findAdjListNode(pi[i]))).univName;

            i++;
        }
        cout<<endl;
    }


    void printDiscoverTime(int cnter)			//to print discover times of AdjListNodes
    {
        cout<<"\nThe array discoverTime content:\n";
        int i=0;
        while(i<cnter)
        {
            cout<<"\ndiscoverTime["<<(*(findAdjListNode(i))).univName<<"]=number "<<d[i];
             i++;
        }
        cout<<endl;
    }



    void printFinishTime(int cnter)			//to print found time of AdjListNodes
    {
        cout<<"\nThe array finishTime content:\n";
        int i=0;
        while(i<cnter)
        {
            cout<<"\nfinishTime["<<(*(findAdjListNode(i))).univName<<"]=number "<<f[i];
            i++;
        }
        cout<<endl;
    }
};



int main(int argc,char*argv[])
{
    Graph myGraph;
    string input,Var1,Var2,line,edge11;
    int firstLine,secondLine,totalLines=0,check=0;
    if ( argc < 3 || argc > 3 )
    {
        cout<<"Invalid arguments passed";
        exit(0);
    }
    ifstream command1(argv[1]);
    if ( !command1.is_open() )
    {
        cout<<"Unable to open file1\n";
        exit(0);
    }
    edge11=argv[2];
    while(getline(command1,line))
    {
        cout<<"\nnext command: "<<line<<endl;
        stringstream ss(line);
        getline(ss,input,',');
        if(input=="graph")
        {
            getline(ss,Var1,',');
            getline(ss,Var2,',');
            firstLine=atoi(Var1.c_str());
            secondLine=atoi(Var2.c_str());
            ifstream edge1(edge11.c_str());
            if ( !edge1.is_open() )
            {
                cout<<"Unable to open file2\n";
                exit(0);
            }
            else
            {
                while (getline(edge1, line))
                {
                    if(totalLines==firstLine)
                    {
                        check=1;
                    }
                    if(check==1)
                    {
                        myGraph.graphInsertNode(line);
                    }
                    if(totalLines==secondLine)
                    {
                        check=0;
                        break;
                    }
                    totalLines++;
                }
                edge1.close();
            }
        }
        else if(input=="print_graph\r")
        {
            myGraph.print_graph();
        }
        else if(input=="depth_first_search\r")
        {
            myGraph.depthFirstSearch();
        }
        else if(input=="end_graph\r")
        {
            myGraph.~Graph();
            totalLines=0;
            check=0;
        }
        else if(input=="quit\r")
        {
            exit(0);
        }
        else
        {
            cout<<"Please Enter Valid Command\n";
            exit(0);
        }
    }
    command1.close();
    return 0;
}
