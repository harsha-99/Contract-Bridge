#include <bits/stdc++.h>
using namespace std;

class cashing {
public:
	vector<pair<int,int> > north[4];
	vector<pair<int,int> > south[4];
	vector<pair<int,int> > played;
	int leadSuit = -1;
	int finishCount = 0;
	void input();
	void rank();
	void findcard(bool,bool);
};
bool compare(const pair<int,int> &a,const pair<int,int> &b){
	return a.first>b.first;
}
void cashing::findcard(bool side,bool level) {
	if(finishCount>=2)
		return;
	if(side) {
		if(leadSuit!=-1 && north[leadSuit].size()) {
			if(level) {
				played.push_back(north[leadSuit][0]);
				north[leadSuit].erase(north[leadSuit].begin());
				leadSuit = -1;
				findcard(true,true);
			}
			else {
				//condition to check if this is rank1 card
				pair <int,int> pp = north[leadSuit].back();
				pair <int,int> dd = played.back();
				north[leadSuit].pop_back();
				leadSuit = -1;
				played.push_back(pp);
				if(pp.second == 1) {
					if(pp.first > dd.first)
						findcard(true,true);
					else
						findcard(false,true);
				}
			}
		}
		else if(leadSuit!=-1) {
			int max = -10000;
			int card;	
			if(level) {
				for(int i=0;i<4;i++) {
					if(north[i].size()+south[i].size() > max && north[i][0].second==1) {
						card = i; 
						max = north[i].size()+south[i].size();
					}
				}
				played.push_back(north[leadSuit][0]);
				north[leadSuit].erase(north[leadSuit].begin());
				if(card!=-1) {
					leadSuit = card;
					findcard(false,false);
				}
				else {
					return;
				}
			}
			else {
				for(int i=0;i<4;i++) {
					if(i!=leadSuit && north[i].size()+south[i].size() > max) {
						card = i; 
						max = north[i].size()+south[i].size();
					}
				}	
				played.push_back(north[leadSuit].back());
				north[card].pop_back();
				leadSuit = -1;
				findcard(false,true);
			}
		}
		else {
			int max1 = -10000;
			int card1 = -1;	
			int max2 = -10000;
			int card2 = -1;	
			for(int i=0;i<4;i++) {
				cout<<max1<<endl;
				cout<<north[i][0].second<<" "<<north[i].size()+south[i].size()<<endl;
				if(((north[i].size()+south[i].size()) > max1) && (north[i].size()>0) && (north[i][0].second==1)) {
					card1 = i; 
					cout<<"gh";
					max1 = north[i].size()+south[i].size();
				}
				if((north[i].size()+south[i].size() > max2) && north[i].size()>0 && south[i].size()>0 && south[i][0].second==1) {
					card2 = i; 
					max2 = north[i].size()+south[i].size();
				}
			}
			if(card1 != -1) { 
				cout<<"lol1";
				leadSuit = card1;
				played.push_back(north[leadSuit][0]);
				north[card1].erase(north[card1].begin());
				findcard(false,true);
			}
			else if(card2 != -1){
				cout<<"lol2";
				leadSuit = card2;
				played.push_back(north[leadSuit].back());
				north[card2].pop_back();
				finishCount++;
				findcard(false,false);
			}
			else
				return;
		}
	}
	else {
		return;
	}
}
void cashing::rank(){
	vector<pair<int,int> > temp[4];
	for(int i=0;i<4;i++){
		for(int j=0;j<north[i].size();j++){
			temp[i].push_back(north[i][j]);
		}
		for(int j=0;j<south[i].size();j++){
			temp[i].push_back(south[i][j]);
		}
		sort(temp[i].begin(),temp[i].end(),compare);
	}
	for(int i=0;i<4;i++){
		int check=14;
		int rank=1;
		for(int j=0;j<temp[i].size();j++){
			if(check==temp[i][j].first){
				temp[i][j].second=rank;
				check--;
			}
			else{
				check=temp[i][j].first;
				check--;
				rank++;
				temp[i][j].second=rank;
			}
		}
	}
	for(int i=0;i<4;i++){
		int a=0,b=0;
		for(int j=0;j<temp[i].size();j++){
			if(north[i].size()!=0 && temp[i][j].first==north[i][a].first){
				north[i][a++].second=temp[i][j].second;
			}
			else{
				south[i][b++].second=temp[i][j].second;	
			}
		}
	}

	/*for(int i=0;i<4;i++){
		for(int j=0;j<north[i].size();j++){
			cout<<north[i][j].first<<" "<<north[i][j].second<<"  ";
		}
		cout<<endl;
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<south[i].size();j++){
			cout<<south[i][j].first<<" "<<south[i][j].second<<"  ";
		}
		cout<<endl;
	}*/
}
void cashing::input(){
	for(int i=0;i<4;i++){
		string s;
		getline(cin,s);
		istringstream ss(s);
		string x;
		while(ss>>x){
			if(x=="-"){
				continue;
			}
			north[i].push_back({stoi(x),-1});
		}
	}	
	for(int i=0;i<4;i++){
		string s;
		getline(cin,s);
		istringstream ss(s);
		string x;
		while(ss>>x){
			if(x=="-"){
				continue;
			}
			south[i].push_back({stoi(x),-1});
		}
	}
    /*for(int i=0;i<4;i++){
 		for(int j=0;j<north[i].size();j++){
 			cout<<north[i][j].first<<" ";
 		}
 		cout<<endl;
	}
	for(int i=0;i<4;i++){
 		for(int j=0;j<south[i].size();j++){
 			cout<<south[i][j].first<<" ";
 		}
 		cout<<endl;
    }*/
}

int main() {
	cashing c;
	c.input();
	c.rank();
	c.findcard(true,true);
	vector <pair<int,int> > ans = c.played;
	for(int i=0;i<ans.size();i++)
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	return 0;
}