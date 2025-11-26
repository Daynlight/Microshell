<div align=center>
  <h1>Microshell</h1>
</div>

## About
This is small shell build on threads optimized for parallel operations and data batching. Main focus is to make it work for multiple operations at the same time. Contains only own implementations of structures no libs. Uses a lot of dynamic arrays.


---


## Screenshots


---


## TOC
- [About](#about)
- [Screenshots](#screenshots)
- [TOC](#toc)
- [Installation](#installation)
- [Usage](#usage)
- [Diagram](#diagram)
- [Components](#components)
  - [Error Codes](#error-codes)
  - [Log System (SINGLETON)](#log-system-singleton)
  - [Microshell Initialize](#microshell-initialize)
  - [Microshell Destroy](#microshell-destroy)
  - [Shared Memory](#shared-memory)
  - [Helpers](#helpers)
  - [Input Layer](#input-layer)
  - [Processing Layer](#processing-layer)
  - [Process Thread](#process-thread)
  - [Own Commands](#own-commands)
  - [Output Layer](#output-layer)
- [Error Handling](#error-handling-32)
- [Structures](#structures)
  - [Vector](#vector)
  - [String](#string)
- [Tests](#tests)
- [Features](#features)


---


## Installation


---


## Usage


---


## Diagram
![Diagram](docs/Architecture.svg)





## Components
### Error Codes
##### Responsibility
  * storing error codes for pipeline errors checking.



### Log System (SINGLETON)
##### Responsibility
  * Used for logging
  * Used for testability
##### Functions
  * output
  * info
  * warning
  * error



### Microshell Initialize
##### Responsibility
  * Start program
  * Run Threads (Input, Processing, Output, Memory Updater)
##### Functions
##### Error Handling



### Microshell Destroy



### Shared Memory
#### Processing Priority Queue
##### Responsibility
##### Functions
##### Error Handling

#### Processing Diff Buffer
##### Responsibility
##### Functions
##### Error Handling

#### Command Diff Buffer
##### Responsibility
##### Functions
##### Error Handling

#### Env Var
##### Responsibility
##### Functions
##### Error Handling



### Helpers
#### History
##### Responsibility
##### Functions
##### Error Handling

#### Backup System
##### Responsibility
##### Functions
##### Error Handling

#### Prefix Array
##### Responsibility
##### Functions
##### Error Handling

#### Memory Updater
##### Responsibility
##### Functions
##### Error Handling

#### Update Files
##### Responsibility
##### Functions
##### Error Handling

#### Data I/O
##### Responsibility
##### Functions
##### Error Handling



### Input Layer
#### Get Input
##### Responsibility
##### Functions
##### Error Handling

#### Input Action (Strategy)
##### Responsibility
##### Functions
##### Error Handling

#### Check Command Correctness
##### Responsibility
##### Functions
##### Error Handling

#### Add to Processing Queue
##### Responsibility
##### Functions
##### Error Handling

#### Predict Command
##### Responsibility
##### Functions
##### Error Handling

#### Prefix Controller
##### Responsibility
##### Functions
##### Error Handling

#### History Controller
##### Responsibility
##### Functions
##### Error Handling

#### Auto Complete
##### Responsibility
##### Functions
##### Error Handling



### Processing Layer
#### Command Thread Controller
##### Responsibility
##### Functions
##### Error Handling

#### Parse Command
##### Responsibility
##### Functions
##### Error Handling

#### Run Process
##### Responsibility
##### Functions
##### Error Handling

#### Result Controller
##### Responsibility
##### Functions
##### Error Handling



### Process Thread
#### Process Start
##### Responsibility
##### Functions
##### Error Handling

#### Process Run
##### Responsibility
##### Functions
##### Error Handling

#### Check Result
##### Responsibility
##### Functions
##### Error Handling



### Own Commands
#### cd
##### Responsibility
##### Functions
##### Error Handling

#### exit
##### Responsibility
##### Functions
##### Error Handling

#### help
##### Responsibility
##### Functions
##### Error Handling



### Output Layer
#### Get output
##### Responsibility
##### Functions
##### Error Handling

#### Move Cursor
##### Responsibility
##### Functions
##### Error Handling

#### Print in Terminal
##### Responsibility
##### Functions
##### Error Handling


---


## Error Handling


---


## Structures
### Vector
##### IDEA
Vector is dynamic array that allows storing dynamic data that can change with time We want it for unordered_map and string.

##### How it works:

##### In this project:

##### Fields:

##### Complexity:

##### Functions:
- [ ] void init(size_of_el, [none, reserve_size])
- [ ] void destroy()
- [ ] void reserve(size)
- [ ] void resize(size)
- [ ] void shrink() ^
- [ ] void fit()    ^
- [ ] void push(data)
- [ ] char* pop()
- [ ] void erase(x, y) -- it removes in [x, y] with edges, circular indexes
- [ ] void clean()  ^
- [ ] char* get(index)
- [ ] void set(data, index)
- [ ] void alloc(data, size)

##### Error Handling:


### String 
##### IDEA 
Dynamic string have no base size limitation and we can expand it as long as we have enough memory.

##### How it works:

##### In this project:
Used for saving dynamic size names and path.

##### Fields:

##### Complexity:

##### Functions:
- [x] void init([none, initial, string {copy}])
- [x] void destroy()
- [x] char get(index)
- [x] void set(data, index)
- [x] void concat([string, char*])
- [x] int find(char*)
- [x] void erase(x, y) -- it removes in [x, y] with edges, circular indexes
- [x] char* get_ptr()

##### Error Handling:


---


## Tests


---


## Features
- [ ] User name
- [ ] ^ encouragement sign {path} $
- [ ] ^ cd
- [ ] ^ exit
- [ ] ^ execute form PATH: ```fork + exec*()```
- [ ] ^ Error Comuniact: When can't parsee command
- [ ] ^ help: Info + Features + Commands
- [ ] Data I/O
- [ ] History Controller
- [ ] Prefix Controller
- [ ] Data Controller
- [ ] Command Predictor
- [ ] Autocomplete with the most relevant
- [ ] Task Result
- [ ] Task Error Handler
- [ ] UI Error Handler
- [ ] coloring text for params, "", (), {}. [].
- [ ] arrows for history/autocomplete
- [ ] ^ two more commands
- [ ] cp
- [ ] Windows integration (Cross-Platform update)