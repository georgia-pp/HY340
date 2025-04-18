/* 
    HY340 Languages and Compilers              Alpha Compiler Syntactical Analysis

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include "SymbolTable.h"
#define stringify( name ) #name
extern  SymbolTable* symbolTable;

string convert_enum[] =
{
    stringify( GLOBAL ),
    stringify( LOCALVAR ),
    stringify( USERFUNCTION ),
    stringify( LIB_FUNCTION ),
    stringify( FORMAL )
};

void SymbolTableEntry::hide() {this->active = 0;}

void SymbolTableEntry::insertArg(SymbolTableEntry* arg) { 
    list_arg.push_back(arg);
}

bool SymbolTable::isLibFunct(string name){
    if(name == "print" || name == "input"
       || name == "objectmemberkeys" || name == "objecttotalmembers"
       || name == "objectcopy" || name == "totalarguments"
       || name == "arguments" || name == "typeof"
       || name == "strtonum" || name == "sqrt" || name == "cos"
       || name == "sin") return true;

    else return false;
} 

SymbolTableEntry::SymbolTableEntry(string name, Symbol type, unsigned int scope, unsigned int line, bool active) {
    this->name = name;
    this->type = type;
    this->scope = scope;
    this->line = line;
    this->active = active;
}

void SymbolTable::insertLibFunct() {
    this->insert("print",LIB_FUNCTION,0,0);
    this->insert("input",LIB_FUNCTION,0,0);
    this->insert("objectmemberkeys",LIB_FUNCTION,0,0);
    this->insert("objecttotalmembers",LIB_FUNCTION,0,0);
    this->insert("objectcopy",LIB_FUNCTION,0,0);
    this->insert("totalarguments",LIB_FUNCTION,0,0);
    this->insert("argument",LIB_FUNCTION,0,0);
    this->insert("typeof",LIB_FUNCTION,0,0);
    this->insert("strtonum",LIB_FUNCTION,0,0);
    this->insert("sqrt",LIB_FUNCTION,0,0);
    this->insert("cos",LIB_FUNCTION,0,0);
    this->insert("sin",LIB_FUNCTION,0,0);
}

SymbolTable::SymbolTable() {
    insertLibFunct();
}

/* ONLY TO INSERT LIBRARY FUNCTIONS */
void SymbolTable::insert(string name, Symbol type, unsigned int scope, unsigned int line){
    SymbolTableEntry *tmp= new SymbolTableEntry();

    tmp->name=name;
    tmp->type=type;
    tmp->scope=scope;
    tmp->line=line;
    tmp->active=true;

    scope_table[scope].push_back(tmp);
    auto tmp1 = hash_table.insert(hash_table.end(), pair<string, SymbolTableEntry *>(name, tmp));
}

void SymbolTable::insert(SymbolTableEntry* var){
    if( lookUp(var) ){
        scope_table[var->scope].push_back(var);
        auto tmp1 = hash_table.insert(hash_table.end(), pair<string, SymbolTableEntry *>(var->name, var));
    }
}

bool SymbolTable::lookUp(SymbolTableEntry* key){
    switch (key->type){
    case GLOBAL:
                if(lookUp(key->name, 0) == NULL)
                    return true;
                else
                    return false;
                break;
    
    case LOCALVAR: 
                if(lookUp(key->name, key->scope) == NULL)
                    return true;
                else 
                    return false;
                break;

    case USERFUNCTION: 
                if (isLibFunct(key->name)) {
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" collision with library function");
                    return false;
                }

                if(lookUp(key->name, key->scope) != NULL){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" already exist as variable/function");
                    return false;
                }
                else
                    return true;
                break;

    case FORMAL: 
                if (isLibFunct(key->name) ){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" formal argument collision with library function");
                    return false;
                }

                if(lookUp(key->name, key->scope) != NULL){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" formal argument already exist");
                    return false;
                }
                else {
                    return true;
                }
                break;

    default:
        break;
    }
    return false;
}

SymbolTableEntry* SymbolTable::lookUp(string name, int scope) {
    vector<SymbolTableEntry*> tmp;
    for(auto n : scope_table){
        if(n.first == scope) {tmp=n.second; break;}
    }
    for(int i=0; i<tmp.size(); i++){
        if(tmp.at(i)->name == name && tmp.at(i)->active) return tmp.at(i);
    }

    return NULL;
}

SymbolTableEntry* SymbolTable::lookEverywhere(string key, int currScope){
    for(int i=currScope; i>=0; i--){
        for(auto tmp : hash_table){
            if(tmp.first == key && tmp.second->scope == i && tmp.second->active)
                return tmp.second;
        }
    }
    return NULL;
}

void SymbolTable::hide(int scope) {
    for(auto n : scope_table){
        if(n.first == scope){
            for(int i=0; i<n.second.size(); i++)
                n.second.at(i)->hide();
        }
    }
}

void SymbolTable::displayHash(){
    cout<<endl;
    cout<<"\033[1;31m"<<"**********************          ERRORS          **********************"<<endl;
    for(int i=0; i<errors.size(); i++) {
        cerr<<errors.at(i)<<endl;
    }
    cout<<endl;

    for( const auto& n : scope_table){
        cout<<"\033[1;35m"<<"**********************\t\tSCOPE "<<n.first<<"\t\t**********************"<<"\033[0m"<<endl;
        for (int i = 0; i < n.second.size(); i++) {
            cout<<"\""<<n.second.at(i)->name 
            << "\"\t\t["<<convert_enum[n.second.at(i)->type] 
            << "]\t\t(line "<<n.second.at(i)->line 
            <<")\t(scope "<< n.first<<")"<<endl;
        }
        cout<<endl;
    }
}