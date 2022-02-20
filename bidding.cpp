#include <bits/stdc++.h>
using namespace std;

// • opening bid------>1
// • passable bid------>2
// • invitational bid------>3
// • sign-off bid------>4
// • asking bid (by default this is forcing)------>5
// • response bid (to an asking bid)------>6
// • cue bid------>7
// • descriptive bid------>8

class hand {
public:
	int hcp,dp;
	int s,h,d,c;
	hand() {
		hcp=0;dp=0;
		s=0;h=0;d=0;c=0;
	}
};
class data {
public:
	int hcp,dp;
	char type;
}
hand A();
hand B();
map <char,int> _rank;
set <char> zone = {'p','g','s','S'};
void assign() {
	for(int i=2;i<11;i++)
		_rank['0'+i] = i;
	_rank['J'] = 11;
	_rank['Q'] = 12;
	_rank['K'] = 13;
	_rank['A'] = 14;
}
int HCP(vector <char> cards[4]) {
	int ans = 0;
	int temp;
	for(int i=0;i<4;i++) {
		for(int j=0;j<cards[i].size();j++) {
			temp = _rank[cards[i][j]]-10;
			if(temp > 0)
				ans+=temp;
		}
	}
	return ans;
}
int DP(vector <char> cards[4]) {
	int dp=0;
	for(int i=0;i<4;i++)
		if(cards[i].size()<3)
			dp+=3-cards[i].size();
	return dp;
}
void input_hand() {
	string card;
	vector <char> cards[4];
	for(int i=0;i<13;i++) {
		cin>>card;
		switch(card[1]) {
			case 'S':
				A.s++;
				cards[0].push_back(card[0]);
				break;
			case 'H':
				A.h++;
				cards[1].push_back(card[0]);
				break;
			case 'D':
				A.d++;
				cards[2].push_back(card[0]);
				break;
			case 'C':
				A.c++;
				cards[3].push_back(card[0]);
				break;
			default: cout<<"suit error\n";
		}
	}
	A.hcp = HCP(cards);
	A.dp = DP(cards);
}
int certain(data D,hand A) {
	
}
data getData(string seq) {			//retrieves data from tree

}
void updateHand(data D) {		//updates hand based on data retrieved
	B.hcp = D.hcp;
	B.dp = B.dp;	
}
bool checkGame() {
	if(A.hcp+A.dp+B.hcp+B.dp >= 25) {
		return true;
	}
}
bool checkSlam() {
	if(A.hcp+B.hcp >= 31) {
		return true;
	}
}
string getResponse(string seq,int t) {
	if(t==1) {
		return openbid();
	}
	if(t==2) {
		return "p";
	}
	if(t==3) {
		if(A.hcp()>10 && A.hcp()<12) {
			return "3nt";	
		}
	}
	if(t==4) {

	}
	if(t==5) {

	}
	if(t==7) {

	}
}
string nextbid(string seq) {
	data D = getData(seq);
	updateHand(D);
	checkGame();
	checkSlam();
	vector <string> child = getChild(seq);
	int minval = 0;
	if(D.type == 6 || D.type == 8) {
		for(string s : child) {
			data temp = getData(seq+" "+s);
			certain(temp,A);
		}
	}
	else {
		return getResponse(seq,type);
	}
}
vector <string> getChild(string seq) {		//returns all possible bids for a sequence
	
}
int main() {
	assign();
	cout<<"input hand:"<<endl;
	input_hand();
	string bidseq;
	cin>>bidseq;
	cout<<nextbid(bidseq)<<endl;
	return 0;
}