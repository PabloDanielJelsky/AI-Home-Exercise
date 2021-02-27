//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloSupportClasses.h
//
// Version:			01.00
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
		// Description		: This class represents a specific location for DSM maps
		// Remarks      	:
		/////////////////////////////////////////////////////////////////////////////////
		class Location
		{
			public:
				double LocationValue(void);
				void Walkable(bool walkable);
				bool Walkable(void);

				friend ostream& operator << (ostream& ostream, const Location& location);
				Location& operator = (const Location& location);
				bool operator == (const Location& location);
				bool operator != (const Location& location);
			
				//	Default Constructor 
//				Location(); 

				//	Parametrized Constructors 
				Location(int x, int y, int locationValue);
				Location(int x, int y, long locationValue);
				Location(int x, int y, float locationValue);
				Location(int x, int y, double locationValue);
		 
				//	Destructor
				~Location();

			private:
				//	Private member function
				void 		_LocationValue(int x, int y, double locationValue);
				//	Private variables
				int			x;
				int			y;
				double		locationValue;
				bool		walkable	= false;

		};	//	class Location	
		
		
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
				double PixelValue(int row, int column);
				bool PixelValue(int row, int column, double pixelValue);

				//	Default Constructor 
				DsmInformation();

				//	Parametrized Constructor 
				DsmInformation(int columns, int rows); 

				//	Destructor
				~DsmInformation();
				
			private: 
				//	Private variables
				bool    		initialized = false;
				double  		*pPixelValue = NULL; 
				int     		columns = 0, rows = 0;
				class Logger	logger;
				
		};  //  class DsmInformation
		
	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/

	

#endif	// __PABLO_AI_SUPPORT_CLASSES_H__
