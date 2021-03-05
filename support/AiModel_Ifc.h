//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiModel_Ifc.h
//
// Version:			01.00
//
// Description:		Model classes the AI home excercise interface file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
//
// Copyright:		
//
// Remarks:			In this module the objective is to create model classes that will be instantiated as agents or targets
//
//	DEVELOPMENT HISTORY:
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	02-03-2021	Pablo Daniel Jelsky		01			00			Initial
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __AI_MODEL_IFC_H__
#define	__AI_MODEL_IFC_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <list>				// for STL lists
		#include <string>			// for C++ strings
		#include <cstring>			// for C strings
		#include <unordered_map>	// for STL unorder maps
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "AiSupportAlgorithms_Ifc.h"
		#include "AiSupportClasses_Ifc.h"
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;	
		/*---- defines --------------------------------------------------------------*/
		/*---- enums --------------------------------------------------------------*/
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
		// Class name		: Model
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 02-03-2021
		// Description		: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Remarks         : This class will have as internal info:
		//						DSM map information object
		//						GDAL dataset object, that will read from GeoTIFF file
		//							into the DSM maap information object
		//						use of A* algorithm to reach any point in the DSM map
		//						current, and destination position 
		//						list of location objects that include the steps from 
		//							current position to destination position
		//						graphic object to be created
		//						logger class to send info to text files
		//						
		/////////////////////////////////////////////////////////////////////////////////	
		class Model
		{ 
			public:
				bool GraphicOpen(string filename, string description = "");
				bool GraphicPreparation(bool clearPreviousGraphic);
				bool GraphicText(class Location from, string text, 
					//	Default arguments
					AI_SUPPORT_CLASSES_color textColor = AI_SUPPORT_CLASSES_COLOR_WHITE, 
					int fontSize = 12,
					string fontPathAndFilename = "/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf",
					double angle = 0.0			//	angle is the text angle in degrees
					);
				bool GraphicClose(graphicType typeOfGraphic);
				int FindPath(aStarSearchPixelsMovementType typeOfPixelMovement, bool possibilityOfNotMoving, string csvModelPathFilename);
				bool CurrentLocation(Location currentLocation);
				Location& CurrentLocation(void);
				bool DestinationLocation(Location destinationLocation);
				Location& DestinationLocation(void);
				Location& NextLocation(void);
			
				//	Default Constructor 
				Model();
				//	Parametrized Constructors 
				Model(string geoTiffFilename, string modelName);
				//	Destructor
				~Model();
				
			protected:
				//	Protected member functions
				
			private: 
				//	Private variables
				bool    										initialized		= false;
				string											geoTiffFilename;
				string											modelName;
				class DsmInformation							dsmMapInfo;
				GDALDataset  									*poDataset		= NULL;
				float 											*pafScanline	= NULL;
				class Location									currentLocation, destinationLocation;
				unordered_map <int, AI_SUPPORT_CLASSES_color>	elevationColor;
				list <class Location>							pathList;
				class Graphic									graphic;
				class Logger									logger;
				
				//	Private member functions
				void _GdalDriverInitialization(void);
				bool _DsmInputFileRaster(void);
				
				
		};  //  class Model

#endif	// __AI_MODEL_IFC_H__
