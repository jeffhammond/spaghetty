spaghetty
=========

Self-optimizing Python Automatic Generator of Hierarchically blockEd Tensor Transpose librarY

# Purpose

Spaghetty uses brute-force (unpruned search) auto-tuning to generate optimized
tensor permutation (transposition) routines as are used heavily in NWChem.

As an example, here is a common permutation in the NWChem CCSD code:

```
for all i,j,k,l:
  b(i,j,k,l) = a(l,k,j,i)
end
```

Obviously, this memory access pattern is inefficient.  The ordering of the loops
over (i,j,k,l) has a significant effect on the performance and this effect is
hardware-dependent.  This is why we use auto-tuning to discover what order is best
on a given processor.

In many cases, it is obvious why some loop orders are better than others, but not 
always.  And the optimal ordering changes as a function of the array dimensions.
We do not attempt to tune over all cases in this regard, but only over a representative
size that corresponds to a reasonable tile size that an NWChem expert would use for 
a particular simulation.

In the case of CCSD, tilesize is usually around 30, but perhaps as much as 100 if one
is using ARMCI-MPI, which does not crash for huge tiles.

For CCSD(T), tilesize is closer to 20, and 20 is perhaps the most common value.
For CCSDT, tilesize of less than 20 is necessary.  For CCSDTQ, tilesize is more like 10.

# History

This project began when I was in graduate school and discovered that NWChem spent more
time in ``TCE_SORT_4`` than in in ``DGEMM`` for CCSD-QR calculations on my laptop.

The code generator has been written at least 3 times, including once in C++, which was
determined to be a waste of time.
