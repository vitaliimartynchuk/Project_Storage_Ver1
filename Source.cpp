#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <functional>


using namespace std;

int id = 1;





void funcMenutext()
{
	cout << "\nStorage menu:" << endl;
	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;

	cout << left << setw(21) << "| 1. Show all goods"
		<< setw(18) << "| 2. Add a goods"
		<< setw(21) << "| 3. Edit the goods"
		<< setw(19) << "| 4. Delete Goods"
		<< setw(13) << "| 5. Search"
		<< setw(14) << "| 6. Sorting"
		<< setw(18) << "| 0. Finish work |" << endl;

	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;
}





void headStorage()
{
	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;

	cout << left << setw(9) << "id"
		<< setw(23) << "Name"
		<< setw(19) << "Producer"
		<< setw(18) << "Price"
		<< setw(20) << "Group"
		<< setw(19) << "Date of receipt"
		<< setw(10) << "Expiration date" << endl;

	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;
}





struct Goods
{
	int id;
	string Name;
	string Producer;
	string Price;
	string Group;
	string Date_of_receipt;
	string Expiration_date;





	void fillGoods(Goods& goods)
	{
		cout << "\nEnter goods Name: ";
		getline(cin, goods.Name);
		cout << "\nEnter goods Producer: ";
		getline(cin, goods.Producer);
		cout << "\nEnter goods Price: ";
		getline(cin, goods.Price);
		cout << "\nEnter goods Group: ";
		getline(cin, goods.Group);
		cout << "\nEnter goods Date of receipt: ";
		getline(cin, goods.Date_of_receipt);
		cout << "\nEnter goods Expiration date: ";
		getline(cin, goods.Expiration_date);
	}





	void printGoods()
	{
		cout << left << setw(9) << id
			<< setw(23) << Name
			<< setw(19) << Producer
			<< setw(18) << Price
			<< setw(20) << Group
			<< setw(19) << Date_of_receipt
			<< setw(10) << Expiration_date << endl;
	}
};






struct Storage
{
	int count = 0;
	Goods* goods = new Goods[count];

	void AddGoods(Goods newgoods)
	{
		Goods* tmp = new Goods[count + 1];
		for (int i = 0; i < count; i++)
		{
			tmp[i] = goods[i];
		}
		tmp[count] = newgoods;
		delete[] goods;
		goods = tmp;
		count++;
	}





	void AddGoods_withFile()
	{
		ifstream file;
		string path = "Storage.txt";
		file.open(path);
		if (file.is_open())
		{
			char s;
			string text;
			while (file.get(s))
			{
				text += s;
			}

			int start = 0;
			int lens = text.length();
			int countText = 0;
			Goods newgoods;
			while (start < lens)
			{
				int end = text.find('\n', start);
				string line = text.substr(start, end - start);
				if (countText == 0)
				{
					newgoods.Name = line;
				}
				if (countText == 1)
				{
					newgoods.Producer = line;
				}
				if (countText == 2)
				{
					newgoods.Price = line;
				}
				if (countText == 3)
				{
					newgoods.Group = line;
				}
				if (countText == 4)
				{
					newgoods.Date_of_receipt = line;
				}
				if (countText == 5)
				{
					newgoods.Expiration_date = line;
				}


				if (end < lens)
				{
					start = end + 1;
				}
				else
				{
					start = lens;
				}


				if (countText >= 5)
				{
					newgoods.id = id++;
					AddGoods(newgoods);
					countText = 0;
				}
				else
				{
					countText++;
				}
			}
		}
		else
		{
			cout << "\nStorage.txt is not open!\n";
		}
		file.close();
	}





	void goods_infile()
	{
		string text_infile;
		for (int i = 0; i < count; i++)
		{
			text_infile += goods[i].Name;
			text_infile += "\n";
			text_infile += goods[i].Producer;
			text_infile += "\n";
			text_infile += goods[i].Price;
			text_infile += "\n";
			text_infile += goods[i].Group;
			text_infile += "\n";
			text_infile += goods[i].Date_of_receipt;
			text_infile += "\n";
			text_infile += goods[i].Expiration_date;
			text_infile += "\n";
		}
		ofstream file;
		string path = "Storage.txt";
		file.open(path);
		if (file.is_open())
		{
			file << text_infile;
		}
		else
		{
			cout << "\nStorage.txt is not open!\n";
		}
		file.close();
	}





	void printAllGoods()
	{
		for (int i = 0; i < count; i++)
		{
			goods[i].printGoods();
		}
	}





	void editGoods(int idGoods)
	{
		for (int i = 0; i < count; i++)
		{
			if (goods[i].id == idGoods)
			{
				cout << "\nEnter goods Name: ";
				getline(cin, goods[i].Name);
				cout << "\nEnter goods Producer: ";
				getline(cin, goods[i].Producer);
				cout << "\nEnter goods Price: ";
				getline(cin, goods[i].Price);
				cout << "\nEnter goods Group: ";
				getline(cin, goods[i].Group);
				cout << "\nEnter goods Date_of_receipt: ";
				getline(cin, goods[i].Date_of_receipt);
				cout << "\nEnter goods Expiration_date: ";
				getline(cin, goods[i].Expiration_date);
			}
		}
	}





	void deleteGoods(int idGoods)
	{
		bool found = false;
		for (int i = 0; i < count; i++)
		{
			if (goods[i].id == idGoods)
			{
				found = true;
				for (int j = i; j < count - 1; j++)
				{
					goods[j] = goods[j + 1];
				}

				count--;
				break;
			}
		}
		if (found)
		{
			cout << "\nGoods deleted!\n";
		}
		else
		{
			cout << "\nNot found!\n";
		}
	}





	void findGoods(function<bool(Goods)> pred)
	{
		headStorage();
		for (int i = 0; i < count; i++)
		{
			if (pred(goods[i]))
			{
				goods[i].printGoods();
			}
		}
	}





	void sortGoods(function<bool(Goods, Goods)> pred)
	{
		for (int i = 0; i < count - 1; i++)
		{
			for (int j = i + 1; j < count; j++)
			{
				if (pred(goods[j], goods[i]))
				{
					Goods tmp = goods[i];
					goods[i] = goods[j];
					goods[j] = tmp;
				}
			}
		}
	}
};





void main()
{
	Storage storage;

	storage.AddGoods_withFile();

	int numMenu = 0;
	do
	{
		funcMenutext();
		cout << "Enter number menu: ";
		cin >> numMenu;
		cin.ignore();



		if (numMenu > 6)
		{
			system("cls");
			funcMenutext();
			cout << "Enter number menu: ";
			cin >> numMenu;
			cin.ignore();
		}



		if (numMenu == 1)
		{
			system("cls");
			cout << "Oll Storage" << endl << endl;
			headStorage();
			storage.printAllGoods();
			fill_n(ostream_iterator<char>(cout), 124, '-');
			cout << endl;
		}



		if (numMenu == 2)
		{
			system("cls");

			Goods newgoods;
			newgoods.fillGoods(newgoods);
			newgoods.id = id++;
			storage.AddGoods(newgoods);
			storage.goods_infile();

			system("cls");
			cout << "\nA new goods has been added!" << endl;
			Sleep(2000);
			system("cls");
		}



		if (numMenu == 3)
		{
			int idGoods;
			do
			{
				system("cls");
				cout << "Whot goods you wont edit? (Enter id or Enter Null(0) for back):";
				cin >> idGoods;
				cin.ignore();
			} while (idGoods >= id);

			system("cls");
			storage.editGoods(idGoods);
			storage.goods_infile();

			if (idGoods > 0 && idGoods <= id)
			{
				system("cls");
				cout << "\nThe goods has been changed!" << endl;
				Sleep(2000);
				system("cls");
			}
			else
			{
				system("cls");
				cout << "\nBack!\n";
				Sleep(2000);
				system("cls");
			}
		}



		if (numMenu == 4)
		{
			int idGoods2;
			do
			{
				system("cls");
				cout << "Whot goods you wont delete? (Enter id or Enter Null(0) for back):";
				cin >> idGoods2;
				cin.ignore();
			} while (idGoods2 >= id);

			storage.deleteGoods(idGoods2);
			storage.goods_infile();

			if (idGoods2 > 0 && idGoods2 <= id)
			{
				system("cls");
				cout << "\nThe goods has been deleted!" << endl;
				Sleep(2000);
				system("cls");
			}
			else
			{
				system("cls");
				cout << "\nBack!\n";
				Sleep(2000);
				system("cls");
			}
		}



		if (numMenu == 5)
		{
			system("cls");
			cout << "1. Find goods by Name" << endl;
			cout << "2. Find goods by Producer" << endl;
			cout << "3. Find goods by Price" << endl;
			cout << "4. Find goods by Group" << endl;
			cout << "5. Find goods by Date of receipt" << endl;
			cout << "6. Find goods by Expiration date" << endl;
			cout << "Another number: Exit to the initial menu" << endl;
			int numberFind;
			cout << "Enter search criteria: ";
			cin >> numberFind;
			cin.ignore();

			switch (numberFind)
			{
			case 1:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Name == cinfind; });
			}
			case 2:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Producer == cinfind; });
			}
			case 3:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Price == cinfind; });
			}
			case 4:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Group == cinfind; });
			}
			case 5:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Date_of_receipt == cinfind; });
			}
			case 6:
			{
				string cinfind;
				cout << "Enter name to search: ";
				cin >> cinfind;
				cin.ignore();
				storage.findGoods([&](Goods c) { return c.Expiration_date == cinfind; });
			}
			default:
				break;
			}
		}



		if (numMenu == 6)
		{
			system("cls");
			cout << "1. Sorting goods by Price" << endl;
			cout << "2. Sorting goods by Group" << endl;
			cout << "3. Sorting goods by ID" << endl;
			cout << "Another number: Exit to the initial menu" << endl;
			int numberSort;
			cout << "Enter number menu: ";
			cin >> numberSort;
			cin.ignore();


			switch (numberSort)
			{
			case 1:
			{
				storage.sortGoods([](Goods a, Goods b) {return a.Price < b.Price; });
				storage.goods_infile();
				system("cls");
				cout << "\nGoods are sorted by Price!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			case 2:
			{
				storage.sortGoods([](Goods a, Goods b) {return a.Group < b.Group; });
				storage.goods_infile();
				system("cls");
				cout << "\nGoods are sorted by Group!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			case 3:
			{
				storage.sortGoods([](Goods a, Goods b) {return a.id < b.id; });
				storage.goods_infile();
				system("cls");
				cout << "\nGoods are sorted by ID!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			default:
				break;
			}
		}
	} while (numMenu != 0);
}