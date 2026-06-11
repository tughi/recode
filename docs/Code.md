# Code Language Reference

This document describes the **Code** programming language — a statically-typed, procedural language for systems programming.

Statements are separated by newlines. There are no semicolons. Comments start with `//` and run to the end of the line.

## Program Entry Point

A Code program starts execution at `main`:

```code
proc main() -> i32 {
    return 0
}
```

The entry point may also accept command-line arguments:

```code
proc main(anon argc: i32, anon argv: [^][^]u8) -> i32 {
    return 0
}
```

---

## Primitive Types

| Type | Description |
|------|-------------|
| `bool` | Boolean (`true` / `false`) |
| `i8`, `i16`, `i32`, `i64` | Signed integers |
| `u8`, `u16`, `u32`, `u64` | Unsigned integers |
| `isize`, `usize` | Pointer-sized signed / unsigned integers |
| `str` | String (see [Strings](#strings)) |
| `Any` | Opaque pointer target (used with `^Any`) |

### Integer Literals

```code
let a = 42          // default type inferred from context
let b = 42i32       // explicit i32
let c = 255u8       // explicit u8
let d = 0usize      // explicit usize
let e = 0x0000_00ff // hex, underscores allowed
```

### Character Literals

```code
let ch = 'a'
let nl = '\n'
let zero = '0'
```

Character literals have type `u8`.

### Boolean Literals

```code
let yes = true
let no  = false
```

---

## Variables

```code
let name: Type          // declared, zero-initialized
let name = value        // type inferred from initializer
let name: Type = value  // explicit type with initializer
```

All `let` variables are mutable — they can be reassigned at any time with `=`:

```code
name = new_value
```

### Global Variables

Declared at file scope, and are zero-initialized by default:

```code
let counter: i32
let message: str
```

Global variables cannot have non-constant initializers. If initialization requires a procedure call or any non-trivial expression, assign the value inside a procedure:

```code
let stdout: ^Writer   // declared at file scope

proc init() {
    stdout = alloc Writer(...)
}
```

---

## Procedures

```code
proc name(param: Type, other: Type) -> ReturnType {
    ...
}

proc no_return(value: i32) {
    ...
}
```

### Parameter Labels

Every parameter has a **label** used by the caller and an internal **name**:

```code
// Default: label = name
proc echo(value: i32) -> i32 {
    return value
}
echo(value: 42)

// Custom label
proc echo(number value: i32) -> i32 {
    return value
}
echo(number: 42)

// Anonymous — caller passes no label
proc echo(anon value: i32) -> i32 {
    return value
}
echo(42)
```

### Procedure Overloading

Multiple procedures may share the same name if their parameter signatures differ:

```code
proc fallback() -> i32 {
    return 42
}

proc fallback(value: i32) -> i32 {
    return value
}
```

### Calling Style

Arguments may span multiple lines and mix inline / multi-line styles freely:

```code
test(1, 2, 3, 4, 5)

test(
    1, 2, 3
    4, 5
)
```

### Procedure Pointers

```code
let fn: proc (value: i32) -> i32       // declare
fn = echo                               // assign
let fn2 = echo                          // infer type
let result = fn(value: 42)             // call via pointer
```

Procedure pointer types for fallible procedures:

```code
let fn: proc () -> i32 !> i32
```

---

## Pointers

### Single Pointer `^T`

```code
let value = 42
let ref = ^value        // take address (prefix ^)
let copy = ref.^        // dereference (suffix .^)
ref.^ = 100             // assign through pointer
```

The `^` address-of operator binds loosely — it applies to the entire expression to its right, including member access chains:

```code
let field_ref = ^point.x          // address of point.x, not (^point).x
let deep_ref  = ^first.next.value // address of the nested field
```

Use parentheses to take the address first and then operate on the pointer:

```code
let any_ptr = (^value).as(^Any)
```

### Multi-Pointer `[^]T`

An unbound pointer to an array of elements:

```code
let array: [^]i32
let item = array[0]         // index
array[3] = 42               // assign through index
let elem_ref = ^array[3]    // address of element
```

Multi-pointers are obtained by casting (`malloc`, etc.) or from function parameters.

### Null Pointer

```code
let ptr: ^i32 = null
let typed_null = null.as(^i32)
```

### Type Casts

```code
value.as(TargetType)
```

Used for numeric conversions and pointer reinterpretation:

```code
let byte: u8 = 255
let wide = byte.as(i32)

let raw = malloc(32).as([^]i32)
let any_ptr = (^value).as(^Any)
```

### Type Introspection

```code
let i32_size: usize = type_size(i32)            // byte size of a type
let i32_alignment: usize = type_alignment(i32)  // alignment of a type
```

Both accept any type expression, including generic instantiations.

---

## Operators

### Arithmetic

`+`, `-`, `*`, `/`, `%` (modulo)

### Comparison

`==`, `!=`, `<`, `<=`, `>`, `>=`

### Logic

`and`, `or`, `not`

```code
if a and b { ... }
if a or b { ... }
if not c { ... }
```

### Unary

`-value` (integer negation), `not value` (boolean negation)

### Precedence

From highest to lowest:

| Level | Operators |
|-------|-----------|
| Unary | `-` (negation), `not` |
| Multiplicative | `*`, `/`, `%` |
| Additive | `+`, `-` |
| Comparison | `==`, `!=`, `<`, `<=`, `>`, `>=` |
| Logic | `and` |
| Logic | `or` |

Use parentheses to override the default grouping:

```code
if (t and f) or (f and t) { ... }   // and binds tighter than or
let x = value * 10 + offset         // * before +
```

---

## Control Flow

### if / else

```code
if condition {
    ...
}

if condition {
    ...
} else {
    ...
}

if condition {
    ...
} else if other {
    ...
} else {
    ...
}
```

### while

```code
while condition {
    ...
}
```

### loop

An infinite loop — use `break` to exit:

```code
loop {
    if done {
        break
    }
}
```

### break

Exits the innermost `while` or `loop`.

### return

```code
return value   // return with a value
return         // return from a void procedure
```

---

## Struct Types

```code
type Point = struct {
    x: i32
    y: i32
}
```

### Construction

```code
let p = Point(x: 16, y: 32)
```

Fields may be omitted (zero-initialized) or listed in any order.

### Heap Allocation

```code
let p = alloc Point(x: 0, y: 0)   // returns ^Point
```

### Member Access

```code
let x = p.x
p.y = 64

// Through a pointer
let pr = ^p
let x2 = pr.x      // auto-dereferences
```

### Callable Member

Struct fields may hold procedure pointers:

```code
type Function = struct {
    run: proc () -> i32
}
let f = Function(run: forty_two)
let result = f.run()
```

### Struct Inheritance (`super`)

A struct may embed another struct as its first field named `super`:

```code
type Vehicle = struct {
    wheels: i32
}

type Car = struct {
    super: Vehicle
}

type Sports_Car = struct {
    super: Car
    turbo: bool
}
```

- Fields from base types are accessible directly: `sports_car.wheels`
- A `^Sports_Car` is assignable to `^Vehicle` (implicit pointer narrowing)
- Methods defined on `Vehicle` are resolved on `Sports_Car`
- The `super` field must be a plain struct type (not a pointer)

---

## Fixed-Size Arrays

`[N]T` holds `N` contiguous elements of type `T`, stored in place (no heap allocation). The size must be an integer literal:

```code
let array: [4]i32
array[3] = 42               // assign through index
let item = array[3]         // index
let item_ref = ^array[3]    // address of element
```

Arrays nest — `[2][3]i32` is an array of two `[3]i32` rows:

```code
let matrix: [2][3]i32
matrix[1][2] = 42
```

Arrays are value types — assignment copies all elements:

```code
let copy = array            // copies the whole array
copy[3] = 13                // does not affect array[3]
```

Arrays may be struct fields, and structs may be array elements; accesses compose both ways:

```code
type Point = struct {
    x: i32
    y: i32
}

type Path = struct {
    points: [4]Point
}

let points: [2]Point
points[1].x = 42            // field of an array element

let path: Path
path.points[0].y = 7        // array field, then element field
```

### Construction

Arrays are constructed call-style, like structs — one unnamed value per item, and every item must be provided:

```code
let numbers = [3]i32(40, 1, 1)
let corners = [2]Point(Point(x: 1, y: 2), Point(x: 3, y: 4))
```

---

## Methods

Methods are procedures with a typed receiver as the first parameter:

```code
proc (^Type).method_name(self, param: i32) -> ReturnType {
    return self.field + param
}
```

Called with dot syntax:

```code
value.method_name(param: 42)
```

Methods may be defined on:
- Struct pointer: `proc (^Point).scale(self, ...) { ... }`
- Primitive types: `proc (i32).abs(self) -> i32 { ... }`
- Multi-pointer: `proc ([^]u8).length(self) -> i32 { ... }`
- Trait pointer: `proc (^Writer).end_line(self) -> ^Writer { ... }` (default impl)
- The `str` type: `proc (str).equals(self, anon other: str) -> bool { ... }`

The receiver label (`self` in the examples above) can be any name.

### Method Chaining

A method that returns a pointer to its receiver type enables chaining. For example, `write` is defined to return `^FILE` so subsequent calls can be chained:

```code
proc (^FILE).write(self, char ch: u8) -> ^FILE {
    fputc(ch.as(i32), self)
    return self
}
```

This allows calls to be chained directly:

```code
stdout.write(char: '4').write(char: '2').write(char: '\n')
```

The same pattern works for trait methods — a default method on a trait that returns a pointer to the trait also supports chaining:

```code
proc (^Writer).end_line(self) -> ^Writer {
    self.write_char('\n')
    return self
}

out.write("Hello, World!").end_line()
```

### Inherited Methods

Methods defined on a base struct type are callable directly on any derived type:

```code
type Token_Base = struct {
    lexeme: str
    source_position: usize
}

proc (^Token_Base).end_position(self) -> usize {
    return self.source_position + self.lexeme.length
}

type Integer = struct {
    super: Token_Base
    value: u64
}

let token = Integer(super: Token_Base(lexeme: "42", source_position: 5), value: 42)
token.end_position()   // resolves to Token_Base.end_position — returns 7
```

---

## Trait Types

Traits define an interface with required methods (structural typing):

```code
type Shape = trait {
    proc area(self) -> i32
}
```

Any type that has all required methods automatically satisfies the trait:

```code
type Square = struct { side: i32 }

proc (^Square).area(self) -> i32 {
    return self.side * self.side
}

type Circle = struct { radius: i32 }

proc (^Circle).area(self) -> i32 {
    return 314 * self.radius * self.radius / 100
}
```

### Construction

Wrap a pointer to a concrete value to create a trait value:

```code
let square = Square(side: 10)
let shape = Shape(^square)          // wrap a pointer
let shape2 = alloc Shape(^square)   // heap allocation
```

### Method Dispatch

```code
shape.area()    // calls Square.area — returns 100
shape2.area()   // calls through heap-allocated trait value
```

### Implicit Structural Typing

When a procedure accepts a trait value, a concrete value whose type satisfies the trait can be passed directly — the wrapping is done automatically:

```code
proc largest(anon a: Shape, anon b: Shape) -> i32 {
    if a.area() >= b.area() {
        return a.area()
    }
    return b.area()
}

let square = Square(side: 10)
let circle = Circle(radius: 5)
largest(square, circle)   // Square and Circle satisfy Shape implicitly
```

---

## Variant Types (Tagged Unions)

```code
type Value = variant {
    bool
    i32
    ^MyStruct
}
```

Variants may be nested — a variant may include another variant type as a member.

### Construction

```code
let v: Value = 42          // implicit — type inferred
let v2 = Value(42)         // explicit wrapping
let v3 = Value(nil)        // nil / empty
```

The `nil` value represents an unset variant.

### Pattern Matching — `switch`

The optional `as name` gives access to the inner value typed as the matched case:

```code
switch value {
    is TypeA as binding {
        // binding has type TypeA
    }
    is TypeB {
        // matches, but inner value not accessible
    }
    is nil {
        // unset variant
    }
    else {
        // catch-all
    }
}
```

Rules:
- `switch` must be exhaustive — all cases covered, or an `else` present
- `else` must come last
- Cases after `else` are an error
- Duplicate cases are an error

### Pattern Matching — `if is`

`as name` gives access to the inner value typed as the matched case:

```code
if value is i32 as integer {
    // integer has type i32
}

if value is i32 as integer {
    ...
} else {
    ...
}
```

### Negated Check — `is not`

`is not` checks that the variant does not hold the specified type. With `as`, the alias is typed as the actual case currently held:

```code
if value is not bool {
    // value holds something other than bool
}

if value is not bool as other {
    // other gives access to the actual inner value typed as the case held (e.g. i32)
}
```

---

## Optional Types

An optional type `?T` represents a value that is either present (holds a `T`) or absent (`nil`). It is a built-in alternative to declaring a two-case variant by hand.

```code
let x: ?i32 = 42      // has a value
let y: ?i32 = nil     // no value
```

Optional types work with any type: primitives, structs, pointers, etc.

### Construction

```code
let a: ?str = "hello"   // implicit wrap — value present
let b: ?str = nil        // absent
```

### Pattern Matching — `switch`

```code
switch x {
    is i32 as value {
        // value has type i32
    }
    is nil {
        // no value
    }
}
```

### Pattern Matching — `if is`

```code
if x is i32 as value {
    // value has type i32
}

if x is nil {
    // no value
}
```

### As a Struct Field or Return Type

```code
type Person = struct {
    name: str
    age: ?i32
}

proc find(anon target: i32) -> ?i32 {
    if target > 0 {
        return target
    }
    return nil
}
```

---

## Error Handling

### Fallible Return Type

```code
proc increment(anon value: i32) -> i32 !> Error {
    if value > 10 {
        raise Error(code: 42)
    }
    return value + 1
}
```

`T !> E` means: returns `T` on success, raises an error of type `E`.

### Handling Errors with `try`

```code
// Provide a fallback value
let result = try increment(13) else 0

// Access the error value in the else branch
let result = try increment(13) else error.code - 42

// Early return on error
let result = try increment(13) else {
    return error.code
}

// Yield a value from a block
let result = try increment(13) else {
    yield error.code - 42
}
```

In the `else` branch, `error` is the raised error value.

### Automatic Propagation

A call to a fallible procedure inside another fallible procedure propagates the error automatically (no explicit `try` needed):

```code
proc count_from(anon value: i32) -> i32 !> Error {
    let v = value
    while v < 100 {
        v = increment(v)   // error propagates automatically
    }
    return v
}
```

### `raise`

```code
raise ErrorValue
```

`raise` transfers control out of the current procedure (and any callers that don't handle it). Code after `raise` is unreachable.

---

## Defer

`defer` schedules a statement or block to run when the enclosing scope exits, in LIFO order:

```code
defer value = 42
defer {
    cleanup()
}
```

Deferred statements run before:
- A `return`
- A `break`
- A `raise`
- The end of a block `{ ... }`

Multiple defers execute in reverse order (last registered, first executed):

```code
defer value = 42    // runs second
defer value = 13    // runs first
```

Defers are scoped — a `defer` inside `{ ... }` fires at the end of that block, not the procedure.

---

## Constants

Compile-time constants with arithmetic expressions:

```code
const FORTY_TWO = 50 - 8
const FORTY_THREE = FORTY_TWO + 1
```

Constants may reference other constants. They are accessible from other packages via the package prefix.

---

## Strings

`str` is a built-in type backed by the `String` struct:

```code
type String = struct {
    data:   [^]u8
    length: usize
}
```

### String Literals

```code
let s: str = "hello"
let empty: str = ""
```

### Length

```code
let n = s.length    // usize
```

`length` is read-only — assignment to it is a compile error.

### String as `String`

You can cast between `str` and `^String` to access raw data:

```code
let string_ptr = (^s).as(^String)
let byte = string_ptr.data[0]
```

### Methods on `str`

Methods may be defined on `str` using the method syntax:

```code
proc (str).equals(self, anon other: str) -> bool { ... }
proc (str).concat(self, anon other: str) -> str { ... }
```

---

## Generics

Structs and their methods may be parameterized by type:

```code
type Array<T> = struct {
    items:    [^]T
    length:   usize
    capacity: usize
}
```

Multiple type parameters:

```code
type Map<K, V> = struct { ... }
```

### Instantiation

```code
let a: Array<i32>
let m: Map<str, i32>
let b = Array<i32>(items: null, length: 0, capacity: 0)
```

### Generic Methods

```code
proc (^List<T>).prepend<T>(self, data: T) {
    let item = alloc List_Item<T>(data: data, next: self.first_item)
    ...
}
```

The type parameter must appear in both the receiver type and the method's own type parameter list.

Generic specialization is monomorphized — each unique instantiation produces a separate compiled version.

---

## Packages and Imports

### File Layout

- Each `.code` file is a module.
- A directory of `.code` files is a package.
- Files within a package share the same namespace.

### Import

```code
import package_name
import package.subpackage
```

Access imported symbols with the package prefix:

```code
import source

let span = source.Span(start: 0, end: 42)
```

### The `builtin` Package

All primitive types (`i32`, `str`, `String`, etc.) live in the implicit `builtin` package. Normally they are accessed without a prefix, but if a package defines a type with the same name it shadows the builtin. In that case, use the `builtin.` qualifier to refer to the original:

```code
// A user-defined String that wraps the builtin one
type String = struct {
    lexeme: builtin.String
}

// A user-defined i32 that wraps the builtin one
type i32 = struct {
    value: builtin.i32
}

// Procedure returning the builtin type explicitly
proc main() -> builtin.i32 {
    let wrapped = i32(value: 0)
    return wrapped.value
}
```

The `builtin` qualifier is also available even when there is no shadowing — it is simply redundant in that case.

### Multi-Level Packages

For a dotted import path the namespace prefix is always the **last** component only:

```code
import calculator.expression
import calculator.source

let expr: expression.Expression   // not calculator.expression.Expression
let span: source.Span
```

---

## External Bindings

Bindings to external (C) symbols.

### External Type

```code
type FILE = external
```

Declares an opaque type whose definition is in C.

### External Procedure

```code
proc fputc(anon c: i32, anon file: ^FILE) -> i32 = external
proc exit(anon status: i32) = external
```

The Code parameter labels need not match the C names.

### External Variable

```code
// Use the Code identifier as the C name
let optind: i32 = external

// Provide an explicit C symbol name
let stdout: ^FILE = external "__stdoutp"
```

---

## Comments

```code
// Single-line comment
```

There are no block comments.

---

## Blocks

Any `{ ... }` creates a new scope. Standalone blocks are useful with `defer`:

```code
{
    defer cleanup()
    ...
}  // cleanup() runs here
```

---

## `yield`

`yield` produces a value from a `try ... else { ... }` block (analogous to `return` but scoped to the block):

```code
let result = try action() else {
    let v = error.code - 42
    yield v
}
```
