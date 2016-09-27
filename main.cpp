#include "console.h"
#include <iostream>
#include <string>
#include <vector>

void help()
{
    std::cout << "Don't abuse me" << std::endl;
}

int main()
{
    Console console;
    console.registerCommand(
        "help", // command
        "show usage", // description
        {}, // argument names
        {}, // argument default values
        (std::function<void(void)>) ([]() {help();}) // callback
    );
    for (auto i: Console::tokenizeLine("this is a text"))
          std::cout << i << std::endl;
}
