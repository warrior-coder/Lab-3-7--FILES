#include <iostream>
#include <stdio.h>
#include <io.h>

using namespace std;

FILE* fl;

struct dinfo
{
	int code;
	int amount;
	int month;
} detail;

int n = 0;
char flname[30];
bool no_fl_name = true;

int menu();     // MENU
void fl_add();  // Enter data to file
void fl_read(); // Read data from file
void res_con(); // Print result in console
void res_fl();  // Print result in file

int main()
{
	while (true)
	{
		switch (menu())
		{
		case 1: fl_add(); break;
		case 2: fl_read(); break;
		case 3: res_con(); break;
		case 4: res_fl(); break;
		case 5: return 0; break;
		default: cout << "Enter correct!" << endl;
		}

		cout << endl;
		system("pause");
		system("cls");
	}
}

int menu()
{
	cout << "1. Enter data to file" << endl;
	cout << "2. Read data from file" << endl;
	cout << "3. Print result in console" << endl;
	cout << "4. Print result in file" << endl;
	cout << "5. Exit" << endl;
	cout << "--------------------------" << endl;

	int k;
	cin >> k;
	cout << endl;

	return k;
}

char* fl_name_get()
{
	if (no_fl_name)
	{
		cout << "Enter file name: ";
		cin >> flname;
		no_fl_name = false;
	}

	return flname;
}

void fl_add()
{
	fopen_s(&fl, fl_name_get(), "ab");
	if (fl == NULL)
	{
		fopen_s(&fl, fl_name_get(), "wb");
		if (fl == NULL)
		{
			cout << "FILE CREATE ERROR" << endl;
			return;
		}
	}

	char chr;

	do {
		cout << "Enter detail code: "; cin >> detail.code;
		cout << "Enter detail amount: "; cin >> detail.amount;
		cout << "Enter detail month: "; cin >> detail.month;

		fwrite(&detail, sizeof(dinfo), 1, fl);

		cout << endl << "Enter more? (y/n) "; cin >> chr;
	} while (chr == 'y');

	fclose(fl);
}

void fl_read()
{
	fopen_s(&fl, fl_name_get(), "rb");
	if (fl == NULL)
	{
		cout << "FILE READ ERROR" << endl;
		return;
	}

	n = _filelength(_fileno(fl)) / sizeof(dinfo);

	for (int i = 0; i < n; i++)
	{
		fread(&detail, sizeof(dinfo), 1, fl);
		cout << "Code - " << detail.code << " Amount - " << detail.amount << " Month - " << detail.month << endl;
	}
	fclose(fl);
}

void res_con()
{
	fopen_s(&fl, fl_name_get(), "rb");
	if (fl == NULL)
	{
		cout << "FILE READ ERROR" << endl;
		return;
	}

	n = _filelength(_fileno(fl)) / sizeof(dinfo);

	int month;
	cout << "Ener month number: ";
	cin >> month;
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		fread(&detail, sizeof(dinfo), 1, fl);
		if (detail.month == month)
			cout << "Code - " << detail.code << " Amount - " << detail.amount << endl;
	}

	fclose(fl);
}

void res_fl()
{
	fopen_s(&fl, fl_name_get(), "rb");
	if (fl == NULL)
	{
		cout << "FILE OPEN ERROR" << endl;
		return;
	}

	int month;
	cout << "Ener month number: ";
	cin >> month;

	char flname2[20];
	cout << "Enter result file name: ";
	cin >> flname2;

	FILE* fl2;
	fopen_s(&fl2, flname2, "wt");
	if (fl2 == NULL)
	{
		cout << "FILE CREATE ERROR" << endl;
		return;
	}

	n = _filelength(_fileno(fl)) / sizeof(dinfo);

	fprintf(fl2, "%s%d%s", "Details for month ", month, ":\n");
	for (int i = 0; i < n; i++) {
		fread(&detail, sizeof(dinfo), 1, fl);
		if (detail.month == month)
			fprintf(fl2, "%s%d%s%d\n", "Code - ", detail.code, " Amount - ", detail.amount);
	}
	cout << "Done" << endl;

	_fcloseall();
}