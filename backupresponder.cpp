string b = partner[0];
		char l = b[0];
		char c = b[1];
		string a;
		if(POINTS.first < 23) {
			if(A.suit[c].first+B.suit[c].first >= 8) {
				a += l+1;
				a += c;
			}
			else if(A.balanced) {
				a = "1N";
			}
			else {
				char d = getfourcard(c);
				a = to_string(availbids[d][0]);
				a += d;
				if(a[0] == '2')
					a = "1N";
			} 
		}
		if(POINTS.first > 22 && POINTS.first < 25) {
			if(A.suit[c].first+B.suit[c].first >= 8) {
				char d = getfourcard(c);
				a = to_string(availbids[d][0]);
				a += d;
			}
			else if(A.balanced) {
				char d = getfourcard(c);
				a = to_string(availbids[d][0]);
				a += d;
			}
		}
		if(POINTS.first >= 25) {
			if(A.suit[c].first+B.suit[c].first >= 8) {
				a += l+2;
				a += c;
			}
			else if(A.balanced) {
				a = "2N";
			}
			else {
				char d = getfourcard(c);
				a = to_string(availbids[d][0]);
				a += d;	
			}
		}
		return "P";