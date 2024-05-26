#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unistd.h>
using namespace std;
class Menus
{
	public:
		void DisplayList()
		{
			int numEntries = 0;
			string line, id, name, author, genre;
			int stock;
			double price;

			//Get number of entries
			ifstream countFile("books.txt");
			if (countFile.is_open())
			{
			    while (getline(countFile, line))
				{
			        numEntries++;
			    }
			    countFile.close();
			} else {
			    cout << "Error: Unable to open the file 'records/books.txt'\n";
			    exit(0);
			}
		    countFile.close();

			ifstream list ("books.txt");
			cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
			//List Books
			while(list >> id >> name >> price >> stock >> author >> genre)
			{
				replace(name.begin(), name.end(), '%', ' ');
				replace(author.begin(), author.end(), '%', ' ');
				cout << left << setw(5) << id << left << setw(35) << name << left << "RM " << setw(10) << fixed << setprecision(2) << price << left << setw(7) << stock << left << setw(25) << author << left << setw(15) << genre << endl;
			}
			list.close();
		}

		void SortMenus()
		{
			string choice;

			cout << "=================================================================================="<<endl;
			cout << "\t\t\t\tSORT MENU"<<endl;
			cout << "=================================================================================="<<endl;
			DisplayList();
			cout << endl << "How do you like to sort the list?" << endl;
			cout << "1. Sort by Price" << endl;
			//FOR MING DA
			cout << "2. Search by " << endl;
			cout << "3. Back to Main Menu\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice=="1")
			{
				//SORT BY PRICE
			}
			else if (choice=="2")
			{
				//SORT BY AUTHOR
			}
			else if (choice=="3")
			{
				cout << endl << "Going back to main menu..." << endl;
				sleep(1);
				system("cls");
				return;
			}
			else
			{
				cout << "Invalid choice! Please re-enter...\n";
				sleep(1);
				system("cls");
				SortMenus();
			}
		}
};

int main(){
	Menus client;
    string choice;
	
	while (true)
	{
		cout << "=================================================================================="<<endl;
		cout << "\t        ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
		cout << "=================================================================================="<<endl;
		cout << "\t\t\t\tMAIN MENU"<<endl;
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout << "1. BOOKS\n";
        cout << "2. SEARCH\n";
        cout << "3. SORT\n";
        cout << "4. EXIT\n";
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            cout << "D";
            system("cls");
        } else if (choice == "2") {
            cout << "Directing to search page...\n";
            sleep(1);
			system("cls");
			//client.SearchMenus();
        } else if (choice == "3") {
            cout << "Directing to sort page...\n";
            sleep(1);
			system("cls");
			client.SortMenus();
        } else if (choice == "4") {
            cout << "Thank you for using our system! Goodbye!\n";
		    exit(0);
        } else {
            cout << "Invalid choice! Please re-enter...\n";
			sleep(1);
			system("cls");
        }
    }
    
	return 0;
}
