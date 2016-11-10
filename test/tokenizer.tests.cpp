#include "console.h"
#include <gmock/gmock.h>
#include <string>


using namespace ::testing;
using namespace std;

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

TEST(Tokenizer, tokenize_with_quoted_params) {
  Console c;
  std::vector<std::string> v = c.tokenizeLine("command \"Param1 Param2\" Arg3");
  ASSERT_THAT("command", Eq(v[0]));
  ASSERT_THAT("Param1 Param2", Eq(v[1]));
  ASSERT_THAT("Arg3", Eq(v[2]));
}

int fire_a_registered_command_counter = 0;
auto fire_a_registered_command_func() -> void {
  fire_a_registered_command_counter++;
}
TEST(Console, fire_a_registered_command) {
  Console console;
  console.registerCommand(
      "fire_a_registered_command", // command
      "Test to see a command without args fire", // description
      {}, // argument names
      {}, // argument default values
      (std::function<void(void)>) ([]() {fire_a_registered_command_func();}) // callback
  );
  console.processInput("fire_a_registered_command");
  ASSERT_THAT(1, fire_a_registered_command_counter);
}


int fire_a_registered_command_counter_2 = 0;
auto fire_a_registered_command_func_2() -> void {
  fire_a_registered_command_counter_2++;
}
TEST(Console, fire_a_registered_command_2) {
  Console console;
  console.registerCommand(
      "fire_a_registered_command_2", // command
      "Test to see a command without args fire a second time", // description
      {}, // argument names
      {}, // argument default values
      (std::function<void(void)>) ([]() {fire_a_registered_command_func_2();}) // callback
  );
  console.processInput("fire_a_registered_command_2");
  ASSERT_THAT(1, fire_a_registered_command_counter_2);
}


int fire_a_registered_command_with_argument_counter = 0;
int fire_a_registered_command_with_argument_arg = 0;
auto fire_a_registered_command_with_argument_func(int a) -> void {
  fire_a_registered_command_with_argument_counter++;
  fire_a_registered_command_with_argument_arg = a;
}
TEST(Console, fire_a_registered_command_with_argument) {
  Console console;
  console.registerCommand(
      "fire_a_registered_command_with_argument", // command
      "Test to see a command with args fire", // description
      {"Arg1"}, // argument names
      {"42"}, // argument default values
      (std::function<void(int)>) ([this](int a) {fire_a_registered_command_with_argument_func(a);})// callback
  );
  console.processInput("fire_a_registered_command_with_argument 22");
  ASSERT_THAT(1, fire_a_registered_command_with_argument_counter);
  ASSERT_THAT(22, fire_a_registered_command_with_argument_arg);
}



int fire_a_registered_command_with_argument_default_counter = 0;
int fire_a_registered_command_with_argument_default_arg = 0;
auto fire_a_registered_command_with_argument_default_func(int a) -> void {
  fire_a_registered_command_with_argument_default_counter++;
  fire_a_registered_command_with_argument_default_arg = a;
}
TEST(Console, fire_a_registered_command_with_argument_default) {
  Console console;
  console.registerCommand(
      "fire_a_registered_command_with_argument_default", // command
      "Test to see a command with args and default value fire", // description
      {"Arg1"}, // argument names
      {"42"}, // argument default values
      (std::function<void(int)>) ([this](int a) {fire_a_registered_command_with_argument_default_func(a);}) // callback
  );
  console.processInput("fire_a_registered_command_with_argument_default");
  ASSERT_THAT(1, fire_a_registered_command_with_argument_default_counter);
  ASSERT_THAT(42, fire_a_registered_command_with_argument_default_arg);
}
