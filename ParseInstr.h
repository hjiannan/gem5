//
//  ParseInstr.h
//  Dependency
//
//  Created by Jiannan Huang on 12/1/14.
//  Copyright (c) 2014 Jiannan Huang. All rights reserved.
//

#ifndef __Dependency__ParseInstr__
#define __Dependency__ParseInstr__
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Instr {
    Instr(): operation(""), reg1(""), reg2("") {}
    string operation;
    string reg1;
    string reg2;
    string reg3;
    int rep;
};




void inputOne_1(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, waste */
    string waste;
    cin >> instr.reg1;
    cin >> waste;
    instrVec.push_back(instr);
    
}

///////////////////



void inputTwo_1(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, r2 */
    string waste;
    cin >> instr.reg1;
    cin >> instr.reg2;
    instrVec.push_back(instr);
}


void inputTwo_2(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, r2, waste */
    string waste;
    cin >> instr.reg1;
    cin >> instr.reg2;
    cin >> waste;
    instrVec.push_back(instr);
}

void inputTwo_3(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, [r2, waste] */
    string waste;
    cin >> instr.reg1;
    cin >> instr.reg2;
    cin >> waste;
    instr.reg2 = instr.reg2.substr(1, 10);
    instrVec.push_back(instr);
}


void inputTwo_4(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, r2, waste waste */
    string waste;
    cin >> instr.reg1;
    cin >> instr.reg2;
    cin >> waste;
    cin >> waste;
    instrVec.push_back(instr);
}

///////////////////

void inputThree_1(Instr& instr, vector<Instr>& instrVec){ /* e.g. op r1, r2, r3 */
    string waste;
    cin >> instr.reg1;
    cin >> instr.reg2;
    cin >> instr.reg3;
    instrVec.push_back(instr);
}




void parseInstr(vector<Instr>& instrVec){
    Instr instr;
    string waste;
    while (cin >> instr.operation) {
        if (instr.operation.substr(0, 3) == "ldr" || instr.operation.substr(0,3) == "str") {
            /* op r1, [r2, waste] */
            inputTwo_3(instr, instrVec);
            continue;
        }
        else if (instr.operation.substr(0, 3) == "rsb"){
            cin >> instr.reg1 >> instr.reg2;
            string temp;
            cin >> temp;
            if (temp[0] == '#') {
                instrVec.push_back(instr);
                continue;
            }
            instr.reg3 = temp;
            instrVec.push_back(instr);
            continue;
        }
        else if( instr.operation.substr(0, 3) == "tst" || instr.operation.substr(0, 3) == "cmps"){
            cin >> instr.reg1;
            string temp;
            cin >> temp;
            if (temp[0] == '#') {
                instrVec.push_back(instr);
                continue;
            }
            instr.reg2 = temp;
            instrVec.push_back(instr);
            continue;
        }
        else if(instr.operation.substr(0, 3) == "mov" ){
            /* mov type instr */
            if (instr.operation == "mov" ){ /* op r1, r2 */
                inputTwo_1(instr, instrVec);
                continue;
            }
            if (instr.operation == "movt.w") {
                inputTwo_2(instr, instrVec);
                continue;
            }
            if (instr.operation == "movs") {
                cin >> instr.reg1;
                string temp;
                cin >> temp;
                if (temp[0] == '#') {
                    instrVec.push_back(instr);
                    continue;
                }
                instr.reg2 = temp;
                getline(cin, waste);
                if (instr.reg2[instr.reg2.size()-1] == ',') instr.reg2.pop_back();
                instrVec.push_back(instr);
                continue;
            }
            
            if (instr.operation == "mov.w") {
                inputOne_1(instr, instrVec);
                continue;
            }
        }
        else if(instr.operation.substr(0, 3) == "add" || instr.operation.substr(0, 3) == "sub" || instr.operation.substr(0, 3) == "orr"){
            if (instr.operation == "add" || instr.operation.substr(0, 8) == "addi_uop"
                || instr.operation == "sub" || instr.operation.substr(0, 8) == "subi_uop") {
                inputTwo_2(instr, instrVec);
                continue;
            }
            if (instr.operation[3] == 's'){
                cin >> instr.reg1 >> instr.reg2;
                string temp;
                cin >> temp;
                if (temp[0] == '#') {
                    instrVec.push_back(instr);
                    continue;
                }
                instr.reg3 = temp;
                instrVec.push_back(instr);
                continue;
            }
            if (instr.operation.substr(3, 2) == ".w") {
                cin >> instr.reg1 >> instr.reg2;
                string temp;
                cin >> temp;
                if (temp[0] == '#') {
                    instrVec.push_back(instr);
                    continue;
                }
                instr.reg3 = temp;
                getline(cin, waste);
                instrVec.push_back(instr);
                continue;
                
            }
        }
        
    }
    for (auto& inst : instrVec){
     //   cout << inst.reg1[inst.reg1.size()-1] << " " << inst.reg2 << " " << inst.reg3 << endl;
        if (!isalnum(inst.reg1[inst.reg1.size()-1])) {
            inst.reg1.pop_back();
        }

        if (!isalnum(inst.reg2[inst.reg2.size()-1])) {
            inst.reg2.pop_back();
        }

        if (!isalnum(inst.reg3[inst.reg3.size()-1])) {
            inst.reg3.pop_back();
        }
    }
}

#endif /* defined(__Dependency__ParseInstr__) */
