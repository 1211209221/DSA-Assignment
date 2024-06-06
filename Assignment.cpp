#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
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
		// Heapify function to find the max heap
		void heapify(vector<Book>& arr, int n, int i)
		{
			int largest = i; 
			int left = 2 * i + 1; 
			int right = 2 * i + 2; 

			if (left < n && arr[left].price > arr[largest].price)
				largest = left;

			if (right < n && arr[right].price > arr[largest].price)
				largest = right;

			if (largest != i)
			{
				swap(arr[i], arr[largest]);
				heapify(arr, n, largest);
			}
		}

		// Heaping sort function to sort individual buckets
		void heapSort(vector<Book>& b, int n)
		{
			for(int i = n/2-1; i>=0; i--)
			{
				//create max heap
				heapify(b, n, i);
			}
			for(int i = n-1; i>=0; i--)
			{
				//swap 1st node with last node
				swap(b[0],b[i]);
				heapify(b, i, 0);
			}
		} 

		// Bucket Sort to distribute elements into corresponding buckets
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
			// 3) Sort individual buckets using heap sort 
			for (int i = 0; i < n; i++)
			{ 
				//countingSort(b[i], maxPrice);
				heapSort(b[i], b[i].size());
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
		        int compareResult = books[mid].genre.compare(0, keyword.length(), keyword);
		
		        if (compareResult == 0) {
		            // If keyword matches at this position
		            indices.push_back(mid);
		
		            // Check for matches to the left
		            int i = mid - 1;
		            while (i >= 0 && books[i].genre.compare(0, keyword.length(), keyword) == 0) {
		                indices.push_back(i);
		                i--;
		            }
		
		            // Check for matches to the right
		            i = mid + 1;
		            while (i < books.size() && books[i].genre.compare(0, keyword.length(), keyword) == 0) {
		                indices.push_back(i);
		                i++;
		            }
		            break; // All occurrences found
		        } else if (compareResult < 0) {
		            left = mid + 1;
		        } else {
		            right = mid - 1;
		        }
		    }
		    return indices;
		}
		
		
		vector<int> preprocessBadCharacter(const string& pattern) {
		    const int CHARSET_SIZE = 256; // Size of the character set (e.g., ASCII)
		    vector<int> badCharTable(CHARSET_SIZE, -1);
		
		    for (int i = 0; i < pattern.size(); ++i) {
		        badCharTable[pattern[i]] = i;
		    }
		
		    return badCharTable;
		}

		// Function to preprocess the good suffix heuristic
		vector<int> preprocessGoodSuffix(const string& pattern) {
		    int m = pattern.size();
		    vector<int> goodSuffixTable(m + 1, m);
		    vector<int> borderPos(m + 1, 0);
		    int i = m;
		    int j = m + 1;
		
		    borderPos[i] = j;
		    while (i > 0) {
		        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
		            if (goodSuffixTable[j] == m) {
		                goodSuffixTable[j] = j - i;
		            }
		            j = borderPos[j];
		        }
		        i--;
		        j--;
		        borderPos[i] = j;
		    }
		
		    j = borderPos[0];
		    for (i = 0; i <= m; ++i) {
		        if (goodSuffixTable[i] == m) {
		            goodSuffixTable[i] = j;
		        }
		        if (i == j) {
		            j = borderPos[j];
		        }
		    }
		
		    return goodSuffixTable;
		}
		
		// Function to check pattern of the keyword match or not
		bool BoyerMooreSearch(const string& text, const string& pattern) {
		    int n = text.size();
		    int m = pattern.size();
		
		    vector<int> badCharTable = preprocessBadCharacter(pattern);
		    vector<int> goodSuffixTable = preprocessGoodSuffix(pattern);
		
		    int s = 0; // s is the shift of the pattern with respect to the text
		    while (s <= (n - m)) {
		        int j = m - 1;
		
		        while (j >= 0 && pattern[j] == text[s + j]) {
		            j--;
		        }
		
		        if (j < 0) {
		            return true; // pattern found
		            s += goodSuffixTable[0];
		        } else {
		            s += max(goodSuffixTable[j + 1], j - badCharTable[text[s + j]]);
		        }
		    }
		
		    return false; // pattern not found
		}
		
		// Function to search for books containing the keyword in their title
		vector<int> stringSearch(const vector<Book>& books, const string& keyword) {
		    vector<int> indices;
		    for (int i = 0; i < books.size(); ++i) {
		        if (BoyerMooreSearch(books[i].name, keyword)) {
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
			cout << "The current unsorted list of book:"<<endl<<endl;
			cout << left << setw(5) << "No." << left << setw(35) << "Book Name" << left << setw(13) << "Price" << left << setw(7) << "Stock" << left << setw(25) << "Author" << left << setw(15) << "Genre\n" << endl;
			while(list >> b.id >> b.name >> b.price >> b.stock >> b.author >> b.genre)
			{
				b.numEntries++;
				replace(b.name.begin(), b.name.end(), '%', ' ');
				replace(b.author.begin(), b.author.end(), '%', ' ');
				cout << left << setw(5) << b.id << left << setw(35) << b.name << left << "RM " << setw(10) << fixed << setprecision(2) << b.price << left << setw(7) << b.stock << left << setw(25) << b.author << left << setw(15) << b.genre << endl;
			}
			cout<<endl<<"Total Number of Book: "<<b.numEntries<<endl<<endl;
			list.close();
		}

		void SortMenus()
		{
			string choice, line;
			Book b;

			cout << "=============================================================================================="<<endl;
			cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "==============================================================================================" << endl;			
			cout << "\t\t\t\t\tSORT MENU"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
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
				cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
				cout << "==============================================================================================" << endl;			
				cout << "\t\t\t\t\tSORT MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "Displaying list sorted by price:" << endl <<endl;
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
		        cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
				cout << "==============================================================================================" << endl;			
				cout << "\t\t\t\t\tSORT MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "This list sorted by stock:" << endl <<endl;
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

			cout << "=============================================================================================="<<endl;
			cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "==============================================================================================" << endl;
			cout << "\t\t\t\t\tSEARCH MENU"<<endl;
		    cout << "----------------------------------------------------------------------------------------------"<<endl;
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
			    cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
				cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "Search titles: ";
			    getline(cin, target);
				system("cls");
		    	cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
				cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
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
			    cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
				cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
			    cout << "Search genres: ";
			    getline(cin, target);
				system("cls");
				cout << "=============================================================================================="<<endl;
				cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
		    	cout << "==============================================================================================" << endl;
				cout << "\t\t\t\t\tSEARCH MENU"<<endl;
			    cout << "----------------------------------------------------------------------------------------------"<<endl;
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
		
		//yansan
		void BookMenu(){
			string choice;
			fflush(stdin);
			//3 things add, view, main menu
			system("cls");
			cout << "=============================================================================================="<<endl;
			cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "==============================================================================================" << endl;
			cout << "\t\t\t\t\tBOOK MENU"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "[1] Add New Book"<<endl;
			cout << "[2] View List of Book"<<endl;
			cout << "[3] Back to Main Menu"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "Enter your choice: ";
			cin >> choice;
			
			if(choice == "1"){
				//invoke a function to add new book
				addnewbook();
			}
			else if(choice == "2"){
				viewbook();
			}
			else if(choice == "3"){
				cout << endl << "Returning to main menu..." << endl;
				sleep(1);
				system("cls");
				fflush(stdin);
				return;
			}
			else{
				cout << "\nInvalid choice! Please re-enter...\n";
				sleep(1);
				BookMenu();
			}
		}
		
		void saveextrastock(Book* nb,int num){
			ofstream putinfile("books.txt");
		    if (!putinfile) {
		        cout << "Error: Unable to open the file 'books.txt'\n"<< endl;
		        exit(0);
		    }
		
		    for (int i = 0; i < num; i++) {
		        string tempName = nb[i].name;
		        replace(tempName.begin(), tempName.end(), ' ', '%');
		        putinfile << nb[i].id << " " << tempName << " " << fixed << setprecision(2) << nb[i].price << " "
		                  << nb[i].stock << " " << nb[i].author << " " << nb[i].genre << endl;
		    }
		    putinfile.close();	
		}
		
		//to know whether the first letter of id is alphabet 
		bool isValidID(const string& id) {
		    if (id.empty()) {
		        return false; // An empty ID is not valid
		    }
		    return isalpha(id[0]);
		}
		
		//to know genre from id
		string getGenre(const string& id) {
		    if (id.empty()) {
		        return "Invalid ID";
		    }
		
		    char firstChar = toupper(id[0]); // Convert to uppercase to handle both cases
		
		    switch (firstChar) {
		        case 'M': return "Mystery";break;
		        case 'N': return "Fiction";break;
		        case 'X': return "Non-fiction";break;
		        case 'P': return "Philosophy";break;
		        case 'C': return "Classics";break;
		        case 'A': return "Action";break;
		        case 'T': return "Thriller";break;
		        case 'R': return "Children";break;
		        case 'H': return "Horror";break;
		        case 'D': return "Dystopian";break;
		        case 'E': return "Detective";break;
		        case 'I': return "Historical";break;
		        case 'F': return "Fantasy";break;
		        case 'L': return "Romance";break;
		        default: return "Unknown"; 
		    }
		}
		
		void addnewbook(){
			//create struct obj
			Book b; 
			string line, confirm, id, name, author, genre;
			double price;
			int stock;
			string yesno;
			
			fflush(stdin);
			
			system("cls");
			cout << "=============================================================================================="<<endl;
			cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "==============================================================================================" << endl;
			cout << "BOOK MENU > ADD NEW BOOK"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "The first letter of ID that corresponds to the genre:"<<endl;
			cout << left << setw(15) <<"\tM-Mystery" << setw(15) <<"N-Fiction"<< setw(15) <<"X-Non-fiction"<<setw(15) <<"C-Classics"<< setw(15) <<"A-Action"<<endl;
			cout << left << setw(15) <<"\tT-Thriller"<< setw(15) <<"R-Children"<< setw(15) <<"H-Horror"<< setw(15) <<"D-Dystopian"<< setw(15) <<"I-Historical"<<endl;
			cout << left << setw(15) <<"\tF-Fantasy" << setw(15) <<"L-Romance"<< setw(15) <<"P-Philosophy"<< setw(15) <<"E-Detective"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "Please fill the information of new book."<<endl<<endl;
			//open file
			ifstream takefile("books.txt");
			if (takefile.is_open())
		    {
		            while (getline(takefile, line))
		            {
		                b.numEntries++;
		            }
		    }
			else{
				cout<<"Error: Unable to open the file 'books.txt'\n"<<endl;
				exit(0);
			}
			//move to beginning of file
			takefile.clear();
			takefile.seekg(0);
				
			Book nb[b.numEntries];
			
			cout << "Book ID : ";
			getline(cin,id);
			if(id=="0"|| !isValidID(id)){
				cout<<"~ Incorrect format!"<<endl;
				cout << "\nInvalid data! Please re-enter...\n";
				sleep(2);
				addnewbook();
			}
			
			for(int i=0;i<b.numEntries;i++){
				takefile >> nb[i].id >> nb[i].name >> nb[i].price >> nb[i].stock >> nb[i].author >> nb[i].genre;
				if(id==nb[i].id){
					cout<<"\n=>The ID already exists. "<<endl;
					sleep(1);
					addnewbook();
				}
			}
			//move to beginning of file
			takefile.clear();
			takefile.seekg(0);
			
			cout << "Name    : ";
			getline(cin,name);
			if(name == "0"){
				cout<<"\n~ Incorrect format!"<<endl;
				cout << "\nInvalid data! Please re-enter...\n";
				sleep(2);
				addnewbook();
			} 
			else{
				string tempname;
				tempname = name;
				transform(tempname.begin(), tempname.end(), tempname.begin(), ::tolower);
				for(int i=0;i<b.numEntries;i++){
					takefile >> nb[i].id >> nb[i].name >> nb[i].price >> nb[i].stock >> nb[i].author >> nb[i].genre;
					replace(nb[i].name.begin(), nb[i].name.end(), '%', ' ');
					transform(nb[i].name.begin(), nb[i].name.end(), nb[i].name.begin(), ::tolower);
					if(tempname==nb[i].name){
						cout<<"\nThere is a book same name with it"<<endl<<"Do you want to add stock instead of adding new book? [Y/N]: ";
						cin >> yesno;
						
						fflush(stdin);
						if(yesno =="Y"||yesno == "y"){
							int addstock;
							cout<<"\nEnter additional stock: ";
							cin >> addstock;
							
							nb[i].stock += addstock;
							saveextrastock(nb, b.numEntries);
							cout << "----------------------------------------------------------------------------------------------"<<endl;
							DisplayList();
							cout << "----------------------------------------------------------------------------------------------"<<endl;
							cout << "Press any key to go back to the book menu...";
							getch();  // waits for any key press
							system("cls");
							BookMenu();
						}
						else if(yesno == "N" || yesno == "n"){
							cout<<endl;
							break;
						}
						else{
							cout <<"\nInvalid choice. Please re-enter..." << endl;
							sleep(1);
							system("cls");
							addnewbook();
						}
					}
				}
			}
			
			cout << "Price   : RM ";
			cin >> price;
			if(price <= 0){
				cout<<"\n~ Price CANNOT be written as NEGATIVE / ZERO value!"<<endl;
				cout << "\nInvalid data! Please re-enter...\n";
				sleep(2);
				addnewbook();
			} 
			
			cout << "Stock   : ";
			cin >> stock;
			if(stock <= 0){
				cout<<"\n~ Stock CANNOT be written as NEGATIVE / ZERO value!"<<endl;
				cout << "\nInvalid data! Please re-enter...\n";
				sleep(2);
				addnewbook();
			}
			fflush(stdin);
			cout << "Author  : ";
			getline(cin,author);
			if(author == "0"){
				cout<<"~ Incorrect format!"<<endl;
				cout << "\nInvalid data! Please re-enter...\n";
				sleep(2);
				addnewbook();
			}
			fflush(stdin);
			
			genre = getGenre(id);
			
			
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			//confirm
				fflush(stdin);
				cout<<"Enter 'C' to confirm saving, other key to cancel: ";
				cin>>confirm;
				
				//save
				if(confirm == "C" || confirm == "c"){
					//save in file
					//replace space between each string word to %
					replace(author.begin(), author.end(), ' ', '%');
					replace(name.begin(), name.end(), ' ', '%');
					replace(genre.begin(), genre.end(), ' ', '%');
					
					
					ofstream putinfile("books.txt",ios::app);
					if(!putinfile){
						cout<<"Error: Unable to open the file 'books.txt'\n"<<endl;
						exit(0);
					}
					else{
						putinfile <<id <<" "<< name <<" " <<fixed<<setprecision(2)<< price <<" " << stock <<" " << author <<" " << genre <<endl;
						putinfile.close();
					}
					
					//after that , show the list of book
					takefile.close();
					cout<<"\nThe book is added successfully!"<<endl;		
					cout << "----------------------------------------------------------------------------------------------"<<endl;
					DisplayList();
					cout << "----------------------------------------------------------------------------------------------"<<endl;
					cout << "Press any key to go back to the book menu...";
					getch();  // waits for any key press
					system("cls");
					BookMenu();
					
				}
				else if(confirm != "C" && confirm != "c"){
					cout <<"\nReturning to book menu..." << endl;
					sleep(1);
					system("cls");
					BookMenu();
				}
			
		}
		
		void viewbook(){
			
			system("cls");
			cout << "=============================================================================================="<<endl;
			cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "==============================================================================================" << endl;
			cout << "BOOK MENU > VIEW BOOK"<<endl;
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			DisplayList();
			cout << "----------------------------------------------------------------------------------------------"<<endl;
			cout << "Press any key to go back to the book menu...";
			getch();  // waits for any key press
			system("cls");
			BookMenu();    	
        	
		}
		
};


int main(){
	Menus client;
    string choice;
	
	while (true)
	{
		cout << "=============================================================================================="<<endl;
		cout << "\t\t    ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
		cout << "==============================================================================================" << endl;
		cout << "\t\t\t\t\tMAIN MENU"<<endl;
		cout << "----------------------------------------------------------------------------------------------"<<endl;
        cout << "1. BOOKS\n";
        cout << "2. SEARCH (String search + Ubiquitous binary search)\n";
        cout << "3. SORT (Bucket sort + counting sort)\n";
        cout << "4. EXIT\n";
		cout << "----------------------------------------------------------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            cout << "\nDirecting to Book Menu...\n";
            sleep(1);
            client.BookMenu();
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
