#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;

void uzupelnienie_ciagu(queue<char> kolejka[], int indeks);

void wypisywanie_bck(queue<char> kolejka[], int nr);

void generowanie(queue<char> kolejka[]);

void wypisywanie(queue<char> kolejka[], int nr);

void rysowanie(queue<char> kolejka[], bool zwrotnica[], int wynik);

int ruch(queue<char> kolejka[], bool zwrotnica[]);

int spr(bool zwrotnica[]);

int punkty(queue<char> kolejka[], int wybor2);

int main()
{
	int wynik = 0;
	bool zwrotnica[4] = { true, true, true, true };
	srand(time(NULL));

	queue<char> kolejka[11];                                //0 - tor
															//1-5 - rzeczywisty ciąg
	generowanie(kolejka);                                   //6-10 - sprawdzenie
	do
	{
		system("cls");
		rysowanie(kolejka, zwrotnica, wynik);
		wynik += ruch(kolejka, zwrotnica);

	} while (wynik >= 0 && wynik < 50);
	if (wynik >= 50) {
		cout << "Wygrales!!!" << endl;
	}
	else cout << "Przegrales!!!" << endl;
	return 0;
}

void wypisywanie_bck(queue<char> kolejka[], int nr)
{
	vector<char> bck;
	for (unsigned int i = 0; i < kolejka[nr].size(); i++)
	{
		bck.push_back(kolejka[nr].front());
		kolejka[nr].push(kolejka[nr].front());
		kolejka[nr].pop();
	}
	for (int i = bck.size() - 1; i >= 0; i--)
	{
		cout << bck[i];
	}
}

void generowanie(queue<char> kolejka[])
{
	int x;
	char alfabet[] = "ABCD";

	cout << "Podaj ilosc wagonow(>=5): " << endl;
	cin >> x;
	for (int i = 0; i < 5; i++)
	{
		int y = rand() % (sizeof(alfabet) - 1);
		int s = (i + 6);
		kolejka[0].push(alfabet[y]);
		kolejka[s].push(alfabet[y]);
	}
	for (int i = 0; i < (x - 5); i++)
	{
		int y = rand() % (sizeof(alfabet) - 1);
		int s = (rand() % 5) + 6;
		kolejka[0].push(alfabet[y]);
		kolejka[s].push(alfabet[y]);
	}

}

void wypisywanie(queue<char> kolejka[], int nr)
{
	int x = kolejka[nr].size();
	for (int i = 0; i < x; i++)
	{
		cout << kolejka[nr].front();
		kolejka[nr].push(kolejka[nr].front());
		kolejka[nr].pop();
	}
}

void rysowanie(queue<char> kolejka[], bool zwrotnica[], int wynik)
{

	cout << "Wynik: " << wynik << endl << endl;

	wypisywanie_bck(kolejka, 0);

	for (int j = 1; j <= 5; j++)
	{
		if (j == 1)
		{
			cout << ' ';
		}
		else
		{
			for (unsigned int i = 0; i < kolejka[0].size() + 2 * j; i++)
			{
				cout << ' ';
			}
		}

		for (int i = 0; i < 50; i++)
		{
			cout << '=';
		}

		wypisywanie_bck(kolejka, j);

		cout << "    Tor " << j << ":  [";

		wypisywanie_bck(kolejka, j + 5);

		cout << ']' << endl << endl;

		for (unsigned int i = 0; i < kolejka[0].size() + 2 * j; i++)
		{
			cout << ' ';
		}

		if (j != 5 && zwrotnica[j - 1] == true)
		{
			cout << char(92) << char(92);
			cout << "   (" << j + 1 << ')';
		}
		cout << endl << endl;
	}
	cout << endl;
}

int ruch(queue<char> kolejka[], bool zwrotnica[])
{
	char wybor;
	cout << "Wybierz tor (2-5), aby zmienic stan zwrotnicy lub zwolnij wagon (w):" << endl << endl;
	cin >> wybor;
	int wybor2 = wybor - '0';
	if (wybor == 'w')
	{
		kolejka[spr(zwrotnica)].push(kolejka[0].front());
		kolejka[0].pop();
		uzupelnienie_ciagu(kolejka, 0);
		return punkty(kolejka, spr(zwrotnica));
	}
	else if (wybor == '2' || wybor == '3' || wybor == '4' || wybor == '5')
	{
		zwrotnica[wybor2 - 2] = !zwrotnica[wybor2 - 2];
		return 0;
	}
	return 0;
}

int spr(bool zwrotnica[])
{
	for (int i = 0; i < 4; i++)
	{
		if (zwrotnica[i] == false)
		{
			return i + 1;
		}
	}
	return 5;
}

void uzupelnienie_ciagu(queue<char> kolejka[], int indeks)
{
	char alfabet[] = "ABCD";
	int y = rand() % (sizeof(alfabet) - 1);
	kolejka[indeks].push(alfabet[y]);
}

int punkty(queue<char> kolejka[], int wybor)
{
	bool pod = true;
	int x = (kolejka[wybor + 5].size() - kolejka[wybor].size());
	for (unsigned int i = 0; i < kolejka[wybor].size(); i++)
	{
		if (kolejka[wybor].front() != kolejka[wybor + 5].front())
		{
			pod = false;
		}
		kolejka[wybor].push(kolejka[wybor].front());
		kolejka[wybor].pop();

		kolejka[wybor + 5].push(kolejka[wybor + 5].front());
		kolejka[wybor + 5].pop();

	}
	for (int i = 0; i < x; i++)
	{
		kolejka[wybor + 5].push(kolejka[wybor + 5].front());
		kolejka[wybor + 5].pop();
	}
	if (pod == true && x == 0)
	{
		unsigned int rozmiar = kolejka[wybor].size();
		for (unsigned int i = 0; i < rozmiar; i++) {
			kolejka[wybor].pop();
		}
		rozmiar = kolejka[wybor + 5].size();
		for (unsigned int i = 0; i < rozmiar; i++) {
			kolejka[wybor + 5].pop();
			uzupelnienie_ciagu(kolejka, wybor + 5);
		}
		return 10;
	}
	else if (pod != true)
	{
		unsigned int rozmiar = kolejka[wybor].size();
		for (unsigned int i = 0; i < rozmiar; i++) {
			kolejka[wybor].pop();
		}
		rozmiar = kolejka[wybor + 5].size();
		for (unsigned int i = 0; i < rozmiar; i++) {
			kolejka[wybor + 5].pop();
			uzupelnienie_ciagu(kolejka, wybor + 5);
		}
		return -10;
	}
	else
	{
		return 0;
	}
}