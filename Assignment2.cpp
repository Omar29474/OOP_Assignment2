#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Player {
private:
    string name;
    int yearOfBirth;
    int height;
    int internationalGoals;
    string nationality;

public:
    Player(){}
    Player(string playerName, int birthYear, int playerHeight, int goals, string playerNationality) {
        name = playerName;
        yearOfBirth = birthYear;
        height = playerHeight;
        internationalGoals = goals;
        nationality = playerNationality;
    }
    void setName(string playerName) {
        name = playerName;
    }

    void setYearOfBirth(int birthYear) {
        yearOfBirth = birthYear;
    }

    void setHeight(int playerHeight) {
        height = playerHeight;
    }

    void setInternationalGoals(int goals) {
        internationalGoals = goals;
    }

    void setNationality(string playerNationality) {
        nationality = playerNationality;
    }
    string getName() const {
        return name;
    }

    int getYearOfBirth() const {
        return yearOfBirth;
    }

    int getHeight() const {
        return height;
    }

    int getInternationalGoals() const {
        return internationalGoals;
    }

    string getNationality() const {
        return nationality;
    }
};
class NationalTeam {
private:
    string country;
    Player players[18];
    bool active[18];
    int numOfPlayers;
 public:
     NationalTeam() {}
     NationalTeam (string Playercountry , int Numbers) {
     country = Playercountry;
     numOfPlayers = Numbers;
     }
     bool addPlayer(const Player& newPlayer) {
        for (int i = 0; i < 18; ++i) {
            if (!active[i]) {
                players[i] = newPlayer;
                active[i] = true;
                numOfPlayers++;
                return true;
            }
        }
        return false;
    }
    bool removePlayer(string playerName) {
        for (int i = 0; i < 18; ++i) {
            if (active[i] && players[i].getName() == playerName) {
                active[i] = false;
                numOfPlayers--;
                return true;
            }
        }
        return false;
    }
    int getNumOfPlayers() const {
        return numOfPlayers;
        }
    Player OldestPlayer() const {
        Player oldest = players[0];
        for (int i = 1; i < 18; ++i) {
            if (active[i] && players[i].getYearOfBirth() < oldest.getYearOfBirth()) {
                oldest = players[i];
            }
        }
        return oldest;
    }
    Player YoungestPlayer() const {
        Player youngest = players[0];
        for (int i = 1; i < 18; ++i) {
            if (active[i] && players[i].getYearOfBirth() > youngest.getYearOfBirth()) {
                youngest = players[i];
            }
        }
        return youngest;
    }
    Player highestIntGoals() const {
        Player highest = players[0];
        for (int i = 1; i < 18; ++i) {
            if (active[i] && players[i].getInternationalGoals() > highest.getInternationalGoals()) {
                highest = players[i];
            }
        }
        return highest;
    }
    friend ostream& operator<<(ostream& os, const NationalTeam& team) {
        os << "Team Country: " << team.country << endl;
        os << "Players: " << endl;
        for (int i = 0; i < team.18; ++i) {
            if (team.active[i]) {
                os << "  " << team.players[i].getName() << endl;
            }
        }
        return os;
    }
    void writeStatistics(ofstream& ofs) const {
        ofs << "Team Country: " << country << endl;
        ofs << "Number of players: " << numOfPlayers << endl;
        Player oldest = OldestPlayer();
        ofs << "Oldest Player: " << oldest.getName() << ", Age: " << (2024 - oldest.getYearOfBirth()) << endl;

        Player youngest = YoungestPlayer();
        ofs << "Youngest Player: " << youngest.getName() << ", Age: " << (2024 - youngest.getYearOfBirth()) << endl;
        Player highestGoals = highestIntGoals();
        ofs << "Player with the highest international goals: " << highestGoals.getName() << ", Goals: " << highestGoals.getInternationalGoals() << endl;
    }
};
    void readPlayersFromFile(ifstream& ifs, Player players [18]& players, int& numPlayers) {
    ifs >> numPlayers;
    for (int i = 0; i < numPlayers; ++i) {
        string playerName, nationality;
        int yearOfBirth, height, goals;
        ifs >> playerName >> yearOfBirth >> height >> goals >> nationality;
        players[i] = Player(playerName, yearOfBirth, height, goals, nationality);
    }
}
int main()
{
  int numplayers;
  ifstream inFile("players.txt",ios::in);
  if (inFile.fail())
    cout<< "could not open file"<<endl;
  else
  {
      ofstream outFile("team statistics.txt",ios::out);
       for (int i=0 ; i<18 ; i++)
  {
      inFile >> numplayers;
      outFile << numplayers<<endl;
  }
  outFile.close();
  }
  inFile.close();
  Player allPlayers [18];
  readPlayersFromFile(inFile, allPlayers, numPlayers);
  NationalTeam team("Egypt");
    for (int i = 0; i < numPlayers; ++i) {
        team.addPlayer(allPlayers[i]);
    }
  cout << "Number of players: " << team.getNumOfPlayers() << endl;
  Player oldest = team.OldestPlayer();
  cout << "Oldest Player: " << oldest.getName() << ", Age: " << (2024 - oldest.getYearOfBirth()) << endl;
  Player youngest = team.YoungestPlayer();
  cout << "Youngest Player: " << youngest.getName() << ", Age: " << (2024 - youngest.getYearOfBirth()) << endl;
  Player highestGoals = team.highestIntGoals();
  cout << "Player with the highest international goals: " << highestGoals.getName() << ", Goals: " << highestGoals.getInternationalGoals() << endl;
  cout << team;
  team.writeStatistics(outputFile);

}
