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

Commands can be registered and triggered.

The engine is not complete and has not been tested in production yet, but it should work.

## Todo

Next steps:

- ask for MIT / BSD licensing.
- move the action on strings (tokenize, argumentConverter, evt. the case insensitive functions) to a separate "Utils" class.
- change `getUsage()` to return "(<string> name, [<int> i])"?
- implement the filter for the list of commands. 
- implement a `listOfCommands()` that returns a vector of strings.
- create a demo program. 
- check if we should bother about BOM
- allow to run a list of commands from a text file?
- check if the `names` list is really needed (only used in the assert)
- suggest similar commands if no matching found?
- eventually implement a "tab complete" (return a list of commands starting with...)
- rename the project as "CommandEngine"?
- tests:
  - add a command that already exists
  - add an alias that already exists (alias, command)
  - add an alias to a command that does not exist
