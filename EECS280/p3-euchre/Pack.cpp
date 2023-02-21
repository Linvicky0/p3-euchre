// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Pack.h"
#include "Card.h"
//./Pack_tests.exe > output.txt
//touch creates files
using namespace std;


Pack::Pack() {
  int index = 0;
  next = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
      for(int r = NINE; r <= ACE; ++r) {
        Card c(static_cast<Rank>(r), static_cast<Suit>(s));
        cards[index] = c;
        index++;
}
    }
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input) {
    string junk, rank, suit;
    next = 0;
     int index = 0;
    for (int s = 0; s < PACK_SIZE; ++s) {
        pack_input >> rank >> junk >> suit;
        Card c(string_to_rank(rank),  string_to_suit(suit));
        cards[index] = c;
        index++;
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one() {
    int temp = next;
    next++;
    return cards[temp];

  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset() {
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle()  {
   int secondIndex = 0;
   int firstIndex = 0;
   next = 0;
   //shuffle 7 times
   for (int c = 0; c < 7; c++) {

   Card arr[PACK_SIZE];

   for(int i = 0; i < PACK_SIZE; i++) {
      arr[i] = cards[i];
   } 

    for (int i = 0; i < PACK_SIZE; i++) {
    
       if (i %2 == 0) {
      Card second = arr[secondIndex + (PACK_SIZE/2)];
       cards[i] = second; 
       secondIndex++;
       }
       else {
      Card first = arr[firstIndex];
       cards[i] = first;
      firstIndex++;
       }
    }
    secondIndex = 0;
    firstIndex = 0;
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const {
    if (next >= PACK_SIZE) {
      return true;
    }
    return false;
  }

