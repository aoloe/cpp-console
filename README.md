# Console

Console "engine" sending commands to a running program.

This console is heavily based on the "Game Console" created by Michael König and presented at the [August Meetup](https://www.meetup.com/Zurich-C-Meetup/events/233492659/) of the C++ User Group Zurich.

The [C++ Learning Group at the OpenTechSchool Zurich](https://www.meetup.com/opentechschool-zurich/events/234084415/) is going through the code and:

- while learning about the use variadic templates,
- refactors the code to avoid the dependence on the SFML framework.

## Status

The implementation is in its infancy and only a basic version of `registerCommand()` and `processInput()` have been already implemented .

## Todo

Next steps:

- Get the "doIt" command to work (implement the body of `command->call` in the `registerCommand()` function template).
- in the Console constructor, register and implement the commands for the list of commands (is `cmdlist` a good command? `dir` inspired by python? or `help ? commands`? or `console ? commands`?) and for `help`.
- implement the arguments recognition in `registerCommand()`.
- add a new command with arguments.
- implement the destructor.
- create a program that can be controlled through the console.
- suggest similar commands if no matching found?
- suggestion: if there is a return value, it can be be displayed on the console. Or: provide an output channel.
