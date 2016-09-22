#ifndef CONSOLE_H
#define CONSOLE_H

#include <cassert>

#include <functional>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class Console {
public:
    explicit Console();
    ~Console();

    // disallow copying
    Console(Console const &) = delete;
    Console& operator=(const Console &) = delete;

    /**
     * @brief Registers a new command with the given name and callback.
     *
     * The callback's signature determines what arguments the command
     * requires and may only consist of int, float and std::string arguments.
     */
    template <typename... Args>
        void registerCommand(const std::string &name, const std::string &description, const std::vector<std::string> &argumentNames, const std::vector<std::string> &defaultArguments, const std::function<void(Args...)> &callback);

private:
	struct Command {
		const std::string name;
		std::string description;
		const unsigned int numArguments;
		const std::vector<std::string> argumentNames;
		const std::vector<std::string> defaultArguments;
		std::function<void(std::vector<std::string>&)> call;
		std::function<std::string(void)> getUsage;

		explicit Command(const std::string &name, const std::string &description, unsigned int numArguments, const std::vector<std::string> &argumentNames, const std::vector<std::string> &defaultArguments) 
            : name(name)
            , description(description)
            , numArguments(numArguments)
            , argumentNames(argumentNames)
            , defaultArguments(defaultArguments)
        {
        }

		// disallow copying
		Command(Command const &) = delete;
		Command& operator=(const Command &) = delete;
    };

	std::unordered_map<std::string, Command*> commands;
	std::set<std::string> names;
};

/***********************************
 * Template function implementaions
 ***********************************
 */

template <typename... Args>
void Console::registerCommand(const std::string &name, const std::string &description, const std::vector<std::string> &argumentNames, const std::vector<std::string> &defaultArguments, const std::function<void(Args...)> &callback)
{

	assert(argumentNames.size() <= sizeof...(Args));
	assert(defaultArguments.size() <= sizeof...(Args));
	assert(commands.find(name) == commands.end());
	assert(names.find(name) == names.end());

	Command* command = new Command(name, description, sizeof...(Args), argumentNames, defaultArguments);

	command->call = [this, command, callback](std::vector<std::string> &arguments) {
        // TODO: add the arguments binding from the original RegisterCommand()
    };

	commands[name] = command;
	names.insert(name);
}

#endif
