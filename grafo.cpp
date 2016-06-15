#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>

using namespace std;

template<class G>
struct gnode
{
    typedef typename G::N N;
    typedef typename G::Edge Edge;
    vector<Edge*> m_edges;
    N data;
    gnode(){}
    gnode(N a){data=a;}
};

template<class G>
struct gedge
{
    typedef typename G::E E;
    typedef typename G::Node Node;
    Node * m_nodes[2];
    E data;
    gedge(){}
    gedge(E w,Node* X,Node* Y){data=w;m_nodes[0]=X;m_nodes[1]=Y;}
};

template <class A, class B>
struct Graph
{
    typedef Graph<A,B> self;
    typedef gnode<self> Node;
    typedef gedge<self> Edge;
    typedef A N;
    typedef B E;
    vector<Node*> m_nodes;
    Graph(){}
    bool insert_node(N data){
        for(unsigned int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i]->data==data)
                return 0;
        }
        Node *nodo=new Node(data);
        m_nodes.push_back(nodo);
        return 1;
    }
    bool insert_edge(N in,N fn,E data,bool dir){
        unsigned int fA=0,fB=0;
        for(unsigned int i=0;i<m_nodes.size();i++)
        {
            if(m_nodes[i]->data==in)
                fA=i;
            if(m_nodes[i]->data==fn)
                fB=i;
        }
        if(fA!=m_nodes.size() and fB!=m_nodes.size())
        {
            if(dir)
            {
                Edge* ED2=new Edge(data,m_nodes[fB],m_nodes[fA]);
                m_nodes[fB]->m_edges.push_back(ED2);
            }
            Edge* ED=new Edge(data,m_nodes[fA],m_nodes[fB]);
            m_nodes[fA]->m_edges.push_back(ED);
            return 1;
        }
        return 0;
    }
    void print()
    {
        unsigned long X=m_nodes.size();
        for(int i=0;i<X;i++)
            cout<<'\t'<<m_nodes[i]->data;
        cout<<endl;
        for(int i=0;i<X;i++)
        {
            cout<<m_nodes[i]->data<<'\t';
            for(int j=0;j<X;j++)
            {
                bool mmm=0;
                unsigned long Y=m_nodes[i]->m_edges.size();
                unsigned long k;
                for(k=0;k<Y;k++)
                {
                    if(m_nodes[i]->m_edges[k]->m_nodes[1]==m_nodes[j])
                    {
                        mmm=1;
                        break;
                    }
                }
                if(mmm)
                    cout<<m_nodes[i]->m_edges[k]->data;
                else
                    cout<<"-";
                cout<<'\t';
            }
            cout<<endl;
        }
    }
    ~Graph(){}
};


int main()
{
    Graph<int , int> graph;
    graph.insert_node(2);
    graph.insert_node(4);
    graph.insert_node(1);
    graph.insert_node(6);
    graph.insert_node(8);
    graph.insert_node(5);
    graph.insert_edge(2, 4, 12, 0);
    graph.insert_edge(1, 4, 4, 0);
    graph.insert_edge(6, 1, 8, 0);
    graph.insert_edge(8, 6, 2, 0);
    graph.insert_edge(5, 8, 27, 0);
    graph.insert_edge(5, 6, 6, 0);
    graph.print();
    return 0;
}
