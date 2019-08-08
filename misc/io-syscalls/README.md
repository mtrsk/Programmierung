# Some Notes

## Using Raw IO (open, close) instead of stdio.

```
$ time ./raw.out 1 5000000
./raw.out 1 5000000  2.04s user 6.06s system 99% cpu 8.105 total
```

## Comparing with fopen and fwrite

```
time ./std.out 1 5000000
./std.out 1 5000000  0.10s user 0.01s system 70% cpu 0.155 total
```
