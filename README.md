# write1.c

## Description
Writes to another terminal, gives warning if other terminal user is not logged in. Also ensures most recent terminal opened is written to.

## Language
C

## Overview
A C implementation of inter-terminal communication that sends messages to other user terminals. It includes validation checks to ensure the target user is logged in and prioritizes the most recently opened terminal.

## Features
- Inter-terminal messaging
- User login verification
- Terminal prioritization
- Warning system for offline users

## Usage
```bash
gcc -o write1 write1.c
./write1 <username>
```

## How It Works
1. Checks if the target user is logged in
2. Finds the most recently opened terminal for that user
3. Sends message to that terminal
4. Displays warning if user is not logged in

## Requirements
- C compiler
- Unix/Linux environment
- Access to utmp/wtmp system files

## License
See LICENSE file for details.
