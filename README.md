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

## Depenedencies 📦
This game is compiled with g++

## How To Run 🚀
### Run Commander
1. in the 'pirates_speed_game' folder, run the following command in the commander computer:

```bash
make commander
```

2. Run the commander executable in the commander computer.

```bash
./commander.out
```

3. Select the menu option to set up the game, then select the network you would like to play, your IP should be assigned automatically

4. Enter your name port for the game to be played.

>   For example: "Moby Dick"

5. Enter TCP port for the game to be played
   
>   For example: "8080"

6. Once this is done you can select the option to add a captain

### Run Captain

1. in the 'pirates_speed_game' folder, run the following command in the captain computer:

```bash
make captain
```
2. Run the captain executable in the captain computer.

```bash
./captain.out
```

3. Enter your captain name

>   For example: "Jack Sparrow"

4. Enter the port you chose for the game when setting up the commander

>   For example "8080"

5. Enter the commander's computer ip address (displayed on the commander terminal).

>   For example "172.12.864.151"

Choose 'Start Game' in the commander's computer to start the game.

## Playing The Game 🎮

The game is played by minimum of two players, one commander and one captain.

All captains are showed which pirates they have and what command they can perform.

The commander first has to shout what command he wants executed.
After the command is shouted, the captain will be able to send a pirate index to the commander.

>   For example: commander: "Defend" captain: "1"

If the pirate is able to perform the command, the captain will be rid of the pirate.


###   Remember, First captain to get rid of all his pirates is the winner.


