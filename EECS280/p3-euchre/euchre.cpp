// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
//remember add and discard and print hand
using namespace std;

   const int MAX_PLAYERS = 4;

class Game {

 private:
  std::vector<Player*> players;
  Pack pack;
  int dealer = 0;
  bool isDealer = false;
  int team1score = 0;
  int team2score = 0;
  int pointsToWin;
  Suit trump;
  int teamtrump;
  int tricksTeam1 = 0;
  int tricksTeam2 = 0;
  int totalScore1 = 0;
  int totalScore2 = 0;
  bool doShuffle = false;
  Card upcard;
  int hand = 0;

  void shuffle(Pack &pack) {
    if (doShuffle) {
     pack.shuffle();
    }
  }
 
  void deal() {
    dealer = dealer % 4;
  cout << "Hand " << dealer << endl;
  cout << players[dealer]->get_name() << " deals" << endl;
    int playerIndex = dealer + 1;
    int num = playerIndex; 
      for (int i = playerIndex; i < playerIndex+ (MAX_PLAYERS*2); i++) { 
      if (i == MAX_PLAYERS + playerIndex) {
        num++;
      }
      if ((num + dealer) % 2 != 0) {
         for (int n = 0; n < 3; n++) {
          players[i % 4]->add_card(pack.deal_one());
         }
      }
         else {
           for (int n = 0; n < 2; n++) {
          players[i % 4]->add_card(pack.deal_one());
         }
         }
         num++;
      }
    }
  
  void make_trump() {
  int round = 1;
   int eldest = (dealer + 1) % MAX_PLAYERS;
   upcard = pack.deal_one();
   cout << upcard << " turned up" << endl;

      for (int i = eldest; i < eldest + (MAX_PLAYERS*2); i++) {
        if (i % MAX_PLAYERS == dealer) {
          isDealer = true;
        }
        if (i > dealer + MAX_PLAYERS) {
            round = 2;
        }
      if (players[i%MAX_PLAYERS]->make_trump(upcard, isDealer, round, trump)) {
          if ((i%MAX_PLAYERS) % 2 == 0) {
            teamtrump = 1;
          }
          else {
            teamtrump = 2;
          }
            cout << players[i % MAX_PLAYERS]->get_name()
                           << " orders up " << trump << "\n\n";
            if (round == 1) {
            players[dealer]->add_and_discard(upcard); // if human it also prints hand
            }
            return;
      }
      
       cout << players[i%MAX_PLAYERS]->get_name() << " passes" << endl;
      }
  }
  void team_trick(const int player) {
    if (player % 2 == 0) {
            tricksTeam1++;
            return;
          }
           tricksTeam2++;
  }
  int left_person(int player) {
    if ((player+1) % MAX_PLAYERS == 0) {
        return 0;
    }
    return player + 1;
  }
  void play_hand() {
    Card max;
    int eldest = (dealer + 1) % MAX_PLAYERS;
      Card lead = players[eldest]->lead_card(trump);

      cout << lead << " led by " << players[eldest]->get_name() << endl;
      int winner = eldest;
      //one round = 1 trick
    for (int i = eldest+1; i < eldest + MAX_PLAYERS; i++) { 
      Card current = players[i%MAX_PLAYERS]->play_card(lead, trump);
      cout << current << " played by " 
                  << players[i%MAX_PLAYERS]->get_name() << endl;
      if (Card_less(lead, current, lead, trump)) {
        max = current;
        current = lead;
        winner = i % MAX_PLAYERS;
      }
    }
    team_trick(winner);

    cout << players[winner]->get_name() << " takes the trick\n\n";
    
       // 4 rounds = 4 tricks
       for (int i = 0; i < 4; ++i) {
          Card lead = players[winner]->lead_card(trump);
         cout << lead << " led by " << players[winner]->get_name() << endl;

       int start = left_person(winner);

        for (int i = start; i < start + MAX_PLAYERS - 1; i++) {

      Card current = players[i%MAX_PLAYERS]->play_card(lead, trump);
      cout << current << " played by " << 
                    players[i%MAX_PLAYERS]->get_name() << endl;

      if (Card_less(lead, current, lead, trump)) {
        max = current;
        current = lead;
        winner = i % MAX_PLAYERS;
      }
        }
            team_trick(winner);

        cout << players[winner]->get_name() << " takes the trick\n\n";
    }
  }
  
  void scoring() {
     if (tricksTeam1 > tricksTeam2) {
      cout << players[0]->get_name() << " and " 
              << players[2]->get_name() << " win the hand" << endl;
      if (teamtrump != 1) {
          team1score+=2;
          cout << "euchred!\n";

      }
      else {
        team1score++;
        if (tricksTeam1 == 5) {
          cout << "march!\n";
        }
      }
      totalScore1 += team1score;
     }
     else {
    cout << players[1]->get_name() << " and " 
              << players[3]->get_name() << " win the hand" << endl;
      if (teamtrump != 2) {
        team2score += 2;
        cout << "euchred!\n";

      }
      else {
        team2score++;
         if (tricksTeam1 == 5) {
          cout << "march!\n";
        }
      }
      totalScore2 += team2score;
      tricksTeam1 = 0;
      tricksTeam2 = 0;
     }
    
    cout << players[0]->get_name() << " and " << players[2]->get_name()
               << " have " << team1score << " points\n";
    cout << players[1]->get_name() << " and " << players[3]->get_name()
               << " have " << team2score << " points\n\n";
  }

  public:
  Game(string name[MAX_PLAYERS], string strategy[MAX_PLAYERS], int points) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
      players.push_back(Player_factory(name[i],strategy[i]));
    }
    pointsToWin = points;
}
  
  void play(ifstream &ins, string shuf) {

       pack = Pack(ins);
   
if (shuf == "shuffle") {
  doShuffle = true;
}
  while (totalScore1 < pointsToWin && totalScore2 < pointsToWin) {
    pack.reset();
      shuffle(pack);

     deal();
     make_trump();
     play_hand();
     scoring();
      hand++;
      dealer++;
  }
   if (team1score > team2score) {
    cout << players[0]->get_name() << " and " 
              << players[2]->get_name() << " win!" << endl;
   }
   else {
    cout << players[1]->get_name() << " and " 
              << players[3]->get_name() << " win!" << endl;
   }
   
  for (size_t i = 0; i < MAX_PLAYERS; ++i) {
  delete players[i];
  }
}
};

int main(int argc, const char * argv[]) {

string pack_filename = argv[1];
ifstream ins(argv[1]);
 if (!ins.is_open()) {
  cout << "Error opening " << pack_filename << endl;
  return 1;
 }
   string shufNoShuf = argv[2];
 
  if (argc != 12 || atoi(argv[3]) < 1 || atoi(argv[3]) > 100 ||
       (shufNoShuf != "noshuffle" && shufNoShuf != "shuffle")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
       }
for (int i = 5; i < argc; ++i) {
  if (i % 2 != 0) {
    string strategies = argv[i];
    if (strategies != "Simple" && strategies != "Human") {
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
    }
  }
}
string name[MAX_PLAYERS];
string strategy[MAX_PLAYERS];
 
 int playerCount = 0;
 int strategyCount = 0;

   for (int i = 4; i < 12; ++i) {
    if (i % 2 == 0) {
     name[playerCount] = (argv[i]);
     playerCount++;
    }
    else {
    strategy[strategyCount] = (argv[i]);
    strategyCount++;

    }
   }

Game game(name, strategy, atoi(argv[3]));
game.play(ins, shufNoShuf);
}