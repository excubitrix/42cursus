# :large_orange_diamond: Philosophers &ensp; ![42Project Score](https://badge42.herokuapp.com/api/project/floogman/Philosophers)

The objective of this project is to code three different programs that each solve the ["Dining Philosopher Problem"](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in a slightly different way.

## :small_orange_diamond: Description

This project consists of three programs: `philo_one`, `philo_two` and `philo_three`.

- in `philo_one` each philosopher is represented by a *thread* and the forks are protected by *mutex locks*
- in `philo_two` each philosopher is also represented by a *thread* but the number of forks are represented by a *semaphore* this time
- in `philo_three` each philosopher is now represented by a *process* but the number of forks are represented by a *semaphore* again

## :small_orange_diamond: Instructions

1. Run `make` to compile all three programs.

2. Execute the desired program as follows:
`./<program> <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`

Where
- `number_of_philosophers` is the number of philosophers and also the number of forks,
- `time_to_die` is - in milliseconds - the time a philosopher has to start eating (again) after starting his last meal or the beginning of the simulation before it dies,
- `time_to_eat` is - in milliseconds - the time it takes for a philosopher to finish their meal, and
- `time_to_sleep` is - in milliseconds - the time a philosopher will spend sleeping.

`number_of_times_each_philosopher_must_eat` is an optional argument. If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` the simulation stops. If not specified, the simulation will stop only once a philosopher has died.

## :small_orange_diamond: Resources
- [Programming with Threads by Jacob Sorber](https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM)
#### Makefile
- [GNU make Manual](https://www.gnu.org/software/make/manual/make.html)
    - [addprefix](https://www.gnu.org/software/make/manual/make.html#File-Name-Functions)
    - [$@, $<](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)
#### README
- [Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Multiple Consecutive Spaces in Markdown](https://steemit.com/markdown/@jamesanto/how-to-add-multiple-spaces-between-texts-in-markdown)
#### ProjectScore Badge
- [🚀 Dynamically Generated Badge by badge42](https://github.com/JaeSeoKim/badge42)
