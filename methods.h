#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define INF 1000
#define mp make_pair
#define pb push_back
vector <string> partner;
set <char> trumps;
vector <char> trumpv;
vector <string> my;
map <char, vector<string> > availbids;
pii POINTS;
char TRUMP;
string nextbid;
vector <char> suits;
class hand {
public:
	int hcp,tp;
	bool balanced;
	map <char,pii> suit;
	int range;
	hand() {
		hcp = 0;
		tp = 0;
		range = 0;
		balanced = false;
		suit['C'] = mp(0,13);
		suit['D'] = mp(0,13);
		suit['H'] = mp(0,13);
		suit['S'] = mp(0,13);
	}
};
hand A,B;
bool inRange(int,int,int);
void init();
char sixcardsuit();
void prunespace(string);
char getfourcard(char c);
char getminor(char);
bool balanced(int,int,int,int);
bool perfect();
bool checkfit();
string bid_new_suit();
bool comp(char a,char b);
void possible_trumps();