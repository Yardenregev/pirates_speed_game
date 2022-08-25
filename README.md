# Pirates Speed Game

## Game Rules 📃
The players split into commander and captains,
the commander manages the game and the captains play the game.
Captains can't have the same name.

Each captain has a hand of pirate scum, that he wishes to rid the ship of.

The commander shouts a command to all the captains, and the captains each look 
for a pirate that can perform the command and send the identifier number, written above a selected pirate, to the commander.
The first captain to send a pirate that is able to perform the command is able to
get rid of the pirate.

The winning captain is the first captain to have no pirates on the ship.

## Known Bugs 🐛
If multiple messages are being sent instead of one by accident, the synchronization might mess up.
Messages cannot have spaces, if spaces are entered, each word will be sent in the next message.

## Depenedencies 📦
This game is compiled with g++

## How To Run 🚀
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

>   For example: "Moby Dick" "8080" "10.10.0.197"

5. When choosing 'Add Captain', run the captain executable in the captain computer.

```bash
./captain.out
```

6. Enter your name, port for the game to be played and commander computer ip address.
   The port and ip must be the same as entered in the commander computer.

>   For example: "Jack Sparrow" "8080" "10.10.0.197"

7. Choose 'Start Game' to start the game.

## Playing The Game 🎮

The game is played by minimum of two players, the commander and the captain.

All captains are showed which pirates they have and what command they can perform.

The commander first has to shout what command he wants executed.
After the command is shouted, the captain will be able to send a pirate index to the commander.

>   For example: commander: "Defend" captain: "1"

If the pirate is able to perform the command, the captain will be rid of the pirate.


###   Remember, First captain to get rid of all his pirates is the winner.


