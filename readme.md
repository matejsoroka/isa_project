# ISA PROJECT

## HTTP Dashboard

### How to build
In build folder is Makefile for build a binary and generate docs, simply run `make all` and Makefile will build `isaclient` and `isaserver` binary and generate documentation in `docs` folder (it is already generated in this zip).

### How to run

#### Server
After building run binary `isaserver` with port as argument `-p` for example

`./isaserver -p 8080`

#### Client
After building run binary `isaclient` with port as argument `-H` for host, host can be IP address of server or hostname of server. And `-p` for port, for example

`./isaclient -H 127.0.0.1 -p 80 <command>`

where command can be from supported commands below.

##### Supported commands and operations
`boards` - Get list of boards

`board add <name>` - Create new board
 
`board delete <name>` - Delete board

`board list <name>` - List board posts

`item add <name> <content>` - Add post to board

`item delete <name> <id>` - Delete board post by id

`item update <name> <id> <content>` - Edit post by id
