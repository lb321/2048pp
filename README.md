# 2048pp
The popular 2048 game written in c++ with some additional features. Hence the name 2048 plus plus...

## Raylib C++ Starter
This project was created with the [Raylib C++ Starter kit](https://github.com/CapsCollective/raylib-cpp-starter). Raylib C++ Starter kit is a template project that provides a simple starter template for the [raylib](https://github.com/raysan5/raylib) game tools library incorporating the [raylib-cpp](https://github.com/robloach/raylib-cpp) C++ bindings and using [Make](https://www.gnu.org/software/make/) for building. The starter kit can automatcially clone down raylib and the bindings, compile them, and setup the project for separate compilation using a static library.

## Getting Started

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