#include "Project1-A05142549-backwardChain.h"
#include<fstream>
#include<algorithm>
#include<map>

using namespace std;

backwardChain::backwardChain(){
    ifstream inp;
    string line;
    inp.open("bwData/bwKnowledgeBase.txt");

    int i=10;
    while(!inp.eof()){
        getline(inp,line);
        knowledgeBase.insert(pair<int,string>(i,line));
        i=i+10;
    }
    inp.close();

    inp.open("bwData/variableList.txt");
    while(!inp.eof()){
        getline(inp,line);
        variableList.insert(pair<string,string>(line,"NI"));
    }
    inp.close();

    inp.open("bwData/conclusionList.txt");
    i=10;
    while(!inp.eof()){
        getline(inp,line);
        concList.insert(pair<int,string>(i,line));
        i=i+10;
    }
    inp.close();

    inp.open("bwData/clauseVariables.txt");
    i=1;
    while(!inp.eof()){
        getline(inp,line);
        clauseList.insert(pair<int,string>(i,line));
        i++;
    }
    inp.close();

    inp.open("bwData/clauseVariablesAnswers.txt");
    i=1;
    while(!inp.eof()){
        getline(inp,line);
        clauseAnswers.insert(pair<int,string>(i,line));
        i++;
    }
    inp.close();

    inp.open("bwData/conclusionAnswers.txt");
    i=10;
    while(!inp.eof()){
        getline(inp,line);
        conclusionAnswers.insert(pair<int,string>(i,line));
        i=i+10;
    }
    inp.close();

    questions.insert(pair<string,string>("Sick","Are you feeling sick?"));
    questions.insert(pair<string,string>("Vomiting","Do you have vomiting sensation?"));
    questions.insert(pair<string,string>("Diziness","Are you feeling dizzy?"));
    questions.insert(pair<string,string>("Constipation","Do you have constipation?"));
    questions.insert(pair<string,string>("StingingSensation","Do you feel something is stinging you?"));
    questions.insert(pair<string,string>("MoodDisorders","Dose your mood keep changing frequently?"));
    questions.insert(pair<string,string>("Headache","Do you have a head ache?"));
    questions.insert(pair<string,string>("BloodInUrine","Does your unrine contain blood in it?"));
    questions.insert(pair<string,string>("Numbness","Are you feeling numb?"));
    questions.insert(pair<string,string>("MetallicTasteInMouth","Do you taste metal in mouth?"));
    questions.insert(pair<string,string>("Diarrhea","Do you have Diarrhea?"));
    questions.insert(pair<string,string>("MemoryProblems","Are you constantly forgetting things?"));
    questions.insert(pair<string,string>("Nausea","Do you have Nausea?"));
    questions.insert(pair<string,string>("StomachCramps","Do you have stomach cramps?"));
    questions.insert(pair<string,string>("LossOfAppetite","Did you lose your appetite?"));
    questions.insert(pair<string,string>("DifficultyInBreathing","Are you facing difficulty in breathing?"));
    questions.insert(pair<string,string>("Irritability","Are you getting skin irritation?"));
    questions.insert(pair<string,string>("Depression","Are you getting depressed for no reason?"));
    questions.insert(pair<string,string>("HighBloodPressure","Is your blood pressure high?"));
}
string backwardChain::identifyPoison(){
    int i = 10;
    string answer = "";
    while(i<=310){
        if("Poisoning"==concList.at(i)){
            ruleNumber.push(i);
            clauseNumber.push((((i/10)-1)*12)+1);
            question();
            if(conclusion2.find("Poisoning") != conclusion2.end()){
                answer = conclusion2["Poisoning"];
                if(answer == "NO"){
                    cout << endl;
                    cout << "Symptoms does not indicate any poisoning" << endl;
                    cout << endl;
                }
                else
                    return answer;
                break;
            }

        }
        i = i+10;
    }
    if(answer == ""){
        cout << "-----------------------------------------" << endl;
        cout << "Sorry not sure about poisoning" << endl;
        cout << "-----------------------------------------" << endl;
    }
    return answer;
}

void backwardChain::question(){
    string response;
    int finalAnswer=1;
    while(!ruleNumber.empty()){
        finalAnswer=1;
        int clauseNum = clauseNumber.top();
        int ruleNum = ruleNumber.top();
        for(int i=clauseNum;i<=clauseNum+11;i++){
            if(clauseList.at(i)!="n"){
                string clauseVariable = clauseList.at(i);
                if(variableList.find(clauseList.at(i))!= variableList.end()){
                    if(variableList[clauseList.at(i)]=="NI"){
                        cout<<questions[clauseList.at(i)]<<"(YES/NO): "<<endl;
                        cin >> response;
                        transform(response.begin(),response.end(),response.begin(), ::toupper);
                        if(response=="YES" || response=="NO")
                            variableList[clauseList.at(i)] = response;
                        else{
                            cout << "Wrong input: " << endl;
                            cout << "Please enter only YES or NO" << endl;
                            cout <<questions[clauseList.at(i)]<<"(YES/NO): "<<endl;
                            cin >> response;
                            transform(response.begin(),response.end(), response.begin(), ::toupper);
                            variableList[clauseList.at(i)] = response;
                        }
                    }
                    if(variableList[clauseList.at(i)]==clauseAnswers[i]){
                        finalAnswer = 1;
                        continue;
                    }
                    else{
                        finalAnswer = 0;
                        conclusion1.insert(pair<int,int>(ruleNumber.top(),finalAnswer));
                        string foundConclusion = concList[ruleNumber.top()];
                        if(foundConclusion != "Poisoning"){
                            conclusion2.insert(pair<string,string>(foundConclusion,"NO"));
                        }
                        ruleNumber.pop();
                        clauseNumber.pop();
                        break;
                    }
                }
                else{
                    if(conclusion1.find(ruleNum) != conclusion1.end()){
                        clauseNumber.pop();
                        ruleNumber.pop();
                        continue;
                    }
                   if((conclusion2.find(clauseVariable) != conclusion2.end()) && conclusion2.at(clauseVariable)== "YES"){
                        continue;
                    }
                    else{
                        if((conclusion2.find(clauseVariable) != conclusion2.end()) && conclusion2.at(clauseVariable) == "NO"){
                            clauseNumber.pop();
                            ruleNumber.pop();
                            string foundConclusion = concList[ruleNum];
                            if(foundConclusion != "Poisoning")
                                conclusion2.insert(pair<string,string>(foundConclusion,"NO"));
                            break;
                        }
                        for(auto itr = concList.begin(); itr!= concList.end(); itr++){
                            if((clauseVariable == itr->second) && itr->second != "Poisoning"){
                                int clauseNo = (((itr->first/10)-1)*12)+1;
                                ruleNumber.push(itr->first);
                                clauseNumber.push(clauseNo);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else{
                if(i-clauseNum == 11){
                    string conclusion = concList.at(ruleNumber.top());
                    if(conclusion == "Poisoning")
                        conclusion2.insert(pair<string,string>(conclusion,conclusionAnswers.at(ruleNumber.top())));
                    else
                        conclusion2.insert(pair<string,string>(conclusion,"YES"));
                    clauseNumber.pop();
                    ruleNumber.pop();
                }
                continue;
            }
            int finishedClause = clauseNumber.top();
            clauseNumber.pop();
            finishedClause++;
            clauseNumber.push(finishedClause);
        }
    }
}

