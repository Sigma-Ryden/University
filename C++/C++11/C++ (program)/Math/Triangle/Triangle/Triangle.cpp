#include "pch.h" 
#include <iostream>

using namespace std;

int main()
{
	float a, b, c;
	cout << "a=";
	cin >> a;
	cout << "b=";
	cin >> b;
	cout << "c=";
	cin >> c;
	if (a <= 0 || b <= 0 || c <= 0) {
		cout << "Input side not correct";
		return -1;
	}

	if ((a + b > c) && (a + c > b) && (b + c > a)) {
		cout << "Triangle";
	}
	else {
		cout << "Not triangle";
	}
	if (a*a + b * b == c * c) {
		cout << " is right, c - gipotenuza";
	}
	else if (a*a + c * c == b * b) {
		cout << " is right, b - gipotenuza";
	}
	else if (c*c + b * b == a * a) {
		cout << " is right, a - gipotenuza";
	}
	else {
		cout << " not is pramokutniy trekutnik";
	}
	return 0;
}