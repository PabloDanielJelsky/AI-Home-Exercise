//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportClasses.cpp
//
// Version:			01.05
//
// Description:		Support classes for the AI home excercise source file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
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
//	05-03-2021	Pablo Daniel Jelsky		01			04			Modification of internal representation
//																	of pixels.
//																The internal representation of the DSM map in the DsmInformation class is that 
//																the south-west (down-left) pixel is (0,0), and all the pixels are positive, 
//																and therefore, pixel in the north-east (up-right) is (Columns-1, Rows-1), where 
//																Columns is the total number of columns of the DSM file, and Rows is the total
//																number of rows of the DSM file
//	06-03-2021	Pablo Daniel Jelsky		01			05			Added Timer class (for profiling and Tick() functions
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
		Location AI_SUPPORT_CLASSES_DefaultLocation (DEFAULT_LOCATION_COLUMN, DEFAULT_LOCATION_ROW);
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
			{NO_COLOR, NO_COLOR, NO_COLOR},					//	AI_SUPPORT_CLASSES_COLOR_BLACK,			 	(0,0,0)
			{MAXIMUM_COLOR, NO_COLOR, NO_COLOR},			//	AI_SUPPORT_CLASSES_COLOR_RED,				(255,0,0)
			{NO_COLOR, MAXIMUM_COLOR, NO_COLOR},			//	AI_SUPPORT_CLASSES_COLOR_LIME,				(0,255,0)
			{NO_COLOR, NO_COLOR, MAXIMUM_COLOR},			//	AI_SUPPORT_CLASSES_COLOR_BLUE,				(0,0,255)
			{MAXIMUM_COLOR, MAXIMUM_COLOR, NO_COLOR},		//	AI_SUPPORT_CLASSES_COLOR_YELLOW,			(255,255,0) 
			{NO_COLOR, MAXIMUM_COLOR, MAXIMUM_COLOR},		//	AI_SUPPORT_CLASSES_COLOR_CYAN,				(0,255,255) 
			{MAXIMUM_COLOR, NO_COLOR, MAXIMUM_COLOR},		//	AI_SUPPORT_CLASSES_COLOR_MAGENTA,			(255,0,255)
			{192, 192, 192},								//	AI_SUPPORT_CLASSES_COLOR_SILVER,			(192,192,192)
			{HALF_COLOR, HALF_COLOR, HALF_COLOR}, 			//	AI_SUPPORT_CLASSES_COLOR_GRAY,				(128,128,128)
			{HALF_COLOR, NO_COLOR, NO_COLOR},				//	AI_SUPPORT_CLASSES_COLOR_MAROON,			(128,0,0)
			{HALF_COLOR, HALF_COLOR, NO_COLOR},				//	AI_SUPPORT_CLASSES_COLOR_OLIVE,				(128,128,0)
			{238, 130, 238},								//	AI_SUPPORT_CLASSES_COLOR_VIOLET,			(238,130,238)
			{HALF_COLOR, NO_COLOR, HALF_COLOR},				//	AI_SUPPORT_CLASSES_COLOR_PURPLE,			(128,0,128)
			{NO_COLOR, HALF_COLOR, HALF_COLOR},				//	AI_SUPPORT_CLASSES_COLOR_TEAL,				(0,128,128)
			{NO_COLOR, NO_COLOR, HALF_COLOR},				//	AI_SUPPORT_CLASSES_COLOR_NAVY,				(0,0,128)
			{MAXIMUM_COLOR, 99, 71},						//	AI_SUPPORT_CLASSES_COLOR_TOMATO,			(255,99,71)
			{MAXIMUM_COLOR, 165, NO_COLOR},					//	AI_SUPPORT_CLASSES_COLOR_ORANGE,			(255,165,0)
			{NO_COLOR, 100, NO_COLOR},						//	AI_SUPPORT_CLASSES_COLOR_DARK_GREEN,		(0,100,0)
			{64, 224, 208},									//	AI_SUPPORT_CLASSES_COLOR_TURQUOISE,			(64,224,208)
			{210, 105, 30},									//	AI_SUPPORT_CLASSES_COLOR_CHOCOLATE,			(210,105,30)
			{MAXIMUM_COLOR, MAXIMUM_COLOR, MAXIMUM_COLOR}	//	AI_SUPPORT_CLASSES_COLOR_WHITE				(255,255,255)
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Logger::Logger() 
		{ 
			this->initialized	= false;
			this->filename		= "";
			
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
		// Remarks				:
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Logger::~Logger() 
		{ 
			this->outfile.close();
			
		}	//	Logger::~Logger()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This constructor will create a non valid object
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location::Location()
		{
			this->_Location(AI_SUPPORT_CLASSES_INVALID_COLUMN, AI_SUPPORT_CLASSES_INVALID_ROW);
			
		}	//	Location::Location()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location
		// Function description	: This constructors take as parameter the location
		//							(column, row)
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::DsmLocation()
		{
			this->_Location(AI_SUPPORT_CLASSES_INVALID_COLUMN, AI_SUPPORT_CLASSES_INVALID_ROW);
			this->elevation	= AI_SUPPORT_CLASSES_INVALID_DSM_ELEVATION;
			
		}	//	DsmLocation::DsmLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This constructor will create a non valid object
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:	column
		//							row
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::DsmLocation(int column, int row)
		{
			this->_Location(column, row);
			this->elevation	= AI_SUPPORT_CLASSES_INVALID_DSM_ELEVATION;
			
		}	//	DsmLocation::DsmLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Parametrized constructors
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This family of constructors will create a valid object
		// Remarks				:
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		DsmLocation::~DsmLocation()
		{
			
		}	//	DsmLocation::~DsmLocation()
			
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents the information taken from a DSM file
		//							A DSM (Digital Surface Model) is a computer graphics 
		//							representation of elevation data to represent terrain
		// Function description	:
		// Remarks				:Set the default logger file to "DsmInformation.txt"
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

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents the information taken from a DSM file
		//							A DSM (Digital Surface Model) is a computer graphics 
		//							representation of elevation data to represent terrain
		// Function description	:
		// Remarks				:Set the default logger file to "DsmInformation.txt"
		//							in "output" sub-directory
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: columns and rows
		/////////////////////////////////////////////////////////////////////////////////
		DsmInformation::DsmInformation(int columns, int rows) 
		{ 
			logger.Filename(DEFAULT_DSM_INFORMATION_FILE_NAME);
			logger.WriteLine("Parametrized Constructor called"); 

			this->initialized	= true;
			this->columns		= columns;
			this->rows			= rows;

			this->pLocation		= new DsmLocation[columns * rows];
			
		}	//	DsmInformation::DsmInformation()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents the information taken from a DSM file
		//							A DSM (Digital Surface Model) is a computer graphics 
		//							representation of elevation data to represent terrain
		// Function description	:
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		DsmInformation::~DsmInformation() 
		{
			logger.WriteLine("Destructor called for cleanup");  
			
			if (NULL != this->pLocation)
			{
				logger.WriteLine("Internal array of locations is deallocated");  
				delete [] pLocation; 
			}
			else
			{
				logger.WriteLine("The internal array of locations was NOT initialized and therefore there is no need to deallocate it");
			}
			
		}	//	DsmInformation::~DsmInformation()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: TargetDsmInformation
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Function description	:
		// Remarks				:  It is derived from DsmInformation class
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		TargetDsmInformation::~TargetDsmInformation()
		{
		}	//	TargetDsmInformation::~TargetDsmInformation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents a graphic
		// Function description	:
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Graphic::Graphic() 
		{ 
			this->initialized			= false; 
			this->columns				= 0;
			this->rows					= 0;
			
			if (NULL == this->pPngObject)
				this->pPngObject		= new pngwriter(0, 0, 0, "");
				
			if (NULL == this->pPngObjectShadow)
				this->pPngObjectShadow	= new pngwriter(0, 0, 0, "");
			
			
		}	//	Graphic::Graphic()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents a graphic
		// Function description	:
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Graphic::Graphic(int columns, int rows) 
		{ 
			this->initialized			= true;
			this->columns				= columns;
			this->rows					= rows;
			
			if (NULL == this->pPngObject)
				this->pPngObject		= new pngwriter(columns, rows, 0, "");
				
			if (NULL == this->pPngObjectShadow)
				this->pPngObjectShadow	= new pngwriter(columns, rows, 0, "");
				
			if (NULL == this->pafWriteDspMap)
				this->pafWriteDspMap	= (float*) CPLMalloc(sizeof(float) * columns * rows);
			
		}	//	Graphic::Graphic()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 26-02-2021
		// Class description	: This class represents a graphic
		// Function description	:
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Graphic::~Graphic() 
		{
			if (NULL != this->pPngObject)
				delete this->pPngObject;
				
			if (NULL != this->pPngObjectShadow)
				delete this->pPngObjectShadow;

			if (NULL != this->pafWriteDspMap)
				CPLFree(this->pafWriteDspMap);
			
		}	//	Graphic::~Graphic()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Timer
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for timer and system clock functions
		// Function description	:
		// Remarks				: This class will give support to Logger class and algorithms
		//						for profiling issues
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Timer::Timer() 
		{ 
			this->running		= false;
			this->systemStart 	= std::chrono::high_resolution_clock::now();
			
		}	//	Timer::Timer() 

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Timer
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for timer and system clock functions
		// Function description	:
		// Remarks				: This class will give support to Logger class and algorithms
		//						for profiling issues
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Timer::~Timer() 
		{ 
		}	//	Timer::~Timer()
		
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Write 
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function is used to return the system time
		// Remarks				:Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: 
		/////////////////////////////////////////////////////////////////////////////////
		class Timer& Logger::SystemTime(void)
		{
			return this->timer;
			
		}	//	Logger::SystemTime()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Logger
		// Function				: Write 
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for logging in a text file all
		//							the events that are needed to follow the sequence of
		//							events in the software
		// Function description	: This member function is used to send information (with
		//							different types of arguments) into the logger file
		// Remarks				:Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file
		/////////////////////////////////////////////////////////////////////////////////
		template <class GenericType> 
		bool Logger::Write(GenericType loggerGenericType)
		{
			if (!this->initialized)
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
		// Remarks				:Returns false, if the object was not initialized
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string))
		/////////////////////////////////////////////////////////////////////////////////
		bool Logger::WriteLine(string loggerString)
		{
			if (!this->initialized)
				return false;
				
//			this->outfile << "{" << this->timer.Tick() << "} - " << loggerString << endl;
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
		// Remarks				:Returns false, if the file name could not be set
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Log file name (string)
		/////////////////////////////////////////////////////////////////////////////////
		bool Logger::Filename(string filename)
		{
			if (!this->initialized && this->filename == "")
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
		// Remarks				:
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
		// Remarks				:Returns the column location
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
		// Remarks				:Returns the row location
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
		// Remarks				:Returns the line intercept point
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location
		/////////////////////////////////////////////////////////////////////////////////
		double Location::LineIntercept(Location point)
		{
			double	intercept	= ((double) (this->Row() - (double) (this->LineSlope(point) * this->Column())));
		
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
		// Remarks				:Returns the line slope
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location
		/////////////////////////////////////////////////////////////////////////////////
		double Location::LineSlope(Location point)
		{
			double	slope		= ((double) (this->Row() - point.Row()) / (double) (this->Column() - point.Column()));
			
			return slope;
			
		}	//	Location::LineSlope()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Distance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns the distance between
		//							2 points
		// Remarks				:Returns the distance between them
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location
		/////////////////////////////////////////////////////////////////////////////////
		double Location::Distance(Location point)
		{
			double	distance, columm_distance, row_distance;
			row_distance	= (double) (this->Row() - point.Row());
			columm_distance	= (double) (this->Column() - point.Column());
			distance		= sqrt((row_distance * row_distance) + (columm_distance * columm_distance));
			
			return distance;
			
		}	//	Location::Distance()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Distance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns the distance between
		//							2 points
		// Remarks				:Returns the distance between them
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two points location
		/////////////////////////////////////////////////////////////////////////////////
		double Location::Distance(Location& pointA, Location pointB)
		{
			return pointA.Distance(pointB);
			
		}	//	Location::Distance()
		
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Location
		// Function				: Opposite
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 20-03-2021
		// Class description	: This class represents a specific location
		// Function description	: This member function returns the opposite location
		//							entering as input the central location and the 
		//							A location
		// Remarks				:Returns the opposite location to this point
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: central point location
		/////////////////////////////////////////////////////////////////////////////////
		Location& Location::Opposite(Location centralPoint)
		{
			Location*	oppositeLocation;
			int			oppositeColumn, oppositeRow;
			
			if (centralPoint.Column() == this->Column())
			{
				//	If both central and A points have the same column
				oppositeColumn					= centralPoint.Column();
				int	distanceToCentralPoint		= abs(centralPoint.Row() - this->Row());
				oppositeRow						= (centralPoint.Row() > this->Row()) ? (centralPoint.Row() + distanceToCentralPoint) : (centralPoint.Row() - distanceToCentralPoint);
			}
			else
			{
				double	slope, intercept;
				int		distanceToCentralPoint	= abs(centralPoint.Column() - this->Column());
				
				//	Calculate row = (m * column) + b with central and A points being m (slope) and b (intercept)
				slope							= this->LineSlope(centralPoint);
				intercept						= this->LineIntercept(centralPoint);
				oppositeColumn					= (centralPoint.Column() > this->Column()) ? round(centralPoint.Column() + distanceToCentralPoint) : round(centralPoint.Column() - distanceToCentralPoint);
				oppositeRow						= round((oppositeColumn * slope) + intercept);
			}
			
			oppositeLocation	= new Location();
			oppositeLocation->Modify(oppositeColumn, oppositeRow);

			return (*oppositeLocation);

		}	//	Location::Opposite()
			
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This is a member function that sets the 
		//							location and elevation
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:Returns the location elevation
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		double DsmLocation::Elevation(void)
		{
			return this->elevation;
			
		}	//	DsmLocation::Elevation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmLocation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Class description	: This class represents a specific location for DSM maps
		// Function description	: This member function defines if the location is an obstacle
		//							of the location
		// Remarks				:
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
		// Remarks				:Returns true, if the location is an obstacle
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
		// Remarks				:Returns true, if the locations are visible between them
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
				column	= pointA.Column();
				
				if (pointA.Row() > pointB.Row())
				{
					for (row = pointB.Row(); row <= pointA.Row(); row++)
					{
						if (this->Obstacle(column, row))
							return false;
					}
				}
				else if (pointB.Row() > pointA.Row())
				{
					for (row = pointA.Row(); row <= pointB.Row(); row++)
					{
						if (this->Obstacle(column, row))
							return false;
					}
				}
			}
			else if (pointA.Column() > pointB.Column())
			{
				for (column = pointB.Column(); column <= pointA.Column(); column++)
				{
					row	= (int) (slope * column) + intercept;
					
					if (this->Obstacle(column, row))
						return false;
				}
			}
			else
			{
				for (column = pointA.Column(); column <= pointB.Column(); column++)
				{
					row	= (int) (slope * column) + intercept;
					
					if (this->Obstacle(column, row))
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		int DsmInformation::Rows(void)
		{
			return this->rows;
			
		}   //  DsmInformation::Rows()
 
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Columns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns DSM map number of columns
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		int DsmInformation::Columns(void)
		{
			return this->columns;
			
		}   //  DsmInformation::Columns()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the DSM map number of rows
		// Remarks				:If also the columns are initialized, creates the
		//							internal array
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of rows
		/////////////////////////////////////////////////////////////////////////////////
		void DsmInformation::Rows(int rows)
		{
			this->logger.Write("Called rows(");
			this->logger.Write(rows);
			this->	logger.WriteLine(")");

			this->rows	= rows;
			
			if (!this->initialized && 0 != this->Columns())
			{
				this->logger.Write("Initializing internal array (");
				this->logger.Write(this->Columns());
				this->logger.Write("x");
				this->logger.Write(rows);
				this->logger.WriteLine(")");
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
		// Remarks				:If also the rows are initialized, creates the
		//							internal array
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of columns
		/////////////////////////////////////////////////////////////////////////////////
		void DsmInformation::Columns(int columns)
		{
			this->logger.Write("Called columns(");
			this->logger.Write(columns);
			this->logger.WriteLine(")");
			
			this->columns	= columns;
			
			if (!this->initialized && 0 != this->Rows())
			{
				this->logger.Write("Initializing internal array (");
				this->logger.Write(columns);
				this->logger.Write("x");
				this->logger.Write(this->Rows());
				this->logger.WriteLine(")");
				this->pLocation		= new DsmLocation[columns * this->Rows()];  
				this->initialized	= true; 
			}
			
		}   //  DsmInformation::Columns()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns the elevation of the column/row
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		double DsmInformation::Elevation(Location location)
		{
			return (this->pLocation[(location.Row() * this->Columns()) + location.Column()].Elevation());
			
		}   //  DsmInformation::Elevation()

 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns the elevation of the column/row
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column and row
		/////////////////////////////////////////////////////////////////////////////////
		double DsmInformation::Elevation(int column, int row)
		{
			return (this->pLocation[(row * this->Columns()) + column].Elevation());
			
		}   //  DsmInformation::Elevation()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Elevation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the elevation of the column/row
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row and elevation to be set
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::Elevation(int column, int row, double elevation)
		{
			if (row > this->Rows())
			{
				this->logger << "Input row: " << row << " is greater than the maximum number of rows: " << this->Rows() << "\n";
				return false;
			} 
			if (column > this->Columns())
			{
				this->logger << "Input column: " << column << " is greater than the maximum number of columns: " << this->Columns() << "\n";
				return false;
			}
			
			this->pLocation[(this->Columns() * row) + column].Elevation(elevation);
			this->logger << "[" << column << "," << row << "] elevation set to " << elevation << "\n";
			
			return true;
			
		}	//	DsmInformation::Elevation()

 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function defines location as an obstacle
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row and boolean deciding if the location could
		//							is an obstacle
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::Obstacle(int column, int row, bool theLocationIsAnObstacle)
		{
			if (row > this->Rows())
			{
				this->logger << "Input row: " << row << " is greater than the maximum number of rows: " << this->Rows() << "\n";
				return false;
			} 
			if (column > this->Columns())
			{
				this->logger << "Input column: " << column << " is greater than the maximum number of columns: " << this->Columns() << "\n";
				return false;
			}
			
			
			this->pLocation[(this->Columns() * row) + column].Obstacle(theLocationIsAnObstacle);
			if (theLocationIsAnObstacle)
				this->logger << "[" << column << "," << row << "] was set to be an obstacle\n";
			else
				this->logger << "[" << column << "," << row << "] was set not to be an obstacle\n";
			
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
		// Remarks				:Returns true, if the location is an obstacle,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::Obstacle(Location location)
		{
			return (this->pLocation[(location.Row() * this->Columns()) + location.Column()].Obstacle());
			
		}   //  DsmInformation::Obstacle()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: Obstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns if the location is an
		//							obstacle or not
		// Remarks				:Returns true, if the location is an obstacle,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row 
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::Obstacle(int column, int row)
		{
			return (this->pLocation[(row * this->Columns()) + column].Obstacle());
			
		}   //  DsmInformation::Obstacle()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: IsInDsmMap
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns if the location is in
		//							the DSM map
		// Remarks				:Returns true, if the location is in the DSM map,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::IsInDsmMap(Location location)
		{
			if ((location.Row() >= 0 && location.Row() < this->Rows()) && (location.Column() >= 0 && location.Column() < this->Columns()))
				return true;
				
			return false;
		
		}	//	DsmInformation::IsInDsmMap()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: GroundLevel
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function sets the elevation of the
		//							ground level of this DSM map
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map ground level
		/////////////////////////////////////////////////////////////////////////////////
		void DsmInformation::GroundLevel(double groundLevelElevation)
		{
			this->groundLevelElevation	= groundLevelElevation;
			
		}   //  DsmInformation::GroundLevel()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: GroundLevel
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns the ground level elevation
		//							of the DSM map
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		double DsmInformation::GroundLevel(void)
		{
			return this->groundLevelElevation;
			
		}	//	DsmInformation::GroundLevel()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: GroundLevel
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Function description	: This member function returns true if the location is 
		//							at the ground level elevation of the DSM map
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool DsmInformation::GroundLevel(Location location)
		{
			return (this->GroundLevel() == this->Elevation(location));
			
		}	//	DsmInformation::GroundLevel()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: TargetDsmInformation
		// Function				: DsmMapForTargetReset
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents the information taken from a DSM file
		//							A DSM (Digital Surface Model) is a computer graphics 
		//							representation of elevation data to represent terrain but
		//							specialized with info on target
		// Function description	: This member function updates the internal DSM
		//							map (in agent) with the information from target DSM
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: source DSM map
		/////////////////////////////////////////////////////////////////////////////////
		void TargetDsmInformation::DsmMapForTargetReset(DsmInformation& sourceDsmMap, 
					// Default parameters
					bool includingForbiddenCloseToTargetLocations,
					Location targetLocation,
					int minimumDistanceToTarget,
					bool clearPreviousObstacles)
		{
			int	column, row;
			int	columns = sourceDsmMap.Columns();
			int	rows	= sourceDsmMap.Rows();
			
			for (row = 0; row < rows; row++)
			{
				for (column = 0; column < columns; column++)
				{
					if (clearPreviousObstacles)
					{
						//	Copy elevation from dsmInformation object
						this->Elevation(column, row, sourceDsmMap.Elevation(column, row));
						//	Copy obstacle from dsmInformation object
						this->Obstacle(column, row, sourceDsmMap.Obstacle(column, row));
					}
					
					if (includingForbiddenCloseToTargetLocations)
					{
						Location	currentLocation(column, row);
						
						if (currentLocation.Distance(targetLocation) < minimumDistanceToTarget)
						{
							if (!this->Obstacle(currentLocation))
							{
								//	If the location is close enough to target
								//		and it is NOT an obstacle,
								//		the set this position as a forbidden one
								this->ForbiddenDistance(column, row, true);
							}
						}
					}
				}
			}
			
		}	//	TargetDsmInformation::DsmMapForTargetReset()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: TargetDsmInformation
		// Function				: ForbiddenDistance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Function description	: This member function defines location close enough to
		//							target
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row and boolean deciding if the location could
		//							is a forbidden distance from target
		/////////////////////////////////////////////////////////////////////////////////
		bool TargetDsmInformation::ForbiddenDistance(int column, int row, bool forbiddenDistance)
		{
			if (row > this->Rows())
			{
				this->logger << "Input row: " << row << " is greater than the maximum number of rows: " << this->Rows() << "\n";
				return false;
			} 
			if (column > this->Columns())
			{
				this->logger << "Input column: " << column << " is greater than the maximum number of columns: " << this->Columns() << "\n";
				return false;
			}
			
			
			this->pLocation[(this->Columns() * row) + column].Obstacle(forbiddenDistance);
			this->pLocation[(this->Columns() * row) + column].Elevation(ELEVATION_TO_DEFINE_PROXIMITY_TO_TARGET);
			
			if (forbiddenDistance)
				this->logger << "[" << column << "," << row << "] was set to be at forbidden distance\n";
			else
				this->logger << "[" << column << "," << row << "] was set not to be at forbidden distance\n";
			
			return true;
			
		}	//	TargetDsmInformation::ForbiddenDistance()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: TargetDsmInformation
		// Function				: ForbiddenDistance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Function description	: This member function returns if the location is close
		//							enough to target
		// Remarks				:Returns true, if the location is close enough to target,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool TargetDsmInformation::ForbiddenDistance(Location location)
		{
			return (this->pLocation[(location.Row() * this->Columns()) + location.Column()].Obstacle());
			
		}   //  TargetDsmInformation::ForbiddenDistance()
		
 		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: ForbiddenDistance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: TThis class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Function description	: This member function returns if the location is close
		//							enough to target
		// Remarks				:Returns true, if the location is close enough to target,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: column, row 
		/////////////////////////////////////////////////////////////////////////////////
		bool TargetDsmInformation::ForbiddenDistance(int column, int row)
		{
			return (this->pLocation[(row * this->Columns()) + column].Obstacle());
			
		}   //  TargetDsmInformation::ForbiddenDistance()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Open
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function opens the graphic with the 
		//							pre-inserted information
		// Remarks				:Returns true, if it succeeded creating the graphic file,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: filename,
		//					Default parameters
		//							.png header description
		//							if open from shadow
		//							.png header Author
		//							.png header Software
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Open(string filename, string description, bool fromShadow, string author, string software)
		{
			if (!this->Filename(filename, fromShadow))
				return false;
				
			//	Change the text information in the PNG header
			(*this->pPngObject).settext(filename.c_str(), author.c_str(), description.c_str(), software.c_str());
			
			return true;

		}   //  Graphic::Open()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Close
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function closes the graphic with the 
		//							pre-inserted information
		// Remarks				:Returns true, if it succeeded creating the graphic file,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic type
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Close(AI_SUPPORT_CLASSES_graphicType typeOfGraphic)
		{
			int	row;
			
			if (!this->initialized)
				return false;
				
			switch (typeOfGraphic)
			{
				case AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG:
					//	Close the instance of the class, and write the image to disk.
//					(*pPngObject).close();
					(*pPngObject).write_png();
					break;
					
				case AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF:
					{
						CPLErr		rasterIoError;
						const int	BAND_TO_BE_WRITTEN	= 1;
						int			columns				= this->Columns();
						int			rows				= this->Rows();
						
						for (row = 0; row < rows; row++)
						{
							rasterIoError	= this->geotiffDataset->GetRasterBand(BAND_TO_BE_WRITTEN)->RasterIO
							(
								GF_Write,
								0,								//	The pixel offset to the top left corner of the region of the band to be accessed. 
																//	This would be zero to start from the left side.
								row,							//	The line offset to the top left corner of the region of the band to be accessed. 
																//	This would be zero to start from the top.
								columns,						//	The width of the region of the band to be accessed in pixels.
								1,								//	The height of the region of the band to be accessed in lines.
								&pafWriteDspMap[row * columns],	//	The buffer into which the data should be read, or from which it should be written. 
												//	This buffer must contain at least nBufXSize * nBufYSize * nBandCount words of type eBufType. 
												//	It is organized in left to right,top to bottom pixel order. Spacing is controlled by the nPixelSpace, and nLineSpace parameters.
								columns,						//	The width of the buffer image into which the desired region is to be read, or from which it is to be written.
								1,								//	The height of the buffer image into which the desired region is to be read, or from which it is to be written.
								GDT_Float32,					//	The type of the pixel values in the pData data buffer. The pixel values will automatically be translated to/from the GDALRasterBand data type as needed.
								0,
								0
							);
								
							if (CE_None != rasterIoError)
							{
								cout << "\tRasterIO(GF_Write) function returns with error: " << rasterIoError << "\n";
								return false;
							}
						}
					}
					//	close out GeoTIFF dataset
					GDALClose(this->geotiffDataset);
					break;
				default:
					return false;
			}

			return true;

		}   //  Graphic::Close()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Rows
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function returns the graphic number of rows
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of rows
		/////////////////////////////////////////////////////////////////////////////////
		void Graphic::Rows(int rows)
		{
			this->rows	= rows;

			if (!this->initialized && 0 != this->Columns() && this->filename != "")
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Number of columns
		/////////////////////////////////////////////////////////////////////////////////
		void Graphic::Columns(int columns)
		{
			this->columns	= columns;
			
			if (!this->initialized && 0 != this->Rows() && this->filename != "")
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic file name
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Filename(string filename, bool fromShadow)
		{
			this->filename	= filename;
			
			if ((!this->initialized || fromShadow) && 0 != this->Rows() && 0 != this->Columns())
			{
				this->initialized	= true; 
				this->_Update(fromShadow);
				return true;
			}
			
			return false;

		}   //  Graphic::Filename()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Line
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 01-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function draws a line with a specific color
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location of the start and end points of the line and
		//							the color to be used in the line
		//					Default parameters:
		//							copyToShadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Line(class Location from, class Location to, AI_SUPPORT_CLASSES_color lineColor, bool copyToShadow)
		{
			if (!this->initialized || !this->_IsInGraphic(from) || !this->_IsInGraphic(to))
				return false;

			(*this->pPngObject).line(
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				from.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				to.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				to.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				colorToRgb[lineColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[lineColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[lineColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
				
			if (copyToShadow)
			{
				(*this->pPngObjectShadow).line(
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				from.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				to.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				to.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				colorToRgb[lineColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[lineColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[lineColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
			}

			return true;

		}   //  Graphic::Line()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Arrow
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function draws an arrow with a specific color
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location of the start and end points of the arrow and
		//							the color to be used in the arrow
		//					Default parameters:
		//							copyToShadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Arrow(class Location from, class Location to, AI_SUPPORT_CLASSES_color arrowColor, bool copyToShadow)
		{
			const int 		ARROW_SIZE 	= 5;
			const double	HEAD_ANGLE	= 0.0;
			
			if (!this->initialized || !this->_IsInGraphic(from) || !this->_IsInGraphic(to))
				return false;
				
			(*this->pPngObject).arrow(
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				from.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				to.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				to.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				ARROW_SIZE,
				HEAD_ANGLE,
				colorToRgb[arrowColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[arrowColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[arrowColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
				
			if (copyToShadow)
			{
				(*this->pPngObjectShadow).arrow(
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				from.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				to.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP,
				to.Row() + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				ARROW_SIZE,
				HEAD_ANGLE,
				colorToRgb[arrowColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[arrowColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[arrowColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
			}

			return true;
			
		}	//	Graphic::Arrow()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Cross
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 0-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function set a cross to a specific color
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location and specific color (relevant to .png)
		//					Default parameters:
		//							copyToShadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Cross(class Location at, AI_SUPPORT_CLASSES_color crossColor, bool copyToShadow)
		{
			const int CROSS_WIDTH 	= 3;
			const int CROSS_HEIGTH	= 3;
			
			if (!this->initialized || !this->_IsInGraphic(at))
				return false;

			//	.png graphic cross with color
			(*this->pPngObject).cross(
				at.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				at.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				CROSS_WIDTH,
				CROSS_HEIGTH,
				colorToRgb[crossColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[crossColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[crossColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
				
			if (copyToShadow)
			{
				(*this->pPngObjectShadow).cross(
					at.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
					at.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
					CROSS_WIDTH,
					CROSS_HEIGTH,
					colorToRgb[crossColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
					colorToRgb[crossColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
					colorToRgb[crossColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
			}

			return true;
			
		}	//	Graphic::Cross()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Point
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function set a pixel to a specific color
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location and specific color (relevant to .png)
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Point(class Location at, AI_SUPPORT_CLASSES_color pixelColor)
		{
			if (!this->initialized || !this->_IsInGraphic(at))
				return false;

			//	.png graphic point with color
			(*this->pPngObject).plot(
				at.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				at.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				colorToRgb[pixelColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[pixelColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[pixelColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
				
			(*this->pPngObjectShadow).plot(
				at.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				at.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				colorToRgb[pixelColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[pixelColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[pixelColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);

			return true;

		}	//	Graphic::Point()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Point
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function set a pixel to a specific color
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: point location and elevation (relevant to GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Point(class Location at, int elevation)
		{
			//	Inserts the elevation info into the DSM map
			//		Because of unification of pixel coordinates
			//		to internal representation where SW pixel is 0,0
			//		and info to GeoTIFF file is NW pixel as 0,0
			int	internalRepresentationRows		= this->Rows();
			int	internalRepresentationColumns	= this->Columns();
			int	dsmRepresentationColumn			= at.Column();									// stays the same representation
			int	dsmRepresentationRow			= (internalRepresentationRows-1) - at.Row();		// the order changes in the representation
			
			if (!this->initialized || !this->_IsInGraphic(at))
				return false;

			//	GeoTIFF graphic point with elevation
			pafWriteDspMap[(dsmRepresentationRow * internalRepresentationColumns) + dsmRepresentationColumn]	= elevation;

			return true;

		}	//	Graphic::Point()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: Text
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This member function set a text in the output file
		// Remarks				:Currently supported formats (.png)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: text location 
		//							text string
		//						Default parameters:
		//							text color
		//							copy to shado
		//							font size
		//							path and filename of the font to be used
		//							angle of the text (in degrees)
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::Text(class Location from, string text, 
			//	Default arguments
			AI_SUPPORT_CLASSES_color textColor, bool copyToShadow, int fontSize,
			string fontPathAndFilename,	double angle)
		{
			const double PI	= 3.141592653589793238463;
			
			if (!this->initialized || !this->_IsInGraphic(from))
				return false;
				
			(*this->pPngObject).plot_text_utf8(
				(char *)fontPathAndFilename.c_str(), fontSize,
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				from.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				(angle * PI / 180.0),	// convert from degrees to radians
				(char *) text.c_str(),
				colorToRgb[textColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[textColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[textColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
				
			if (copyToShadow)
			{
				(*this->pPngObjectShadow).plot_text_utf8(
				(char *)fontPathAndFilename.c_str(), fontSize,
				from.Column() + PNG_COLUMN_OFFSET_FROM_DSM_MAP, 
				from.Row()  + PNG_ROW_OFFSET_FROM_DSM_MAP, 
				(angle * PI / 180.0),	// convert from degrees to radians
				(char *) text.c_str(),
				colorToRgb[textColor].red * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[textColor].green * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR, 
				colorToRgb[textColor].blue * CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR);
			}

			return true;
			 
		}	//	Graphic::Text()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Timer
		// Function				: Start
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for timer and system clock functions
		// Function description	: This functions starts the "stopper"
		// Remarks				: This class will give support to Logger class and algorithms
		//						for profiling issues
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		void Timer::Start(void)
		{ 
			this->running	= true;
			this->start		= std::chrono::high_resolution_clock::now();
			
		}	//	Timer::Start() 
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Timer
		// Function				: Stop
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for timer and system clock functions
		// Function description	: This functions stops the "stopper" and returns the elapsed
		//							time betweein Start() and Stop() functions
		// Remarks				: This class will give support to Logger class and algorithms
		//						for profiling issues
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		long int Timer::Stop(void)
		{
			if (this->running)
			{
				long int	durationMilliseconds	= (long int) chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->start).count();
 
				this->running	= false;
				return durationMilliseconds;
			}
			
			return 0;
			
		}	//	Timer::Stop() 
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Timer
		// Function				: Tick
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class gives support for timer and system clock functions
		// Function description	: This functions returns the current "tick"
		// Remarks				: This class will give support to Logger class and algorithms
		//						for profiling issues
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		long int Timer::Tick(void)
		{ 
			return ((long int) chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->systemStart).count());
			
		}	//	Timer::Tick() 

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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Info to be sent to the logger file (string, integer,
		//							long, float, double, class Timer
		/////////////////////////////////////////////////////////////////////////////////
		Logger& operator << (Logger& logger, const class Timer& loggerTimer)
		{
			class Timer systemTimer = loggerTimer;
			
			logger << "{" << systemTimer.Tick()  << "} - ";

			return logger;

		}	//	Logger& operator <<
		
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
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
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
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Location::operator != (Location& location)
		{
			return (this->Column() != location.Column()) || (this->Row() != location.Row());

		}	//	bool Location::operator !=
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents a graphic
		// Operator description	: This operator (=) is used to assign a location to another
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: 
		/////////////////////////////////////////////////////////////////////////////////
		Graphic& Graphic::operator = (Graphic& graphic)
		{
			return (*this);

		}	//	Graphic::operator =

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: DsmInformation
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents all the needed info for DSM maps
		// Operator description	: This operator (=) is used to assign DSM information to another
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map information
		/////////////////////////////////////////////////////////////////////////////////
		DsmInformation& DsmInformation::operator = (DsmInformation &dsmInformation)
		{
			if (this != &dsmInformation)
			{
				int	column, row;
				int	columns = this->Columns();
				int	rows	= this->Rows();
				
				for (row = 0; row < rows; row++)
				{
					for (column = 0; column < columns; column++)
					{
						//	Copy elevation from dsmInformation object
						this->Elevation(column, row, dsmInformation.Elevation(column, row));
						//	Copy obstacle from dsmInformation object
						this->Obstacle(column, row, dsmInformation.Obstacle(column, row));
					}
				}
			}

			return (*this);

		}	//	DsmLocation::operator =

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: TargetDsmInformation
		// Function				: = operator (location assignment operator)
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Operator description	: This operator (=) is used to assign DSM information to another
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map information
		/////////////////////////////////////////////////////////////////////////////////
		TargetDsmInformation& TargetDsmInformation::operator = (DsmInformation &dsmInformation)
		{
			if (this != &dsmInformation)
			{
				int	column, row;
				int	columns = this->Columns();
				int	rows	= this->Rows();
				
				for (row = 0; row < rows; row++)
				{
					for (column = 0; column < columns; column++)
					{
						//	Copy elevation from dsmInformation object
						this->Elevation(column, row, dsmInformation.Elevation(column, row));
						//	Copy obstacle from dsmInformation object
						this->Obstacle(column, row, dsmInformation.Obstacle(column, row));
					}
				}
			}

			return (*this);

		}	//	TargetDsmInformation::operator =
		
	/*
		****************************************************************************
		* PROTECTED CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
	
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
		// Remarks				: 
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
		// Remarks				:
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
		// Function				: _IsInGraphic
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This private member function sets the graphic file name
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: location
		/////////////////////////////////////////////////////////////////////////////////
		bool Graphic::_IsInGraphic(Location location)
		{
			if ((location.Row() < 0 || location.Row() >= this->Rows()) || (location.Column() < 0 || location.Column() >= this->Columns()))
				return false;
				
			return true;
			
		}	//	Graphic::_IsInGraphic()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Graphic
		// Function				: _Update
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This class represents a graphic
		// Function description	: This private member function updates the output graphic
		//							file that is being created
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		void Graphic::_Update(bool fromShadow)
		{
			string	pngFilename		= this->filename + ".png";
			string	geoTiffFilename	= this->filename + ".tif";

			if (!this->initialized)
				return;

			//	Update .png graphic file size (if not from shadow)
			if (!fromShadow)
				(*this->pPngObject).resize(this->Columns(), this->Rows());
			
			if (!fromShadow)
				(*this->pPngObjectShadow).resize(this->Columns(), this->Rows());
			else
				(*this->pPngObject)	= (*this->pPngObjectShadow);
			
			//	Update .png graphic file name
			(*this->pPngObject).pngwriter_rename(pngFilename.c_str());

			//	Update GeoTIFF graphic file
				//	Create GDAL driver object whose Create() method will be used to create Geotiff writer object. */
			if (!fromShadow)
			{
				this->driverGeotiff 	= GetGDALDriverManager()->GetDriverByName("GTiff");
				this->geotiffDataset	= this->driverGeotiff->Create(geoTiffFilename.c_str(), this->Columns(), this->Rows(), 1, GDT_Float32, NULL);
				this->pafWriteDspMap	= (float*) CPLMalloc(sizeof(float) * this->Columns() * this->Rows());
			}

		}	//	Graphic::_Update()





