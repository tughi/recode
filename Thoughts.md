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

> **NOTE**: Floats are not supported yet.

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
    let node = make @Node(type: 13)     \ allocates and initializes a heap Node

Initilization arguments can be declared also on separate lines.

    let node = make @Extended_Node(
        parent: null
        type: 6
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
        accept: func (self: @T, visitor: @Visitor)
    }


## Pointers

A pointer contains the address of a value and can be created usig the `@` operator:

    struct Data {
        value: i32
    }

    let data = make Data()              \ local Data variable
    let data_ptr = @data                \ create pointer to data having type @Data
    let data_value_ptr = @data.value    \ create pointer to data.value having type @i32

Dereferencing is done via the `.@` operator:

    let response = 0
    let response_ptr = @response
    response_ptr.@ = 42

Struct member access uses auto-dereferencing. Following statements are the same:

    let response = data_ptr.value
    let response = data_ptr.@.value

There is no pointer arithmetic.

## Multi-pointers

A multi-pointer contains the address of a sequence of items that can be accessed like an array.

    let data: [42]Data                  \ array of 42 Data items
    let data_ptrs = @data               \ create pointer to data with type [@]Data

Accessing multi-pointer items is an unsafe operation.

    let result = data[1] == data_ptrs[1]    \ true

Default value is `nil`.

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

An array is a sequence of items with a size known at compile time.

An `[7]i32` array has the following in-memory structure:

    struct I32_7_Array {
        _0: i32
        _1: i32
        _2: i32
        _3: i32
        _4: i32
        _5: i32
        _6: i32
    }

Arrays are value types but are passed by reference for performance reasons. A function can modify an
array only if it was explicitly passed as a pointer to the array.

    func change(a1: [42]Data, a2: @[42]Data) {
        a1[0].value = 13        \ raises a compiler error
        a2[0].value = 42        \ this is the way
    }

## Strings

Strings have the `str` type, are immutable and default to the `""` value.

The `str` type is treated internally as the following struct:

    struct String {
        data: [@]u8
        length: usize
    }

String literals are converted to `str` values.

    let text = "Hello"      \ text uses 16 bytes on the stack and 2 bytes in the data section
    text = "42"             \ this assignment changes the data pointer and sets len to 2

Strings can be created at runtime using builtin functions...

## Variables

    let text = "123"                    \ text holds address and length of "123"
    let number = text.length + 1        \ number holds the usize result of the provided expression
    let root_node = make @Node()        \ root_node holds the address of a new Node

The variable names are symbols used by the compiler to know where the value are stored.

## Any

The `Any` type can be used only as reference to data of unknown type.

    let node = make @Node()
    let data: @Any = node       \ auto-casting to @Any
    let token = data.as(@Token) \ unsafe, but this is the way

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

The function parameters order must be respected and parameter labels are mandatory, unless
paramaters are marked as anonymous with the `anon` modifier.

    func panic() {}
    func panic(at location: @Location, anon message: str) {}
    func panic(at location: @Location, unexpected_keyword: @Token) {}
    func panic(at location: @Location, unexpected_token: @Token) {}

    panic(at: token.location, unexpected_token: token)  \ function call with labels 

> **NOTE**: Parameter labels are part of the generated function name, like: *panic*, *panic__at*,
*panic__at__unexpected_keyword* and *panic__at__unexpected_token*. There cannot be two functions
having the same name and the same sequence of parameter labels.

## Generic functions

    func max[T](v1: T, v2: T) -> T {
        if v1 > v2 {
            return v1
        }
        return v2
    }

The compiler will generate dedicated code for each specialization of a generic function.

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

## Extension methods

Methods can be declared also outside of a type block.

    func @Binary_Expression.accept(self, visitor: @Visitor) {
        visitor.visit(self)
    }
