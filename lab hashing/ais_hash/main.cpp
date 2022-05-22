#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
    using namespace std;
int gcd(int a, int b) {
	while (true) {
		if (a == 0) {
			return (b >= 0) ? b : -b;
		}
		b %= a;
		if (b == 0) {
			return (a >= 0) ? a : -a;
		}
		a %= b;
	}
}

class Rational {

public:
	int numer, denom;
	Rational(int a, int b) :numer(a), denom(b) {
		int divisor = gcd(numer, denom);
		divisor = (denom >= 0) ? divisor : -divisor;
		numer /= divisor;
		denom /= divisor;
	}
};

bool operator == (Rational first, Rational second) {
	return ((first.numer == second.numer) && (first.denom == second.denom));
}

bool operator != (Rational first, Rational second) {
	return !(first == second);
}


int calcHash(int a, vector<Rational> k, int b, int n) {
	int k2 = 0;
	for (int i = 0; i < k.size(); i++) {
		k2 += k[i].numer + k[i].denom;
	}
	return ((a*k2 + b) % n);
}


vector<vector<vector<Rational>>> Hashing(vector<vector<Rational>> data, int a, int b) {

	srand((unsigned int)time(nullptr));
	int n = data.size()*2;
	vector<vector<Rational>> hashtable1(n, vector<Rational>(0, Rational(0,1)));
	vector<vector<vector<Rational>>> hashtable2(n, hashtable1);
	vector<vector<vector<Rational>>> hashtable3(n, hashtable1);

	int index = 0;
	for (int i = 0; i < data.size(); i++) {
		int index1 = calcHash(a, data[i], b, n);
		index = 0;

		while (hashtable2[index1][index].size() > 0) {
			index++;
		}
		hashtable2[index1][index] = data[i];
	}
	vector<vector<int>> values(n); //a, b

	for (int i = 0; i < hashtable2.size(); i++) {
		index = 0;
		a = rand() % (100 - 1);
		b = rand() % (100 - 1);
		while (index < hashtable2[i].size() && hashtable2[i][index].size()>0) {
			int index2 = calcHash(a, hashtable2[i][index], b, n);
			if (hashtable3[i][index2].size() > 0 && hashtable3[i][index2] != hashtable2[i][index]) {
				a = rand() % (100 - 1);
				b = rand() % (100 - 1);
				index = 0;
				hashtable3[i] = hashtable1;
				continue;
			}
			hashtable3[i][index2] = hashtable2[i][index];
			index++;
		}
		values.push_back({ a, b });

	}
	for (int i = 0; i < hashtable3.size(); i++) {
		for (int j = 0; j < hashtable3[i].size(); j++) {
			if (hashtable3[i][j].size() < 1) {
				cout << "0";
			}
			for (int m = 0; m < hashtable3[i][j].size(); m++) {
				cout << hashtable3[i][j][m].numer << "/"<< hashtable3[i][j][m].denom<<" ";
			}
			cout << "\t";
		}
		cout << "\n";
	}
	return hashtable3;

}



int main()
{
	vector < vector < Rational >> data;
	data.push_back({ Rational(1,2), Rational(3,5), Rational(1,6)});
	data.push_back({ Rational(1,2), Rational(3,5), Rational(1,6) });
	data.push_back({ Rational(1,2) });
	data.push_back({ Rational(4,8) });
	data.push_back({ Rational(1,2), Rational(3,5), Rational(1,8)});
	int a = rand() % (100 - 1);
	int b = rand() % (100 - 1);
	vector<vector<vector<Rational>>> hashtable = Hashing(data, a, b);
}
