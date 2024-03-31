#include <iostream>
#include <ñmath>

using namespace std;

int main()
{
	int first, first_test, gr_key;
	int incoh = 0, grow = 0;
	do {
		grow = 0;
		cout << "Enter Graphic key: ";
		cin >> gr_key;
		if (gr_key > pow(10, 9) - 1 || gr_key < pow(10, 3)) {
			cout << "Enter a number between 4 and 9 digits!\n";
		}
		for (int gr_key_test = gr_key; gr_key_test > 0; gr_key_test /= 10, grow++) {
			first_test = gr_key_test % 10;
			if (first_test == 0) {
				cout << "Incorrect key, try again!\n";
				break;
			}
		}
	} while ((gr_key > pow(10, 9) - 1 || gr_key < pow(10, 3)) || first_test == 0);

	int long_gr_key[9]{ 0 };
	cout << "Back_numb [ ";
	for (int gr_key_back = gr_key, Rq = 9; Rq > 0; gr_key_back /= 10) {
		Rq--;
		long_gr_key[Rq] = gr_key_back % 10;
		if (long_gr_key[Rq] == 0) {
			continue;
		}cout << long_gr_key[Rq];
	}cout << " ]";

	first = long_gr_key[0];
	cout << "\nEnable debug mode? Chose answer: Y \\ N: ";

	int one = 0, two = 0, three = 0, four = 0, five = 0;
	int six = 0, seven = 0, eight = 0, nine = 0;
	bool use_Ptwo = 0, use_Pfour = 0, use_Psix = 0;
	bool use_Peight = 0, use_Pfive = 0, flag_options = 1;
	char line;

	do {
		cin >> line;
		if (line == 'Y') {
			cout << "Debug mode allows!\n";
			break;
		}
		else if (line == 'N') {
			cout << "You can only see the key opportunity!\n";
			flag_options = false;
			break;
		}
		else cout << "Please choose only answer Y or N: ";
	} while (line != 'Y' || line != 'N');
	cout << "\nGraphic key layout: ";
	cout << first << " ";

	const int ROWS = 3, COLS = 3;
	int MAS[ROWS][COLS]{}, step = 0;
	long_gr_key[step] = first;
	int Re, GG;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			MAS[i][j] = long_gr_key[step];
			step++;
			GG = long_gr_key[step];
			Re = first + GG;
			switch (first) {
			case 1: {
				if (Re == 4 || Re == 8 || Re == 10) {
					if (use_Pfive == true && Re == 10) first = GG;
					else if (use_Pfive == false && Re == 10) {
						incoh++;
						first = GG;
					}
					if (use_Ptwo == true && Re == 4) first = GG;
					else if (use_Ptwo == false && Re == 4) {
						incoh++;
						first = GG;
					}
					if (use_Pfour == true && Re == 8) first = GG;
					else if (use_Pfour == false && Re == 8) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				one++;
				break;
			}
			case 3: {
				if (Re == 4 || Re == 10 || Re == 12) {
					if (use_Pfive == true && Re == 10) first = GG;
					else if (use_Pfive == false && Re == 10) {
						incoh++;
						first = GG;
					}
					if (use_Ptwo == true && Re == 4) first = GG;
					else if (use_Ptwo == false && Re == 4) {
						incoh++;
						first = GG;
					}
					if (use_Psix == true && Re == 12) first = GG;
					else if (use_Psix == false && Re == 12) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				three++;
				break;
			}
			case 5: {
				first = GG;
				use_Pfive = true;
				five++;
				break;
			}
			case 7: {
				if (Re == 8 || Re == 10 || Re == 16) {
					if (use_Pfive == true && Re == 10) first = GG;
					else if (use_Pfive == false && Re == 10) {
						incoh++;
						first = GG;
					}
					if (use_Pfour == true && Re == 8) first = GG;
					else if (use_Pfour == false && Re == 8) {
						incoh++;
						first = GG;
					}
					if (use_Peight == true && Re == 16) first = GG;
					else if (use_Peight == false && Re == 16) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				seven++;
				break;
			}
			case 9: {
				if (Re == 10 || Re == 12 || Re == 16) {
					if (use_Pfive == true && Re == 10) first = GG;
					else if (use_Pfive == false && Re == 10) {
						incoh++;
						first = GG;
					}
					if (use_Psix == true && Re == 12) first = GG;
					else if (use_Psix == false && Re == 12) {
						incoh++;
						first = GG;
					}
					if (use_Peight == true && Re == 16) first = GG;
					else if (use_Peight == false && Re == 16) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				nine++;
				break;
			}
			case 2: {
				if (Re == 10) {
					if (use_Pfive == true) first = GG;
					else if (use_Pfive == false) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				use_Ptwo = true;
				two++;
				break;
			}
			case 4: {
				if (Re == 10) {
					if (use_Pfive == true) first = GG;
					else if (use_Pfive == false) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				use_Pfour = true;
				four++;
				break;
			}
			case 6: {
				if (Re == 10) {
					if (use_Pfive == true) first = GG;
					else if (use_Pfive == false) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				use_Psix = true;
				six++;
				break;
			}
			case 8: {
				if (Re == 10) {
					if (use_Pfive == true) first = GG;
					else if (use_Pfive == false) {
						incoh++;
						first = GG;
					}
				}
				else first = GG;
				use_Peight = true;
				eight++;
				break;
			}
			default: {
				first = GG;
				break; }
			}
			if (step < 9) cout << first << " ";
		}
	}
	if (flag_options == true) {
		cout << "\n\nMasKey [3][3] = { { ";
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				j == 2 ? cout << MAS[i][j] : cout << MAS[i][j] << ", ";
				if (COLS - j == 1) cout << " }";
			}if (ROWS - i != 1) cout << ", { ";
		}cout << " }\n";

		cout << "\nKey length: <" << grow << "> points";
		cout << "\nIncoherent chains: " << incoh;
		cout << "\nNumber of uses of the center point: " << use_Pfive;
		if (one > 1 || two > 1 || three > 1 || four > 1 || five > 1 || six > 1 || seven > 1 || eight > 1 || nine > 1) {
			cout << "\n\nReplay number - [1] : " << one;
			cout << "\t\tReplay number - [6] : " << six;
			cout << "\nReplay number - [2] : " << two;
			cout << "\t\tReplay number - [7] : " << seven;
			cout << "\nReplay number - [3] : " << three;
			cout << "\t\tReplay number - [8] : " << eight;
			cout << "\nReplay number - [4] : " << four;
			cout << "\t\tReplay number - [9] : " << nine;
			cout << "\nReplay number - [5] : " << five;
			cout << "\t\tReplay number - [0] : -";
		}
		else cout << "\n\nReplay numbers : 0";
		bool start_hack = false;
		if (incoh == 0 && !(one > 1 || two > 1 || three > 1 || four > 1 || five > 1 || six > 1 || seven > 1 || eight > 1 || nine > 1)) {
			cout << "\n\nKey exists!\n\nHACK this key ? (ans: Y \\ N) : ";
			do {
				cin >> line;
				if (line == 'Y') {
					cout << "\nWell, let's get started!\n";
					start_hack = true;
					break;
				}
				else if (line == 'N') {
					cout << "\nGet on your knees and pray!\n";
					break;
				}
				else cout << "Please choose only answer Y or N: ";
			} while (line != 'Y' || line != 'N');
		}
		else {
			cout << "\n\nKey does not exist!\n";
		}
		if (start_hack == true) {
			const int R = 3, L = 3;
			bool flag_run = false;

			int h_MAS[R][L]{ 0 }, avg = 0, incoh = 0, _Num = 0;
			int a = 0, b = 0, c = 0, a1 = 0, b1 = 0, c1 = 1, a2 = 2, b2 = 3, c2 = 4;

			for (int _E_FV; flag_run == false; c2++) {
				if (MAS[0][0] == h_MAS[0][0] && MAS[0][1] == h_MAS[0][1] && MAS[0][2] == h_MAS[0][2]) {
					if (MAS[1][0] == h_MAS[1][0] && MAS[1][1] == h_MAS[1][1] && MAS[1][2] == h_MAS[1][2]) {
						if (MAS[2][0] == h_MAS[2][0] && MAS[2][1] == h_MAS[2][1] && MAS[2][2] == h_MAS[2][2]) {
							flag_run = true;
							break;
						}
					}
				}
				incoh = 0;
				one = two = three = four = five = six = seven = eight = nine = 0;
				use_Ptwo = use_Pfour = use_Psix = use_Peight = use_Pfive = false;
				if (c2 > 9) {
					c2 = 1;
					b2++;
				}h_MAS[2][2] = c2;
				if (b2 > 9) {
					b2 = 1;
					a2++;
				}h_MAS[2][1] = b2;
				if (a2 > 9) {
					a2 = 1;
					c1++;
				}h_MAS[2][0] = a2;
				if (c1 > 9) {
					c1 = 1;
					b1++;
				}h_MAS[1][2] = c1;
				if (b1 > 9) {
					b1 = 1;
					a1++;
				}h_MAS[1][1] = b1;
				if (a1 > 9) {
					a1 = 1;
					c++;
				}h_MAS[1][0] = a1;
				if (c > 9) {
					c = 1;
					b++;
				}h_MAS[0][2] = c;
				if (b > 9) {
					b = 1;
					a++;
				}h_MAS[0][1] = b;
				h_MAS[0][0] = a;
				if (c1 > 0) {
					_E_FV = 4;
					_Num = int(c1 + 10 * (a2 + 10 * (b2 + 10 * c2)));
				}if (b1 > 0) {
					_E_FV = 5;
					_Num = int(b1 + 10 * (c1 + 10 * (a2 + 10 * (b2 + 10 * c2))));
				}if (a1 > 0) {
					_E_FV = 6;
					_Num = int(a1 + 10 * (b1 + 10 * (c1 + 10 * (a2 + 10 * (b2 + 10 * c2)))));
				}if (c > 0) {
					_E_FV = 7;
					_Num = int(c + 10 * (a1 + 10 * (b1 + 10 * (c1 + 10 * (a2 + 10 * (b2 + 10 * c2))))));
				}if (b > 0) {
					_E_FV = 8;
					_Num = int(b + 10 * (c + 10 * (a1 + 10 * (b1 + 10 * (c1 + 10 * (a2 + 10 * (b2 + 10 * c2)))))));
				}if (a > 0) {
					_E_FV = 9;
					_Num = int(a + 10 * (b + 10 * (c + 10 * (a1 + 10 * (b1 + 10 * (c1 + 10 * (a2 + 10 * (b2 + 10 * c2))))))));
				}
				first = _Num % 10;
				_Num /= 10;
				switch (first) {
				case 1: {
					one++;
					break;
				}
				case 2: {
					two++;
					break;
				}
				case 3: {
					three++;
					break;
				}
				case 4: {
					four++;
					break;
				}
				case 5: {
					five++;
					break;
				}
				case 6: {
					six++;
					break;
				}
				case 7: {
					seven++;
					break;
				}
				case 8: {
					eight++;
					break;
				}
				case 9: {
					nine++;
					break; }
				}
				for (int i = 0; i < _E_FV; _Num /= 10, i++) {
					GG = _Num % 10;
					Re = first + GG;
					switch (first) {
					case 1: {
						if (Re == 4 || Re == 8 || Re == 10) {
							if (use_Pfive == true && Re == 10) first = GG;
							else if (use_Pfive == false && Re == 10) {
								incoh++;
								first = GG;
							}
							if (use_Ptwo == true && Re == 4) first = GG;
							else if (use_Ptwo == false && Re == 4) {
								incoh++;
								first = GG;
							}
							if (use_Pfour == true && Re == 8) first = GG;
							else if (use_Pfour == false && Re == 8) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						if (i > 0) {
							one++;
						}
						break;
					}
					case 3: {
						if (Re == 4 || Re == 10 || Re == 12) {
							if (use_Pfive == true && Re == 10) first = GG;
							else if (use_Pfive == false && Re == 10) {
								incoh++;
								first = GG;
							}
							if (use_Ptwo == true && Re == 4) first = GG;
							else if (use_Ptwo == false && Re == 4) {
								incoh++;
								first = GG;
							}
							if (use_Psix == true && Re == 12) first = GG;
							else if (use_Psix == false && Re == 12) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						if (i > 0) {
							three++;
						}
						break;
					}
					case 5: {
						first = GG;
						use_Pfive = true;
						if (i > 0) {
							five++;
						}
						break;
					}
					case 7: {
						if (Re == 8 || Re == 10 || Re == 16) {
							if (use_Pfive == true && Re == 10) first = GG;
							else if (use_Pfive == false && Re == 10) {
								incoh++;
								first = GG;
							}
							if (use_Pfour == true && Re == 8) first = GG;
							else if (use_Pfour == false && Re == 8) {
								incoh++;
								first = GG;
							}
							if (use_Peight == true && Re == 16) first = GG;
							else if (use_Peight == false && Re == 16) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						if (i > 0) {
							seven++;
						}
						break;
					}
					case 9: {
						if (Re == 10 || Re == 12 || Re == 16) {
							if (use_Pfive == true && Re == 10) first = GG;
							else if (use_Pfive == false && Re == 10) {
								incoh++;
								first = GG;
							}
							if (use_Psix == true && Re == 12) first = GG;
							else if (use_Psix == false && Re == 12) {
								incoh++;
								first = GG;
							}
							if (use_Peight == true && Re == 16) first = GG;
							else if (use_Peight == false && Re == 16) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						if (i > 0) {
							nine++;
						}
						break;
					}
					case 2: {
						if (Re == 10) {
							if (use_Pfive == true) first = GG;
							else if (use_Pfive == false) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						use_Ptwo = true;
						if (i > 0) {
							two++;
						}
						break;
					}
					case 4: {
						if (Re == 10) {
							if (use_Pfive == true) first = GG;
							else if (use_Pfive == false) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						use_Pfour = true;
						if (i > 0) {
							four++;
						}
						break;
					}
					case 6: {
						if (Re == 10) {
							if (use_Pfive == true) first = GG;
							else if (use_Pfive == false) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						use_Psix = true;
						if (i > 0) {
							six++;
						}
						break;
					}
					case 8: {
						if (Re == 10) {
							if (use_Pfive == true) first = GG;
							else if (use_Pfive == false) {
								incoh++;
								first = GG;
							}
						}
						else first = GG;
						use_Peight = true;
						if (i > 0) {
							eight++;
						}
						break;
					}
					default: {
						first = GG;
						incoh++;
						break; }
					}
				}
				if (incoh == 0 && !(one > 1 || two > 1 || three > 1 || four > 1)) {
					if (!(five > 1 || six > 1 || seven > 1 || eight > 1 || nine > 1)) {
						cout << "\nMasKey [R][L]" << " attention < " << ++avg << " > = [( ";
						for (int i = 0; i < ROWS; i++) {
							for (int j = 0; j < COLS; j++) {
								j == 2 ? cout << h_MAS[i][j] : cout << h_MAS[i][j] << ", ";
								if (COLS - j == 1) cout << " )";
							}
							if (ROWS - i != 1) cout << ", ( ";
						}
						cout << "]";
					
					}
				}
				else {
					cout << "\nMasKey [R][L]" << " attention </> [ Erf ]";
				}
				cout << "\nIncoherent chains: " << incoh;
				cout << "\nNumber of uses of the center point: " << use_Pfive;
				cout << "\nVF: " << a << b << c << a1 << b1 << c1 << a2 << b2 << c2;
				cout << "\nReplay number - [1] : " << one;
				cout << "\t\tReplay number - [6] : " << six;
				cout << "\nReplay number - [2] : " << two;
				cout << "\t\tReplay number - [7] : " << seven;
				cout << "\nReplay number - [3] : " << three;
				cout << "\t\tReplay number - [8] : " << eight;
				cout << "\nReplay number - [4] : " << four;
				cout << "\t\tReplay number - [9] : " << nine;
				cout << "\nReplay number - [5] : " << five;
				cout << "\t\tReplay number - [0] : -\n";
			}
			cout << "RS: "<<avg;
			if (flag_run == true)
			{
				cout << "\n\nYour password HACK = < ";
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						if (h_MAS[i][j] == 0) {
							continue;
						}
						else cout << h_MAS[i][j] << " ";
					}
				}
				cout << ">\n\n";
			}
			else cout << "\n\nGame Over ^-^\n\n";
		}
	}
	system("pause");
	return 0;
}