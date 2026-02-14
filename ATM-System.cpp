#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const string ClientsFileName = "Clients.txt";

struct stClient {

    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
};

stClient CurrentClient;

enum enMainMenuOption { enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, Logout = 5 };

void PerfromMainMenuOption(enMainMenuOption MainMenuOption);

bool FindClientByAccountNumber(const string& AccountNumber, const string& PinCode, const vector <stClient>& vClients, stClient& Client) {

    for (const stClient& C : vClients)
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode) {

            Client = C;
            return true;
        }

    return false;
}

vector<string> SplitString(string S1, const string& Delim) {

    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos) {

        sWord = S1.substr(0, pos);

        if (sWord != "")
            vString.push_back(sWord);

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;
}

stClient ConvertLinetoRecord(const string& Line, const string& Seperator = "#//#") {

    stClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

vector <stClient> LoadCleintsDataFromFile(const string& FileName) {

    vector <stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {

        string Line;
        stClient Client;

        while (getline(MyFile, Line)) {

            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

short ReadMainMenueOption() {

    cout << "Choose what do you want to do? [1 to 5] ? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void ShowMainMenuScreen() {

    system("cls");
    cout << "===========================================\n";
    cout << "\tATM Main Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    
    PerfromMainMenuOption((enMainMenuOption)ReadMainMenueOption());
}

void Login() {

    bool LoginFaild = false;
    string AccountNumber, PinCode;
    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	do
	{
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild)
			cout << "Invlaid Username/Password!\n";

		cout << "Enter AccountNumber ? ";
        getline(cin >> ws, AccountNumber);

		cout << "Pin Code ? ";
        getline(cin >> ws, PinCode);

		LoginFaild = !FindClientByAccountNumber(AccountNumber, PinCode,vClients, CurrentClient);

	} while (LoginFaild);

    ShowMainMenuScreen();
}

void PerfromMainMenuOption(enMainMenuOption MainMenuOption) {

    switch (MainMenuOption) {

    case enMainMenuOption::enQuickWithdraw:

        system("cls");
        break;

    case enMainMenuOption::enNormalWithdraw:
        system("cls");
        break;

    case enMainMenuOption::enDeposit:
        system("cls");
        break;

    case enMainMenuOption::enCheckBalance:
        system("cls");
        break;

    case enMainMenuOption::Logout:
        Login();
        break;
    }
}

int main() {

    Login();

	return 0;
}