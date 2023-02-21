// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(make_trump) {
  Suit trump;
  Player * jimmy = Player_factory("Jimmy", "Simple");
  jimmy->add_card(Card(NINE, CLUBS));
  jimmy->add_card(Card(TEN, SPADES));
  jimmy->add_card(Card(QUEEN, DIAMONDS));
  jimmy->add_card(Card(KING, SPADES));
  jimmy->add_card(Card(ACE, SPADES));
  Card upcardJ(NINE, SPADES);
  bool orderupJ = jimmy -> make_trump(upcardJ,true,1,trump);
  ASSERT_TRUE(orderupJ);
  ASSERT_EQUAL(trump, SPADES);
  delete jimmy;
}
TEST(make_trump1) {
    Suit trump;
  Player * jimmy = Player_factory("Jimmy", "Simple");
  jimmy->add_card(Card(NINE, CLUBS));
  jimmy->add_card(Card(TEN, SPADES));
  jimmy->add_card(Card(QUEEN, DIAMONDS));
  jimmy->add_card(Card(KING, SPADES));
  jimmy->add_card(Card(ACE, SPADES));
  Card upcardJ2(NINE, DIAMONDS);
  bool orderupJ2 = jimmy -> make_trump(upcardJ2,true,1,trump);
  ASSERT_FALSE(orderupJ2);
  delete jimmy;
  }
 //left bower and face card led suit is present
 TEST(make_trump2) {
    Suit trump;
  Player * jimmy = Player_factory("Jimmy", "Simple");
  jimmy->add_card(Card(TEN, SPADES));
  jimmy->add_card(Card(QUEEN, DIAMONDS));
  jimmy->add_card(Card(KING, SPADES));
  jimmy->add_card(Card(ACE, SPADES));
  jimmy->add_card(Card(JACK, HEARTS));
    Card upcardJ2(NINE, DIAMONDS);
 bool orderupJ3 = jimmy -> make_trump(upcardJ2,true,1,trump);
 ASSERT_TRUE(orderupJ3);
  ASSERT_EQUAL(trump, DIAMONDS);
 delete jimmy;
}

TEST(TRUMP_BO) {
      Suit trump;
        Card upcardJ2(NINE, DIAMONDS);
   Player * bo = Player_factory("bo", "Simple");
   bo->add_card(Card(TEN, HEARTS));
  bo->add_card(Card(TEN, SPADES));
  bo->add_card(Card(QUEEN, DIAMONDS));
  bo->add_card(Card(KING, CLUBS));
  bo->add_card(Card(ACE, SPADES));
  //upcardJ2 is Nine of Diamonds
   bool orderupB = bo -> make_trump(upcardJ2,true,1,trump);
   //only have 1 potential trump suit but 0 higher than face
   ASSERT_FALSE(orderupB);
   Card upCardB1(NINE, SPADES);
   // only have one face or higher potential trump suit
    bool orderupB1 = bo -> make_trump(upCardB1,true,1,trump);
    ASSERT_FALSE(orderupB1);
    //round 2
   bool orderupR = bo -> make_trump(upcardJ2,false,2,trump);
   ASSERT_FALSE(orderupR);
   bool orderupB2 = bo -> make_trump(upCardB1,false,2,trump);
   ASSERT_TRUE(orderupB2);
   bool orderupB3 = bo -> make_trump(upcardJ2,true,2,trump);
   ASSERT_TRUE(orderupB3);
    Card upcardB(NINE, HEARTS);
   bool simP = bo -> make_trump(upcardB,true,2,trump);
   ASSERT_TRUE(simP);
   ASSERT_EQUAL(trump, DIAMONDS);
   bool simpleP = bo -> make_trump(upcardB,false,2,trump);
    ASSERT_TRUE(simpleP);
    Card upcardB3(NINE, DIAMONDS);
    bool simpleP2 = bo -> make_trump(upcardB3,false,2,trump);
    ASSERT_FALSE(simpleP2);
    delete bo;
}
TEST(TRUMP_BEN) {
        Suit trump;
//with left bower
   Player * ben  = Player_factory("ben", "Simple");
   ben->add_card(Card(JACK, HEARTS));
  ben->add_card(Card(TEN, SPADES));
  ben->add_card(Card(QUEEN, DIAMONDS));
  ben->add_card(Card(KING, CLUBS));
  ben->add_card(Card(ACE, SPADES));
  Card benCard(NINE, DIAMONDS);
   bool benTest = ben -> make_trump(benCard,false,1,trump);
   ASSERT_TRUE(benTest);
   ASSERT_EQUAL(trump, DIAMONDS);
   delete ben;
}
// Add more tests here
TEST(ADD_DISCARD) {
    Player * ben  = Player_factory("ben", "Simple");
   ben->add_card(Card(JACK, HEARTS));
  ben->add_card(Card(TEN, DIAMONDS));
  ben->add_card(Card(JACK, CLUBS)); //expected to be swapped
  ben->add_card(Card(KING, CLUBS));
  ben->add_card(Card(NINE, DIAMONDS));
  Card upcard1(NINE, DIAMONDS);
   Card upcard(NINE, CLUBS);
  Suit orderup;
  bool benboolBefore = ben->make_trump(upcard,false,1,orderup);
  ASSERT_TRUE(benboolBefore);

  ben->add_and_discard(upcard1);
  bool benbool = ben->make_trump(upcard,false,1,orderup);
  ASSERT_FALSE(benbool);
  delete ben;

//upcard should get discarded
  Card inputN(JACK, HEARTS);
    Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(ACE, HEARTS));
  nina->add_card(Card(TEN, CLUBS)); // swapped to become Jack of Hearts
  nina->add_card(Card(JACK, DIAMONDS)); 
  nina->add_card(Card(KING, CLUBS));
  nina->add_card(Card(ACE, CLUBS));
  Suit orderupN;
  Card upcardNB(NINE,DIAMONDS);
  bool ninaboolBefore = nina->make_trump(upcardNB,false,1,orderupN);
  ASSERT_FALSE(ninaboolBefore);
  nina->add_and_discard(inputN);
  bool ninaboolAfter = nina->make_trump(upcardNB,false,1,orderupN);
  ASSERT_TRUE(ninaboolAfter);
  delete nina;
}

TEST(LEAD_CARD1) {
    Suit trump = HEARTS;
    Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(ACE, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 
  Card lead = nina->lead_card(trump);
  ASSERT_EQUAL(lead.get_rank(), JACK);
  ASSERT_EQUAL(lead.get_suit(), DIAMONDS);
  delete nina;
}
TEST(LEAD_CARD2) {
   Suit trump = HEARTS;
  Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(ACE, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 
  nina->add_card(Card(TEN, CLUBS));
 Card lead2 = nina->lead_card(trump);
ASSERT_EQUAL(lead2.get_rank(), TEN);
ASSERT_EQUAL(lead2.get_suit(), CLUBS);
delete nina;
}
TEST(LEAD_CARD3) {
    Suit trump = HEARTS;
  Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(ACE, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 
  nina->add_card(Card(TEN, CLUBS));
  nina->add_card(Card(KING, CLUBS));
Card lead3 = nina->lead_card(trump);
ASSERT_EQUAL(lead3.get_rank(), KING);
ASSERT_EQUAL(lead3.get_suit(), CLUBS);
delete nina;
}
TEST(LEAD_CARD4) {
   Suit trump = HEARTS;
  Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(ACE, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 
  nina->add_card(Card(TEN, CLUBS));
  nina->add_card(Card(KING, CLUBS));
  nina->add_card(Card(NINE, CLUBS));
Card lead4 = nina->lead_card(trump);
  ASSERT_EQUAL(lead4.get_rank(), KING);
ASSERT_EQUAL(lead4.get_suit(), CLUBS);
delete nina;
}
// check on my piazza post
TEST(PIAZZA) {
   Suit trump = SPADES;
  Card ledCard(TEN, SPADES);
     Player * cat  = Player_factory("cat", "Simple");
 cat->add_card(Card(JACK, CLUBS)); // left bower; suit = spades
  cat->add_card(Card(JACK, DIAMONDS)); 
  Card play = cat->play_card(ledCard,trump);
    ASSERT_EQUAL(play.get_rank(), JACK);
  ASSERT_EQUAL(play.get_suit(), CLUBS);
  delete cat;
 }
 TEST (PIAZZA2) { // special case
    Suit trump = HEARTS;
  Card ledCard(TEN, DIAMONDS);
     Player * cat  = Player_factory("cat", "Simple");
 cat->add_card(Card(ACE, HEARTS));
  cat->add_card(Card(KING, HEARTS)); 
   cat->add_card(Card(QUEEN, HEARTS));
  cat->add_card(Card(JACK, DIAMONDS)); //follows heart suit instead
    cat->add_card(Card(JACK, HEARTS));
  Card play = cat->play_card(ledCard,trump);
    ASSERT_EQUAL(play.get_rank(), QUEEN);
  ASSERT_EQUAL(play.get_suit(), HEARTS);
    delete cat;

 }
 TEST (PIAZZA22) {
    Suit trump = HEARTS;
  Card ledCard(TEN, HEARTS);
     Player * cat  = Player_factory("cat", "Simple");
 cat->add_card(Card(ACE, HEARTS));
  cat->add_card(Card(KING, HEARTS)); 
   cat->add_card(Card(QUEEN, HEARTS));
  cat->add_card(Card(JACK, DIAMONDS));
    cat->add_card(Card(JACK, HEARTS));
  Card play = cat->play_card(ledCard,trump);
    ASSERT_EQUAL(play.get_rank(), JACK);
  ASSERT_EQUAL(play.get_suit(), HEARTS);
    delete cat;

 }
 TEST (PIAZZA3) {
    Suit trump = DIAMONDS;
  Card ledCard(JACK, DIAMONDS);
     Player * cat  = Player_factory("cat", "Simple");
 cat->add_card(Card(JACK, HEARTS)); // left bower; suit = diamonds
  cat->add_card(Card(QUEEN, DIAMONDS)); 
   cat->add_card(Card(TEN, DIAMONDS));
  cat->add_card(Card(ACE, CLUBS));
    cat->add_card(Card(QUEEN, CLUBS));
  Card play = cat->play_card(ledCard,trump);
    ASSERT_EQUAL(play.get_rank(), JACK);
  ASSERT_EQUAL(play.get_suit(), HEARTS);
    delete cat;

 }
 TEST (PIAZZA4) {
    Suit trump = SPADES;
  Card ledCard(JACK, CLUBS); // left bower: suit = spades
     Player * cat  = Player_factory("cat", "Simple");
     //plays lowest card in hand
  cat->add_card(Card(QUEEN, DIAMONDS)); 
   cat->add_card(Card(TEN, CLUBS));
  cat->add_card(Card(NINE, CLUBS));
  Card play = cat->play_card(ledCard,trump);
    ASSERT_EQUAL(play.get_rank(), NINE);
  ASSERT_EQUAL(play.get_suit(), CLUBS);
    delete cat;

 }
TEST(PLAYCARD) {
 Suit trump = SPADES;
 Card ledCard(TEN, SPADES);
   Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(JACK, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 

  Card play = nina->play_card(ledCard,trump);
  ASSERT_EQUAL(play.get_rank(), JACK);
  ASSERT_EQUAL(play.get_suit(), HEARTS);  
 delete nina;
}
TEST(PLAY1CARD) {
   Suit trump = SPADES;
 Card ledCard(TEN, SPADES);
  Player * alice  = Player_factory("alice", "Simple");
  alice->add_card(Card(JACK, HEARTS));
  alice->add_card(Card(JACK, DIAMONDS)); 
  alice->add_card(Card(JACK, CLUBS));
  Card play2 = alice->play_card(ledCard,trump);
  ASSERT_EQUAL(play2.get_rank(), JACK);
  ASSERT_EQUAL(play2.get_suit(), CLUBS); // changed back
delete alice;
}
TEST(PLAY2CARD) {
 Suit trump = SPADES;
 Card ledCard(TEN, SPADES);
  Player * hana  = Player_factory("hana", "Simple");
  hana->add_card(Card(JACK, HEARTS));
  hana->add_card(Card(JACK, DIAMONDS)); 
  hana->add_card(Card(JACK, CLUBS));
  hana->add_card(Card(TEN, SPADES));
  Card play3 = hana->play_card(ledCard,trump);
   ASSERT_EQUAL(play3.get_rank(), JACK); // ten != Jack changed back to orginal
  ASSERT_EQUAL(play3.get_suit(), CLUBS);
  delete hana;
}
TEST(PLAY3CARD) {
 Suit trump = SPADES;
 Card ledCard(TEN, SPADES);
   Player * cat  = Player_factory("cat", "Simple");
   cat->add_card(Card(JACK, HEARTS));
  cat->add_card(Card(JACK, DIAMONDS)); 
  cat->add_card(Card(JACK, CLUBS));
  cat->add_card(Card(TEN, SPADES));
  cat->add_card(Card(JACK, SPADES));
  Card play4 = cat->play_card(ledCard,trump);
  ASSERT_EQUAL(play4.get_rank(), JACK);
  ASSERT_EQUAL(play4.get_suit(), SPADES);
 delete cat;
}
TEST(removePlayCard) {
  // cards get removed
  Suit trump1 = SPADES;
 Card ledCard2(TEN, SPADES);
   Player * nina1  = Player_factory("nina1", "Simple");
   nina1->add_card(Card(JACK, HEARTS));
  nina1->add_card(Card(JACK, DIAMONDS)); 
  Card play10 = nina1->play_card(ledCard2,trump1);
  ASSERT_EQUAL(play10.get_rank(), JACK);
  ASSERT_EQUAL(play10.get_suit(), HEARTS);  

  nina1->add_card(Card(JACK, CLUBS));
   //nina1: Card(JACK, CLUBS);
  //nina1: Card(JACK, DIAMONDS); 
  Card play20 = nina1->play_card(ledCard2,trump1);
  ASSERT_EQUAL(play20.get_rank(), JACK);
 ASSERT_EQUAL(play20.get_suit(), CLUBS); //Diamonds !=Clubs //changed

  nina1->add_card(Card(TEN, SPADES));
 // nina1: Card(TEN, SPADES);
  //nina1: Card(JACK, DIAMONDS); 
  Card play30 = nina1->play_card(ledCard2,trump1);
  ASSERT_EQUAL(play30.get_rank(), TEN);
  ASSERT_EQUAL(play30.get_suit(), SPADES);
  
  nina1->add_card(Card(JACK, SPADES));
  nina1->add_card(Card(TEN, SPADES));
   // nina1: Card(TEN, SPADES);
  // nina1: Card(JACK, DIAMONDS); 
    // nina1: Card(JACK, SPADES);
  Card play40 = nina1->play_card(ledCard2,trump1);
  ASSERT_EQUAL(play40.get_rank(), JACK);
  ASSERT_EQUAL(play40.get_suit(), SPADES);
  delete nina1;
}

TEST(MORE_PLAYCARD) {
   Suit trump = HEARTS;
  Card ledCard(TEN, SPADES);
   Player * nina  = Player_factory("nina", "Simple");
   nina->add_card(Card(TEN, HEARTS));
  nina->add_card(Card(JACK, DIAMONDS)); 

  Card play = nina->play_card(ledCard,trump);
  ASSERT_EQUAL(play.get_rank(), TEN);
  ASSERT_EQUAL(play.get_suit(), HEARTS);  
 delete nina;

  Suit trump1 = HEARTS;
  Card ledCard1(TEN, HEARTS);
   Player * nina1  = Player_factory("nina1", "Simple");
   nina1->add_card(Card(TEN, HEARTS));
  nina1->add_card(Card(JACK, DIAMONDS)); 

  Card play1 = nina1->play_card(ledCard1,trump1);
  ASSERT_EQUAL(play1.get_rank(), JACK);
  ASSERT_EQUAL(play1.get_suit(), DIAMONDS);   //changed
 delete nina1;

Suit trump2 = HEARTS;
  Card ledCard2(JACK, DIAMONDS); //left bower, actual suit is hearts
   Player * cat  = Player_factory("cat", "Simple");
   cat->add_card(Card(NINE, HEARTS)); 
  cat->add_card(Card(ACE, DIAMONDS)); 
  cat->add_card(Card(QUEEN, CLUBS));
  cat->add_card(Card(NINE, SPADES));
  cat->add_card(Card(ACE, HEARTS));
  Card play4 = cat->play_card(ledCard2,trump2);
  ASSERT_EQUAL(play4.get_rank(), ACE);
  ASSERT_EQUAL(play4.get_suit(), HEARTS);
 delete cat;

Suit trump3 = DIAMONDS;
  Card ledCard3(JACK, HEARTS);
   Player * hana  = Player_factory("hana", "Simple");
  hana->add_card(Card(ACE, HEARTS));
  hana->add_card(Card(TEN, HEARTS)); 
  hana->add_card(Card(ACE, DIAMONDS));
  hana->add_card(Card(TEN, SPADES));
  Card play3 = hana->play_card(ledCard3,trump3);
  ASSERT_EQUAL(play3.get_rank(), ACE);
  ASSERT_EQUAL(play3.get_suit(), DIAMONDS);
  delete hana;
}
 TEST(PLAYCARD3) {
Suit trump3 = HEARTS;
  Card ledCard3(JACK, HEARTS);
   Player * hana  = Player_factory("hana", "Simple");
  hana->add_card(Card(ACE, HEARTS));
  hana->add_card(Card(TEN, HEARTS)); 
  hana->add_card(Card(ACE, DIAMONDS));
  hana->add_card(Card(TEN, SPADES));
  Card play3 = hana->play_card(ledCard3,trump3);
  ASSERT_EQUAL(play3.get_rank(), ACE);
  ASSERT_EQUAL(play3.get_suit(), HEARTS);
  delete hana;
 }

 TEST(PLAYCARD4) {
  Suit trump2 = HEARTS;
  Card ledCard2(JACK, DIAMONDS); 
   Player * cat  = Player_factory("cat", "Simple");
   cat->add_card(Card(NINE, CLUBS)); 
  cat->add_card(Card(ACE, DIAMONDS)); 
  cat->add_card(Card(QUEEN, CLUBS));
  cat->add_card(Card(NINE, SPADES));
  cat->add_card(Card(ACE, DIAMONDS));
  Card play4 = cat->play_card(ledCard2,trump2);
  ASSERT_EQUAL(play4.get_rank(), NINE);
  ASSERT_EQUAL(play4.get_suit(), SPADES);
 delete cat;
 }
 
TEST_MAIN()
