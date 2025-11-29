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

**Innovations**:
* Synchronized batch processing across threads.
* Thread-block execution.
* Storing only changes.

---


## Screenshots
<!-- Will be added -->


---


## TOC
- [About](#about)
- [Screenshots](#screenshots)
- [TOC](#toc)
- [Installation](#installation)
- [Usage](#usage)
- [Core Idea](#core-idea)
- [New Bash Dialect](#new-bash-dialect)
- [Architecture](#architecture)
- [ProgramCodes](#programcodes)
- [Error Handling](#error-handling)
- [Architecture Decision](#architecture-decision)
- [Concurrency](#concurrency)
- [Trade-offs](#trade-offs)
- [Stability](#stability)
- [Strategic Parts](#strategic-parts)
- [Limitations](#limitations)
- [Future](#future)
- [Prerequisites](#prerequisites)
- [Code Philosophy](#code-philosophy)
- [Tests](#tests)
  - [Running Tests](#running-tests)
  - [Current Tests:](#current-tests)
- [Versions Supports and Features](#versions-supports-and-features)
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
      ctest --test-dir ./build/
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
      cd ..
      ```


---


## Usage
<!-- Will be added -->


---


## Core Idea
Core idea for **parallelism** is to make new **bash dialect**. Dialect will specify **block of executions**. Each **inside block** work **line by line**. **Blocks** work in **parallel**. We can specify **blocks dependency**. Which block have to **wait** for other. What data it require **files**, **env variables**. 

Each block stores **changes** in **files**, **env variables** and are **passed** to another **blocks** that are **dependant** on it. No data are saved **directly** back after block ends and everything is **synced** after **whole program ends** with changes.

If we can predict **env variables** for example via **cd** we **bake** it in **execution plan**. This saved **variables** allows us to **skip waiting** for thread end. Because we can just **start running** on this **baked** ones that never changes.

Of course **all changes** are **strictly isolated** and nothing is **changed in files** before program **successfully ends**. If we use **too much memory** we save **not often** used **changes** in ```~/.microshell/temp/<pid>```.

For now each **block**, **dependency between them**, what **files**, **env variables**, **baked variables** are specified by **programmers**. But in **future** it will be **detected** and **created automatic**. It will **analyze scripts** and create **execution plans**. Of course **programmers** must **approve each execution plan**.

Each **command** that users **create** are **saved** in ```~/.microshell/plans/<name>``` and ```~/.microshell/plans/raw/<name>```. They can be **edited**, **reused**, **removed**.

Data are **loaded with batches**. First **n small batches** are **merged** into one **mid size batch** in **memory**. Than each **process** is runs on **this data**. If **two** or **more** threads uses one **file** we operate on them in **execution order**. Next **process** in **execution order** uses **changes** from **previous threads**. **Threads** operate on **specific parts of blocks** that means: **thread 1** first **thread** operate on **block k**, **thread 2** operate on **batch k - 1** etc. **Sequences of read** are **consider** in this as **one thread** and **every write** separates it. **Threads** are in **sync** with **each other**. Also **first** thread can run **as fast as can** second only need to **wait on first** etc. Also **TW3** can run before **TR2** becouse it doesn't change data that **TW2** uses etc for others and **TRs** dont need to work in sync that mean **TR4** can run before **TR2** becouse it is not dependant on **TR2**. Whole idea **makes it** a bit **slower** but **keep data consistency**. **Changes** are **isolated not directly saved to file**. After **program** end it is **commit** to file.

**Cross-platform** is **organized** via **interfaces** we create one **interface** that specify most **important operations** for **system dependant operations**. And each **platform creates** his **inherence class** this allows easy **scalability**.


---


## New Bash Dialect


---


## Architecture
- [Phase 1](docs/Architecture/Architecture.md)


---


## ProgramCodes
<!-- Will be added -->


---


## Error Handling
When an **error** occurs, we **log it** and **return an error** value from `ProgramCodes`. This allows us to track the **error path** and see what went wrong during execution.

We store only **changes** that **minimize memory usage** and provides **isolation**.

Only if program ends **successfully** than we commit **changes** to files.

If an **error occurs**, we first try to **resolve it automatically**. If all attempts **fail**, we stop with an error and don't commit changes.

We also save **logs** to `~/.microshell.log`, keeping the last **8000 lines**.


---


## Architecture Decision


---


## Concurrency


---


## Trade-offs


---


## Stability


---


## Strategic Parts


---


## Limitations


---


## Future


---



## Prerequisites
- **CMake** – to build the project.
- **Git** – to clone the repository.
- **C compiler** – for building Microshell.
- **C++17 compiler** – for building tests and examples.


---



## Code Philosophy
1. **Strict and logical placement** of functions and methods.
2. **Consistent naming** conventions across the codebase.
3. Comprehensive **UnitTests**, **IntegrationTests**, **StressTests**, and **RegressionTests**.
4. Thorough **testing** of all **structures** and **core modules**.
5. Provide **examples** for key data structures.
6. **CI/CD integration**: CodeQL, CTests, and Release Build automation.
7. Ensure **documentation** covers all implemented code.
8. Prioritize **performance considerations** in algorithms and data structures.
9. Track **asymptotic and amortized complexities** where relevant.
10. **Benchmarking** whenever possible.
11. Handle **edge cases** rigorously.
12. **Error handling** and **error propagation** considered in all modules.
13. Avoid **magic numbers**; store all constants in `Setting.h`.
14. Implement **logging** for **testability** and debugging.
15. Support **verbose logging mode** for deeper inspection.



---


## Tests
### Running Tests
  ```bash
    ctest --test-dir ./build/
  ```
### Current Tests:
- Unit Tests
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
  <details>
    <summary>String</summary>

    - init, Destroy
    - Concat
    - Get, Set, Get pointer
    - Find, Erase
  </details>


---


## Versions Supports and Features
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
- [ ] load ~/.microshellrc
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
- [x] (Docs) - Why it exists, for who it is etc.
- [x] (Docs) - Move Architecture
- [x] (Docs) - About section
- [x] (Docs) - Installation section
- [x] (Docs) - Core Idea section
- [x] (Docs) - Error handling section
- [x] (Docs) - Prerequisites section
- [x] (Docs) - Code philosophy section
- [x] (Docs) - Tests section
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
- [ ] (String) - Code Philosophy
- [ ] (Vector) - Change loops to memcpy.
- [ ] (Vector) - Optimization.
- [ ] (Vector) - Error checking.
- [ ] (Vector) - Edge cases.
- [ ] (Vector) - All examples
- [ ] (Vector) - Stress Tests
- [ ] (Vector) - Amortized complexity
- [ ] (Vector) - Code Philosophy
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
