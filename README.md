# Aggregate Signatures

An implementations of different aggregate signature schemes using the [MCL pairings library](https://github.com/herumi/mcl).

### Sources

- [Short signatures from the Weil pairing](https://link.springer.com/content/pdf/10.1007/s00145-004-0314-9.pdf), Boneh et al. (2001)
- [Aggregate and verifiably encrypted signatures from bilinear maps](https://link.springer.com/content/pdf/10.1007/3-540-39200-9_26.pdf), Boneh et al. (2003)
- [History-free sequential aggregate signatures](https://eprint.iacr.org/2011/231.pdf), Fischlin et al. (2012)


## Getting started

1. Download this repo with

```
git clone https://github.com/shangsuru/aggregate-signatures.git
```

2. Install githooks via

```
git config core.hookspath .githooks
```

3. Run benchmarks with

```
./run_experiments.sh
```
