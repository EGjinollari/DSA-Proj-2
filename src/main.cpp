#include "RBTree/rbforest.h"
#include "BTree/bforest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

    BForest b_tree;

    RBForest rb_immigrant_data;
    ifstream file("src/immigrants.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }
    
    string ln;
    getline(file, ln);
    int id = 1;
    
    while (getline(file, ln)) {
        cout << ln << endl;
        stringstream ss(ln);
        string given_name, family_name, gender, birth_date, origin_country, dest_country, rest;

        getline(ss, given_name, ',');
        getline(ss, family_name, ',');
        getline(ss, birth_date, ',');
        getline(ss, origin_country, ',');
        getline(ss, dest_country, ',');

        string bday_num;
        for (char c : birth_date) {
            if (isdigit(c)) bday_num += c;
        }
        int bday = 0;
        bday = stoi(bday_num);
        rb_immigrant_data.Insert(id, given_name, family_name, bday, origin_country, dest_country);
        id++;
    }

    file.close();
    cout << "Inserted " << (id - 1) << " records into the RB tree.\n\n";

    while (true) {
        cout << "Search categories: id | first | last | birthday | origin | destination\n";
        cout << "Enter category (or 'exit' to quit): ";
        string category;
        getline(cin, category);
        if (category == "exit") break;

        cout << "Enter value to search for: ";
        string value;
        getline(cin, value);

        vector<Person*> results = rb_immigrant_data.Search(category, value);

        if (results.empty()) {
            cout << "No matches found.\n\n";
        } else {
            cout << "\n--- Search Results ---\n";
            for (auto p : results) {
                cout << "ID: " << p->get_id()
                     << " | Name: " << p->get_first() << " " << p->get_last()
                     << " | Birthday: " << p->get_birthday()
                     << " | Origin: " << p->get_origin()
                     << " | Destination: " << p->get_destination()
                     << "\n";
            }
            cout << endl;
        }
    }

    cout << "Goodbye!\n";
    return 0;
}