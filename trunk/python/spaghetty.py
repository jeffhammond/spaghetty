import fileinput
import string
import sys
import os

class Subroutine:
    
   def __init__(self,language):
      """Creates an empty subroutine class"""
      self.language = language
      self.name = []



class Language:
    
    def __init__(self,language):
      if (self.language == "Fortran77"):
         self.comment = "C     "
         self.indent  = "      "
      elif (self.language == "Fortran90"):
         self.comment = "! "
         self.indent  = ""
      elif (self.language == "C"):
         self.comment = "// "
         self.indent  = ""
      elif (self.language == "C++"):
         self.comment = "// "
         self.indent  = ""
      else:
         return "Unknown language"

