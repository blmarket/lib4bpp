#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

#define pb push_back

using namespace std;

namespace util
{
    string bit2string(int candidate,int size)
    {
        ostringstream ost;
        for(int i=0;i<size;i++)
            ost << ((candidate & (1<<i)) != 0) << " ";
        return ost.str();
    }
}

class nemonemorow
{
private:
    int ncheck, nX;
public:
    int check, X;
    int size;
    vector<int> state;

    nemonemorow(int size) : size(size), check(0), X(0) {}

    string tostring(void)
    {
        return util::bit2string(check,size);
    }

    string bit2string(int num)
    {
        return util::bit2string(num,size);
    }

    string bit2string(int num,int s)
    {
        return util::bit2string(num,s);
    }

    bool validate(int candidate)
    {
        if((candidate & check) != check) return false;
        if((~candidate & X) != X) return false;
        int cur = 0;
        vector<int> tmp;
        for(int i=0;i<size;i++)
        {
            if(candidate & (1<<i))
                cur++;
            else
            {
                if(cur != 0) tmp.pb(cur);
                cur = 0;
            }
        }
        if(cur != 0) tmp.pb(cur);
        if(tmp != state) return false;

//        cout << "candidate : " << bit2string(candidate) << endl;

        ncheck &= candidate;
        nX |= candidate;
        return true;
    }

    bool place(int a,int pos,int current)
    {
        bool ret = false;
        if(a == state.size()) { return validate(current); }
        for(int i=pos;i<=(int)size - state[a];i++)
        {
            int tmp = current;
            for(int j=i;j<i+state[a];j++)
                tmp |= (1<<j);
            ret |= place(a+1,i + state[a] + 1, tmp);
        }
        return ret;
    }

    bool doit(void)
    {
        bool ret = false;
        ncheck = (1<<size)-1;
        nX = 0;
        if(place(0,0,0))
        {
            if(ncheck != check)
            {
                check = ncheck;
                ret = true;
            }
            if(~nX != X)
            {
                X = ~nX;
                ret = true;
            }
        }
    }

    static void test(void)
    {
        nemonemorow aa(15);
        aa.check = 0; aa.X = 0;
        for(int i=0;i<rand()%5;i++)
            aa.state.pb(rand()%10);
        aa.doit();
    }
};

int board[30];
vector<nemonemorow> row;
vector<nemonemorow> col;

int main(void)
{
    int n;
    string str;
    getline(cin,str);
    istringstream(str) >> n;
    row.resize(n,nemonemorow(n));
    col.resize(n,nemonemorow(n));
    for(int i=0;i<n*2;i++)
    {
        getline(cin,str);
        istringstream sin(str);

        nemonemorow &target = ((i>=n)?col[i-n]:row[i]);

        int num;
        while(sin >> num)
        {
            if(num != 0)
                target.state.pb(num);
        }
    }

    for(int i=0;i<10;i++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(col[j].check & (1<<i)) row[i].check |= (1<<j);
                if(col[j].X & (1<<i)) row[i].X |= (1<<j);
            }
            row[i].doit();
        }

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(row[i].check & (1<<j)) cout << "# ";
                else if(row[i].X & (1<<j)) cout << ". ";
                else cout << ". ";
            }
            cout << endl;
        }
        cout << endl;

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(row[j].check & (1<<i)) col[i].check |= (1<<j);
                if(row[j].X & (1<<i)) col[i].X |= (1<<j);
            }
            col[i].doit();
        }
    }
}
