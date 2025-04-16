#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}

Network::Network(string fileName){
    loadDB(fileName);
}

Network::~Network(){ 
    Person* current = head;
    while (current != NULL) {
        Person* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = NULL;
    count = 0;
}

Person* Network::search(Person* searchEntry){
    Person* current = head;
    while (current != NULL) {
        if (*current == *searchEntry) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

Person* Network::search(string fname, string lname){
    Person* current = head;
    while (current != NULL) {
        if (((current -> f_name) == fname) && ((current ->l_name) == lname)) {
            return current;
        }
        current = current -> next;
    }
    return NULL;
}

void Network::loadDB(string filename){
    ifstream infile(filename);
    Person* current;
    string line;
    while (!infile.eof()) {
        ofstream temp("temp.txt"); 
        for (int i = 0; i < 5; i++) {
            if (getline(infile, line)) temp << line << endl;
        }
        temp.close();
        current = new Person("temp.txt");
        push_back(current);
        getline(infile, line); 
    }
    infile.close();
}

void Network::saveDB(string filename){
    ofstream outfile(filename);
    if(!outfile.is_open()){
        cerr << "Error opening file " << filename << endl;
        return;
    }
    Person* current = head;
    while (current != NULL) {
        outfile << current->f_name << endl;
        outfile << current->l_name << endl;

        if (current->birthdate != nullptr) {
            outfile << current->birthdate->get_date_string() << endl;
        } else {
            outfile << "No birthdate available" << endl;
        }

        if (current->email != nullptr) {
            outfile << current->email->get_contact("full") << endl;
        } else {
            outfile << "No email available" << endl;
        }

        if (current->phone != nullptr) {
            outfile << current->phone->get_contact("full") << endl;
        } else {
            outfile << "No phone available" << endl;
        }

        if (current->next != NULL) {
            outfile << "--------------------" << endl;
        }
        current = current->next;
    }
    outfile.close();
}

void Network::printDB(){
    cout << "Number of people: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}

void Network::push_front(Person* newEntry){
    newEntry->prev = NULL;
    newEntry->next = head;
    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    head = newEntry;
    count++;
}

void Network::push_back(Person* newEntry){
    newEntry->next = NULL;
    newEntry->prev = tail;
    if (tail != NULL)
        tail->next = newEntry;
    else
        head = newEntry;
    tail = newEntry;
    count++;
}

bool Network::remove(string fname, string lname){
    Person* target = search(fname, lname);
    if (target == NULL) {
        return false;
    }
    if (target->prev != NULL){
        target->prev->next = target->next;
    }
    else{
        head = target->next;
    }
    if (target->next != NULL){
        target->next->prev = target->prev;
    }
    else{
        tail = target->prev;
    }
    delete target;
    count--;
    return true;
}

void Network::showMenu(){
    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner");

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Remove a person \n";
        cout << "5. Print people with last name  \n";
        cout << "\nSelect an option ... ";

        if (cin >> opt) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }

        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            getline(cin, fileName);
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            cout << "Loading network database \n";
            for (const auto& entry : fs::directory_iterator(".")) {
                if (entry.path().extension() == ".txt")
                    cout << entry.path().filename() << endl;
            }
            cout << "Enter the name of the load file: "; 
            getline(cin, fileName);
            ifstream infile(fileName);
            if (!infile.good()) {
                cout << "File " << fileName << " does not exist!" << endl;
            }
            else {
                head = tail = NULL;
                count = 0;
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " people \n";
            }
        }
        else if (opt == 3){
            cout << "Adding a new person \n";
            Person* newP = new Person();
            if (search(newP) == NULL) {
                push_front(newP);
            } 
            else {
                cout << "Person already exists! \n";
                delete newP;
            }
        }
        else if (opt == 4){
            cout << "Removing a person \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);
            if (remove(fname, lname)) {
                cout << "Remove Successful! \n";
            } 
            else {
                cout << "Person not found! \n";
            }
        }
        else if (opt==5){
            cout << "Print people with last name \n";
            cout << "Last name: ";
            getline(cin, lname);
            bool found = false;
            Person* current = head;
            while (current != NULL) {
                if (current->l_name == lname) {
                    current->print_person();
                    cout << "------------------------------" << endl;
                    found = true;
                }
                current = current->next;
            }
            if (!found) {
                cout << "Person not found! \n";
            }
        }
        else{
            cout << "Nothing matched!\n";
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}
