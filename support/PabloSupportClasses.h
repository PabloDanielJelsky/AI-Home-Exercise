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
				bool setFilename(string sFilename);
				bool write(string sString);
				bool write(int iInteger);
				bool write(long lLong);
				bool write(float fFloat);
				bool write(double dDouble);
				bool writeLine(string sLine);
				
				friend Logger& operator << (Logger& logger, const int& iInteger);
				friend Logger& operator << (Logger& logger, const long& lLong);
				friend Logger& operator << (Logger& logger, const float& fFloat);
				friend Logger& operator << (Logger& logger, const double& dDouble);
				friend Logger& operator << (Logger& logger, const string& sString);
			
				//	Default Constructor 
				Logger(); 

				//	Parametrized Constructor 
				Logger(string sFilename);
		 
				//	Destructor
				~Logger();

			private:
				bool    	bInitialized 	= false;
				string		sFilename		= "";
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
				
				double walkable(void);
				walkable(

				friend ostream& operator << (ostream& ostream, const Location& location);
				Location& operator = (const Location& location);
				Location& operator == (const Location& location);
				Location& operator != (const Location& location);
			
				//	Default Constructor 
				Location(); 

				//	Parametrized Constructors 
				Location(int x, int y, int locationValue);
				Location(int x, int y, long locationValue);
				Location(int x, int y, float locationValue);
				Location(int x, int y, double locationValue);
		 
				//	Destructor
				~Location();

			private:
				bool    	initialized	= false;
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
				void rows(int rows);
				void columns(int columns);
				int rows(void);
				int columns(void);
				double pixelValue(int row, int column);
				bool pixelValue(int row, int column, double pixelValue);

				//	Default Constructor 
				DsmInformation();

				//	Parametrized Constructor 
				DsmInformation(int iColumns, int iRows); 

				//	Destructor
				~DsmInformation();
				
			private: 
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
