<div align=center>
  <h1>MVP</h1>
</div>

## TOC
- [TOC](#toc)
- [Diagram](#diagram)
- [Components](#components)
  - [ProgramCodes](#programcodes)
  - [Log System (SINGLETON)](#log-system-singleton)
  - [Microshell](#microshell)
  - [Shared Memory](#shared-memory)
  - [Input Layer](#input-layer)
  - [Processing Layer](#processing-layer)
  - [Output Layer](#output-layer)
  - [Commands](#commands)
- [ProgramCodes](#programcodes-1)
- [New Bash Dialect](#new-bash-dialect)
- [Terminal layout](#terminal-layout)
- [Structures](#structures)
  - [Vector](#vector)
  - [String](#string)
- [Features in this part](#features-in-this-part)



## Diagram
![Diagram](diagram/Architecture.svg)


---


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



### Microshell
##### Responsibility
  * Start program
  * Run Threads (Input, Processing, Output, Memory Updater)
##### Functions
  * initialize
  * run
  * destroy
##### Error Handling
  - return deeper level error and exit
  - if initialization fails return ProgramCodesInitializationERROR;




### Shared Memory
#### Processing Priority Queue
##### Responsibility
  * Storing queue of Execution Plans that are ran from input layer.
##### Functions
  * pop();
  * push(priority, execution_plan_name);
  * clear();
  * setBlock();
  * releaseBlock();
##### Structure
  * Priority Heap.

#### Execution Plan
##### Responsibility
  * storing execution plans created via input layer.
##### Functions
  * get(execution_plan_name);
  * set(execution_plan_name, execution_plan);
  * remove(execution_plan_name);
##### Structure
  * unordered_map<string, string>;

#### Input Draw Data
##### Responsibility
  * Storing input changes for printing in terminal whole lines.
##### Functions
  * getChanges();
  * addChange(id, whole_line);
  * setBlock();
  * releaseBlock();
##### Structure
  * vector<string> - size of window height.

#### Env Var
##### Responsibility
  * Storing microshell variables.
##### Functions
  * getVariable(var_name)l
  * setVariable(var_name, value);
  * setBlock();
  * releaseBlock();
##### Structure
  * unordered_map<string, string>;




### Input Layer
#### Get Input
##### Responsibility
  * Getting and controlling user I/O.
  * No blocking input.
  * Saving Changes.
  * Operate on special chars.
##### Functions
  * getChar();
  * wait();
  * SwitchTab(); - Execution Plan Editor, Command Line
##### Error Handling
  * If error print error and skip.

#### Execution Plan Editor
##### Responsibility
  * editing Plans.
  * saving Plans.
  * list of plans.
  * chose plan to edit.
  * add plan to processing queue.
##### Functions
  * cursorMove();
  * editFile();
  * listPlans();
  * savePlan();
  * chosePlan();
  * abortPlan();
##### Error Handling
  * If error print error and skip.

#### Command Line
##### Responsibility
  * execution commands
  * running plans
##### Functions
  * editCommand();
  * runCommand();
  * runPlan();
  * abortPlan();
  * abortCommand();
##### Error Handling
  * If error print error and skip.

#### Add to Processing Queue
##### Responsibility
  * Saving new process's
  * Adding to queue
  * Blocking queue
  * Stopping commands and plans
##### Functions
  * addToQueue();
  * abortTask();
##### Error Handling
  * If error print error and abort.



### Processing Layer
#### Processing Controller
##### Responsibility
##### Functions
##### Error Handling

#### Command Thread Controller
##### Responsibility
##### Functions
##### Error Handling

#### Process Deltas
##### Responsibility
##### Functions
##### Error Handling

#### Plan Executor
##### Responsibility
##### Functions
##### Error Handling

#### Result Validator
##### Responsibility
##### Functions
##### Error Handling



### Output Layer
#### Compose Terminal
##### Responsibility
##### Functions
##### Error Handling

#### Draw in Terminal
##### Responsibility
##### Functions
##### Error Handling



### Commands
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

#### others
##### Responsibility
##### Functions
##### Error Handling


---


## ProgramCodes
  * ProgramCodesInitializationERROR; 


---


## New Bash Dialect


---


## Terminal layout
```
----------------------------------------------
|         Plan Editor          |    Logs     |
|                              |             |  
|                              |             |  
|                              |             |  
|------------------------------|             |  
|            helper            |             |
----------------------------------------------
|                Command Line                |  
----------------------------------------------
```
* Color for current chosen tab
* Red for errors in log etc.


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
  [Here](../../../Examples/Structures/string.h)



## Features in this part

<details>
  <summary>Planned Features</summary>

- [ ] User name
- [ ] ^ encouragement sign {path} $
- [ ] ^ cd
- [ ] ^ exit
- [ ] ^ execute form PATH: ```fork + exec*()```
- [ ] ^ Error Comuniact: When can't parsee command
- [ ] ^ help: Info + Features + Commands
- [ ] ^ two more commands
- [ ] execution plan
</details>