//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloSupportClasses.c
//
// Version:			01.00
//
// Description:		Support classes for the AI home excercise source file
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

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "PabloSupportClasses.h"
	
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
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
		/*---- data declarations ---------------------------------------------------*/		
		/*---- function prototypes -------------------------------------------------*/	

	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	:
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Logger::Logger() 
		{ 
			this->bInitialized  = false;
			this->sFilename		= "";
			
		}	//	Logger::Logger() 

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This constructor takes as parameter the filename where
		//							the event logs will be recorded
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Log file name (string)
		/////////////////////////////////////////////////////////////////////////////////
		Logger::Logger(string sFilename) 
		{ 
			this->setFilename(sFilename);	
			
		}	//	Logger::Logger()      

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	:
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Logger::~Logger() 
		{ 
			this->outfile.close();
			
		}	//	Logger::~Logger()
			
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents the information taken from a DSM file
		//							A DSM (Digital Surface Model) is a computer graphics 
		//							representation of elevation data to represent terrain
		// Function description	:
		// Remarks         		: Set the default logger file to "DsmInformation.txt"
		//							in "output" sub-directory
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		DsmInformation::DsmInformation() 
		{ 
			logger.setFilename(DEFAULT_DSM_INFORMATION_FILE_NAME);
			logger.writeLine("Default Constructor called"); 
			this->bInitialized  = false; 
			this->iColumns      = 0;
			this->iRows         = 0;
			
		}	//	DsmInformation::DsmInformation()

		//	Parametrized Constructor 
		DsmInformation::DsmInformation(int iColumns, int iRows) 
		{ 
			logger.writeLine("Parametrized Constructor called"); 

			this->bInitialized  = true;
			this->iColumns      = iColumns;
			this->iRows         = iRows;

			pdPixelValue  = new double[iColumns * iRows];
			
		}	//	DsmInformation::DsmInformation()

		//	Destructor
		DsmInformation::~DsmInformation() 
		{
			logger.writeLine("Destructor called for cleanup");  
			
			if (pdPixelValue != NULL)
			{
				logger.writeLine("Internal array is deallocated");  
				delete [] pdPixelValue; 
			}
			else
			{
				logger.writeLine("The internal array was NOT initialized and therefore there is no need to deallocate it");
			}
			
		}	//	DsmInformation::~DsmInformation()
		
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: write (family of overloaded operators with
		//							different types of arguments
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Operator description	: This member function is used to send information (with
		//							different types of variables) into the logger file
		// Remarks         		: Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double)
		/////////////////////////////////////////////////////////////////////////////////		
		bool Logger::write(string sString)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << sString;
			return true;
				
		}	//	Logger::write()

		bool Logger::write(int iInteger)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << iInteger;
			return true;
			
		}	//	Logger::write()

		bool Logger::write(long lLong)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << lLong;
			return true;
			
		}	//	Logger::write()

		bool Logger::write(float fFloat)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << fFloat;
			return true;
			
		}	//	Logger::write()

		bool Logger::write(double dDouble)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << dDouble;
			return true;
			
		}	//	Logger::write()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: writeLine
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Operator description	: This member function is used to send string information 
		//							(and adding - end of line - in the en into the logger 
		//							file)
		// Remarks         		: Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string))
		/////////////////////////////////////////////////////////////////////////////////	
		bool Logger::writeLine(string sLine)
		{
			if (this->bInitialized == false)
				return false;
				
			this->outfile << sLine << endl;
			return true;
			
		}	//	Logger::writeLine()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: setFilename
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Operator description	: This member function to set the filename where
		//							the event logs will be recorded (in case the object
		//							was instatiated with the default constructor)
		// Remarks         		: Returns false, if the file name could not be set
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Log file name (string)
		/////////////////////////////////////////////////////////////////////////////////	
		bool Logger::setFilename(string sFilename)
		{
			if (this->bInitialized == false && this->sFilename == "")
			{
				this->bInitialized  = true;
				this->sFilename		= sFilename;
				this->outfile.open(sFilename);	
				
				return true; 
			}
			else
				return false;
			
		}	//	Logger::setFilename()		

		
	/*
		****************************************************************************
		* PUBLIC CLASS OPERATOR DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: << operator (family of overloaded operators with
		//							different types of arguments
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Operator description	: This operator (<<) is used to send information (with
		//							different types of variables) into the logger file
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double)
		/////////////////////////////////////////////////////////////////////////////////
		Logger& operator << (Logger& logger, const string& sString)
		{
			logger.write(sString);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const int& iInteger)
		{
			logger.write(iInteger);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const long& lLong)
		{
			logger.write(lLong);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const float& fFloat)
		{
			logger.write(fFloat);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const double& dDouble)
		{
			logger.write(dDouble);
			
			return logger;
			
		}	//	Logger& operator <<


	/*
		****************************************************************************
		* PRIVATE CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
	
	




int DsmInformation::rows(void)
{
    return (this->iRows);
    
}   //  DsmInformation::rows()
 
int DsmInformation::columns(void)
{
    return (this->iColumns);
    
}   //  DsmInformation::columns()

void DsmInformation::rows(int iRows)
{
	logger.write("Called rows(");
	logger.write(iRows);
	logger.writeLine(")");

    this->iRows = iRows;
    
    if (this->bInitialized == false && this->columns() != 0)
    {
    	logger.write("Initializing internal array (");
    	logger.write(this->columns());
    	logger.write("x");
    	logger.write(iRows);
    	logger.writeLine(")");
        this->pdPixelValue  = new double[this->columns() * iRows];   
        this->bInitialized  = true; 
    }
    
}   //  DsmInformation::rows()

void DsmInformation::columns(int iColumns)
{
	logger.write("Called columns(");
	logger.write(iColumns);
	logger.writeLine(")");
	
    this->iColumns  = iColumns;
    
    if (this->bInitialized == false && this->rows() != 0)
    {
    	logger.write("Initializing internal array (");
    	logger.write(iColumns);
    	logger.write("x");
    	logger.write(this->rows());
    	logger.writeLine(")");
        this->pdPixelValue  = new double[iColumns * this->rows()];  
        this->bInitialized  = true; 
    }
    
}   //  DsmInformation::columns()

double DsmInformation::pixelValue(int row, int column)
{
    return (this->pdPixelValue[row*this->columns()+column]);
    
}   //  DsmInformation::pixelValue()

bool DsmInformation::pixelValue(int row, int column, double dPixelValue)
{
	if (row > this->rows())
	{
		logger << "Input row: " << row << " is greater than the maximum number of rows: " << this->rows() << "\n";
		return false;
	} 
	if (column > this->columns())
	{
		logger << "Input column: " << column << " is greater than the maximum number of columns: " << this->columns() << "\n";
		return false;
	}
	
	this->pdPixelValue[this->columns() * row + column]	=  dPixelValue;
	logger << "Values of [" << column << "," << row << "] = " << dPixelValue << "\n";
	
	return true;
	
}	//	DsmInformation::pixelValue()

