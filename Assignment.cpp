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
};

int main(){
	Menus client;
	//UsersLinkedList userlist;
    string choice;
	
    //while(true){
    
    	cout << "----------------------------------------------------------------------------------"<<endl;
        cout << "1. BOOKS\n";
        cout << "2. ASSIGNMENT\n";
        cout << "4. EXIT\n";
    	cout << "----------------------------------------------------------------------------------"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
		if (choice == "1") {
		    system("cls");
		} else if (choice == "2") {
		    system("cls");
		} else if (choice == "3") {
		    system("cls");
		} else if (choice == "4") {
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
