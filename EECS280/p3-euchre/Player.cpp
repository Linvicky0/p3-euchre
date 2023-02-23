// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include "Card.h"
#include <string>
#include <vector>
#include "Player.h"
#include <cassert>
#include <algorithm>
#include <sstream>
using namespace std;


  static const Suit sameColor(const Suit &order_up_suit) {
     if (order_up_suit == DIAMONDS) {
        return HEARTS;
      }
      else if (order_up_suit == CLUBS) {
          return SPADES;
        }
      else if (order_up_suit == HEARTS) {
           return DIAMONDS;
          }
        return CLUBS;
   }

class Simple: public Player {
  private:
  string name;
  vector<Card> hand; 

  public:
  Simple(string name_in):name(name_in) {
    return;
  }
  const std::string & get_name() const override { 
    return name;
   }
  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
   void add_card(const Card &c) override {
      hand.push_back(c);
    }
  
  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
   bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override { 
      //checking to see if 2> ace of face
      if (round == 1) {
      int count = 0;

      for (int i = 0; i < int(hand.size()); i++) {
        if (hand[i].is_trump(upcard.get_suit()) && hand[i].is_face_or_ace()) {
            count++;
          }
      }
      if (count >= 2) {
        order_up_suit = upcard.get_suit();
        return true;
      }
      }
      //round 2
      else {
        int count = 0;
      const Suit &sameColorAsLed = sameColor(upcard.get_suit());

      for (int i = 0; i < int(hand.size()); i++) {
        if ((hand[i].is_trump(sameColorAsLed)) && hand[i].is_face_or_ace()) {
            count++;
          }
      }
      if (count>=1 || is_dealer) {
        order_up_suit = sameColorAsLed;
        return true;
      }
      }
      return false;
       }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
   void add_and_discard(const Card &upcard) override { 
    int minIndex = -1;
    Suit trump = upcard.get_suit();
    Card min(JACK, trump);

       for (int i = 0; i < int(hand.size()); i++) {

          if (hand[i] <= min && !hand[i].is_trump(trump)) {
            min = hand[i];
            minIndex = i;
          }
       }

       if (minIndex != -1) { 
         hand[minIndex] = upcard;
       }
       //when all of the cards in player's hand are trump
       else {
        //test whether all of the cards in player's hand are bowers
        bool allBowers = 1;
        Card lbow;
        int leftIn = -1;
         for (int i = 0; i < int(hand.size()); i++) {
          if (!hand[i].is_left_bower(trump) && 
                      !hand[i].is_right_bower(trump) && hand[i] <= min) {
                min = hand[i];
                allBowers = 0;
                minIndex = i;
              
          }
          //when the card at index i is a bower
          else if (hand[i].is_left_bower(trump)) {
              lbow = hand[i];
              leftIn = i;
             }
         }
          if (!allBowers) {
            hand[minIndex] = upcard;
          }
          if (allBowers && upcard.is_right_bower(trump)) {
            hand[leftIn] = upcard;
         }
       }
   }
       
    

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
   Card lead_card(Suit trump) override {  
    Card max = Card(TWO, SPADES);
    int maxIndex, leftBowIndex = -1;
    Card lbow = Card(THREE, SPADES);
    for (int i = 0; i < int(hand.size()); i++) {
       if (!hand[i].is_trump(trump) && hand[i] > max) {
            max = hand[i];
            maxIndex = i;
       }
    }

    if (max.get_rank() != TWO) {
      Card temp = max;
      hand.erase(hand.begin() + maxIndex);
      return temp;
    }
    else {
      for (int i = 0; i < int(hand.size()); i++) {
        if (hand[i].is_right_bower(trump)) {
          Card temp = hand[i];
           hand.erase(hand.begin() + i);
          return temp;
        }
        else if (hand[i].is_left_bower(trump)) {
          leftBowIndex = i;
          lbow = hand[i];
        }
        else if (hand[i] > max) {
            max = hand[i];
            maxIndex = i;
        }
    }
   }
      if(leftBowIndex != -1) {
        Card temp = lbow;
        hand.erase(hand.begin() + leftBowIndex);
        return temp;
      }
      Card temp = max;
      hand.erase(hand.begin() + maxIndex);
      return temp;
   }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
   Card play_card(const Card &led_card, Suit trump) override {
    Card maxSuit = Card(TWO, SPADES);
    Card min = Card(ACE, DIAMONDS);
    int minIndex = -1;
    int lbowIndex = -1;
    int maxIndex = -1;
    int minTrumpIndex = 0;
    Card mintrumpcard = Card(ACE, DIAMONDS);
     bool rbow = false;
     bool minTrump = false;

  		Suit cardSuit;
     Suit ledSuit = led_card.get_suit();	
     if (led_card.is_left_bower(trump)) {	
       ledSuit = trump;	
     }	
    for (int i = 0; i < int(hand.size()); i++) {	
        cardSuit = hand[i].get_suit();
      if (hand[i].is_left_bower(trump)) {	
          cardSuit = trump;
      }
      if (cardSuit == ledSuit) {
        // when the right bower follows suit	
         if (hand[i].is_right_bower(trump)) {	
          maxIndex = i;	
          rbow = true;	
          break;	
         }	
         // when left bower follows suit	
         else if (hand[i].is_left_bower(trump)) {
          lbowIndex = i;
         }
         else if (hand[i] > maxSuit) {
          maxSuit = hand[i];
          maxIndex = i;
        }
      }
    }
     if (lbowIndex != -1 && !rbow) {
        Card temp = hand[lbowIndex];
        hand.erase(hand.begin() + lbowIndex);
        return temp;
      }
     else if (maxIndex != -1) {
        Card temp = hand[maxIndex];
        hand.erase(hand.begin() + maxIndex);
        return temp;
      }
      //none of the cards follow suit
        for (int i = 0; i < int(hand.size()); i++) {
          if (!hand[i].is_trump(trump) && (hand[i] <= min)) { 
              min = hand[i];
              minIndex = i;
          }
          else if (hand[i].is_trump(trump)) {
             if (hand[i].is_left_bower(trump)) {
                lbowIndex = i;
            }
             else if (hand[i] <= mintrumpcard && !hand[i].is_right_bower(trump)) {
              mintrumpcard = hand[i];
              minTrumpIndex = i;
              minTrump = true;
             }
          }
        }
      
    if (minIndex != -1) {
        Card temp = min;
        hand.erase(hand.begin() + minIndex);
        return temp;
    }
    else if (minTrump) {
       Card temp = hand[minTrumpIndex];
        hand.erase(hand.begin() + minTrumpIndex);
        return temp;
    }
     else if (lbowIndex != -1) {
         Card temp = hand[lbowIndex];
        hand.erase(hand.begin() + lbowIndex);
        return temp;
      }
      //only card left is right bower
        Card temp = hand[0];
        hand.erase(hand.begin());
        return temp;
   }
};

class Human: public Player {
   
  private:
  string name;
  vector<Card> hand; 

  void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i) {
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
  }
}
  public:
  Human(string name_in):name(name_in) {
    return;
  }

    const std::string & get_name() const override {
         return name;
      }

//   //REQUIRES player has less than MAX_HAND_SIZE cards
//   //EFFECTS  adds Card c to Player's hand
   void add_card(const Card &c) override { 
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());  
    }

//   //REQUIRES round is 1 or 2
//   //MODIFIES order_up_suit
//   //EFFECTS If Player wishes to order up a trump suit then return true and
//   //  change order_up_suit to desired suit.  If Player wishes to pass, then do
//   //  not modify order_up_suit and return false.
   bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const override { 
          print_hand();

    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
          string decision;
          cin >> decision;
         if (decision != "pass") {
           order_up_suit = string_to_suit(decision);
           return true;
          }
              return false;
}
                           

//   //REQUIRES Player has at least one card
//   //EFFECTS  Player adds one card to hand and removes one card from hand.
   void add_and_discard(const Card &upcard) override { 
    std::sort(hand.begin(), hand.end());  
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    int num;
    cin >> num;
    if (num == -1) {
      return;
    }
    hand[num] = upcard;
    }

//   //REQUIRES Player has at least one card
//   //EFFECTS  Leads one Card from Player's hand according to their strategy
//   //  "Lead" means to play the first Card in a trick.  The card
//   //  is removed the player's hand.
   Card lead_card(Suit trump) override {
    std::sort(hand.begin(), hand.end());  
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int num;
    cin >> num;
    Card lead = hand[num];

    hand.erase(hand.begin() + num); //removed the temp here
    return lead;
     }

//   //REQUIRES Player has at least one card
//   //EFFECTS  Plays one Card from Player's hand according to their strategy.
//   //  The card is removed from the player's hand.
   Card play_card(const Card &led_card, Suit trump) override { 
   std::sort(hand.begin(), hand.end());  
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
     int num;
    cin >> num;
    Card play = hand[num];
    
     hand.erase(hand.begin() + num); //removed the temp here
    return play;
    }

};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  
  if (strategy == "Simple") {
    return new Simple(name);
    
  }
  else if (strategy == "Human") {
    return new Human(name);
  }
 
  return nullptr;
  }

std::ostream & operator<<(std::ostream &os, const Player &p) {
   os << p.get_name();
   return os;
}