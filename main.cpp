#include "console.h"
#include <iostream>
#include <string>
#include <vector>

void doIt()
{
    std::cout << "I did it." << std::endl;
}

void sayTheName(std::string name)
{
    std::cout << "The name is: " << name << std::endl;
}

/*
void giveMeTheNumber(int number)
{
    std::cout << "The number is: " << number << std::endl;
}
*/

/*
void serveTheDrinks(int bottles, std::string beverage)
{
    std::cout << "here are " << bottles << " bottles " of " << beverage << std::endl;
}
*/


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

    console.registerCommand(
        "say", // command
        "says the name", // description
        {"name"}, // argument names
        {"arturo"}, // argument default values
        (std::function<void(std::string)>) ([](std::string name) {sayTheName(name);}) // callback
    );

    console.registerAlias("hey", "say"); // TODO: finish the alias implementation
    console.registerAlias("!", "say"); // TODO: finish the alias implementation

    std::cout << console.processInput("doIt");
    std::cout << console.processInput("say arthur");
    std::cout << console.processInput("say");
    std::cout << console.processInput("hey dent");
    std::cout << console.processInput("! dent");
    std::cout << console.processInput("! \"\\\"arthur\\\" dent\"");
    std::cout << "--- help" << std::endl;
    std::cout << console.processInput("help");
    std::cout << "--- help say" << std::endl;
    std::cout << console.processInput("help say");
    std::cout << "--- help commands" << std::endl;
    std::cout << console.processInput("help commands");
    std::cout << "--- listOfCommands()" << std::endl;
    for (const auto command: console.listOfCommands())
          std::cout << command << std::endl;
    std::cout << "--- listOfCommands(sa)" << std::endl;
    for (const auto command: console.listOfCommands("sa"))
          std::cout << command << std::endl;
}
