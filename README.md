# praph
Pregel-esque parallel graph algorithms

[Pregel](https://research.google/pubs/pub37252/) is a distributed graph processing engine developed at Google. Pregel provides unique semantics to program graph algorithms so that they can easily be distributed across large clusters. While this project doesn't aim to reproduce the distributed compute framework of Pregel, it attempts to create a multi-threaded graph processing engine analogous to how Pregel computes its own algorithms.

Implemented Algorithms:
- [ ] pagerank

To use, extend the virtual class in `pregel.hh`. To run examples in this project, build with make and run the binary with the algorithm name in question. 