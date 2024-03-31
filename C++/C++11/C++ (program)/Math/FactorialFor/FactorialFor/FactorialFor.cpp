#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	double f, n, ft=1;
	cout << "Input number: ";
	cin >> n;
	if (n>=0) {
		for (f = 1; f <= n; f++ ) {
			ft *= f;
		}
		cout << "Factorial:" << ft;
	}
	else cout <<"Please input value integer!";

	system("pause");
	return 0;
}