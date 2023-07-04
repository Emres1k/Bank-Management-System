#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <clocale>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cassert>

using namespace std;


class Account {
public:
	Account(string name = "", string surname = "", float balance = 0, string phoneNumber = "", string password = "");
	void controlReceipt();
	void mainMenu();
	int options();
	void controlName();
	void controlSurname();
	void controlPhone(Account* accounts);
	void controlBalance();
	void controlPassword();
	void setPerson(string name = "", string surname = "", float balance = 0,
		string phoneNumber = "", string password = "");
	float getAccountBalance() const { return accountBalance; }
	string getAccountName()const { return accountName; }
	string getAccountSurname() const { return accountSurname; }
	string getAccountPhone() const { return accountPhone; }
	string getAccountPassword() const { return accountPassword; }
	void displayProfile();
	void logoutAccount(Account* currentAccount);
	void deposit(Account* accounts, Account* currentAccount);
	void withdraw(Account* accounts, Account* currentAccount);
	void showOtherAccounts(Account* accounts, Account* currentAccount);
	void deleteAccount(Account* accounts, Account* currentAccount);
	void modifyAccount(Account* accounts, Account* currentAccount);
	void sendMoney(Account* accounts, Account* currentAccount);
	void createAccount(Account* accounts, int i);
	void loginOrCreateAccount(Account* accounts, Account* currentAccount);
	void loginAccount(Account* accounts, Account* currentAccount);
	void mergeObjects(Account* accounts, Account* currentAccount);
	bool operator ==(const Account& other) {
		return (accountName == other.accountName && accountSurname == other.accountSurname && accountPassword == other.accountPassword && accountPhone
			== other.accountPhone && accountBalance == other.accountBalance);
	}
	bool operator ==(const int i) {
		assert(i == 0);
		return (accountName == "" && accountSurname == "" && accountPassword == "" && accountPhone
			== "" && accountBalance == 0);
	}
	void operator =(const Account& other) {
		accountName = other.accountName;
		accountSurname = other.accountSurname;
		accountPassword = other.accountPassword;
		accountPhone = other.accountPhone;
		accountBalance = other.accountBalance;
	}
private:
	float accountBalance;
	string accountName, accountSurname, accountPhone, accountPassword;
	bool accountReceipt;
	fstream receipt;
};
Account::Account(string name, string surname, float balance, string phone, string password) {
	setPerson(name, surname, balance, phone, password);
}
void Account::mainMenu() {
	cout << "MAIN MENU" << endl;
	cout << "01. DISPLAY THE ACCOUNT" << endl;
	cout << "02. LOG OUT FROM THE ACCOUNT" << endl;
	cout << "03. DEPOSIT MONEY" << endl;
	cout << "04. WITHDRAW MONEY" << endl;
	cout << "05. SHOW OTHER ACCOUNTS" << endl;
	cout << "06. DELETE THE ACCOUNT" << endl;
	cout << "07. MODIFY THE ACCOUNT" << endl;
	cout << "08. SEND MONEY TO OTHER ACCOUNTS" << endl;
	cout << "09. EXIT" << endl;
	cout << "10. MAIN MENU" << endl;
}
int Account::options() {
	cout << "Select Your Option (1-10) " << endl;
	string option;
	int num;
	while (true) {
		cin >> option;
		try {
			num = stoi(option);
			if (num >= 0 && num <= 10)
				break;
		}
		catch (...) {
			cout << "Invalid value. Please choose an option between 1-10" << endl;
		}
	}
	return num;
}
void Account::setPerson(string name, string surname, float balance, string phone, string password) {
	accountName = name;
	accountSurname = surname;
	accountBalance = balance;
	accountPhone = phone;
	accountPassword = password;
}
void Account::loginOrCreateAccount(Account* accounts, Account* currentAccount) {
	cout << "WELCOME DEAR CUSTOMER" << endl << "Enter '1' to log in your account or enter 2 to create an new account." << endl;
	cout << "Please note that you can enter '-1' to exit now or later to cancel for your next processes." << endl;
	string loginOrCreate;
	bool accExceed=true;
	while (true) {
		cin >> loginOrCreate;
		if (loginOrCreate == "1") {
			loginAccount(accounts, currentAccount);
			break;
		}
		else if (loginOrCreate == "2") {
			int i = 0;
			for (i; i < 10; i++) {
				if (accounts[i]==0) {
					accounts[i].createAccount(accounts, i);
					accExceed = false;
					if (accountReceipt && !(accounts[i] == 0)) 
						receipt << "An account named \"" << accounts[i].accountName << "\" has been created." << endl;
					loginOrCreateAccount(accounts, currentAccount);
					return;
				}
			}
			if (accExceed) {
				cout << "Account limit exceeded! You can only add up to 10 accounts." << endl;
				continue;
			}
		}
		else if (loginOrCreate == "-1")
			exit(0);
		else
			cout << "Please choose an option (1,2)" << endl;
	}
}
void Account::loginAccount(Account* accounts, Account* currentAccount) {
	string phoneCheck, passwordCheck;
	bool phoneValid = false, passwordValid = false;
	char character;
	cout << "Please enter your phone number" << endl;
	while (true){
		cout << "05";
		cin >> phoneCheck;
		if (phoneCheck == "-1") {
			cout << "Current process cancelled!." << endl;
			loginOrCreateAccount(accounts, currentAccount);
		}
		phoneCheck = "05" + phoneCheck;
		for (int i = 0; i < 10; i++) {
			if (accounts[i].getAccountName() != "" && accounts[i].getAccountPhone() == phoneCheck) {
				phoneValid = true;
				break;
			}
		}
		if (!phoneValid)
			cout << "No account was found with the entered phone number! Please enter your phone number again" << endl;
		else
			break;
	} 
	cout << "Please enter your password" << endl;
	while ((character = _getch()) != '\r') {
		if (character == '\b') {
			if (!passwordCheck.empty()) {
				cout << "\b \b";
				passwordCheck.pop_back();
			}
		}
		else {
			cout << "*";
			passwordCheck += character;
		}
	}
	while (true){
		if (passwordCheck == "-1") {
			cout << "\nCurrent process cancelled!." << endl;
			loginOrCreateAccount(accounts, currentAccount);
		}
		for (int i = 0; i < 10; i++) {
			if (accounts[i].getAccountName() != "" && accounts[i].getAccountPassword() == passwordCheck && accounts[i].getAccountPhone() == phoneCheck) {
				cout << "\nYou have successfully logged into your account!\n" << endl;
				*currentAccount = accounts[i];
				passwordValid = true;
				if (accountReceipt)
					receipt << "Logged into \"" << currentAccount->accountName << "\" account." << endl;
				return;
			}
		}
		if (!passwordValid)
			cout << "No account was found with entered password! Please enter your password again" << endl;
		else
			break;
	} 
}
void Account::createAccount(Account* accounts, int i) {
	controlName();
	if (accountName == "-1") {
		setPerson();
		cout << "Cancelled!" << endl;
		return;
	}
	controlSurname();
	if (accountSurname == "-1") {
		setPerson();
		cout << "Cancelled!" << endl;
		return;
	}
	controlPhone(accounts);
	if (accountPhone == "-1") {
		setPerson();
		cout << "Cancelled!" << endl;
		return;
	}
	controlBalance();
	if (accountBalance == -1) {
		setPerson();
		cout << "Cancelled!" << endl;
		return;
	}
	controlPassword();
	if (accountPassword == "-1") {
		setPerson();
		cout << "Cancelled!" << endl;
		return;
	}
	cout << "\nYou have succesfully created your account" << endl;
	cout << "Please login to see your account." << endl;
}
void Account::displayProfile() {
	string upperPersonName = accountName;
	for (int i = 0; i < upperPersonName.length(); i++) {
		if (upperPersonName[i] == 'þ')
			upperPersonName[i] = 'Þ';
		else if (upperPersonName[i] == 'ç')
			upperPersonName[i] = 'Ç';
		else if (upperPersonName[i] == 'i')
			upperPersonName[i] = 'Ý';
		else if (upperPersonName[i] == 'ý')
			upperPersonName[i] = 'I';
		else if (upperPersonName[i] == 'ö')
			upperPersonName[i] = 'Ö';
		else if (upperPersonName[i] == 'ü')
			upperPersonName[i] = 'Ü';
		else if (upperPersonName[i] == 'ð')
			upperPersonName[i] = 'Ð';
	}
	transform(upperPersonName.begin(), upperPersonName.end(), upperPersonName.begin(), ::toupper);
	cout << upperPersonName << " Profile: " << endl;
	cout << "Name: " << accountName << endl << "Surname: " << accountSurname << endl << "Phone Number: " << accountPhone << endl
		<< "Balance: " << accountBalance << "$" << endl;
	cout << "--------------------------------------" << endl;
}
void Account::logoutAccount(Account* currentAccount) {
	cout << "You have succesfully logged out your current account!" << endl;
	if (accountReceipt) {
		receipt << "Successfully logged out of the \"" << currentAccount->accountName << "\" account." << endl;
	}
	currentAccount->setPerson();
}
void Account::deposit(Account* accounts, Account* currentAccount) {
	float amount;
	float oldBalance;
	oldBalance = currentAccount->accountBalance;
	cout << "Enter the amount you want to deposit: " << endl;
	cin >> amount;
	if (amount == -1) {
		cout << "Current process cancelled!." << endl;
		return;
	}
	currentAccount->accountBalance += amount;
	cout << "Deposited." << endl;
	cout << "Previous  Balance: " << oldBalance << "$";
	cout << " Current  Balance: " << currentAccount->accountBalance << "$" << endl;
	mergeObjects(accounts, currentAccount);
	if (accountReceipt) {
		receipt << "03. DEPOSÝT" << endl;
		receipt << amount << " dollars is deposited!" << endl;
		receipt << "Previous  Balance: " << oldBalance << "$";
		receipt << " Current  Balance: " << currentAccount->accountBalance << "$" << endl;
	}
}
void Account::withdraw(Account* accounts, Account* currentAccount) {
	float amount;
	float oldBalance;
	oldBalance = currentAccount->accountBalance;
	cout << "Enter the amount you want to withdraw?" << endl;
	do {
		cin >> amount;
		if (amount == -1) {
			cout << "Current process cancelled!." << endl;
			return;
		}
		if (amount > accountBalance)
			cout << "The amount exceeded account balance. Please enter the amount again." << endl;
	} while (amount > accountBalance);
	currentAccount->accountBalance -= amount;
	cout << "Withdrawed." << endl;
	cout << "Previous  Balance: " << oldBalance << "$";
	cout << " Current  Balance: " << currentAccount->accountBalance << "$" << endl;
	mergeObjects(accounts, currentAccount);
	if (accountReceipt) {
		receipt << "04. DEBÝT" << endl;
		receipt << amount << " dollars is withdrawed!" << endl;
		receipt << "Previous  Balance: " << oldBalance << "$";
		receipt << " Current  Balance: " << currentAccount->accountBalance << "$" << endl;
	}
}
void Account::showOtherAccounts(Account* accounts, Account* currentAccount) {
	cout << "\nOTHER ACCOUNTS\n" << endl;
	cout << "--------------------------------------" << endl;
	if (accounts[1].getAccountName() == "") {
		cout << "No other accounts found!" << endl;
		cout << "--------------------------------------" << endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (*currentAccount == accounts[i]) {
			continue;
		}
		if (accounts[i].getAccountName() == "") {
			break;
		}
		accounts[i].displayProfile();
	}

}
void Account::deleteAccount(Account* accounts, Account* currentAccount) {
	int j;
	string deletedName = currentAccount->accountName;
	for (int i = 0; i < 10; i++) {
		if (accounts[i] == *currentAccount) {
			cout << "--------------------------------------" << endl;
			cout << "CURRENT ACCOUNT HAS BEEN DELETED!" << endl;
			cout << "--------------------------------------" << endl;
			accounts[i].setPerson();
			currentAccount->setPerson();
			j = i;
			break;
		}
	}
	for (j; j < 9; j++) {
		accounts[j] = accounts[j + 1];
	}
	if (accountReceipt) {
		receipt << "06. DELETE THE ACCOUNT" << endl;
		receipt << "\"" << deletedName << "\" account has been deleted." << endl;
	}
	loginOrCreateAccount(accounts, currentAccount);
}
void Account::modifyAccount(Account* accounts, Account* currentAccount) {
	int num, i;
	string oldString, passwordCheck,option;
	cout << "Which information would you like to change in your account?" << endl;
	cout << "1.Name 2.Surname 3.Phone number 4.Password" << endl;
	while (true) {
		cin >> option;
		try {
			num = stoi(option);
			if (num >= 1 && num <= 4)
				break;
			if (num == -1) {
				cout << "The process of changing the name has been canceled." << endl;
				return;
			}
		}
		catch (...) {
			cout << "Invalid value. Please choose an option between 1-4" << endl;
		}
	}
	if (accountReceipt) {
		receipt << "07. MODIFY THE ACCOUNT" << endl;
	}
	switch (num) {
	case 1:
		oldString = currentAccount->accountName;
		controlName();
		if (accountName == "-1") {
			accountName = oldString;
			cout << "The process of changing the name has been canceled." << endl;
			return;
		}
		for (i = 0; i < 10; i++) {
			if (accounts[i].accountName == oldString && accounts[i].accountSurname == currentAccount->accountSurname) {
				accounts[i] = *currentAccount;
				break;
			}
		}
		cout << "You have successfulluy changed your name." << endl;
		if (accountReceipt)
			receipt << "The name \"" << oldString << "\" turned into \"" << accountName << "\"." << endl;
		break;
	case 2:
		oldString = currentAccount->accountSurname;
		controlSurname();
		if (accountSurname == "-1") {
			accountSurname = oldString;
			cout << "The process of changing the surname has been canceled." << endl;
			return;
		}
		for (i = 0; i < 10; i++) {
			if (accounts[i].accountName == currentAccount->accountName && accounts[i].accountSurname == oldString) {
				accounts[i] = *currentAccount;
				break;
			}
		}
		cout << "You have successfulluy changed your surname." << endl;
		if (accountReceipt)
			receipt << "The surname \"" << oldString << "\" turned into \"" << accountSurname << "\"." << endl;
		break;
	case 3:
		oldString = currentAccount->accountPhone;
		controlPhone(accounts);
		if (accountPhone == "-1") {
			accountPhone = oldString;
			cout << "The process of changing the phone number has been canceled." << endl;
			return;
		}
		mergeObjects(accounts, currentAccount);
		cout << "You have successfulluy changed your phone number." << endl;
		if (accountReceipt)
			receipt << "The phone number \"" << oldString << "\" turned into \"" << accountPhone << "\"." << endl;
		break;
	case 4:
		cout << "Are you certain that you would like to change your password?" << endl;
		while (true) {
			cin >> passwordCheck;
			if (passwordCheck == "no" || passwordCheck == "NO") {
				cout << "The process of changing the password has been canceled." << endl;
				return;
			}
			else if (passwordCheck == "yes" || passwordCheck == "YES") {
				break;
			}
			else
				cout << "Please enter yes to change the password or no to cancel the process" << endl;
		}
		oldString = currentAccount->accountPassword;
		controlPassword();
		if (accountPassword == "-1") {
			accountPassword = oldString;
			cout << "The process of changing the password has been canceled." << endl;
			return;
		}
		mergeObjects(accounts, currentAccount);
		cout << "\nYou have successfulluy changed your password." << endl;
		if (accountReceipt)
			receipt << "The phone number \"" << oldString << "\" turned into \"" << accountPassword << "\"." << endl;
		break;
	}
	mergeObjects(accounts, currentAccount);
	cout << "--------------------------------------" << endl;
}
void Account::sendMoney(Account* accounts, Account* currentAccount) {
	float amount, oldBalance;
	int accountNo, j = 0;
	string acc[10];
	oldBalance = currentAccount->accountBalance;
	cout << "Which account do you want to send money to?" << endl << endl;
	for (int i = 0; i < 10; i++) {
		if (*currentAccount == accounts[i]) {
			continue;
		}
		if (accounts[i].getAccountName() == "") {
			break;
		}
		cout << j + 1 << "." << accounts[i].getAccountName() << endl;
		acc[j] = accounts[i].getAccountName();
		j++;
	}
	if (j == 0) {
		cout << "No other accounts found!." << endl;
		return;
	}
	cin >> accountNo;
	if (accountNo == -1) {
		cout << "Current process cancelled!." << endl;
		return;
	}
	while (accountNo<0 || accountNo>j) {
		cout << "Please choose an option between 1-" << j << endl;
		cin >> accountNo;
	}
	for (int i = 0; i < 10; i++) {
		if (acc[accountNo - 1] == accounts[i].getAccountName())
			accountNo = i;
	}
	cout << "Enter the amount of money to be sent" << endl;
	while (true) {
		cin >> amount;
		if (amount == -1) {
			cout << "Current process cancelled!." << endl;
			return;
		}
		if (accountBalance < amount) {
			cout << "To be sent amount exceeded account balance. Please enter the amount of money to be sent correctly." << endl;
		}
		else {
			currentAccount->accountBalance -= amount;
			accounts[accountNo].accountBalance += amount;
			cout << "Transaction successful." << endl;
			cout << "Previous  Balance: " << oldBalance;
			cout << " Current  Balance: " << currentAccount->accountBalance << endl;
			break;
		}
	}
	mergeObjects(accounts, currentAccount);
	if (accountReceipt) {
		receipt << "08. SEND MONEY TO OTHER ACCOUNTS" << endl;
		receipt << amount << "$ sent to " << accounts[accountNo].accountName << endl;
		receipt << "Previous  Balance: " << oldBalance << "$";
		receipt << " Current  Balance: " << currentAccount->accountBalance << "$" << endl;
	}
}
auto characterInquiry = [](string nameOrSurname) {
	for (int i = 0; i < nameOrSurname.length(); i++) {
		unsigned char check = nameOrSurname.at(i);
		if (!((check >= 'A' && check <= 'Z') || (check == ' ') ||
			(check >= 'a' && check <= 'z') ||
			(int(check) >= 192 && int(check) <= 256))) {
			return false;
		}
	}
	return true;
};
void Account::controlName() {
	string name;
	cout << "Enter your name  " << endl;
	do {
		std::getline(std::cin, name);
	} while (name.length() == 0);
	while (true) {
		if (name == "-1") {
			accountName = "-1";
			return;
		}
		if (name.length() < 3) {
			cout << "The name is too short. Please enter your name again" << endl;
			continue;
		}
		else if (!(characterInquiry(name))) {
			cout << "the name cannot be contain special characters! Please enter your name again" << endl;
			continue;
		}
		else
			break;
	}
	accountName = name;
}
void Account::controlSurname() {
	string surname;
	cout << "Enter your surname  " << endl;
	while (true) {
		cin >> surname;
		if (surname == "-1") {
			accountSurname = "-1";
			return;
		}
		if (surname.length() < 3) {
			cout << "The surname is too short! Please enter your name again" << endl;
			continue;
		}
		else if (!(characterInquiry(surname))) {
			cout << "the surname cannot be contain special characters! Please enter your surname again" << endl;
			continue;
		}
		else
			break;
	}
	accountSurname = surname;
}
void Account::controlPhone(Account* accounts) {
	string phone;
	bool numberCheck=true;
	cout << "Enter your phone number" << endl;
	while (1) {
		numberCheck = true;
		cout << "05";
		cin >> phone;
		if (phone == "-1") {
			accountPhone = "-1";
			return;
		}
		phone = "05" + phone;
		if (phone.length() != 11) {
			cout << "Phone number length must be ten characters! Please enter your phone number again." << endl;
			numberCheck = false;
			continue;
		}
		for (unsigned i = 0; i < 10; i++) {
			if (accounts[i].getAccountPhone() == phone) {
				cout << "An account already exists for the phone number you entered! Please enter your phone number again." << endl;
				numberCheck = false;
			}
			if (!(phone.at(i) >= '0' && phone.at(i) <= '9')) {
				cout << "Your phone number must consist of numbers only. Please do not enter any characters other than numbers." << endl;
				numberCheck = false;
			}
		}
		if (numberCheck)
			break;
	}
	accountPhone = phone;
}
void Account::controlBalance() {
	string check;
	float balance;
	cout << "Enter yes to add your balance optionally. Enter no to not to do it" << endl;
	while (true) {
		cin >> check;
		if (check == "yes" || check == "YES") {
			cout << "Enter your balance" << endl;
			while (true) {
				cin >> balance;
				if (balance == -1) {
					accountBalance = -1;
					return;
				}
				if (balance >= 0)
					break;
				else
					cout << "The balance cannot be under 0. Please enter your balance again" << endl;
			}
			accountBalance = balance;
			break;
		}
		else if (check == "no" || check == "NO") {
			accountBalance = 0;
			break;
		}
		else
			cout << "Please enter yes or no for the account balance" << endl;
	}
	
}
void Account::controlPassword() {
	string password, confirmPassword;
	bool letter = false, number = false;
	char character;
	if (password == "-1") {
		accountPassword = "-1";
		return;
	}
	cout << "Choose a password" << endl;
	while ((character = _getch()) != '\r') {
		if (character == '\b') {
			if (!password.empty()) {
				std::cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			std::cout << "*";
			password += character;
		}
	}
	if (password.length() < 6) {
		cout << "\nPassword length must be at least six characters! Please retry again." << endl;
		controlPassword();
		return;
	}
	for (char ch : password) {
		if (ch == 'þ' || ch == 'Þ' || ch == 'ç' || ch == 'Ç' || ch == 'ü' || ch == 'Ü' || ch == 'ö' ||
			ch == 'Ö' || ch == 'ý' || ch == 'Ý')
			letter = true;
		else if (isalpha(ch))
			letter = true;
		else if (isdigit(ch))
			number = true;
	}
	if (!number || !letter) {
		cout << "\nPassword must contain both letters and numbers! Please retry again." << endl;
		controlPassword();
		return;
	}
	cout << "\nConfirm your password " << endl;
	while ((character = _getch()) != '\r') {
		if (character == '\b') {
			if (!confirmPassword.empty()) {
				std::cout << "\b \b";
				confirmPassword.pop_back();
			}
		}
		else {
			std::cout << "*";
			confirmPassword += character;
		}
	}
	if (password != confirmPassword) {
		cout << "\nPasswords do not match! Please retry again." << endl;
		controlPassword();
		return;
	}
	accountPassword = password;
}
void Account::controlReceipt() {
	string receiptCheck;
	cout << "Do you want a receipt for the transactions?" << endl;
	while (true) {
		cin >> receiptCheck;
		if (receiptCheck == "yes" || receiptCheck == "YES") {
			receipt.open("receipt.txt", ios::out);
			accountReceipt = true;
			break;
		}
		else if (receiptCheck == "no" || receiptCheck == "NO") {
			accountReceipt = false;
			break;
		}
		else
			cout << "Please enter yes for receipt or enter no for not a receipt." << endl;
	}
}
void Account::mergeObjects(Account* accounts, Account* currentAccount) {
	int i;
	for (i = 0; i < 10; i++) {
		if (accounts[i].accountName == currentAccount->accountName) {
			if (accounts[i].accountSurname == currentAccount->accountSurname)
				break;
		}
	}
	accounts[i] = *currentAccount;
}
