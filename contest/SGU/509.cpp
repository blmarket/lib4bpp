#include <iostream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#include <vector>

#define mp make_pair
#define pb push_back
#define sqr(x) ((x)*(x))
#define foreach(it,c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef long long LL;

template<typename T> int size(const T &a) { return a.size(); } 

inline LL modrange(LL a, LL sz)
{
    return ((a%sz)+sz)%sz;
}

int n;
LL L;
LL T;

struct data
{
    data(int name, int pos, int color) : name(name), pos(pos), color(color) {}
    int name, pos, color;

    LL endpos(int cc, LL tt)
    {
        return modrange(tt*cc + pos, L);
    }

    bool operator<(const data &a) const
    {
        return pos < a.pos;
    }
};

vector<data> cl,rl;

inline LL modd(LL a)
{
    LL tmp = (((a%L)+L)%L);
    if(tmp == 0) return L; else return tmp;
}

LL sum1(int pos,LL x)
{
    LL ret = 0;

    if( (x / size(cl)) > (T/L)+1 ) return T+1;

    ret += (x / size(cl)) * L;
    x %= size(cl);

    while(x)
    {
        int npos = (pos + size(cl) -1 ) % size(cl);
        LL tmp = modd(cl[pos].pos - cl[npos].pos);
        ret += tmp;
        pos = npos;
        x--;
    }

    return ret;
}

LL sum2(int pos,LL x)
{
    LL ret = 0;
    if( (x / size(rl)) > (T/L) + 1) return T+1;

    ret += (x / size(rl)) * L;
    x %= size(rl);

    while(x)
    {
        int npos = (pos + 1) % size(rl);
        LL tmp = modd(rl[npos].pos - rl[pos].pos);
        ret += tmp;
        pos = npos;
        x--;
    }

    return ret;
}

vector<int> spos;
vector<data> epos;

int main(void)
{
    scanf("%d",&n);
    scanf("%d",&L);
    for(int i=0;i<n;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(c>0)
        {
            cl.pb(data(i,a,b));
        }
        else
        {
            rl.pb(data(i,a,b));
        }
    }
    cin >> T;

    T*=2;

    sort(cl.begin(),cl.end());
    sort(rl.begin(),rl.end());

    if(size(cl))
    {
        for(int i=0;i<size(rl);i++)
        {
            LL pos = modd(rl[i].pos - T);
            int idx = upper_bound(cl.begin(), cl.end(), data(-1,pos,-1)) - cl.begin();
            if(idx == size(cl)) idx = 0;

            if(modd(rl[i].pos - cl[idx].pos) > T) continue;
            rl[i].color = cl[idx].color;
        }
    }

    for(int i=0;i<size(cl);i++)
    {
        spos.pb(cl[i].pos);
        epos.pb(data(1, cl[i].endpos(1,T/2), cl[i].color));
    }

    for(int i=0;i<size(rl);i++)
    {
        spos.pb(rl[i].pos);
        epos.pb(data(-1, rl[i].endpos(-1,T/2), rl[i].color));
    }

    sort(spos.begin(), spos.end());
    sort(epos.begin(), epos.end());

    vector<string> ret(n);

    if(size(cl) == 0 || size(rl) == 0)
    {
        for(int i=0;i<size(cl);i++)
        {
            ostringstream ost;
            ost << cl[i].endpos(1,T/2) << ".000 " << cl[i].color << " 1";
            ret[cl[i].name] = ost.str();
        }
        for(int i=0;i<size(rl);i++)
        {
            ostringstream ost;
            ost << rl[i].endpos(-1,T/2) << ".000 " << rl[i].color << " -1";
            ret[rl[i].name] = ost.str();
        }

        for(int i=0;i<size(ret);i++)
            printf("%s\n",ret[i].c_str());
        return 0;
    }

    int sp = cl[0].pos;
    int ep;
    {
        int pos = 0, rpos = (upper_bound(rl.begin(), rl.end(), data(-1,cl[0].pos, -1) ) - rl.begin());
        if(rpos == size(rl)) rpos = 0;

        LL diff1 = modd(rl[rpos].pos - cl[pos].pos);
        LL tmp1 = T - diff1;

        if(tmp1 < 0)
        {
            ep = cl[pos].endpos(1, T/2);
        }
        else
        {
            LL xs = 0, xe = T;
            while(xs + 1 < xe)
            {
                LL mid = (xs+xe+1)/2;
                if(sum1(pos, mid) + sum2(rpos, mid) > tmp1)
                    xe = mid;
                else
                    xs = mid;
            }

            if(sum1(pos,xs+1) + sum2(rpos,xs) < tmp1)
            {
                ep = cl[modrange(- xs + pos - 1, size(cl))].endpos(1, T/2);
            }
            else
            {
                ep = rl[modrange(xs+rpos, size(rl))].endpos(-1, T/2);
            }
        }
    }

    int spidx = lower_bound(spos.begin(), spos.end(), sp) - spos.begin();
    int epidx = lower_bound(epos.begin(), epos.end(), data(0,ep,0) ) - epos.begin();

    int idxdiff = epidx - spidx;

    char tmpstr[10000];
    for(int i=0;i<size(cl);i++)
    {
        int pos = lower_bound(spos.begin(), spos.end(), cl[i].pos) - spos.begin();
        int np = modrange(pos + idxdiff, size(epos));
        sprintf(tmpstr, "%d.000 %d %d",epos[np].pos , epos[np].color, epos[np].name);

        ret[cl[i].name] = tmpstr;
    }
    for(int i=0;i<size(rl);i++)
    {
        int pos = lower_bound(spos.begin(), spos.end(), rl[i].pos) - spos.begin();
        int np = modrange(pos + idxdiff, size(epos));
        sprintf(tmpstr,"%d.000 %d %d",epos[np].pos, epos[np].color, epos[np].name);

        ret[rl[i].name] = tmpstr;
    }

    for(int i=0;i<size(ret);i++)
        printf("%s\n",ret[i].c_str());
    return 0;
}
