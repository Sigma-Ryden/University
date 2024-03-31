#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int Nst, Nfn, i, Sum = 0;
	cout << "I can find sum number from a to b, please input value for a and b:" << endl;
	cin >> Nst >> Nfn;
	if (Nst < Nfn) {
		for (i = Nst; i <= Nfn; i++) {
			Sum += i;
		}
		cout << "Sum:" << Sum;
	}
	else cout << "Please check, that a<b and try again!";
	return 0;
}