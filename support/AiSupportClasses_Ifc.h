//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportClasses_Ifc.h
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
// Remarks:			
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
		typedef enum {GRAPHIC_TYPE_PNG, GRAPHIC_TYPE_GEOTIFF} graphicType;
		typedef enum {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_WHITE, COLOR_BLACK, COLOR_YELLOW, COLOR_CYAN, COLOR_MAGENTA} color;
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
				bool Filename(string filename);
				template <class GenericType> 
				bool Write(GenericType loggerGenericType);
				bool WriteLine(string loggerString);
				
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
				bool    	initialized 	= false;
				string		filename		= "";
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
				void Modify(int column, int row);
				int	Column(void);
				int Row(void);
				double LineIntercept(Location point);
				double LineSlope(Location point);

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
		// Remarks      	: It is derived from Location class
		/////////////////////////////////////////////////////////////////////////////////
		class DsmLocation : public Location
		{
			public:
				template <class GenericType> 
				void Elevation(DsmLocation location, GenericType genericTypeElevation);
				void Elevation(double elevation);
				double Elevation(void);
				void Obstacle(bool theLocationIsAnObstacle);
				bool Obstacle(void);

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
		// Remarks         : 
		/////////////////////////////////////////////////////////////////////////////////	
		class DsmInformation
		{ 
			public:
				void Rows(int rows);
				void Columns(int columns);
				int Rows(void);
				int Columns(void);
				double Elevation(int column, int row);
				bool Elevation(int column, int row, double elevation);
				bool Obstacle(int column, int row, bool theLocationIsAnObstacle);
				bool Obstacle(int column, int row);
				void GroundLevel(double groundLevelElevation);
				double GroundLevel(void);
				bool LineOfSight(Location pointA, Location pointB);

				//	Default Constructor 
				DsmInformation();
				//	Parametrized Constructor 
				DsmInformation(int columns, int rows); 
				//	Destructor
				~DsmInformation();
				
			private: 
				//	Private variables
				bool    		initialized				= false;
				DsmLocation		*pLocation				= NULL; 
				int     		columns 				= AI_SUPPORT_CLASSES_INVALID_COLUMN;
				int				rows 					= AI_SUPPORT_CLASSES_INVALID_ROW;
				double			groundLevelElevation	= AI_SUPPORT_CLASSES_INVALID_DSM_ELEVATION;
				class Logger	logger;
				//	Private member functions

				
		};  //  class DsmInformation
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Graphic
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 02-03-2021
		// Description		: This class represents a graphic
		// Remarks      	: Currently supported formats (.png and GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		class Graphic
		{
			public:
				bool Create(graphicType typeOfGraphic);
				void Filename(string filename);
				void Columns(int columns);
				int Columns(void);
				void Rows(int rows);
				int Rows(void);
				
				bool Line(class Location from, class Location to, color lineColor);
			
				//	Default Constructor 
				Graphic(); 
				//	Parametrized Constructors 
				Graphic(int columns, int rows);
				//	Destructor
				~Graphic();

			protected:
				//	Protected member function
				
			private:
				void _Update(void);
				
				//	Private variables
				bool			initialized 			= false;
/*
				string			fileHeaderTitle 		= "";
				string			fileHeaderAuthor		= "";
				string			fileHeaderDescription	= "";
				string			fileHeaderSoftware		= "";
				string			fileTextFont			= "/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf";
				int				fileTextFontSize		= 12;
				class Location	fileText(0,0);
				color			fileTextColor			= COLOR_WHITE;
*/
				string			filename				= "";
				int				columns;
				int				rows;
				
				//	PNGWriter object for .png graphic file
				class pngwriter	*pPngObject				= NULL;
				//	GDAL objects for GeoTIFF graphic file
				/* declare pointer variables that will hold memory
				   * addresses (or "point to") for two GDALDataset
				   * objects, one for the grib file and one for the
				   * output Geotiff.
				   */
 				GDALDataset 	*geotiffDataset			= NULL;
				GDALDriver 		*driverGeotiff			= NULL;			//	also declare pointers for Geotiff
				GDALRasterBand	*geotiffBand			= NULL;			//	and raster band object(s)
 

		};	//	class Graphic	
		
	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/

#endif	// __AI_SUPPORT_CLASSES_IFC_H__
