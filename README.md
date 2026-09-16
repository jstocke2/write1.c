# write1.c

A Unix systems-programming exercise that sends terminal input to another logged-in user's most recent terminal session.

## Build and run

```sh
cc write1.c -o write1
./write1 username
```

The program depends on Unix login-session and terminal facilities and may require appropriate permissions.
