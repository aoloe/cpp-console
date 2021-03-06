#include "console.h"

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <algorithm>

Console::Console()
{
    registerHelpCommand();
}

Console::~Console()
{
    commands.clear();
}

/**
 * @brief Add an alias to the command.
 */
void Console::registerAlias(const std::string &alias, const std::string &command)
{
    assert(commands.find(command) != commands.end());
    assert(commands.find(alias) == commands.end());
    commands[alias] = commands[command];
}

/**
 * @brief process an input line possibly containing commands
 *
 * Tokenize the line and process the tokens.
 *
 * The first token is the command to be run, the other tokens are
 * the arguments.
 *
 * TODO:
 * - create an history of inputs (shouldn't it be on the client side?)
 * - eventually make the commands lowercase / case insensitive
 */
std::string Console::processInput(const std::string &line)
{
    printBuffer.str(std::string()); // clear()
    std::vector<std::string> tokens = tokenizeLine(line);

    if (tokens.size() == 0)
        return "";

    std::string identifier = tokens.at(0);

    tokens.erase(tokens.begin());

    if (commands.find(identifier) != commands.end()) {
        commands[identifier]->call(tokens);
    }
    else {
        // TODO: we probably need a more flexible way to give feedback
        print("Unknown command \"" + identifier + "\".");

    }
    return printBuffer.str();
}

/**
 * @brief Separate a string by spaces into words
 *
 * TODO:
 * - Find if there is a better way to tokenize a string.
 */
std::vector<std::string> Console::tokenizeLine(const std::string &line)
{
    std::vector<std::string> out;
    std::string currWord;
    bool insideQuotes = false;
    bool escapingQuotes = false;
    // TODO: we might want to use getwc() to correctly read unicode characters
    for (const auto& c : line) {
        // ignore control characters
        if (std::iscntrl(c) != 0) {
            // TODO: BOM might not be recognized on non-Windows platforms. We might want to
            // check for it.
            continue;
        }
        else if (c == ' ' && !insideQuotes) {
            // keep spaces inside of quoted text
            if (currWord.empty()) {
                // ignore leading spaces
                continue;
            }
            else {
                // finish off word
                out.push_back(currWord);
                currWord.clear();
            }
        }
        else if (!escapingQuotes && c == '\\') {
            escapingQuotes = true;
        }
        else if (escapingQuotes) {
            if (c != '"' && c != '\\') {
                currWord += '\\';
            }
            currWord += c;
            escapingQuotes = false;
        }
        else if (c == '"') {
            // finish off word or start quoted text
            if (insideQuotes) {
                out.push_back(currWord);
                currWord.clear();
                insideQuotes = false;
            }
            else {
                insideQuotes = true;
            }
        }
        else {
            currWord += c;
        }
    }
    // add the last word
    if (!currWord.empty())
        out.push_back(currWord);
    return out;
}

/**
 * @brief Register the help command.
 */
void Console::registerHelpCommand()
{
    registerCommand(
        "help",
        "Prints information about using the console or a given command.",
        {"term", "argument"},
        {"", ""},
        (std::function<void(std::string, std::string)>) ([this](std::string term, std::string argument) {helpCommand(term, argument);})
    );
}

/**
 * @brief Return the help
 *
 * - return a general help if no term is set
 * - return the list of commands if the term is "commands" (eventually filtered)
 * - return the command usage and description if the term is a valid command.
 *
 * TODO:
 * - if commands will ever be case insensitive, the filter should also be
 */
void Console::helpCommand(std::string term, std::string filter)
{
    if (term.empty()) {
        // TODO by Michael: print version number
        print("Welcome to the console of (this engine).");
        print("  Command syntax:          \"command_name parameter1 parameter2 ...\"");
        print("Type \"help commands [filter]\" to find a command.");
        print("Type \"help command_name\" to display detailed information.");
    }
    else if (term == "commands") {
        for (const auto command: listOfCommands(filter)) {
            print(command);
            if (!commands[command]->description.empty())
                print("    " + commands[command]->description);
        }

    }
    else {
        if (commands.find(term) != commands.end()) {
            print(commands[term]->getUsage());
            if (!commands[term]->description.empty())
                print("    " + commands[term]->description);
        }
        else {
            print("Unknown command or variable \"" + term + "\".");
        }
    }
}

/**
 * @brief Return a vector of command names (eventually filtered)
 *
 * TODO:
 * - if the commands will ever be case insensitive, the filter should also be
 */
std::vector<std::string> Console::listOfCommands(std::string filter)
{
    std::vector<std::string> list{};
    for(auto value: commands) {
        if (filter == "" || value.first.compare(0, filter.length(), filter) == 0) {
            list.push_back(value.first);
        }
    }
    std::sort(list.begin(), list.end());
    return list;
}
