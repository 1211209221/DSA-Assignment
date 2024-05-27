#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector> 
#include <unistd.h>
using namespace std;

struct Book
{
	string id, name, author, genre;
	double price;
	int stock, numEntries = 0;
};

// Insertion sort function to sort individual buckets 
		void insertionSort(vector<Book>& bucket)
		{ 
			cout << "Sorting..." << endl;
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

int main ()
{
	Book b;
	string line;
	//Display List of Books
	DisplayList();
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
	// To make the price range from 0 to 1 (uniformly distributed)
	double maxPrice = 0.0;
	for (int i = 0; i < b.numEntries; i++)
	{
		if (bs[i].price > maxPrice)
		{
			maxPrice = bs[i].price;
		}
	}
	bucketSort(bs, b.numEntries, maxPrice);
	//Revert back to the original values
	/*for (int i = 0; i < b.numEntries; i++)
	{
		cout << bs[i].price << endl;
		cout << maxPrice << endl;
		bs[i].price *= maxPrice;
	}*/
	// Display the sorted results
	for (int i = 0; i < b.numEntries; i++)
	{
		cout << bs[i].id << " " << bs[i].name << " " << bs[i].price << " " << bs[i].stock << " " << bs[i].author << " " << bs[i].genre << endl;
	}
}
/*



*/