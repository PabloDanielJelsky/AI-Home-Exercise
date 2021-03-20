//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportClasses_Ifc.h
//
// Version:			01.05
//
// Description:		Support classes for the AI home excercise interface file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
//
// Copyright:
//
//	DEVELOPMENT HISTORY:
//
// Remarks:
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

#ifndef __AI_SUPPORT_CLASSES_IFC_H__
#define	__AI_SUPPORT_CLASSES_IFC_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <iostream>
		#include <fstream> 
		#include <string>
		#include <chrono>	// for timer object
		/*---- library files -------------------------------------------------------*/
		#include "/usr/include/gdal/gdal.h"
		#include "/usr/include/gdal/gdal_priv.h"
		#include "/usr/include/gdal/gdal_utils.h"
		#include "/usr/include/gdal/cpl_conv.h"
		#include "/usr/include/gdal/cpl_string.h"
		#include "pngwriter.h"
		/*---- program files -------------------------------------------------------*/
	
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		//	Template declaration
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;
		/*---- defines --------------------------------------------------------------*/
		#define	AI_SUPPORT_CLASSES_INVALID_COLUMN			-1
		#define	AI_SUPPORT_CLASSES_INVALID_ROW				-1
		#define AI_SUPPORT_CLASSES_INVALID_DSM_ELEVATION	-999999999
		/*---- enums --------------------------------------------------------------*/
		typedef enum {
						AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG, 
						AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF
						
					} AI_SUPPORT_CLASSES_graphicType;
		typedef enum {
						AI_SUPPORT_CLASSES_COLOR_BLACK,			 	//	(0,0,0)
						AI_SUPPORT_CLASSES_COLOR_RED,				//	(255,0,0)
						AI_SUPPORT_CLASSES_COLOR_LIME,				//	(0,255,0)
						AI_SUPPORT_CLASSES_COLOR_BLUE,				//	(0,0,255)
						AI_SUPPORT_CLASSES_COLOR_YELLOW,			//	(255,255,0) 
						AI_SUPPORT_CLASSES_COLOR_CYAN,				//	(0,255,255) 
						AI_SUPPORT_CLASSES_COLOR_MAGENTA,			//	(255,0,255)
						AI_SUPPORT_CLASSES_COLOR_SILVER,			//	(192,192,192)
						AI_SUPPORT_CLASSES_COLOR_GRAY,				//	(128,128,128)
						AI_SUPPORT_CLASSES_COLOR_MAROON,			//	(128,0,0)
						AI_SUPPORT_CLASSES_COLOR_OLIVE,				//	(128,128,0)
						AI_SUPPORT_CLASSES_COLOR_VIOLET,			//	(238,130,238)
						AI_SUPPORT_CLASSES_COLOR_PURPLE,			//	(128,0,128)
						AI_SUPPORT_CLASSES_COLOR_TEAL,				//	(0,128,128)
						AI_SUPPORT_CLASSES_COLOR_NAVY,				//	(0,0,128)
						AI_SUPPORT_CLASSES_COLOR_TOMATO,			//	(255,99,71)
						AI_SUPPORT_CLASSES_COLOR_ORANGE,			//	(255,165,0)
						AI_SUPPORT_CLASSES_COLOR_DARK_GREEN,		//	(0,100,0)
						AI_SUPPORT_CLASSES_COLOR_TURQUOISE,			//	(64,224,208)
						AI_SUPPORT_CLASSES_COLOR_CHOCOLATE,			//	(210,105,30)
						AI_SUPPORT_CLASSES_COLOR_WHITE				//	(255,255,255)
						
					} AI_SUPPORT_CLASSES_color;
					
		/*---- data declarations ---------------------------------------------------*/
		/*---- function prototypes -------------------------------------------------*/
		class Location;
	
	/*
		****************************************************************************
		* PUBLIC DECLARATIONS 
		****************************************************************************
	*/
		/*---- data declarations ---------------------------------------------------*/
		extern class Location AI_SUPPORT_CLASSES_DefaultLocation;
	/*
		****************************************************************************
		* PUBLIC CLASS DEFINITIONS
		****************************************************************************
	*/
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Timer
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 06-03-2021
		// Description		: This class gives support for timer and system clock functions
		// Remarks			: This class will give support to Logger class and algorithms
		//						for profiling issues
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Timer
		{
			public:
				//	Public member functions
				void Start(void);
				long int Stop(void);
				long int Tick(void);
			
				//	Default Constructor 
				Timer(); 
				//	Destructor
				~Timer();

			private:
				//	Private variables
				std::chrono::time_point<std::chrono::system_clock>	systemStart;
				bool												running 	= false;
				std::chrono::time_point<std::chrono::system_clock>	start;

		};	//	class Timer
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Logger
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 06-03-2021
		// Description		: This class gives support for logging in a text file all
		//						the events that are needed to follow the sequence of
		//						events in the software
		// Remarks			:
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Logger
		{
			public:
				//	Public member functions
				bool Filename(string filename);
				template <class GenericType> 
				bool Write(GenericType loggerGenericType);
				bool WriteLine(string loggerString);
				class Timer& SystemTime(void);
				
				//	Operators
				friend Logger& operator << (Logger& logger, const class Timer& loggerTimer);
				friend Logger& operator << (Logger& logger, const int& loggerInteger);
				friend Logger& operator << (Logger& logger, const long& loggerLong);
				friend Logger& operator << (Logger& logger, const float& loggerFloat);
				friend Logger& operator << (Logger& logger, const double& loggerDouble);
				friend Logger& operator << (Logger& logger, const string& loggerString);
			
				//	Default Constructor 
				Logger(); 
				//	Parametrized Constructor 
				Logger(string filename);
				//	Destructor
				~Logger();

			private:
				//	Private variables
				bool			initialized 	= false;
				string			filename		= "";
				ofstream		outfile;
				class Timer		timer;

		};	//	class Logger
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Location
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 27-02-2021
		// Description		: This class represents a specific location
		// Remarks			:
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Location
		{
			public:
				//	Public member functions
				void Modify(int column, int row);
				int	Column(void);
				int Row(void);
				double LineIntercept(Location point);
				double LineSlope(Location point);
				double Distance(Location point);
				double Distance(Location& pointA, Location pointB);
				Location& Opposite(Location centralPoint);

				//	Operators
//				friend ostream& operator << (ostream& ostream, const Location& location);
				friend ostream& operator << (ostream& ostream, Location& location);
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
				void _Location(int column, int row);
			private:
				//	Private variables
				int	column;
				int	row;

		};	//	class Location
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: DsmLocation
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 27-02-2021
		// Description		: This class represents a specific location for DSM maps
		// Remarks			: It is derived from Location class
		//
		/////////////////////////////////////////////////////////////////////////////////
		class DsmLocation : public Location
		{
			public:
				//	Public member functions
				template <class GenericType> 
				void Elevation(DsmLocation location, GenericType genericTypeElevation);
				void Elevation(double elevation);
				double Elevation(void);
				void Obstacle(bool theLocationIsAnObstacle);
				bool Obstacle(void);

				//	Operators
				friend ostream& operator << (ostream& ostream, DsmLocation& location);
				DsmLocation& operator = (DsmLocation& location);
			
				//	Default Constructor 
				DsmLocation(); 
				//	Parametrized Constructors 
				DsmLocation(int column, int row);
				template <class GenericType> 
				DsmLocation(int column, int row, GenericType genericTypeElevation);
				//	Destructor
				~DsmLocation();

			protected:
				//	Protected member function
				void _Elevation(DsmLocation location, double elevation);
			private:

				//	Private variables
				double	elevation;
				bool	obstacle	= false;

		};	//	class DsmLocation
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: DsmInformation
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 26-02-2021
		// Description		: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain
		// Remarks			:
		//
		/////////////////////////////////////////////////////////////////////////////////
		class DsmInformation
		{ 
			public:
				//	Public member functions
				void Rows(int rows);
				void Columns(int columns);
				int Rows(void);
				int Columns(void);
				bool IsInDsmMap(Location location);
				double Elevation(Location location);
				double Elevation(int column, int row);
				bool Elevation(int column, int row, double elevation);
				bool Obstacle(int column, int row, bool theLocationIsAnObstacle);
				bool Obstacle(Location location);
				bool Obstacle(int column, int row);
				void GroundLevel(double groundLevelElevation);
				double GroundLevel(void);
				bool GroundLevel(Location location);
				bool LineOfSight(Location pointA, Location pointB);

				//	Default Constructor 
				DsmInformation();
				//	Parametrized Constructor 
				DsmInformation(int columns, int rows); 
				//	Destructor
				~DsmInformation();
				
				//	Assignment operator
				DsmInformation& operator = (DsmInformation &dsmInformation);
				
			protected:
				//	Protected member functions
				class Logger	logger;
				DsmLocation		*pLocation				= NULL; 
			private: 
				//	Private variables
				bool			initialized				= false;
				int				columns 				= AI_SUPPORT_CLASSES_INVALID_COLUMN;
				int				rows 					= AI_SUPPORT_CLASSES_INVALID_ROW;
				double			groundLevelElevation	= AI_SUPPORT_CLASSES_INVALID_DSM_ELEVATION;

				//	Private member functions

		};  //  class DsmInformation
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: TargetDsmInformation
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 06-03-2021
		// Description		: This class represents the information taken from a DSM file
		//						A DSM (Digital Surface Model) is a computer graphics 
		//						representation of elevation data to represent terrain but
		//						specialized with info on target
		// Remarks			: It is derived from DsmInformation class
		//
		/////////////////////////////////////////////////////////////////////////////////
		class TargetDsmInformation : public DsmInformation
		{
			public:
				//	Public member functions
				void DsmMapForTargetReset(DsmInformation& sourceDsmMap,
					// Default parameters
					bool includingForbiddenCloseToTargetLocations = false,
					Location targetLocation = {0,0},
					int minimumDistanceToTarget = 10,
					bool clearPreviousObstacles = true);
					
				bool ForbiddenDistance(int column, int row, bool forbiddenDistance);
				bool ForbiddenDistance(Location location);
				bool ForbiddenDistance(int column, int row);
				
				//	Default Constructor 
				TargetDsmInformation() : DsmInformation {} {};
				//	Parametrized Constructors 
				TargetDsmInformation(int columns, int rows) : DsmInformation {columns, rows} 
				{
				}
				//	Destructor
				~TargetDsmInformation();
				
				//	Assignment operator
				TargetDsmInformation& operator = (DsmInformation &dsmInformation);

			protected:
				//	Protected member function
			private:
				//	Private member function
				//	Private variables

		};	//	class TargetDsmInformation

		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Graphic
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 02-03-2021
		// Description		: This class represents a graphic
		// Remarks			: Currently supported formats (.png and GeoTIFF)
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Graphic
		{
			public:
				//	Public member functions
				bool Open(string filename, string description = "", bool fromShadow = false, string author = "Pablo Daniel Jelsky", string software = "AI Home Exercise");
				bool Close(AI_SUPPORT_CLASSES_graphicType typeOfGraphic);
				bool Filename(string filename, bool fromShadow = false);
				void Columns(int columns);
				int Columns(void);
				void Rows(int rows);
				int Rows(void);
				bool Point(class Location at, AI_SUPPORT_CLASSES_color pixelColor);													//	for .png files
				bool Point(class Location at, int elevation);																		//	for GeoTIFF files
				bool Line(class Location from, class Location to, AI_SUPPORT_CLASSES_color lineColor, bool copyToShadow = false);	//	for .png files
				bool Arrow(class Location from, class Location to, AI_SUPPORT_CLASSES_color arrowColor, bool copyToShadow = false);	//	for .png files
				bool Cross(class Location at, AI_SUPPORT_CLASSES_color crossColor, bool copyToShadow = false);						//	for .png files
				bool Text(class Location from, string text, 
					//	Default arguments
					AI_SUPPORT_CLASSES_color textColor = AI_SUPPORT_CLASSES_COLOR_WHITE, 
					int fontSize = 12,
					string fontPathAndFilename = "/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf",
					double angle = 0.0			//	angle is the text angle in degrees
					);																												//	for .png files
					
				//	Operators
				Graphic& operator = (Graphic& graphic);
			
				//	Default Constructor 
				Graphic(); 
				//	Parametrized Constructors 
				Graphic(int columns, int rows);
				//	Destructor
				~Graphic();

			protected:
				//	Protected member function
				
			private:
				//	Private variables
				bool			initialized 			= false;
				string			filename				= "";
				int				columns;
				int				rows;
				
				//	PNGWriter object for .png graphic file
				class pngwriter	*pPngObject				= NULL;
				class pngwriter	*pPngObjectShadow		= NULL;
				//	GDAL objects for GeoTIFF graphic file
				/* declare pointer variables that will hold memory
				   * addresses (or "point to") for two GDALDataset
				   * objects, one for the grib file and one for the
				   * output Geotiff.
				   */
 				GDALDataset 	*geotiffDataset			= NULL;
				GDALDriver 		*driverGeotiff			= NULL;			//	also declare pointers for Geotiff
				GDALRasterBand	*geotiffBand			= NULL;			//	and raster band object(s)
				float			*pafWriteDspMap			= NULL;
				
				//	Private member functions
				void _Update(bool fromShadow = false);
				bool _IsInGraphic(Location location);

		};	//	class Graphic
		
	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/

#endif	// __AI_SUPPORT_CLASSES_IFC_H__
