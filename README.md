# KV - Persistent Key-Value Store

A simple command-line key-value database implemented in C++ with persistent storage to disk.

## Overview

KV is a lightweight, persistent key-value store that allows you to insert, retrieve, delete, and manage integer-keyed data with string values. All data persists between program invocations through a plain-text database file.

## Features

- **Simple command-line interface** - All operations via command-line arguments
- **Persistent storage** - Data survives program restarts via `database.txt`
- **Five core operations** - put, get, delete, clear, and all
- **Integer keys** - Fast lookups using hash table implementation
- **String values** - Store arbitrary text (excluding commas)

## Installation

### Prerequisites
- C++11 or later compiler (g++, clang++)
- Standard C++ library
- Make (optional, for using Makefile)

### Compilation

**Using Makefile (recommended):**
```bash
make
```

**Manual compilation:**
```bash
g++ -std=c++11 -Wall -Wextra -o kv kv.cpp
```

### Makefile Targets

```bash
make           # Compile the program
make clean     # Remove object files and executable
make cleanall  # Remove everything including database.txt
make run       # Compile and run (no arguments)
```

## Usage

The general format is:
```bash
./kv [command1] [command2] ... [commandN]
```

Multiple commands can be specified on a single invocation and are executed in order from left to right.

### Commands

#### Put - Insert or Update a Key-Value Pair
**Format**: `p,key,value`

- `key` must be an integer
- `value` is any string without commas

**Examples**:
```bash
./kv p,10,remzi
./kv p,20,andrea p,40,someotherperson
./kv p,1,first p,2,second p,3,third
```

#### Get - Retrieve a Value by Key
**Format**: `g,key`

Prints `key,value` if found, otherwise prints `key not found`

**Examples**:
```bash
./kv g,10
# Output: 10,remzi

./kv g,999
# Output: 999 not found
```

#### Delete - Remove a Key-Value Pair
**Format**: `d,key`

Removes the key-value pair if it exists. Prints `key not found` if the key doesn't exist. Prints nothing on successful deletion.

**Examples**:
```bash
./kv d,10
# (no output if successful)

./kv d,999
# Output: 999 not found
```

#### Clear - Remove All Entries
**Format**: `c`

Removes all key-value pairs from the database.

**Example**:
```bash
./kv c
```

#### All - Display All Entries
**Format**: `a`

Prints all key-value pairs in the database, one per line. Order is not guaranteed.

**Example**:
```bash
./kv a
# Output:
# 1,first
# 2,second
# 3,third
```

## Persistence

Data is automatically loaded from `database.txt` at program startup and saved back to the file before program exit. The file format is plain text with one key-value pair per line:

```
1,first
2,second
3,third
```

If `database.txt` doesn't exist on first run, it will be created when data is first saved.

## Complete Usage Example

```bash
# Start fresh - insert some data
./kv p,1,apple p,2,banana p,3,cherry

# Retrieve a value
./kv g,2
# Output: 2,banana

# Add more data
./kv p,4,date p,5,elderberry

# View all entries
./kv a
# Output:
# 1,apple
# 2,banana
# 3,cherry
# 4,date
# 5,elderberry

# Delete an entry
./kv d,3

# Verify deletion
./kv g,3
# Output: 3 not found

# Try to get a non-existent key
./kv g,999
# Output: 999 not found

# Clear everything
./kv c

# Verify database is empty
./kv a
# (no output)
```

## Error Handling

### Bad Command
If a command is malformed or unrecognized, the program prints `bad command` and continues processing remaining commands.

**Examples of bad commands**:
- Invalid operation: `x,10,value`
- Non-integer key: `p,abc,value`
- Missing arguments: `p,10` or `g`
- Empty command

**Example**:
```bash
./kv p,abc,test g,10
# Output:
# bad command
# 10,remzi
```

### Key Not Found
When attempting to get or delete a non-existent key:
```bash
./kv g,999
# Output: 999 not found
```

## Implementation Details

- **Data structure**: `std::unordered_map<int, std::string>` for O(1) average-case operations
- **Parsing**: Custom string splitting using `std::stringstream` and `std::getline`
- **Validation**: Try-catch blocks for integer parsing with proper error handling
- **Persistence**: Plain-text file I/O using `std::fstream`

## Limitations

- Values cannot contain commas
- Keys must be integers (32-bit signed range: -2,147,483,648 to 2,147,483,647)
- No support for concurrent access or file locking
- Database file is plain text (not encrypted or compressed)
- No transaction support or atomicity guarantees

## Project Structure

```
.
├── kv.cpp          # Main source code
├── Makefile        # Build configuration
├── database.txt    # Persistent storage (auto-generated)
└── README.md       # This file
```

## Testing

The program has been tested with various scenarios including:

- Single and multiple command invocations
- Edge cases (empty database, non-existent keys, overwriting values)
- Error conditions (bad commands, invalid keys, missing arguments)
- Persistence across multiple program runs
- Large datasets

## Author

Created by Griffin Kuchar as a warm-up project for Operating Systems class to practice C++ programming and systems concepts.

## License

Educational project - free to use and modify.