import fileinput
import string
import sys
import os
import commands

class Subroutine:
    
    def __init__(self):
        """Creates a subroutine class"""
        self.name = []


class Language:
    
    def __init__(self,language):
        """Creates a language class"""        
        self.language = language
        if (self.language == "Fortran77"):
            self.comment    = "C     "
            self.indent     = "      "
            self.ordering   = "F" # Fortran indexing, ie left-to-right
            self.offset     = 1
        elif (self.language == "Fortran90"):
            self.comment    = "! "
            self.indent     = ""
            self.ordering   = "F"
            self.offset     = 1
        elif (self.language == "C"):
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C" # C indexing, ie right-to-left
            self.offset     = 0            
        elif (self.language == "C++"):
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C"
            self.offset     = 0            
        elif (self.language == "Cuda"):
            self.comment    = "// "
            self.indent     = ""
            self.ordering   = "C"
            self.offset     = 0            
        else:
            raise "Unsupported language"
        
        
    def __str__(self):
        """Prints code"""
        raise "Printing not yet enabled."
        
class Processor:
    def __init__(self):
        """Creates a processor class""" 
        self.processor_type  = []
        self.number_of_cores = []
        self.has_sse   = []
        self.has_sse2  = []
        self.has_sse3  = []
        self.has_ssse3 = []
        self.number_of_registers = []
        self.size_L1cache = []
        self.size_L2cache = []
        self.size_L3cache = []
        self.size_L4cache = []

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
        else:
            self.has_sse = False
            
        if ' sse2 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_sse2 = True
        else:
            self.has_sse2 = False
            
        if ' sse3 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_sse3 = True
        else:
            self.has_sse3 = False
            
        if ' ssse3 ' in commands.getoutput('cat /proc/cpuinfo'):
            self.has_ssse3 = True
        else:
            self.has_ssse3 = False      
            
        
    def setCacheSizes(self,cache_sizes):
        """Manually set cache sizes: cache_sizes[n] is Ln cache"""          
        raise "The setCacheSizes feature is not available"                                   
        
        
    def __str__(self):
        """Prints code"""
        raise "Printing not yet enabled."
                
        
class Compiler:
    
    def __init__(self,vendor):
        """Creates a compiler class"""     
        self.vendor = vendor
        if (self.vendor == "Intel"):
            self.Fname    = "ifort"
            self.Cname    = "icc"
            if commands.getstatusoutput(self.Fname+" --version")[0] == 0:
                try:
                    self.Fversion = float(commands.getoutput(Fname+" --version").split()[2])
                except:
                    raise "Failed to parse version for "+self.Fname
                
            else:
                raise "Failed to determine version for "+self.Fname   
                
            if commands.getstatusoutput(self.Cname+" --version")[0] == 0:
                try:
                    self.Cversion = float(commands.getoutput(Cname+" --version").split()[2])
                except:
                    raise "Failed to parse version for "+self.Cname
                
            else:
                raise "Failed to determine version for "+self.Cname  
                
                
        elif (self.vendor == "IBM"):
            self.Fname    = "xlf"
            self.Cname    = "xlc"
            self.Fversion = ""
            self.Cversion = ""
        elif (self.vendor == "GNU"):
            self.Fname    = "gfortran" # no support for g77
            self.Cname    = "gcc"
            self.Fversion = ""
            self.Cversion = ""    
        elif (self.vendor == "Pathscale"):
            self.Fname    = ""
            self.Cname    = ""
            self.Fversion = ""
            self.Cversion = ""   
        elif (self.vendor == "PGI"):
            self.Fname    = ""
            self.Cname    = ""
            self.Fversion = ""
            self.Cversion = ""      
        elif (self.vendor == "NVIDIA"):
            self.Cname    = ""
            self.Cversion = ""        
        else:
            raise "Unsupported compiler"
        
        
    def __str__(self):
        """Prints code"""
        raise "Printing not yet enabled."

        
class Loop:        
    
    def __init__(self):
        """Constructs a generic do/for loop"""
        self.loop_offset  = 0
        self.loop_index   = ""
        self.loop_active  = True
        self.index_begin  = 0
        self.index_end    = 2^31
        self.index_stride = 1

    def setLoopIndex(self,loop_index):
        if type(loop_index) == type('i1'):
            self.loop_index   = loop_index
        else:
            raise "A loop index must be a string"
        
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
        
    def __str__(self):
        """Prints code"""
        raise "Printing not yet enabled."