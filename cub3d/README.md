# :large_orange_diamond: cub3d &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/cub3d)

The aim of this project is to make a dynamic view inside a maze using ray-casting.

## :small_orange_diamond: Instructions

1. Run `make` to compile a game equipped with only the mandatory features and `make bonus` for one with all features.

2. Execute the resulting executable with a valid .cub file as its first argument.
```
./cub3D maps/mandatory.cub
```

## :small_orange_diamond: Controls

Key(s) | Mandatory | Bonus
:-----:|:---------:|:-----:
`[w][a][s][d]` | move around the maze | move around the maze
`[<][>]` | rotate the point of view | rotate the point of view
`[^][v]` | n/a | rotate the point of view
`mouse` | n/a | rotate the point of view
`[space]` | n/a | jump
`[shift]` | n/a | crouch
`[e]` | n/a | interact with objects
`[1][2][3][4]` | n/a | interact with objects in your inventory
`[esc]` | exit | exit


## :small_orange_diamond: Map Symbols

Symbol | Mandatory | Bonus
:-----:|:---------:|:-----:
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
- earning points and / or losing life through picking up objects / traps
- doors which can open and close
- animated sprite (doors)
- sounds and music
- rotate the point of view with the mouse

Unofficial bonuses (1):
- inventory

## :small_orange_diamond: Sneak Peek

Mandatory | Bonus
:----:|:-----:
![cub3d](https://user-images.githubusercontent.com/59726559/136191725-80ea9a67-8aba-4b6e-a61f-ad499503982b.gif) | ![bonus_cub3d](https://user-images.githubusercontent.com/59726559/136191133-655ffe1b-3345-448e-93c5-e533eae64a3e.gif)

## :small_orange_diamond: Resources
- [A MiniLibX Documentation by hsmits and jvan-sni](https://harm-smits.github.io/42docs/libs/minilibx)
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
