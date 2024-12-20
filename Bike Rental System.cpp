#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <vector>
#include <cctype>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <unistd.h>
using namespace std;

class Bike
{
private:
    double SerialNumber;
    double RatingCount;
    double RatingSum;

public:
    bool isRented;
    double Rate = 0;
    const double cost;
    Bike() : SerialNumber(0), RatingCount(0), RatingSum(0), isRented(false), cost(0) {}
    Bike(double sn, double money) : SerialNumber(sn), RatingCount(0), RatingSum(0), isRented(false), Rate(0), cost(money) {}
    virtual ~Bike() {}
    double getSerialNum() const
    {
        return SerialNumber;
    }
    void setSerialNum(double sn)
    {
        SerialNumber = sn;
    }
    void AddRating(double rating)
    {
        RatingSum += rating;
        RatingCount++;
        Rate = (RatingSum / RatingCount);
    }
    virtual void Display() const
    {
        cout << "SerialNumber: " << SerialNumber << "  Cost: " << cost << "$" << "  Rented: " << (isRented ? "Yes" : "No");
        if (Rate != 0)
        {
            cout << "  Rate: " << Rate << endl;
        }
        else
            cout << endl;
    }
};

class ElectricBike : public Bike
{
public:
    bool charge;
    ElectricBike() : charge(false) {}
    ElectricBike(double sn, double money, bool ch) : Bike(sn, money), charge(ch) {}
    void Display() const override
    {
        Bike::Display();
        cout << "Charge " << (charge ? "Yes" : "No") << endl;
    }
};

class RoadBike : public Bike
{
public:
    RoadBike() {}
    RoadBike(double sn, double money) : Bike(sn, money) {}
    void Display() const override
    {
        Bike::Display();
        cout << "Type: RoadBike" << endl;
    }
};

class wallet
{
private:
    string Passkey;

public:
    int Id;
    double balance;
    wallet() : Id(0), balance(0) {}
    wallet(int uid) : Id(uid), balance(0.0) {}
    void SetPass(string &pass)
    {
        Passkey = pass;
    }
    string GetPass() { return Passkey; }
    void Display() const
    {
        cout << "ID: " << Id << "  Balance: " << balance << "$" << endl;
    }
};

class User
{
private:
    string Password;

public:
    wallet CustomersWallet;
    bool CheckWallet = false;
    vector<Bike *> CustomersBikes;
    int Rentedcount, Id;
    string Name;
    User() : Password(0), Rentedcount(0), Id(0) {}
    User(string password, int uid, string uname) : Password(password), Rentedcount(0), Id(uid), Name(uname) {}
    void Display() const
    {
        cout << "Name: " << Name << ", User Id: " << Id << endl;
        if (CheckWallet)
        {
            CustomersWallet.Display();
        }
    }
    bool CheckPass(string pass)
    {
        if (pass == Password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void SetPass(string upass)
    {
        Password = upass;
    }
    string GetPass()
    {
        return Password;
    }
};

vector<Bike *> Bikes;
vector<User *> Users;

void menu();
void DisplayAvailableBikes();
void DisplayRentedBike();
void ReturnBike();
void RentBike();
void AddBike();
void AddUser();
void BikeList();
void UserList();
void Information();
void LoadData();
int NumberCount(double);
void Chargewallet();
void Addwallet();
void Wallet();
/////////////////////////////////////////////////ArashGandomkar
int main()
{
    int choice;
    while (true)
    {
        cout << endl;
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            DisplayAvailableBikes();
            break;
        case 2:
            DisplayRentedBike();
            break;
        case 3:
            ReturnBike();
            break;
        case 4:
            RentBike();
            break;
        case 5:
            AddBike();
            break;
        case 6:
            AddUser();
            break;
        case 7:
            BikeList();
            break;
        case 8:
            UserList();
            break;
        case 9:
            Information();
            break;
        case 10:
            Wallet();
            break;
        case 11:
            LoadData();
            break;
        case 12:
            return 0;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
    for (auto bike : Bikes)
    {
        delete bike;
    }
    return 0;
}
/////////////////////////////////////////////////ArashGandomkar
void menu()
{
    cout << "<--Menu-->" << endl;
    cout << "1.Available Bike" << endl;
    cout << "2.Rented Bike" << endl;
    cout << "3.Return Bike" << endl;
    cout << "4.Rent Bike" << endl;
    cout << "5.Add Bike" << endl;
    cout << "6.Add user" << endl;
    cout << "7.Bike's list" << endl;
    cout << "8.User's list" << endl;
    cout << "9.My Information" << endl;
    cout << "10.Wallet" << endl;
    cout << "11.Load Data" << endl;
    cout << "12.Exit" << endl
         << endl;
    cout << "Pick a number: ";
}
void DisplayAvailableBikes()
{
    for (auto bike : Bikes)
    {
        if (!bike->isRented)
        {
            bike->Display();
        }
    }
    getch();
}
void DisplayRentedBike()
{
    for (auto bike : Bikes)
    {
        if (bike->isRented)
        {
            bike->Display();
        }
    }
    getch();
}

bool PassManager(string Password)
{
    Password.erase(remove(Password.begin(), Password.end(), ' '), Password.end());
    vector<char> Key(Password.begin(), Password.end());
    int PassCount = Key.size();
    if (PassCount >= 8)
    {
        int alpha = 0, number = 0, special = 0, upper = 0;
        for (char c : Key)
        {
            if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
            {
                special++;
            }
            else if (isalpha(c))
            {
                alpha++;
                if (isupper(c))
                {
                    upper++;
                }
            }
            else if (isdigit(c))
            {
                number++;
            }
        }
        if (alpha == 0)
        {
            cout << "Please enter at least one character.";
            getch();
            cout << endl;
        }
        if (alpha > 0 && upper == 0)
        {
            cout << "Please enter at least one uppercase character.";
            getch();
            cout << endl;
        }
        if (special == 0)
        {
            cout << "Please enter at least one special character.";
            getch();
            cout << endl;
        }
        if (number == 0)
        {
            cout << "Please enter at least one number.";
            getch();
            cout << endl;
        }
        if (alpha == 0 || upper == 0 || number == 0 || special == 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        cout << "Please enter at least 8 character.";
        getch();
        cout << endl;
        return false;
    }
}

string getPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = getch();
        if (ch == '\r')
        {
            break;
        }
        if (ch == '\b')
        {
            if (!password.empty())
            {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void ReturnBike()
{
    int uid;
    int attempts = 0;
    int maxAttempts = 3;
    while (true)
    {
        cout << "Enter your id: ";
        cin >> uid;
        cin.ignore();
        bool userFound = false;
        for (auto user : Users)
        {
            if (uid == user->Id)
            {
                userFound = true;
                string pass;
                cout << "Enter your password: ";
                pass = getPassword();
                if (user->CheckPass(pass))
                {
                    if (user->Rentedcount > 0 && user->Rentedcount < 4)
                    {
                        cout << endl
                             << "Your rented bikes:" << endl;
                        for (auto bike : user->CustomersBikes)
                        {
                            bike->Display();
                        }
                        double sn;
                        cout << "Enter a SerialNumber to return bike: ";
                        cin >> sn;
                        for (auto bike : Bikes)
                        {
                            if (bike->getSerialNum() == sn && bike->isRented)
                            {
                                bike->isRented = false;
                                cout << "Bike returned successfully." << endl;
                                user->Rentedcount--;
                                double rating;
                                cout << "Enter your rating for this bike(0 to 10): ";
                                cin >> rating;
                                if (rating >= 0 && rating <= 10)
                                {
                                    bike->AddRating(rating);
                                    if (rating < 5)
                                    {
                                        cout << "We will try to fix the problem." << endl;
                                        getch();
                                        return;
                                    }
                                    else if (rating > 5)
                                    {
                                        cout << "We are very glad that you had a good experience." << endl;
                                        getch();
                                        return;
                                    }
                                    getch();
                                    return;
                                }
                                else
                                {
                                    cout << "Invalid rate." << endl;
                                    getch();
                                    return;
                                }
                            }
                        }
                        cout << "Bike not found or not rented." << endl;
                        getch();
                        return;
                    }
                    else if (user->Rentedcount == 0)
                    {
                        cout << "You didn't have rent any bike to return." << endl;
                        getch();
                        return;
                    }
                }
                else if (!user->CheckPass(pass))
                {
                    attempts++;
                    cout << "Incorrect password. Attempt " << attempts << " of " << maxAttempts << "." << endl;
                    if (attempts >= maxAttempts)
                    {
                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                        usleep(10000000);
                        attempts = 0;
                        return;
                    }
                }
            }
        }
        if (!userFound)
        {
            cout << "Your Id is incorrect." << endl;
            getch();
            return;
        }
    }
}
////////////////////////////////////////////////////////New
void RentBike()
{
    int uid;
    int attempts = 0;
    int walletAttempts = 0;
    int maxAttempts = 3;
    while (true)
    {
        cout << "Enter your id: ";
        cin >> uid;
        cin.ignore();
        bool userFound = false;
        for (auto user : Users)
        {
            if (uid == user->Id)
            {
                userFound = true;
                string pass;
                cout << "Enter your password: ";
                pass = getPassword();
                if (user->CheckPass(pass))
                {
                    if (user->Rentedcount >= 0 && user->Rentedcount < 3)
                    {
                        cout << endl
                             << "AvailableBike:" << endl;
                        DisplayAvailableBikes();
                        double sn;
                        cout << "Enter a SerialNumber to rent bike: ";
                        cin >> sn;
                        cin.ignore();
                        for (auto bike : Bikes)
                        {
                            if (bike->getSerialNum() == sn && !bike->isRented)
                            {
                                if (user->CheckWallet)
                                {
                                    cout << endl
                                         << "Your wallet information is:    ID: " << user->CustomersWallet.Id << "      balance: " << user->CustomersWallet.balance << "$" << endl;
                                    string WalletPass;
                                    cout << "Enter password of your wallet: ";
                                    WalletPass = getPassword();
                                    if (user->CustomersWallet.GetPass() == WalletPass)
                                    {

                                        if (user->CustomersWallet.balance >= bike->cost)
                                        {

                                            bike->isRented = true;
                                            cout << "Bike rented successfully." << endl;
                                            user->CustomersBikes.push_back(bike);
                                            user->Rentedcount++;
                                            user->CustomersWallet.balance -= bike->cost;
                                            getch();
                                            return;
                                        }
                                        else if (user->CustomersWallet.balance < bike->cost)
                                        {
                                            cout << "Please charge your wallet." << endl;
                                            getch();
                                            return;
                                        }
                                    }
                                    else if (user->CustomersWallet.GetPass() != WalletPass)
                                    {
                                        walletAttempts++;
                                        cout << "Incorrect password. Attempt " << walletAttempts << " of " << maxAttempts << "." << endl;
                                        if (walletAttempts >= maxAttempts)
                                        {
                                            cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                                            usleep(10000000);
                                            walletAttempts = 0;
                                            return;
                                        }
                                        getch();
                                    }
                                }
                                else if (!user->CheckWallet)
                                {
                                    cout << "You don't have any wallet." << endl;
                                    getch();
                                    return;
                                }
                            }
                            else
                            {
                                cout << "Bike not found or already rented." << endl;
                                getch();
                                return;
                            }
                        }
                    }
                    else if (user->Rentedcount >= 3)
                    {
                        cout << "You have rented " << user->Rentedcount << " bikes, You can't rent any more." << endl;
                        getch();
                        return;
                    }
                }
                else if (!user->CheckPass(pass))
                {
                    attempts++;
                    cout << "Incorrect password. Attempt " << attempts << " of " << maxAttempts << "." << endl;
                    if (attempts >= maxAttempts)
                    {
                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                        usleep(10000000);
                        attempts = 0;
                        return;
                    }
                    getch();
                    return;
                }
            }
        }
        if (!userFound)
        {
            cout << "Your Id is incorrect." << endl;
            getch();
            return;
        }
    }
}
void AddBike()
{
    int type;
    double sn, money;
    cout << "Enter Bike type(1.ElectricBike , 2.RoadBike): ";
    cin >> type;
    cout << "Enter SerialNumber of your bike: ";
    cin >> sn;
    switch (type)
    {
    case 1:
        bool ch;
        cout << "Enter a charge(1.True , 0.False): ";
        cin >> ch;
        cout << "Enter a bicycle rental fee: ";
        cin >> money;
        Bikes.push_back(new ElectricBike(sn, money, ch));
        break;

    case 2:
        cout << "Enter a bicycle rental fee: ";
        cin >> money;
        Bikes.push_back(new RoadBike(sn, money));
        break;

    default:
        cout << "Invalid type." << endl;
    }
    getch();
}
void AddUser()
{
    string uname, pass;
    int uid;
    cout << "Enter your Name: ";
    cin >> uname;
    cout << "Enter your id: ";
    cin >> uid;
    cin.ignore();
    cout << "Enter your password (above 8 (character|upeercase character|special character|number)): ";
    getline(cin, pass);
    if (PassManager(pass))
    {
        Users.push_back(new User(pass, uid, uname));
    }
    getch();
}
void BikeList()
{
    for (auto bike : Bikes)
    {
        bike->Display();
    }
    getch();
}
void UserList()
{
    for (auto user : Users)
    {
        user->Display();
    }
    getch();
}
void LoadData()
{
    ifstream bikeFile("(The address of the selected file)/bikes.txt");
    ifstream userFile("(The address of the selected file)/users.txt");

    if (bikeFile.is_open())
    {
        double sn, money;
        int type;
        bool charge, Rented;
        while (bikeFile >> sn >> money >> type >> Rented)
        {
            if (type == 1)
            {
                bikeFile >> charge;
                ElectricBike *eBike = new ElectricBike(sn, money, charge);
                eBike->isRented = Rented;
                Bikes.push_back(eBike);
            }
            else if (type == 2)
            {
                RoadBike *rBike = new RoadBike(sn, money);
                rBike->isRented = Rented;
                Bikes.push_back(rBike);
            }
        }
        bikeFile.close();
    }
    else
    {
        cout << "Unable to open bikes.txt File." << endl;
        getch();
        return;
    }
    if (userFile.is_open())
    {
        int id;
        string name, pass;
        while (userFile >> pass >> id >> name)
        {
            Users.push_back(new User(pass, id, name));
        }
        userFile.close();
    }
    else
    {
        cout << "Unable to open users.txt File." << endl;
        getch();
        return;
    }
}
int NumberCount(double num)
{
    int count = 0;
    while (num >= 1)
    {
        num /= 10;
        count++;
    }
    return count;
}
void ShowData();
void ChangeData();
void InformationMenu()
{
    cout << "1.Show Information" << endl;
    cout << "2.Change Information" << endl;
    cout << "3.Main Menu" << endl
         << endl;
    cout << "Pick a number: ";
}

void Information()
{

    int choose;
    while (true)
    {
        cout << endl;
        InformationMenu();
        cin >> choose;
        switch (choose)
        {
        case 1:
            ShowData();
            break;
        case 2:
            ChangeData();
            break;
        case 3:
            return;
            break;

        default:
            cout << "Invalid choice." << endl;
        }
    }
}
void ShowData()
{
    int uid;
    string upass;
    int attempts = 0;
    int maxAttempts = 3;
    while (true)
    {
        cout << "Enter your id: ";
        cin >> uid;
        cin.ignore();
        for (auto user : Users)
        {
            if (user->Id == uid)
            {
                cout << "Enter your password: ";
                upass = getPassword();
                if (user->CheckPass(upass))
                {
                    user->Display();
                    int answer;
                    cout << "Do you want to see your password(1 for YES, 2 for NO)? ";
                    cin >> answer;
                    if (answer == 1)
                    {
                        cout << "Your password is " << user->GetPass() << "." << endl;
                        getch();
                        return;
                    }
                    else if (answer == 2)
                    {
                        getch();
                        return;
                    }
                }
                else if (!user->CheckPass(upass))
                {
                    attempts++;
                    cout << "Incorrect password. Attempt " << attempts << " of " << maxAttempts << "." << endl;
                    if (attempts >= maxAttempts)
                    {
                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                        usleep(10000000);
                        attempts = 0;
                        return;
                    }
                }
                else if (user->Id != uid)
                {
                    cout << "Your id is incorrect." << endl;
                    getch();
                    return;
                }
            }
        }
    }
}
void ChangeDataMenu()
{
    cout << "1.Change Name" << endl;
    cout << "2.Change Password" << endl;
    cout << "3.Change Wallet's Password" << endl;
    cout << "4.Change Id" << endl;
    cout << "5.Main Menu" << endl
         << endl;
    cout << "Pick a number: ";
}

void ChangeData()
{
    int uid;
    string upass;
    int attempts = 0;
    int walletAttempts = 0;
    int maxAttempts = 3;
    while (true)
    {
        cout << "Enter your id: ";
        cin >> uid;
        cin.ignore();
        for (auto user : Users)
        {
            if (user->Id == uid)
            {
                cout << "Enter your password: ";
                upass = getPassword();
                if (user->CheckPass(upass))
                {
                    while (true)
                    {
                        cout << endl;
                        ChangeDataMenu();
                        int choice;
                        cin >> choice;
                        if (choice == 1)
                        {
                            string uname;
                            cout << "Enter your new Name: ";
                            cin >> uname;
                            user->Name = uname;
                            cout << "Your Name changed to " << user->Name << " successfully." << endl;
                            getch();
                        }

                        else if (choice == 2)
                        {
                            string upass;
                            cout << "Enter your new password: ";
                            cin.ignore();
                            getline(cin, upass);
                            if (PassManager(upass))
                            {
                                user->SetPass(upass);
                                cout << "Your password changed to " << user->GetPass() << " successfully." << endl;
                            }
                            else if (!PassManager(upass))
                            {
                                return;
                            }
                            getch();
                        }

                        else if (choice == 3)
                        {
                            if (user->CheckWallet)
                            {
                                string WalletPass;
                                user->CustomersWallet.Display();
                                cout << "Enter a current password: ";
                                cin.ignore();
                                WalletPass = getPassword();
                                if (user->CustomersWallet.GetPass() == WalletPass)
                                {
                                    string newWalletPass;
                                    cout << "Enter the new password: ";
                                    getline(cin, newWalletPass);
                                    if (PassManager(newWalletPass))
                                    {
                                        user->CustomersWallet.SetPass(newWalletPass);
                                        cout << "Your password has been successfully changed." << endl;
                                        getch();
                                    }
                                    else
                                    {
                                        getch();
                                        return;
                                    }
                                }
                                else if (user->CustomersWallet.GetPass() != WalletPass)
                                {
                                    walletAttempts++;
                                    cout << "Incorrect password. Attempt " << walletAttempts << " of " << maxAttempts << "." << endl;
                                    if (walletAttempts >= maxAttempts)
                                    {
                                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                                        usleep(10000000);
                                        walletAttempts = 0;
                                    }
                                    getch();
                                }
                            }
                            else if (!user->CheckWallet)
                            {
                                cout << "You don't have any wallet." << endl;
                                getch();
                            }
                        }

                        else if (choice == 4)
                        {
                            int uid;
                            cout << "Enter your new ID: ";
                            cin >> uid;
                            user->Id = uid;
                            cout << "Your ID changed to " << user->Id << " successfully.";
                            getch();
                        }

                        else if (choice == 5)
                        {
                            return;
                        }

                        cout << "Invalid choice." << endl;
                    }
                }
                else if (!user->CheckPass(upass))
                {
                    attempts++;
                    cout << "Incorrect password. Attempt " << attempts << " of " << maxAttempts << "." << endl;
                    if (attempts >= maxAttempts)
                    {
                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                        usleep(10000000);
                        attempts = 0;
                        return;
                    }
                }
            }
            else if (user->Id != uid)
            {
                cout << "Your id is incorrect." << endl;
                getch();
                return;
            }
        }
    }
}
void Addwallet()
{
    int uid;
    string upass;
    cout << "Enter your ID: ";
    cin >> uid;
    cin.ignore();
    bool userFound = false;
    for (auto user : Users)
    {
        if (uid == user->Id)
        {
            userFound = true;
            cout << "Enter your password: ";
            upass = getPassword();
            if (user->CheckPass(upass))
            {
                // Get Data for Wallet
                double WalletID;
                string WalletPass;
                srand(static_cast<unsigned int>(time(0)));
                WalletID = rand();
                cout << "Enter password for your wallet: ";
                getline(cin, WalletPass);
                if (PassManager(WalletPass))
                {
                    user->CustomersWallet = wallet(WalletID);
                    user->CustomersWallet.SetPass(WalletPass);
                    user->CheckWallet = true;
                    user->CustomersWallet.Display();
                    getch();
                    return;
                }
                else
                {
                    getch();
                    return;
                }
            }
            else if (!user->CheckPass(upass))
            {
                cout << "Your password is incorrect." << endl;
                getch();
                return;
            }
        }
        if (!userFound)
        {
            cout << "Your Id is incorrect." << endl;
            getch();
            return;
        }
    }
}

void Chargewallet()
{
    int uid;
    string upass;
    int attempts = 0;
    int walletAttempts = 0;
    int maxAttempts = 3;
    while (true)
    {
        cout << "Enter your ID: ";
        cin >> uid;
        cin.ignore();
        bool userFound = false;
        for (auto user : Users)
        {
            if (uid == user->Id)
            {
                userFound = true;
                cout << "Enter your password: ";
                upass = getPassword();
                if (user->CheckPass(upass))
                {
                    if (user->CheckWallet)
                    {
                        cout << "Your wallet information is:    ID: " << user->CustomersWallet.Id << "      balance: " << user->CustomersWallet.balance << "$" << endl;
                        double charge;
                        string WalletPass;
                        cout << "Enter password of your wallet: ";
                        WalletPass = getPassword();
                        if (user->CustomersWallet.GetPass() == WalletPass)
                        {
                            cout << "How much that you want charge your wallet? ";
                            cin >> charge;
                            user->CustomersWallet.balance += charge;
                            user->CustomersWallet.Display();
                            getch();
                            return;
                        }
                        else if (user->CustomersWallet.GetPass() != WalletPass)
                        {
                            walletAttempts++;
                            cout << "Incorrect password. Attempt " << walletAttempts << " of " << maxAttempts << "." << endl;
                            if (walletAttempts >= maxAttempts)
                            {
                                cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                                usleep(10000000);
                                walletAttempts = 0;
                                return;
                            }
                            getch();
                        }
                    }
                    else if (!user->CheckWallet)
                    {
                        cout << "You don't have any wallet." << endl;
                        getch();
                        return;
                    }
                }
                else if (!user->CheckPass(upass))
                {
                    attempts++;
                    cout << "Incorrect password. Attempt " << attempts << " of " << maxAttempts << "." << endl;
                    if (attempts >= maxAttempts)
                    {
                        cout << "Too many incorrect attempts. Please wait 10 seconds before trying again." << endl;
                        usleep(10000000);
                        attempts = 0;
                        return;
                    }
                }
            }
            if (!userFound)
            {
                cout << "Your Id is incorrect." << endl;
                getch();
                return;
            }
        }
    }
}

void Wallet()
{
    int choice;
    cout << endl;
    while (true)
    {
        cout << endl;
        cout << "1.Create Wallet" << endl;
        cout << "2.Charge Wallet" << endl;
        cout << "3.Main Menu" << endl
             << endl;
        cout << "Pick a Number: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Addwallet();
            break;
        case 2:
            Chargewallet();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}
/////////////////////////////////////////////////ArashGandomkar