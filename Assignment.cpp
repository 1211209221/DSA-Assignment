#include<iostream>
#include <unistd.h>
using namespace std;
class Menus
{
	public:
		Menus()
		{
			cout << "=================================================================================="<<endl;
			cout << "\t        ~WELCOME TO THE SUNRISE 2ND BOOK RENTAL SYSTEM~"<<endl;
			cout << "=================================================================================="<<endl;
			cout << "\t\t\t\tMAIN MENU"<<endl;
		}

		void SearchMenus()
		{
			string choice;

			cout << "=================================================================================="<<endl;
			cout << "\t\t\t\tSEARCH MENU"<<endl;
			cout << "=================================================================================="<<endl;
			cout << "1. Search by Title\n";
			cout << "2. Search by Author\n";
			cout << "3. Search by ISBN\n";
			cout << "4. Search by Genre\n";
			cout << "5. Search by Publisher\n";
			cout << "6. Search by Year\n";
			cout << "7. Search by Price\n";
			cout << "8. Search by Rating\n";
			cout << "9. Search by Availability\n";
			cout << "10. Back to Main Menu\n";

			cout << "Enter your choice: ";
			cin >> choice;
		}
};

int main(){
	Menus client;
	//UsersLinkedList userlist;
    string choice;
	
    //while(true){
    
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
		} else if (choice == "3") {
			cout << "Directing to sort page...\n";
			sleep(1);
		    system("cls");

		} else if (choice == "4") {
			cout << "Thank you for using our system! Goodbye!\n";
		    exit(0);
		    return 0;
		} else {
		    cout << "\nInvalid choice! Please re-enter...\n";
		    sleep(1);
		    system("cls");
		    main();
		}

    //}
    
	return 0;
}
