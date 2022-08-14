#include<iostream>
#include<vector>
#include<sstream>

using namespace std;

void split(vector<string>&tokens, string& str, char ch) {
 
    stringstream stream_1(str);
    string temp;

    while (getline(stream_1, temp, ch)) {
        tokens.push_back(temp);
    }
}


int main(){

    string sentence("I love my India");
    vector<string>tokens;
    split(tokens, sentence, ' ');

    for(string str:tokens){
        cout<<str<<endl;
    }
    return 0;
}