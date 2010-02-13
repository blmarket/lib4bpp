#include <iostream>
#include <cstdio>
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

void chomp(string &str)
{
    char tmp = *(str.rbegin());
    if(tmp >= 'a' && tmp <= 'z') return;
    str.resize(size(str)-1);
    chomp(str);
}

int main(void)
{
    string str1,str2;
    char tmp1[200000];
    fgets(tmp1,200000, stdin);
    str1 = tmp1;
    fgets(tmp1,200000,stdin);
    str2 = tmp1;

    chomp(str1); chomp(str2);

    VI arr(size(str2),-1);

    LL ret = 0;

    for(int i=0;i<size(str1);i++)
    {
        char tmp = str1[i];

        for(int j= size(str2)-1;j>=0;j--)
        {
            if(tmp == str2[j])
            {
                if(arr[j-1] != -1)
                {
                    arr[j] = arr[j-1];
                }
            }
        }

        if(tmp == str2[0])
            arr[0] = i;

        if(arr.back() != -1)
        {
            ret += arr.back() + 1;
        }
    }

    cout << ret << endl;
}
