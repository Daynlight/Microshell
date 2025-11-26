<div align=center>
  <h1>Microshell</h1>
</div>

## About
This is small shell build on threads optimized for parallel operations and data batching. Main focus is to make it work for multiple operations at the same time. Contains only own implementations of structures no libs. Uses a lot of dynamic arrays.


---


## TOC
- [About](#about)
- [TOC](#toc)
- [Installation](#installation)
- [Usage](#usage)
- [Screenshots](#screenshots)
- [Diagram](#diagram)
- [Components](#components)
  - [Error Codes](#error-codes)
      - [Responsibility](#responsibility)
  - [Log System (SINGLETON)](#log-system-singleton)
      - [Responsibility](#responsibility-1)
      - [Functions](#functions)
  - [Microshell Initialize](#microshell-initialize)
      - [Responsibility](#responsibility-2)
      - [Functions](#functions-1)
      - [Error Handling](#error-handling)
  - [Microshell Destroy](#microshell-destroy)
  - [Shared Memory](#shared-memory)
    - [Processing Priority Queue](#processing-priority-queue)
      - [Responsibility](#responsibility-3)
      - [Functions](#functions-2)
      - [Error Handling](#error-handling-1)
    - [Processing Diff Buffer](#processing-diff-buffer)
      - [Responsibility](#responsibility-4)
      - [Functions](#functions-3)
      - [Error Handling](#error-handling-2)
    - [Command Diff Buffer](#command-diff-buffer)
      - [Responsibility](#responsibility-5)
      - [Functions](#functions-4)
      - [Error Handling](#error-handling-3)
    - [Env Var](#env-var)
      - [Responsibility](#responsibility-6)
      - [Functions](#functions-5)
      - [Error Handling](#error-handling-4)
  - [Helpers](#helpers)
    - [History](#history)
      - [Responsibility](#responsibility-7)
      - [Functions](#functions-6)
      - [Error Handling](#error-handling-5)
    - [Backup System](#backup-system)
      - [Responsibility](#responsibility-8)
      - [Functions](#functions-7)
      - [Error Handling](#error-handling-6)
    - [Prefix Array](#prefix-array)
      - [Responsibility](#responsibility-9)
      - [Functions](#functions-8)
      - [Error Handling](#error-handling-7)
    - [Memory Updater](#memory-updater)
      - [Responsibility](#responsibility-10)
      - [Functions](#functions-9)
      - [Error Handling](#error-handling-8)
    - [Update Files](#update-files)
      - [Responsibility](#responsibility-11)
      - [Functions](#functions-10)
      - [Error Handling](#error-handling-9)
    - [Data I/O](#data-io)
      - [Responsibility](#responsibility-12)
      - [Functions](#functions-11)
      - [Error Handling](#error-handling-10)
  - [Input Layer](#input-layer)
    - [Get Input](#get-input)
      - [Responsibility](#responsibility-13)
      - [Functions](#functions-12)
      - [Error Handling](#error-handling-11)
    - [Input Action (Strategy)](#input-action-strategy)
      - [Responsibility](#responsibility-14)
      - [Functions](#functions-13)
      - [Error Handling](#error-handling-12)
    - [Check Command Correctness](#check-command-correctness)
      - [Responsibility](#responsibility-15)
      - [Functions](#functions-14)
      - [Error Handling](#error-handling-13)
    - [Add to Processing Queue](#add-to-processing-queue)
      - [Responsibility](#responsibility-16)
      - [Functions](#functions-15)
      - [Error Handling](#error-handling-14)
    - [Predict Command](#predict-command)
      - [Responsibility](#responsibility-17)
      - [Functions](#functions-16)
      - [Error Handling](#error-handling-15)
    - [Prefix Controller](#prefix-controller)
      - [Responsibility](#responsibility-18)
      - [Functions](#functions-17)
      - [Error Handling](#error-handling-16)
    - [History Controller](#history-controller)
      - [Responsibility](#responsibility-19)
      - [Functions](#functions-18)
      - [Error Handling](#error-handling-17)
    - [Auto Complete](#auto-complete)
      - [Responsibility](#responsibility-20)
      - [Functions](#functions-19)
      - [Error Handling](#error-handling-18)
  - [Processing Layer](#processing-layer)
    - [Command Thread Controller](#command-thread-controller)
      - [Responsibility](#responsibility-21)
      - [Functions](#functions-20)
      - [Error Handling](#error-handling-19)
    - [Parse Command](#parse-command)
      - [Responsibility](#responsibility-22)
      - [Functions](#functions-21)
      - [Error Handling](#error-handling-20)
    - [Run Process](#run-process)
      - [Responsibility](#responsibility-23)
      - [Functions](#functions-22)
      - [Error Handling](#error-handling-21)
    - [Result Controller](#result-controller)
      - [Responsibility](#responsibility-24)
      - [Functions](#functions-23)
      - [Error Handling](#error-handling-22)
  - [Process Thread](#process-thread)
    - [Process Start](#process-start)
      - [Responsibility](#responsibility-25)
      - [Functions](#functions-24)
      - [Error Handling](#error-handling-23)
    - [Process Run](#process-run)
      - [Responsibility](#responsibility-26)
      - [Functions](#functions-25)
      - [Error Handling](#error-handling-24)
    - [Check Result](#check-result)
      - [Responsibility](#responsibility-27)
      - [Functions](#functions-26)
      - [Error Handling](#error-handling-25)
  - [Own Commands](#own-commands)
    - [cd](#cd)
      - [Responsibility](#responsibility-28)
      - [Functions](#functions-27)
      - [Error Handling](#error-handling-26)
    - [exit](#exit)
      - [Responsibility](#responsibility-29)
      - [Functions](#functions-28)
      - [Error Handling](#error-handling-27)
    - [help](#help)
      - [Responsibility](#responsibility-30)
      - [Functions](#functions-29)
      - [Error Handling](#error-handling-28)
  - [Output Layer](#output-layer)
    - [Get output](#get-output)
      - [Responsibility](#responsibility-31)
      - [Functions](#functions-30)
      - [Error Handling](#error-handling-29)
    - [Move Cursor](#move-cursor)
      - [Responsibility](#responsibility-32)
      - [Functions](#functions-31)
      - [Error Handling](#error-handling-30)
    - [Print in Terminal](#print-in-terminal)
      - [Responsibility](#responsibility-33)
      - [Functions](#functions-32)
      - [Error Handling](#error-handling-31)
- [Error Handling](#error-handling-32)
- [Structures](#structures)
  - [Vector](#vector)
      - [IDEA](#idea)
      - [How it works:](#how-it-works)
      - [In this project:](#in-this-project)
      - [Fields:](#fields)
      - [Complexity:](#complexity)
      - [Functions:](#functions-33)
      - [Error Handling:](#error-handling-33)
  - [String](#string)
      - [IDEA](#idea-1)
      - [How it works:](#how-it-works-1)
      - [In this project:](#in-this-project-1)
      - [Fields:](#fields-1)
      - [Complexity:](#complexity-1)
      - [Functions:](#functions-34)
      - [Error Handling:](#error-handling-34)
- [Tests](#tests)
- [Features](#features)


---


## Installation


---


## Usage


---


## Screenshots


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