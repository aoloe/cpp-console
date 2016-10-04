#ifndef CONSOLE_H
#define CONSOLE_H

#include <cassert>

#include <functional>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

// TODO: remove this include
#include <iostream>

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


    void processInput(const std::string &line);

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


	template <typename T>
	struct argumentConverter {
		static inline T convert(const std::string &s);
	};

	static inline std::function<void()> bindCallback(std::function<void(          )> callback, const std::vector<std::string> &arguments, int argumentIndex);
	template <typename T, typename... Args>
		static std::function<void()>    bindCallback(std::function<void(T, Args...)> callback, const std::vector<std::string> &arguments, int argumentIndex);


public:
    // TODO: make this private
    static std::vector<std::string> tokenizeLine(const std::string &line);

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
        // TODO: add the arguments checks and set the default arguments
        bool failed = false;
        std::function<void()> boundCallback;
        // bind the command callback recursively while allowing type conversion errors to raise exceptions
        try {
            boundCallback = bindCallback(callback, arguments, 0);
        }
        catch (const std::exception&) {
            failed = true;
        }

        if (!failed) {
            // actually execute the command
            boundCallback();

            return;
        }
    };

    commands[name] = command;
    names.insert(name);
}

/**
 * bindCallback, base case
 */
inline std::function<void()> Console::bindCallback(std::function<void()> callback, const std::vector<std::string> &, int) {
    // TODO: remove the cout
    std::cout << "ain't no arguments (no more)" << std::endl;
	return callback;
}

/**
 * bindCallback, recursion step.
 *
 * Run the "bind" code for each argument.
 */
template <typename T, typename... Args>
std::function<void()> Console::bindCallback(std::function<void(T, Args...)> callback, const std::vector<std::string> &arguments, int argumentIndex)
{
    // TODO: remove the cout
    std::cout << "argument " << argumentIndex << ": " << arguments[argumentIndex] << std::endl;
	T value = argumentConverter<T>::convert(arguments[argumentIndex]);
	std::function<void(Args...)> nextCallback = [callback, value](Args... args) {
		callback(value, args...);
	};
	return bindCallback(nextCallback, arguments, argumentIndex + 1);
}

/**
 * default argument converter: faile if none of the specific converters
 * has been run
 */
template <typename T>
inline T Console::argumentConverter<T>::convert(const std::string &s)
{
	static_assert(sizeof(T) != sizeof(T), "Console commands may only take arguments of type int, float or std::string.");
}

/**
 * convert arguments fron string to int
 */
template <>
inline int Console::argumentConverter<int>::convert(const std::string &s)
{
	return std::stoi(s);
}

/**
 * convert arguments fron string to float
 */
template <>
inline float Console::argumentConverter<float>::convert(const std::string &s)
{
	return std::stof(s);
}

/**
 *  (dummy)convert arguments fron string to string
 */
template <>
inline std::string Console::argumentConverter<std::string>::convert(const std::string &s)
{
	return s;
}


#endif
