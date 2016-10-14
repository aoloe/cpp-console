# Console

Console "engine" sending commands to a running program.

This console is heavily based on the "Game Console" created by Michael König and presented at the [August Meetup](https://www.meetup.com/Zurich-C-Meetup/events/233492659/) of the C++ User Group Zurich.

The [C++ Learning Group at the OpenTechSchool Zurich](https://www.meetup.com/opentechschool-zurich/events/234084415/) is going through the code and:

- while learning about the use variadic templates,
- refactors the code to avoid the dependence on the SFML framework.

## Features

## Documentation

- Commands are case sensitive

### Reserved words

- `help`
- `commands`

You can get a list of commands by typing `help commands`.

## Status

The implementation is in its infancy and only a basic version of `registerCommand()` and `processInput()` have been already implemented .

## Todo

Next steps:

- change `getUsage()` to return "(<string> name, [<int> i])" 
- implement the filter for the list of commands. 
- create a demo program. 
- implement the destructor.
- implement commandAlias
- suggestion: if there is a return value, it can be be displayed on the console. Or: provide an output channel.

- create a program that can be controlled through the console.
- suggest similar commands if no matching found?
- eventually implement a "tab complete" (return a list of commands starting with...)
- rename the project as "CommandEngine"?
