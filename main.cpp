#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;
// them user info
// flag check limit
struct Customer{
    string ID;
    string PIN;
    int balance;
};

ostream& operator<<(ostream& os,const Customer& customer);
void appendCustomersToFile(const Customer& customer,const string& filename);
vector<Customer> readCustomersFromFile(const string& filename);
int to_int(const string& number);
Customer getInformationFromLine (const string& line);
int isAuthenticated(const string& ID, const string& PIN,const string& filename);

int main()
{
    vector<Customer>customers = readCustomersFromFile("customer_accounts.txt");
    for (Customer customer : customers){
        cout << customer << '\n';
    }
    cout << isAuthenticated("ABCDE","123456","customer_accounts.txt");
    return 0;
}

void appendCustomersToFile(const Customer& customer,const string& filename){
    ofstream outputFile(filename,ios::app);
    if(!outputFile.is_open()){
        cout << "Khong tim thay file\n";
        return;
    }
    outputFile << customer.ID << " " << customer.PIN << " " << customer.balance << "\n";
    outputFile.close();
}
vector<Customer> readCustomersFromFile(const string& filename){
    ifstream inputFile(filename);
    if(!inputFile.is_open()){
        cout << "Khong tim thay file\n";
        return {};
    }

    vector<Customer>customer_list;
    string inputLine;

    while (getline(inputFile,inputLine)){
        customer_list.push_back(getInformationFromLine(inputLine));
    }
    inputFile.close();
    return customer_list;
}
int to_int(const string& number){
    int result = 0;
    size_t n = number.size();
    for (size_t i = 0;i < n;++i){
        result = result * 10 + (number[i] - '0');
    }
    return result;
}
ostream& operator<<(ostream& os,const Customer& customer){
    os << customer.ID << " " << customer.PIN << " " << customer.balance;
    return os;
}
Customer getInformationFromLine(const string& line){
    size_t first_space = line.find(" ");
    size_t second_space = line.find(" ",first_space+1);
    Customer customer;

    customer.ID = line.substr(0,first_space);
    customer.PIN = line.substr(first_space+1,second_space-first_space-1);
    customer.balance = to_int(line.substr(second_space+1));

    return customer;
}
int isAuthenticated(const string& ID, const string& PIN, const string& filename){
    ifstream accounts_file(filename);
    if (!accounts_file.is_open()){
        cout << "Khong tim thay file!";
        return 0;
    }
    string account;
    while (getline(accounts_file,account)){
        Customer checker = getInformationFromLine(account);
        if (checker.ID == ID && checker.PIN == PIN) return 1;
    }
    accounts_file.close();
    return 0;
}
