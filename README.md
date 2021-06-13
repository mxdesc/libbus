# Bus Library
This project was done in C++ ( following the C++17 standard).

## Table of contents
* [Presentation](#presentation)
* [How to run](#how-to-run)
* [Features](#features)
*  [Credits](#credits)

## Presentation

This is a library that allows you to send some data from sources to some clients.
Source only have to send the message one time to a bus (by an entity) and then the bus will simply distribute it to client that are subscribed to this source.

## How to run
We will see how to use and test the library step by step.
### Clone the project
First, you will need to clone the project :
```
$ git clone git@github.com:mxdesc/libbus_project.git
$ cd libbus_project
$ ls
Makefile  README.md  src  tests
```

### Compile
You can use the provided Makefile.
```
$ make main
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/  -c -o src/main.o src/main.cc
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/   src/main.o  -o main
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/  -c -o tests/unary_tests.o tests/unary_tests.cc
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/   tests/unary_tests.o -lcriterion -o unary_tests
```
You should get a binary called **main**.
### Run Main Tests
This will excecute the main and performs some operation with the library to make sure that it works well.
Here is preview of what it will print.
```
$./main
Registering Source 1...Done !
Subscribing Client A and Client B to Source 1...Done !
Client A is subscribed to Source 1.
Client B is subscribed to Source 1.
... 
```
 ### Run Testsuite
 You can use the **check** rule of the given Makefile to produce the **unary_tests** binary and run it :
  ```
 $ make check
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/  -c -o tests/unary_tests.o tests/unary_tests.cc
g++ -Wall -Wextra -Werror -pedantic -std=c++17 -Isrc/   tests/unary_tests.o -lcriterion -o unary_tests
./unary_tests
[====] Synthesis: Tested: 10 | Passing: 10 | Failing: 0 | Crashing: 0 
```

## Features
By instanciating a Bus object, you can then call these functions:
 - **void register_source(std::string sourcename)**: register a new source as "sourcename" in the bus.
 - **void unregister_source(std::string sourcename, bool alert = false)**: unregister the source "sourcename" from the bus and alert every client subscribed to the source if the alert parameter is set to true.
 - **template <typename DerivedClient> void subscribe(DerivedCLient& client, std::string sourcename)**: subscribe a client to the given sourcename.
 - **template <typename DerivedClient> void unsubscribe(DerivedClient& client, std::string sourcename)**: unsubscribe the client from the source "sourcename".
 - **template <typename DerivedClient> bool is_sub(DerivedClient& client, std::string sourcename)**: return true if the given client parameter is subscribed to the source "sourcename", false otherwise. 
 - **bool is_registered(std::string sourcename)**: return true if a source named "sourcename" is registered in the bus, false otherwise.
 - **void pretty_print()**: function to display the different sources registered in the bus.

## Credits
Entirely produced by Maxime Descouts.

<maxime.descouts@epita.fr> - Ing1 - Promo 2023 EPITA.
