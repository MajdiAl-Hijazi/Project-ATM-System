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

enum enQuickWithdrawOption {

    Withdraw20 = 1,
    Withdraw50 = 2,
    Withdraw100 = 3,
    Withdraw200 = 4,
    Withdraw400 = 5,
    Withdraw600 = 6,
    Withdraw800 = 7,
    Withdraw1000 = 8,
    Exit = 9
};

void ClearCurrentClientDataInATM(stClient& Client) {

    Client.AccountNumber = "";
    Client.PinCode = "";
    Client.Name = "";
    Client.Phone = "";
    Client.AccountBalance = 0;
}

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

short ReadQuickWithdrawOption() {

    cout << "\nChoose what to withdraw from [1] to [9] ? ";
    short Choice;
    cin >> Choice;

    return Choice;
}

short PerformQuickWithdrawOption(enQuickWithdrawOption QuickWithdrawOption) {

    switch (QuickWithdrawOption) {
    
    case enQuickWithdrawOption::Withdraw20:
        return 20;

    case enQuickWithdrawOption::Withdraw50:
        return 50;

    case enQuickWithdrawOption::Withdraw100:
        return 100;

    case enQuickWithdrawOption::Withdraw200:
        return 200;

    case enQuickWithdrawOption::Withdraw400:
        return 400;

    case enQuickWithdrawOption::Withdraw600:
        return 600;

    case enQuickWithdrawOption::Withdraw800:
        return 80;

    case enQuickWithdrawOption::Withdraw1000:
        return 1000;

    case enQuickWithdrawOption::Exit:
        return -1;

    default:
        return -1;
    }
}

string ConvertRecordToLine(const stClient& Client, string Seperator = "#//#") {

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

void SaveCleintsDataToFile(const string& FileName, const vector <stClient>& vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DataLine;

    if (MyFile.is_open()) {

        for (const stClient& C : vClients) {

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
        }

        MyFile.close();
    }
}

void SaveChange() {

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (stClient& Client : vClients)
        if (Client.AccountNumber == CurrentClient.AccountNumber) {

            Client.AccountBalance = CurrentClient.AccountBalance;
            break;
        }

    SaveCleintsDataToFile(ClientsFileName, vClients);
}

void CheckBalanceScreen() {

    system("cls");
    cout << "\n===================================\n";
    cout << "\tCheck Balance Screen ";
    cout << "\n===================================\n";
    cout << "Yor Balance is " << CurrentClient.AccountBalance << endl;

    cout << "\nPress anykey to continue...";
    system("pause>0");
}

void Withdraw(int Amount) {

    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y') {

        CurrentClient.AccountBalance -= Amount;
        cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance;
        SaveChange();
        cout << "\nPerss Any Key to go back to main menu...";
        system("pause>0");
    }
    else {

        cout << "\nCanceled Process.";
        cout << "\nPerss Any Key to go back to main menu...";
        system("pause>0");
    }
}

void ShowNormalWithdrawScreen() {

    bool WithdrawFailed = false;

    do {
    
        system("cls");
        cout << "\n===================================\n";
        cout << "\tNormal withdraw Withdraw ";
        cout << "\n===================================\n";

        int Amount = 0;
        
        do {
        
            cout << "\nEnter an amount multiple if 5's ? ";
            cin >> Amount;
        } while (Amount % 5 != 0);

        if (Amount > CurrentClient.AccountBalance) {

            cout << "\n\nThe amount exceeds your balance, make another choice.\n";
            WithdrawFailed = true;
            cout << "Press anykey to continue...";
            system("pause>0");
        }
        else {

            Withdraw(Amount);
            WithdrawFailed = false;
        }

	} while (WithdrawFailed);
}

void ShowQuickWithDrawScreen() {

    bool WithdrawFailed = false;

    do {

        system("cls");
        cout << "\n===================================\n";
        cout << "\t   Quick Withdraw ";
        cout << "\n===================================\n";

        cout << "\t[1] 20\t\t[2] 50\n";
        cout << "\t[3] 100\t\t[4] 200\n";
        cout << "\t[5] 400\t\t[6] 600\n";
        cout << "\t[7] 800\t\t[8] 1000\n";
        cout << "\t[9] Exit";

        cout << "\n===================================\n";

        cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

        short Amount = PerformQuickWithdrawOption((enQuickWithdrawOption)ReadQuickWithdrawOption());

        if (Amount == -1)
            return;

        if (Amount > CurrentClient.AccountBalance) {
        
            cout << "\n\nThe amount exceeds your balance, make another choice.\n";
            WithdrawFailed = true;
            cout << "Press anykey to continue...";
            system("pause>0");
        }
        else {
        
            Withdraw(Amount);
            WithdrawFailed = false;
        }

    } while (WithdrawFailed);
}

void ShowDepositScreen() {

    system("cls");
    cout << "\n===================================\n";
    cout << "\tDeposit Screen";
    cout << "\n===================================\n";

    int Amount = 0;

    do {
    
        cout << "\nEnter a positsve Deposite Amount ? ";
        cin >> Amount;
    } while (Amount <= 0);

    Withdraw(-1 * Amount);
}

void PerfromMainMenuOption(enMainMenuOption MainMenuOption) {

    switch (MainMenuOption) {

    case enMainMenuOption::enQuickWithdraw:
        ShowQuickWithDrawScreen();
        ShowMainMenuScreen();
        break;

    case enMainMenuOption::enNormalWithdraw:
        ShowNormalWithdrawScreen();
        ShowMainMenuScreen();
        break;

    case enMainMenuOption::enDeposit:
        ShowDepositScreen();
        ShowMainMenuScreen();
        break;

    case enMainMenuOption::enCheckBalance:
        CheckBalanceScreen();
        ShowMainMenuScreen();
        break;

    case enMainMenuOption::Logout:
        ClearCurrentClientDataInATM(CurrentClient);
        Login();
        break;
    }
}

int main() {

    Login();

	return 0;
}