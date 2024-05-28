#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <unistd.h>
using namespace std;

struct Book
{
	string id, name, author, genre;
	double price;
	int stock, numEntries = 0;
};

class Menus
{
	public:
		// Insertion sort function to sort individual buckets 
		void insertionSort(vector<Book>& bucket)
		{ 
			for (int i = 1; i < bucket.size(); ++i)
			{ 
				Book key = bucket[i]; 
				int j = i - 1; 
				while (j >= 0 && bucket[j].price > key.price)
				{ 
					bucket[j + 1] = bucket[j]; 
					j--; 
				} 
				bucket[j + 1] = key; 
			} 
		} 

		// Function to sort arr[] of size n using bucket sort 
		void bucketSort(Book arr[], int n, double maxPrice)
		{ 
			// 1) Create n empty buckets 
			vector<Book> b[n];
			// 2) Put array elements in different buckets
			for (int i = 0; i < n; i++)
			{ 
				// To make the price range from 0 to 1 (uniformly distributed)
				int bi = (n-1) * (arr[i].price / maxPrice);  
				//push_back means add the current element arr[i] to the end of the bucket b[bi]
				b[bi].push_back(arr[i]);
			} 
			// 3) Sort individual buckets using insertion sort 
			for (int i = 0; i < n; i++)
			{ 
				insertionSort(b[i]);
			} 
			// 4) Concatenate all buckets into arr[] 
			int index = 0; 
			for (int i = 0; i < n; i++) 
			{ 
				for (int j = 0; j < b[i].size(); j++)
				{ 
					arr[index++] = b[i][j]; 
				}
			}
		} 
		
		void DisplayList()
		{
			Book b;
			//Display List of Books
			ifstream list ("books.txt");
			cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
			while(list >> b.id >> b.name >> b.price >> b.stock >> b.author >> b.genre)
			{
				replace(b.name.begin(), b.name.end(), '%', ' ');
				replace(b.author.begin(), b.author.end(), '%', ' ');
				cout << left << setw(5) << b.id << left << setw(35) << b.name << left << "RM " << setw(10) << fixed << setprecision(2) << b.price << left << setw(7) << b.stock << left << setw(25) << b.author << left << setw(15) << b.genre << endl;
			}
			list.close();
		}

		void SortMenus()
		{
			string choice, line;
			Book b;

			cout << "==============================================================================================" << endl;
			cout << "\t\t\t\tSORT MENU"<<endl;
			cout << "==============================================================================================" << endl;
			DisplayList();
			cout << endl << "How do you like to sort the list?" << endl;
			cout << "1. Sort by Price" << endl;
			//FOR MING DA
			cout << "2. Sort by " << endl;
			cout << "3. Back to Main Menu\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice=="1")
			{
				//Calculate number of entries
				ifstream countFile("books.txt");
				if (countFile.is_open())
				{
					while (getline(countFile, line))
					{
						b.numEntries++;
					}
					countFile.close();
				} else {
					cout << "Error: Unable to open the file 'books.txt'\n";
					exit(0);
				}
				Book bs[b.numEntries];
				//Insert into Array
				ifstream list("books.txt");
				for (int i = 0; i < b.numEntries; i++)
				{
					list >> bs[i].id >> bs[i].name >> bs[i].price >> bs[i].stock >> bs[i].author >> bs[i].genre;
					replace(bs[i].name.begin(), bs[i].name.end(), '%', ' ');
					replace(bs[i].author.begin(), bs[i].author.end(), '%', ' ');
				}
				list.close();
				// Will be used at bucketSort function
				double maxPrice = 0.0;
				for (int i = 0; i < b.numEntries; i++)
				{
					if (bs[i].price > maxPrice)
					{
						maxPrice = bs[i].price;
					}
				}
				bucketSort(bs, b.numEntries, maxPrice);
				// Display the sorted results
				cout << endl << "This is the sorted list of books by price:" << endl;
				cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
				for (int i = 0; i < b.numEntries; i++)
				{
					cout << left << setw(5) << bs[i].id << left << setw(35) << bs[i].name << left << "RM " << setw(10) << fixed << setprecision(2) << bs[i].price << left << setw(7) << bs[i].stock << left << setw(25) << bs[i].author << left << setw(15) << bs[i].genre << endl;
				}
				cout << "Press any key to go back to sort menu...";
				cin.ignore();  //clear buffer
				getch();  // waits for any key press
				system("cls");
				SortMenus();
			}
			else if (choice=="2")
			{
				//SORT BY 
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