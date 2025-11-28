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
* People who want fast **execution** of automatically generated plans.
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
- [Usage](#usage)
- [Core Idea](#core-idea)
- [Architecture](#architecture)
- [ProgramCodes](#programcodes)
- [Error Handling](#error-handling)
- [Architecture Decision](#architecture-decision)
- [Concurrency](#concurrency)
- [Trade-offs](#trade-offs)
- [Future](#future)
- [Stability](#stability)
- [Strategic Parts](#strategic-parts)
- [Limitations](#limitations)
- [Prerequisites](#prerequisites)
- [Code Philosophy](#code-philosophy)
- [Tests](#tests)
  - [Running Tests](#running-tests)
  - [Current Tests:](#current-tests)
- [Versions](#versions)
- [Tasks:](#tasks)
- [Cat](#cat)



---


## Installation
1. **Download from github**
    ```bash
    git clone https://github.com/Daynlight/Microshell.git
    cd Microshell/
    ```
2. **Development**
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


## Usage


---


## Core Idea


---

## Architecture
- [Architecture Phase1](docs/Architecture/Architecture.md)


---


## ProgramCodes


---


## Error Handling
When Error occur we log it and return error value from ```ProgramCodes``` this allows us to track error path.


---


## Architecture Decision


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
5. Examples for structures
6. CI/CD - CodeQL, Ctests, Release Build
7. Everything included in code is described in docs
8. Performance Consideration
9. Error propagation handling
10. No static numbers every magic value in ```Setting.h```
11. Logging where possible
12. Asymptotic and Amortized Complexities
13. We tastes all structures and core modules
14. Benchmarking


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
    <details>
      <summary>Vector</summary>

        - Init, Destroy
        - Resize, Reserve, Shrink, Alloc, Fit
        - Push, Pop
        - Erase, Clean
        - Set, Get
        - Copy
      </details>
- Integration Tests
  - Structures
    <details>
      <summary>String</summary>

    </details>


---


## Versions
<details>
  <summary>v1.0.0</summary>
</details>

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
</details>

---


## Tasks:
<details>
  <summary>Done</summary>

- [x] (String) - Shrink after erase and concat.
- [x] (String) - Find edge case for string and el sizes.
- [x] (Docs) Why it exists, for who it is etc.
- [x] (Docs) Move Architecture
</details>
<details>
  <summary>To do</summary>

- [ ] (String) - Optimize Shrink concat.
- [ ] (String) - Change loops to memcpy.
- [ ] (String) - Edge cases.
- [ ] (String) - Optimization.
- [ ] (String) - Error codes.
- [ ] (String) - All examples
- [ ] (String) - Stress Tests
- [ ] (String) - Amortized complexity
- [ ] (Vector) - Change loops to memcpy.
- [ ] (Vector) - Optimization.
- [ ] (Vector) - Error checking.
- [ ] (Vector) - Edge cases.
- [ ] (Vector) - All examples
- [ ] (Vector) - Stress Tests
- [ ] (Vector) - Amortized complexity
- [ ] (Smart_PTR) - Create Structure and use in Vector.
- [ ] (Docs) Separate to Phases.
- [ ] (Docs) Core Idea
- [ ] (Docs) Enhance looking part of readme.
- [ ] (Docs) Fill docs.
- [ ] (GitHub) Github Setup Community Standards
</details>

---

## Cat
<img src="https://i.pinimg.com/736x/29/41/b0/2941b0a266c0fc1cb388429315b9ccf9.jpg">