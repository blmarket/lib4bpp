#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool check_solved(const vector<string> &board) {
	int checks[6][2] = { {0,2}, {2,0}, {2,2}, {2,4}, {2,6}, {4,2} };

	const vector<string> &b = board;

	for(int i=0; i<6; i++) {
		for(int j=0; j<2; j++) {
			for(int k=0; k<2; k++) {
				if(b[checks[i][0]][checks[i][1]] != b[checks[i][0] + j][checks[i][1] + k])
					return false;
			}
		}
	}

	return true;
}

vector<string> spin(const int xyz, const vector<string> &board) {
	int spins[3][3][4][2] = {
		// spin X
		{ { {0,3}, {2,3}, {4,3}, {3,6} },
		  { {1,3}, {3,3}, {5,3}, {2,6} },
		  { {2,4}, {3,4}, {3,5}, {2,5} }
		},
		// spin Y
		{ { {2,0}, {2,2}, {2,4}, {2,6} },
		  { {2,1}, {2,3}, {2,5}, {2,7} },
		  { {0,2}, {1,2}, {1,3}, {0,3} }
		},
		// spin Z
		{ { {2,2}, {3,2}, {3,3}, {2,3} },
		  { {1,2}, {3,1}, {4,3}, {2,4} },
		  { {1,3}, {2,1}, {4,2}, {3,4} }
		}
	};

	vector<string> b = board;

	for(int i=0; i<3; i++) {
		char save = b[spins[xyz][i][3][0]][spins[xyz][i][3][1]];

		for(int j=3; j; j--)
			b[spins[xyz][i][j][0]][spins[xyz][i][j][1]] = b[spins[xyz][i][j-1][0]][spins[xyz][i][j-1][1]];

		b[spins[xyz][i][0][0]][spins[xyz][i][0][1]] = save;
	}

	return b;
}

int main() {
	while(true) {
		vector<string> board(6);
		for(int i=0; i<6; i++)
			cin >> board[i];
            
        if (board[4][2] == '.') break;

		if(check_solved(board)) {
			cout << endl;
			continue;
		}

		map< vector<string>, string > solutions;
		queue< vector<string> > boards;

		solutions[board] = "";
		boards.push(board);

		bool solved = false;
		while(!boards.empty()) {
			const vector<string> &b = boards.front();

			for(int i=0; i<3; i++) {
				string codes = "XYZ";

				vector<string> test = spin(i, b);

				if(check_solved(test)) {
					cout << solutions[b] + codes[i] << endl;
					solved = true;
					break;
				}

				if(solutions.find(test) == solutions.end()) {
					solutions[test] = solutions[b] + codes[i];
					boards.push(test);
				}
			}

			boards.pop();

			if(solved)
				break;
		}
	}

	return 0;
}
