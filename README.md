# Console

Console "engine" sending commands to a running program.

This console is heavily based on the "Game Console" created by Michael König and presented at the [August Meetup](https://www.meetup.com/Zurich-C-Meetup/events/233492659/) of the C++ User Group Zurich.

The [C++ Learning Group at the OpenTechSchool Zurich](https://www.meetup.com/opentechschool-zurich/events/234084415/) is going through the code and:

- while learning about the use variadic templates,
- refactors the code to avoid the dependence on the SFML framework.

## Features

## Documentation

- Commands are case sensitive
- Use double quotes (`"`) to enclose arguments with spaces in them.
- Double quotes can be escaped with a backspace (`\"`).
- If the backspace (`\`) is not followed by a double quote or a backslash, it is inserted literally. Double backslashes are reduced to a single one (`\\`).

### Reserved words

- `help`

You can get a list of commands by typing `help commands`.

## Status

Commands can be registered and triggered.

The engine is not complete and has not been tested in production yet, but it should work.

## Differences

- std::string
- Only commands no variables
- only `help commandName` to get help on commands (no `commandName?`)
- No direct output: print builds a string that is returned on demand
- Commands are case sensitive
- Escaping of quotes inside of quotes not yet implemented (probably with `\"`)
- camelCase
- everything in `.cpp` and `.h` (for now)
- no naked pointers
- reduced the LOCs

## Todo

Next steps:

- ask for MIT / BSD licensing.
- move the action on strings (tokenize, argumentConverter, evt. the case insensitive functions) to a separate "Utils" class.
- change `getUsage()` to return "(<string> name, [<int> i])"?
- create a demo program. 
- check if we should bother about BOM
- allow to run a list of commands from a text file?
- check if the `names` list is really needed (only used in the assert)
- suggest similar commands if no matching found? (or should it be a different tool?)
- eventually implement a "tab complete" (or should it be a different tool?)
- rename the project as "CommandEngine"?
- tests:
  - add a command that already exists
  - add an alias that already exists (alias, command)
  - add an alias to a command that does not exist
- check c++ interpreter goto (root.cern.ch/cint)
