# Aggregate Signatures

An implementations of different aggregate signature schemes using the [MCL pairings library](https://github.com/herumi/mcl).

## Getting started

1. Download this repo with

```
git clone https://github.com/shangsuru/aggregate-signatures.git
```

2. Install githooks via

```
git config core.hookspath .githooks
```

## Build the Code

```
cmake -S . -B build
cmake --build build
```

## Run tests

```
cd /build/tests
./main-t
```
