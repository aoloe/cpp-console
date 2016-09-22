# Console

Console "engine" sending commands to a running program.

This console is heavily based on the "Game Console" created by Michael König and presented at the [August Meetup](https://www.meetup.com/Zurich-C-Meetup/events/233492659/) of the C++ User Group Zurich.

The [C++ Learning Group at the OpenTechSchool Zurich](https://www.meetup.com/opentechschool-zurich/events/234084415/) is going through the code and:

- while learning about the use variadic templates,
- refactors the code to avoid the dependence on the SFML framework.

## Status

The implementation is in its infancy and only a basic version of `registerCommand` has been already implemented .

## Notes

### `wstring` vs `string`

Michael is using `wstring`s for the keys in the maps.

After having read

http://stackoverflow.com/questions/402283/stdwstring-vs-stdstring

we decided to stick to `string`s for now.
