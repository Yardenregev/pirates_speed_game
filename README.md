# Pirates Speed Game

## Game Rules
The players split into commander and captain,
the commander manages the game and the captain plays the game.

Each captain has a hand of pirate scum, that he wishes to rid the ship of.

The commander shouts a command to all the captains, and the captains each look 
for a pirate that can perform the command and send the pirate to the commander.
The first captain to send a pirate that is able to perform the command is able to
get rid of the pirate.

The winning captain is the first captain to have no pirates on the ship.

## Game Play
The game is played by minimum of two players, the commander and the captain.

## Known Bugs
When multiple messages are send before receiving, the game will read all of them
as one message. Can and will be fixed by some seperator between the messages.

## Depenedencies
This game is compiled with g++

## How To Play
1. in the 'pirates_speed_game' folder, run the following command in the commander computer:

```bash
make commander
```

2. in the 'pirates_speed_game' folder, run the following command in the captain computer:

```bash
make captain
```

3. Run the commander executable in the commander computer.

```bash
./commander.out
```

4. Enter your name, port for the game to be played and commander computer ip address.

    For example: "Moby Dick" "8080" "10.10.0.197"

5. Run the captain executable in the captain computer.

```bash
./captain.out
```

6. Enter your name, port for the game to be played and commander computer ip address.
   The port and ip must be the same as entered in the commander computer.

    For example: "Jack Sparrow" "8080" "10.10.0.197"

7. The game will start.
