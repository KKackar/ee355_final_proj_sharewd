#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
using namespace std;

class Date {
private:
    string date;

public:
    Date(string input_date);
    void print_date(string format = "Month D, YYYY");
    bool operator==(const Date& rhs) const;

    string get_date_string();
};

#endif
