#include "Project1-A05142549-forwardChain.h"
#include<fstream>
using namespace std;

forwardChain::forwardChain(){
    ifstream in;
    string line;

    in.open("fwData/fwKnowledgeBase.txt");
    int i=10;

    while(!in.eof()){
        getline(in,line);
        fwKnowledgeBase.insert(pair<int,string>(i,line));
        i = i+10;
    }
    in.close();

    in.open("fwData/fwVariables.txt");
    while(!in.eof()){
        getline(in,line);
        variableList.insert(pair<string,string>(line,"NI"));
    }
    in.close();

    in.open("fwData/fwClauseVariables.txt");
    i=1;
    while(!in.eof()){
        getline(in,line);
        clauseVariable.insert(pair<int,string>(i,line));
        i++;
    }
    in.close();

    in.open("fwData/clauseAnswers.txt");
    i=1;
    while(!in.eof()){
        getline(in,line);
        clauseAnswers.insert(pair<int,string>(i,line));
        i++;
    }
    in.close();

    in.open("fwData/conclusionAnswers.txt");
    i=10;
    while(!in.eof()){
        getline(in,line);
        conclusionAnswers.insert(pair<int,string>(i,line));
        i = i+10;
    }
    in.close();
}

string forwardChain::treatment(string poison){
    string answer;
    int i = 1;
    int flag = 0;
    variableList["Poisoning"] = poison;
    if(poison!="No Prime Symptoms of Poisoning"){
        fQueue.push("Poisoning");
        int num=1,rule;
        int k;
        while(i<100){
            k = 0;
            for(int j=num;j<num+2;j++){
                if(clauseVariable.at(j)!="p"){
                    rule = ((i/2)+1)*10;
                    if(variableList.at(clauseVariable.at(j)) == "NI"){
                        variableList[clauseVariable.at(j)] == poison;
                    }
                    if(variableList[clauseVariable.at(j)] == clauseAnswers[j]){
                        flag = 1;
                        k++;
                    }
                    else{
                        flag = 0;
                        break;
                    }
                }
            }
            if(flag==1){
                answer = conclusionAnswers[rule];
                fQueue.empty();
                break;
            }
            num = num+2;
            i=i+2;
        }
        return answer;
    }
    else{
        answer = "No Treatment Required at this time";
        return answer;
    }

}


