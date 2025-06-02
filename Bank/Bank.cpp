#include <iostream>
#include <string>
#include<fstream>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

	//template<typename T> 
enum SignOption{login=1,signin=2};
enum enumOperationTransaction { Depsite = 1, Withdraw = 2, TotalBalance = 3, GoBack = 4 };
enum Roles  { admin = 1,user = 2 };
string ClientsFileName = "Client.txt";
string UsersFileName = "users.txt";
string FileAction = "action.txt";


//fstream file;
int indexfile = 1;
const int Max_Size = 1024;
struct Users
{
	int ID = 0;
	int AccountNumber = 0;
	string Name = "";
	string Password = "";
	Roles role;
	bool tracke = false;
	bool MarkDeleted = false;
};

struct Client
{
	int ID = 0;
	string AccountNumber;
	string pinCode;
	string Name;
	string PhoneNumber;
	double Balance = 00.00;
	bool MarkDeleted = false;

};
struct Action
{
	string AccountNumber;
	double amount;
	string op;
	bool MarkDeleted = false;
};



int ReadPositiveNumber(string message) {
	int Number;
	short isvalid = false;
	do {
		cout << message;
		cin >> Number;
		isvalid = 1;
		if (cin.fail() || Number < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a positive number." << endl;
			isvalid=0;
		}
	} while (Number < 0 || isvalid==0);
	return Number;
}
void Pause()
{
	cout << "\n\n\nEnter Any Key to Go Home Page?";
	system("pause>0");

}
string ReadString(string message)
{
	string str;
	cout << message << " :" << endl;
	getline(cin >> ws, str);
	return str;
}
void menueUser();
bool SelectUserIdFromFile(int &
	Id);

void TransactonManue();
void MainManue();
string ConvertRecordToLineString(Client client, string delim = "#//#")
{
	string Record = "";
	Record = to_string(client.ID) + delim;
	Record = Record+client.AccountNumber + delim;
	Record = Record + client.pinCode + delim;
	Record = Record + client.Name + delim;
	Record = Record + client.PhoneNumber + delim;
	Record = Record + to_string(client.Balance);
	return  Record;

}
string ConvertRecordUserToLineString(Users user, string delim = "#//#")
{
	string Record = "";
	Record += to_string(user.ID) + delim;
	Record = Record + to_string(user.AccountNumber) + delim;
	Record = Record + user.Name + delim;
	Record = Record + user.Password;
	return  Record;

}
vector<string> SplitString(string st, string delim = "#//#")
{
	rsize_t pos;
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
void HeaderAction( vector<Action>& vaction)
{
	cout << "\n\t\t\t\t\tAction List (" << vaction.size() << ")";
	cout << "\n___________________________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(20) << "Amount";
	cout << "| " << left << setw(20) << "Operation";
	cout <<
		"\n_______________________________________________________";
	cout << "_____________________________________________________\n" << endl;
}
string ActionClient(enumOperationTransaction op)
{
	switch (op)
	{
	case enumOperationTransaction::Depsite:return "Deposit";
		break;
	case enumOperationTransaction::Withdraw:return "Withdraw";
		break;
	}
}
Action ConvertRecordToActionData(string data)
{
	Action action;
	vector<string> vaction = SplitString(data);
	action.AccountNumber = vaction[0];
	action.amount = stod(vaction[1]);
	action.op= vaction[2];
	return action;
}
bool SaveAction(Action action, string delim = "#//#")
{
	 
	 // get time now


	 // convert in string form
	string Dataline = action.AccountNumber + delim;
	Dataline = Dataline + to_string(action.amount) + delim;
	Dataline = Dataline + action.op;
	bool save=false;
	// Convert to local time (struct tm)

	fstream file;
	file.open(FileAction, ios::out | ios::app);
	if (file.is_open())
	{
		file << Dataline << endl;
		save = true;
	}
	file.close();
	return save;
}



vector <Action> LoadActionClientDataFromFile(string ActionFileName)
{
	//Client client;
	string Line = "";
	vector <Action> vaction;
	Action action;

	fstream file;
	file.open(ActionFileName, ios::in);//read Mode
	if (file.is_open())
	{
		while (getline(file, Line))
		{
			if (Line != "") {
				action = ConvertRecordToActionData(Line);
				vaction.push_back(action);
			}
			
		}
	}
	file.close();

	return vaction;
}

vector<Action> DataSearch(string AccountNumber)
{
	vector<Action> vactionData;


	vector<Action> vaction = LoadActionClientDataFromFile(FileAction);

	if (AccountNumber != "")
	{
		for (Action action : vaction)
		{
			if (action.AccountNumber == AccountNumber)
			{
				vactionData.push_back(action);
			}
			
		}
	}
	else {
		cout << "Account Number is not found!" << endl;
	}
	return vactionData;
}
void SearchAction()

{
	 
	string AccountNumber = ReadString("Enter Account Number to Search Action: ");
	vector<Action> vaction = DataSearch(AccountNumber);
	HeaderAction(vaction);

	for (Action& action : vaction)
	{


		cout << "| " << setw(20) << left << action.AccountNumber;
		cout << "| " << setw(20) << left << action.amount;
		cout << "| " << setw(20) << left << action.op;
		cout << "\n";

	}
}




void GoToMenue(bool check)
{
	if (check)
	{
		cout << "\n\n\n Continue....? ";
		system("pause>0");

		MainManue();
	}
	else {
		menueUser();
	}



}
Users SignIN(int role)
{
	Users users;

	cout << "======================\n";
	cout << "Add Users \n";
	cout << "======================";
	cout << endl;
	cout << "Enter Id User:";
	cin >> users.ID;
	cout << "Enter AccountNumber:";
	cin >> users.AccountNumber;
	cout << "Enter User Name:";
	cin >> users.Name;
	cout << "Enter Password:";
	cin >> users.Password;
	users.role = (Roles)role;


	return users;
}


Client ConvertRecordToClietData(string data)
{
	Client client;
	vector<string> vclient = SplitString(data);
	client.ID = stoi(vclient[0]);
	client.AccountNumber = vclient[1];
	client.pinCode = vclient[2];
	client.Name = vclient[3];
	client.PhoneNumber = vclient[4];
	client.Balance = stod(vclient[5]);
	return client;
}
Users ConvertRecordToUsersData(string data)
{
	Users user;
	vector<string> vuser= SplitString(data);
	user.ID = stoi(vuser.at(0));
	user.AccountNumber = stoi(vuser.at(1));
	user.Name = vuser.at(2);
	user.Password = vuser.at(3);
	
	return user;
}

vector <Users> LoadUsersDataFromFile(string ClientsFileName)
{
	//Client client;
	string Line = "";
	vector <Users> vUsers;
	Users user;

	fstream file;
	file.open(ClientsFileName, ios::in);//read Mode
	if (file.is_open())
	{
		while (getline(file, Line))
		{
			if (Line != "") {
				user = ConvertRecordToUsersData(Line);
				vUsers.push_back(user);
			}
			else {
				cout << "Line is not found Data!!" << endl;
			}
		}
	}
	file.close();

	return vUsers;
}
void SaveFile()
{
	vector<Users> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Dataline;
	fstream file;
	file.open(UsersFileName, ios::out | ios::app);
	if (file.is_open())
	{
		for (Users user : vUsers)
		{
			Dataline = ConvertRecordUserToLineString(user);
			if (Dataline != "")
			{
				file << Dataline << endl;
			}
			else {
				cout << "This Record is null!" << endl;
			}

		}
	}


}
void AddUserToFile()
{
	string Dataline;
	fstream file;
	file.open(UsersFileName, ios::out | ios::app);
	if (file.is_open())
	{
	
		Dataline = ConvertRecordUserToLineString(SignIN((Roles)ReadPositiveNumber("Select Role -> Use:1 Admin:2 ?")));
		file << Dataline << endl;
		cout << "Successfuly Regisres>" << endl;


	}
}
bool Login()
{
	string Password;
	int AccountNumber;
	bool track = false;
	char choice = 'n';


	vector<Users> vusers = LoadUsersDataFromFile(UsersFileName);

	cout << "Do you Want Login y/n? ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		do {

			AccountNumber = ReadPositiveNumber("Enter AccountNumber:");
			Password = ReadString("Enter Password:");

			for (Users user : vusers)
			{
				if (user.AccountNumber == AccountNumber && user.Password == Password)
				{
					cout << "Successfuly Login>" << endl;
					return true;

				}

			}

			cout << "This User Not Fount" << endl;
			track = false;

		}
	

	while (track == false);
}
	return false;

}

vector <Client> LoadCleintsDataFromFile(string ClientsFileName);

//bool SignIn(int AccountNumber, string Password)
//{
//	vector<Users> vuser = ReadFileToVector<Users>(UsersFileName);
//	for (Users& users:vuser)
//	{
//		if (users.AccountNumber == AccountNumber&& users.Password==Password)
//		{
//			if (users.role == Roles::admin) {
//				cout << "Welcome Admin!" << endl;
//				return true;
//			}
//			else if (users.role == Roles::user) {
//				cout << "Welcome User!" << endl;
//				return true;
//			}
//			else {
//				cout << "Invalid Role!" << endl;
//				return false;
//			}
//			break;
//		}
//	}
//}



void SingUsers(SignOption Choice)
{
	bool track=true;
	switch (Choice)
	{

	case SignOption::login: track = Login();
		GoToMenue(track);
		break;
	case SignOption::signin:  AddUserToFile();
		Pause();
		menueUser();
		break;

	}
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






void HeaderClientTable(vector<Client> client)
{
	cout << "\n\t\t\t\t\tClient List (" << client.size() << ")";
	cout <<
		"\n___________________________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "ID";
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
	vector<Client> vClients = LoadCleintsDataFromFile(ClientsFileName);

	HeaderClientTable(vClients);
	for (Client client : vClients)
	{
		cout << "| " << setw(15) << left << client.ID;
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
	vector<Client> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")";
	cout << "\n___________________________________________________________________";
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
	cout << right << setw(60) << " Total BALANCE = " << Sum;

}


bool CheckCkclientIsFound(string  Number)
{
	vector<Client> vclient = LoadCleintsDataFromFile(ClientsFileName);
	for (Client& client : vclient) {
		if (client.AccountNumber == Number)
			return true;
	}
	return false;
}

Client AddClient()
{
	Client client;
	cout << "Enter The ID:";

	cin >> client.ID;
	while (SelectUserIdFromFile(client.ID) == false)
	{
		cout << " The ID(" << client.ID << ")is Not Fount in Users Table:" << endl;
		cout << "Enter Again The ID:";

		cin >> client.ID;
	}
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
	return client;
}

Client UpdateClient(string AccountNumber,int ID)
{

	Client client;

	client.ID = ID;
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
	cout << "\nClient Details:\n"
		<< "----------------------------------------\n"
		<< "ID: " << client.ID << "\n"
		<< "Account Number: " << client.AccountNumber << "\n"
		<< "PIN Code:       " << client.pinCode << "\n"
		<< "Name:           " << client.Name << "\n"
		<< "Phone:          " << client.PhoneNumber << "\n"
		<< "Balance:        " << fixed << setprecision(2) << client.Balance << "\n"
		<< "----------------------------------------\n";
}

void Add()
{
	Client  client;
	char add = 'n';
	fstream file;
	do {
		client=AddClient();
		string Record = "";
		Record = ConvertRecordToLineString(client, "#//#");
		file.open(ClientsFileName, ios::out | ios::app);
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

	} while (add == 'y' || add == 'Y');

}
bool FindClientByAccountNumber(string AccountNumber, vector
	<Client> vClients, Client& client)
{
	for (Client &C : vClients)
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
vector <Client>SaveCleintsDataToFile(string ClientsFileName, vector<Client>vClients)
{
	fstream file;
	file.open(ClientsFileName, ios::out);//overwrite
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
	vector<Client> vClients = LoadCleintsDataFromFile(ClientsFileName);

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
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadCleintsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";

			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
	}
	return false;


}
bool Update(string AccountNumber)
{
	vector<Client> vClients = LoadCleintsDataFromFile(ClientsFileName);

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
					C = UpdateClient(AccountNumber,C.ID);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	return true;


}
bool Search(string AccountNumber)
{
	vector<Client> vClients = LoadCleintsDataFromFile(ClientsFileName);
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


void GoToManueTransaction()
{
	cout << "\n\n\nEnter Any Key to Go Home Page?";
	system("pause>0");
	TransactonManue();



}
bool ValidateAmoun(double amount, double amountentry) {
	if (amount > amountentry)
		return true;

	return false;
}
double ShowAllBalance()
{
	double Sum = 0.0;
	vector<Client> vclient = LoadCleintsDataFromFile(ClientsFileName);

	for (Client& client : vclient)
	{
		Sum += client.Balance;
	}
	return Sum;
}

void Deposit(enumOperationTransaction Operation)
{
	string AccountNumber;

	double amount = 00.00;
	bool check = false;
	bool find = false;
	Action action;
	Client client;
	vector<Client> vclient = LoadCleintsDataFromFile(ClientsFileName);
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
					action.AccountNumber = client.AccountNumber;
					action.amount = amount;
					action.op = ActionClient(Operation);
					if (Operation == enumOperationTransaction::Depsite)
					{
						if (ValidateAmoun(client.Balance, amount))
						{
							client.Balance = client.Balance - amount;
							cout << "\n\nClient Updated Successfully.";
							check = true;
							
							SaveAction(action);
						}
						else
						{
							cout << "\nClient Updated error.\n";

							cout << "The Entery Amount Is biggest than Balance:!!" << endl;
							check = false;
						}
					}
					else if (Operation == enumOperationTransaction::Withdraw)
					{
						client.Balance = client.Balance + amount;
						cout << "\n\nClient Updated Successfully.";
						check = true;
						
						SaveAction(action);
						break;
					}
				}
			}
		}
	} while (amount < 0 || check == false || find == false);
	SaveCleintsDataToFile(ClientsFileName, vclient);
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
	case 7:
		SearchAction();
		Pause();
		system("cls");
		MainManue();

	case 8:
		system("cls");
		menueUser();
		break;
	case 9:
		system("cls");
		cout << "Thank you for using the Bank System. Goodbye!" << endl;
		exit(0);

		break;
	}
}

int main()
{

	
	menueUser();

	return 0;
}
void MainManue()
{
	system("cls");
		cout <<
			"\n_______________________________________________________\n";
		cout << right << setw(10) << "[1]" << "Show All Clients" << endl;
		cout << right << setw(10) << "[2]" << "Add New Client" << endl;
		cout << right << setw(10) << "[3]" << "Update Client " << endl;
		cout << right << setw(10) << "[4]" << "Delete Client" << endl;
		cout << right << setw(10) << "[5]" << "Find Client" << endl;
		cout << right << setw(10) << "[6]" << "Transaction" << endl;
		cout << right << setw(10) << "[7]" << "SearchAction" << endl;
		cout << right << setw(10) << "[8]" << "Logout" << endl;
		cout << right << setw(10) << "[9]" << "Exit" << endl;
		cout <<
			"\n_______________________________________________________\n";
		StarAction(ReadPositiveNumber(" Select Number  from Manue ?"));

}

void TransactonManue() {
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
}void menueUser() {
	system("cls");
	
	cout <<
		"\n_______________________________________________________\n";
	cout << right << setw(10) << "[1]" << "Login" << endl;
	cout << right << setw(10) << "[2]" << "SignIN" << endl;
	
	cout <<
		"\n_______________________________________________________\n";
	SingUsers((SignOption)ReadPositiveNumber("Choice Action From Manue?"));
}
bool SelectUserIdFromFile(int& Id)
{
	Users user;
	fstream file;
	string Line;
	file.open(UsersFileName, ios::in);
	if (file.is_open())
	{
		while (getline(file, Line))
		{
			if (Line != "") {
				user = ConvertRecordToUsersData(Line);
				if (user.ID == Id) 
					return true;
				
			}
			else {
				cout << "Line is not found Data!!" << endl;
			}
		}

		}
	file.close();
	return false;
	
	}

//8476362741

vector <Client> LoadCleintsDataFromFile(string ClientsFileName)
{
	//Client client;
	string Line = "";
	vector <Client> vClients;
	Client client;

	fstream file;
	file.open(ClientsFileName, ios::in);//read Mode
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
