#include <iostream> // cin, cout
#include <stdio.h>  // fopen_s(), fclose(), fwrite(), fread(), fprintf()
#include <io.h>     // _fileno(), _filelength()

using namespace std;

struct Flat_Info
{
	int number;
	int rooms;
	char owner_name[20];
	float area;
	//
	// Other fields
	//
};

FILE* fp;
char fname[20] = "";

char menu();                    // Menu
char* get_file_name();          // File name read
void add_data_to_file();        // Enter data to file
void read_data_from_file();     // Read data from file
void print_result_in_console(); // Print result in console
void print_result_in_file();    // Print result in file

int main()
{
	while (true)
	{
		switch (menu())
		{
			case '1': add_data_to_file(); break;
			case '2': read_data_from_file(); break;
			case '3': print_result_in_console(); break;
			case '4': print_result_in_file(); break;
			default: return 0;
		}

		cout << endl;
		system("pause");
		system("cls");
	}
}

char menu()
{
	cout << "+---------FILE-SYSTEM----------+" << endl;
	cout << "| 1 - Enter data to file       |" << endl;
	cout << "| 2 - Read data from file      |" << endl;
	cout << "| 3 - Print result in console  |" << endl;
	cout << "| 4 - Print result in file     |" << endl;
	cout << "| 5 - Exit                     |" << endl;
	cout << "+------------------------------+" << endl;

	char menu;
	cin >> menu;
	cout << endl;
	return menu;
}

char* get_file_name()
{
	if (fname[0] == '\0')
	{
		cout << "Enter file name: ";
		cin >> fname;
	}
	return fname;
}

void add_data_to_file()
{
	fopen_s(&fp, get_file_name(), "ab");
	if (!fp)
	{
		fopen_s(&fp, get_file_name(), "wb");
		if (!fp)
		{
			cout << "File create error." << endl;
			return;
		}
	}

	char chr;
	Flat_Info flat;
	cout << "Enter flat data: " << endl;

	do
	{
		cout << "Flat: "; cin >> flat.number;
		cout << "Owner name: "; cin >> flat.owner_name;
		cout << "Rooms: "; cin >> flat.rooms;
		cout << "Area: "; cin >> flat.area;
		cout << endl;

		fwrite(&flat, sizeof(Flat_Info), 1, fp);

		cout << "Add more? (y/n) ";
		cin >> chr;

	} while (chr == 'y');

	fclose(fp);
}

void read_data_from_file()
{
	fopen_s(&fp, get_file_name(), "rb");
	if (fp)
	{
		int n = _filelength(_fileno(fp)) / sizeof(Flat_Info);
		Flat_Info* flats = new Flat_Info[n];
		fread(flats, sizeof(Flat_Info), n, fp);

		cout << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "Flat " << flats[i].number << ": Owner - " << flats[i].owner_name << ", Rooms - " << flats[i].rooms << ", Area - " << flats[i].area << endl;
		}
		if (n == 0) cout << "Empty." << endl;

		delete[] flats;
		flats = nullptr;

		fclose(fp);
	}
	else cout << "File read error." << endl;
}

void print_result_in_console()
{
	fopen_s(&fp, get_file_name(), "rb");
	if (fp)
	{
		int n = _filelength(_fileno(fp));
		Flat_Info* flats = new Flat_Info[n];
		bool empty = true;
		fread(flats, sizeof(Flat_Info), n, fp);

		cout << "3 rooms flats:" << endl;
		for (int i = 0; i < n; i++)
		{
			if (flats[i].rooms == 3)
			{
				cout << fixed;
				cout.precision(2);
				cout << "Flat " << flats[i].number << ": Owner - " << flats[i].owner_name << ", Area - " << flats[i].area << endl;
				empty = false;
			}
		}
		if (empty) cout << "Empty." << endl;

		fclose(fp);
	}
	else cout << "File read error." << endl;
}

void print_result_in_file()
{
	fopen_s(&fp, get_file_name(), "rb");
	if (fp)
	{
		char fname2[20];
		FILE* fp2;

		cout << "Enter result file name: ";
		cin >> fname2;

		fopen_s(&fp2, fname2, "wt");
		if (fp2)
		{
			int n = _filelength(_fileno(fp));
			bool empty = true;
			Flat_Info* flats = new Flat_Info[n];
			fread(flats, sizeof(Flat_Info), n, fp);

			fprintf(fp2, "3 rooms flats:\n");
			for (int i = 0; i < n; i++)
			{
				if (flats[i].rooms == 3)
				{
					fprintf(fp2, "%s%d%s%s%s%.2f\n", "Flat ", flats[i].number, ": Owner - ", flats[i].owner_name, ", Area - ", flats[i].area);
					empty = false;
				}
			}
			if (empty) fprintf(fp2, "Empty.\n");

			fclose(fp2);
		}
		else cout << "File create error." << endl;

		fclose(fp);
	}
	else cout << "File read error." << endl;
}