#include "RBTree/rbforest.h"
#include "BTree/bforest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <windows.h>

using namespace std;

int main() {

    BForest b_immigrant_data;

    RBForest rb_immigrant_data;
    ifstream file("src/immigrants.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }
    
    string ln;
    getline(file, ln);
    int id = 1;

    auto start_time = std::chrono::high_resolution_clock::now();

    while (getline(file, ln)) {
        cout << ln << endl;
        stringstream ss(ln);
        string given_name, family_name, birth_date, origin_country, dest_country;

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
    auto duration = std::chrono::high_resolution_clock::now() - start_time;
    file.close();
    cout << "Inserted " << (id - 1) << " records into the RB tree.\n\n";
    cout << "This took: " << duration.count() / 1000000000.0 << " seconds"<< endl << "On average a Red Black Tree insertion took: " <<
    duration.count() / (id - 1) / 1000000000.0 << " seconds" << endl;

    Sleep(5000);

    file.open("src/immigrants.csv"); 
    if (!file.is_open()) {
        cerr << "Error: Could not open file.\n";
        return 1;
    }
    
    getline(file, ln);
    id = 1;

    start_time = std::chrono::high_resolution_clock::now();

    while (getline(file, ln)) {
        cout << ln << endl;
        stringstream ss(ln);
        string given_name, family_name, birth_date, origin_country, dest_country;

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
        b_immigrant_data.Insert(id, given_name, family_name, bday, origin_country, dest_country);
        id++;
    }
    duration = std::chrono::high_resolution_clock::now() - start_time;
    file.close();
    cout << "Inserted " << (id - 1) << " records into the B-tree.\n\n";
    cout << "This took: " << duration.count() / 1000000000.0 << " seconds"<< endl << "On average a B-Tree insertion took: " <<
    duration.count() / (id - 1) / 1000000000.0 << " seconds" << endl;
    
    id --;


    while (true) {       
        cout << "Enter an action (or 'exit' to quit): " << endl;
        
        cout << "Choose an action: add | search | delete" << endl;
        string action;
        getline(cin, action);
        if (action == "exit") break;
        else if (action == "add"){
            cout << "Enter given name: ";
            string given_name;
            getline(cin, given_name);

            cout << "Enter family name: ";
            string family_name;
            getline(cin, family_name);

            cout << "Enter birth date (YYYYMMDD): ";
            string birth_date;
            getline(cin, birth_date);

            cout << "Enter origin country: ";
            string origin_country;
            getline(cin, origin_country);

            cout << "Enter destination country: ";
            string dest_country;
            getline(cin, dest_country);

            id ++;

            start_time = std::chrono::high_resolution_clock::now();
            rb_immigrant_data.Insert(id, given_name, family_name, stoi(birth_date), origin_country, dest_country);
            duration = std::chrono::high_resolution_clock::now() - start_time;
            cout << "This took: " << duration.count() / 1000000000.0 << " seconds for the RBtree" << endl;

            start_time = std::chrono::high_resolution_clock::now();
            b_immigrant_data.Insert(id, given_name, family_name, stoi(birth_date), origin_country, dest_country);
            duration = std::chrono::high_resolution_clock::now() - start_time;
            cout << "This took: " << duration.count() / 1000000000.0 << " seconds for the Btree" << endl;

        }
        else if (action == "search"){
            cout << "Search categories: id | first | last | birthday | origin | destination\n";
            string category;
            getline(cin, category);

            cout << "Enter value to search for: ";
            string value;
            getline(cin, value);

            cout << "Select data structure: rbtree | btree" << endl;
            string data_structure;

            getline(cin, data_structure);

            start_time = std::chrono::high_resolution_clock::now();
            vector<Person*> results;
            if (data_structure == "rbtree"){
                results = rb_immigrant_data.Search(category, value);
            }

            else{
                results = b_immigrant_data.Search(category, value);
            }
            duration = std::chrono::high_resolution_clock::now() - start_time;

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
            cout << "Searching by people with the " << category << ' ' << value << " resulted in " << results.size() << " matches and took: " <<  
            duration.count() / 1000000000.0 << " seconds"<< endl <<"On average a "<< data_structure  << " search took: " 
            << duration.count() / (id - 1) / 1000000000.0 << " seconds" << endl;
        }
        else if (action == "delete"){
            cout << "Delete categories: id | first | last | birthday | origin | destination\n";
            string category;
            getline(cin, category);

            cout << "Enter value to delete with: ";
            string value;
            getline(cin, value);

            cout << "Select data structure: rbtree | btree" << endl;
            string data_structure;

            getline(cin, data_structure);

            vector<Person*> results;

            if (data_structure == "rbtree") {
                results = rb_immigrant_data.Search(category, value);
            } 
            else {
                results = b_immigrant_data.Search(category, value);
            }

            

            if (results.empty()) {
                cout << "No matches found.\n\n";
            } 
            else {
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

            auto start_time = std::chrono::high_resolution_clock::now();

            for (auto datapoint: results){
                if (data_structure == "rbtree"){
                    rb_immigrant_data.Delete(datapoint->get_id()); 
                }
                else{
                   b_immigrant_data.Delete(datapoint->get_id()); 
                }
            }

            auto duration = std::chrono::high_resolution_clock::now() - start_time;

            cout << "Deleting by people with the " << category << ' ' << value << " resulted in " << results.size() << " deletions and took: " <<  
            duration.count() / 1000000000.0 << " seconds"<< endl << "On average a "<< data_structure  << " deletion took: " 
            << duration.count() / (id - 1) / 1000000000.0 << " seconds" << endl;

        }
    }

        

    cout << "Goodbye!\n";
    return 0;
}