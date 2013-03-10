#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <sys/timeb.h>
#include <cstdlib>

using namespace std;

const long long modulo=1000003;

long long modular_pow(long long base, long long exponent)
{
    long long result = 1;
    while (exponent > 0)
    {
        if (exponent%2 == 1)
            result = (result * base)%modulo;
        exponent = exponent >> 1;
        base = (base * base)%modulo;
    }
    return result;
}

int GetMilliCount()
{
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

int GetMilliSpan( int nTimeStart )
{
  int nSpan = GetMilliCount() - nTimeStart;
  if ( nSpan < 0 )
    nSpan += 0x100000 * 1000;
  return nSpan;
}

typedef struct segment_tree_node{
    int ibegin;
    int iend;
    long long dp;
    long long psum;
    long long dprod;
    int index;
    long long lazy;
    segment_tree_node()
    {
        index=-1;
        dp=1;
        lazy=0;
        psum=0;
        dprod=1;
    };
}segment_tree_node;

segment_tree_node treeRoot[1+(1<<20)];

class segment_tree{
public:
    static segment_tree_node *root;
    vector<long long> &d;
    vector<long long> &p;
    static int rootsize;
    segment_tree( vector<long long> &d,
                  vector<long long> &p)
        :d(d), p(p)
    {
    };
    //build tree
    void build_tree(int n)
    {
        build(1, n, 1);
    };
    void build(int i, int j, int index)
    {
        if (i > j) 
        {
            root[index].ibegin=i;
            root[index].iend=j;
            return;
        }
        if (index > rootsize-1)
        {
            cout << "Warning: your segment tree is not large enough!!!" << endl;
            exit(1);
        }
        root[index].ibegin=i;
        root[index].iend=j;
        root[index].index=index;
        if (root[index].ibegin==root[index].iend)
        {
            root[index].psum=p[root[index].ibegin-1];
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=modular_pow(d[root[index].ibegin-1],p[root[index].ibegin-1]);
            root[index].dprod=d[root[index].ibegin-1];
            return;
        }
        else
        {
            build(i,(i+j)/2, index*2);
            build((i+j)/2+1,j, index*2+1);
            root[index].dprod=(root[index*2].dprod*root[index*2+1].dprod)%modulo;
            root[index].psum=root[index*2].psum+root[index*2+1].psum;
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=(root[index*2].dp*root[index*2+1].dp)%modulo;
        }
    };
    //update tree
    void update_tree(int i, int j, long long v, int index)
    {
        if (root[index].index==-1)
            return;
        if(root[index].lazy) {
            root[index].psum+=(root[index].iend-root[index].ibegin+1)*root[index].lazy;
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=(root[index].dp*modular_pow(root[index].dprod,root[index].lazy))%modulo;
            if(root[index].ibegin != root[index].iend) {
                root[index*2].lazy += root[index].lazy;
                root[index*2+1].lazy += root[index].lazy;
            }
            root[index].lazy=0;
        }
        if(root[index].ibegin > root[index].iend || root[index].ibegin > j || root[index].iend < i) 
            return;
        if(root[index].ibegin >= i && root[index].iend <= j) 
        {
            root[index].psum+=(root[index].iend-root[index].ibegin+1)*v;
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=(root[index].dp*modular_pow(root[index].dprod,v))%modulo;
            if(root[index].ibegin != root[index].iend) { // Not leaf node
                root[index*2].lazy += v;
                root[index*2+1].lazy += v;
            }
            return;
        }
        if (root[index].ibegin!=root[index].iend)
        {
            update_tree(i,j,v,index*2);
            update_tree(i,j,v,index*2+1);
            root[index].psum=root[index*2].psum+root[index*2+1].psum;
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=(root[index*2].dp*root[index*2+1].dp)%modulo;
        }
    };
    //query tree
    void query_tree(int i, int j, int index, long long &dp, long long &psum)
    {
        if (root[index].index==-1)
        {
            dp=1;
            psum=0;
            return;
        }
        if(root[index].lazy) {
            root[index].psum+=(root[index].iend-root[index].ibegin+1)*root[index].lazy;
            if (root[index].psum >= modulo)
                root[index].dp=1;
            else
                root[index].dp=(root[index].dp*modular_pow(root[index].dprod,root[index].lazy))%modulo;
            if(root[index].ibegin != root[index].iend) {
                root[index*2].lazy += root[index].lazy;
                root[index*2+1].lazy += root[index].lazy;
            }
            root[index].lazy=0;
        }
        if(root[index].ibegin >= i && root[index].iend <= j) 
        {
            dp=root[index].dp;
            psum=root[index].psum;
            return;
        }
        if (root[index].ibegin > root[index].iend || root[index].ibegin > j || root[index].iend < i)
        {
            dp=1;
            psum=0;
            return;
        }
        if (root[index].ibegin !=root[index].iend)
        {
            long long dp1,dp2,psum1,psum2;
            query_tree(i, j, index*2, dp1,psum1); 
            query_tree(i, j, index*2+1, dp2,psum2);
            psum=psum1+psum2;
            if (psum >= modulo)
                dp=1;
            else
                dp=(dp1*dp2)%modulo;
        }
        else
        {
            dp=1;
            psum=0;
        }
        return;
    };
};
segment_tree_node* segment_tree::root=treeRoot;
int segment_tree::rootsize = (1<<20)+1;


int main(int argc, char **argv)
{
    int n;
    cin >> n;
    vector<long long> d(n);
    vector<long long> a(n);
    vector<long long> p(n);

    int nTimeStart;
    if (argc > 1)
    {
        nTimeStart = GetMilliCount();
    }

    for (int i=0; i<n; i++)
    {
        cin >> a[i];
        cin >> d[i];
        cin >> p[i];
    }

    segment_tree tree(d, p);
    tree.build_tree(n);

    int q;
    cin >> q;
    vector<int> qs(q);
    vector<int> qbegins(q);
    vector<int> qends(q);
    vector<long long> qvs(q);
    vector<long long> dp(q);
    vector<long long> pfact(q);
    long long plargest=0;
    unordered_map<long long, long long> pfactmap;
    pfactmap.reserve(modulo);

    for (int i=0; i<q; i++)
    {
        cin >> qs[i];
        cin >> qbegins[i];
        cin >> qends[i];
        if (qs[i])
        {
            cin >> qvs[i];
            tree.update_tree(qbegins[i], qends[i], qvs[i],1);
        }
        else
        {
            tree.query_tree(qbegins[i], qends[i], 1, dp[i], pfact[i]);
            pfactmap[pfact[i]]=-1;
            if (pfact[i]>plargest)
                plargest=pfact[i];
        }
    }

    long long factmod=1;
    for (long long i=1; i<=min(plargest,modulo-1); i++)
    {
        factmod=(factmod*i)%modulo;
        if (pfactmap.find(i)!=pfactmap.end())
            pfactmap[i]=factmod;
    }
    for (int i=0; i<q; i++)
    {
        if (!qs[i])
        {
            if (pfact[i] < modulo)
                cout << pfact[i] << " " << (dp[i]*pfactmap[pfact[i]])%modulo << endl;
            else
                cout << pfact[i] << " " << 0 << endl;
        }
    }
    if (argc > 1)
    {
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        cout << "Time: " << nTimeElapsed << endl;
    }
}
