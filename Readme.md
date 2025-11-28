<div align=center>
  <h1>Microshell</h1>
</div>

## About
This is a **shell** built on **threads**, optimized for **parallel operations**, **data batching** and **concurrency between threads**.

It optimizes shell operations by **splitting** tasks into **threads**, **batching data** for faster access, and supporting **cross-platform** use.

It contains only **custom implementations** of **structures** and **algorithms** with no external libraries.

**Why it exists**:
* Typical shells work **line by line** what is slow.
* Originally created as a **university assignment**, but I wanted to make it more **optimized** and **ambitious**.
* Aiming for **cross-platform** compatibility.

**For who it is**:
* People who want to run many operations **simultaneously**.
* People who want fast **execution of plans** generated automatically.
* People who want a **faster** shell.
* People who want **easy-to-use** and **minimal** thread management.

**Main points**:
* **Cross-platform** shell.
* Fast **execution of plans**.
* Fast **data access**.
* Multiple plans running **simultaneously**.
* Easy **control** of **data access** between threads.


---


## Screenshots


---


## TOC
- [About](#about)
- [Screenshots](#screenshots)
- [TOC](#toc)
- [Installation](#installation)
- [Tests](#tests)
  - [Running Tests](#running-tests)
  - [Current Tests:](#current-tests)
- [Usage](#usage)
- [Diagram](#diagram)
- [Architecture Overview](#architecture-overview)
- [Components](#components)
  - [ProgramCodes](#programcodes)
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
- [ProgramCodes](#programcodes-1)
- [Structures](#structures)
  - [Vector](#vector)
  - [String](#string)
- [Error Handling](#error-handling-35)
- [Decision Decisions](#decision-decisions)
- [Concurrency](#concurrency)
- [Trade-offs](#trade-offs)
- [Future](#future)
- [Stability](#stability)
- [Strategic Parts](#strategic-parts)
- [Limitations](#limitations-2)
- [Prerequisites](#prerequisites)
- [Code Philosophy](#code-philosophy)
- [Features](#features)
- [To do:](#to-do)
- [Cat](#cat)



---


## Installation
1. **Download from github**
    ```bash
    git clone https://github.com/Daynlight/Microshell.git
    cd Microshell/
    ```
2. **Dev**
   1. **Build with cmake**
      ```bash
      mkdir -p build/
      cd build/
      cmake ..
      cmake --build .
      cd ..
      ```
   2. **Run Tests**
      ```bash
      ctest build/
      ```
   3. **Run Microshell**
      ```bash
      ./build/Microshell/Microshell
      ```
3. **For usage**
   1. **Install with cmake**
      ```bash
      mkdir build/
      cd build/
      cmake .. -DCMAKE_BUILD_TYPE=Release
      cmake --build .
      sudo cmake --install .
      ```


---


## Tests
### Running Tests
  ```bash
    cd build/
    ctest
  ```
### Current Tests:
- Unit Tests
  - Structures
    - Vector 
      - Init, Destroy
      - Resize, Reserve, Shrink, Alloc, Fit
      - Push, Pop
      - Erase, Clean
      - Set, Get
      - Copy
- Integration Tests
  - Structures
    - String []


---


## Usage


---


## Diagram
![Diagram](docs/Architecture.svg)


---


## Architecture Overview


---


<!-- # Phase 1 MVP -->
## Components
### ProgramCodes
##### Responsibility
  * storing program codes for pipeline errors checking.



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
##### Responsibility
##### Functions
##### Error Handling



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


## ProgramCodes


---


## Structures
### Vector
##### IDEA
Vector is dynamic array that allows storing dynamic data that can change with time We want it for unordered_map and string.

##### How it works:

##### In this project:

##### Fields:
* cap --- tells how much space we have left before resize
* size --- current vector size
* size_of_el --- size of single element
* data --- pointer to ```char*``` real data

##### Complexity:

##### Functions:
- [x] void init(size_of_el)
- [x] void destroy()
- [x] void resize()
- [x] void reserve(additional_cap)
- [x] void shrink()
- [x] void alloc(data, size)
- [x] void fit(size)
- [x] void push(data)
- [x] void pop(out_ptr)
- [x] void erase(x, y) -- it removes in [x, y] with edges, circular indexes
- [x] void clean()
- [x] void get(out_ptr, index)
- [x] void set(data, index)
- [x] void copy(src_ptr, dest_ptr)

##### Error Handling:

##### Limitations:

##### Usage:



### String 
##### IDEA 
Dynamic string have no base size limitation and we can expand it as long as we have enough memory.

##### How it works:
It creates vector of char. For operation we just adjust size and make operation. After ```erase``` it is shrink. When concat first we reserve space than we copy data.

##### In this project:
Used for saving dynamic size names and path.

##### Fields:
* vector --- vector that string is using.

##### Complexity:
| function         | complexity  |
|:----------------:|:-----------:|
| init             | $O(1)$      |
| init initial     | $O(n)$      |
| init string      | $O(n)$      |
| destroy          | $O(1)$      |
| get              | $O(1)$      |
| set              | $O(1)$      |
| concat           | $O(n)$      |
| concat string    | $O(n)$      |
| find             | $O(n^2)$    |
| erase            | $O(n)$      |
| get_ptr          | $O(1)$      |

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
- Functions returns ```ProgramCodes``` with minus values where it can.
- No error checking for ptr existence before first initialization.

##### Limitations:
- Every time we ```concat```, ```erase```, ```initialize``` we create new ptr and allocate memory what takes time.
- We can't detect in ```C``` if ptr is initialized. But after initialization and destroy we set ptr to ```NULL```. Good practice is to initialize after creation.

##### Usage:
  ```cpp
    printf("== Concat Example ==\n");

    struct string string;
    char initial[] = "Hello ";
    char initial2[] = "World";
    
    string_init_initial(&string, initial);

    string_concat(&string, initial2);

    printf("%s\n", string_get_ptr(&string));

    string_destroy(&string);
  ```
  [More Here](Examples/Structures/string.h)


---


## Error Handling
When Error occur we log it and return error value from ```ProgramCodes``` this allows us to track error path.


---


## Decision Decisions


---


## Concurrency


---


## Trade-offs


---


## Future


---


## Stability


---


## Strategic Parts


---


## Limitations


---


## Prerequisites
- **CMake** – to build the project  
- **Git** – to clone the repository  
- **C compiler** – for building Microshell  
- **C++23 compiler** – for building tests and examples  


---



## Code Philosophy
1. Strict and logical function placement
2. Consistency naming
3. Edge-cases
4. UnitTests, IntegrationTests, StressTests, RegressionTests
5. CI/CD - CodeQL, Ctests, Release Build
6. Everything included in code is described in docs
7. Performance Consideration
8. Error propagation handling
9. No static numbers every magic value in ```Setting.h```
10. Logging where possible
11. Asymptotic and Amortized Complexities
12. We tastes all structures and core modules
13. Benchmarking


---


## Features
- [ ] User name
- [ ] ^ encouragement sign {path} $
- [ ] ^ cd
- [ ] ^ exit
- [ ] ^ execute form PATH: ```fork + exec*()```
- [ ] ^ Error Comuniact: When can't parsee command
- [ ] ^ help: Info + Features + Commands
- [ ] ^ two more commands
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
- [ ] cp
- [ ] Windows integration (Cross-Platform update)
- [ ] | pipes or execution plan
- [ ] Run with params
- [ ] Run script
- [ ] Snippet for Microshell script 


---


## To do:
- [x] (String) - Shrink after erase and concat.
- [x] (String) - Find edge case for string and el sizes.
- [ ] (String) - Optimize Shrink concat.
- [ ] (String) - Change loops to memcpy.
- [ ] (String) - Edge cases.
- [ ] (String) - Optimization.
- [ ] (String) - Error codes.
- [ ] (String) - All examples
- [ ] (String) - Stress Tests
- [ ] (Vector) - Change loops to memcpy.
- [ ] (Vector) - Optimization.
- [ ] (Vector) - Error checking.
- [ ] (Vector) - Edge cases.
- [ ] (Vector) - All examples
- [ ] (Vector) - Stress Tests
- [ ] (Smart_PTR) - Create Structure and use in Vector.
- [ ] Separate to Phases.
- [ ] Fill docs.
- [x] Why it exists, for who it is etc.
- [ ] Core Idea
- [ ] Enhance looking part of readme.
- [ ] Github Setup Community Standards


---

## Cat
<img src="https://i.pinimg.com/736x/29/41/b0/2941b0a266c0fc1cb388429315b9ccf9.jpg">