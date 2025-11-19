# Microshell

## Architecture Overview


### Structures
- [ ] vector *
- [ ] string *
- [ ] path
- [ ] prefix array
- [ ] unordered_map *
- [ ] deque
- [ ] stack

#### vector
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


#### string 
##### IDEA 
Dynamic string with no size limitation We don't know path size and we need strings to dynamicly operate on them without it we waste a lot of memory and can it cause mem overflow
##### In this project:
Used for saving dynamic size names and path.
##### Functions:
- init
- destroy
- concat
- at
- find
- erase
- set
- get_ptr


#### unordered_map
##### IDEA We want a fast way to find the value from a kay. An unordered_map gives O(1) average lookup time, so it is fast to finding values from keys.
##### Functions:
- init
- destroy
- get
- set


#### prefix array
##### IDEA
##### Functions:


#### deque
##### IDEA
##### Functions:


#### stack 
##### IDEA
##### Functions:


#### path
##### IDEA 
Dynamic array of strings that contains folders and provide  whole path
##### Functions:




## TODO
### Structures
- [x] Use String
- [ ] Path Struct
- [ ] Dequeue Struct
- [ ] Stack Struct
- [ ] Prefix Array Struct
- [ ] Update program to use new structures

### MVP
- [x] Workflow for every system (Cross-Platform update)
- [ ] Architecture Overview logic part
- [ ] Input Handler
- [ ] Input Controller
- [ ] Command Composer
- [ ] Command Parser
- [ ] Command Runner
- [ ] Task Queue
- [ ] Task Controller
- [ ] Env Register
- [x] UI Colorer 
- [ ] UI Composer
- [ ] Ui Printer
- [ ] ```Ctrl + Z``` process exit or program

### Requirements
- [x] User name
- [x] ^ encouragement sign {path} $
- [ ] ^ cd
- [x] ^ exit
- [ ] ^ execute form PATH: ```fork + exec*()```
- [ ] ^ Error Comuniact: When can't parsee command
- [x] ^ help: Info + Features + Commands

### Features
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