# Contribution to project

## Git Workflow

There are several rules that will simplify management of the project. Every contributor must follow them.

1. Master branch contains stable version of the program. Any changes must be done in separate branches and merged to master after review by other contributor.

2. It is advisable to use rebase instead of merge, and squash commits before rebasing. Commits must be squashed to logical parts. For example if commit only fixes typo, it is better be merged with previous commit.

## Code Guidelines

1. Do not use "using namespace" declaration.
2. Class and struct names are done in CamelCase, however functions and variable declarations must be done using underscore notation.
3. Avoid using raw pointers.
4. Prefer enum classes over enums
5. Utilize std as much as possible. Do not reinvent the wheel
6. If not sure, consult with a partner

To be continued...

## How to work with CMake

If you add file or directory, these changes must be reflected in CMakeLists.txt file. If you add new source file, to teach CMake about it, add it to files in add_executable function.