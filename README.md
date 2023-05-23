# REST Web App

## Description

This application sends HTTP requests to a REST server and prints out the response. All the requests take the form of a
command. The commands are taken from STDIN. The server simulates an online library, where you can query information
about books and perform actions like adding or deleting books. It also provides an authentication/authorization mechanism.

## Usage

This application provides a prompt where the user can input commands and get the results. The commands are checked for
their correctness and then run by the client.

The commands may be categorized as:

### Authentification commands

The commands `login` and `register` both provide a prompt to input the *username* and the *password*, which are then encapsulated in the request's payload. The `logout` command requires that the user is first authenticated for it to execute successfully.

> **_Note:_** Both the *username* and the *password* shall not contain any spaces.

### Library access commands

`enter_library` is the first command you have to enter before you can execute any action related to the library. The
command `get_books` retrieves a list of the books available in the library (JSON format). The commands `get_book` and
`delete_book` both require an input *id* to retrieve or delete a book from the library. `add_book` command requires
a list of book attributes that can be intuitively parsed in the prompt.

> **_Note:_** The *id* or *page_number* should be whole, positive numbers, with no aditional characters (although
> trailing spaces do not affect the normal execution).

### The `exit` command

The `exit` command can be executed anytime.

> **_Note:_** Exiting the program does **not** automatically log out the user.

## Additional implementation details

The client provides a configuration file (`include/config.h`) where you can tweak the application's behavior. It also
provides a logging system that can be enabled by defining the `SETLOG` macro. The server IP address and port are
hardcoded in the configuration file.

To build and parse the request's JSON payload, the client uses the [nlohmann/json](https://github.com/nlohmann/json.git) library.

## Building

To build the client, run:

```bash
make
```

To clean binaries, run:

```bash
make clean-bin
```

To clean logs, run:

```bash
make clean-logs
```

To clean everything, run:

```bash
make clean
```

## Running

To run the client, simply run the command:

```bash
./client
```