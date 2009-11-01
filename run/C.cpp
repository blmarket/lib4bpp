#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <vector>

#define mp make_pair
#define pb push_back
#define pmp(x,y) push_back(make_pair(x,y))
#define sqr(x) ((x)*(x))
#define foreach(it,c) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int,int> PII;

template<typename T> int size(const T &a) { return a.size(); }

struct road
{
	template<typename T> road(T s1,int n1,T s2,int n2) : s1(s1),n1(n1),s2(s2),n2(n2) {}	

	string s1,s2;
	int n1,n2;

	bool operator==(const road &a) const
	{
		return s1==a.s1 && s2==a.s2 && n1==a.n1 && n2==a.n2;
	}
};

vector<road> V;
vector<vector<PII> > edge;
map<string,vector<PII> > proh;

void add_edge(int s,int e,int v)
{
	for(int i=0;i<edge[s].size();i++)
	{
		if(edge[s][i].first == e)
		{
			edge[s][i].second += v;
			return;
		}
	}
	edge[s].pmp(e,v);
}

vector<bool> visit;
int try_flow(int s,int e)
{
	if(s==e) return 1;
	if(visit[s]) return 0;
	visit[s]=true;
	for(int i=0;i<edge[s].size();i++)
	{
		int n2,f;
		n2 = edge[s][i].first;
		f = edge[s][i].second;
		if(f==0) continue;
		if(try_flow(n2,e))
		{
//			cout << s << " " << n2 << endl;
			add_edge(s,n2,-1);
			add_edge(n2,s,1);
			return 1;
		}
	}
	return 0;
}

map<string,set<int> > citiesXL;
map<pair<string,int>,int> mapper;

void process(void)
{
	int n,m;
	V.clear();
	scanf("%d %d",&n,&m);
	int nn;
	scanf("%d",&nn);
	proh.clear();
	citiesXL.clear();
	for(int i=0;i<nn;i++)
	{
		char s1[30],s2[30];
		char s3[30],s4[30];
		int n1,n2=0;
		scanf("%s %s %s %s",s1,s3,s2,s4);
		istringstream(s3) >> n1;
		istringstream(s4) >> n2;
		citiesXL[s1].insert(n1);
		citiesXL[s2].insert(n2);
		V.pb(road(s1,n1,s2,n2));
	}
	int mm;
	scanf("%d",&mm);
	for(int i=0;i<mm;i++)
	{
		char s1[30];
		int n1,n2;
		scanf("%s %d %d",s1,&n1,&n2);
		proh[s1].pb(mp(n1,n2));
		citiesXL[s1].insert(n1);
		citiesXL[s1].insert(n2);
	}

	edge.clear();
	int ppp=2;
	int flow=0;


	for(int days=0;days<10000;days++)
	{
		foreach(it,citiesXL)
		{
			edge.resize(ppp+5);
			if(it->first == "algospot")
			{
				add_edge(0,ppp,9999);
			}
			else if(it->first == "run")
			{
				add_edge(ppp,1,9999);
			}
			mapper[mp(it->first,*(it->second.begin()) + days*3000)]=ppp++;

			foreach(jt,it->second)
			{
				set<int>::iterator jjt = jt;
				++jjt;
				edge.resize(ppp+5);
				edge[ppp-1].pmp(ppp,1);
				if(it->first == "algospot")
					add_edge(0,ppp,9999);
				else if(it->first == "run")
					add_edge(ppp,1,9999);
				mapper[mp(it->first,*jjt + days*3000)] = ppp++;

				if(jjt == it->second.end()) break;
			}

			const vector<PII> &vec = proh[it->first];

			for(int i=0;i<vec.size();i++)
			{
				int idx1 = mapper[mp(it->first,vec[i].first + days*3000)];
				int idx2 = mapper[mp(it->first,vec[i].second + days*3000)];
				for(int j=idx1;j<idx2;j++)
				{
					add_edge(j,j+1,-1);
				}
			}
		}

		for(int i=0;i<V.size();i++)
		{
			int idx1 = mapper[mp(V[i].s1,V[i].n1 + days*3000)];
			int idx2 = mapper[mp(V[i].s2,V[i].n2 + days*3000)];
			add_edge(idx1,idx2,1);
		}

		edge.resize(ppp);


//	foreach(iter, mapper)
//	{
//		cout << iter->first.first << " " << iter->first.second << " : ";
//		for(int i=0;i<edge[iter->second].size();i++)
//		{
//			cout << edge[iter->second][i].first << "," << edge[iter->second][i].second << " ";
//		}
//		cout << endl;
//	}

		while(flow < m)
		{
			visit = vector<bool>(edge.size(),false);
			if(try_flow(0,1) == 0)
			{
				break;
			}
			flow++;
		}
		if(flow == m)
		{
			cout << days+1 << endl;
			return;
		}
	}

//	cout << "flow = " << ret << endl;

	cout << -1 << endl;
	return;
}

int main(void)
{
    int N;
	scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        process();
    }
}

