# stracciacamicia

## About The Project
Search potentially infinite games of the "stracciacamicia" card game, the Italian variant of [beggar-my-neighbour](https://en.wikipedia.org/wiki/Beggar-my-neighbour) game.

### Prerequisites
You can build the project using Cmake. Hence you should install Cmake on your machine. For more information, refer to https://cmake.org/install/

### Installation
Installation instruction macOS and Linux distributions

```sh
git clone https://github.com/andrea321123/stracciacamicia
cd stracciacamicia
mkdir build
cd build
cmake ..
make
```

## Usage
To know information about this program, run

```sh
./bf --help
```
## Infinite games

The algorithm will search for potentially infinite games (games longer than 1000 turns). When such game is found, it will be added in the file "infinite_games.txt".
