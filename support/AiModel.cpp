//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiModel.cpp
//
// Version:			01.01
//
// Description:		Model classes the AI home excercise source file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
//
// Copyright:
//
// Remarks:			In this module the objective is to create model base class that will be derived as agent or target classes
//
//	DEVELOPMENT HISTORY:
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	02-03-2021	Pablo Daniel Jelsky		01			00			Initial
//	05-03-2021	Pablo Daniel Jelsky		01			01			Addition of new Agent class derived from new Target class based on Model class
//																Modification of internal representation
//																	of pixels.
//																The internal representation of the DSM map in the DsmInformation class is that 
//																the south-west (down-left) pixel is (0,0), and all the pixels are positive, 
//																and therefore, pixel in the north-east (up-right) is (Columns-1, Rows-1), where 
//																Columns is the total number of columns of the DSM file, and Rows is the total
//																number of rows of the DSM file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	========
//	========
//	Model // 
//	========
//	========
//	The model class will use composition between internal structures and classes like: DsmInformation, and use of A* algorithm function, or
//	libraries like GDAL (to read and write GeoTIFF files), and PNGWriter (to read/write .png files)
//
//	The libraries used by this module:
//
//	GDAL
//	====
//		This library is used to read and create GetoTIFF files
//			GDAL is a translator library for raster and vector geospatial data formats that is released under an X/MIT style Open Source License by the Open Source Geospatial Foundation. 
//			As a library, it presents a single raster abstract data model and single vector abstract data model to the calling application for all supported formats. 
//			It also comes with a variety of useful command line utilities for data translation and processing.
//				Web site: https://gdal.org/
//				library is located in /usr/lib/libgdal.a (called by g++ linker with -lgdal), for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/gdal/, for simplicity the library will be copied inside the "include" directory in the project
//	PNGwriter
//	=========
//		This "library" is included as two files that will wrap the png library, pngwriter.cc and pngwriter.h
//		This module will use of libraries, the png library (for creating and reading .png files) and the freetype library to write text inside the .png files
//			PNGwriter is a very easy to use open source graphics library that uses PNG as its output format. The interface has been designed to be as simple and intuitive as possible. 
//			It supports plotting and reading pixels in the RGB (red, green, blue), HSV (hue, saturation, value/brightness) and CMYK (cyan, magenta, yellow, black) colour spaces, 
//			basic shapes, scaling, bilinear interpolation, full TrueType antialiased and rotated text support, bezier curves, opening existing PNG images and more.
//				Web site: http://pngwriter.sourceforge.net/
//				source and include files are located under the "support" directory inside the project and are compiled and linked with the help of the Makefile
//	libpng
//	======
//		This library is used by PNGWriter module
//			libpng is the official PNG reference library. It supports almost all PNG features, is extensible, and has been extensively tested for over 23 years. 
//			The home site for development versions (i.e., may be buggy or subject to change or include experimental features) is https://libpng.sourceforge.io/, 
//			and the place to go for questions about the library is the png-mng-implement mailing list.
//				Web site: http://libpng.org/pub/png/libpng.html
//				library is located in /usr/lib/x86_64-linux-gnu/libpng.a (link to /usr/lib/x86_64-linux-gnu/libpng16.a) (called by g++ linker with -lpng), 
//					for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/libpng (link to /usr/include/libpng16), for simplicity the library will be copied inside the "include" directory in the project
//	FreeType2
//	=========
//		This library is used by PNGWriter module		
//			FreeType is a freely available software library to render fonts.
//			It is written in C, designed to be small, efficient, highly customizable, and portable while capable of producing high-quality output (glyph images) of most vector and bitmap font formats.	
//				Web site: https://www.freetype.org/
//				library is located in /usr/lib/x86_64-linux-gnu/libfreetype.a (called by g++ linker with -lfreetype), for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/freetype2, for simplicity the library will be copied inside the "include" directory in the project	
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
		#include "AiModel.h"
	
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
	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This constructor will create a non valid object
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Model::Model()
		{
			this->initialized	= false;
			this->_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
			
		}	//	Model::Model()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This constructors take as parameter GeoTIFF file that
		//							will be the base of the DSM information map
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: string geoTiffFilename (name of the GeoTIFF file)
		//						 string modelName (name that will be used for logger and .csv files)
		/////////////////////////////////////////////////////////////////////////////////
		Model::Model(string geoTiffFilename, string modelName)
		{
			this->Initialize(geoTiffFilename, modelName);
			this->_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
			
		}	//	Model::Model()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This destructor destroys the array data created with CPLMalloc()
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Model::~Model()
		{
			if (NULL != this->pafScanline)
				CPLFree(this->pafScanline);

		}	//	Model::~Model()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Target
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents the target class derived
		//							from model class
		// Function description	: This constructor will create a non valid object
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Target::Target()
		{
			this->_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
			
		}	//	Target::Target()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Target
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents the target class derived
		//							from model class
		// Function description	: 
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Target::~Target()
		{
		}	//	Target::~Target()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents the agent class derived
		//							from target class
		// Function description	: This constructor will create a non valid object
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Agent::Agent()
		{
			this->_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, true);
			
		}	//	Agent::Agent()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This class represents the agent class derived
		//							from target class
		// Function description	: 
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Agent::~Agent()
		{
		}	//	Agent::~Agent()

	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: DsmMapFileColumns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function returns the DSM map info
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		class DsmInformation & Model::DsmMap(void)
		{
			return this->dsmMapInfo;
			
		}	//	Model::DsmMap()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Initialize
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This public class member takes as parameter GeoTIFF
		// 							file that will be the base of the DSM information map
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: string geoTiffFilename (name of the GeoTIFF file)
		//						 string modelName (name that will be used for logger and .csv files)
		/////////////////////////////////////////////////////////////////////////////////
		void Model::Initialize(string geoTiffFilename, string modelName)
		{
			if (!this->initialized)
			{
				string	loggerDirectory	= "output/";
				string	loggerSuffix	= ".txt";
				
				this->geoTiffFilename	= geoTiffFilename;
				this->modelName			= modelName;
				//	Creating the logger object
				this->logger.Filename(loggerDirectory + this->modelName + loggerSuffix);
				//	Registering the GDAL drivers
				this->_GdalDriverInitialization();
				//	Raster the GeoTIFF input file inside the object for further use
				if (!_DsmInputFileRaster())
				{
					this->initialized	= false;
					return;
				}
				
				this->graphic.Rows(this->dsmMapInfo.Rows());
				this->graphic.Columns(this->dsmMapInfo.Columns());
			
				this->initialized	= true;
			}
			
		}	//	Model::Initialize()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: DsmMapFileColumns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function returns the number of 
		//							columns in the input DSM file
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		int Model::DsmMapFileColumns(void)
		{
			return this->dsmMapInfo.Columns();
			
		}	//	Model::DsmMapFileColumns()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: DsmMapFileColumns
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function returns the number of 
		//							columns in the input DSM file
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		int Model::DsmMapFileRows(void)
		{
			return this->dsmMapInfo.Rows();
			
		}	//	Model::DsmMapFileRows()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: CurrentLocation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function sets the model current location
		// Remarks				:Returns true, if it is a ground level location
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: current location
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::CurrentLocation(Location currentLocation)
		{
			//	Verify the location is a valid one
			if (!this->dsmMapInfo.IsInDsmMap(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to set current location in DSM map: CURRENT LOCATION is NOT in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return false;
			}
			if (!this->dsmMapInfo.GroundLevel(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to set current location in DSM map: CURRENT LOCATION is not at GROUND LEVEL in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return false;
			}
			
			this->logger << this->logger.SystemTime() << "Current location in DSM map set to [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";

			//	If the current location is at ground level
			this->currentLocation	= currentLocation;
			return true;
			
		}	//	Model::CurrentLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: CurrentLocation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function returns the model current 
		//							location
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location& Model::CurrentLocation(void)
		{
			return this->currentLocation;
			
		}	//	Model::CurrentLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: DestinationLocation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function sets the model destination
		//							location
		// Remarks				: Returns true, if it is a ground level location
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: destination location
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::DestinationLocation(Location destinationLocation)
		{
			//	Verify the location is a valid one
			if (!this->dsmMapInfo.IsInDsmMap(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to set destination location in DSM map: DESTINATION LOCATION is NOT in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return false;
			}
			if (!this->dsmMapInfo.GroundLevel(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to set destination location in DSM map: DESTINATION LOCATION is not at GROUND LEVEL in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return false;
			}
			
			this->logger << this->logger.SystemTime() << "Destination location in DSM map set to [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
			//	If the destination location is at ground level
			this->destinationLocation	= destinationLocation;
			return true;
			
		}	//	Model::DestinationLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: DestinationLocation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description_: This public member function returns the model destination 
		//							location
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location& Model::DestinationLocation(void)
		{
			return this->destinationLocation;
			
		}	//	Model::DestinationLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: FindPath
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function finds a path from current
		//							to destination location
		// Remarks				: Returns the model path length
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: .csv results file
		/////////////////////////////////////////////////////////////////////////////////
		int Model::FindPath(string csvModelPathFilename)
		{
			int 		modelPathLength;
			Location	currentLocation			= this->CurrentLocation();
			Location	destinationLocation		= this->DestinationLocation();
			long int	algorithmDuration[3];
			
			//	Verify the locations are valid ones
			if (!this->dsmMapInfo.IsInDsmMap(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from source to destination: CURRENT LOCATION is NOT in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (!this->dsmMapInfo.IsInDsmMap(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from source to destination: DESTINATION LOCATION is NOT in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (this->dsmMapInfo.Obstacle(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from source to destination: CURRENT LOCATION is an OBSTACLE in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (this->dsmMapInfo.Obstacle(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from source to destination: DESTINATION LOCATION is an OBSTACLE in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			
			algorithmDuration[0]	= this->Tick();
			cout << "Start tick = " << algorithmDuration[0] << endl;
			modelPathLength = AStarSearch(this->aStarSearchPixelsMovementTypeForFindPath, this->aStartSearchPixelsCouldStayOnPlace, 
				this->dsmMapInfo, this->CurrentLocation(), this->DestinationLocation(), 
				this->pathList, csvModelPathFilename);
			algorithmDuration[1]	= this->Tick();
			cout << "End tick = " << algorithmDuration[1] << endl;
			algorithmDuration[2]	= algorithmDuration[1] - algorithmDuration[0];
			cout << "Algorithm time for " << currentLocation << " to " << destinationLocation << " is " << algorithmDuration[2] << " milliseconds" << endl;
			this->logger << this->logger.SystemTime() << "Algorithm time for [" << currentLocation.Column() << ", " <<  currentLocation.Row()
				<< "] to [" << destinationLocation.Column() << "," << destinationLocation.Row() << "] is " << algorithmDuration[2] << " milliseconds\n";
				
			return modelPathLength;
			
		}	//	Model::FindPath
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: NextLocation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function returns next location of
		//							the path from current to destination location
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Location& Model::NextLocation(void)
		{
			if (!this->pathList.empty())
			{
				this->pathList.pop_front();
				this->CurrentLocation(this->pathList.front());
			}
			
			return this->CurrentLocation();
			
		}	//	Model::NextLocation()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: LineOfSight
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This member function returns the visibility between
		//							two location (line of sight = LOS)
		// Remarks				:Returns true, if the locations are visible between them
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: pointA and pointB (as Location)
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::LineOfSight(Location pointA, Location pointB)
		{
			return (this->dsmMapInfo.LineOfSight(pointA, pointB));
			
		}	//	Model::LineOfSight()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: DsmMapForTargetReset
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents an agent person
		// Function description	: This member function updates the internal DSM
		//							map (in agent) with the information from target DSM
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: 
		/////////////////////////////////////////////////////////////////////////////////
		void Agent::DsmMapForTargetReset(void)
		{
			this->targetDsmMapInfo.DsmMapForTargetReset(this->dsmMapInfo);
			
		}	//	Agent::DsmMapForTargetReset()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: DsmMapForTargetResetIncludingForbiddenLocations
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents an agent person
		// Function description	: This member function updates the internal DSM
		//							map (in agent) with the information from target DSM,
		//							including the marking of locations that are close
		//							enough to target
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: target location, minimum distance to target and
		//							boolean indicating if need to clear previous
		//							obstacles
		/////////////////////////////////////////////////////////////////////////////////
		void Agent::DsmMapForTargetResetIncludingForbiddenLocations(
						Location targetLocation,
						//	Default parameter
						int minimumDistanceToTarget,
						bool clearPreviousObstacles)
		{
			TargetLocation(targetLocation);
			this->targetDsmMapInfo.DsmMapForTargetReset(this->dsmMapInfo, true, targetLocation, minimumDistanceToTarget, clearPreviousObstacles);
			
		}	//	Agent::DsmMapForTargetResetIncludingForbiddenLocations()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: FindPathToFollowTarget
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents an agent person
		// Function description	: This member function updates the internal DSM
		//							map (in agent) with the information from target DSM,
		//							including the marking of locations that are close
		//							enough to target
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: number of steps to target
		/////////////////////////////////////////////////////////////////////////////////
		int Agent::FindPathToFollowTarget(
									string csvAgentPathFilename,
									Location targetLocation,
									//	Default parameter
									int minimumDistanceToTarget)
		{
			int 		agentPathLength;
			Location	currentLocation			= this->CurrentLocation();
			Location	destinationLocation		= targetLocation;
			list <class Location>				tentativeLocationsClosedEnoughToTarget;
			
			//	Verify the locations are valid ones
			if (!this->dsmMapInfo.IsInDsmMap(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from agent to target: AGENT CURRENT LOCATION is NOT in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (!this->dsmMapInfo.IsInDsmMap(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from agent to target: TARGET LOCATION is NOT in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (this->dsmMapInfo.Obstacle(currentLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from agent to target: AGENT CURRENT LOCATION is an OBSTACLE in DSM map => [" << currentLocation.Column() << ", " << currentLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			if (this->dsmMapInfo.Obstacle(destinationLocation))
			{
				this->logger << this->logger.SystemTime() << "While trying to find path from agent to target: TARGET LOCATION is an OBSTACLE in DSM map => [" << destinationLocation.Column() << ", " << destinationLocation.Row() << "]\n";
				return EXIT_FAILURE;
			}
			
			//	Reset the DSM map and including all the forbidden locations (close enough to target)
			//	TODO: MUCH BETTER, NOT HARD CODED
			Location	tentativeTargetLocation;
			bool		dsmMapReset				= false;
			//	EAST (perform the others but before function)
			tentativeTargetLocation	= destinationLocation;
			tentativeTargetLocation.Modify(destinationLocation.Column()-1, destinationLocation.Row());
			if (!this->dsmMapInfo.Obstacle(tentativeTargetLocation.Column(), tentativeTargetLocation.Row()))
			{
				//	If the location is a valid one
				DsmMapForTargetResetIncludingForbiddenLocations(targetLocation, AI_MODEL_MINIMUM_DISTANCE_FROM_AGENT_TO_TARGET, dsmMapReset ? false : true);
				dsmMapReset	= true;
			}
			
			//	Look for a possible list of targets to be used with A* algorithm
			_ListOfPossibleTargets(tentativeLocationsClosedEnoughToTarget, 5);

			//	Activate
			agentPathLength = AStarSearch(this->aStarSearchPixelsMovementTypeForFindPath, this->aStartSearchPixelsCouldStayOnPlace, 
				this->targetDsmMapInfo, currentLocation, destinationLocation,  
				this->pathList, csvAgentPathFilename);
				
			return agentPathLength;
		
		}	//	Agent::FindPathToFollowTarget()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicOpen
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function opens an output graphic
		//							file based on the raster information in it
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was created,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic name
		//					Default parameter:
		//							graphic description
		//							if open from shadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicOpen(string filename, string description, bool fromShadow)
		{
			this->graphic.Open(filename, description, fromShadow);

			return true;
			
		}	//	Model::GraphicOpen()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicPreparation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function prepares an output graphic
		//							file based on the raster information in it
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was prepared,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: clear previous graphic (true, if clear, false otherwise)
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicPreparation(bool clearPreviousGraphic)
		{
			int							row, column;
			AI_SUPPORT_CLASSES_color	pixelColor;

			for (row = 0; row < this->dsmMapInfo.Rows(); row++)
			{
				for (column = 0; column < this->dsmMapInfo.Columns(); column++)
				{
					Location	pixel(column, row);
					
					int	elevation	=  this->dsmMapInfo.Elevation(column, row);
					
					//	For .png
					if (1 == this->elevationColor.count(elevation))
					{
						//	If there is a match for this elevation
						pixelColor	= (AI_SUPPORT_CLASSES_color) this->elevationColor.at(elevation);
						this->graphic.Point(pixel, pixelColor);
					}
					//	For GeoTIFF
					this->graphic.Point(pixel, elevation);
				}
			}
				
			return true;
				
		}	//	Model::GraphicPreparation()
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicLine
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function draws a line in the graphic
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was prepared,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: from and to locations, line color
		//					Default parameters:
		//							copy to shadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicLine(Location from, Location to, 
			AI_SUPPORT_CLASSES_color lineColor, 
			//	Default arguments
			bool copyToShadow)
		{
			if (from == to)
			{
				cout << "Locations are the same one, and therefore the line is not drawn...\n";
				return false;
			}
			
			return (this->graphic.Line(from, to, lineColor, copyToShadow));
			
		}	//	Model::GraphicLine()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicArrow
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function draws an arrow in the graphic
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was prepared,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: from and to locations, arrow color
		//					Default parameters:
		//							copy to shadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicArrow(Location from, Location to, 
						AI_SUPPORT_CLASSES_color arrowColor, 
						//	Default arguments
						bool copyToShadow)
		{
			if (from == to)
			{
				cout << "Locations are the same one, and therefore the arrow is not drawn...\n";
				return false;
			}
			
			return (this->graphic.Arrow(from, to, arrowColor, copyToShadow));
						
		}	//	Model::GraphicArrow()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicCross
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function draws a cross in the graphic
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was prepared,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: at location, cross color
		//					Default parameters:
		//							copy to shadow
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicCross(Location at, 
						AI_SUPPORT_CLASSES_color crossColor, 
						//	Default arguments
						bool copyToShadow)
		{
			return (this->graphic.Cross(at, crossColor, copyToShadow));
						
		}	//	Model::GraphicCross()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicText
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 04-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function displays a text in the graphic
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was prepared,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: text location, text
		//					Default parameters:
		//							text color, font size
		//							font path and filename, angle
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicText(class Location from, string text, 
			//	Default arguments
			AI_SUPPORT_CLASSES_color textColor, 
			int fontSize,
			string fontPathAndFilename,
			double angle)					//	angle is the text angle in degrees
		{
			return (this->graphic.Text(from, text, textColor, fontSize, fontPathAndFilename, angle));
			
		}	//	Model::GraphicText()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicClose
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function closes an output graphic
		//							file based on the raster information in it
		// Remarks				: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was created,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic type (.png or GeoTIFF)
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::GraphicClose(AI_SUPPORT_CLASSES_graphicType typeOfGraphic)
		{
			this->graphic.Close(typeOfGraphic);
			
			return true;
			
		}	//	Model::GraphicClose()

	/*
		****************************************************************************
		* PUBLIC CLASS OPERATOR DEFINITIONS
		****************************************************************************
	*/

	/*
		****************************************************************************
		* PROTECTED CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: _AStarAlgorithmConfiguration
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This protected member function configures the A* algorithm
		// Remarks				: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_pixelsMovementType aStarSearchPixelsMovementTypeForFindPath, bool possibilityOfNotMoving)
		{
			switch (aStarSearchPixelsMovementTypeForFindPath)
			{
				case AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT:
				case AI_SUPPORT_ALGORITHMS_8_PIXELS_MOVEMENT:
				case AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT:
					this->aStarSearchPixelsMovementTypeForFindPath	= aStarSearchPixelsMovementTypeForFindPath;
					break;
				default:
					this->logger << this->logger.SystemTime() << "Parameter aStarSearchPixelsMovementTypeForFindPath = " << aStarSearchPixelsMovementTypeForFindPath << "is not a valid one in _AStarAlgorithmConfiguration()\n";
					return false;
			}
			
			this->aStartSearchPixelsCouldStayOnPlace	= (possibilityOfNotMoving) ? true : false;
			return true;
			
		}	//	 Model::_AStarAlgorithmConfiguration()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: _AStarAlgorithmConfiguration
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This class represents an agent person
		// Function description	: This protected member function configures the A* algorithm
		// Remarks				: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		bool Agent::_AStarAlgorithmConfigurationForTarget(AI_SUPPORT_ALGORITHMS_pixelsMovementType aStarSearchPixelsMovementTypeForFindPath, bool possibilityOfNotMoving)
		{
			switch (aStarSearchPixelsMovementTypeForFindPath)
			{
				case AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT:
				case AI_SUPPORT_ALGORITHMS_8_PIXELS_MOVEMENT:
				case AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT:
					this->aStarSearchPixelsMovementTypeForFindPathForTarget	= aStarSearchPixelsMovementTypeForFindPath;
					break;
				default:
					this->logger << this->logger.SystemTime() << "Parameter aStarSearchPixelsMovementTypeForFindPath = " << aStarSearchPixelsMovementTypeForFindPathForTarget << "is not a valid one in _AStarAlgorithmConfiguration()\n";
					return false;
			}
			
			this->aStartSearchPixelsCouldStayOnPlaceForTarget	= (possibilityOfNotMoving) ? true : false;
			return true;
			
		}	//	 Agent::_AStarAlgorithmConfigurationForTarget()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: _GdalDriverInitialization
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This protected member function that will register the
		//							GDAL drivers for reading/creating GeoTIFF files
		// Remarks				: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		void Model::_GdalDriverInitialization(void)
		{
			//  Register all the GDAL drivers
			GDALAllRegister();
			
			this->logger << this->logger.SystemTime();
			this->logger.WriteLine("*** GDAL Driver Initialization ***");
			this->logger.WriteLine("\tThe following format drivers are configured and support output:");
			
			for (int iDriverFormat = 0; iDriverFormat < GDALGetDriverCount(); iDriverFormat++)
			{
				string		loggerString;
				GDALDriverH hDriver = GDALGetDriver(iDriverFormat);

				if (GDALGetMetadataItem(hDriver, GDAL_DCAP_RASTER, nullptr) != nullptr &&
				    (GDALGetMetadataItem(hDriver, GDAL_DCAP_CREATE, nullptr ) != nullptr
				    || GDALGetMetadataItem(hDriver, GDAL_DCAP_CREATECOPY, nullptr ) != nullptr))
				{
					loggerString	= "\t\t" + (string) GDALGetDriverShortName(hDriver) + ":  " + (string) GDALGetDriverLongName(hDriver) + "\n";
					this->logger << loggerString;
				}
			}
			   
		}   //	Model::_GdalDriverInitialization(void)
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: _DsmInputFileRaster
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 05-03-2021
		// Class description	: This base class represents the model that will be derived
		//							as a person (class) that could be an agent, a target, etc
		// Function description	: This protected member function read the GeoTIFF file and 
		//							raster it inside the object for further use
		// Remarks				: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		bool Model::_DsmInputFileRaster(void)
		{
			const int	BAND_TO_BE_FETCHED = 1;	// Taken for granted that there is ONLY one band in this DSM map
				
			this->logger << this->logger.SystemTime();
			this->logger.WriteLine("*** GeoTIFF DSM Input File Raster Operation ***");
			  
			//  Opening the File        
			this->poDataset = (GDALDataset *) GDALOpen(this->geoTiffFilename.c_str(), GA_ReadOnly);
			
			if (NULL == poDataset)
			{
				this->logger << "\t" <<  this->geoTiffFilename << " file could not be opened...\n";
			}
			else
			{
				this->logger << "\t" <<  this->geoTiffFilename << " file was successfully opened...\n";

				//  Getting Dataset Information
				double        adfGeoTransform[6];
				
				this->logger << "\tDriver: " << this->poDataset->GetDriver()->GetDescription() << "/" <<  this->poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME) << "\n";
				this->logger << "\tDSM file size is: " << this->poDataset->GetRasterXSize() << " columns by " << this->poDataset->GetRasterYSize() << " rows by " << this->poDataset->GetRasterCount() << " pixel" << "\n";
				if (CE_None == poDataset->GetGeoTransform(adfGeoTransform))
					this->logger << "\tOrigin (top-left x = " << adfGeoTransform[0] << ", top-left y = " << adfGeoTransform[3] << "), pixel size = (w-e pixel resolution = " 
								<< adfGeoTransform[1] << ", n-s pixel resolution (negative value) = " << adfGeoTransform[5] << ")\n";
				
				//	Create the DSM map info object with the GeoTIFF size
				this->dsmMapInfo.Rows(poDataset->GetRasterYSize());
				this->dsmMapInfo.Columns(poDataset->GetRasterXSize());

				{
					CPLErr	rasterIoError;
					
					//  Fetching a Raster Band
					GDALRasterBand	*poBand;
					int				nBlockXSize, nBlockYSize;
					int				bGotMin, bGotMax;
					double			adfMinMax[2];
					
					poBand = this->poDataset->GetRasterBand(BAND_TO_BE_FETCHED);
					poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
					this->logger << "\nDSM file block is " << nBlockXSize << " by " << nBlockYSize << " type is " << GDALGetDataTypeName(poBand->GetRasterDataType()) 
								<< " and color interpretation is " << GDALGetColorInterpretationName(poBand->GetColorInterpretation()) << "\n";

					adfMinMax[0]	= poBand->GetMinimum(&bGotMin);
					adfMinMax[1]	= poBand->GetMaximum(&bGotMax);
					
					if (!(bGotMin && bGotMax))
					{
						GDALComputeRasterMinMax((GDALRasterBandH) poBand, true, adfMinMax);
						this->dsmMapInfo.GroundLevel(adfMinMax[0]);
						this->logger << "\t\tMinimum elevation = " << adfMinMax[0] << ", maximum elevation = " << adfMinMax[1] << "\n";
						this->logger << "\t\tDSM map ground level set to " << this->dsmMapInfo.GroundLevel() << "\n";
					}
					if (poBand->GetOverviewCount() > 0)
					{
						this->logger << "\t\tBand has " << poBand->GetOverviewCount() << " overviews.\n";
					}

					if (NULL != poBand->GetColorTable())
					{
						this->logger << "\t\tBand has a color table with " << poBand->GetColorTable()->GetColorEntryCount() << " entries.\n";
					}
					
					//	Reading Raster Data
					//	Reading Raster Data
					//	Reading Raster Data
					int		nXSize = poBand->GetXSize();
					int		nYSize = poBand->GetYSize();
					
					this->pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize*nYSize);
					if (NULL == this->pafScanline)
					{
						this->logger << "\tThe raster data array could NOT be created.\n";
						return false;
					}
					else
					{
						this->logger << "\tThe raster data array was successfully created.\n";
					}

					rasterIoError	= poBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize,
														this->pafScanline, nXSize, nYSize, GDT_Float32,
														0, 0);
					if (CE_None != rasterIoError)
					{
						this->logger << "\tRasterIO(GF_Read) function returns with error: " << rasterIoError << "\n";
						cout << "\tRasterIO(GF_Read) function returns with error: " << rasterIoError << "\n";
						return false;
					}
							 			
		 			//	Insert the array information into the DSM map object and set the color for each different elevation
		 			{
		 				int	column, row;
		 				int	color	= (int) AI_SUPPORT_CLASSES_COLOR_BLACK;
		 				
						//	Sets the color of ground level to black
		 				this->elevationColor.insert({this->dsmMapInfo.GroundLevel(), (AI_SUPPORT_CLASSES_color) color++});
		 				
		 				for (row = 0; row < nYSize; row++)
		 					for (column = 0; column < nXSize; column++)
		 					{
								int	elevation	= this->pafScanline[(row * nXSize) + column];

								if (0 == this->elevationColor.count(elevation))
								{
									//	If the index of the elevation was not found in the unorder map,
									//	then insert it and set its color to the next color enumerator
									this->elevationColor.insert({elevation, (AI_SUPPORT_CLASSES_color) color++});
								}
								
								//	Inserts the elevation info into the DSM map
								//	And also sets the obstacle as everything different thant ground level (per project)
								//		Because of unification of pixel coordinates
								//		to internal representation where SW pixel is 0,0
								//		and info from GeoTIFF file is NW pixel as 0,0
								{
									int internalRepresentationColumn	= column;			// stays the same representation
									int internalRepresentationRow		= (nYSize-1) - row;	// the order changes in the representation
									bool obstacle						= (elevation == this->dsmMapInfo.GroundLevel()) ? false : true;
									                                    
									this->dsmMapInfo.Elevation(internalRepresentationColumn, internalRepresentationRow, elevation);
									this->dsmMapInfo.Obstacle(internalRepresentationColumn, internalRepresentationRow, obstacle);
								}
		 					}
		 			}
				}
			}

			return true;

		}   //  Model::_DsmInputFileRaster()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Agent
		// Function				: _ListOfPossibleTargets
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 06-03-2021
		// Class description	: This base class represents the agent person
		// Function description	: This protected member function gets a list of possible
		//							targets that will suit the A* search with all the 
		//							constraints
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: list of possible targets, maximum number of possible targets
		/////////////////////////////////////////////////////////////////////////////////
		bool Agent::_ListOfPossibleTargets(list <Location>& targetPossibleList, int maximumNumberOfPossibleTargets)
		{
			Location	temporalLocation;
			
//			targetPossibleList.push_back(temporalLocation);
			
			return true;

		}	//	Agent::_ListOfPossibleTargets()
	/*
		****************************************************************************
		* PRIVATE CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/









