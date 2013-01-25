/*
Please write complete compilable code.
Read input from standard input (STDIN) and print output to standard output(STDOUT).
For more details, please check https://www.interviewstreet.com/recruit/challenges/faq/view#stdio
*/

#include <queue>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Peg{
public:
    vector<int> discs;
    int id;
};

class Node{
public:
    int *conf;
    int n;
    int k;
    Node *parent;
    Peg *pegs;
    string steps;

    void fillPegs()
    {
        pegs = new Peg[k];
        for (int i=0; i<k; i++)
        {
            pegs[i].id = i;
        }
        for (int i=0; i<n; i++)
        {
            pegs[conf[i]].discs.push_back(i);
        }
        for (int i=0; i<k; i++)
        {
            sort(pegs[i].discs.begin(), pegs[i].discs.end());
        }
    };

    void deletePegs()
    {
        delete[] pegs;
    }
    
    Node(int *c, int n, int k):n(n), k(k)
    {
      	conf=new int[n];
        memcpy(conf, c, n*sizeof(int));
        parent = NULL;
    };
    
    ~Node()
    {
      	delete[] conf;
    };
};

class Records{
public:
    vector<Node*> records;
    bool isDup(int *query)
    {
        bool found = false;
        for (vector<Node*>::iterator it=records.begin(); it!=records.end(); it++)
        {
            int i=0;
            for (i=0; i<(*it)->n; i++)
            {
                if ((*it)->conf[i] != query[i])
                    break;
            }
            if (i==(*it)->n) 
            {
                found = true;
                break;
            }
        }
        return found;
    };
    void printSolution(Node* node)
    {
        stack<string> statements;
        while (node->parent)
        {
            statements.push(node->steps);
            node = node->parent;
        }
        cout << statements.size() << std::endl;
        while (!statements.empty())
        {
            string p = statements.top();
            cout << p << std::endl;
            statements.pop();
        }
    }
    ~Records(){
        for (vector<Node*>::iterator it=records.begin(); it!=records.end(); it++)
        {
            delete *it;
        }
    };
};

int main(int argc, char **argv)
{
    int n, k;
    int *conf_init, *tmp;
    Records r;
	
    cin >> n >> k;
    conf_init=new int[n];
    tmp=new int[n];
    
    for (int i=0; i<n; i++)
       	cin >> conf_init[i];
    for (int i=0; i<n; i++)
        cin >> tmp[i];
    
    for (int i=0; i<n; i++)
        conf_init[i] = conf_init[i]-1;
    	
    for (int i=0; i<n; i++)
        tmp[i] = tmp[i]-1;
    
    queue<Node*> q;
    Node *target = new Node(tmp, n, k);
    bool found = false;
    q.push(new Node(conf_init,n,k));

    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        r.records.push_back(node);
        int fi=0;
        for (fi=0; fi<n; fi++)
        {
            if (node->conf[fi]!=target->conf[fi])
            {
                break;
            }
        }
        if (fi==n)
        {
            found = true;
            r.printSolution(node);
            break;
        }
        node->fillPegs();
        for (int i=0; i<node->k; i++)
        {
            memcpy(tmp, node->conf, n*sizeof(int));
            for (int j=0; j<node->k && !node->pegs[i].discs.empty(); j++)
            {
                if (j!=i)
                {
                    if (node->pegs[j].discs.empty() ||
                        node->pegs[i].discs[0] < node->pegs[j].discs[0])
                    {
                        tmp[node->pegs[i].discs[0]]=j;
                        if (!r.isDup(tmp))
                        {
                            Node *newNode = new Node(tmp, n, k);
                            newNode->parent = node;
                            stringstream ss(stringstream::in | stringstream::out);
                            ss << i+1 << " " << j+1;
                            newNode->steps = ss.str();
                            //cout << newNode->steps << endl;
                            q.push(newNode);
                        }
                    }
                }
            }
            
        }
        node->deletePegs();
    }
    delete[] conf_init;
    delete[] tmp;
    delete target;
}
