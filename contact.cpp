#include "contact.h"
// TODO: Add needed libraries! 

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this->type = type;
    this->email_addr = email_addr;
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    cin >> type;
    cout << "Enter email address: ";
    // some code here
    cin >> email_addr;
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it!
    // TODO: Complete this method!
    // Note: We don't want to use C++11! stol is not valid!
    this->type = type;
    for (char& c : num) {
        if (c != '-') {
            this->phone_num += c;
        }
    }

}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
    cin >> type;
	cout << "Enter the phone number: ";
    string raw;
    cin >> raw;
    phone_num = "";
    for (char& c : raw) {
        if (c != '-') phone_num += c;
    }
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    if (style == "full") {
        return "Phone (" + type + "): " + phone_num.substr(0, 3) + "-" + phone_num.substr(3, 3) + "-" + phone_num.substr(6);
    } else {
        return phone_num;
    }
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}
