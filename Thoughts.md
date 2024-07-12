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

To improve readability, integer literals can include underscore (e.g. `1_000_000`).

## Boolean

The `bool` values can be either `true` or `false`.

You cannot cast a `bool` to an integer value.

## Floats

There will be a fixed set of float types:
- `f32` - 32 bit float
- `f64` - 64 bit float

> NOTE: Floats are not supported yet.

## Structs

    struct Node {
        name: String        \ embedded
        parent: @Node       \ parent Node reference
        children: [@Node]   \ checked array of Node references
        type: i32 = 42      \ with default value

        \ a method that returns @Node
        func add(self, child: @Node) -> @Self { \ Self is a placeholder for the struct name
            self.children.append(child)
            return self
        }

        \ static method
        func new() -> Node {
            return make Node()
        }
    }

    struct Extended_Node {
        super: Node(type = 7)   \ super must always be the first member
        data: alias Data        \ members of Data can be accessed without .data
    }

Newly created structs can be initializated using named arguments, which can replace default values.

    let node = make Node()              \ initializes a stack Node
    let node = make @Node(type = 13)    \ allocates and initializes a heap Node

Initilization arguments can be declared also on separate lines.

    let node = make @Extended_Node(
        parent = null
        type = 6
    )

Structs are passed by value.

## Generic structs

Generic structs have one or more other types as parameters.

    struct Item[T] {
        next_item: @Self
        data: T

        func append(self, item: @Self) -> @Self {
            self.next_item = item
            return self
        }
    }

## Traits

A trait defines shared methods between different types and allows their invocation in a polymorphic
way, enabling code to operate on objects of different types through a common interface.

    trait Visitable {
        func accept(self, visitor: @Visitor)
    }

    struct Expression {
        func accept(self, visitor: @Visitor)
    }


The compiler generates trait objects that could be modeled like this:

    struct VisitableTrait[T] {
        object: @T
        type: @Type
        accept: func (self: @T, visitor: @Visitor)
    }


## Extension methods

Methods can be declared also outside of a type block.

    func Binary_Expression.accept(self, visitor: @Visitor) {
        visitor.visit(self)
    }

## References

References point to a value and can be created usig the `@` operator:

    let data = make Data()      \ local Data variable
    let data_ref = @data        \ reference to data's value

## Nullable values

Types suffixed with a `?` become nullable types, and require a `null` check to get to the its value.

Nullable types have a similar in-memory structure with the following struct:

    struct Nullable[T] {
        is_null: bool
        value: T
    }

The compiler will complain of missing null-checks.

    func length(self: @String?) -> i32 {
        if self != null {
            return self.length  \ the compiler treats self as @String at this point
        }
    }

## Arrays

Like structs, arrays are passed by reference.

### Checked Arrays

An `[i8]` array has the following in-memory structure:

    struct Int8_Array {
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

    struct I32_7_Array {
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

    struct String {
        data: [u8; ?]
        data_size: i32
        length: i32
    }

String literals are global values of type `String`.

## Variables

    let text: @String = "123"           \ text holds the address to the specified string
    let number: i32 = text.length + 1   \ number holds the result of the provided expression
    let root_node = make @Node()        \ root_node holds the address of a new Node

The variable names are symbols used by the compiler to know where the value are stored.

## Functions

    func max(v1: i32, v2: i32) -> i32 {
        if v1 > v2 {
            return v1
        }
        return v2
    }

Functions that don't return a value are missing the `-> type` part.

Call arguments are separated by `,` or new lines.

    execute(
        command
        first_parameter, second_parameter, third_parameter
    )

## Generic functions

    func max[T](v1: T, v2: T) -> T {
        if v1 > v2 {
            return v1
        }
        return v2
    }

Depending on the generic type parameters and function's body, the compiler might generate multiple
instances of a generic function.

## Macros

Macros look like functions but they are always inlined where _invoked_, and have no return type.

    define for_each = macro (list: @List, block: macro (item: @Any, index: i32)) {
        let index = 0
        let item = list.first_item
        while item != null {
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
