#include <iostream>
using namespace std;

struct window {
	int x, y;
	int w, h;
	int num;
	window *next;
} *list;

bool inside(int x, int y, int left, int bottom, int right, int top)
{
	return (x >=left && x <= right && y >= bottom && y <= top);
}

int findWin(int x, int y, window* list)
{
	for(window *p=list; p != 0; p=p->next) {
		if (inside(x, y, p->x, p->y, p->x+p->h-1, p->y+p->w-1))
			return p->num;
	}
	return 0;
}

void deleteList(window *list)
{
	window *p = list;
	while (p!=0) {
		window *pnext = p->next;
		delete p;
		p = p->next;
	}
}

int main()
{
	int icase=0;
	int n, m;
	cin >> n;
	while (n != 0) {
		icase++;
		list = 0;
		cout << "Desktop " << icase << ":"<<endl;
		for(int i=1; i<=n; i++) {
			window *win = new window;
			cin >> win->x >> win->y >> win->w >> win->h;
			win->num = i;
			win->next = list;
			list = win;
		}
		cin >> m;
		for(int i=0; i<m; i++) {
			int x, y;
			cin >> x >> y;
			int win = findWin(x, y, list);
			if (win > 0) 
				cout << "window " << win << endl;
			else
				cout << "background" << endl;
		}
		deleteList(list);

		cin >> n;
	}
}
