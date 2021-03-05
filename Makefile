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
	$(info AI Home Exercise executable linking finished...)
	@echo "========================================================"
	@echo ""
	

# To create the PabloAIHomeExercise. executable file count we need the object files
# PabloAIHomeExercise.o, AiModel.o, AiSupportAlgorithms.o AiSupportClasses.o, and pngwriter.o:
#

PabloAIHomeExercise:  PabloAIHomeExercise.o AiModel.o AiSupportAlgorithms.o AiSupportClasses.o pngwriter.o 
	@echo "========================================================"
	@echo "AI Home Exercise executable linking started..."
	$(CC) $(CFLAGS) -o PabloAIHomeExercise. $(OBJ_DIR)AiModel.o $(OBJ_DIR)PabloAIHomeExercise.o $(OBJ_DIR)AiSupportAlgorithms.o $(OBJ_DIR)AiSupportClasses.o $(OBJ_DIR)pngwriter.o $(LIBRARIES)

# To create the object file PabloAIHomeExercise.o, we need the source
# file PabloAIHomeExercise.cpp:
#
PabloAIHomeExercise.o:  PabloAIHomeExercise.cpp
	@echo "--------------------------------------------------------"
	@echo "Compiling AI Home Exercise main file"
	$(CC) $(CFLAGS) -c PabloAIHomeExercise.cpp $(INC_DIR) -o $(OBJ_DIR)PabloAIHomeExercise.o 
	@echo "AI Home Exercise main file compilation process completed"
	@echo "--------------------------------------------------------"
	@echo ""

	
# To create the object file AiModel.o, we need the source
# file AiModel.cpp:
#
AiModel.o: $(SUPPORT_DIR)AiModel.cpp
	@echo "----------------------------------------------"
	@echo "Compiling AI Model classes"
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiModel.cpp $(INC_DIR) -o $(OBJ_DIR)AiModel.o 
	@echo "AI Model classes compilation process completed"
	@echo "----------------------------------------------"
	@echo ""

	
# To create the object file AiSupportAlgorithms.o, we need the source
# file AiSupportAlgorithms.cpp:
#
AiSupportAlgorithms.o: $(SUPPORT_DIR)AiSupportAlgorithms.cpp
	@echo "-------------------------------------------------------------"
	@echo "Compiling AI Support Algorithms functions"
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiSupportAlgorithms.cpp $(INC_DIR)-o $(OBJ_DIR)AiSupportAlgorithms.o
	@echo "AI Support Algorithms functions compilation process completed"
	@echo "-------------------------------------------------------------"
	@echo ""

# To create the object file AiSupportClasses.o, we need the source
# file AiSupportClasses.cpp:
#
AiSupportClasses.o: $(SUPPORT_DIR)AiSupportClasses.cpp
	@echo "-----------------------------------------------"
	@echo "Compiling AI Suport classes"
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)AiSupportClasses.cpp $(INC_DIR) -o $(OBJ_DIR)AiSupportClasses.o
	@echo "AI Suport classes compilation process completed"
	@echo "-----------------------------------------------"
	@echo ""

# To create the object file pngwriter.o, we need the source
# file pngwriter.cc:
pngwriter.o:  $(SUPPORT_DIR)pngwriter.cc
	@echo "---------------------------------------------"
	@echo "Compiling PNGWriter files"
	$(CC) $(CFLAGS) -c $(SUPPORT_DIR)pngwriter.cc $(INC_DIR) -o $(OBJ_DIR)pngwriter.o
	@echo "PNGWriter files compilation process completed"
	@echo "---------------------------------------------"
	@echo ""

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	@echo "========================================================"
	@echo "Removing all the object files..."
	$(RM) $(OBJ_DIR)*.o
	@echo "All the object files removed..."
	@echo "========================================================"
	@echo ""
	

