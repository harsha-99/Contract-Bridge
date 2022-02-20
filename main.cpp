#include <bits/stdc++.h>
#include "responder.h"
#include "opener.h"
using namespace std;

void play_opener() {
	POINTS.first = A.tp;
	POINTS.second = A.tp;
	opener O;
	cout<<"bid: ";
	if(partner.size()==0) {
		nextbid = O.openbid();
		prunespace(nextbid);
		cout<<nextbid<<"; ";
	}
	else if(partner.size()==1) {
		inference2(my[0],partner[0]);
		prunespace(partner[0]);
		if(my[0] == "1N" && partner[0] == "2C") 
			nextbid = O.staymanrebid();
		else if(my[0] == "1N" && (partner[0] == "2D" || partner[0] == "2H"))
			nextbid = O.jacobyrebid();
		else
			nextbid = O.rebid();
		cout<<nextbid<<"; ";
		prunespace(nextbid);
		outputdata1();
	}
}
void play_responder() {
	POINTS.first = A.hcp;
	POINTS.second = A.hcp;
	inference1(partner[0]);
	responder R;
	if(partner.size()==1) {
		prunespace(partner[0]);
		cout<<"bid: ";
		if(partner[0] == "1N")
			nextbid = R.firstbidnot();
		else
			nextbid = R.firstbidsuit();
		cout<<nextbid<<"; ";
		prunespace(nextbid);
		possible_trumps();
		outputdata2();
	}
	if(partner.size()==2) {
		prunespace(partner[1]);
		inference3(partner[0],my[0],partner[1]);
		cout<<"bid: ";
		if(partner[0] == "1N") {
			if(my[0] == "2C") 
				nextbid = R.staymanrebid();
			else if(my[0] == "2D" || my[0] == "2H")
				nextbid = R.jacobyrebid();
		}
		else
			nextbid = R.rebid();
		cout<<nextbid<<"; ";
		prunespace(nextbid);
		possible_trumps();
		outputdata2();
	}
}
int main() {
	init();
	cout<<"enter hand:\n";
	string cd;
	vector <char> cards[4];
	map <int,char> idx;
	map <char,int> rank;
	rank['A'] = 4;rank['K'] = 3;rank['Q'] = 2;rank['J'] = 1;
	idx[0] = 'S';idx[1] = 'H';idx[2] = 'D';idx[3] = 'C';
	for(int i=0;i<4;i++) {
		getline(cin,cd);
		stringstream s(cd);
		char sc;
		while(s >> sc) {
			cards[i].push_back(sc);
			A.suit[idx[i]].first++;
			A.suit[idx[i]].second++;
			A.hcp+=rank[sc];
		}
		if(cards[i].size()<3)
			A.tp+=3-cards[i].size();
	}
	A.tp+=A.hcp;
	A.balanced = balanced(A.suit['S'].first,A.suit['H'].first,A.suit['D'].first,A.suit['C'].first);
	cout<<"enter sequence:\n";
	int j = 0;
	getline(cin,cd);
	stringstream s(cd);
	string ss;	
	while(s>>ss) {
		if(j&1)
			my.pb(ss);
		else
			partner.pb(ss);
		j++;
	}
	if(j%2 == 0)
		play_opener();
	else
		play_responder();
	return 0;
}