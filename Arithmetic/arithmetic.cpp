// Your includes here
#include "arithmetic.h"
// Your implementations here


long double Arithmetic::binary_to_decimal(string fraction){
	
	long double result = 0.0;
	for (int i = 1; i < fraction.size()+1; i++){
		 if (fraction[i - 1] == '1') {
			result += (pow(2, -i));
		}

	}

	return result;
}

// assume we onlu have double represent up to 32 bit 
string  Arithmetic::decimal_to_binary(long double fraction) {

	string result="";
	for (int i = 0; i < 32 && fraction != 0; i++) {
		fraction *= 2;
		if (fraction >= 1) {
			result += "1";
			fraction--;
		}
		else if (fraction < 1) {
			result += "0";
		}
	}
	
	while (result.size() < 32) {
		result += "0";
	}
	
	return result;
}



int Arithmetic::encode(const vector<unsigned char>& msg, int num_symbols_per_block, vector<bitset<32> >* encoded_msg) {
	
	int Num_bits=0;
	calc_pro(msg);
	long double R ;
	long double L ;
	int k;

	
	CDF.push_back(make_pair(0,0));
	double c = 0;
	for (int i = 0; i < Alphapet.size(); i++) {
		c += Alphapet[i].second;
		CDF.push_back(make_pair(Alphapet[i].first, c));
	}
	
	// for every block
	for (k = 0; k < int(msg.size()) / num_symbols_per_block; k++) {
		R = 1;
		L = 0;
		// for every symbol in the block
		for (int i = 0; i < num_symbols_per_block; i++) {
			unsigned char S = msg[k*num_symbols_per_block + i];
			for (int j = 1; j < CDF.size(); j++) {
				if (S == CDF[j].first) {
					double lold = L;
					L = L + (R - L)*CDF[j - 1].second;
					R = lold + (R - lold)*CDF[j].second;
					break;
				}
			}
		}
		// save and encode tags and calculate # of bits to every tag

		encoded_msg->push_back(bitset<32>(decimal_to_binary((R + L) / 2.0)));

		if (R - L > 0.0000001) {
			if (1 + ceil(log2(1 / (R - L))) < 32)
				Num_bits += 1 + ceil(log2(1 / (R - L)));
			else
				Num_bits += 32;
		}
		else {
			if (1 + ceil(log2(1 / (0.0000001))) < 32)
				Num_bits += 1 + ceil(log2(1 / (0.0000001)));
			else
				Num_bits += 32;
		}
	}
	// remider of symbols
	R = 1;
	L = 0;
		if ( (k*num_symbols_per_block) < msg.size()) {
			for (int i = k * num_symbols_per_block; i < msg.size(); i++) {
				unsigned char S = msg[i];
				for (int j = 1; j < CDF.size(); j++) {
					if (S == CDF[j].first) {
						
					double lold = L;
					L = L + (R - L)*CDF[j - 1].second;
					R = lold + (R - lold)*CDF[j].second;
					break;
						
					}
				}
			}

			// save and encode tags and calculate # of bits to every tag 
			encoded_msg->push_back(bitset<32>(decimal_to_binary((R + L) / 2)));
			if (R - L > 0.0000001) {
				if (1 + ceil(log2(1 / (R - L))) < 32)
					Num_bits += 1 + ceil(log2(1 / (R - L)));
				else
					Num_bits += 32;
			}
			else {
				if (1 + ceil(log2(1 / (0.0000001))) < 32)
					Num_bits += 1 + ceil(log2(1 / (0.0000001)));
				else
					Num_bits += 32;
			}
		}

	return Num_bits;
}

bool sortbysec(const pair<unsigned char, double> &a, const pair<unsigned char, double> &b)
{
	return (a.second < b.second);
}
void Arithmetic::calc_pro(const vector<unsigned char>& msg) {
	
	set<unsigned char> Alphaset;

	//make set of values
	double allchar = msg.size();
	for (int i = 0; i < msg.size(); i++)
		Alphaset.insert(msg[i]);
	

	//make pairs of values and thier probabilty
	for (std::set<unsigned char>::iterator it = Alphaset.begin(); it != Alphaset.end(); ++it) {
		int freq = std::count(msg.begin(), msg.end(), *it);
		Alphapet.push_back(make_pair(*it,freq/ allchar));
	
	}
	//sort descending
	sort(Alphapet.begin(), Alphapet.end(), sortbysec);
	reverse(Alphapet.begin(), Alphapet.end());

}


void Arithmetic::decode(const vector<bitset<32> >& encoded_msg, int num_symbols_per_block, vector<unsigned char>* decoded_msg) {
	double l, u,t,d;

	for (int i = 0; i < encoded_msg.size(); i++) {
		l = 0;
		u = 1;

		t = binary_to_decimal((encoded_msg[i]).to_string());
		
		for (int k = 0; k < num_symbols_per_block; k++) {
			d = (t - l) / (u - l);
			for (int j = 1; j < CDF.size(); j++) {
				if (d < CDF[j].second) {
					decoded_msg->push_back(CDF[j].first);
						double lold = l;
						l = l + (u - l)*CDF[j - 1].second;
						u = lold + (u - lold)*CDF[j].second;
						break;
					
				}
			}


		}



	}
	

}
void Arithmetic::Read_Alph() {
	int size; int val; double pro;
	cin >> size;
	for (int i = 0; i < size; i++) {
		cin >> val>>pro;
		CDF.push_back(make_pair(val, pro));
	}
	return;
}

void Arithmetic::Write_Alph() {
	cout << CDF.size() << endl;
	for (int i = 0; i < CDF.size()-1; i++)
		cout << (int)CDF[i].first << " " << CDF[i].second<<" ";
	cout << (int)CDF[CDF.size() - 1].first << " " << CDF[CDF.size() - 1].second;
	return;
}