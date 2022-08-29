# 2048pp
The popular 2048 game written in c++ with some additional features. Hence the name 2048 plus plus...

## Raylib C++ Starter
This project was created with the [Raylib C++ Starter kit](https://github.com/CapsCollective/raylib-cpp-starter). Raylib C++ Starter kit is a template project that provides a simple starter template for the [raylib](https://github.com/raysan5/raylib) game tools library incorporating the [raylib-cpp](https://github.com/robloach/raylib-cpp) C++ bindings and using [Make](https://www.gnu.org/software/make/) for building. The starter kit can automatcially clone down raylib and the bindings, compile them, and setup the project for separate compilation using a static library.

## Development with docker and vscode
You will need to have a XServer installed on your host machine.

To work inside the docker container with VSCode install the following extensions:
 - `ms-vscode-remote.remote-containers` (to work inside the docker container)
 - `ms-vscode-remote.remote-ssh` (to work inside the docker container)
 - `spadin.remote-x11-ssh` (to display the window)

In VS Code, press `Ctrl + Shift + P` to bring up the task list, then select "Remote Containers: Reopen in Container...",

Make sure these extensions are installed inside the container: 
 - `spadin.remote-x11` (to display the window)
 - `llvm-vs-code-extensions.vscode-clangd` (for code completion)

 ### First time setup
 1. Run the following command inside the docker container terminal:
 ```console
 > make setup
 ```
 This will clone in the lastest C++ bindings and targeted version of raylib, copy across any relevant header files into `/includes`, and build a static library file from them, placing it in `/lib`.
 
2. Execute the `clangd: Restart language server` VSCode task. This will update the language server so it will recognize the new libaries

 ### Building and running the project
You can run the code inside the docker container with the VSCode task 'Run Build Task'. (`CTRL + SHIFT + B`)

Or you can use the ```make``` or ```make CXX=clang++``` command in the terminal.

### Reconnect Display
If you get an error that the window cannot be created, execute the 'Remote X11: Reconnect Display' VSCode command and restart the terminal.


## Getting Started On Your Local Machine

### Installing Dependencies

Before building the project, you will need to install all relevant dependencies for your platform so that the project has access to all the tools required, and raylib can compile and link correctly. You can find intructions for installing dependencies on macOS, Linux, and Windows in the [docs file on installing dependencies](docs/InstallingDependencies.md).

### Building the Project
Once you have cloned this repository and installed dependencies, building the project is as simple as running these two commands in its root directory:

#### macOS & Linux
```console
$ make setup
$ make
```

#### Windows
```console
> mingw32-make setup
> mingw32-make
```

The first command will clone in the lastest C++ bindings and targeted version of raylib, copy across any relevant header files into `/includes`, and build a static library file from them, placing it in `/lib`. The second command then compiles, runs and cleans up your project using the source code in `/src/main.cpp`.

*If a window pops up, congratulations, you've successfully built the project and you can now start programming your game!*


### Making Use of Separate Compilation
When building compiled applications from scratch, *each* source file needs to be compiled into an object file in order for them all to be linked together as a full program. This can become rather time-consuming and inefficient as your codebase expands to use tens or even hundreds of files that recompile each time you build. Fortunately, with a few clever rules in our [`Makefile`](Makefile), we can be sure to only have to recompile files affected by our changes.

By using the following Make commands instead of the default target, we can skip the cleanup step, and only recompile files that changed:

#### macOS & Linux

```console
$ make bin/app; make execute
```

#### Windows

```console
> mingw32-make bin/app && mingw32-make execute
```

Using this method can save you a huge amount of time compiling *(in reality, just a few seconds)* each time you make a small change to your code! If you want to know more about how it works, you should have a read through [the docs entry explaining the Makefile](docs/MakefileExplanation.md).

While separate compilation works quite well in most scenarios, it's not magic, and there are a few caveats to take note of here:

1. Changing `.h` files will often result in longer compile times by causing all files that include them to recompile
2. Constant changes to files included by many others in your program (like a base-class) will also cause all of those dependent to recompile
3. Including widely-scoped files (like the whole of `raylib-cpp.hpp`) will add all of its own includes as dependent and increase the build time
4. Placing includes in `.h` files instead of forward-declarations will also increase recursive includes and therefore the build time

### Passing Args to the Executable
For working with some projects, you may want to pass arguments to the program once it's been built. This can be achieved by assigning values to the `ARGS` flag in the Makefile like below:

#### macOS & Linux

```console
$ make ARGS="--somearg"
```

#### Windows

```console
> mingw32-make ARGS="--somearg"
```

### Specifying Custom Macro Definitions
You may also want to pass in your own macro definitions for certain configurations (such as setting log levels). You can pass in your definitions using `CXXFLAGS`:

#### macOS & Linux

```console
$ make CXXFLAGS=-DMY_MACRO=1
```

#### Windows

```console
> mingw32-make CXXFLAGS=-DMY_MACRO=1
```

### Specifying a Non-Default Compiler
If you want to use a compiler for your platform that isn't the default for your system (or potentially you would like to explicitly state it), you can make use of the system-implicit `CXX` variable like so:

#### macOS & Linux

```console
$ make CXX=g++
```

#### Windows

```console
> mingw32-make CXX=g++
```