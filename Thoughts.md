## Integers

There is a fixed set of integer types:
- `Int` - platform dependend integer
- `Int8` - 8 bit integer
- `Int16` - 16 bit integer
- `Int32` - 32 bit integer
- `Int64` - 64 bit integer

## Boolean

The `Boolean` type has two possible values, `true` and `false`, but nothing else.

You can cast a `Boolean` to an integer value, but not the other way around. 

## Floats

There is no support for floats yet.
There will be a fixed set of float types:
- `Float32` - 32 bit float
- `Float64` - 64 bit float

## Nothing

The `Nothing` type is used only as return type to state that a function does not return anything.

## Pointers

The `@` prefix declares a pointer type.

A variables of type `@Any` stores the address of an `Any` value, where `Any` can be any type, even
another pointer type.

Pointers can be treated as unchecked arrays of unknown size: `x[n]` is the address of the `n`-th
`x` item.

## Nullable pointers

The `@?` prefix declares a nullable pointer type.

The value of an `@?Any` variable can be access only after a `null` check.

    define length = func (self: @?String) -> Int {
        if (self != null) {
            return self.length
        }
    }

## Checked Arrays

An `[Int8]` array has the following in-memory structure:

    define Int8_Array = struct {
        size: Int
        data: @Int8
    }

For checked arrays, the compiler makes sure that each access is withing bounds. The program will
panick if an out of bounds access is detected.

### Fixed size arrays

Fixed size arrays are arrays for which the compiler knows the size.

`[Any; 42]` can be passed as `[Any]` parameter. The compiler converts the fixed size array to a
checked array automatically.

## Strings

The `String` type has the following structure:

    define String = struct {
        data: @Int8
        data_size: Int
        length: Int
    }

String literals are global values of type `String`.

## Structs

    define Node = struct {
        name: String        \ embedded
        parent: @Node       \ parent node address
        children: [@Node]   \ checked array of child node addresses
        type: Int = 42      \ with default value
    }

    define Extended_Node = struct {
        extends Node(type = 7)  \ type has another default value
        data: @Object           \ checked array of child node addresses
    }

Newly created structs can be initializated using named arguments, which can replace default values.

    node := new Extended_Node(parent = null, type = 6)

Initilization arguments can be declared also on separate lines.

    node := new Extended_Node(
        parent = null
        type = 6
    )

## Object types

For each declared `Object` type, the compiler generates a `Object_Type` global variable, named after
the type.

The `Object_Type` structure looks like this:

    define Object_Type = struct {
        id: Int
        name: String
        base_type: @Object_Type
    }

## Variables

    text: @String = "123"           \ text holds the address to the specified string
    number: Int = text.length + 1   \ number holds the result of the provided expression
    root_node := new Node           \ root_node holds the address of a Node

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

    define for_each = func (list: @List, block: (item: @Any, index: Int) => Nothing) => Nothing {
        index := 0
        item := list.first_item
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
