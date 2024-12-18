#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<queue>
#include <iterator>

using namespace std;

class forwardChain{
public:
    forwardChain();
    map<int,string> fwKnowledgeBase;
    map<string,string> variableList;
    map<int,string> clauseVariable;
    map<int,string> clauseAnswers;
    map<int,string> conclusionAnswers;

    string treatment(string);

    queue<string> fQueue;
};

