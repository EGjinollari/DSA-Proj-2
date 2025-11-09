#pragma once

#include <vector>
#include <string>
#include "../person.h"

using namespace std;

class BNode {
private:
    bool leaf;
    int deg;
    vector<string> keys;
    vector<Person*> persons;
    vector<BNode*> children;

public:
    BNode(int deg, bool leaf);
    ~BNode();
    BNode* search(const string& key);
    void insertNonFull(Person* person, const string& key);
    void splitChild(int i, BNode* y);
    bool isLeaf() { return leaf; }
    int getKeyCount() { return keys.size(); }
    string getKey(int index) { return keys[index]; }
    Person* getPerson(int index) { return persons[index]; }
    BNode* getChild(int index) { return children[index]; }
    int getdeg() { return deg; }
    void setKey(int index, const string& key) { keys[index] = key; }
    void setPerson(int index, Person* person) { persons[index] = person; }
    void addKey(const string& key) { keys.push_back(key); }
    void addPerson(Person* person) { persons.push_back(person); }
    void addChild(BNode* child) { children.push_back(child); }
    
    void insertKey(int index, const string& key) { 
        vector<string> new_keys;
        for (int j = 0; j < index; j++) {
            new_keys.push_back(keys[j]);
        }
        new_keys.push_back(key);
        for (int j = index; j < keys.size(); j++) {
            new_keys.push_back(keys[j]);
        }
        keys = new_keys;
    }
    
    void insertPerson(int index, Person* person) { 
        vector<Person*> new_persons;
        for (int j = 0; j < index; j++) {
            new_persons.push_back(persons[j]);
        }
        new_persons.push_back(person);
        for (int j = index; j < persons.size(); j++) {
            new_persons.push_back(persons[j]);
        }
        persons = new_persons;
    }
    
    void insertChild(int index, BNode* child) { 
        vector<BNode*> new_children;
        for (int j = 0; j < index; j++) {
            new_children.push_back(children[j]);
        }
        new_children.push_back(child);
        for (int j = index; j < children.size(); j++) {
            new_children.push_back(children[j]);
        }
        children = new_children;
    }
    
    void removeKey(int index) { 
        vector<string> new_keys;
        for (int j = 0; j < keys.size(); j++) {
            if (j != index) {
                new_keys.push_back(keys[j]);
            }
        }
        keys = new_keys;
    }
    
    void removePerson(int index) { 
        vector<Person*> new_persons;
        for (int j = 0; j < persons.size(); j++) {
            if (j != index) {
                new_persons.push_back(persons[j]);
            }
        }
        persons = new_persons;
    }
    
    void removeChild(int index) { 
        vector<BNode*> new_children;
        for (int j = 0; j < children.size(); j++) {
            if (j != index) {
                new_children.push_back(children[j]);
            }
        }
        children = new_children;
    }
    
    void resizeKeys(int size) { 
        vector<string> new_keys;
        for (int j = 0; j < size && j < keys.size(); j++) {
            new_keys.push_back(keys[j]);
        }
        keys = new_keys;
    }
    
    void resizepersons(int size) { 
        vector<Person*> new_persons;
        for (int j = 0; j < size && j < persons.size(); j++) {
            new_persons.push_back(persons[j]);
        }
        persons = new_persons;
    }
    
    void resizeChildren(int size) { 
        vector<BNode*> new_children;
        for (int j = 0; j < size && j < children.size(); j++) {
            new_children.push_back(children[j]);
        }
        children = new_children;
    }
    
    void clearPersons() { 
        vector<Person*> new_persons;
        persons = new_persons;
    }
    
    void popBackKey() { 
        if (keys.size() > 0) {
            vector<string> new_keys;
            for (int j = 0; j < keys.size() - 1; j++) {
                new_keys.push_back(keys[j]);
            }
            keys = new_keys;
        }
    }
    
    void popBackPerson() { 
        if (persons.size() > 0) {
            vector<Person*> new_persons;
            for (int j = 0; j < persons.size() - 1; j++) {
                new_persons.push_back(persons[j]);
            }
            persons = new_persons;
        }
    }
    
    void popBackChild() { 
        if (children.size() > 0) {
            vector<BNode*> new_children;
            for (int j = 0; j < children.size() - 1; j++) {
                new_children.push_back(children[j]);
            }
            children = new_children;
        }
    }
};