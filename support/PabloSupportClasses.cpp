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
			this->initialized	= false;
			this->fileName		= "";
			
		}	//	Logger::Logger() 
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Parametrized constructors
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This family of constructors take as parameter the 
		//							location (x,y) and the location value
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	x (column)
		//							y (row)
		//							locationValue (as int, long, float or double)	
		/////////////////////////////////////////////////////////////////////////////////
		Location::Location(int x, int y, int locationValue)
		{
			this->_LocationValue(x, y, (double) locationValue);
			
		}	//	Logger::Location()
		
		Location::Location(int x, int y, long locationValue)
		{
			this->_LocationValue(x, y, (double) locationValue);
			
		}	//	Logger::Location()
		
		Location::Location(int x, int y, float locationValue)
		{
			this->_LocationValue(x, y, (double) locationValue);
			
		}	//	Logger::Location()
		
		Location::Location(int x, int y, double locationValue)
		{
			this->_LocationValue(x, y, (double) locationValue);
			
		}	//	Logger::Location()

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
		Logger::Logger(string fileName) 
		{ 
			this->SetFilename(fileName);	
			
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
			logger.SetFilename(DEFAULT_DSM_INFORMATION_FILE_NAME);
			logger.WriteLine("Default Constructor called"); 
			this->initialized  = false; 
			this->columns      = 0;
			this->rows         = 0;
			
		}	//	DsmInformation::DsmInformation()

		//	Parametrized Constructor 
		DsmInformation::DsmInformation(int columns, int rows) 
		{ 
			logger.WriteLine("Parametrized Constructor called"); 

			this->initialized  = true;
			this->columns      = columns;
			this->rows         = rows;

			this->pPixelValue	= new double[columns * rows];
			
		}	//	DsmInformation::DsmInformation()

		//	Destructor
		DsmInformation::~DsmInformation() 
		{
			logger.WriteLine("Destructor called for cleanup");  
			
			if (NULL != this->pPixelValue)
			{
				logger.WriteLine("Internal array is deallocated");  
				delete [] pPixelValue; 
			}
			else
			{
				logger.WriteLine("The internal array was NOT initialized and therefore there is no need to deallocate it");
			}
			
		}	//	DsmInformation::~DsmInformation()
		
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Write (family ofmember functions with
		//							different types of arguments
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function is used to send information (with
		//							different types of arguments) into the logger file
		// Remarks         		: Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double)
		/////////////////////////////////////////////////////////////////////////////////		
		bool Logger::Write(string loggerString)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerString;
			return true;
				
		}	//	Logger::Write()

		bool Logger::Write(int loggerInteger)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerInteger;
			return true;
			
		}	//	Logger::Write()

		bool Logger::Write(long loggerLong)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerLong;
			return true;
			
		}	//	Logger::Write()

		bool Logger::Write(float loggerFloat)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerFloat;
			return true;
			
		}	//	Logger::Write()

		bool Logger::Write(double loggerDouble)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerDouble;
			return true;
			
		}	//	Logger::Write()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: WriteLine
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function is used to send string information 
		//							(and adding - end of line - in the en into the logger 
		//							file)
		// Remarks         		: Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string))
		/////////////////////////////////////////////////////////////////////////////////	
		bool Logger::WriteLine(string loggerString)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerString << endl;
			return true;
			
		}	//	Logger::WriteLine()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: SetFilename
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function to set the filename where
		//							the event logs will be recorded (in case the object
		//							was instatiated with the default constructor)
		// Remarks         		: Returns false, if the file name could not be set
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Log file name (string)
		/////////////////////////////////////////////////////////////////////////////////	
		bool Logger::SetFilename(string fileName)
		{
			if (this->initialized == false && this->fileName == "")
			{
				this->initialized  = true;
				this->fileName		= fileName;
				this->outfile.open(fileName);	
				
				return true; 
			}
			else
				return false;
			
		}	//	Logger::SetFilename()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: LocationValue
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function returns the location value
		// Remarks         		: Returns the location value
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		double Location::LocationValue(void)
		{
			return (this->locationValue);
			
		}	//	Location::LocationValue()		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Walkable
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function sets the walkability
		//							of the location
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: true, if the location is walkable, 
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		void Location::Walkable(bool walkable)
		{
			this->walkable	= walkable;
			
		}	//	Location::Walkable()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Walkable
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function returns the walkability
		//							of the location
		// Remarks         		: Returns true, if the location is walkable
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		bool Location::Walkable(void)
		{
			return (this->walkable);
			
		}	//	Location::Walkable()	
		
int DsmInformation::Rows(void)
{
    return (this->rows);
    
}   //  DsmInformation::Rows()
 
int DsmInformation::Columns(void)
{
    return (this->columns);
    
}   //  DsmInformation::Columns()

void DsmInformation::Rows(int rows)
{
	logger.Write("Called rows(");
	logger.Write(rows);
	logger.WriteLine(")");

    this->rows	= rows;
    
    if (this->initialized == false && this->Columns() != 0)
    {
    	logger.Write("Initializing internal array (");
    	logger.Write(this->Columns());
    	logger.Write("x");
    	logger.Write(rows);
    	logger.WriteLine(")");
        this->pPixelValue	= new double[this->Columns() * rows];   
        this->initialized	= true; 
    }
    
}   //  DsmInformation::Rows()

void DsmInformation::Columns(int columns)
{
	logger.Write("Called columns(");
	logger.Write(columns);
	logger.WriteLine(")");
	
    this->columns	= columns;
    
    if (this->initialized == false && this->Rows() != 0)
    {
    	logger.Write("Initializing internal array (");
    	logger.Write(columns);
    	logger.Write("x");
    	logger.Write(this->Rows());
    	logger.WriteLine(")");
        this->pPixelValue	= new double[columns * this->Rows()];  
        this->initialized	= true; 
    }
    
}   //  DsmInformation::Columns()

double DsmInformation::PixelValue(int row, int column)
{
    return (this->pPixelValue[row*this->Columns()+column]);
    
}   //  DsmInformation::PixelValue()

bool DsmInformation::PixelValue(int row, int column, double pixelValue)
{
	if (row > this->Rows())
	{
		logger << "Input row: " << row << " is greater than the maximum number of rows: " << this->Rows() << "\n";
		return false;
	} 
	if (column > this->Columns())
	{
		logger << "Input column: " << column << " is greater than the maximum number of columns: " << this->Columns() << "\n";
		return false;
	}
	
	this->pPixelValue[this->Columns() * row + column]	=  pixelValue;
	logger << "Values of [" << column << "," << row << "] = " << pixelValue << "\n";
	
	return true;
	
}	//	DsmInformation::PixelValue()




		
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
		Logger& operator << (Logger& logger, const string& loggerString)
		{
			logger.Write(loggerString);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const int& loggerInteger)
		{
			logger.Write(loggerInteger);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const long& loggerLong)
		{
			logger.Write(loggerLong);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const float& loggerFloat)
		{
			logger.Write(loggerFloat);
			
			return logger;
			
		}	//	Logger& operator <<

		Logger& operator << (Logger& logger, const double& loggerDouble)
		{
			logger.Write(loggerDouble);
			
			return logger;
			
		}	//	Logger& operator <<
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: << operator (family of overloaded operators with
		//							different types of arguments
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Operator description	: This operator (<<) is used to overload the default << 
		//							operator
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double)
		/////////////////////////////////////////////////////////////////////////////////
		ostream& operator << (ostream& ostream, const Location& location)
		{
         	ostream << "location [" << location.x << ", " << location.y << "] = " << location.locationValue;
         	return ostream;  
         	
		}	//	ostream& operator <<
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Operator description	: This operator (=) is used to assign a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		Location& Location::operator = (const Location& location)
		{
			if (this != &location)
			{
				this->_LocationValue(location.x, location.y, location.locationValue);
				this->walkable	= location.walkable;
			}
			
			return (*this);
         	
		}	//	Location::operator =
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: == operator (location equality operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Operator description	: This operator (==) is used to compare a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Location::operator == (const Location& location)
		{
			return ((this->x == location.x) && (this->y == location.y));
			
		}	//	bool Location::operator ==
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: == operator (location inequality operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Operator description	: This operator (==) is used to compare a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Location::operator != (const Location& location)
		{
			return ((this->x != location.x) || (this->y != location.y));
			
		}	//	bool Location::operator !=

	/*
		****************************************************************************
		* PRIVATE CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: _LocationValue
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This private member function takes as parameter the 
		//							location (x,y) and sets its location value
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	x (column)
		//							y (row)
		//							locationValue	
		/////////////////////////////////////////////////////////////////////////////////	
		void Location::_LocationValue(int x, int y, double locationValue)
		{
			this->x				= x;
			this->y				= y;
			this->locationValue	= locationValue;
			this->walkable		= false;
			
		}	//	Location::_LocationValue()	



