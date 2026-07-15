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
proc main(argc: i32, argv: [^][^]u8) -> i32 {
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
let log_file: ^FILE   // declared at file scope

proc init() {
    log_file = fopen(...)
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

### Parameters

Each parameter has a **name** and a **type**:

```code
proc echo(value: i32) -> i32 {
    return value
}
```

Arguments are **positional**:

```code
echo(42)
```

A caller may optionally annotate an argument with its parameter name for clarity. If given, the name must match the parameter at that position:

```code
echo(value: 42)    // OK — matches the parameter name
echo(number: 42)   // error — the parameter is named `value`
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
let fn: proc (i32) -> i32               // declare
fn = echo                               // assign
let fn2 = echo                          // infer type
let result = fn(42)                     // call via pointer
```

### Generic Procedures

A procedure may declare **type parameters** in `<...>` after its name; the parameter names act as types throughout the signature and body:

```code
proc identity<T>(value: T) -> T {
    return value
}
```

A generic procedure may be called with **explicit type arguments**:

```code
let n = identity<i32>(42)
```

The type arguments may also be **inferred** from the call arguments — omit the `<...>` and each type parameter is deduced by matching the declared parameter types against the argument types:

```code
let n = identity(42)       // T inferred as i32
```

- Type parameters are deduced from the arguments — including through pointer types (`^T`, `[^]T`) and, for a generic method, from the receiver.
- A type parameter that appears only in the return type (e.g. `proc make<T>() -> ^T`) cannot be inferred and requires explicit type arguments; the call is rejected with `Cannot infer type arguments`.
- The type-argument list must match the type-parameter list in length.
- The `<` of a type-argument list follows the callee directly, with no space — a `<` with surrounding spaces is the less-than operator.
- A generic procedure must be instantiated and called; it cannot be used as a value or assigned to a procedure pointer, and it cannot be `external`.

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

### Bitwise

`&` (AND), `|` (OR), `^` (XOR), `<<` (shift left), `>>` (shift right)

Both operands must have the same integer type, which is also the result type. `>>` is arithmetic (sign-filling) on signed types and logical (zero-filling) on unsigned types. A shift count outside `0 .. bit width - 1` is a runtime error.

```code
let masked = flags & 0x0F
let packed = high << 8 | low
if flags & 4 != 0 { ... }   // & binds tighter than !=
```

Binary `^` is XOR; prefix `^` remains the address-of operator (`^value`).

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
| Shift | `<<`, `>>` |
| Bitwise AND | `&` |
| Bitwise XOR | `^` |
| Bitwise OR | `|` |
| Comparison | `<`, `<=`, `>`, `>=` |
| Equality | `==`, `!=` |
| Logic | `and` |
| Logic | `or` |

Equality binds looser than comparison — `a == b < c` parses as `a == (b < c)`.

The bitwise levels bind tighter than comparisons, so `flags & MASK != 0` parses as `(flags & MASK) != 0`. Note that shifts bind looser than `+`/`-`: `x << 2 + 1` parses as `x << (2 + 1)`.

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

### continue

Skips the rest of the current iteration of the innermost `while` or `loop` and starts the next one:

```code
let i = 0
while i < 10 {
    i = i + 1
    if i % 2 == 0 {
        continue    // skip even numbers
    }
    // ... only runs for odd i
}
```

In a `while`, control jumps back to the condition (which is re-tested); in a `loop`, it jumps back to the top of the body. Like `break`, it ends the control flow path it is on — a statement after `continue` in the same block is unreachable.

### switch

Dispatches on an enum value. A case may match several members with `or`; the optional `else` handles the remaining members and must come last. There is no fallthrough.

```code
switch direction {
    case .EAST {
        return 1
    }
    case .NORTH or .SOUTH {
        return 0
    }
    else {
        return -1
    }
}
```

- The switched value must be an enum and is evaluated once.
- Case labels are members of the switched enum type (dot shorthand infers it); listing a member twice is an error.
- Without `else`, the cases must cover **every** member — a missing one is an error. An `else` when all members are covered is also an error.
- `break` and `continue` keep their loop meaning inside a case body.
- An empty case body is allowed — it explicitly ignores that member.

### return

```code
return value   // return with a value
return         // return from a void procedure
```

### panic

```code
panic "Not supported yet"   // with a message
panic                       // without a message
```

Terminates the program immediately: writes `<file>:<line>: Panic! <message>` to `stderr` and exits with status 1, where `<file>:<line>` is the location of the `panic` statement itself. The message must be a string literal. Like `return`, `panic` ends the control flow path it is on, so it satisfies the "missing return statement" check.

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

Fields may be listed in any order, but a struct initializer must cover **all** fields of the struct — omitting any field is an error (`Struct member not initialized: <name>`). To get a zero-initialized value, declare without an initializer instead (`let p: Point`).

### Heap Allocation

There is no built-in allocation expression. Heap memory comes from an external allocator (e.g. libc `malloc`): allocate the right number of bytes, cast the pointer, and store a constructed value through it:

```code
let p = malloc(type_size(Point)).as(^Point)
p.^ = Point(x: 0, y: 0)
```

```code
proc malloc(size: usize) -> ^Any = external
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

### Generic Structs

A struct may declare **type parameters** in `<...>` after its name; the parameter names act as types throughout the member list:

```code
type Box<T> = struct {
    value: T
}

type Node<T> = struct {
    value: T
    next: ^Node<T>    // self-reference is fine
}
```

Every use of a generic struct names its type arguments — in type position and in construction alike:

```code
let node: ^Node<i32> = null
let boxed = Box<Box<i32>>(value: Box<i32>(value: 42))
```

Methods may target one instance, or all of them via a generic procedure whose type parameters appear in the receiver:

```code
proc (^Box<i32>).increment(self) { ... }        // only on Box<i32>
proc (^Box<T>).get<T>(self) -> T { ... }        // on every Box<T>; T inferred from the receiver
```

A generic procedure can also infer its type parameters through a generic struct argument:

```code
proc unwrap<T>(box: Box<T>) -> T { ... }
let n = unwrap(Box<i32>(value: 42))    // T inferred as i32
```

- Each distinct type-argument list names a distinct struct type; two mentions of `Box<i32>` are the same type, while `Box<i32>` and `Box<u8>` are unrelated.
- The type-argument list must match the type-parameter list in length (`Expected N type arguments but got M`); referencing a generic struct without type arguments is an error (`Missing type arguments`), as is applying type arguments to a non-generic type (`Not a generic type`).
- Only structs can be generic — type parameters on an `enum` (or any other type declaration) are rejected with `Only struct types can be generic`.

---

## Enum Types

```code
type Direction = enum {
    NORTH
    EAST
    SOUTH
    WEST
}
```

### Member Access

Members are accessed through the type name:

```code
let d = Direction.NORTH
```

When the enum type is inferable from context, the type name may be omitted — a **dot shorthand**:

```code
let d: Direction = .WEST   // declared type provides the context
d = .SOUTH                 // d is already a Direction
if d == .SOUTH { ... }     // compared against a Direction
```

The shorthand requires an inferable type — `let d = .SOUTH` on its own is a compile error.

Enum values are compared with `==` and `!=`.

### Built-in Members

Every enum value carries two read-only members:

```code
let d = Direction.SOUTH
let v = d.value   // i32 ordinal of the member (NORTH = 0, EAST = 1, …)
let n = d.name    // member name as str ("SOUTH")
```

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
- The `str` type: `proc (str).equals(self, other: str) -> bool { ... }`

The receiver parameter (`self` in the examples above) can be any name.

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

### Method Pointers

A method can be referenced as a value — a procedure pointer — using the type-qualified form `(T).method`, which mirrors the way methods are declared (`proc (T).method`). The parentheses are part of the syntax and are required.

```code
type Point = struct {
    x: i32
    y: i32
}

proc (Point).get_x(self) -> i32 {
    return self.x
}

proc main() -> i32 {
    let get_x = (Point).get_x   // proc (Point) -> i32
    let point = Point(x: 42)
    return get_x(point)
}
```

The result is an ordinary procedure pointer whose first parameter is the receiver, so it is called by passing the receiver explicitly (`get_x(point)`, not `point.get_x()`).

The receiver may be any type a method can be defined on:

```code
let a = (i32).abs           // primitive receiver
let b = (^Point).scale      // pointer receiver
let c = ([^]u8).length      // multi-pointer receiver
let d = (str).equals        // str receiver
```

Restrictions:

- The parentheses are mandatory. Writing `Point.get_x` is a compile error (`Did you mean: \`(Point).get_x\`?`).
- Only a **type** receiver yields a method pointer. Taking a method off a **value** — e.g. `(42).get_value` — is rejected, because Code has no closures to capture the receiver.

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
proc (str).equals(self, other: str) -> bool { ... }
proc (str).concat(self, other: str) -> str { ... }
```

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
proc fputc(c: i32, file: ^FILE) -> i32 = external
proc exit(status: i32) = external
```

The Code parameter names need not match the C names.

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

Any `{ ... }` creates a new scope. Variables declared inside a block are not visible outside it:

```code
{
    let temp = compute()
    use(temp)
}  // temp is out of scope here
```

