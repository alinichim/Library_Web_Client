# REST Web App

## Description

This application sends HTTP requests to a REST server and prints out the response. All the requests take the form of a
command. The commands are taken from STDIN. The server simulates an online library, where you can query information
about books and perform actions like deleting books. It also provides an authentication/authorization mechanism.

## Usage

To use this applica

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