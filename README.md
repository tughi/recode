# ReCode

A compiler for the _Code_ language.

## Bootstrapping

- [X] Implement self-hosted minimal _C_ compiler
  - types: 
    - **bool**
    - **char**
    - **int8_t**, **int16_t**, **int32_t**, **int64_t**
    - **uint8_t**, **uint16_t**, **uint32_t**, **uint64_t**
    - **size_t**
    - **void**
    - **struct**
  - values:
    - **null**
    - **true**, **false**
  - control:
    - **if-else**
    - **while**
    - **break**
    - **return**
  - line comments
  - literals:
    - base 10 integers
    - char
    - string
  - no preprocessor
- [ ] Translate and refactor compiler to _Code_
  - TODO: Change struct syntax
  - TODO: Disallow forward declaration of structs
  - TODO: Change variable declarations syntax
  - TODO: Change funtion syntax
  - TODO: Treat string literals as local String instances
  - TODO: Change cast syntax
  - TODO: Collect copyright headers and put the in the generated file


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
