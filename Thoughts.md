## Integers

There is a fixed set of integer types:
- `i8` - 8 bit signed integer
- `u8` - 8 bit unsigned integer
- `i16` - 16 bit signed integer
- `u16` - 16 bit unsigned integer
- `i32` - 32 bit signed integer
- `u32` - 32 bit unsigned integer
- `i64` - 64 bit signed integer
- `u64` - 64 bit unsigned integer
- `isize` - platform dependent signed integer
- `usize` - platform dependent unsigned integer

Integer literals have the `i32` type implicitly. The type can be changed with a type suffix
(e.g. `42i64`).

To improve readability, integer literals can also include underscores (e.g. `1_000_000`).

> NOTE: Unsigned integers are not supported yet.

## Boolean

The `bool` values can be either `true` or `false`.

You cannot cast a `bool` to an integer value.

## Floats

There will be a fixed set of float types:
- `f32` - 32 bit float
- `f64` - 64 bit float

> NOTE: Floats are not supported yet.

## Structs

    define Node = struct {
        name: !String       \ embedded
        parent: Node        \ parent node reference
        children: [Node]    \ checked array of child node references
        type: i32 = 42      \ with default value
    }

    define Extended_Node = struct {
        extends Node(type = 7)  \ type has another default value
        data: alias Data        \ members of Data can be accessed without .data
    }

Newly created structs can be initializated using named arguments, which can replace default values.

    let node = make !Node()         \ Initializes the local !Node variable
    let node = make Node(type = 13) \ Allocates !Node before initialization

Initilization arguments can be declared also on separate lines.

    let node = make Extended_Node(
        parent = null
        type = 6
    )

Structs are reference types... Struct values are passed by default by reference.

To pass a struct by value one need to specify this with the `!` prefix, like this: `!Node`.

## Generic structs

Generic structs have one or more other types as parameters.

    define Box = struct [T] {
        it: alias T
    }

Declared variables of generic structs have different types if the generic type parameters are
different.

> NOTE: The `Box[!Value]` and `Value` types have similar usage.

## Object types

For each defined struct that extends `Object`, the compiler generates an `Object_Type` global
variable, named after the type.

The `Object_Type` structure looks like this:

    define Object_Type = struct {
        _id: u32
        _max_derivate_id: u32
        name: !String
        base_type: Object_Type
    }

The *_id* and *_max_derivate_id* fields are used internally for 'is' operations.

## Pointers

There are no pointers, but one can fake pointers by using the `Box[T]` generic type.

Boxes can be also used to pass value types (like integers) by reference.

## Nullable values

Types prefixed with a `?` become nullable types, and require a `null` check to get to the its value.

Nullable types have a similar in-memory structure with the following struct:

    define Nullable = struct [T] {
        is_null: bool
        value: T
    }

The compiler will complain of missing a null-checks.

    define length = func (self: ?String) -> i32 {
        if (self != null) {
            return self.length  \ the compiler treats self as String at this point
        }
    }

## Arrays

Like structs, arrays are passed by reference.

### Checked Arrays

An `[i8]` array has the following in-memory structure:

    define Int8_Array = struct {
        data: [i8; ?]       \ reference to an unchecked array
        size: isize
    }

For checked arrays, the compiler makes sure that each access has a bounds-check, similar to a null-
check like in the case of nullable types.

### Unchecked Arrays

Unchecked arrays are unsafe. Avoid using them as much as possible.

#### Fixed arrays

Fixed arrays, like `[i8; 42]` are arrays for which the compiler knows their size.

An `[i32; 7]` array has the following in-memory structure:

    define I32_7_Array = struct {
        _0: i32
        _1: i32
        _2: i32
        _3: i32
        _4: i32
        _5: i32
        _6: i32
    }

## Strings

The `String` type has the following structure:

    define String = struct {
        data: [i8; ?]
        data_size: i32
        length: i32
    }

String literals are global values of type `String`.

## Variables

    let text: String = "123"            \ text holds the address to the specified string
    let number: i32 = text.length + 1   \ number holds the result of the provided expression
    let root_node = make Node()         \ root_node holds the address of a Node

The variable names are symbols used by the compiler to know where the value are stored.

## Functions

    define max = func (v1: i32, v2: i32) -> i32 {
        if (v1 > v2) {
            return v1
        }
        return v2
    }

Functions that don't return a value are missing the `-> type` part.

Functions can be called using the Uniform Function Call Syntax (UFCS). In this case, if the
_receiver_ is a struct variable, it is passed by reference.

UFCS is useful to chain function calls.

    file.write("An example of ").write(4).write(" chained calls").end_line()

## Generic functions

    define max = func [T] (v1: T, v2: T) -> T {
        if (v1 > v2) {
            return v1
        }
        return v2
    }

Depending on the generic type parameters and function's body, the compiler might generate multiple
instances of a generic function.

## Macros

Macros look like functions but they are always inlined where _invoked_, and have no return type.

    define for_each = macro (list: List, block: macro (item: Any, index: i32)) {
        let index = 0
        let item = list.first_item
        while (item != null) {
            block(item.data, index)
            index = index + 1
            item = item.next_item
        }
    }

If a macro accepts block-parameters, these blocks are treated as macros and get inlined within the
macros's body.

The last block-parameter can be declared after the macro _invocation_.

    list.for_each() {
        stdout.write(item)
    }
