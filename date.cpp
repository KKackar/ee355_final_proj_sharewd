#include "date.h"
#include <iostream>
#include <string>
using namespace std;

Date::Date(string input_date) {
    date = input_date;
}

void Date::print_date(string format) {
    if (format == "Month D, YYYY") {
        cout << get_date_string() << endl;
    } else {
        cout << date << endl;
    }
}

string Date::get_date_string() {
    string months[12] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    int pos_first_slash = date.find("/");
    int pos_second_slash = date.find("/", pos_first_slash + 1);

    if (pos_first_slash == -1 || pos_second_slash == -1) {
        return "incorrect date format";
    }

    int month = stoi(date.substr(0, pos_first_slash));
    int day = stoi(date.substr(pos_first_slash + 1, pos_second_slash - pos_first_slash - 1));
    int year = stoi(date.substr(pos_second_slash + 1));

    if ((month < 1) || (month > 12) || (day < 1) ||( day > 31) || (year > 2026)) {
        return "incorrect date";
    }

    return months[month - 1] + " " + to_string(day) + ", " + to_string(year);
}
bool Date::operator==(const Date& rhs) const {
    return this->date == rhs.date;
}
