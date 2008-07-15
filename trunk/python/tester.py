import spaghetty

s = spaghetty.Subroutine("tester.F")
s.details()

a = spaghetty.TransposeAlgorithm()
a.details()
a.defineAlgorithm([1,2,3,4])
a.details()

i = spaghetty.TransposeImplementation(a)
i.details()
i.setLoopOrdering([1,2,3,4])
i.details()

l = spaghetty.Language("Fortran")
l.details()

p = spaghetty.Processor()
p.details()
p.determineProcessorType()
p.determineNumberProcessorCores()
p.determineSpecialInstructions()
#p.setCacheSizes()
p.details()

c = spaghetty.Compiler("Intel")
c.details()
c.determineCompilerVersion()
c.details()

o = spaghetty.Loop()
o.details()
o.setLoopIndex('i1')
o.setLoopOffset(0)
o.setIndexBegin(1)
o.setIndexEnd(10)
o.setLoopStride(1)
o.details()

t = spaghetty.Tensor("a",4)
t.details()
t.makeIndices()
t.details()