# Microshell
## About
This is small shell build on threads optimized for parallel operations




## Diagram
![Diagram](docs/Architecture.svg)





## Components
### Error Codes
##### Responsibility
  * storing error codes for pipeline errors.

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
#### Processing Diff Buffer
#### Command Diff Buffer
#### Env Var

### Helpers
#### History
#### Backup System
#### Prefix Array
#### Memory Updater
#### Update Files
#### Data I/O

### Input Layer
#### Get Input
#### Input Action (Strategy)
#### Check Command Correctness
#### Add to Processing Queue
#### Predict Command
#### Prefix Controller
#### History Controller
#### Auto Complete

### Processing Layer
#### Command Thread Controller
#### Parse Command
#### Run Process
#### Result Controller

### Process Thread
#### Process Start
#### Process Run
#### Check Result

### Own Commands
#### cd
#### exit
#### help

### Output Layer
#### Get output
#### Move Cursor
#### Print in Terminal




## Requirements
- [ ] User name
- [ ] ^ encouragement sign {path} $
- [ ] ^ cd
- [ ] ^ exit
- [ ] ^ execute form PATH: ```fork + exec*()```
- [ ] ^ Error Comuniact: When can't parsee command
- [ ] ^ help: Info + Features + Commands




## Features
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