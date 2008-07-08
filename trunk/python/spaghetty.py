import fileinput
import string
import sys
import os

class Subroutine:
    
    def __init__(self,language):
        """Creates a subroutine class"""
        self.language = language
        self.name = []


class Language:
    
    def __init__(self,language):
        """Creates a language class"""        
        self.language = language
        if (self.language == "Fortran77"):
            self.comment   = "C     "
            self.indent    = "      "
        elif (self.language == "Fortran90"):
            self.comment = "! "
            self.indent  = ""
        elif (self.language == "C"):
            self.comment = "// "
            self.indent  = ""
        elif (self.language == "C++"):
            self.comment = "// "
            self.indent  = ""
        elif (self.language == "Cuda"):
            self.comment = "// "
            self.indent  = ""
        else:
            return "Unsupported language"
        
        
    def __str__(self):
        """Prints code"""
        print "Printing yet enabled."
        
        
class Loop:        
    
    def __init__(self):
        """Initializes a do/for loop"""
        loop_offset = []
        loop_unrolling = []
        loop_index = []
        index_begin = []
        index_end = []
        index_stride = []
