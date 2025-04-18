#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <list>
using namespace std;

enum Symbol{
    GLOBAL, LOCALVAR, USERFUNCTION, LIB_FUNCTION, FORMAL
};

class SymbolTableEntry{
    public:
    string name;
    bool active;
    Symbol type;
    unsigned int scope;
    unsigned int line;
    
    vector<SymbolTableEntry*> list_arg;
    
    SymbolTableEntry() {};
    SymbolTableEntry(string name, Symbol type, unsigned int scope, unsigned int line, bool active = 1);
    void insertArg(SymbolTableEntry* arg);
    void hide();
    friend class SymbolTable;
};

class SymbolTable{
    std::map<unsigned int, std::vector<SymbolTableEntry*> > scope_table;
    std::unordered_multimap<std::string, SymbolTableEntry *> hash_table;

    public:
    SymbolTable();
    vector<string> errors;
    bool isLibFunct(string name);
    void insert(string name, Symbol type, unsigned int scope, unsigned int line);
    void insert(SymbolTableEntry* var);

    bool lookUp(SymbolTableEntry* key);
    SymbolTableEntry* lookUp(string name, int scope);
    SymbolTableEntry* lookEverywhere(string key, int currScope);

    void insertLibFunct();
    void hide(int scope);
    void displayHash();
};

#endif
