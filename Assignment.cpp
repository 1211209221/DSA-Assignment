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
		
		void countingSort(Book arr[], int n)
	    {
	        // Find the maximum stock to determine the range of counting array
	        int maxStock = 0;
	        for (int i = 0; i < n; ++i)
	        {
	            if (arr[i].stock > maxStock)
	                maxStock = arr[i].stock;
	        }
	
	        // Create a counting array to store the count of each stock value
	        int count[maxStock + 1] = {0};
	
	        // Count the occurrences of each stock value
	        for (int i = 0; i < n; ++i)
	        {
	            count[arr[i].stock]++;
	        }
	
	        // Modify the count array to store the actual position of the elements
	        for (int i = 1; i <= maxStock; ++i)
	        {
	            count[i] += count[i - 1];
	        }
	
	        // Create a temporary array to store the sorted elements
	        Book temp[n];
	
	        // Build the sorted array
	        for (int i = n - 1; i >= 0; --i)
	        {
	            temp[count[arr[i].stock] - 1] = arr[i];
	            count[arr[i].stock]--;
	        }
	
	        // Copy the sorted elements back to the original array
	        for (int i = 0; i < n; ++i)
	        {
	            arr[i] = temp[i];
	        }
	    }
	    
		// Function to sort the vector of books by genre first, then by price within each genre using insertion sort
		void insertionSortGenre(vector<Book>& books) {
		    for (int i = 1; i < books.size(); ++i) {
		        Book key = books[i];
		        int j = i - 1;
		        
		        // Sort by genre
		        while (j >= 0 && (books[j].genre > key.genre)) {
		            books[j + 1] = books[j];
		            j--;
		        }
		        books[j + 1] = key;
		    }
		}
		
		vector<int> searchBooksByGenre(const vector<Book>& books, const string& keyword) {
		    vector<int> indices;
		    int left = 0;
		    int right = books.size() - 1;
		
		    while (left <= right) {
		        int mid = left + (right - left) / 2;
		
		        // Compare the keyword with the genre of the book at the middle index
		        if (books[mid].genre < keyword) {
		            left = mid + 1;
		        } else {
		            right = mid - 1;
		        }
		    }
		
		    // Now left points to the first occurrence of the keyword or its immediate greater
		    // element if not found
		    int firstOccurrence = left;
		
		    // Check if the first occurrence matches the keyword
		    if (firstOccurrence < books.size() && books[firstOccurrence].genre == keyword) {
		
		        // Add the index of the first occurrence
		        indices.push_back(firstOccurrence);
		
		        // Search for all occurrences to the right
		        int i = firstOccurrence + 1;
		        while (i < books.size() && books[i].genre == keyword) {
		            indices.push_back(i);
		            i++;
		        }
		    }
		
		    return indices;
		}
		
		// Function to check if the keyword is contained in the title
		bool containsKeyword(const string& str, const string& keyword) {
		    int keywordLength = keyword.length();
		    int strLength = str.length();
		    for (int i = 0; i <= strLength - keywordLength; ++i) {
		        int j;
		        for (j = 0; j < keywordLength; ++j) {
		            if (str[i + j] != keyword[j])
		                break;
		        }
		        if (j == keywordLength)
		            return true; // keyword found
		    }
		    return false; // keyword not found
		}
		
		// Function to search for books containing the keyword in their title
		vector<int> stringSearch(const vector<Book>& books, const string& keyword) {
		    vector<int> indices;
		    for (int i = 0; i < books.size(); ++i) {
		        if (containsKeyword(books[i].name, keyword)) {
		            indices.push_back(i);
		        }
		    }
		    return indices;
		}
		
		void DisplayList()
		{
			Book b;
			//Display List of Books
			ifstream list ("books.txt");
			cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre\n" << endl;
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
			cout << "\t\t\t\t\tSORT MENU"<<endl;
			cout << "==============================================================================================" << endl;
			DisplayList();
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "[1] Sort by Price" << endl;
			cout << "[2] Sort by Stock" << endl;
			cout << "[3] Back to Main Menu\n";
			cout << "----------------------------------------------------------------------------------------------"<<endl;
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
				system("cls");
				cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSORT MENU"<<endl;
				cout << "==============================================================================================" << endl;
				cout << "Displaying list sorted by price:" << endl;
				cout << "----------------------------------------------------------------------------------------------"<<endl;
				cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
				for (int i = 0; i < b.numEntries; i++)
				{
					cout << left << setw(5) << bs[i].id << left << setw(35) << bs[i].name << left << "RM " << setw(10) << fixed << setprecision(2) << bs[i].price << left << setw(7) << bs[i].stock << left << setw(25) << bs[i].author << left << setw(15) << bs[i].genre << endl;
				}
				cout << "----------------------------------------------------------------------------------------------"<<endl;
				cout << "Press any key to go back to sort menu...";
				cin.ignore();  //clear buffer
				getch();  // waits for any key press
				system("cls");
				SortMenus();
			}
			else if (choice=="2")
			{
				// Recalculate number of entries for sorting by stock
		        ifstream countFile("books.txt");
		        if (countFile.is_open())
		        {
		            while (getline(countFile, line))
		            {
		                b.numEntries++;
		            }
		            countFile.close();
		        }
		        else
		        {
		            cout << "Error: Unable to open the file 'books.txt'\n";
		            exit(0);
		        }
		
		        // Read books from file and create array
		        Book bs[b.numEntries];
		        // Insert books into array
		        ifstream list("books.txt");
		        for (int i = 0; i < b.numEntries; i++)
		        {
		            list >> bs[i].id >> bs[i].name >> bs[i].price >> bs[i].stock >> bs[i].author >> bs[i].genre;
		            replace(bs[i].name.begin(), bs[i].name.end(), '%', ' ');
		            replace(bs[i].author.begin(), bs[i].author.end(), '%', ' ');
		        }
		        list.close();
		
		        // Perform counting sort by stock
		        countingSort(bs, b.numEntries);
		
		        // Display the sorted results
		        system("cls");
				cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSORT MENU"<<endl;
				cout << "==============================================================================================" << endl;
			    cout << "This list sorted by stock:" << endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
			    for (int i = 0; i < b.numEntries; i++)
			    {
			        cout << left << setw(5) << bs[i].id << left << setw(35) << bs[i].name << left << "RM " << setw(10) << fixed << setprecision(2) << bs[i].price << left << setw(7) << bs[i].stock << left << setw(25) << bs[i].author << left << setw(15) << bs[i].genre << endl;
				}
				cout << "----------------------------------------------------------------------------------------------"<<endl;
				cout << "Press any key to go back to sort menu...";
				cin.ignore();
				getch();  // waits for any key press
				system("cls");
				SortMenus();
			}
			else if (choice=="3")
			{
				cout << endl << "Returning to main menu..." << endl;
				sleep(1);
				system("cls");
				return;
			}
			else
			{
				cout << "\nInvalid choice! Please re-enter...\n";
				sleep(1);
				system("cls");
				SortMenus();
			}
		}
		
		void SearchMenus()
		{
			string choice, line;
			Book b;

			cout << "==============================================================================================" << endl;
			cout << "\t\t\t\t\tSEARCH MENU"<<endl;
			cout << "==============================================================================================" << endl;
			DisplayList();
			
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "[1] Search by Book Title" << endl;
			cout << "[2] Search by Genre" << endl;
			cout << "[3] Back to Main Menu\n";
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "Enter your choice: ";
			cin >> choice;
			cin.ignore();
			
			if (choice=="1")
			{
				ifstream countFile("books.txt");
			    if (!countFile.is_open()) {
			        cout << "Error: Unable to open the file 'books.txt'\n";
			    }
			
			    string line;
			    int numEntries = 0;
			    while (getline(countFile, line)) {
			        numEntries++;
			    }
			    countFile.close();
			
			    vector<Book> bs(numEntries);
			
			    ifstream list("books.txt");
			    for (int i = 0; i < numEntries; i++) {
			        list >> bs[i].id >> bs[i].name >> bs[i].price >> bs[i].stock >> bs[i].author >> bs[i].genre;
			        // Replace '%' with space in book name and author
			        replace(bs[i].name.begin(), bs[i].name.end(), '%', ' ');
			        replace(bs[i].author.begin(), bs[i].author.end(), '%', ' ');
			    }
			    list.close();
				
			    // Ask the user for the target string
			    string target;
			    system("cls");
			    cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
				cout << "==============================================================================================" << endl;
			    cout << "Search titles: ";
			    getline(cin, target);
				system("cls");
		    	cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
				cout << "==============================================================================================" << endl;
			    vector<int> indices = stringSearch(bs, target);
			    cout << "Showing " << indices.size() << " result(s) for '" << target << "':" << endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
			    if (!indices.empty()) {
					cout << "" << endl;
				    for (size_t i = 0; i < indices.size(); ++i) {
				        cout << left << setw(5) << bs[indices[i]].id << left << setw(35) << bs[indices[i]].name << left << "RM " << setw(10) << fixed << setprecision(2) << bs[indices[i]].price << left << setw(7) << bs[indices[i]].stock << left << setw(25) << bs[indices[i]].author << left << setw(15) << bs[indices[i]].genre << endl;
				    }
				    
				} else {
				    cout << "\n\n\n\t\t\t\t\tNo results...\n\n\n"<< endl;
				}

			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "Press any key to go back to the search menu...";
				getch();  // waits for any key press
				system("cls");
				SearchMenus();
			}
			else if (choice=="2")
			{
				ifstream countFile("books.txt");
			    if (!countFile.is_open()) {
			        cout << "Error: Unable to open the file 'books.txt'\n";
			    }
			
			    string line;
			    int numEntries = 0;
			    while (getline(countFile, line)) {
			        numEntries++;
			    }
			    countFile.close();
			
			    vector<Book> bs(numEntries);
			
			    ifstream list("books.txt");
			    for (int i = 0; i < numEntries; i++) {
			        list >> bs[i].id >> bs[i].name >> bs[i].price >> bs[i].stock >> bs[i].author >> bs[i].genre;
			        // Replace '%' with space in book name and author
			        replace(bs[i].name.begin(), bs[i].name.end(), '%', ' ');
			        replace(bs[i].author.begin(), bs[i].author.end(), '%', ' ');
			    }
			    list.close();
				
				insertionSortGenre(bs);
				
			    // Ask the user for the target string
			    string target;
			    system("cls");
			    cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
				cout << "==============================================================================================" << endl;
			    cout << "Search genres: ";
			    getline(cin, target);
				system("cls");
		    	cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
				cout << "==============================================================================================" << endl;
			    vector<int> indices = searchBooksByGenre(bs, target);
			    cout << "Showing " << indices.size() << " result(s) for the genre '" << target << "':" << endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre" << endl;
			    if (!indices.empty()) {
					cout << "" << endl;
				    for (size_t i = 0; i < indices.size(); ++i) {
				        cout << left << setw(5) << bs[indices[i]].id << left << setw(35) << bs[indices[i]].name << left << "RM " << setw(10) << fixed << setprecision(2) << bs[indices[i]].price << left << setw(7) << bs[indices[i]].stock << left << setw(25) << bs[indices[i]].author << left << setw(15) << bs[indices[i]].genre << endl;
				    }
				    
				} else {
				    cout << "\n\n\n\t\t\t\t\tNo results...\n\n\n"<< endl;
				}

			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "Press any key to go back to the search menu...";
				getch();  // waits for any key press
				system("cls");
				SearchMenus();
			}
			else if (choice=="3")
			{
				cout << endl << "Returning to main menu..." << endl;
				sleep(1);
				system("cls");
				return;
			}
			else
			{
				cout << "\nInvalid choice! Please re-enter...\n";
				sleep(1);
				system("cls");
				SearchMenus();
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
        cout << "2. SEARCH (String search + Ubiquitous binary search)\n";
        cout << "3. SORT (Bucket sort + counting sort)\n";
        cout << "4. EXIT\n";
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            cout << "D";
            system("cls");
        } else if (choice == "2") {
            cout << "\nDirecting to search page...\n";
            sleep(1);
			system("cls");
			client.SearchMenus();
        } else if (choice == "3") {
            cout << "\nDirecting to sort page...\n";
            sleep(1);
			system("cls");
			client.SortMenus();
        } else if (choice == "4") {
            cout << "\nThank you for using our system! Goodbye!\n";
		    exit(0);
        } else {
            cout << "\nInvalid choice! Please re-enter...\n";
			sleep(1);
			system("cls");
        }
    }

	return 0;
}
