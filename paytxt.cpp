#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;

void pause() {
  string pause_input;
  cout << "enter C to continue ";
  cin >> pause_input;
  system("clear");
}

class user {
private:
  string password;
  string username;
  double balance;

public:
  user() {
    password = "";
    username = "nonexistent user";
    balance = 0.0;
  } // default initalizer

  user(string u, string p, double b) {
    password = p;
    username = u;
    balance = b;
  } // initializer of class

  string get_username() { return username; }

  double get_balance() { return balance; }

  bool has_balance(double amount) {
    if (amount <= balance) {
      balance -= amount;
      return true;
    } else {
      return false;
    }
  }

  void display_new_balance() {
    cout << "your new balance is " << balance << " cryptocoins" << endl;
    pause();
  }

  void receive(double amount) { balance += amount; }

  void buy() {
    double amount;
    cout << "how much cryptocurrency do you wish to buy? ";
    cin >> amount;
    cout << "this amount of cryptocurrency costs " << amount * 50 << " dollars"
         << endl;
    balance += amount;
    display_new_balance();
  }

  void sell() {
    double amount;

    while (true) {
      cout << "how much cryptocurrency do you wish to sell? ";
      cin >> amount;
      if (amount <= balance) {
        balance -= amount;
        cout << "operation successful" << endl;
        cout << "the total for which this sold is: " << (amount * 50)
             << " dollars" << endl;
        display_new_balance();
        break;
      } else {
        cout << "not enough cryptocurrency for this operation. " << endl;
      }
    }
  }

  void check_balance() {
    cout << "your balance is " << balance << " cryptocurrency" << endl;
    pause();
  }

  void check_password() {
    string password_input;

    while (true) {
      cout << "enter password: ";
      cin >> password_input;
      if (password_input == password) {
        system("clear");
        cout << "login successful" << endl << endl;
        cout << "Welcome " << username << "!" << endl;
        break;
      } else {
        cout << "wrong password, try again" << endl << endl;
      }
    }
  }
};

user user_list[]{
    {"john", "1940", 101},  {"paul", "1942", 100},  {"george", "1943", 50},
    {"ringo", "1940", 0},   {"brian", "1934", 150}, {"jim", "1943", 25},
    {"arca", "1989", 200},  {"alan", "2022", 25},   {"luis", "2004", 300},
    {"sofia", "2005", 300},

};

void pay(int from, int to) {
  double amount;
  int receipt;

  while (true) {
    cout << "how much to pay? ";
    cin >> amount;

    if (user_list[from].has_balance(amount)) {
      user_list[to].receive(amount);

      cout << "payment complete" << endl << endl;

      cout << "would you like a receipt?" << endl;
      cout << "press 1 for receipt or 0 to ignore" << endl;
      cin >> receipt;

      if (receipt == 1) {
        ofstream file("receipt.txt");

        file << "┌────────────────┐" << endl;
        file << "receipt of payment" << endl;
        file << "paid to: " << user_list[to].get_username() << endl;
        file << "total: " << amount << " cryptocoins" << endl;
        file << "total in dollars: " << (amount * 50) << endl << endl;
        file << "USERNAME: " << user_list[from].get_username() << endl;
        file << "USER ID: " << user_list[from].get_username() << endl;
        file << "The App payment" << endl;
        file << "        ✎" << endl;
        file << "└────────────────┘" << endl;

        file.close();
        cout << "receipt printed successfully" << endl << endl;
      }

      user_list[from].display_new_balance();
      break;

    } else {
      cout << "not enough cryptocurrency for this operation." << endl;
      cout << "your balance is " << user_list[from].get_balance() << endl;
    }
  }
}

void transfer(int from, int to) {
  bool success = false;
  int amount;
  while (true) {
    cout << "how much do you wish to transfer? ";
    cin >> amount;
    if (user_list[from].has_balance(amount)) {
      user_list[to].receive(amount);
      cout << "Transfer complete" << endl;
      user_list[from].display_new_balance();
      break;
    } else {
      cout << "not enough cryptocurrency for this operation. " << endl;
    }
  }
}

int get_user_index() {
  string username_input = "";
  int len_usr = sizeof(user_list) / sizeof(user_list[0]);

  while (true) {
    cin >> username_input;
    for (int i = 0; i < len_usr; i++) {
      if (user_list[i].get_username() == username_input) {
        return i;
      }
    }
    cout << "account not found" << endl;
    cout << "enter username: ";
  }
  return -1;
}

int display_main_menu() {
  int choice = 0;
  system("clear");
  cout << "≪ Welcome to the app ≫" << endl;
  cout << "This app uses a cryptocurrency equivalent to 50 dollars" << endl
       << endl;

  while (true) {
    cout << "Press 1 to login" << endl;
    cout << "Press 0 to exit" << endl;
    cin >> choice;

    if (choice == 0 || choice == 1) {
      system("clear");
      return choice;

    } else {
      cout << "option not recognized" << endl << endl;
    }
  }
}

int display_user_menu() {
  int choice;

  cout << "What would you like to do today?" << endl << endl;
  cout << "press 0 to logout" << endl;
  cout << "press 1 to buy cryptocurrency" << endl;
  cout << "press 2 to sell cryptocurrency" << endl;
  cout << "press 3 to pay" << endl;
  cout << "press 4 to transfer" << endl;
  cout << "press 5 to check balance" << endl << endl;

  while (true) {
    cin >> choice;
    if (choice == 0 || choice == 1 || choice == 2 || choice == 3 ||
        choice == 4 || choice == 5) {
      return choice;
    } else {
      cout << "invalid input, try again" << endl;
    }
  }
}

int main() {
  while (true) {
    int choice = 0;
    choice = display_main_menu();

    if (choice == 1) {
      cout << "enter username: ";
      int current_user = get_user_index();
      user_list[current_user].check_password();
      while (true) {
        choice = display_user_menu();
        if (choice == 0) { // logout
          break;
        } else if (choice == 1) { // buy cryptocurrency
          user_list[current_user].buy();
        } else if (choice == 2) { // sell cryptocurrency
          user_list[current_user].sell();
        } else if (choice == 3) { // pay
          cout << "who are you paying to? ";
          int to = get_user_index();
          pay(current_user, to);
        } else if (choice == 4) { // transfer
          cout << "who do you want to transfer to? ";
          int transferee = get_user_index();
          transfer(current_user, transferee);
        } else if (choice == 5) { // check balance
          user_list[current_user].check_balance();
        }
      }
    } else if (choice == 0) {
      break;
    }
  }
} // end of main