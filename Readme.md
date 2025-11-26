# Microshell
## About
This is small shell build on threads optimized for parallel operations and data batching. Main focus is to make it work for multiple operations at the same time. Contains only own implementations of structures no libs. Uses a lot of dynamic arrays.




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




## Structures
### Vector
##### IDEA
Vector is dynamic array that allows storing dynamic data that can change with time We want it for unordered_map and string.

##### Functions:
- init
- destroy
- reserve
- resize
- shrink ^
- fit    ^
- push
- pop
- erase
- clean  ^
- get
- set
- alloc


### String 
##### IDEA 
Dynamic string have no base size limitation and we can expand it as long as we have enough memory.

##### In this project:
Used for saving dynamic size names and path.

##### Functions:
- void init([none, initial, string {copy}])
- void destroy()
- char& at(index)
- void concat([string, char*])
- int find(el)
- void erase(x, y) -- it removes in [x, y] with edges, circular indexes
- char* get_ptr()




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