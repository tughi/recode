# ReCode

A compiler for the _Code_ language.

## Bootstrapping

- [X] Implement self-hosted minimal _C_ compiler
  - types: 
    - **bool**
    - **char**
    - **int8_t**, **uint8_t**
    - **int16_t**, **uint16_t**
    - **int32_t**, **uint32_t**
    - **int64_t**, **uint64_t**
    - **size_t**
    - **struct**
    - **void**
  - values:
    - **null**
    - **true**, **false**
  - control:
    - **break**
    - **if-else**
    - **return**
    - **while**
  - line comments
  - literals:
    - base 10 integers
    - char
    - string
  - no preprocessor
- [ ] Translate and refactor compiler to _Code_
  - [ ] integer types
  - [ ] struct types
  - [ ] remove forward delarations
  - [ ] remove ;
  - [ ] explicit variable declarations
  - [ ] funtion definitions
- [ ] Implement compiler in _Code_


## How to add new features

1. Add or update tests
1. Implement feature to pass all tests
1. Stage compiler via: `./ReCode stage`
1. _Optional:_ Refactor compiler to use new feature and stage again
