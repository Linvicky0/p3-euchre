// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(RightleftBower) {
    Card c(JACK, CLUBS);
    Suit trump1 = SPADES;
    ASSERT_EQUAL(c.is_trump(c.get_suit(trump1)), 1);
    ASSERT_EQUAL(c.is_right_bower(trump1), 0);
    Suit trump2 = CLUBS;
    ASSERT_EQUAL(c.is_right_bower(trump2), 1);

}
TEST(trump) {
    Suit trump1 = SPADES;
    Card c(JACK, CLUBS);
    ASSERT_EQUAL(c.is_trump(trump1), 1);
    Card c2(ACE, SPADES);
    ASSERT_EQUAL(c2.is_trump(trump1), 1);
    Card c3(TEN, HEARTS);
    ASSERT_EQUAL(c3.is_trump(trump1), 0);
}
TEST(faceorAce) {
    Card c(JACK, HEARTS);
    Card b(TEN, SPADES);
    Card d(ACE, HEARTS);
   ASSERT_EQUAL(c.is_face_or_ace(), 1);
    ASSERT_EQUAL(b.is_face_or_ace(), 0);
    ASSERT_EQUAL(d.is_face_or_ace(), 1);
    Card c3(JACK, CLUBS);
    ASSERT_EQUAL(c3.is_face_or_ace(), 1);
    Card c1(TEN, CLUBS);
    ASSERT_EQUAL(c1.is_face_or_ace(), 0);
    Card c2(ACE, CLUBS);
    ASSERT_EQUAL(c2.is_face_or_ace(), 1);
}
TEST(cardless) {
     Card c(JACK, CLUBS); //left bower
    Suit trump1 = SPADES;
    Card c2(ACE, CLUBS);
    ASSERT_EQUAL(Card_less(c, c2, trump1),0);
    Card c3(JACK, SPADES); //right bower
    //c is right bower
    ASSERT_EQUAL(Card_less(c, c3, trump1), 1);
    // second trump suit
    Suit trump2 = HEARTS;
    ASSERT_EQUAL(Card_less(c,c2,trump2), 1);
    ASSERT_EQUAL(Card_less(c,c3,trump2), 0);
}
TEST(suit) {
     Suit s = SPADES;
     ASSERT_EQUAL(Suit_next(s), CLUBS);
     Suit s1 = HEARTS;
    ASSERT_EQUAL(Suit_next(s1), DIAMONDS);
    Suit s2 = CLUBS;
    ASSERT_EQUAL(Suit_next(s2), SPADES);
    Suit s3 = DIAMONDS;
    ASSERT_EQUAL(Suit_next(s3), HEARTS);
}
TEST(Equality) {
    Card c(JACK, CLUBS); 
    Card c2(ACE, CLUBS);
    ASSERT_EQUAL((c != c2), 1);
    ASSERT_EQUAL((c == c2), 0);
    ASSERT_EQUAL((c <= c2), 1);
    Card c3(JACK, HEARTS);
    ASSERT_EQUAL((c != c3), 1);
    ASSERT_EQUAL((c == c3), 0);
    ASSERT_EQUAL((c <= c3), 0);

    Card c4(JACK, HEARTS);
    ASSERT_EQUAL((c3 != c4), 0);
    ASSERT_EQUAL((c3 == c4), 1);
    ASSERT_EQUAL((c3 <= c4), 1);
    ASSERT_EQUAL((c3 >= c4), 1);
}
TEST(greaterLessthan) {
    Card c(JACK, CLUBS); 
    Card c2(ACE, CLUBS);
    ASSERT_EQUAL((c > c2), 0);
    ASSERT_EQUAL((c < c2), 1);
    Card c3(JACK, HEARTS);
    ASSERT_EQUAL((c > c3), 1);
    ASSERT_EQUAL((c < c3), 0);
    Card c4(JACK, HEARTS);
    ASSERT_EQUAL((c3 > c4), 0);
    ASSERT_EQUAL((c3 < c4), 0);
    ASSERT_EQUAL((c3 <= c4), 1);
    ASSERT_EQUAL((c3 >= c4), 1);
}
TEST(ostringstreamTest) {
    Card c(JACK, CLUBS); 
    ostringstream os;
    os << c;
    ostringstream oss2;
    oss2 << "Jack of Clubs";
    ASSERT_EQUAL(os.str(), oss2.str());
}
TEST(istringstreamTest) {
  istringstream is("Three of Spades");
  Card c;
  is >> c;
  ASSERT_EQUAL(c, Card(THREE, SPADES));
}
TEST(SuitNext) {
    Suit s = DIAMONDS;
    ASSERT_EQUAL(Suit_next(s), HEARTS);
     s = HEARTS;
    ASSERT_EQUAL(Suit_next(s), DIAMONDS);
    s = CLUBS;
    ASSERT_EQUAL(Suit_next(s), SPADES);
    s = SPADES;
    ASSERT_EQUAL(Suit_next(s), CLUBS);
}
TEST(cardLessLedCard) {
    Card led(ACE, SPADES);
    Suit trump = HEARTS;
    Card a(TEN, SPADES);
    Card b(TEN, DIAMONDS);
    // card a follows suit and card b doesn't
    ASSERT_EQUAL(Card_less(a,b,led,trump),0);
    Card c(NINE, SPADES);
    ASSERT_EQUAL(Card_less(b,c,led,trump),1);
    Card d(NINE, HEARTS);
    ASSERT_EQUAL(Card_less(d,c,led, trump), 0);
}
// Add more test cases here

TEST_MAIN()
