#
# My heavily modified version of the NVIDIA transpose code.
#
################################################################################
#
# Build script for project
#
################################################################################

EXECUTABLE  := transpose4d
# Cuda source files (compiled with cudacc)
CUFILES   := transpose.cu
# C/C++ source files (compiled with gcc / c++)
CCFILES   := \
  transpose_gold.cpp \
  $(NULL)

################################################################################
# Rules and targets

#include ../../common/common.mk
include /opt/nvidia/cuda/common/common.mk
