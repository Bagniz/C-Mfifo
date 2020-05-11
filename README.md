# Mfifo

In this project we try to implement a communication system between processes
that allows two types of communication:
* Similar communication to Pipes in C
* Message communication

## Getting Started

These instruction will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites

To be able to run the tests confortably you need to have localy on your conputer:
* `GCC` compiler
```bash
sudo apt-get install gcc
```
* `Make` command
```bash
sudo apt-get install build-essential
```
* `Git` Version control system
```bash
sudo apt-get install git
```

### Installing

To get the project files on your computer localy for testing or developement you
need to:

1. Open a `terminal`
1. Create a new folder to put project files in it
1. Clone project files using `git`
```git
git clone https://gaufre.informatique.univ-paris-diderot.fr/khengui/c-mfifo.git
```

To build the project with all its executables:

1. Change directory to the root of the project
1. Build the project
```bash
make
```

If you want to clean all executables:

1. Change directory to the root of the project
1. Clean the project
```bash
make clean
```

## Running The Tests

### Prerequisites

To be able to run the tests you need to create an `mfifo object`
before executing the tests

#### Create an Mfifo

Navigate to the `config` folder
```bash
cd C-Mfifo/config
```

If you did not build the project already, then build the executable
```bash
make
```

Create an `mfifo object` by giving it a `name` and a `capacity`
```bash
./create mfifo 20

# Results

# Mfifo object mfifo created with capacity 20
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

#### Delete an Mfifo

Navigate to the `config` folder
```bash
cd C-Mfifo/config
```

If you did not build the project already, then build the executable
```bash
make
```

Delete an `mfifo object` by providing its `name`
```bash
./delete mfifo

# Results

# Mfifo object mfifo deleted
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Capacity

Navigate to the `tests/mfifo_capacity` folder
```bash
cd C-Mfifo/tests/mfifo_capacity
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./capacity mfifo

# Results

# Connected to mfifo object mfifo
#  mfifo capacity is 10
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Connect

Navigate to the `tests/mfifo_connect` folder
```bash
cd C-Mfifo/tests/mfifo_connect
```

If you did not build the project already, then build the executable
```bash
make
```

To connect to an existing named `mfifo object`, just provide its `name`
```bash
./connect mfifo

# Results
# Connected to mfifo object mfifo with capacity 20
```

To connect a new named `mfifo object`, you need to provide its `name`
And its `capacity`, and specify if it uses the `O_EXCL` option to create
the object with `true` of `false`
```bash
./connect mfifo 20 false
# OR 
./connect mfifo 20 true # with O_EXCL

# Results

# Mfifo object mfifo created with capacity 20
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Disconnect

Navigate to the `tests/mfifo_disconnect` folder
```bash
cd C-Mfifo/tests/mfifo_disconnect
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./disconnect mfifo

# Results

# Connected to mfifo object mfifo
#  mfifo capacity is 20
# Disconnected from mfifo object mfifo
#  Segmentation Fault
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Free Memory

Navigate to the `tests/mfifo_free_memory` folder
```bash
cd C-Mfifo/tests/mfifo_free_memory
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./free_memory mfifo

# Results

# Connected to mfifo object mfifo
#  mfifo free space is 20

# PS: (It also includes the case in the memory that never contains a value
# thats why if mfifo is empty, than mfifo_free_memory(mfifo) > mfifo_capacity(mfifo))
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Lock Unlock

Navigate to the `tests/mfifo_lock_unlock` folder
```bash
cd C-Mfifo/tests/mfifo_lock_unlock
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./lock_unlock mfifo

# Comment
# Its better to execute to instances at the same time to see the effect,
# where one will wait until the other finishes (unlock the object) to
# start executing

# Results

# Connected to mfifo object mfifo
# Locked mfifo object mfifo
# 0
# 1
# 2
# 3
# 4
# Unlocked mfifo object mfifo
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Read Write

Open two terminals or more

Navigate to the `tests/mfifo_read_write` folder
```bash
cd C-Mfifo/tests/mfifo_read_write
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
# On one of the terminals
./write mfifo

# On another terminal
./read mfifo [true | false] 
# if true, use lock() and unlock() with read
# if flase, use only read()
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Trylock Unlock

Navigate to the `tests/mfifo_trylock_unlock` folder
```bash
cd C-Mfifo/tests/mfifo_trylock_unlock
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./trylock_unlock mfifo

# Comment
# Its better to execute to instances at the same time to see the effect,
# where one will wait until the other finishes (unlock the object) to
# start executing

# Results on the first process

# Connected to mfifo object mfifo
# Locked mfifo object mfifo
# 0
# 1
# 2
# 3
# 4
# Unlocked mfifo object mfifo

# Results on the second process

# Connected to mfifo object mfifo
# Cannot trylock mfifo object mfifo
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Trywrite Read

Open two terminals or more

Navigate to the `tests/mfifo_trywrite_read` folder
```bash
cd C-Mfifo/tests/mfifo_trywrite_read
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
# On one of the terminals
./write mfifo

# On another terminal
./read mfifo [true | false] 
# if true, use lock() and unlock() with read
# if flase, use only read()
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Unlink

Navigate to the `tests/mfifo_unlink` folder
```bash
cd C-Mfifo/tests/mfifo_unlink
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
./unlink mfifo

# Results

# Connected to mfifo object mfifo
#  mfifo capacity is 20
# Unlinked mfifo object mfifo

# Trying to reconnect to mfifo object mfifo
# Could not reconnect to mfifo object mfifo it is now deleted
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

### Write Partial Read

Open two terminals or more

Navigate to the `tests/mfifo_write_partial_read` folder
```bash
cd C-Mfifo/tests/mfifo_write_partial_read
```

If you did not build the project already, then build the executable
```bash
make
```

Provide the `mfifo object`'s `name`
```bash
# On one of the terminals
./write mfifo

# Results

# Connected to mfifo object mfifo
# Process 20387 wrote all caracters abcdefghij

# On another terminal
./read mfifo [true | false] 
# if true, use lock() and unlock() with read
# if flase, use only read()

# Results

# IF (true)

# Connected to mfifo object mfifo
# Locked mfifo object mfifo
# Process 20389 read caracter a
# Process 20389 read caracter b
# Process 20389 read caracter c
# Process 20389 read caracter d
# Process 20389 read caracter e
# Process 20389 read caracter f
# Process 20389 read caracter g
# Process 20389 read caracter h
# Process 20389 read caracter i
# Process 20389 read caracter j
# Unlocked mfifo object mfifo

# OR (false)

# Connected to mfifo object mfifo
# Process 20644 read caracter a
# Process 20644 read caracter b
# Process 20644 read caracter c
# Process 20644 read caracter d
# Process 20644 read caracter e
# Process 20644 read caracter f
# Process 20644 read caracter g
# Process 20644 read caracter h
# Process 20644 read caracter i
# Process 20644 read caracter j
```

You can use the `clean` option of `make` to delete the executables
```bash
make clean
```

## Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language)) - Programming Language
* [Git](https://git-scm.com/) - Free distributed version control system

## Authors

Please read [EQUIPE.md](EQUIPE.md) for details on our team, and the contributors on this project