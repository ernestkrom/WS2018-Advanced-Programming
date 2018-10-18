//#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Party {
private:
    string name;
    uint num_votes;
    uint seats;

public:
    void setName(string name) { this->name = name; }
    string getName() { return this->name; }
    void setNum_Votes(uint num_votes) { this->num_votes = num_votes; }
    uint getNum_Votes() { return this->num_votes; }
    vector<float> getDivisionVector(uint num_seats)
    {
        vector<float> tmp;
        for (uint i = 1; i <= num_seats; i++) {
            tmp.push_back(float(this->getNum_Votes()) / i);
        }
        return tmp;
    }
    void setSeats(uint seats) { this->seats = seats; }
    uint getSeats() { return this->seats; }
};

int main()
{
    uint num_seats = 0, num_parties = 0;
    vector<Party> parties;

    ifstream infile("inputTxt.txt");
    string line;
    uint position = 0;
    while (getline(infile, line)) {
        switch (position) {
        case 0:
            num_seats = stoi(line);
            break;
        case 1:
            num_parties = stoi(line);
            break;
        default:
            string delimiter = " ";
            string name = line.substr(0, line.find(delimiter));
            uint number = stoi(line.substr(line.find(delimiter), '\n'));

            Party party;
            party.setName(name);
            party.setNum_Votes(number);
            parties.push_back(party);
        }
        position++;
    }

    vector<vector<float>> divisionTable;
    vector<uint> counters;
    for (uint i = 0; i < parties.size(); i++) {
        divisionTable.push_back(parties[i].getDivisionVector(num_seats));
        counters.push_back(0);
    }
    //    for (uint i = 0; i < parties.size(); i++) {
    //        sort(divisionTable[i].begin(), divisionTable[i].end(), greater<uint>());
    //    }

    for (uint j = 0; j < num_seats; j++) {
        float tmp_max = 0;
        uint tmp_mark = 0;

        for (uint i = 0; i < parties.size(); i++) {
            if (divisionTable[i][0] > tmp_max) {
                tmp_max = divisionTable[i][0];
                tmp_mark = i;
            }
        }
        counters[tmp_mark]++;
        divisionTable[tmp_mark].erase(divisionTable[tmp_mark].begin());
    }

    for (uint i = 0; i < parties.size(); i++) {
        parties[i].setSeats(counters[i]);
    }

    for (uint i = 0; i < parties.size(); i++) {
        cout << "Party: " << parties[i].getName() << "\tVotes: " << parties[i].getNum_Votes() << "\tSeats: " << parties[i].getSeats() << endl;
    }

    return 0;
}
