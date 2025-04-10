# 🧠 Philosophers
**Without bonus**

A multithreaded simulation of the classic **Dining Philosophers Problem** using **threads** and **mutexes** in C.
This project explores concurrency, synchronization, and resource sharing in a deadlock-free environment.
## 📝 Table of Contents
- [Overview](#overview)
- [Rules](#rules)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage](#usage)
- [Example](#example)

## Overview
The **Dining Philosophers Problem** models a group of philosophers sitting around a table, each alternating between **thinking**, **eating**, and **sleeping**. Forks are shared resources placed between each pair of philosophers, and a philosopher needs both their left and right fork to eat.

The simulation:

- Stops if a philosopher **dies of starvation**
- Optionally ends if all philosophers have eaten a given number of times

## Rules
Each philosopher must alternate between **thinking**, **eating**, and **sleeping**

- A philosopher **must hold both forks** to eat
- A philosopher dies if they don’t eat within `time_to_die` milliseconds
- Philosophers **do not communicate**
- Forks are shared and protected with **mutexes**

**No global variables** allowed

## How It Works
Each philosopher is a thread. The shared forks are represented by mutexes. Philosophers:

1. **Take forks**
2. **Eat** for `time_to_eat` ms
3. **Sleep** for `time_to_sleep` ms
4. **Think**, then repeat

If a philosopher doesn’t eat within the allowed time, they **die**, ending the simulation.
## Installation
To install the project and run the simulation:

1. **Clone the repository:**
```bash
git clone https://github.com/DarynaSerhieieva/philosophers.git
```
2. **Navigate into the project folder:**
Open a folder:
```bash
cd philosopher/philo
```
## Compilation
Compile using the provided Makefile:
```bash
make
```
Targets:

- `make`: builds the executable philo

- `make clean`: removes object files

- `make fclean`: removes object files and the executable

- `make re`: rebuilds everything

## Usage
Use your **own data** instead of `number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep` and `[number_of_times_each_philosopher_must_eat]`(optional argument)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## Example
```bash
./philo 5 800 200 200
```
This starts 5 philosophers who die after 800ms of starvation, eat for 200ms, and sleep for 200ms.
With optional parameter:
```bash
./philo 5 800 200 200 7
```
This stops the simulation once all philosophers have eaten at least 7 times.
