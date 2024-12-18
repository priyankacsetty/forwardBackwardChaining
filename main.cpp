#include <iostream>
#include "Project1-A05142549-backwardChain.h"
#include "Project1-A05142549-forwardChain.h"
using namespace std;

int main()
{
    cout << "********************************************************" << endl;
    cout << "****Expert System for Poison Detection in Human Body****" << endl;
    cout << "********************************************************" << endl;

    int input;
    int flag = 1;
    string poison; //diagnosis
    backwardChain bc;
    forwardChain fc;
    string treat;
    while(flag!=0){
        cout << "Enter an option: 1. Do you need any diagnosis? 2. Stop the program." << endl;
        cin >> input;
        switch(input){
        case 1:
            cout << "Starting the System to determine the poison." << endl;
            cout << "Enter YES or NO for each question." <<endl;
            poison = bc.identifyPoison();
            cout <<"----------------------------------------------------" << endl;
            cout <<"Poisoning is: " << poison << endl;
            cout <<"----------------------------------------------------" << endl;
            treat = fc.treatment(poison);
            if(poison!=""){
                cout <<"----------------------------------------------------" << endl;
                cout <<"Recommend Treatment is: " << treat << endl;
                cout <<"----------------------------------------------------" << endl;
                flag = 0;
            }
            else{
                cout <<"----------------------------------------------------" << endl;
                cout << "No Treatment Required." << endl;
                cout <<"----------------------------------------------------" << endl;
                flag = 0;
            }
            break;
        case 2:
            flag = 0;
            break;
        default:
            cout << "Invalid Choice." << endl;
            flag = 0;
            break;
        }
    }


    return 0;
}

