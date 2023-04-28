# ReCode

A compiler for the _Code_ language.

## Progress

- [X] Implement self-hosted minimal _C_ compiler
  - See [bootstrap/c-compiler](https://github.com/tughi/recode/tree/bootstrap/c-compiler) tag
- [ ] Translate compiler to _Code_
  - TODO: Implement closures (functions with context)
  - TODO: Treat string literals as local String instances
  - TODO: Collect copyright headers and put them in the generated file
  - TODO: Declare external functions with Code and C signatures


## How to add new features

Non-breaking changes follow a simple process:
1. Add tests
1. Implement feature to pass all tests
1. Stage compiler via: `./ReCode stage`

Bracking changes require a carefully planned approach:
1. Add or update tests
1. Deprecated old feature via warnings
1. Implement new feature to pass all tests
1. Stage compiler via: `./ReCode stage`
1. Remove depredated feature
1. Stage compiler via: `./ReCode stage`
