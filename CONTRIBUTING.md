# Contributing

## Framework for efficient collaborative working

### Coding conventions

+ follow the norm
+ Document functions using the Doxygen format
+ when possible, push changes on a branch with a descriptive name and a single purpose.
+ every new source file must have an according test file, which uses the Unity framework to test the relevant functions. If no tests can be written for said function, just put a dummy file.
+ the test file must be in the tests/ directory, and have the same arborescence as the source file. For instance, if the source file is src/parsing/parsing.c, the test file must be in tests/parsing/test_parsing.c.

### merge requests

+ please keep merge requests small and focused on a single purpose.
+ write a descriptive title for your merge request.
+ only merge if you have written tests for your code, and they pass.
