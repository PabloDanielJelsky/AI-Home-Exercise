#############################################	
#############################################
#############################################	
### Pablo AI Home Exercise Makefile	- C++ ###
#############################################
#############################################
#############################################

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC              = g++
CFLAGS          = -g -Wall
LIBRARIES       = -lgdal -lpng -lfreetype
OBJ_DIR         = objects/
SUPPORT_DIR     = support/
INC_DIR         = /usr/include/freetype2


# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: PabloAIHomeExercise

# To create the PabloAIHomeExercise. executable file count we need the object files
# PabloAIHomeExercise.o, PabloSupportClasses.o, and pngwriter.o:
#
PabloAIHomeExercise:  PabloAIHomeExercise.o PabloSupportClasses.o pngwriter.o 
	$(CC) $(CFLAGS) -o PabloAIHomeExercise. $(OBJ_DIR)PabloAIHomeExercise.o $(OBJ_DIR)PabloSupportClasses.o $(OBJ_DIR)pngwriter.o $(LIBRARIES)

# To create the object file PabloAIHomeExercise.o, we need the source
# file PabloAIHomeExercise.cpp:
#
PabloAIHomeExercise.o:  PabloAIHomeExercise.cpp
	$(CC) $(CFLAGS) -c PabloAIHomeExercise.cpp -I$(INC_DIR) -o $(OBJ_DIR)PabloAIHomeExercise.o 

# To create the object file PabloSupportClasses.o, we need the source
# file PabloSupportClasses.cpp:
#
PabloSupportClasses.o: $(SUPPORT_DIR)PabloSupportClasses.cpp
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)PabloSupportClasses.cpp -o $(OBJ_DIR)PabloSupportClasses.o
	
# To create the object file PabloAIHomeExercise.o, we need the source
# file pngwriter.cc:
pngwriter.o:  $(SUPPORT_DIR)pngwriter.cc
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)pngwriter.cc -I$(INC_DIR) -o $(OBJ_DIR)pngwriter.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) $(OBJ_DIR)*.o
	

