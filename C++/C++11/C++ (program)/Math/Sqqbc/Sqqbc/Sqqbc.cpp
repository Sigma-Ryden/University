#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	float a, s, i, n, q;
	cout << "n=";
	cin >> n;
	i = 1;
	s = 0;
	if (n > 0) {
		while (i <= n) {
			cout << 'a' << i << '=';
			cin >> a;
			s = s + a;
			i++;
		}
		q = s / n;
		cout << "S=" << s << endl << "S/n=" << q;
	}
	else {
		cout << "ERROR";
	}
	return 0;
}