#include <bits/stdc++.h>
#include "methods.h"
using namespace std;

bool inRange(int a,int b,int c) {
	if(a>=b && a<=c)
		return true;
	return false;
}
void init() {
	suits.pb('H');suits.pb('S');suits.pb('D');suits.pb('C');
	string l;
	for(int i=1;i<8;i++) {
		l = to_string(i);
		availbids['C'].pb(l+'C');
		availbids['D'].pb(l+'D');
		availbids['H'].pb(l+'H');
		availbids['S'].pb(l+'S');
	}	
}
char sixcardsuit() {
	for(int i=0;i<4;i++) {
		if(A.suit[suits[i]].first >= 6)
			return suits[i];
	}
	return 'N';
}
//NEEDS LOT OF IMPROVEMENT 
void prunespace(string b) {
	if(b[1] == 'N') {
		char d = b[0];
		for(int i=0;i<4;i++) {
			for(auto it = availbids[suits[i]].begin();it != availbids[suits[i]].end();it++) {
				string s = *it;
				if(s[0] <= d) {
					//cout<<s<<endl;
					availbids[suits[i]].erase(it);
				}
			} 
		}
	}
	else {
		for(int i=0;i<4;i++) {
			for(auto it = availbids[suits[i]].begin();it != availbids[suits[i]].end();it++) {
				if(*it <= b)
					availbids[suits[i]].erase(it);
			} 
		}
	}
}
char getfourcard(char c) {
	for(int i=0;i<4;i++) {
		if(A.suit[suits[i]].first >= 6 && c == suits[i])
			return suits[i];
		else if(A.suit[suits[i]].first >= 4 && c != suits[i])
			return suits[i];
	}	
	return 'N';
}
char getminor(char c) {
	if(c!='C')
		return 'C';
	if(c!='D')
		return 'D';
	if(c!='H')
		return 'H';
	return 'N';
}
bool balanced(int a,int b,int c,int d) {
	vector <int> v(4);
	v[0] = a;v[1] = b;v[2] = c;v[3] = d;
	sort(v.begin(),v.end());
	if(v[0]==3&&v[1]==3&&v[2]==3&&v[3]==4)
		return true;
	if(v[0]==2&&v[1]==3&&v[2]==4&&v[3]==4)
		return true;
	if(v[0]==2&&v[1]==3&&v[2]==3&&v[3]==5)
		return true;
	return false;
}
bool perfect(hand A) {
	int a[4];
	a[0] = A.suit['C'].first;
	a[1] = A.suit['D'].first;
	a[2] = A.suit['H'].first;
	a[3] = A.suit['S'].first;
	sort(a,a+4);
	if(a[0]==3 && a[1]==3 && a[2]==3 && a[3]==4)
		return true;
	return false;
}
bool checkfit(string a) {
	if(A.suit[a[1]].first+B.suit[a[1]].first >= 8)
		return true;
	return false;
}
string bid_new_suit(char a,char b,char c) {
	if(A.suit['S'].first >= 2 && b!='S' && c!='S')
		return availbids['S'][0];
	if(A.suit['H'].first >= 2 && b!='H' && c!='H')
		return availbids['H'][0];
	if(A.suit['D'].first >= 2 && b!='D' && c!='D')
		return availbids['D'][0];
	if(A.suit['C'].first >= 2 && b!='C' && c!='C')
		return availbids['C'][0];
	return "2N";
}
bool comp(char a,char b) {
	if((A.suit[a].first+B.suit[b].first) == (A.suit[a].first+B.suit[b].first))
		return (A.suit[a].second+B.suit[b].second) > (A.suit[a].second+B.suit[b].second);
	return (A.suit[a].first+B.suit[b].first) > (A.suit[a].first+B.suit[b].first);
}
void possible_trumps() {
	char doom[4] = {'S','H','D','C'};
	sort(doom,doom+4,comp);
	vector <char> temp;
	if(A.balanced && B.balanced) {
		if(availbids['S'][0][0] < '4')
			temp.pb('N');
		if(A.suit['H'].first >= 5 && (A.suit['H'].second+B.suit['H'].second) >= 8)
			temp.pb('H');
		if(A.suit['S'].first >= 5 && (A.suit['S'].second+B.suit['S'].second) >= 8) 
			temp.pb('S');
		if(A.suit['H'].first == 4 && inRange(POINTS.first,23,INF) && !perfect(A) && (A.suit['H'].second+B.suit['H'].second) >= 8)
			temp.pb('H');
		if(A.suit['S'].first == 4 && inRange(POINTS.first,23,INF) && !perfect(A) && (A.suit['S'].second+B.suit['S'].second) >= 8)
			temp.pb('S');
	}
	else if(A.balanced || B.balanced) {
		if(availbids['S'][0][0] < 4)
			temp.pb('N');
		for(int i=0;i<2;i++) {
			if((A.suit[doom[i]].second+B.suit[doom[i]].second) >= 8)
				temp.pb(doom[i]);
		}
	}
	else {
		for(int i=0;i<2;i++) {
			if((A.suit[doom[i]].second+B.suit[doom[i]].second) >= 8)
				temp.pb(doom[i]);	
		}
	}
	if(temp[0]=='C' || temp[0]=='D')
		temp.pb('N');
	trumpv = temp;
}