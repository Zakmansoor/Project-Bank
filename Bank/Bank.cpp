#include <iostream>
#include <string>
#include<fstream>
#include <iomanip>

#include <vector>
using namespace std;
string FileName = "Client.txt";
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
	cout  << message << " :" << endl;
	getline(cin >> ws, str);
	return str;
}
void HeaderAction(int choice)
{
	switch (choice) {
	case 1:cout << right << setw(70) << " | Page Show All Client |" << "\n\n\n";
		break;
	case 2:cout << right << setw(70) << " | Page Add  Client |" << "\n\n\n";
		break;
	case 3:cout << right << setw(70) << " | Page  Update Client |" << "\n\n\n";
		break;
	case 4:cout << right << setw(70) << " | Page  Delete Client |" << "\n\n\n";
	case 5:cout << right << setw(70) << " | Page  Search  Client |" << "\n\n\n";
		break;
	default :cout << right << setw(70) << " | Home Page     |" << "\n\n\n";
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
}string ConvertRecordToLineString(Client client, string delim = "#//#")
{
	string Record = "";
	Record += client.AccountNumber + delim;
	Record = Record + client.pinCode + delim;
	Record = Record + client.Name + delim;
	Record = Record + client.PhoneNumber + delim;
	Record = Record + to_string(client.Balance);
	return  Record;

}
vector<string> SplitString(string st, string delim = "#//#")
{
	short pos ;
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

	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			if (Line != "") {
				client = ConvertRecordToClietData(Line);
				vClients.push_back(client);
			}
		}
	}
	MyFile.close();

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

}void UpdateClient(Client& client)
{


	cout << "Enter The Pin Code:";
	getline(cin >> ws, client.pinCode);
	cout << "Enter The Name:";
	getline(cin >> ws, client.Name);
	cout << "Enter The PhoneNumber:";
	getline(cin >> ws, client.PhoneNumber);
	cout << "Enter The Balance:";
	cin >> client.Balance;

}
void PrintClientCard(Client client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << client.AccountNumber;
	cout << "\nPin Code : " << client.pinCode;
	cout << "\nName : " << client.Name;
	cout << "\nPhone : " << client.PhoneNumber;
	cout << "\nAccount Balance: " << client.Balance;
}

bool Add()
{
	Client  client;
	fstream file;
	AddClient(client);
	string Record = "";
	Record = ConvertRecordToLineString(client, "#//#");
	file.open(FileName, ios::out | ios::app);
	if (file.is_open())
	{
		if (Record != "") {
			file << Record << endl;
			cout << "The Client saved Succussfully!" << endl;
			return true;
		}
	}
	else
	{
		cout << "Error Saved Client!" << endl;
		return false;
	}
	file.close();


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
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (Client C : vClients)
		{
			if (C.MarkDeleted == false)
			{

			
				DataLine = ConvertRecordToLineString(C);
				MyFile << DataLine << endl;
			}
			

		}
		MyFile.close();
	}
	return vClients;
}

bool Delete(string AccountNumber )
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
		cout<< "Are you sure you want Update this client? y/n ? ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			
			for (Client& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					UpdateClient(C);
					break;
				}
			}
			SaveCleintsDataToFile(FileName, vClients);
			//Refresh Clients

			cout << "\n\nClient Updated Successfully.";
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
void MainManue(int &choice)
{
	cout <<
		"\n_______________________________________________________\n";
	cout << right << setw(10) << "[1]" << "Show All Clients" << endl;
	cout << right << setw(10) << "[2]" << "Add New Client" << endl;
	cout << right << setw(10) << "[3]" << "Update Client " << endl;
	cout << right << setw(10) << "[4]" << "Delete Client" << endl;
	cout << right << setw(10) << "[5]" << "Find Client" << endl;
	cout << right << setw(10) << "[6]" << "Exit" << endl;
	cout <<
		"\n_______________________________________________________\n";
	choice = ReadPositiveNumber(" Select Number  from Manue ?");

}
void StarAction(int Selected)
{
	system("cls");
	HeaderAction(Selected);

	if(Selected==1)
		ShowAllClients();
	string ReadAccountNumber;

	switch (Selected)
	{
	case 2: Add();				
		break;
		case 3: Update(ReadAccountNumber= ReadString("Enter The Account Number:"));
		break;

	case 4: Delete(ReadAccountNumber = ReadString("Enter The Account Number:"));
		break;

	case 5: Search(ReadAccountNumber = ReadString("Enter The Account Number:"));
		break;
	}

}




void Start() {
	int Selected;

	do {
		MainManue(Selected);

		StarAction(Selected);
		cout<<"\n\n\nEnter Any Key to Go Home Page?" ;
		system("pause>0");
		system("cls");



	} 
	while (Selected != 6);
	


}
int main()
{
	Start();

	return 0;
}

