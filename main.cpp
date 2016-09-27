#include "console.h"
#include <iostream>
#include <string>
#include <vector>

void doIt()
{
    std::cout << "Don't abuse me" << std::endl;
}

int main()
{
    Console console;
    console.registerCommand(
        "doIt", // command
        "do something", // description
        {}, // argument names
        {}, // argument default values
        (std::function<void(void)>) ([]() {doIt();}) // callback
    );
    for (auto i: Console::tokenizeLine("this is a text"))
          std::cout << i << std::endl;
    // console.processInput("doIt ?");
    console.processInput("doIt");
}
