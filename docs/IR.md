# IR Instruction Reference

This document describes all instructions supported by the ReCode intermediate representation. The IR uses SSA (Static Single Assignment) form — each value is defined exactly once, and variables are renamed with numeric suffixes (e.g., `%x.1`, `%x.2`) when redefined.

## Structural Elements

### Function declaration

```
$function_name(%param: type, ...): return_type {
    ...
}
```

Defines a procedure with typed parameters and a return type. The return type annotation is optional — omitting it implies `void`.

Global names may be dotted (e.g. `$code.ast.parse`) and may end with one or more `+`-separated identifiers that encode procedure parameter labels:

```
$test.add+anon+with(%a: i32, %b: i32): i32 {
    ...
}
```

The `+...` suffix is part of the name — `$test.add+anon+with` is the symbol to `call`.

#### Methods (receiver procedures)

A receiver type written as `$( <type> ).<member>` attaches a method to a type. The same member name on different receivers names distinct procedures, so the receiver acts as a namespace. The receiver parameter is written without a type and defaults to the receiver type.

```
$([code.ast.Number]).get(%self): i32 {
@1:
    %0: [i32] = offset %self code.ast.Number.value
    %1: i32 = load %0
    ret %1
}
```

The method is called by its full name, with the receiver passed as the first argument:

```
%n: [code.ast.Number] = alloc code.ast.Number
...
%v: i32 = call $([code.ast.Number]).get %n
```

External functions are declared as external globals:

```
$fputc: [proc (i32, [File]): i32] = external
```

### Labels

```
@1:
```

Numeric labels mark basic block entry points and serve as branch targets within functions.

### Live variables

```
[ %var1 %var2 ... ]
```

Lists the variables whose values are still needed by subsequent instructions at a given point.

### Type declaration

```
type Point = struct {
    x: i32
    y: i32
}
type FILE = opaque
type code.ast.Number = struct {
    value: i32
}
```

Defines a named struct type or declares an opaque (externally defined) type. Type names may be namespaced with `.` (e.g. `code.ast.Number`); the qualified name is used everywhere the type is referenced, including struct-field `offset` (`offset %p code.ast.Number.value`).

### External global variable

```
$stdout: [[File]] = external
```

Declares an external global variable (e.g., from C). All global symbols are pointer values, so the type must reflect that (e.g., a global `i32` would be declared as `[i32]`).

### String-literal global

```
$message: [*]u8 = "Hello!\n"
```

Declares a module-level byte payload. The declared type must be `[*]u8`; the literal's decoded bytes are stored once at module load and the global's value is a `[*]u8` pointer to them. The decoded bytes are always implicitly null-terminated (the trailing `\0` is appended automatically and is not counted by callers who track length separately), so byte-walking loops terminating on `0` work without an explicit `"\0"` in the source.

Recognised escape sequences: `\0`, `\n`, `\t`, `\\`, `\'`, `\"`. Any other escape is a lex error.

### Constant-initialized global

```
$answer: [i32]  = -42
$delta:  [u64]  = 0xffff_ffff_ffff_fff0
$enabled: [bool] = true
$newline: [u8]  = '\n'
$nothing: [[i32]] = null
```

Declares a mutable global with a constant initial value. The declared type must be a single pointer `[T]`; the initializer is a literal of the pointee type `T`, using the same syntax as the `const` instruction (optional leading `-`, optional trailing type suffix, `true`/`false`, character literals, and `null` for pointer pointees). The value is encoded into the global's payload at module load and the global's value is a `[T]` pointer to it, so `load`/`store` read and write the live value.

## Types

**Primitive:** `bool`, `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `isize`, `usize`

**Single pointer:** `[T]` — points to exactly one `T`; supports `load`, `store`, and struct `offset`. Produced by `alloc`, struct `offset`, and indexed `offset`.

**Multi-pointer:** `[*]T` — points into an array of `T`; supports indexed `offset` only (not direct `load`/`store`). Used for `$main`'s `argv` parameter and string pointers.

**Special:** `Any` is only valid as a pointer pointee — it represents an erased pointee type (analogous to `void*` in C) and has no size of its own

## Instructions

### `add`

Integer addition.

```
%result: i32 = add %left %right
```

### `alloc`

Allocates stack memory for a local variable and returns a `[T]` single pointer to it.

```
%x.ptr: [i32] = alloc i32
```

### `br`

Conditional branch. Jumps to the first label if the condition is true, otherwise to the second.

```
br %condition @2 @3
```

### `call`

Calls a function. Callee type must be a `[proc]` function pointer. Arguments follow the callee. The result is omitted for void calls.

```
%result: i32 = call $add %a %b
%result: i32 = call %fn_ptr %a
call $print %value
```

### `cast`

Converts between integer types (widening/narrowing, matching C sign-extension rules) or between any two pointer types (`[T]`, `[*]T`, or combinations).

```
%wide: i32 = cast %narrow       -- u8 to i32, zero-extends
%byte: u8 = cast %wide          -- i32 to u8, truncates
%any: [Any] = cast %specific    -- [T] to [Any]
%reint: [u8] = cast %i32ptr     -- [i32] to [u8]
%mp: [*]u8 = cast %sp           -- [u8] to [*]u8
```

### `cmp_eq`

Compares two values for equality. Returns `bool`.

```
%eq: bool = cmp_eq %left %right
```

### `cmp_ge`

Greater-than-or-equal comparison. Returns `bool`.

```
%ge: bool = cmp_ge %left %right
```

### `cmp_gt`

Greater-than comparison. Returns `bool`.

```
%gt: bool = cmp_gt %left %right
```

### `cmp_le`

Less-than-or-equal comparison. Returns `bool`.

```
%le: bool = cmp_le %left %right
```

### `cmp_lt`

Less-than comparison. Returns `bool`.

```
%lt: bool = cmp_lt %left %right
```

### `cmp_ne`

Not-equal comparison. Returns `bool`.

```
%ne: bool = cmp_ne %left %right
```

### `const`

Loads a compile-time constant literal into a register.

```
%zero: i32 = const 0
%flag: bool = const true
%ch: u8 = const 'a'
%mask: u64 = const 0x0000_0000_ffff_ffff
%ptr: [i32] = const null
%buf: [*]u8 = const null
```

### `div`

Integer division.

```
%result: i32 = div %left %right
```

### `jmp`

Unconditional jump to a label.

```
jmp @3
```

### `load`

Reads a value from a `[T]` single pointer.

```
%value: i32 = load %ptr
```

### `mod`

Integer modulo (remainder).

```
%result: i32 = mod %left %right
```

### `mul`

Integer multiplication.

```
%result: i32 = mul %left %right
```

### `neg`

Integer negation (unary minus).

```
%result: i32 = neg %value
```

### `not`

Boolean negation.

```
%result: bool = not %value
```

### `offset`

Pointer arithmetic. Two forms:

- **Indexed** (`[*]T %index => [T]`): computes a `[T]` single pointer to the element at `%index` in a multi-pointer. The source must be `[*]T`.
- **Struct field** (`[Struct] Name.field => [FieldT]`): computes a `[FieldT]` single pointer to a named field. The source must be `[Struct]`.

Both forms always produce a `[T]` single pointer.

```
%elem: [u8] = offset %array_ptr %index
%field: [i32] = offset %struct_ptr Point.x
```

### `phi`

SSA phi function. Selects a value based on the predecessor basic block.

```
%result: bool = phi @1 %val_from_block1 @4 %val_from_block4
```

### `ret`

Returns from the current function, optionally with a value.

```
ret %value
ret
```

### `store`

Writes a value to memory through a `[T]` single pointer.

```
store %ptr %value
```

### `struct`

Constructs a struct value with the specified field values.

```
%point: Point = struct Point .x %x .y %y
%line: Line = struct Line .p1 %p1 .p2 %p2
```

### `sub`

Integer subtraction.

```
%result: i32 = sub %left %right
```
