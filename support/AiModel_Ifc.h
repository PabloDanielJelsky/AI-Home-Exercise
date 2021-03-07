//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiModel_Ifc.h
//
// Version:			01.01
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
		#define	AI_MODEL_MINIMUM_DISTANCE_FROM_AGENT_TO_TARGET	10
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
		// Remarks				:This class will have as internal info:
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
				//	Public member functions
				class DsmInformation &DsmMap(void);
				int DsmMapFileColumns(void);
				int DsmMapFileRows(void);
				bool GraphicOpen(string filename, string description = "", bool fromShadow = false);
				bool GraphicPreparation(bool clearPreviousGraphic);
				bool GraphicLine(Location from, Location to, AI_SUPPORT_CLASSES_color lineColor, bool copyToShadow = false);
				bool GraphicArrow(Location from, Location to, AI_SUPPORT_CLASSES_color arrowColor, bool copyToShadow = false);
				bool GraphicCross(Location at, AI_SUPPORT_CLASSES_color crossColor, bool copyToShadow = false);
				bool GraphicText(class Location from, string text, 
					//	Default arguments
					AI_SUPPORT_CLASSES_color textColor = AI_SUPPORT_CLASSES_COLOR_WHITE, 
					int fontSize = 12,
					string fontPathAndFilename = "/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf",
					double angle = 0.0			//	angle is the text angle in degrees
					);
				bool GraphicClose(AI_SUPPORT_CLASSES_graphicType typeOfGraphic);
				int FindPath(string csvModelPathFilename);
				bool CurrentLocation(Location currentLocation);
				Location& CurrentLocation(void);
				bool DestinationLocation(Location destinationLocation);
				Location& DestinationLocation(void);
				Location& NextLocation(void);
				bool LineOfSight(Location pointA, Location pointB);

				//	Default Constructor 
				Model();
				//	Parametrized Constructors 
				Model(string geoTiffFilename, string modelName);
				//	Destructor
				~Model();

			protected:
				//	Protected member functions
				void _Initialize(string geoTiffFilename, string modelName);
				bool _AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_pixelsMovementType aStarSearchPixelsMovementTypeForFindPath, bool possibilityOfNotMoving);
				void _GdalDriverInitialization(void);
				bool _DsmInputFileRaster(void);
				
				//	Protected variables
				class DsmInformation							dsmMapInfo;
				AI_SUPPORT_ALGORITHMS_pixelsMovementType		aStarSearchPixelsMovementTypeForFindPath 	= AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT;
				bool 											aStartSearchPixelsCouldStayOnPlace			= false;
				list <class Location>							pathList;
				class Logger									logger;
				
			private: 
				//	Private variables
				bool    										initialized									= false;
				string											geoTiffFilename;
				string											modelName;
				GDALDataset  									*poDataset									= NULL;
				float 											*pafScanline								= NULL;
				class Location									currentLocation, destinationLocation;
				unordered_map <int, AI_SUPPORT_CLASSES_color>	elevationColor;
				class Graphic									graphic;
				
				//	Private member functions

		};  //  class Model

		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Target
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 06-03-2021
		// Description		: This class represents a target person
		// Remarks			: It is derived from Model class
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Target : public Model
		{
			public:
				//	Default Constructor 
				Target(); 
				//	Parametrized Constructors 
				Target(string geoTiffFilename, string modelName) : Model { geoTiffFilename, modelName } 
				{
					this->_Initialize(geoTiffFilename, modelName);
					this->_AStarAlgorithmConfiguration(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
				}
				//	Destructor
				~Target();

			protected:
				//	Protected member function
				//	Protected variables
			private:
				//	Private variables

		};	//	class Target
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Agent
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 06-03-2021
		// Description		: This class represents an agent person
		// Remarks			: It is derived from Target class 
		//						(the agent also could be a target of another agent)
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Agent : public Target
		{
			public:
				//	Public member functions
				void DsmMapForTargetReset(void);
				void DsmMapForTargetResetIncludingForbiddenLocations(
						Location targetLocation,
						//	Default parameter
						int minimumDistanceToTarget = AI_MODEL_MINIMUM_DISTANCE_FROM_AGENT_TO_TARGET,
						bool clearPreviousObstacles = true);
						
				void TargetLocation(Location targetLocation) {	this->currentTargetLocation	= currentTargetLocation;}
				Location& TargetLocation(void) {	return this->currentTargetLocation;}
				void FirstTargetLocation(Location targetLocation) {		this->firstTargetLocation	= currentTargetLocation;}
				Location& FirstTargetLocation(void) {	return this->firstTargetLocation;}
				double TargetLineIntercept(void) {	return this->firstTargetLocation.LineIntercept(this->currentTargetLocation);}
				double TargetLineSlope(void) {	return this->firstTargetLocation.LineSlope(this->currentTargetLocation);}
				double Distance(Location pointA, Location pointB) {	return pointA.Distance(pointB);}
				
				int FindPathToFollowTarget(
									string csvAgentPathFilename,
									Location targetLocation,
									//	Default parameter
									int minimumDistanceToTarget = AI_MODEL_MINIMUM_DISTANCE_FROM_AGENT_TO_TARGET);
				
				//	Default Constructor 
				Agent(); 
				//	Parametrized Constructors 
				Agent(string geoTiffFilename, string modelName) : Target {geoTiffFilename, modelName}
				{
					this->_AStarAlgorithmConfigurationForTarget(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
					this->targetDsmMapInfo	= this->dsmMapInfo;
				}
				//	Destructor
				~Agent();

			protected:
				//	Protected member function
				bool _AStarAlgorithmConfigurationForTarget(AI_SUPPORT_ALGORITHMS_pixelsMovementType aStarSearchPixelsMovementTypeForFindPath, bool possibilityOfNotMoving);
				bool _ListOfPossibleTargets(list <Location>& targetPossibleList, int maximumNumberOfPossibleTargets = 10);
				//	Protected variables
				AI_SUPPORT_ALGORITHMS_pixelsMovementType	aStarSearchPixelsMovementTypeForFindPathForTarget 	= AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT;
				bool 							aStartSearchPixelsCouldStayOnPlaceForTarget			= false;
				int								minimumDistanceToTarget								= AI_MODEL_MINIMUM_DISTANCE_FROM_AGENT_TO_TARGET;
				class TargetDsmInformation		targetDsmMapInfo;
				Location						firstTargetLocation, currentTargetLocation;
			private:
				//	Private variables

		};	//	class Agent
		


#endif	// __AI_MODEL_IFC_H__
