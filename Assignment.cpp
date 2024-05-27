#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector> 
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
			    cout << "Error: Unable to open the file 'books.txt'\n";
			    exit(0);
			}
		    countFile.close();
		    
			//Display List of Books
			ifstream list ("books.txt");
			cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
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
			cout << "2. Sort by " << endl;
			cout << "3. Back to Main Menu\n";
			cout << "Enter your choice: ";
			cin >> choice;
			if (choice=="1")
			{
				//SORT BY PRICE USING BUCKET SORT
				//Get number of entries
				int i=0, numEntries, stock;
				double price;
				string line, id, name, author, genre;
				ifstream countFile("books.txt");
				if (countFile.is_open())
				{
				    while (getline(countFile, line))
					{
				        numEntries++;
				    }
				    countFile.close();
				} else {
				    cout << "Error: Unable to open the file 'books.txt'\n";
				    exit(0);
				}
			    countFile.close();
			    double arr[numEntries];
			    //Insert into array
			    ifstream list ("books.txt");
				while(list >> id >> name >> price >> stock >> author >> genre)
				{
					arr[i] = price;
					i++;
				}
				list.close();
				int n = sizeof(arr) / sizeof(arr[0]);
				bucketSort(arr,n);
				cout << "Sorted array: \n"; 
			    cout << "-------------" << endl; 
			    for (int i = 0; i < n; i++)
				{ 
			        cout << arr[i] << " "; 
			    } 
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
		
		// Insertion sort function to sort individual buckets 
		void insertionSort(vector<float>& bucket)
		{ 
			for (int i = 1; i < bucket.size(); ++i)
			{ 
        		float key = bucket[i]; 
        		int j = i - 1; 
		        while (j >= 0 && bucket[j] > key)
				{ 
		            bucket[j + 1] = bucket[j]; 
		            j--; 
		        } 
		        bucket[j + 1] = key; 
		    } 
		} 

		// Function to sort arr[] of size n using bucket sort 
		void bucketSort(float arr[], int n)
		{ 
		    // 1) Create n empty buckets 
		    vector<float> b[n]; 
		    // 2) Put array elements in different buckets 
		    for (int i = 0; i < n; i++)
			{ 
		        int bi = n * arr[i]; 
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