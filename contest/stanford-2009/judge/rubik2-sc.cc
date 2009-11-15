// --------------------------------------------------------------------------
// SLPC2009 - Rubik 2^3 solution, verifier, and generator all-in-one :)
// Run "rubik2 < (input)" to solve, "rubik2 -g" to generate tests, or
//     "rubik2 (output) < (input)" to verify output against input
// 
// Author:  Sonny Chan
// Date:    September 29, 2009
// --------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctime>

using namespace std;

int g_wrap[][8] = {
    { -1, -1,  0,  1, -1, -1, -1, -1 },
    { -1, -1,  3,  2, -1, -1, -1, -1 },
    {  4,  5,  8,  9, 12, 13, 16, 17 },
    {  7,  6, 11, 10, 15, 14, 19, 18 },
    { -1, -1, 20, 21, -1, -1, -1, -1 },
    { -1, -1, 23, 22, -1, -1, -1, -1 }
};

int g_turn[3][24] = {
    { 0, 19, 16, 3, 4, 5, 6, 7, 8, 1, 2, 11, 13, 14, 15, 12, 22, 17, 18, 21, 20, 9, 10, 23 },
    { 1, 2, 3, 0, 16, 17, 6, 7, 4, 5, 10, 11, 8, 9, 14, 15, 12, 13, 18, 19, 20, 21, 22, 23 },
    { 0, 1, 15, 12, 4, 2, 3, 7, 9, 10, 11, 8, 21, 13, 14, 20, 16, 17, 18, 19, 5, 6, 22, 23 }
};

const string g_moves[] = { "X", "Y", "Z", "XXX", "YYY", "ZZZ"};
const string g_base[2] = {
    "WWWWBBBBOOOOGGGGRRRRYYYY",
    "RRRRGGGGBBBBYYYYWWWWOOOO"
};
const string g_dots = "........................";

const int g_mode = 3;   // can also do a branch factor 6 search, but it's slower

set<string> g_seen;

// function to convert an internal representation into a "wrapper map"
void output(const string &s, ostream &stream)
{
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (g_wrap[i][j] >= 0) stream << s[g_wrap[i][j]];
            else stream << '.';
        }
        stream << endl;
    }
}

string transform(int turn, const string &s)
{
    // apply the permutation on the tiles from s to form new ordering t
    string t = g_dots;
    if (turn < 3)
        for (int i = 0; i < 24; ++i) t[i] = s[g_turn[turn][i]];
    else
        for (int i = 0; i < 24; ++i) t[g_turn[turn-3][i]] = s[i];
    return t;
}

bool solved(const string &s)
{
    // check that each of the six faces have all matching colours
    for (int i = 0; i < 6; ++i) {
        int j = i*4;
        char colour = s[j];
        for (++j; j < (i+1)*4; ++j)
            if (s[j] != colour) return false;
    }
    return true;
}

string scramble(string s, int steps = 42)
{
    for (int i = 0; i < steps; ++i)
        s = transform(rand()%6, s);
    return s;
}

bool bdfs(int depth, int limit, const string &s, string moves)
{
    // cache the configuration so we don't search it more than once
    if (g_seen.find(s) != g_seen.end()) return false;
    g_seen.insert(s);
    
    // hooray!
    if (solved(s)) {
        cout << moves << endl;
        return true;
    }
    
    // recurse, transforming the cube and deeping the level
    if (depth < limit) {
        int m = rand() % g_mode;
        for (int i = 0; i < g_mode; ++i, m = (m+1)%g_mode)
            if (bdfs(depth+1, limit, transform(m, s), moves+g_moves[m]))
                return true;
    }
    
    return false;
}

string readconfig(istream &in)
{
    // read in the map and create an initial configuration from it
    string input, config = g_dots;
    for (int i = 0; i < 6; ++i) {
        in >> input;
        for (int j = 0; j < 8; ++j)
            if (g_wrap[i][j] >= 0) config[g_wrap[i][j]] = input[j];
    }
    return config;
}

int main(int argc, char *argv[])
{
    istream &in = cin;
    srand(time(0));
    
    if (argc < 2)   // solve the problem
    {
        for (;;)
        {
            // read and check for sentinel
            string initial = readconfig(in);            
            if (initial == g_dots) break;
            
            // perform a bounded depth-first search until we're done
            for (int d = 1; ; ++d) {
                g_seen.clear();
                if (bdfs(0, d, initial, "")) break;
                //cout << "depth " << d << " - configurations searched: " << g_seen.size() << endl;
            }
        }
    }
    else
    {
        // generate random test data
        if (string(argv[1]) == "-g") {
            for (int i = 0; i < 7; ++i) {
                string config = (i == 4) ? g_base[1] : scramble(g_base[i&1], i*i+1);
                output(config, cout);
                cout << endl;
            }
            output(g_dots, cout);
        }
        // assume argument is name of output file to verify
        else {
            ifstream file(argv[1]);
            if (file)
            {
                for (int test = 1; ; ++test)
                {
                    // read and check for sentinel
                    string config = readconfig(in);
                    if (config == g_dots) break;
                    
                    // read moves
                    string moves;
                    getline(file, moves);
                    
                    // interpret moves
                    for (string::iterator it = moves.begin(); it != moves.end(); ++it)
                    {
                        // check for valid character
                        if (*it < 'X' || *it > 'Z') {
                            cout << "FAILED - invalid move: " << *it << endl;
                            return -1;
                        }
                        config = transform(*it - 'X', config);
                    }
                    
                    if (solved(config))
                        cout << "PASSED test case #" << test << endl;
                    else {
                        cout << "FAILED test case #" << test << endl;
                        return -1;
                    }
                }                
            }
            else cerr << "Could not open output file for verification!" << endl;
        }
    }
    
    return 0;
}

