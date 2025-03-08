# Secret Of Mana

# Introduction
MSV: 24020142

Họ và tên: Trương Quang Hoành

A clone of Secret Of Mana using the SDL2 library, written in C++. Secret Of Mana is an action-rpg game, where you control the hero to defeat monsters.

# 1. How to start
Start by open game.exe file. A window will pop-up, press enter to start the game.

![alt text](https://github.com/user-attachments/assets/6f45f781-d32d-47d2-8fc1-923a3054a950)

# 2. Game mechanic
## 2.a Player
### Movement
Control the player using the W/A/S/D key.

![alt text](https://github.com/user-attachments/assets/5e578b8c-438d-4656-a8df-9817b3876db3)
![Image](https://github.com/user-attachments/assets/d72d270f-c92d-4140-b965-1284dac98305)

### Attack
Attack the enemies by pressing the J key.

![alt text](https://github.com/user-attachments/assets/4d8eb304-e1f4-438b-9266-e83603d8e938)

### Health
You are given 250 HP at the start of the game. Getting hit by enemies's attacks will cause your character to lose health.

![alt text](https://github.com/user-attachments/assets/ab9837ce-cf35-4825-b6a4-3212ec6ba692)

### Hurt
When getting hit by enemies's attacks, you will be knocked back and invulnerable for a few seconds.

![Image](https://github.com/user-attachments/assets/c7a56412-5619-4ca9-8f9a-11e704af0791)

### Die
When your health reaches zero, the game will ends and you will be brought back to the title screen.

![Image](https://github.com/user-attachments/assets/0813aa1d-bc51-49a4-93a3-b553c42fdc90)

## 2.b Enemies
Enemies will become aggressive when you walk into their aggro range. They can perform certain attacks depending on the type of enemy. When hurt, they will also be invulnerable for a few seconds.

### Pebbler
A high HP enemy, when it get aggro, it will emerge from the ground and spin to the player.

#### Emerge from the ground
![alt text](https://github.com/user-attachments/assets/e5317402-b21b-486e-a427-1d0aa760840c)

#### Idle
![alt text](https://github.com/user-attachments/assets/df5550e2-39ae-4086-b505-761040b1b0a9)

#### Spining
![alt text](https://github.com/user-attachments/assets/43f22268-f518-47d3-b06f-a3c5242f6027)

#### Hurt
![Image](https://github.com/user-attachments/assets/909833c4-dca0-4314-a9a2-7bbcd78be591)

### Kimono Bird
A low HP enemy but can cast powerful lightning bolt.

#### Idle
![Image](https://github.com/user-attachments/assets/9bd33f65-25f6-457a-a7c1-a1147facd663)

#### Cast lightning bolt
![alt text](https://github.com/user-attachments/assets/3e56b495-5626-4def-af92-1654c44649fe)

#### Hurt
![Image](https://github.com/user-attachments/assets/ce086f93-9015-4fbc-b974-930ae6d7a755)

### Water Thug
Lives by the water, can make annoying circle attacks.

#### Idle
![Image](https://github.com/user-attachments/assets/acf71fef-b3b1-4ac8-89b9-89233ca8ef01)

#### Circle attack
![alt text](https://github.com/user-attachments/assets/a4e58491-e512-409c-ba5f-4c2f5197b4de)

#### Stabbing
![Image](https://github.com/user-attachments/assets/790bab49-e6fc-438b-9662-cae360f3f937)

#### Hurt
![Image](https://github.com/user-attachments/assets/0eab35ab-87ba-4bf5-a05a-6e675f697b1d)

## 2.c Map
The game consists of 5 maps, with gates connecting each other. Red boxes indicate location of enemies. When the player reachs the final gates in the last map, the games will ends and you will be brought back to the title screen.

![Image](https://github.com/user-attachments/assets/8d1f2b52-07cb-4295-99d4-377ca3debc4e)
![Image](https://github.com/user-attachments/assets/6f551eaa-2fe4-4b2c-9ade-6733d5d9e112)
![Image](https://github.com/user-attachments/assets/f9f2a430-556b-4018-b245-388cc49cc60e)
![Image](https://github.com/user-attachments/assets/28e1503c-9da0-43cd-96ce-8affe96518c0)
![Image](https://github.com/user-attachments/assets/68f148d2-edfc-45f3-b79a-61eb4bf4ac8d)

# 3. References
Sprites sources:

https://www.spriters-resource.com/snes/secretofmana/

Sound sources: 

https://www.sounds-resource.com/ds_dsi/pokemondiamondpearlandplatinum/

https://www.sounds-resource.com/snes/finalfantasy6/

https://downloads.khinsider.com/game-soundtracks/album/secret-of-mana-1993-snes

Tutorial:

https://www.youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS

https://lazyfoo.net/tutorials/SDL/index.php



