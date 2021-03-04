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
INC_DIR         = -I support -I /usr/include/freetype2 


# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: PabloAIHomeExercise

# To create the PabloAIHomeExercise. executable file count we need the object files
# PabloAIHomeExercise.o, AiModel.o, AiSupportAlgorithms.o AiSupportClasses.o, and pngwriter.o:
#
PabloAIHomeExercise:  PabloAIHomeExercise.o AiModel.o AiSupportAlgorithms.o AiSupportClasses.o pngwriter.o 
	$(CC) $(CFLAGS) -o PabloAIHomeExercise. $(OBJ_DIR)AiModel.o $(OBJ_DIR)PabloAIHomeExercise.o $(OBJ_DIR)AiSupportAlgorithms.o $(OBJ_DIR)AiSupportClasses.o $(OBJ_DIR)pngwriter.o $(LIBRARIES)

# To create the object file PabloAIHomeExercise.o, we need the source
# file PabloAIHomeExercise.cpp:
#
PabloAIHomeExercise.o:  PabloAIHomeExercise.cpp
	$(CC) $(CFLAGS) -c PabloAIHomeExercise.cpp $(INC_DIR) -o $(OBJ_DIR)PabloAIHomeExercise.o 
	
# To create the object file AiModel.o, we need the source
# file AiModel.cpp:
#
AiModel.o: $(SUPPORT_DIR)AiModel.cpp
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiModel.cpp $(INC_DIR) -o $(OBJ_DIR)AiModel.o 

# To create the object file AiSupportAlgorithms.o, we need the source
# file AiSupportAlgorithms.cpp:
#
AiSupportAlgorithms.o: $(SUPPORT_DIR)AiSupportAlgorithms.cpp
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiSupportAlgorithms.cpp $(INC_DIR)-o $(OBJ_DIR)AiSupportAlgorithms.o

# To create the object file AiSupportClasses.o, we need the source
# file AiSupportClasses.cpp:
#
AiSupportClasses.o: $(SUPPORT_DIR)AiSupportClasses.cpp
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiSupportClasses.cpp $(INC_DIR) -o $(OBJ_DIR)AiSupportClasses.o
	

# To create the object file pngwriter.o, we need the source
# file pngwriter.cc:
pngwriter.o:  $(SUPPORT_DIR)pngwriter.cc
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)pngwriter.cc $(INC_DIR) -o $(OBJ_DIR)pngwriter.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) $(OBJ_DIR)*.o
	

