 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Console

Bind text commands to actions in your program.

This console is heavily based on the "Game Console" created by Michael König and presented at the [August Meetup](https://www.meetup.com/Zurich-C-Meetup/events/233492659/) of the C++ User Group Zurich.  
It has been heavily reworked by the [C++ Learning Group at the OpenTechSchool Zurich](https://www.meetup.com/opentechschool-zurich/events/234084415/) to only depend on the standard library and to ease the integration in existing programs.

## Features

- Define commands with parameters and attach actions to them.
- Optionally add aliases.
- Trigger the commands.
- Get a list of all available commands.
- Get a help description for each command.

## License

This software is distributed under the MIT License (see the [License](LICENSE.md) and [Authors](AUTHORS.md) files for more details).

## Usage

For now, see the `main.cpp` file for a first demo.

## Documentation

- Commands are case sensitive
- Use double quotes (`"`) to enclose arguments with spaces in them.
- Double quotes and backslash can be escaped with a backspace (`\"`, `\\`).
- If the backspace (`\`) is not followed by a double quote or a backslash, it is inserted literally and so is the following character.
- `help commandName` returns the help string for `commandName`.
- `help commands` returns the list of commands with their descriptions.
- No direct output: print builds a string that is returned on demand

### Reserved words

- `help`: an help command is automatically generated.
- `commands`: if you create a `commands` command you won't be able to get help on it.

## Status

Commands can be registered and triggered.

The engine is almost complete but has not been tested in production yet.

## Notes

- A very similar project: <https://github.com/RippeR37/SLACC>.

## Todo

Next steps:

- move the action on strings (tokenize, argumentConverter, evt. the case insensitive functions) to a separate "Utils" class?
- check that default values work correctly when there are multiple arguments.
- change `getUsage()` to return "(<string> name, [<int> i])" instead of "<string name>, [<int i>]"?
- create a demo program.
  - move `main.cpp` to a `demo/` directory
  - move `the source files to a `src/` directory?
- check if we should bother about BOM
- allow to run a list of commands from a text file? (or is this something the using software should manage?)
- check if the `names` list is really needed (only used in the assert)
- suggest similar commands if no matching found? (or should it be a different library?)
- eventually implement a "tab complete" (or should it be a different library?)
- rename the project as "CommandEngine"?
- tests:
  - add a command that already exists
  - add an alias that already exists (alias, command)
  - add an alias to a command that does not exist
