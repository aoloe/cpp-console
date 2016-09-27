#include "console.h"
#include <gmock/gmock.h>

using namespace ::testing;

TEST(Tokenizer, test_testing_framework)
{
    ASSERT_THAT(1, Eq(1));
}

TEST(Tokenizer, tokenize_3_words) {
  Console c;
  std::vector<std::string> v = c.tokenizeLine("One Two Three");
  ASSERT_THAT("One", Eq(v[0]));
  ASSERT_THAT("Two", Eq(v[1]));
  ASSERT_THAT("Three", Eq(v[2]));
}
