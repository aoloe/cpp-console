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
 */
void Console::processInput(const std::string &line)
{
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
            // TODO: BOM might not be recogniuzed on non Windows platforms
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
