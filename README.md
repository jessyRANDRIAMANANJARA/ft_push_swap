# ft_push_swap

Minimal implementation of the 42 **push_swap** project:
- Parses integer arguments (including quoted, space-separated values)
- Validates invalid input, duplicates, and int overflow (`Error` on stderr)
- Prints stack operations to sort values using `sa`, `pa`, `pb`, `ra`, `rra`
- Uses small-sort logic for up to 5 values and radix sort for larger inputs

## Build

```bash
make
```

## Run

```bash
./push_swap 3 2 1
```
