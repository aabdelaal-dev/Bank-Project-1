#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "MyString.h";



using namespace std;

struct stClient {
	string AccNumber;
	string PinCode;
	string Name;
	string Phone;
	int Balance = 0;
	bool MarkForDelete = false;
};
const string ClientsDataFile = "Clients.txt";

namespace cl {


	string ConvertRecordToLine(stClient Client, string Separator = "#//#") {

		string stClientRecord;

		stClientRecord += Client.AccNumber + Separator;
		stClientRecord += Client.PinCode + Separator;
		stClientRecord += Client.Name + Separator;
		stClientRecord += Client.Phone + Separator;
		stClientRecord += to_string(Client.Balance);

		return stClientRecord;
	}

	stClient ConvertLineToRecord(string Line, string  delim = "#//#") {

		stClient Client;
		vector <string> vRecord = str::SplitString(Line, delim);

		Client.AccNumber = vRecord[0];
		Client.PinCode = vRecord[1];
		Client.Name = vRecord[2];
		Client.Phone = vRecord[3];
		Client.Balance = stoi(vRecord[4]);

		return Client;
	}

	void DisplayClientData(stClient C) {

		cout << "\n\n the folowing are the client details   \n";
		//cout<<"========================================"
		cout << "----------------------------------------\n";
		cout << "Account number : " << C.AccNumber << endl;
		cout << "PinCode        : " << C.PinCode << endl;
		cout << "Phone Number   : " << C.Phone << endl;
		cout << "Name           : " << C.Name << endl;
		cout << "Balance        : " << C.Balance << endl;
		cout << "----------------------------------------\n\n";

	}

	void SaveDataLineToFile(string FileName, string DataLine) {


		fstream File;

		File.open(FileName, ios::out | ios::app);
		if (File.is_open()) {
			File << DataLine << "\n";
			File.close();
		}

	}

	bool FindClientByAccNumber(string AccNumber, vector <stClient> vClients, stClient& Client) {


		for (stClient& C : vClients)
		{
			if (C.AccNumber == AccNumber) {
				Client = C;
				return true;
			}

		}
		return false;
	}

	bool IsClientExistByAccNumber(string AccNumber, string FileName) {

		fstream file;
		stClient Client;
		string Line;
		file.open(FileName, ios::in);//read mode

		if (file.is_open()) {

			while (getline(file, Line)) {

				Client = ConvertLineToRecord(Line);

				if (Client.AccNumber == AccNumber) {
					file.close();
					return true;
				}
			}
			file.close();
			
		}
		return false;

	}

	vector <stClient> GetClientsDataFromFile(string FileName) {

		fstream ClientFile;
		string Line;
		vector <stClient> vClients;


		ClientFile.open(FileName, ios::in);

		while (getline(ClientFile, Line)) {

			vClients.push_back(ConvertLineToRecord(Line));

		}
		ClientFile.close();
		return vClients;

	}

	stClient FillClientData() {

		stClient Client;
		cout << "Please Enter Client Data \n" << endl;

		string AccNumber;
		vector <stClient> vClients = GetClientsDataFromFile(ClientsDataFile);

		AccNumber = str::EnterString("Enter Account number : ");

		while (IsClientExistByAccNumber(AccNumber,ClientsDataFile))//ClientExistByAccNumber()
		{
			cout << "Client with [" << AccNumber << "] is Already Exist, Enter Another Acc Number ? ";
			AccNumber = str::EnterString();
		}

		Client.AccNumber = AccNumber;
		Client.PinCode = str::EnterString("Enter PinCode : ");
		Client.Name = str::EnterString("Enter Name : ");
		Client.Phone = str::EnterString("Enter Phone Number : ");
		Client.Balance = num::ReadNumber("Enter Your Balance : ");

		return Client;



	}

	void AddNewClient() {

		stClient Client;
		Client = FillClientData();
		SaveDataLineToFile(ClientsDataFile, ConvertRecordToLine(Client));

	}

	void AddClients() {


		char AddMore = 'N';
		do
		{
			system("CLS");

			AddNewClient();

			cout << "Client Added successfully, Do You Want to add more Clients ? ";

			cin >> AddMore;
			//cin.ignore();

		} while (toupper(AddMore) == 'Y');

	}

	void DisplayClientRecord(stClient C) {


		cout << "| " << setw(15) << left << C.AccNumber;
		cout << "| " << setw(10) << left << C.PinCode;
		cout << "| " << setw(40) << left << C.Name;
		cout << "| " << setw(12) << left << C.Phone;
		cout << "| " << setw(12) << left << C.Balance;

	}

	void ShowAllClients(vector <stClient> ClientsData) {

		system("CLS");

		cout << "\n\t\t\t\t\tClient List (" << ClientsData.size() << ")Client(s).";

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(12) << "Balance";
		cout <<
			"\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if(ClientsData.size() > 0 )
		{
			for (stClient& Client : ClientsData)
			{
				DisplayClientRecord(Client);
				cout << endl;
			}
		}
		else
			cout << "\t\t\t\tNo Clients Data Available!";
		cout<<"\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

	vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient> vClients) {

		fstream file;

		file.open(FileName, ios::out); //write mode and delete old file.
		if (file.is_open()) {

			for (stClient& C : vClients) {

				if (C.MarkForDelete == false) {
					SaveDataLineToFile(FileName, ConvertRecordToLine(C));
				}

			}

		}file.close();
		return vClients;

	}

	bool MarkClientForDelete(string AccNumber, vector <stClient>& vClients) {

		for (stClient& C : vClients)
		{

			if (C.AccNumber == AccNumber) {
				C.MarkForDelete = true;
				return true;
			}

		}
		return false;

	}

	bool DeleteClientWithAccNumber(string AccNumber, vector <stClient>& vClients) {

		stClient Client;

		char Answer = 'n';
		if (FindClientByAccNumber(AccNumber, vClients, Client)) {

			DisplayClientData(Client);
			cout << "Are You sure you want to delete this Client ? ";
			cin >> Answer;

			while (tolower(Answer) == 'y')
			{

				MarkClientForDelete(AccNumber, vClients);
				SaveClientsDataToFile(ClientsDataFile, vClients);
				//Refresh Clients
				vClients = GetClientsDataFromFile(ClientsDataFile);

				cout << "\nClient Deleted Successfully. \n\n";
				return true;

			}

		}
		else {
			cout << "\nClient whth Acc Number (" << AccNumber << ") Not Founded !\n";
			return false;
		}

	}

	stClient UpdateClientRecord(string AccNumber) {
		stClient Client;

		Client.AccNumber = AccNumber;
		Client.PinCode = str::EnterString("Enter PinCode : ");
		Client.Name = str::EnterString("Enter Name : ");
		Client.Phone = str::EnterString("Enter Phone Number : ");
		Client.Balance = num::ReadNumber("Enter Your Balance : ");
		return Client;

	}

	bool UpdateClientByAccNumber(string AccNumber, vector <stClient>& vClients) {

		char Answer = 'n';
		stClient Client;

		if (FindClientByAccNumber(AccNumber, vClients, Client)) {

			DisplayClientData(Client);
			cout << "Are you sure you want to update this client ?";
			cin >> Answer;
			if (tolower(Answer == 'y')) {
				for (stClient& C : vClients) {

					if (C.AccNumber == AccNumber) {

						C = UpdateClientRecord(AccNumber);
						break;
					}

				}

				SaveClientsDataToFile(ClientsDataFile, vClients);
				cout << "\n\nClient updated Successfully\n";
				return true;

			}
			else
				return false;

		}
		else {
			cout << "Client whth Acc Number (" << AccNumber << ") Not Founded !\n";
			return false;
		}
	}



}