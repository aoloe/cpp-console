#include "console.h"
#include <iostream>

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
}
