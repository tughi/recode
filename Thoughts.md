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

The `@?` suffix declares a nullable pointer type.

The value of an `@?Any` variable can be access only after a `null` check.

```
length :: (self: @?String) -> Int {
    if (self != null) {
        return self.length
    }
}
```

## Checked Arrays

An `[Int8]` array has the following in-memory structure:

```
Int8_Array :: struct {
    size: Int
    data: @Int8
}
```

For checked arrays, the compiler makes sure that each access is withing bounds. The program will
panick if an out of bounds access is detected.

### Fixed size arrays

Fixed size arrays are arrays for which the compiler knows the size.

`[Any; 42]` can be passed as `[Any]` parameter. The compiler converts the fixed size array to a
checked array automatically.

## Strings

The `String` type has the following structure:

```
String :: struct {
    length: Int
    content: @Int8
}
```

String literals are global values of type `String`.

## Structs

```
Node :: struct {
    name: String        \ embedded
    parent: @Node       \ parent node address
    children: [@Node]   \ checked array of child node addresses
}
```

```
Extended_Node :: struct : Node {
    data: @Object       \ checked array of child node addresses
}
```

## Objects

The `Object` type is a special base type that holds `Type` information.

The compiler assignes the associated `Type` when an `Object` is allocated.

The `Object` structure looks like this:

```
Object :: struct {
    type: @Type
}
```

## Types

For each declared type, the compiler generates a `Type` global variable, named after the type.

The `Type` structure looks like this:

```
Type :: struct {
    id: Int
    base_type: @Type
}
```

## Variables

```
text: @String = "123"           \ text holds the address to the specified string
number: Int = text.length + 1   \ number holds the result of the provided expression
root_node := new Node           \ root_node holds the address of a Node
```

The variable names are symbols used by the compiler to know where the value are stored.
