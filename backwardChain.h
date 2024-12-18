#include<iostream>
#include<stack>
#include<map>
#include<string>
#include<iterator>

using namespace std;

class backwardChain{
public:
    map<int,string> knowledgeBase;
    map<string,string> variableList;
    map<int,string> concList;
    map<int,string> clauseList;
    map<int,string> clauseAnswers;
    map<int,string> conclusionAnswers;

    map<string,string> questions;
    map<int,int> conclusion1;
    map<string,string> conclusion2;

    stack<int> ruleNumber;
    stack<int> clauseNumber;

    backwardChain();
    string identifyPoison();
    void question();

};

