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

```
$function_name(%param: type, ...) {
    ...
}
```

A declaration without a body declares an external function:

```
$fputc(%c: u8, %file: ptr<FILE>): i32
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
```

Defines a named struct type or declares an opaque (externally defined) type.

### External global variable

```
external $stdout: ptr<FILE>
```

Declares an external global variable (e.g., from C).

## Types

**Primitive:** `bool`, `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `isize`, `usize`

**Pointer:** `ptr<T>`, `ptr<ptr<T>>`, `ptr<proc (args...) -> return_type>`

**Special:** `Any` (generic/opaque pointer target)

## Instructions

### `add`

Integer addition.

```
%result: i32 = add %left %right
```

### `address`

Takes the address of a named symbol, producing a pointer.

```
%fp: ptr<proc (value: i32) -> i32> = address $echo__value
```

### `alloc`

Allocates stack memory for a local variable and returns a pointer to it.

```
%x.ptr: ptr<i32> = alloc i32
```

### `br`

Conditional branch. Jumps to the first label if the condition is true, otherwise to the second.

```
br %condition @2 @3
```

### `call`

Calls a function. Callee type must be a function pointer. Arguments follow the callee. The result is omitted for void calls.

```
%result: i32 = call $add %a %b
%result: i32 = call %fn_ptr %a
call $print %value
```

### `cast`

Converts a value between compatible types (numeric widening/narrowing, pointer reinterpretation).

```
%wide: i32 = cast %narrow       -- u8 to i32
%byte: u8 = cast %wide          -- i32 to u8
%any: ptr<Any> = cast %specific -- ptr<T> to ptr<Any>
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

Reads a value from memory at the given pointer.

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

Pointer arithmetic. Computes a pointer to an array element by index or to a struct field by name.

```
%elem: ptr<u8> = offset %array_ptr %index
%field: ptr<i32> = offset %struct_ptr Point.x
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

Writes a value to memory at the given pointer.

```
store %ptr %value
```

### `struct`

Constructs a struct value with the specified field values.

```
%point: Point = struct { Point.x: %x, Point.y: %y }
%line: Line = struct { Line.p1: %p1, Line.p2: %p2 }
```

### `sub`

Integer subtraction.

```
%result: i32 = sub %left %right
```
