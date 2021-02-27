//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloSupportClasses.h
//
// Version:			01.01
//
// Description:		Support classes for the AI home excercise interface file
//
// Author:			Pablo Daniel Jelsky
//
// Copyright:		
//
//	DEVELOPMENT HISTORY:
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	24-02-2021	Pablo Daniel Jelsky		01			00			Initial
//	27-02-2021	Pablo Daniel Jelsky		01			01			Working with Logger, Location, DsmLocation and DsmInformation classes
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PABLO_AI_SUPPORT_CLASSES_H__
#define	__PABLO_AI_SUPPORT_CLASSES_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <iostream>
		#include <fstream> 
		#include <string>		
		/*---- program files -------------------------------------------------------*/
	
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;		
		/*---- data declarations ---------------------------------------------------*/
		/*---- function prototypes -------------------------------------------------*/
	
	/*
		****************************************************************************
		* PUBLIC DECLARATIONS 
		****************************************************************************
	*/
		/*---- data declarations ---------------------------------------------------*/
	
	/*
		****************************************************************************
		* PRIVATE DECLARATIONS  
		****************************************************************************
	*/	
		/*---- context -------------------------------------------------------------*/
		/*---- macros --------------------------------------------------------------*/
		/*---- defines --------------------------------------------------------------*/
		#define	DEFAULT_DSM_INFORMATION_FILE_NAME	"output/DsmInformation.txt"
		#define	INVALID_COLUMN						-1
		#define	INVALID_ROW							-1
		#define INVALID_DSM_VALUE					-1
		/*---- data declarations ---------------------------------------------------*/		
		/*---- function prototypes -------------------------------------------------*/	

	/*
		****************************************************************************
		* PUBLIC CLASS DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Logger
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 26-02-2021
		// Description		: This class gives support for logging in a text file all
		//						the events that are needed to follow the sequence of
		//						events in the software
		// Remarks			: 
		/////////////////////////////////////////////////////////////////////////////////
		class Logger
		{
			public:
				bool SetFilename(string fileName);
				bool Write(string loggerString);
				bool Write(int loggerInteger);
				bool Write(long loggerLong);
				bool Write(float loggerFloat);
				bool Write(double loggerDouble);
				bool WriteLine(string loggerString);
				
				friend Logger& operator << (Logger& logger, const int& loggerInteger);
				friend Logger& operator << (Logger& logger, const long& loggerLong);
				friend Logger& operator << (Logger& logger, const float& loggerFloat);
				friend Logger& operator << (Logger& logger, const double& loggerDouble);
				friend Logger& operator << (Logger& logger, const string& loggerString);
			
				//	Default Constructor 
				Logger(); 

				//	Parametrized Constructor 
				Logger(string fileName);
		 
				//	Destructor
				~Logger();

			private:
				//	Private variables
				bool    	initialized 	= false;
				string		fileName		= "";
				ofstream	outfile;

		};	//	class Logger	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Location
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 27-02-2021
		// Description		: This class represents a specific location
		// Remarks      	:
		/////////////////////////////////////////////////////////////////////////////////
		class Location
		{
			public:
				int	Column(void);
				int Row(void);

				friend ostream& operator << (ostream& ostream, const Location& location);
				Location& operator = (Location& location);
				bool operator == (Location& location);
				bool operator != (Location& location);
			
				//	Default Constructor 
				Location(); 

				//	Parametrized Constructors 
				Location(int column, int row);
		 
				//	Destructor
				~Location();

			protected:
				//	Protected member function
				void 		_Location(int column, int row);
			private:
				//	Private variables
				int			column;
				int			row;

		};	//	class Location	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: DsmLocation
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 27-02-2021
		// Description		: This class represents a specific location for DSM maps
		// Remarks      	: It is derived from Location class
		/////////////////////////////////////////////////////////////////////////////////
		class DsmLocation : public Location
		{
			public:
				void Value(DsmLocation location, int value);
				void Value(DsmLocation location, long value);
				void Value(DsmLocation location, float value);
				void Value(DsmLocation location, double value);
				void Value(double value);
				double Value(void);
				void Walkable(bool walkable);
				bool Walkable(void);

				friend ostream& operator << (ostream& ostream, DsmLocation& location);
				DsmLocation& operator = (DsmLocation& location);
			
				//	Default Constructor 
				DsmLocation(); 

				//	Parametrized Constructors 
				DsmLocation(int column, int row);
				DsmLocation(int column, int row, int value);
				DsmLocation(int column, int row, long value);
				DsmLocation(int column, int row, float value);
				DsmLocation(int column, int row, double value);
		 
				//	Destructor
				~DsmLocation();

			protected:
				//	Protected member function
				void 		_Value(DsmLocation location, double value);				
			private:

				//	Private variables
				double		value;
				bool		walkable	= false;

		};	//	class DsmLocation	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: DsmInformation
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 26-02-2021
		// Description		: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain
		// Remarks         : 
		/////////////////////////////////////////////////////////////////////////////////	
		class DsmInformation
		{ 
			public:
				void Rows(int rows);
				void Columns(int columns);
				int Rows(void);
				int Columns(void);
				double Value(int column, int row);
				bool Value(int column, int row, double value);

				//	Default Constructor 
				DsmInformation();

				//	Parametrized Constructor 
				DsmInformation(int columns, int rows); 

				//	Destructor
				~DsmInformation();
				
			private: 
				//	Private variables
				bool    		initialized		= false;
				DsmLocation		*pLocation		= NULL; 
				int     		columns = 0, rows = 0;
				class Logger	logger;
				
		};  //  class DsmInformation
		
	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/

	

#endif	// __PABLO_AI_SUPPORT_CLASSES_H__
