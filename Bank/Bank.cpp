#include <iostream>
#include <string>
#include<fstream>
#include <iomanip>

#include <vector>
using namespace std;
enum enumOperationTransaction{Depsite=1,Withdraw=2,TotalBalance=3,GoBack=4};
string FileName = "Client.txt";
//fstream file;
int indexfile = 1;
const int Max_Size = 1024;
struct
	Client
{
	string AccountNumber;
	string pinCode;
	string Name;
	string PhoneNumber;
	double Balance = 00.00;
	bool MarkDeleted = false;
};

//void OpenFile()
//{
//	if (file.is_open())
//		file.close();
//	string FileName = "client" + to_string(indexfile) + ".txt";
//	file.open(FileName, ios::out | ios::app);
//	if (!file.is_open())
//		cout << "error When Opern file";
//	indexfile++;
//
//}
//void WriteFile(string& Data)
//{
//	if (!file.is_open() || file.tellp() > Max_Size)
//		OpenFile();
//	file << Data;
//}
//
void TransactonManue();
int ReadPositiveNumber(string message) {
	int Number;
	do {
		cout << message;
		cin >> Number;
		if (cin.fail() || Number < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a positive number." << endl;
		}
	} while (Number < 0);
	return Number;
}
string ReadString(string message)
{
	string str;
	cout << message << " :" << endl;
	getline(cin >> ws, str);
	return str;
}
void HeaderAction(int choice)
{
	switch (choice) {
	case 1:cout << right << setw(70) << " | Page Show All Clients |" << "\n\n\n";
		break;
	case 2:cout << right << setw(70) << " | Page Add  Client |" << "\n\n\n";
		break;
	case 3:cout << right << setw(70) << " | Page  Update Client |" << "\n\n\n";
		break;
	case 4:cout << right << setw(70) << " | Page  Delete Client |" << "\n\n\n";
	case 5:cout << right << setw(70) << " | Page  Search  Client |" << "\n\n\n";
		break;
	case 6:cout << right << setw(70) << " | Transaction Balance Client |" << "\n\n\n";
		break;
	default:cout << right << setw(70) << " | Home Page     |" << "\n\n\n";
		break;
	}
}void HeaderTransaction(int choice)
{
	switch (choice) {
	case 1:cout << right << setw(70) << " | Deposite Page |" << "\n\n\n";
		break;
	case 2:cout << right << setw(70) << " | Withdraw Page |" << "\n\n\n";
		break;
	case 3:cout << right << setw(70) << " | Total Balance |" << "\n\n\n";
		break;
	
	}
}
char ReadChar(string message)
{
	char letter;
	cout << message << " :" << endl;
	cin >> letter;
	while (!(letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'));
	{
		cout << "Invalid input. Please enter a charachter letter." << endl;
		cin >> letter;

	}
	return letter;
}
string ConvertRecordToLineString(Client client, string delim = "#//#")
{
	string Record = "";
	Record += client.AccountNumber + delim;
	Record = Record + client.pinCode + delim;
	Record = Record + client.Name + delim;
	Record = Record + client.PhoneNumber + delim;
	Record = Record + to_string(client.Balance);
	return  Record;

}
void MainManue();

vector<string> SplitString(string st, string delim = "#//#")
{
	short pos;
	string word = "";
	vector<string> vword;
	while ((pos = st.find(delim)) != std::string::npos) {
		word = st.substr(0, pos);
		if (word != "")
		{
			vword.push_back(word);
		}
		st.erase(0, pos + delim.length());
	}
	if (st != "")
	{
		vword.push_back(st);
	}
	return vword;
}
Client ConvertRecordToClietData(string data)
{
	Client client;
	vector<string> vclient = SplitString(data);
	client.AccountNumber = vclient[0];
	client.pinCode = vclient[1];
	client.Name = vclient[2];
	client.PhoneNumber = vclient[3];
	client.Balance = stod(vclient[4]);
	return client;
}

vector <Client> LoadCleintsDataFromFile(string FileName)
{
	//Client client;
	string Line = "";
	vector <Client> vClients;
	Client client;

	fstream file;
	file.open(FileName, ios::in);//read Mode
	if (file.is_open())
	{
		while (getline(file, Line))
		{
			if (Line != "") {
				client = ConvertRecordToClietData(Line);
				vClients.push_back(client);
			}
		}
	}
	file.close();

	return vClients;
}
void HeaderClientTable(vector<Client> client)
{
	cout << "\n\t\t\t\t\tClient List (" << client.size() << ")";
	cout <<
		"\n___________________________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(8) << "Phone";
	cout << "| " << left << setw(10) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;

}

void ShowAllClients()
{
	vector<Client> vClients = LoadCleintsDataFromFile(FileName);

	HeaderClientTable(vClients);
	for (Client client : vClients)
	{
		cout << "| " << setw(15) << left << client.AccountNumber;
		cout << "| " << setw(10) << left << client.pinCode;
		cout << "| " << setw(40) << left << client.Name;
		cout << "| " << setw(10) << left << client.PhoneNumber;
		cout << "| " << setw(10) << left << client.Balance;
		cout << "\n";
	}
}

void ShowBalanceClients()
{
	double Sum = 0.0;
	vector<Client> vClients = LoadCleintsDataFromFile(FileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")";
	cout <<"\n___________________________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(16) << "Accout Number";
	cout << "| " << left << setw(40) << "Pin Code";
	
	cout << "| " << left << setw(16) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;

	for (Client client : vClients)
	{
		cout << "| " << setw(16) << left << client.AccountNumber;
		cout << "| " << setw(40) << left << client.pinCode;
		cout << "| " << setw(16) << left << client.Balance;
		cout << "\n";
		Sum += client.Balance;
	}
	
	cout <<
		"\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;
	cout << right << setw(60) << " Total BALANCE = "<<Sum;

}


bool CheckCkclientIsFound(string  Number)
{
	vector<Client> vclient = LoadCleintsDataFromFile(FileName);
	for (Client& client : vclient) {
		if (client.AccountNumber == Number)
			return true;
	}
	return false;
}

void AddClient(Client& client)
{

	cout << "Enter The AccountNumber:";
	cin >> client.AccountNumber;
	while (CheckCkclientIsFound(client.AccountNumber) == true) {
		cout << " The AccountNumber(" << client.AccountNumber << ")is Already Exit:" << endl;
		cout << "Enter Again The AccountNumber:";

		cin >> client.AccountNumber;


	}

	cout << "Enter The Pin Code:";
	getline(cin >> ws, client.pinCode);
	cout << "Enter The Name:";
	getline(cin >> ws, client.Name);
	cout << "Enter The PhoneNumber:";
	getline(cin >> ws, client.PhoneNumber);
	cout << "Enter The Balance:";
	cin >> client.Balance;

}Client UpdateClient(string AccountNumber)
{

	Client client;
	client.AccountNumber = AccountNumber;
	cout << "Enter The Pin Code:";
	getline(cin >> ws, client.pinCode);
	cout << "Enter The Name:";
	getline(cin >> ws, client.Name);
	cout << "Enter The PhoneNumber:";
	getline(cin >> ws, client.PhoneNumber);
	cout << "Enter The Balance:";
	cin >> client.Balance;
	return client;
}
void PrintClientCard(Client client)
{
	cout << "\n--------------------------------------------\n";

	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << client.AccountNumber;
	cout << "\nPin Code : " << client.pinCode;
	cout << "\nName : " << client.Name;
	cout << "\nPhone : " << client.PhoneNumber;
	cout << "\nAccount Balance: " << client.Balance;
	cout << "\n--------------------------------------------\n";
}

void Add()
{
	Client  client;
	char add = 'n';
	fstream file;
	do {
		AddClient(client);
		string Record = "";
		Record = ConvertRecordToLineString(client, "#//#");
		file.open(FileName, ios::out | ios::app);
		if (file.is_open())
		{
			if (Record != "") {
				file << Record << endl;
				cout << "The Client saved Succussfully!" << endl;


			}

			else
			{
				cout << "Error Saved Client!" << endl;
			}
		}
		file.close();
		cout << "Do you Add another Client ? y/n :";
		cin >> add;

	} 
	while (add == 'y' || add == 'Y');

}
bool FindClientByAccountNumber(string AccountNumber, vector
	<Client> vClients, Client& client)
{
	for (Client C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			client = C;
			return true;
		}
	}
	cout << "\nClient with Account Number (" << AccountNumber
		<< ") is Not Found!";
	return false;
}
bool MarkClientToAction(string AccountNumber, vector<Client>& vclient)
{
	for (Client& C : vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkDeleted = true;
			return true;
		}

	}
	return false;

}
vector <Client>SaveCleintsDataToFile(string FileName, vector<Client>vClients)
{
	fstream file;
	file.open(FileName, ios::out);//overwrite
	string DataLine;
	if (file.is_open())
	{
		for (Client C : vClients)
		{
			if (C.MarkDeleted == false)
			{
				DataLine = ConvertRecordToLineString(C);
				file << DataLine << endl;
			}
		}
		file.close();
	}
	return vClients;
}

bool Delete(string AccountNumber)
{
	vector<Client> vClients = LoadCleintsDataFromFile(FileName);

	char answer;

	Client client;
	if (FindClientByAccountNumber(AccountNumber, vClients, client))
	{
		PrintClientCard(client);
		cout << "Are you sure you want Delete this client? y/n ? ";

		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			MarkClientToAction(AccountNumber,
				vClients);
			SaveCleintsDataToFile(FileName, vClients);
			vClients = LoadCleintsDataFromFile(FileName);
			cout << "\n\nClient Deleted Successfully.";

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
bool Update(string AccountNumber)
{
	vector<Client> vClients = LoadCleintsDataFromFile(FileName);

	char answer;
	Client client;
	if (FindClientByAccountNumber(AccountNumber, vClients, client))
	{
		PrintClientCard(client);
		cout << "Are you sure you want Update this client? y/n ? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			for (Client& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C=UpdateClient(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(FileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	
}
bool Search(string AccountNumber)
{
	vector<Client> vClients = LoadCleintsDataFromFile(FileName);
	Client client;
	for (Client C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			client = C;
			PrintClientCard(C);
			return true;
		}
	}
	cout << "\nClient with Account Number (" << AccountNumber
		<< ") is Not Found!";
	return false;
}
void Pause()
{
	cout << "\n\n\nEnter Any Key to Go Home Page?";
	system("pause>0");


	
}

void GoToManueTransaction()
{
	cout << "\n\n\nEnter Any Key to Go Home Page?";
	system("pause>0");
	TransactonManue();



}
bool ValidateAmoun(double amount, double amountentry) {
	if (amount > amountentry)
		return true;
	cout << "\nClient Updated error.\n";

	cout << "The Entery Amount Is biggest than Balance:!!" << endl;
	return false;
}
double ShowAllBalance()
{
	double Sum = 0.0;
	vector<Client> vclient = LoadCleintsDataFromFile(FileName);
	
		for (Client& client : vclient)
		{
			Sum += client.Balance;
		}
		return Sum;
}

void Deposit(enumOperationTransaction Operation)
{
	string AccountNumber;
	cout << "=========================" << endl;
	cout << "Page Deposit Your Balance" << endl;
	cout << "=========================" << endl;
	double amount = 00.00;
	bool check = false;
	bool find = false;

	Client client;
	vector<Client> vclient = LoadCleintsDataFromFile(FileName);
	do {
		AccountNumber = ReadString("Enter AccountNumber :");
		if (FindClientByAccountNumber(AccountNumber, vclient, client))
		{
			find = true;
			PrintClientCard(client);



			for (Client& client : vclient) {
				if (client.AccountNumber == AccountNumber) {
					cout << "Enter Amount To Deposit From Your Balance? " << endl;
					cin >> amount;
					if (enumOperationTransaction::Depsite && ValidateAmoun(client.Balance, amount))
					{

						client.Balance = client.Balance - amount;
						cout << "\n\nClient Updated Successfully.";
						check = true;

						break;
					


						
					}
					 if (enumOperationTransaction::Withdraw)
					{

						client.Balance = client.Balance + amount;
						cout << "\n\nClient Updated Successfully.";
						check = true;

						break;


					}


				}
			}

		}
	}
	while (amount < 0 || check == false||find==false);

	
	SaveCleintsDataToFile(FileName, vclient);

}
void StarTransaction(enumOperationTransaction Choice)
{

	system("cls");
	HeaderTransaction(Choice);



	switch (Choice)
	{
	case enumOperationTransaction::Depsite:
		system("cls");
		Deposit(Choice);
		GoToManueTransaction();



		break;
	case enumOperationTransaction::Withdraw:
		system("cls");

		Deposit(Choice);
		GoToManueTransaction();

		break;


	case  enumOperationTransaction::TotalBalance:
		system("cls");

		ShowBalanceClients();
		GoToManueTransaction();
		break;
	case  enumOperationTransaction::GoBack:
		MainManue();
		break;
	default:
		system("cls");

		TransactonManue();
	}
}
void StarAction(int Selected)
{
	system("cls");
	
	HeaderAction(Selected);
	
	string ReadAccountNumber;

	switch (Selected)
	{
	case 1: ShowAllClients();
		Pause();
		system("cls");
		MainManue();
		break;
	case 2: Add();
		Pause();
		system("cls");
		MainManue();
		break;
	case 3: Update(ReadAccountNumber = ReadString("Enter The Account Number:"));
		Pause();
		system("cls");
		MainManue();

		break;

	case 4: Delete(ReadAccountNumber = ReadString("Enter The Account Number:"));
		Pause();
		system("cls");
		MainManue();

		break;

	case 5: Search(ReadAccountNumber = ReadString("Enter The Account Number:"));
		Pause();
		system("cls");
		MainManue();

		break;

	case 6: 
		TransactonManue();

		system("cls");
		MainManue();

		
		break;
	}
}

int main()
{
	MainManue();

	return 0;
}
void MainManue()
{
	cout <<
		"\n_______________________________________________________\n";
	cout << right << setw(10) << "[1]" << "Show All Clients" << endl;
	cout << right << setw(10) << "[2]" << "Add New Client" << endl;
	cout << right << setw(10) << "[3]" << "Update Client " << endl;
	cout << right << setw(10) << "[4]" << "Delete Client" << endl;
	cout << right << setw(10) << "[5]" << "Find Client" << endl;
	cout << right << setw(10) << "[6]" << "Transaction" << endl;
	cout << right << setw(10) << "[7]" << "Exit" << endl;
	cout <<
		"\n_______________________________________________________\n";
	StarAction( ReadPositiveNumber(" Select Number  from Manue ?"));
}
void TransactonManue(){
	system("cls");
	cout <<
		"\n_______________________________________________________\n";
	cout << right << setw(10) << "[1]" << "Deposit" << endl;
	cout << right << setw(10) << "[2]" << "withdraw" << endl;
	cout << right << setw(10) << "[3]" << "Total Balance " << endl;
	cout << right << setw(10) << "[4]" << "MainManue" << endl;
	cout <<
		"\n_______________________________________________________\n";
	StarTransaction((enumOperationTransaction)ReadPositiveNumber("Choice Proccess From Manue?"));
}