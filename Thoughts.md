## Integers

There is a fixed set of integer types:
- `Int` - platform dependend integer
- `Int8` - 8 bit integer
- `Int16` - 16 bit integer
- `Int32` - 32 bit integer
- `Int64` - 64 bit integer

## Boolean

The `Boolean` values can be either `true` or `false`.

You cannot cast a `Boolean` to an integer value.

## Floats

There is no support for floats yet.

There will be a fixed set of float types:
- `Float32` - 32 bit float
- `Float64` - 64 bit float

## Nothing

The `Nothing` type is used only as return type to state that a function does not return anything.

## Structs

    define Node = struct {
        name: !String       \ embedded
        parent: Node        \ parent node reference
        children: [Node]    \ checked array of child node references
        type: Int = 42      \ with default value
    }

    define Extended_Node = struct {
        extends Node(type = 7)  \ type has another default value
        data: alias Data        \ members of Data can be accessed without .data
    }

Newly created structs can be initializated using named arguments, which can replace default values.

    let node = new Extended_Node(parent = null, type = 6)

Initilization arguments can be declared also on separate lines.

    let node = new Extended_Node(
        parent = null
        type = 6
    )

Structs are reference types... Struct values are passed by default by reference.

To pass a struct by value one need to specify this with the `!` prefix, like this: `!Node`.

## Template structs

Template types have one or more other types as parameters.

    define Box[T] = struct {
        it: alias T
    }

Concrete template types that have different parameters are different types themselves.

> NOTE: The `Box[!Value]` and `Value` types have similar usage.

## Object types

For each defined struct that extends `Object`, the compiler generates an `Object_Type` global
variable, named after the type.

The `Object_Type` structure looks like this:

    define Object_Type = struct {
        id: Int
        name: !String
        base_type: Object_Type
    }

## Pointers

There are no pointers, but one can fake pointers by using the `Box[T]` template type.

Boxes can be also used to pass value types (like integers) by reference.

## Nullable values

Types prefixed with a `?` become nullable types, and require a `null` check to get to the its value.

Nullable types have a similar in-memory structure with the following struct:

    define Nullable[T] = struct {
        is_null: Boolean
        value: T
    }

The compiler will complain of missing a null-checks.

    define length = func (self: ?String) -> Int {
        if (self != null) {
            return self.length  \ the compiler treats self as String at this point
        }
    }

## Arrays

Like structs, arrays are passed by reference.

### Checked Arrays

An `[Int8]` array has the following in-memory structure:

    define Int8_Array = struct {
        size: Int
        data: [Int8; ?]     \ this is a reference to an unchecked array
    }

For checked arrays, the compiler makes sure that each access has a bounds-check, similar to a null-
check like in the case of nullable types.

### Unchecked Arrays

Unchecked arrays are unsafe. Avoid using them as much as possible.

#### Fixed size arrays

Fixed size arrays, like `[Int8; 42]` are arrays for which the compiler knows their size.

The compliter can do some bounds-checks at compile time.

## Strings

The `String` type has the following structure:

    define String = struct {
        data: [Int8; ?]
        data_size: Int
        length: Int
    }

String literals are global values of type `String`.

## Variables

    let text: String = "123"            \ text holds the address to the specified string
    let number: Int = text.length + 1   \ number holds the result of the provided expression
    let root_node = new Node            \ root_node holds the address of a Node

The variable names are symbols used by the compiler to know where the value are stored.

## Functions

    define max = func (v1: Int, v2: Int) -> Int {
        if (v1 > v2) {
            return v1
        }
        return v2
    }

## Templates

Templates look like functions but they are always inlined where _invoked_.

    define for_each = func (list: List, block: (item: Any, index: Int) => Nothing) => Nothing {
        let index = 0
        let item = list.first_item
        while (item != null) {
            block(item.data, index)
            index = index + 1
            item = item.next_item
        }
    }

If a template has accepts block-parameters, these blocks get inlined within the template's body.

The last block-parameter can be inlined after the template _invocation_.

    list.for_each() {
        stdout.write(item)
    }
