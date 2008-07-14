import fileinput
import string
import sys
import os

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
            return "Unsupported language"
        
        
    def __str__(self):
        """Prints code"""
        print "Printing not yet enabled."
        
class Processor:
    def __init__(self):
        """Creates a processor class"""   
        processor_type  = os.system('uname -p')
        number_of_cores = os.system('grep cores /proc/cpuinfo') 
        self.vendor = vendor
        if (self.vendor == "Intel"):
            self.Fname    = "ifort"
            self.Cname    = "icc"
            self.Fversion = ""
            self.Cversion = ""  
        else:
            return "Processor could not be initialized"              
        
        
    def __str__(self):
        """Prints code"""
        print "Printing not yet enabled."
                
        
class Compiler:
    
    def __init__(self,vendor):
        """Creates a compiler class"""     
        self.vendor = vendor
        if (self.vendor == "Intel"):
            self.Fname    = "ifort"
            self.Cname    = "icc"
            self.Fversion = ""
            self.Cversion = ""
        elif (self.vendor == "IBM"):
            self.Fname    = ""
            self.Cname    = ""
            self.Fversion = ""
            self.Cversion = ""
        elif (self.vendor == "GNU"):
            self.Fname    = ""
            self.Cname    = ""
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
            return "Unsupported compiler"
        
        
    def __str__(self):
        """Prints code"""
        print "Printing not yet enabled."

        
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
        if isinstance(loop_index,str):
            self.loop_index   = loop_index
        else:
            return "A loop index must be a string"
        
    def setIndexBegin(self,index_begin):
        if isinstance(index_begin,int) or isinstance(index_begin,long):
            self.index_begin   = index_begin
        else:
            return "An index bound must be a integer"          

    def setIndexEnd(self,index_end):
        if isinstance(index_end,int) or isinstance(index_end,long):
            self.index_end   = index_end
        else:
            return "An index bound must be a integer"               
              
    def setLoopStride(self,loop_stride):
        if isinstance(loop_stride,int) or isinstance(loop_stride,long):
            self.loop_stride   = loop_stride
        else:
            return "A loop stride must be a integer"
        
    def __str__(self):
        """Prints code"""
        print "Printing not yet enabled."