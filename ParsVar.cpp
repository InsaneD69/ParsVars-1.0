#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>


using namespace std;

string way_to_file = "Stream_of_data.txt";
vector<string> LogicCommands;
string typeWar = "int";
bool inFunc = 0;

map<string, char> globalVarChar;
map<string, int> globalVarInt;
map<string, short> globalVarShort;
map<string, int> localInts; 
map<string, char> localChars; 
map<string, short> localShorts; 


void ParsVars(ifstream& stream, const string& typeVar) {
    string nameVar, endCommand, word;
    stream >> word;
    auto semicolon = word.rfind(";");
    if (semicolon == -1) {
        nameVar = word;
        stream >> word;
        if (word == ";") { endCommand = ";"; }
        else { throw exception(); }
    }
    else {
        if (word.length() == semicolon + 1) {
            nameVar = word.erase(semicolon);
            if ((nameVar.find(";") != -1) || (nameVar == "")) {
                throw exception();
            }
            endCommand = ";";
        }
        else { throw exception(); };
    };
    if (inFunc = 0) {
        if (typeVar == "int") { globalVarInt.emplace(pair<string,int>(nameVar, 0)); };
        if (typeVar == "char") { globalVarChar.emplace(pair<string,char>(nameVar, ' ')); };
        if (typeVar == "short") { globalVarShort.emplace(pair<string, short>(nameVar, 0)); };
    }
    else {
        if (typeVar == "int") { localInts.emplace(pair<string, int>(nameVar, 0)); };
        if (typeVar == "char") { localChars.emplace(pair<string, char>(nameVar, ' ')); };
        if (typeVar == "short") { localShorts.emplace(pair<string, short>(nameVar, 0)); };
    };

    LogicCommands.push_back(typeVar + " " + nameVar + endCommand);
}


int main() {
    ifstream file;
    file.open(way_to_file)       ;
    ParsVars(file, typeWar);
    for (auto command : LogicCommands) {
        cout <<command;
    }
    file.close();
  
};