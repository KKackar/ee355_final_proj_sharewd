
#include "person.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    delete email;
    delete phone;
}


Person::Person(string f_name, string l_name, string b_date, string email_str, string phone_str){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = f_name;
    this->l_name = l_name;
    birthdate = new Date(b_date);

    int pos1_etype = email_str.find("(") + 1;
    int pos2_etype = email_str.find(")");
    string etype = email_str.substr(pos1_etype, pos2_etype - pos1_etype);
    string eaddr = email_str.substr(pos2_etype + 2);
    email = new Email(etype, eaddr);

    int pos1_ptype = phone_str.find("(") + 1;
    int pos2_ptype = phone_str.find(")");
    string ptype = phone_str.substr(pos1_ptype, pos2_ptype - pos1_ptype);
    string pnum = phone_str.substr(pos2_ptype + 2);
    phone = new Phone(ptype, pnum);






}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;

    string addr;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    getline(cin, type);
    
    cout << "Email address: ";
    getline(cin, addr);
    email = new Email(type, addr);
    

    cout << "Type of phone number: ";
    getline(cin, type);
    cout << "Phone number: ";
    getline(cin, addr);
    phone = new Phone(type, addr);
}


void Person::set_person(string filename){
    // reads a Person from a file
    ifstream infile(filename);
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    string line;
    getline(infile, f_name);
    getline(infile, l_name);
    getline(infile, line);

    birthdate = new Date(line);

    getline(infile, line); //email
    int pos1_etype = line.find('(') + 1;
    int pos2_etype = line.find(')');
    string etype = line.substr(pos1_etype, pos2_etype - pos1_etype);
    string eaddr = line.substr(pos2_etype + 2);
    email = new Email(etype, eaddr);

    getline(infile, line); // phone
    int pos1_ptype = line.find('(') + 1;
    int pos2_ptype = line.find(')');
    string ptype = line.substr(pos1_ptype, pos2_ptype - pos1_ptype);
    string pnum = line.substr(pos2_ptype + 2);
    phone = new Phone(ptype, pnum);


}


bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
        if((f_name==rhs.f_name) && (l_name == rhs.l_name) && (*birthdate == *(rhs.birthdate))){
        return true;
    }
    else{
        return false;
    }
}

bool Person::operator!=(const Person& rhs){ 
    return !(*this == rhs);


}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    phone->print();
    email->print();
}