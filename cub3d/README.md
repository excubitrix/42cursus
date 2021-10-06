# :large_orange_diamond: cub3d &ensp; [![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/floogman/cub3d)](https://github.com/JaeSeoKim/badge42)

The aim of this project is to make a dynamic view inside a maze using ray-casting.

## :small_orange_diamond: Instructions

Run `make` to compile a game equipped with only the mandatory features and `make bonus` for one with all features.

## :small_orange_diamond: Controls

Basic controls:
- Use `[w][a][s][d]` to move around the maze,
- `[<][>]` to rotate the point of view,
- and `[esc]` to exit.

Bonus controls:
- Use `[w][a][s][d]` to move around the maze,
- the `arrow keys` or the `mouse` to rotate the point of view,
- `[space]` to jump,
- `[shift]` to crouch,
- `[e]` to interact with objects,
- `[1][2][3][4]` to interact with objects in your inventory.
- and `[esc]` to exit.

## :small_orange_diamond: Map Symbols

Symbol | Basic Map | Bonus Map
:-----:|:---------:|:---------:
`0` | space | space
`1` | wall | wall
`2` | sprite | sprite (1)
`3` | n/a | sprite (2)
`4` | n/a | collectable
`5` | n/a | consumable
`I` | n/a | vertical door / trap
`H` | n/a | horizontal door
`N/S/W/E` | starting position + direction | starting position + direction
`(space)` | empty | empty

## :small_orange_diamond: Bonus Features

Official bonuses (15/14):
- wall collisions
- skybox
- floor and / or ceiling texture
- a HUD
- ability to look up and down
- jump and crouch
- distance related shadow effect
- life bar
- more items (sprites)
- object collisions
- earning points and / or losing life by picking up objects / traps
- doors which can open and close
- animated sprite (doors)
- sounds and music
- rotate the point of view with the mouse

Unofficial bonuses (1):
- inventory

## :small_orange_diamond: Resources
- [A MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) by _hsmits_ and _jvan-sni_
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README.md
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
