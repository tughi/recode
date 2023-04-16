# ReCode

A compiler for the _Code_ language.

## Bootstraping

- [ ] Implement self-hosted minimal _C_ compiler
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
- [ ] Switch parser from _C_ syntax to _Code_ syntax
- [ ] Implement compiler in _Code_
