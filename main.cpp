//
//  main.cpp
//  Dependency
//
//  Created by Jiannan Huang on 11/30/14.
//  Copyright (c) 2014 Jiannan Huang. All rights reserved.
//

#include "ParseInstr.h"
#include <unordered_map>


void checkDependency(vector<Instr>& instrVec);

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream arq(getenv("MYARQ"));    cin.rdbuf(arq.rdbuf());
    vector<string> buffer;
    string str;
    while (getline(cin, str)) {
        buffer.push_back(str);
    }
    cout << "Raw input instructions: \n";
    for (auto entry : buffer) {
        cout << entry << endl;
    }
    cout << endl;
    vector<Instr> instrVec;
    
    parseInstr(instrVec, buffer);
    cout << "Instructions after parsing:\n";
    for(unsigned i = 0; i < instrVec.size(); i++){
        instrVec[i].rep = i;
        cout << "#" << instrVec[i].rep << setw(12) << instrVec[i].operation << setw(7) << instrVec[i].reg1 << setw(7) << instrVec[i].reg2 << setw(7) << instrVec[i].reg3 << endl;
    }
    cout << endl;
    
    checkDependency(instrVec);
}


bool isDependent(Instr& instr1, Instr& instr2){
    if (instr1.reg1 != "" && instr1.reg1 == instr2.reg1 ) {
        return true;
    }
    if ( instr1.reg1 != "" && instr1.reg1 == instr2.reg2) {
        return true;
    }
    if (instr1.reg1 != "" && instr1.reg1 == instr2.reg3 ) {
        return true;
    }
    return false;
}


int Find(int id, vector<Instr>& instrVec){
    if (id != instrVec[id].rep) {
        instrVec[id].rep = Find(instrVec[id].rep, instrVec);
    }
    return instrVec[id].rep;
}


void outputResult(unordered_map<int, Instr> independent_instr){
    cout << "The number of independent instructions is " << independent_instr.size() << ". They are:\n";
    for (unsigned i = 0; i < independent_instr.size(); ++i){
        cout << setw(10) << independent_instr[i].operation << setw(7) <<
        independent_instr[i].reg1 << setw(7) << independent_instr[i].reg2
        << setw(7) << independent_instr[i].reg3 << endl;
    }
}

void checkDependency(vector<Instr>& instrVec){

    for (unsigned i = 0; i < instrVec.size(); i++) {
        for(unsigned j = i+1; j < instrVec.size(); j++){
            if(isDependent(instrVec[i], instrVec[j])){
                instrVec[j].rep = i;
            }
        }
    }
    unordered_map<int, Instr> independent_instr;
    for (unsigned i = 0; i < instrVec.size(); i++){
        independent_instr[Find(i, instrVec)] = instrVec[Find(i, instrVec)];
    }
    
    /**  output independent instructons stored in independent_instr
     */
    outputResult(independent_instr);
    
}









