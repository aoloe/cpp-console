#include "console.h"

#include <iostream>
#include <string>

Console::Console()
{
}

Console::~Console()
{
}


/**
 * @brief process an input line possibly containing commands
 *
 * Tokenize the line and process the tokens.
 *
 * The first token is the command to be run, the other tokens are
 * the arguments.
 *
 * If the second token is a question mark, output the command's
 * description.
 *
 * TODO:
 * - create an history of inputs
 * - eventually make the commands lowercase / case insensitive
 */
void Console::processInput(const std::string &line)
{
   std::vector<std::string> tokens = tokenizeLine(line);

   if (tokens.size() == 0)
       return;

	std::string identifier = tokens.at(0);

    if (tokens.size() > 1 && tokens.at(1) == "?") {
		commands["help"]->call(tokens);
        return;
    }

	tokens.erase(tokens.begin());

	if (commands.find(identifier) != commands.end()) {
		commands[identifier]->call(tokens);
	}
	else {
        // TODO: we might want a more flexible way to give feedback
		std::cout << "Unknown command \"" + identifier + "\"." << std::endl;
    }
}

/**
 * @brief Separate a string by spaces into words
 *
 * Remove:
 * - keep spaces inside of "quoted" text
 *
 * Eventually
 * - unescape "" escaped quotes (or backslash escaping?)
 *
 * TODO:
 * - Find if there is a better way to tokenize a string.
 */
std::vector<std::string> Console::tokenizeLine(const std::string &line)
{
	std::vector<std::string> out;
	std::string currWord;
	bool insideQuotes = false;
    // TODO: and with auto?
    // TODO: we might want to use getwc() to correctly read unicode characters
    for (const unsigned char& c : line) {
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
