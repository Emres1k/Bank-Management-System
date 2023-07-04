#include "Bank.h"
int main()
{
    SetConsoleCP(1254);
    SetConsoleOutputCP(1254);
    Account* currentAccount = new Account();
    Account* accounts = new Account[10];
    accounts[0].setPerson("Furkan", "Kerem", 12500, "05302001010", "furkan123");
    accounts[1].setPerson("Kadir", "Yılmaz", 6000, "05003223220", "kadiryilmaz");
    accounts[2].setPerson("Fatih", "Kaya", 3250.23, "05003004010", "fatih1010");
    accounts[3].setPerson("Erdem", "Tutmuş", 680.78, "05001001010", "tutmuşerdem");
    currentAccount->controlReceipt();
    currentAccount->loginOrCreateAccount(accounts, currentAccount);
    currentAccount->mainMenu();
    bool isExit = false;
    while (!isExit) {
        switch (currentAccount->options()) {
        case 1:
            currentAccount->displayProfile();
            break;
        case 2:
            currentAccount->logoutAccount(currentAccount);
            currentAccount->loginOrCreateAccount(accounts, currentAccount);
            currentAccount->mainMenu();
            break;
        case 3:
            currentAccount->deposit(accounts, currentAccount);
            break;
        case 4:
            currentAccount->withdraw(accounts, currentAccount);
            break;
        case 5:
            currentAccount->showOtherAccounts(accounts, currentAccount);
            break;
        case 6:
            currentAccount->deleteAccount(accounts, currentAccount);
            break;
        case 7:
            currentAccount->modifyAccount(accounts, currentAccount);
            break;
        case 8:
            currentAccount->sendMoney(accounts, currentAccount);
            break;
        case 9:
            cout << "We look forward to welcoming you back to our bank." << endl;
            isExit = true;
            delete[] accounts, currentAccount;
            accounts = nullptr;
            currentAccount = nullptr;
            break;
        case 10:
            currentAccount->mainMenu();
            break;
        }
    }
    return 0;
}