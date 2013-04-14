/*
Names: Calvin Kwan
CS256 - Project 1 ATM Machine
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//declare the functions
void openFile(string[], string[], int[], double[], double[], int[], int[]);
void saveFile(string[], string[], int[], double[], double[], int[], int[]);
bool authorizeAcc(int, int, double[], double[], int);
void mainScreen(double[], double[], int);


int main()
{
	string fname[10]; 
	string lname[10];
	int pin[10];
	double checkB[10];
	double savingB[10];
	int accNum[10];
	int tmpUserInput[1];
	ifstream inFile;

	openFile(fname, lname, pin, checkB, savingB, accNum, tmpUserInput);
	inFile.open("accounts.txt");

	if(inFile)
	{
		saveFile(fname, lname, pin, checkB, savingB, accNum, tmpUserInput);
	}
	
	inFile.close();
	return 0;
}

void openFile(string fname[], string lname[], int pin[], double checkB[], double savingB[], int accNum[], int tmpUserInput[])
{
	ifstream inFile;
	bool flag = false;
	int counter = 0;
	int acc;

	inFile.open("accounts.txt");

	if(!inFile)
	{
		cout << "File not Found" << endl;
	}
	else
	{
		int i = 0;			
		//read each line
		while(!inFile.eof())
		{
			inFile >> fname[i] >> lname[i] >> pin[i] >> checkB[i] >> savingB[i] >> accNum[i];
			i++;
		}

		while (flag == false)
		{	
			cout << "Enter User Account Number: ";
			cin >> tmpUserInput[0];

	//check if the account matches	
			for (int j = 0; j < 10; j++)
			{
				if(tmpUserInput[0] == accNum[j])
				{
					acc = j;
					flag = authorizeAcc(tmpUserInput[0], pin[j], checkB, savingB, acc);
					if(flag == false)
						counter++;

					if(counter >= 3)
					{
						cout << "The system cannot authenticate you please try again later" << endl;
						exit(1);
					}
				}
			}
		}
	}
	
	inFile.close();
}

bool authorizeAcc(int tmpAccNum, int tmpPin, double tempCB[], double tempSB[], int acc)
{
	bool flag = false;
	int pinEnter;


	cout << "Enter User PIN Number: ";
	cin >> pinEnter;

//must have both account and pin to match before entering menu
	if(pinEnter == tmpPin)
	{
		cout << "Your account matches!!!" << endl;
		flag = true;
		mainScreen(tempCB, tempSB, acc);
	}
		
	else if(!(pinEnter == tmpPin))
	{
		cout << "Account does not match" << endl;
	}

	return flag;
}

void mainScreen(double tempCB[], double tempSB[], int acc)
{
	char accChoice = ' ';
	int choice;
	ifstream inFile;
	int amount = 0;

	do
	{
		cout << "1) Transfer money from saving account to checking account" << endl;
		cout << "2) Transfer money from checking account to saving account" << endl;
		cout << "3) Saving Account Balance" << endl;
		cout << "4) Checking Account Balance" << endl;
		cout << "5) Withdraw cash from either account" << endl;
		cout << "6) Exit" << endl;

		cin >> choice;
		switch (choice)
		{
			case 1:
				//Transfer money from saving account to checking account
				system("cls");
				cout << "How much do you want to transfer from saving account to checking account?: $";
				cin >> amount;
				cout << endl;
				if(amount > tempSB[acc])
					cout << "Transaction failed: not enough money" << endl;
				else
				{
					//temp for saving balance after tranferring
					tempSB[acc] = tempSB[acc] - amount;
					//temp for checking balance after transferring
					tempCB[acc] = tempCB[acc] + amount;
				}
				break;
			case 2:
				//Transfer money from checking account to saving account
				system("cls");
				cout << "How much do you want to transfer from checking account to saving account?: $";
				cin >> amount;
				cout << endl;
				if(amount > tempCB[acc])
					cout << "Transaction failed: not enough money" << endl;
				else
				{
					tempCB[acc] = tempCB[acc] - amount;
					tempSB[acc] = tempSB[acc] + amount;
				}
				break;
			case 3: 
				system("cls");
				cout << "Your Saving Account Balance is: $" << tempSB[acc] << endl;
				//change up the code in case 3 to display Saving Acc Balance
				break;
			case 4:
				system("cls");
				cout << "Your Checking Account Balance is: $" << tempCB[acc] << endl;
				//change up the code in case 3 to display Checking Balance
				break;
			case 5:
				//Withdraw cash from either account
				system("cls");
				cout << "Which account do you want to withdraw from?" << endl;
				cout << "A) Savings Account \nB) Checking Account" << endl;
				cin >> accChoice;
				system("cls");
				if(accChoice == 'A' || accChoice == 'a')
				{
					cout << "Enter amount to withdraw from Saving Account: $";
					cin >> amount;
					if(amount > tempSB[acc])
						cout << "Transaction failed: not enough money" << endl;
					else
						tempSB[acc] = tempSB[acc] - amount;
				}
				else if(accChoice == 'B' || accChoice == 'b')
				{
					cout << "Enter amount to withdraw from Checking Account: $";
					cin >> amount;	
					if(amount > tempCB[acc])
						cout << "Transaction failed: not enough money" << endl;
					else
						tempCB[acc] = tempCB[acc] - amount;
				}
				else
					cout << "invalid choice " << endl;
				break;
			case 6:
				cout << "Thank you for using the ATM system" << endl;
				break;
			default:
				system("cls");
				cout << "Not a valid option" << endl;				
		}
	}while (choice !=6);
	inFile.close();
}

//updates the file
void saveFile(string fname[], string lname[], int pin[], double checkB[], double savingB[], int accNum[], int tmpUserInput[])
{
	ofstream outFile("accounts.txt");

	for(int i = 0; i < 9; i++)
	{
		//saves back to the file
		outFile << fname[i] << " " << lname[i] << " " << pin[i] << " " << checkB[i] << " " << savingB[i] << " " << accNum[i] << endl;
	}

	outFile.close();
}