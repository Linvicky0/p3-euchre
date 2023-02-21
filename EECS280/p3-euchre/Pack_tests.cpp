// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    Card second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}
TEST(nondefault_ctor) {
   ifstream ins("Newpack.in");
   Pack pack(ins);
   Card first = pack.deal_one();
   ASSERT_EQUAL(NINE, first.get_rank());
   ASSERT_EQUAL(CLUBS, first.get_suit());
   Card second = pack.deal_one();
   ASSERT_EQUAL(NINE, second.get_rank());
   ASSERT_EQUAL(SPADES, second.get_suit());
   pack.reset();
     Card reset = pack.deal_one();
   ASSERT_EQUAL(NINE, reset.get_rank());
   ASSERT_EQUAL(CLUBS, reset.get_suit());
}
// Add more tests here

TEST_MAIN()
