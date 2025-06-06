#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "MyString.h";
#include "ClientMethods.h";



using namespace std;
using namespace cl;
using namespace str;
using namespace num;

enum enMainChoice { ShowC = 1, AddC = 2, DeleteC = 3, UpdateC = 4, FindC = 5, Transactions = 6, Exit = 7 };

enum enTransactionChoice { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };


//void PerformMainMenueChoice(enMainChoice WhatChoice);

void ShowMainMenueScreen();

void ShowTransactionMenueScreen();

void BackToMainMenue() {

	cout << "\n\n\nPress Any Key to back to main menue...";
	system("pause > 0");
	ShowMainMenueScreen();

}

void AddClientScreen(vector <stClient> vClients) {

	cout << "========================================\n";
	cout << "           Add Client Screen            \n";
	cout << "========================================\n";
	AddClients();

}

void DeleteClientScreen(vector <stClient> vClients) {


	string AccNum;
	cout << "========================================\n";
	cout << "          Delete Client Screen           \n";
	cout << "========================================\n";

	AccNum = str::EnterString("Please Enter Accout number ? ");
	DeleteClientWithAccNumber(AccNum, vClients);


}

void UpdateClientScreen(vector <stClient> vClients) {

	string AccNum;
	cout << "========================================\n";
	cout << "          Update Client Screen           \n";
	cout << "========================================\n";

	AccNum = str::EnterString("Please Enter Accout number ? ");

	UpdateClientByAccNumber(AccNum, vClients);

}

void FindClientScreen(vector <stClient> vClients) {


	string AccNum;
	stClient Client;
	cout << "========================================\n";
	cout << "           Find Client Screen            \n";
	cout << "========================================\n";

	AccNum = str::EnterString("Please Enter Accout number ? ");

	if (FindClientByAccNumber(AccNum, vClients, Client)) {

		DisplayClientData(Client);

	}
	else
		cout << "Client With Account Number (" << AccNum << ") Not Found!\n";

}

void ExitScreen() {
	cout << "========================================\n";
	cout << "             Program Ends :-)            \n";
	cout << "========================================\n";
	system("pause > 0");
}

void BackToTransactionMenue() {

	cout << "\n\n\nPress Any Key to back to Transactions menue...";
	system("pause > 0");
	ShowTransactionMenueScreen();

}

bool DepositBalanceByAccNumber(string AccNumber, int Amount, vector <stClient>& vClients) {

	stClient Client;
	char Ans;

	Ans = str::EnterChar("Are you Sure You want to perform this Transaction ? ");
	if (tolower(Ans) == 'y') {

		for (stClient& C : vClients) {

			if (C.AccNumber == AccNumber) {

				C.Balance += Amount;
				cout << "Done Successfully, New Blance = " << C.Balance << endl;
				break;

			}

		}
		SaveClientsDataToFile(ClientsDataFile, vClients);
		return true;

	}
	else
		return false;

}

bool WithdrawBalanceByAccNumber(string AccNumber, int Amount, vector <stClient>& vClients) {

	stClient Client;
	char Ans;

	Ans = str::EnterChar("Are you Sure You want to perform this Transaction ? ");
	if (tolower(Ans) == 'y') {

		for (stClient& C : vClients) {

			if (C.AccNumber == AccNumber) {
				C.Balance -= Amount;
				cout << "Done Successfully, New Blance = " << C.Balance << endl;
				break;

			}

		}
		SaveClientsDataToFile(ClientsDataFile, vClients);
		return true;

	}
	else
		return false;

}

void DepositMenueScreen() {

	cout << "========================================\n";
	cout << "          Deposit Menue Screen           \n";
	cout << "========================================\n\n";

	vector <stClient> vClients = GetClientsDataFromFile(ClientsDataFile);
	stClient Client;

	string AccNumber = str::EnterString("Please Enter Account Number ? ");

	int Amount;
	while (!FindClientByAccNumber(AccNumber, vClients, Client))
	{
		cout << "Client (" << AccNumber << ") Not Exist! \n";
		AccNumber = str::EnterString("Please Enter Account Number ? ");
	}
	DisplayClientData(Client);
	Amount = num::ReadNumber("Please Enter Amount ? ");

	DepositBalanceByAccNumber(AccNumber, Amount, vClients);

}

void WithdrawMenueScreen() {
	cout << "========================================\n";
	cout << "         Withdraw Menue Screen           \n";
	cout << "========================================\n\n";

	vector <stClient> vClients = GetClientsDataFromFile(ClientsDataFile);
	stClient Client;

	string AccNumber = str::EnterString("Please Enter Account Number ? ");

	while (!FindClientByAccNumber(AccNumber, vClients, Client)) {

		cout << "Client (" << AccNumber << ") Not Exist! \n";
		AccNumber = str::EnterString("Please Enter Account Number ? ");
	}

	DisplayClientData(Client);
	int Amount = num::ReadNumber("Please Enter Amount ? ");

	while (Amount > Client.Balance) {
		cout << "\nSorry Your Balanc is not Enough !\n";
		Amount = num::ReadNumber("Please Enter Another Amount ? ");
	}

	WithdrawBalanceByAccNumber(AccNumber, Amount, vClients);

}

void DisplayClientsBalances(vector <stClient> vClients) {

	int TotalBalances = 0;
	for (stClient& C : vClients)
	{
		cout << "| " << left << setw(15) << C.AccNumber;
		cout << "| " << left << setw(35) << C.Name;
		cout << "| " << left << setw(12) << C.Balance;
		cout << endl;
		TotalBalances += C.Balance;
	}
	cout << "________________________________________________________________________________________\n";

	cout << "\n\t\tTotal Balances = " << TotalBalances << endl;

}

void TotalBalancesMenueScreen() {

	vector <stClient> vClients = GetClientsDataFromFile(ClientsDataFile);

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(35) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________\n" << endl;

	if (vClients.size() > 0) {

		DisplayClientsBalances(vClients);
	}
	else
		cout << "\t\t\t\tNo Clients Available in the System !";


}

void PerformTransactionMenueChoice(enTransactionChoice WhatChoice) {

	switch (WhatChoice)
	{
	case eDeposit:
		system("cls");
		DepositMenueScreen();
		BackToTransactionMenue();
		break;
	case eWithdraw:
		system("cls");
		WithdrawMenueScreen();
		BackToTransactionMenue();
		break;
	case eTotalBalances:
		system("cls");
		TotalBalancesMenueScreen();
		BackToTransactionMenue();
		break;
	case eMainMenue:
		ShowMainMenueScreen();
		break;
	default:
		break;
	}

}

void ShowTransactionMenueScreen() {
	system("cls");

	cout << "========================================\n";
	cout << "        Transaction Menue Screen         \n";
	cout << "========================================\n";
	cout << "       [1] Deposit. \n";
	cout << "       [2] Withdraw. \n";
	cout << "       [3] TotalBalances. \n";
	cout << "       [4] Main Menue. \n";
	cout << "========================================\n";
	PerformTransactionMenueChoice((enTransactionChoice)num::ReadNumber("Chose what do you want to do ? [1 to 4] ?"));
}

void PerformMainMenueChoice(enMainChoice WhatChoice) {

	vector <stClient> vClients = GetClientsDataFromFile(ClientsDataFile);

	switch (WhatChoice)
	{
	case enMainChoice::ShowC:
		system("cls");
		cl::ShowAllClients(vClients);
		BackToMainMenue();
		break;
	case enMainChoice::AddC:
		system("cls");
		AddClientScreen(vClients);
		BackToMainMenue();
		break;
	case enMainChoice::DeleteC:
		system("cls");
		DeleteClientScreen(vClients);
		BackToMainMenue();
		break;
	case enMainChoice::UpdateC:
		system("cls");
		UpdateClientScreen(vClients);
		BackToMainMenue();
		break;
	case enMainChoice::FindC:
		system("cls");
		FindClientScreen(vClients);
		BackToMainMenue();
		break;
	case enMainChoice::Transactions:
		system("cls");
		ShowTransactionMenueScreen();
		BackToMainMenue();
		break;
	case enMainChoice::Exit:
		system("cls");
		ExitScreen();
		break;

	default:
		ShowMainMenueScreen();
		break;
	}

}

void ShowMainMenueScreen() {

	system("cls");
	cout << "========================================\n";
	cout << "            Main Menue Screen            \n";
	cout << "========================================\n";
	cout << "       [1] Show Client List. \n";
	cout << "       [2] Add New Client. \n";
	cout << "       [3] Delete Client. \n";
	cout << "       [4] Update Client. \n";
	cout << "       [5] Find Client. \n";
	cout << "       [6] Transactions. \n";
	cout << "       [7] Exit. \n";
	cout << "========================================\n";

	PerformMainMenueChoice((enMainChoice)num::ReadNumber("Chose what do you want to do ? [1 to 6] ? "));


}





int main() {

	ShowMainMenueScreen();


	system("pause>0");
	return 0;
}


