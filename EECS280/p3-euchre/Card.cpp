// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  is >> str;
  rank = string_to_rank(str);
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  is >> str;
  suit = string_to_suit(str);
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
 //EFFECTS Initializes Card to the Two of Spades
  Card::Card() {
    rank = TWO;
    suit = SPADES;

  }

  //EFFECTS Initializes Card to specified rank and suit
  Card::Card(Rank rank_in, Suit suit_in) {
        rank = rank_in;
        suit = suit_in;
  }

  //EFFECTS Returns the rank
  Card::Rank get_rank() const {
        return rank;

  }

  //EFFECTS Returns the suit.  Does not consider trump.
  Card::Suit get_suit() const {
        return suit;

  }

  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  Card::Suit get_suit(Suit trump) const {
        ASSERT(false);

  }

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool is_face_or_ace() const {
        return (rank >= 9);

  }

  //EFFECTS Returns true if card is the Jack of the trump suit
  bool is_right_bower(Suit trump) const {
    if (trump == suit) {
      if (rank == JACK) {
        return true;
      }
    }
    return false;
  }

  //EFFECTS Returns true if card is the Jack of the next suit
  bool is_left_bower(Suit trump) const {
    if (rank == Jack) {
      if (trump == DIAMONDS) {
        if (suit == HEARTS ) {
          return true;
        }
      }
    }
  }

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool is_trump(Suit trump) const {
        ASSERT(false);

  }
