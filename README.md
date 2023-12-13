# praph
Pregel-esque parallel graph algorithms

[Pregel](https://research.google/pubs/pub37252/) is a distributed graph processing engine developed at Google. Pregel provides unique semantics to program graph algorithms so that they can easily be distributed across large clusters. While this project doesn't aim to reproduce the distributed compute framework of Pregel, it attempts to create a multi-threaded graph processing engine analogous to how Pregel computes its own algorithms.

For testing, we implemented the pagerank algorithm as described in the original paper. To use, extend the virtual class in `pregel.hh`. To run the pagerank example in this project, build with make and run the binary. (This is still in progress as we need sample data to construct the web graph to run PageRank on). 
```
./pregel
```
One change that we made from the original pregel paper is the omission of the MessageIterator as a parameter to Compute. This was made due to making the program thread-safe, but still performant, and also exploiting the fact that we are making a single process program opposed to a distributed compute framework of the original pregel system. 
