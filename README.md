# Concurrent News System

This project is a concurrent news system implemented in C++. It uses multiple threads to simulate producers, a dispatcher, co-editors, and a screen manager, with a scenario of news broadcasting. Different types of stories are produced and the system sorts them and displays them to the public. New stories are simulated by simple strings, displayed by the order of arrival.

## Getting Started

### Prerequisites

- C++11 or later
- A C++ compiler (e.g., g++, clang++)
- MinGW-w64 (optional, for building the project on Windows)
- CMake (optional, for building the project)

### Building the Project

#### Using MinGW-w64

To build the project using MinGW-w64, follow these steps:

1. Install MinGW-w64 from [MinGW-w64](https://sourceforge.net/projects/mingw-w64/).
2. Add the `bin` directory of your MinGW-w64 installation to the system PATH. This is usually located at `C:\Program Files\mingw-w64\x86_64-<version>\mingw64\bin`.
3. Open a terminal in your project directory and run the following command:

```sh
g++ -std=c++11 -o main main.cpp BoundedBuffer.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp
```

#### Using CMake

If you prefer to use CMake, create a CMakeLists.txt file and follow the standard CMake build process.

### Running the Program

To run the program, use the following command:

```sh
./main <input_file.txt>
```

Replace <input_file.txt> with the path to your input file.

### Input File Format

The input file should contain the following information:

- Producer ID
- Number of products
- Queue size

The last line should contain the buffer size for the co-editor queue.

Example

```plaintext
1
30
5

2
25
3    

3
16
30

17
```

### Project Structure

* `main.cpp`: The main entry point of the program.
* `BoundedBuffer.h` / `BoundedBuffer.cpp`: Implementation of the bounded buffer.
* `Producer.h` / `Producer.cpp`: Implementation of the producer.
* `Dispatcher.h` / `Dispatcher.cpp`: Implementation of the dispatcher.
* `CoEditor.h` / `CoEditor.cpp`: Implementation of the co-editor.
* `ScreenManager.h` / `ScreenManager.cpp`: Implementation of the screen manager.
