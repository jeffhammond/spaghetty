import fileinput
import string
import sys
import os
import commands

space = ' '

class Timer:
    
    def __init__(self,name):
        """Creates a timer class"""
        self.repetitions = 0
        self.total_time  = 0.0

    def details(self):
        """Prints timer details"""
        print "repetitions = "+str(self.repetitions)
        print "total_time  = "+str(self.total_time) 

class Subroutine:
    
    def __init__(self,name):
        """Creates a subroutine class"""
        self.name = []
        self.code = []

    def details(self):
        """Prints subroutine details"""
        print "Printing not yet enabled."
     
     
class TransposeAlgorithm:
    
    def __init__(self):
        """Creates a transpose algorithm class"""
        self.dimension = 0
        self.tuple = []
        
    def defineAlgorithm(self,tuple):
        """Defines a transpose algorithm"""
        # This part is not robust at all and needs to be upgraded
        self.dimension = len(tuple)
        if type(tuple) == type([1,2,3,4]):
            self.tuple = tuple
        else:
            raise "The transpose algorithm must be defined by a list"  
        
    def details(self):
        """Prints transpose algorithm details"""
        print "dimension = "+str(self.dimension)
        print "transpose = "+str(self.tuple) 

class TransposeImplementation:
       
    def __init__(self,TransposeAlgorithm):
        """Creates a transpose implementation class"""
        self.dimension = TransposeAlgorithm.dimension
        self.transpose_order = TransposeAlgorithm.tuple
        self.loop_order = [] 
        
    def setLoopOrdering(self,loop_order):
        """Sets the particular loop ordering for a given transpose ordering"""
        # This part is not robust at all and needs to be upgraded
        if type(loop_order) == type([1,2,3,4]):
            self.loop_order = loop_order
        else:
            raise "The loop ordering must be defined by a list"
        
            
    def details(self):
        """Prints transpose implementation details"""
        print "dimension    = "+str(self.dimension)
        print "transpose    = "+str(self.transpose_order) 
        print "loop order   = "+str(self.loop_order)         


class Language:
    
    def __init__(self,language):
        """Creates a language class"""        
        if language == "Fortran77" or language == "Fortran":
            self.language   = "Fortran77"
            self.comment    = "C     "
            self.indent     = "      "
            self.ordering   = "F" # Fortran indexing, ie left-to-right
            self.offset     = 1
            self.integer    = "integer"
            self.real       = "double precision"
        elif language == "Fortran90":
            self.language   = "Fortran90"
            self.comment    = "! "
            self.indent     = ""
            self.ordering   = "F"
            self.offset     = 1
        elif language == "C":
            self.language   = "C"
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C" # C indexing, ie right-to-left
            self.offset     = 0            
        elif language == "C++":
            self.language   = "C++"
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C"
            self.offset     = 0            
        elif language == "Cuda":
            self.language   = "Cuda"
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C"
            self.offset     = 0            
        else:
            raise "Unsupported language"
            

    def details(self):
        """Prints language details"""
        print "comment  = "+str(self.comment)
        print "indent   = "+str(self.indent)
        print "ordering = "+str(self.ordering)
        print "offset   = "+str(  self.offset)
        
        
class Processor:
    def __init__(self):
        """Creates a processor class""" 
        self.processor_type  = ""
        self.processor_name  = ""
        self.number_of_cores = 1
        self.has_sse   = False
        self.has_sse2  = False
        self.has_sse3  = False
        self.has_ssse3 = False
        self.number_of_registers = -1
        self.size_L1cache = -1
        self.size_L2cache = -1
        self.size_L3cache = -1
        self.size_L4cache = -1

    def determineProcessorType(self):
        """Tries to identify processor""" 
        if commands.getstatusoutput('uname -p')[0] == 0:  
            self.processor_type  = commands.getoutput('uname -p')

    def determineNumberProcessorCores(self):    
        """Tries to determine the number of processor cores"""       
        # Cannot implement multi-core support in a universal way  
        self.number_of_cores = 1 

    def determineSpecialInstructions(self): 
        if ' sse ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_sse = True
#        else:
#            self.has_sse = False
            
        if ' sse2 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_sse2 = True
#        else:
#            self.has_sse2 = False
            
        if ' sse3 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_sse3 = True
#        else:
#            self.has_sse3 = False
            
        if ' ssse3 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_ssse3 = True
#        else:
#            self.has_ssse3 = False      
        
    def setCacheSizes(self,cache_sizes):
        """Manually set cache sizes: cache_sizes[n] is Ln cache"""          
        raise "The setCacheSizes feature is not available"                                   
        
    def details(self):
        """Prints processor details"""
        print "processor_type  = "+str(self.processor_type)
        print "processor_name  = "+str(self.processor_name)
        print "number_of_cores  = "+str(self.number_of_cores)
        print "has_sse  = "+str(self.has_sse)
        print "has_sse2  = "+str(self.has_sse2)
        print "has_sse3  = "+str(self.has_sse3)
        print "has_ssse3  = "+str(self.has_ssse3)
        print "number_of_registers  = "+str(self.number_of_registers)
        print "size_L1cache  = "+str(self.size_L1cache)
        print "size_L2cache  = "+str(self.size_L2cache)
        print "size_L3cache  = "+str(self.size_L3cache)
        print "size_L4cache  = "+str(self.size_L4cache)
                
        
class Compiler:
    
    def __init__(self,vendor):
        """Creates a compiler class"""     
        self.vendor = vendor
        if (self.vendor == "Intel"):
            self.Fname    = "ifort"
            self.Cname    = "icc"
            self.Fversion = 0.0
            self.Cversion = 0.0  
        elif (self.vendor == "IBM"):
            self.Fname    = "xlf"
            self.Cname    = "xlc"
            self.Fversion = 0.0
            self.Cversion = 0.0
        elif (self.vendor == "GNU"):
            self.Fname    = "gfortran" # no support for g77
            self.Cname    = "gcc"
            self.Fversion = 0.0
            self.Cversion = 0.0    
#        elif (self.vendor == "Pathscale"):
#        elif (self.vendor == "PGI"):   
#        elif (self.vendor == "NVIDIA"):      
        else:
            raise "Unsupported compiler"
        
    def determineCompilerVersion(self):
        """Determines what version of the compiler we have"""
        # This is probably not the best way to do this
        if commands.getstatusoutput(self.Fname+" --version")[0] == 0:
            self.Fversion = float(commands.getoutput(self.Fname+" --version").split()[2])
                
        else:
            self.Fversion = 0
            raise "Failed to determine version for "+self.Fname              
                
        if commands.getstatusoutput(self.Cname+" --version")[0] == 0:
            self.Cversion = float(commands.getoutput(self.Cname+" --version").split()[2])
                
        else:
            self.Cversion = []
            raise "Failed to determine version for "+self.Cname              
        
        
    def details(self):
        """Prints compiler details"""
        print "Fortran compiler name    = "+str(self.Fname)
        print "Fortran compiler version = "+str(self.Fversion)
        print "C       compiler name    = "+str(self.Cname)        
        print "C       compiler version = "+str(self.Cversion)

class Tensor:
    
    def __init__(self,name,dimension):
        """Constructs a tensor"""
        if type(name) == type("a"):
            self.name = name
        else:
            raise "A loop index must be a integer"
        
        if type(dimension) == type(1):
            self.dimension = dimension
        else:
            raise "A loop index must be a integer"
        
        self.indices = []
        
        
    def setType(self,type):
        if type(loop_index) == type("string"):
            self.type = type
        else:
            raise "A loop index must be a string"       
                
        
    def makeIndices(self):
        for i in range(0,self.dimension):
            self.indices += [self.name+'_'+'i'+str(i)]
            

    def printIndices(self):
        if len(self.indices) > 0:
            for i in range(0,self.dimension):
                print self.indices[i]  
        
    def allocate(self,Language):
        """Prints the code to allocate the tensor"""
        if Language.language == Fortran:
            codelet = Language.real+space+self.name+'('+self.indices+')'
            return codelet

    def details(self):
        """Prints tensor details"""
        print "name      = "+str(self.name)
        print "dimension = "+str(self.dimension)
        self.printIndices()
    
class Loop:        
    
    def __init__(self):
        """Constructs a generic do/for loop"""
        self.loop_offset  = 0
        self.loop_index   = ""
        self.loop_active  = True
        self.index_begin  = 0
        self.index_end    = 2**31
        self.index_stride = 1

    def setLoopIndex(self,loop_index):
        if type(loop_index) == type('i1'):
            self.loop_index   = loop_index
        else:
            raise "A loop index must be a string"

    def setLoopOffset(self,loop_offset):
        if type(loop_offset) == type(1):
            self.loop_offset   = loop_offset
        else:
            raise "A loop offset must be a integer"   
        
    def setIndexBegin(self,index_begin):
        if type(index_begin) == type(1):
            self.index_begin   = index_begin
        else:
            raise "An index bound must be a integer"          

    def setIndexEnd(self,index_end):
        if type(index_end) == type(1):
            self.index_end   = index_end
        else:
            raise "An index bound must be a integer"               
              
    def setLoopStride(self,loop_stride):
        if type(loop_stride) == type(1):
            self.loop_stride   = loop_stride
        else:
            raise "A loop stride must be a integer"
        
    def details(self):
        """Prints loop details"""
        print "loop_offset   = "+str(self.loop_offset)
        print "loop_index    = "+str(self.loop_index)
        print "size_L4cache  = "+str(self.loop_active)
        print "index_begin   = "+str(self.index_begin)
        print "index_end     = "+str(self.index_end)
        print "index_stride  = "+str(self.index_stride)
    
# I found this somewhere on the Internet; it appears to be "free" code.    
def perm(l):
    sz = len(l)
    if sz <= 1:
        return [l]
    return [p[:i]+[l[0]]+p[i:] for i in xrange(sz) for p in perm(l[1:])]    



