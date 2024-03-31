#include "pch.h"
#include <iostream>

using namespace std;

int main() {
	int pin = 0, a = 0, b = 0, c = 0, d = 0, h = 0, s = 0;
	cout << "Enter PIN_CODE: ";
	cin >> pin;
	for (int j = 1; pin > 0; pin /= 10, j++)
	{
		switch (j)
		{
		case 1:
		{
			d = pin % 10;
			break;
		}
		case 2:
		{
			c = pin % 10;
			break;
		}
		case 3:
		{
			b = pin % 10;
			break;
		}
		case 4:
		{
			a = pin % 10;
			break;
		}
		}
	}
	cout << "\nAlignment PIN_CODE: " << a << " " << b << " " << c << " " << d << '\n';
	int pin_code[4] = { a,b,c,d }, avg = 1;

	int ha = 0, hb = 0, hc = 0, hd = 0, pin_hack[4] = { ha, hb, hc, hd };
	/*For example: 9327*/
	for (int r_code = 0; r_code !=1;)
	{
		if (a == ha && b == hb && c == hc && d == hd)
		{
			r_code = 1;
			break;
		}
		else
		{
			hd++;
			if (hd > 9)
			{
				hd = 0;
				hc += 1;
				if (hc > 9)
				{
					hc = 0;
					hb += 1;
					if (hb > 9)
					{
						hb = 0;
						ha += 1;
						if (ha > 9)
						{
							break;
						}
					}
				}
			}
		}
		cout << "Attempt <" << avg++ << ">" << " PIN_RF: " << ha << " " << hb << " " << hc << " " << hd << '\n';
		pin_hack[0] = ha;
		pin_hack[1] = hb;
		pin_hack[2] = hc;
		pin_hack[3] = hd;
	}
	cout << "\nYour Password <PIN_NACK>: ";
	do
	{
		cout << pin_hack[h++];
	} while (h != 4);
	cout << '\n';
	system("Pause");
	return 0;
}