#include <iostream>
#include <map>
#include <string>
#include <limits>

struct details {
    std::string password;
    double balance;
};

std::map<std::string, details> AccountsMap;

void checkType(double amount) {
    while (!(std::cin >> amount) || typeid(amount).name() != typeid(double).name()) {
        std::cout << "Please enter a valid number: \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void createAccount() {
    std::string name;
    std::string password;
    std::cout << "Please enter a username:";
    std::cin >> name;
    std::cout << "Please enter a password:";
    std::cin >> password;
    std::cout << "Account successfully created\n";
    std::cout << "Account Name: " << name << std::endl << "Password: " << password << std::endl;

    details accountDetails;
    accountDetails.password = password;
    accountDetails.balance = 0.0;
    AccountsMap.insert({ name, accountDetails });
}

void signIn() {
    bool signedIn = false;
    while (!signedIn) {
        std::string user;
        std::string pass;
        std::cout << "Enter your username: ";
        std::cin >> user;
        std::cout << "Enter your password: ";
        std::cin >> pass;

        auto it = AccountsMap.find(user);
        if (it != AccountsMap.end()) {
            if (it->second.password == pass) {
                std::cout << "Successfully logged in.\n";
            }
            else {
                std::cout << "Incorrect password.\n";
            }
        }
        else {
            std::cout << "User not found. Please sign up.\n";
        }
    }
    
}


int main() {
    if (AccountsMap.empty()) {
        createAccount();
    }
    signIn();

    bool quit = false;
    while (!quit) {
        int userInput = 0;
        std::cout << "What would you like to do?\n";
        std::cout << "1. Add Money\n" << "2. Withdraw Money\n" << "3. Check Balance\n" << "4. Quit\n";
        std::cin >> userInput;

        if (userInput == 1) {
            double amount = 0.0;
            std::cout << "How much would you like to deposit?";
            std::cin >> amount;
            checkType(amount);
            AccountsMap.begin()->second.balance += amount;
            std::cout << "Money added successfully, you new balance is: $" << AccountsMap.begin()->second.balance << std::endl;
        }
        else if (userInput == 2) {
            double amount = 0.0;
            std::cout << "How much would you like to withdraw?";
            std::cin >> amount;
            checkType(amount);
            if (AccountsMap.begin()->second.balance >= amount) {
                AccountsMap.begin()->second.balance -= amount;
                std::cout << "Money withdrawn successfully\n";
            }
            else {
                std::cout << "Insufficient funds\n";
            }
        }
        else if (userInput == 3) {
            std::cout << "Your balance is: " << AccountsMap.begin()->second.balance << std::endl;
        }
        else if (userInput == 4) {
            std::cout << "Have a good day!";
            quit = true;
        }
        else {
            std::cout << "Invalid option, try again\n";
        }
    }

    return 0;
}
