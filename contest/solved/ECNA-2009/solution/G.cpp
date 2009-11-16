#include <iostream>
using namespace std;

/*
IDEA: associate startup times and wait times at lights with paths leading
away from vertices.  Must be careful to distinguish this added on time with
true arrival time at vertices.
*/

const int MAXVERT = 100;
const int STARTUPTIME = 5;
const long INF = 10000000;

struct edge {
	int time;
	int end;
};

struct light
{
	int g, y, r;
	int cycleTime;		// convenience
	int goTime;			// convenience
	int start;			// may be used later
	edge adj[MAXVERT];
	int nadj;
	long dist;			// arrival time plus wait time for light + startup time when leaving light
	long arrival;		// actual time of arrival at the light
	bool visited;
} lights[MAXVERT];

int timeToGo(int light, int t)
{
	int go = t%lights[light].cycleTime;
	if (go < lights[light].goTime)
		return 0;
	else
		return lights[light].cycleTime - go + STARTUPTIME;
}

int calcDist(edge e, int t)
{
	int dist = t+e.time;
	return dist + timeToGo(e.end, dist);
}

int getNextVertex(int n)
{
	int ans = -1;
	int closest = INF;
	for(int i=0; i<n; i++) {
		if (!lights[i].visited && lights[i].dist < closest) {
			ans = i;
			closest = lights[i].dist;
		}
	}
	return ans;
}

int solve(int n, int endLight)
{
	while (true) {
		int index = getNextVertex(n);
		if (index == endLight)
			return lights[index].arrival;
		if (index == -1)
			return INF;
		lights[index].visited = true;
		for(int i=0; i<lights[index].nadj; i++) {
			edge e = lights[index].adj[i];
			if (lights[e.end].visited)
				continue;
			int edgeDist = calcDist(e, lights[index].dist);
			if (lights[e.end].dist > edgeDist ||
			    (lights[e.end].dist == edgeDist && lights[e.end].arrival > lights[index].dist+e.time) ||
			    (e.end == endLight && lights[e.end].arrival > lights[index].dist+e.time)) {
				lights[e.end].dist = edgeDist;
				if (lights[e.end].arrival > lights[index].dist + e.time)
					lights[e.end].arrival = lights[index].dist + e.time;
			}
		}
	}
	return 0;
}

void outputAns(int ans)
{
	int mins = ans/60;
	int secs = ans%60;
	cout << mins << ":";
	if (secs < 10)
		cout << '0';
	cout << secs << endl;
}

int main()
{
	int n, m, s, e;
	int i;
	cin >> n >> m >> s >> e;
	while (n != 0) {
		for(i=0; i<n; i++) {
			cin >> lights[i].g >> lights[i].y >> lights[i].r;
			lights[i].cycleTime = lights[i].g+lights[i].y+lights[i].r;
			lights[i].goTime = lights[i].g+lights[i].y;
			lights[i].dist = INF;
			lights[i].arrival = INF;
			lights[i].visited = false;
			lights[i].nadj = 0;
		}
		for(i=0; i<m; i++) {
			int l1, l2, time;
			cin >> l1 >> l2 >> time;
			lights[l1].adj[lights[l1].nadj].end = l2;
			lights[l1].adj[lights[l1].nadj].time = time;
			lights[l1].nadj++;
			lights[l2].adj[lights[l2].nadj].end = l1;
			lights[l2].adj[lights[l2].nadj].time = time;
			lights[l2].nadj++;
		}
		lights[s].dist = STARTUPTIME;
		lights[s].arrival = 0;
		int ans = solve(n, e);
		outputAns(ans);

		cin >> n >> m >> s >> e;
	}
}
