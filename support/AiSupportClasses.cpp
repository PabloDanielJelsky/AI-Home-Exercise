//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportClasses.c
//
// Version:			01.01
//
// Description:		Support classes for the AI home excercise source file
//
// Author:			Pablo Daniel Jelsky
//
// Copyright:		
//
// Remarks:			
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

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "AiSupportClasses.h"
	
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
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/
	
	/*
		****************************************************************************
		* PRIVATE FUNCTION DEFINITIONS
		****************************************************************************
	*/	
	
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
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This constructor will create a non valid object
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location::Location()
		{
			this->_Location(INVALID_COLUMN, INVALID_ROW);
			
		}	//	Location::Location()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This constructors take as parameter the location
		//							(column, row)
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		/////////////////////////////////////////////////////////////////////////////////
		Location::Location(int column, int row)
		{
			this->_Location(column, row);
			
		}	//	Location::Location()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This destructor does not do anything as for today
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location::~Location()
		{
			
		}	//	Location::~Location()
		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Default constructors
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This constructor will create a non valid object
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::DsmLocation()
		{
			this->_Location(INVALID_COLUMN, INVALID_ROW);
			this->value	= INVALID_DSM_VALUE;
			
		}	//	DsmLocation::DsmLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This constructor will create a non valid object
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::DsmLocation(int column, int row)
		{
			this->_Location(column, row);
			this->value	= INVALID_DSM_VALUE;
			
		}	//	DsmLocation::DsmLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Parametrized constructors
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This family of constructors will create a valid object
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		//							value (as int, long, float or double)	
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::DsmLocation(int column, int row, int value)
		{
			this->_Location(column, row);
			this->value	= (double) value;
			
		}	//	DsmLocation::DsmLocation()
		
		DsmLocation::DsmLocation(int column, int row, long value)
		{
			this->_Location(column, row);
			this->value	= (double) value;
			
		}	//	DsmLocation::DsmLocation()
		
		DsmLocation::DsmLocation(int column, int row, float value)
		{
			this->_Location(column, row);
			this->value	= (double) value;
			
		}	//	DsmLocation::DsmLocation()
		
		DsmLocation::DsmLocation(int column, int row, double value)
		{
			this->_Location(column, row);
			this->value	= (double) value;
			
		}	//	DsmLocation::DsmLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This destructor does not do anything as for today
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::~DsmLocation()
		{
			
		}	//	DsmLocation::~DsmLocation()

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
			this->initialized	= false; 
			this->columns		= 0;
			this->rows			= 0;
			
		}	//	DsmInformation::DsmInformation()

		//	Parametrized Constructor 
		DsmInformation::DsmInformation(int columns, int rows) 
		{ 
			logger.WriteLine("Parametrized Constructor called"); 

			this->initialized	= true;
			this->columns		= columns;
			this->rows			= rows;

			this->pLocation		= new DsmLocation[columns * rows];
			
		}	//	DsmInformation::DsmInformation()

		//	Destructor
		DsmInformation::~DsmInformation() 
		{
			logger.WriteLine("Destructor called for cleanup");  
			
			if (NULL != this->pLocation)
			{
				logger.WriteLine("Internal array is deallocated");  
				delete [] pLocation; 
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
				this->initialized	= true;
				this->fileName		= fileName;
				this->outfile.open(fileName);	
				
				return true; 
			}
			else
				return false;
			
		}	//	Logger::SetFilename()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Modify
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function modifies the location
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		/////////////////////////////////////////////////////////////////////////////////
		void Location::Modify(int column, int row)
		{
			this->_Location(column, row);
			
		}	//	Location::Modify()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Column
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns column location
		// Remarks         		: Returns the column location
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		int Location::Column(void)
		{
			return (this->column);
			
		}	//	Location::Column()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Row
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns row location
		// Remarks         		: Returns the row location
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		int Location::Row(void)
		{
			return (this->row);
			
		}	//	Location::Row()	
			
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Value
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This is a family of member functions that set the 
		//							location and value (as int, long, float, double)
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	location (as DsmLocation)
		//							value (as int, long, float or double)	
		/////////////////////////////////////////////////////////////////////////////////	
		void DsmLocation::Value(DsmLocation location, int value)
		{
			this->_Value(location, value);
			
		}	//	DsmLocation::Value()
		
		void DsmLocation::Value(DsmLocation location, long value)
		{
			this->_Value(location, value);
			
		}	//	DsmLocation::Value()
		
		void DsmLocation::Value(DsmLocation location, float value)
		{
			this->_Value(location, value);
			
		}	//	DsmLocation::Value()
		
		void DsmLocation::Value(DsmLocation location, double value)
		{
			this->_Value(location, value);
			
		}	//	DsmLocation::Value()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Value
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This is a member functions that sets its value 
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	value (as double)	
		/////////////////////////////////////////////////////////////////////////////////		
		void DsmLocation::Value(double value)
		{
			this->value	= value;
			
		}	//  DsmLocation::Value()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Value
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function returns the location value
		// Remarks         		: Returns the location value
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		double DsmLocation::Value(void)
		{
			return (this->value);
			
		}	//	DsmLocation::Value()		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
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
		void DsmLocation::Walkable(bool walkable)
		{
			this->walkable	= walkable;
			
		}	//	DsmLocation::Walkable()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
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
		bool DsmLocation::Walkable(void)
		{
			return (this->walkable);
			
		}	//	DsmLocation::Walkable()	
		
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
        this->pLocation		= new DsmLocation[this->Columns() * rows];   
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
        this->pLocation		= new DsmLocation[columns * this->Rows()];  
        this->initialized	= true; 
    }
    
}   //  DsmInformation::Columns()

double DsmInformation::Value(int column, int row)
{
    return ((this->pLocation[row*this->Columns()+column]).Value());
    
}   //  DsmInformation::Value()

bool DsmInformation::Value(int column, int row, double value)
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
	
	
	(this->pLocation[this->Columns() * row + column]).Value(value);
	logger << "[" << column << "," << row << "] set to " << value << "\n";
	
	return true;
	
}	//	DsmInformation::Value()

bool DsmInformation::Walkable(int column, int row, bool walkable)
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
	
	
	(this->pLocation[this->Columns() * row + column]).Walkable(walkable);
	if (walkable == true)
		logger << "[" << column << "," << row << "] set to true\n";
	else
		logger << "[" << column << "," << row << "] set to false\n";
	
	return true;
	
}	//	DsmInformation::Walkable()

bool DsmInformation::Walkable(int column, int row)
{
    return ((this->pLocation[row*this->Columns()+column]).Walkable());
    
}   //  DsmInformation::Walkable()


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
		// Function				: << operator
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Operator description	: This operator (<<) is used to overload the default << 
		//							operator
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double)
		/////////////////////////////////////////////////////////////////////////////////
		ostream& operator << (ostream& ostream, Location& location)
		{
         	ostream << "location [" << location.Column() << ", " << location.Row() << "]";
         	return ostream;  
         	
		}	//	ostream& operator <<
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: << operator
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
		ostream& operator << (ostream& ostream, DsmLocation& location)
		{
         	ostream << "location [" << location.Column() << ", " << location.Row() << "] = " << location.Value();
         	return ostream;  
         	
		}	//	ostream& operator <<
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Operator description	: This operator (=) is used to assign a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		Location& Location::operator = (Location& location)
		{
			if (this != &location)
				this->_Location(location.Column(), location.Row());
			
			return (*this);
         	
		}	//	Location::operator =
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Operator description	: This operator (=) is used to assign a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation& DsmLocation::operator = (DsmLocation& location)
		{
			if (this != &location)
			{
				this->_Value(location, location.Value());
				this->walkable	= location.walkable;
			}
			
			return (*this);
         	
		}	//	DsmLocation::operator =
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: == operator (location equality operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Operator description	: This operator (==) is used to compare a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Location::operator == (Location& location)
		{
			return ((this->Column() == location.Column()) && (this->Row() == location.Row()));
			
		}	//	bool Location::operator ==
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: == operator (location inequality operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Operator description	: This operator (==) is used to compare a location to another
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Location::operator != (Location& location)
		{
			return ((this->Column() != location.Column()) || (this->Row() != location.Row()));
			
		}	//	bool Location::operator !=

	/*
		****************************************************************************
		* PRIVATE CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: _Location
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This private member function takes as parameter the 
		//							location (column, row) 
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		/////////////////////////////////////////////////////////////////////////////////	
		void Location::_Location(int column, int row)
		{
			this->column	= column;
			this->row		= row;
			
		}	//	Location::_Location()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: _Value
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This private member function takes as parameter the 
		//							location (column, row) and sets its location value
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	location (as Location)
		//							value (as double)	
		/////////////////////////////////////////////////////////////////////////////////	
		void DsmLocation::_Value(DsmLocation location, double value)
		{
			this->_Location(location.Column(), location.Row());
			this->value		= value;
			this->walkable	= false;
			
		}	//	DsmLocation::_Value()	



