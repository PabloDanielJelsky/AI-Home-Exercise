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
//	01-03-2021	Pablo Daniel Jelsky		01			02			Added LineOfSight() member function to DsmInformation class and added template use
//	02-03-2021	Pablo Daniel Jelsky		01			03			Added Graphic class
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
		/*---- data definitions ---------------------------------------------------*/
		static rgb colorToRgb [] = 
		{
			{MAXIMUM_COLOR, NO_COLOR, NO_COLOR},			// COLOR_RED
			{NO_COLOR, MAXIMUM_COLOR, NO_COLOR},			// COLOR_GREEN
			{NO_COLOR, NO_COLOR, MAXIMUM_COLOR},			// COLOR_BLUE
			{MAXIMUM_COLOR, MAXIMUM_COLOR, MAXIMUM_COLOR},	// COLOR_WHITE
			{NO_COLOR, NO_COLOR, NO_COLOR},					// COLOR_BLACK
			{MAXIMUM_COLOR, MAXIMUM_COLOR, NO_COLOR},		// COLOR_YELLOW
			{NO_COLOR, MAXIMUM_COLOR, MAXIMUM_COLOR},		// COLOR_CYAN
			{MAXIMUM_COLOR, NO_COLOR, MAXIMUM_COLOR}		// COLOR_MAGENTA
		};
		
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
			this->filename		= "";
			
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
			this->elevation	= INVALID_DSM_ELEVATION;
			
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
			this->elevation	= INVALID_DSM_ELEVATION;
			
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
		//							elevation
		/////////////////////////////////////////////////////////////////////////////////
		template <class GenericType> 
		DsmLocation::DsmLocation(int column, int row, GenericType genericTypeElevation)
		{
			this->_Location(column, row);
			this->elevation	= (double) genericTypeElevation;
			
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
		Logger::Logger(string filename) 
		{ 
			this->Filename(filename);	
			
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
			logger.Filename(DEFAULT_DSM_INFORMATION_FILE_NAME);
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
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents a graphic
		// Function description	:
		// Remarks         		: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Graphic::Graphic() 
		{ 
			this->initialized	= false; 
			this->columns		= 0;
			this->rows			= 0;
			
			if (NULL == pPngObject)
				pPngObject	= new pngwriter(0, 0, 0, "");
			
		}	//	Graphic::Graphic()

		//	Parametrized Constructor 
		Graphic::Graphic(int columns, int rows) 
		{ 
			this->initialized	= true;
			this->columns		= columns;
			this->rows			= rows;
			
			if (NULL == pPngObject)
				pPngObject	= new pngwriter(columns, rows, 0, "");
			
		}	//	Graphic::Graphic()

		//	Destructor
		Graphic::~Graphic() 
		{
			if (NULL != pPngObject)
				delete pPngObject;
			
		}	//	Graphic::~Graphic()
		
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Write 
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function is used to send information (with
		//							different types of arguments) into the logger file
		// Remarks         		: Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file
		/////////////////////////////////////////////////////////////////////////////////		
		template <class GenericType> 
		bool Logger::Write(GenericType loggerGenericType)
		{
			if (this->initialized == false)
				return false;
				
			this->outfile << loggerGenericType;
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
		// Function				: Filename
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
		bool Logger::Filename(string filename)
		{
			if (this->initialized == false && this->filename == "")
			{
				this->initialized	= true;
				this->filename		= filename;
				this->outfile.open(filename);	
				
				return true; 
			}
			else
				return false;
			
		}	//	Logger::Filename()	
		
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
		// Class name			: Location
		// Function				: LineIntercept
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns the line intercept point
		//							given 2 points
		// Remarks         		: Returns the line intercept point
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: 	
		/////////////////////////////////////////////////////////////////////////////////	
		double Location::LineIntercept(Location point)
		{
			double	intercept	= (this->Row() - (this->LineSlope(point) * this->Column()));
		
			return intercept;
			
		}	//	Location::LineIntercept()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: LineSlope
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns the line slope
		//							given 2 points
		// Remarks         		: Returns the line slope
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: 	
		/////////////////////////////////////////////////////////////////////////////////	
		double Location::LineSlope(Location point)
		{
			double	slope		= (this->Row() - point.Row()) / (this->Column() - point.Column());
			
			return slope;
			
		}	//	Location::LineSlope()		
		
			
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This is a member function that sets the 
		//							location and elevation
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	location (as DsmLocation)
		//							elevation	
		/////////////////////////////////////////////////////////////////////////////////	
		template <class GenericType> 
		void DsmLocation::Elevation(DsmLocation location, GenericType genericTypeElevation)
		{
			this->_Elevation(location, genericTypeElevation);
			
		}	//	DsmLocation::Elevation()
				
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This is a member functions that sets its elevation 
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	elevation (as double)	
		/////////////////////////////////////////////////////////////////////////////////		
		void DsmLocation::Elevation(double elevation)
		{
			this->elevation	= elevation;
			
		}	//  DsmLocation::Elevation()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function returns the location elevation
		// Remarks         		: Returns the location elevation
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		double DsmLocation::Elevation(void)
		{
			return (this->elevation);
			
		}	//	DsmLocation::Elevation()		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function defines if the location is an obstacle
		//							of the location
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: true, if the location is an obstacle, 
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		void DsmLocation::Obstacle(bool theLocationIsAnObstacle)
		{
			this->obstacle	= theLocationIsAnObstacle;
			
		}	//	DsmLocation::Obstacle()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function returns if the location is an
		//							obstacle
		// Remarks         		: Returns true, if the location is an obstacle
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None	
		/////////////////////////////////////////////////////////////////////////////////	
		bool DsmLocation::Obstacle(void)
		{
			return this->obstacle;
			
		}	//	DsmLocation::Obstacle()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: LineOfSight
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns the visibility between
		//							two location (line of sight = LOS)
		// Remarks         		: Returns true, if the locations are visible between them
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: pointA and pointB (as Location)
		/////////////////////////////////////////////////////////////////////////////////	
		bool DsmInformation::LineOfSight(Location pointA, Location pointB)
		{
			double	slope, intercept;
			int		column, row;
			
			slope		= pointA.LineSlope(pointB);
			intercept	= pointA.LineIntercept(pointB);
			
			if (pointA.Column() == pointB.Column())
			{
				//	Both points are vertical one to the other
			}
			else if (pointA.Column() > pointB.Column())
			{
				for (column = pointB.Column(); column <= pointA.Column(); column++)
				{
					row	= (int) (slope * column) + intercept;
					if (false == this->Obstacle(column, row))
						return false;
				}
			}
			else
			{
				for (column = pointA.Column(); column <= pointB.Column(); column++)
				{
					row	= (int) (slope * column) + intercept;
					if (false == this->Obstacle(column, row))
						return false;
				}
			}
			
			return true;
			
		}	//	DsmInformation::LineOfSight()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns DSM map number of rows
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		int DsmInformation::Rows(void)
		{
			return (this->rows);
			
		}   //  DsmInformation::Rows()
 
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Columns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns DSM map number of columns
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		int DsmInformation::Columns(void)
		{
			return (this->columns);
			
		}   //  DsmInformation::Columns()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the DSM map number of rows
		// Remarks         		: If also the columns are initialized, creates the
		//							internal array
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of rows
		/////////////////////////////////////////////////////////////////////////////////	
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
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Columns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the DSM map number of columns
		// Remarks         		: If also the rows are initialized, creates the
		//							internal array
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of columns
		/////////////////////////////////////////////////////////////////////////////////
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

 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns the elevation of the column/row
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column and row
		/////////////////////////////////////////////////////////////////////////////////	
		double DsmInformation::Elevation(int column, int row)
		{
			return ((this->pLocation[row*this->Columns()+column]).Elevation());
			
		}   //  DsmInformation::Elevation()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the elevation of the column/row
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row and elevation to be set
		/////////////////////////////////////////////////////////////////////////////////	
		bool DsmInformation::Elevation(int column, int row, double elevation)
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
			
			
			(this->pLocation[this->Columns() * row + column]).Elevation(elevation);
			logger << "[" << column << "," << row << "] elevation set to " << elevation << "\n";
			
			return true;
			
		}	//	DsmInformation::Elevation()

 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function defines location as an obstacle
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row and boolean deciding if the location could
		//							is an obstacle
		/////////////////////////////////////////////////////////////////////////////////	
		bool DsmInformation::Obstacle(int column, int row, bool theLocationIsAnObstacle)
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
			
			
			(this->pLocation[this->Columns() * row + column]).Obstacle(theLocationIsAnObstacle);
			if (true == theLocationIsAnObstacle)
				logger << "[" << column << "," << row << "] was set to be an obstacle\n";
			else
				logger << "[" << column << "," << row << "] was set not to be an obstacle\n";
			
			return true;
			
		}	//	DsmInformation::Obstacle()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns if the location is an
		//							obstacle or not
		// Remarks         		: Returns true, if the location is an obstacle,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row 
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::Obstacle(int column, int row)
		{
			return ((this->pLocation[row*this->Columns()+column]).Obstacle());
			
		}   //  DsmInformation::Obstacle()
		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Create
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function creates the graphic with the 
		//							pre-inserted information
		// Remarks         		: Returns true, if it succeeded creating the graphic file,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic type
		/////////////////////////////////////////////////////////////////////////////////	
		bool Graphic::Create(graphicType typeOfGraphic)
		{
			if (false == this->initialized)
				return false;
				
			switch (typeOfGraphic)
			{
				case GRAPHIC_TYPE_PNG:
					{
						class Location from(3,3);
						class Location to(100, 100);
						this->Line(from, to, COLOR_WHITE);
						//	Close the instance of the class, and write the image to disk.
						(*pPngObject).close();
					}
					break;
					
				case GRAPHIC_TYPE_GEOTIFF:
					//	close out GeoTIFF dataset
					GDALClose(this->geotiffDataset);
					break;
				default:
					return false;
			}
				
			return true;
			
		}   //  Graphic::Create()		

		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function returns the graphic number of rows
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		int Graphic::Rows(void)
		{
			return this->rows;
			
		}   //  Graphic::Rows()
 
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Columns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function returns the graphic of columns
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		int Graphic::Columns(void)
		{
			return this->columns;
			
		}   //  Graphic::Columns()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function sets the graphic number of rows
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of rows
		/////////////////////////////////////////////////////////////////////////////////	
		void Graphic::Rows(int rows)
		{
			this->rows	= rows;
			
			if (this->initialized == false && this->Columns() != 0 && this->filename != "")
			{
				this->initialized	= true; 
				this->_Update();
			}
				
		}   //  Graphic::Rows()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Columns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function sets the graphic number of columns
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of columns
		/////////////////////////////////////////////////////////////////////////////////
		void Graphic::Columns(int columns)
		{
			this->columns	= columns;
			
			if (this->initialized == false && this->Rows() != 0 && this->filename != "")
			{
				this->initialized	= true; 
				this->_Update();
			}
			
		}   //  Graphic::Columns()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Filename
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function sets the graphic file name
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic file name
		/////////////////////////////////////////////////////////////////////////////////
		void Graphic::Filename(string filename)
		{
			this->filename	= filename;
			
			if (this->initialized == false && this->Rows() != 0 && this->Columns() != 0)
			{
				this->initialized	= true; 
				this->_Update();
			}
			
		}   //  Graphic::Filename()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Type
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function sets the graphic type
		// Remarks         		: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic file type
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Line(class Location from, class Location to, color lineColor)
		{
			if (false == this->initialized)
				return false;
				
			(*this->pPngObject).line(from.Column(), from.Row(), to.Column(), to.Row(), colorToRgb[lineColor].red, colorToRgb[lineColor].green, colorToRgb[lineColor].blue);
			return true;
			
		}   //  Graphic::Line()
		
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
         	ostream << "location [" << location.Column() << ", " << location.Row() << "] = " << location.Elevation();
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
				this->Elevation(location, location.Elevation());
				this->Obstacle(location.Obstacle());
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
			return (this->Column() == location.Column()) && (this->Row() == location.Row());
			
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
			return (this->Column() != location.Column()) || (this->Row() != location.Row());
			
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
		// Function				: _Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This private member function takes as parameter the 
		//							location (column, row) and sets its elevation
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	location (as Location)
		//							elevation (as double)	
		/////////////////////////////////////////////////////////////////////////////////	
		void DsmLocation::_Elevation(DsmLocation location, double elevation)
		{
			this->_Location(location.Column(), location.Row());
			this->Elevation(elevation);
			this->Obstacle(false);
			
		}	//	DsmLocation::_Elevation()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: _Update
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This private member function updates the output graphic
		//							file that is being created
		// Remarks         		: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		void Graphic::_Update(void)
		{
			string	pngFilename		= this->filename + ".png";
			string	geoTiffFilename	= this->filename + ".tif";
			
			if (false == this->initialized)
				return;
				
			//	Update .png graphic file
			(*this->pPngObject).resize(this->Columns(), this->Rows());
			(*this->pPngObject).pngwriter_rename(pngFilename.c_str());
			//	Update GeoTIFF graphic file
				/* create GDAL driver object whose Create() method will be used
				   * to create Geotiff writer object. Get geotransform using
				   * 6-element array from above. Read projection from GRIB
				   * file and use SetProjection() method to set the projection
				   * of the Geotiff object.
				   */
 			this->driverGeotiff 	= GetGDALDriverManager()->GetDriverByName("GTiff");
  			this->geotiffDataset	= this->driverGeotiff->Create(geoTiffFilename.c_str(), this->Columns(), this->Rows(), 1, GDT_Float32, NULL);

			
		}	//	Graphic::_Update()	
		

		



