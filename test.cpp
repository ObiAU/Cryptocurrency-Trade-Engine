#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> tokenise(string csvLine, char separator)
{
    vector<string> tokens;
    

    signed int start, end;
    string token; 

    start = csvLine.find_first_not_of(separator, 0);

    do{
        end = csvLine.find_first_of(separator, start);

        if (start == csvLine.length() || start == end) break;

        if (end >= 0) token = csvLine.substr(start, end - start);

        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    
    }while(end > 0);

    return tokens;
}

int main() {

    // vector<string> tokens;
    // string s = "x,y,z,1,2,3,";
    
    // tokens = tokenise(s, ',');

    // for (string& t : tokens)
    // {
    //     cout << t << endl;
    // }
    
    ifstream csvFile{"20200317.csv"}; // ifstream is a class, csvFile is an object we have created
    string line;
    vector<string> tokens;

    if (csvFile.is_open())
    {
        cout << "File open" << endl;
        
        while(getline(csvFile, line)){
            cout << "Read line " << line << endl;
            tokens = tokenise(line, ',');

            if (tokens.size() != 5){
                cout << "Bad line" << endl;
                continue;
            } 
            try {
            double price = stod(tokens[3]);
            double amount = stod(tokens[4]);
            cout << price << ":" << amount << endl;

            }
            catch(exception& e) {
                cout << "Bad float! " << tokens[3] << endl;
                cout << "Bad float! " << tokens[4] << endl;
                continue;
            }
            //standard python like indexing
            
            

            // for (string& t : tokens)
            // {
            //     cout << t << endl;
            // }
        }

        

        csvFile.close();
    }
    else
    {
        cout << "Could not open file" << endl;
    }

    return 0;
}
