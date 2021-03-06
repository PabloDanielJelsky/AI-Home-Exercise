//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloAiHomeExercise.cpp
//
// Version:			01.01
//
// Description:		Pablo's AI home excercise source file
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
//	27-02-2021	Pablo Daniel Jelsky		01			00			Initial
//	05-03-2021	Pablo Daniel Jelsky		01			01			Modification of internal representation
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
//
//	============================================================
//	============================================================
//	Task (home exercise) objective:	double tracking on target //
//	============================================================
//	============================================================
//	-	The idea of this task is to create an algorithm that allows the continuous tracking after the person - "target" - by a couple of followers
//	-	Given a DSM (Digital Surface Model) building's map - 100 [m] x 100 [m] matrix ????
//	-	Given the "target" maximum speed as 1 meter/second in a not known in advance route. The "target movement is limited only to "ground" level
//	-	Given the "followers" speed as 2 meters/second, and are only allowed to be as close as 10 meters (no less than this) from the "target". 
//			The "followers" movement is also limited to "ground" level
//	-	The task objective is to create an algorithm that once in a second, gives us the "target" and "followers" position given the limitations above, 
//			and issues instructions to the "followers" next movement in order that at least one of the "followers" could have "eye-contact" as much as 
//			possible with the "target"
//	
//	====================
//	====================
//	Development steps // 
//	====================
//	====================
//	-	1)	Visual Simulation
//	-		-----------------
//	-	1.1)	Display the DSM file in Python / Matlab (in this case as .png file)
//	-	1.2)	"Target" player
//	-	1.2.1)		Create the "target" path given start and objective points
//	-	1.2.2)		Display "target" path progress over time on map
//	-	1.3)	"Agent" players
//	-	1.3.1)		Display "agents" path progress over time on map
//	-	1.4)	LOS (Line Of Sight)
//	-	1.4.1)		Display LOS between every agent ant the "target", if existent
//	-	2)	Solution help tools
//	-		-------------------

//
//	==========================================
//	==========================================
//	Web links related to this home exercise // 
//	==========================================
//	==========================================
//		-	[Digital Elevation Model (DEM)](https://en.wikipedia.org/wiki/Digital_elevation_model)
//		-	[Geospatial Data Abstraction Library (GDAL)](https://en.wikipedia.org/wiki/GDAL)
//		-	[GeoTIFF](https://en.wikipedia.org/wiki/GeoTIFF)
//
//	==============================================
//	==============================================
//	Clarifications from Yair email (2021-02-21) //
//	==============================================
//	==============================================
//		-	Work with the DSM with the size 'as is' 351x201 pixels 
//		-	One pixel equals to one meter
//		-	The target is supposed to have constant rate (1 meter/second) and could NOT stop
//		-	The follower agent could also stop or up to 2 meters/second (0 meters/second, 1 meter/second, 2 meters/second)
//		-	Starting points for the target and follower agents could be in every place but NOT in a "obstacle" level (NOT "ground" level)
//		-	The agents will have LOS with the "target" in the first simulation cycle
//
//	===========================================
//	===========================================
//	Important notes regarding implementation //
//	===========================================
//	===========================================
//		-	The software architecture is based on different support classes (basing ones on top of others by derivation or composition),
//				algorithm function (based on A* algorithm that selects a path from a starting cell to a destination cell), and in the low
//				level the use of classes / functions, especially to deal with graphics reading / writting
//
//			The hierarchy is as follows:
//											Agent			(AiModel module)
//											|
//											Target			(AiModel module)
//											|
//											Model			(AiModel module)
//											|
//	-----------------------------------------------------------------------------------------------------------------
//	|						|				|					|					|								|
//	Location				DsmInformation	Graphic				Logger				FindPath()						GDAL library
//	(current, destination)	(DSM map)		(for .png/gTiff)	(for log events)	(member function)				(to read GeoTIFF DSM input file)
//	(AiSupportClasses module)-----------------------------(AiSupportClasses module)	(AiSupportAlgorithms module)
//											|					|					(also writes a CSV file with the found path)
//			-----------------------------------------			Timer
//			|										|			(AiSupportClasses module)
//			|										|			(for system time and "stopper")
//			|										|
//			GDAL library							PNGWriter library
//			(to create GeoTIFF DSM output file)		(to create .png output file)
//																|
//										---------------------------------------------
//										|											|
//										libpng library								FreeType2 library
//										(to read/create .png files)					(to write text into the .png files)
//
//		-	The internal representation of the DSM map in the DsmInformation class is that the south-west (down-left) pixel is (0,0),
//				and all the pixels are positive, and therefore, pixel in the north-east (up-right) is (Columns-1, Rows-1), where 
//				Columns is the total number of columns of the DSM file, and Rows is the total number of rows of the DSM file
//		-	.PNGWriter library defines this pixel in south-west (down-left) as being (1,1), and therefore pixel in the north-east (up-right) 
//				is (Columns, Rows)
//		-	GDAL library defines the pixel in the north-west (up-left) as being (0,0), and therefore pixel in the south-east (down-right)
//				is (Columns-1, Rows-1)
//		-	The conversion should be non-felt by the "user"
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
		#include <cstdlib>
		/*---- library files -------------------------------------------------------*/
		#include "/usr/include/gdal/gdal.h"
		#include "/usr/include/gdal/gdal_priv.h"
		#include "/usr/include/gdal/gdal_utils.h"
		#include "/usr/include/gdal/cpl_conv.h"
		#include "/usr/include/gdal/cpl_string.h"
		#include "pngwriter.h"
		/*---- program files -------------------------------------------------------*/
		#include "AiModel_Ifc.h"
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
		#define	NUMBER_OF_AGENTS	2
		#define DSM_FILE        	"../Input/cage6.tif"
		#define OUT_FILE        	"output/cage6.png"
		#define TARGET_PATH_FILE	"output/cage6_with_TargetPath.png"
		#define AGENT1_PATH_FILE	"output/cage6_with_Agent1Path.png"
		#define AGENT2_PATH_FILE	"output/cage6_with_Agent2Path.png"
		
		/*---- data declarations ---------------------------------------------------*/
		typedef enum {PERSON_TYPE_TARGET, PERSON_TYPE_AGENT1, PERSON_TYPE_AGENT2} personType;
		//	Logger support object created to log all the relevant events of this simulation
		class Logger				LoggerObject("output/PabloAIHomeExercise.txt");
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

int main()
{
	Location targetStart(2,2);
	Location targetObjective(300,100);
	
	Location pointB(10,10);
	Location pointC(4,4);
	Location pointD(150,150);
	Location text(3,3);

	bool					targetArrived = false, agent1Arrived = false;
	long					targetPathLength, agent1PathLength, agent2PathLength;
	list <DsmLocation> 		targetPathList, agent1PathList, agent2PathList;

	class Agent				agent1(DSM_FILE, "Agent1");
	agent1.CurrentLocation(targetStart);
	agent1.DestinationLocation(targetObjective);
	agent1PathLength 	= agent1.FindPath("output/Agent1Path.csv");
	
	class Target			target(DSM_FILE, "Target");
	target.CurrentLocation(targetStart);
	target.DestinationLocation(targetObjective);
//	-	1.2.1)		Create the "target" path given start and objective points
	targetPathLength 	= target.FindPath("output/TargetPath.csv");
	
	
	class Agent				agent2(DSM_FILE, "Agent2");
	agent2.CurrentLocation(targetStart);
	agent2.DestinationLocation(targetObjective);
	agent2PathLength 	= agent2.FindPath("output/Agent2Path.csv");
   
	cout << "Target path length = " << targetPathLength << "\n";
	cout << "Agent 1 path length = " << agent1PathLength << "\n";
	cout << "Agent 2 path length = " << agent2PathLength << "\n";
	
//	-	1.1)	Display the DSM file in Python / Matlab (in this case as .png file)
	target.GraphicOpen("output/1_1_DsmOriginalFile", "DSM original input");
	target.GraphicPreparation(true);
	target.GraphicText(text, "Original cage6.tif");
	target.GraphicClose(GRAPHIC_TYPE_PNG);
	target.GraphicClose(GRAPHIC_TYPE_GEOTIFF);
	
	agent1.GraphicOpen("output/1_1_DsmOriginalFile - Agent", "DSM original input");
	agent1.GraphicPreparation(true);
	agent1.GraphicClose(GRAPHIC_TYPE_GEOTIFF);
	
	long int	simulationSeconds = 0;
  
	while (false == targetArrived || false == agent1Arrived)
    {
		Location	targetCurrentLocation	= target.CurrentLocation(), targetNextLocation;
		Location	agent1CurrentLocation	= agent1.CurrentLocation(), agent1NextLocation;
		string		target_base_filename	= "output/target/1_2_2_TargetOverTime_";
		string		target_base_text		= "Target path progress over time on map second = ";
		string		agent1_base_filename	= "output/agent/1_2_2_AgentOverTime_";
		string		agent1_base_text		= "Agent path progress over time on map second = ";
		string		filename, text;
		
		if (false == targetArrived)
			targetNextLocation				= target.NextLocation();
			
		if (false == agent1Arrived)
			agent1NextLocation				= agent1.NextLocation();
			
		simulationSeconds++;
		
		if (false == targetArrived)
		{
//	-	1.2.2)		Display "target" path progress over time on map
			filename						= target_base_filename;
			filename						+= std::to_string(simulationSeconds);
			text							= target_base_text;
			text							+= std::to_string(simulationSeconds);
					
			target.GraphicOpen(filename, text, true);
			target.GraphicLine(targetCurrentLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
			target.GraphicClose(GRAPHIC_TYPE_PNG);
		}
			
		if (false == agent1Arrived)
		{
			filename						= agent1_base_filename;
			filename						+= std::to_string(simulationSeconds);
			text							= agent1_base_text;
			text							+= std::to_string(simulationSeconds);
			
			agent1.GraphicOpen(filename, text, true);
			agent1.GraphicLine(targetCurrentLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
			agent1.GraphicLine(agent1CurrentLocation, agent1NextLocation, AI_SUPPORT_CLASSES_COLOR_TOMATO, true);
			agent1.GraphicClose(GRAPHIC_TYPE_PNG);
		}
		
		if (target.CurrentLocation() == target.DestinationLocation())
		{
			targetArrived	= true;
		}
		
		if (agent1.CurrentLocation() == agent1.DestinationLocation())
		{
			agent1Arrived	= true;
		}
		
		if (simulationSeconds > 600)
			break;
    }  
    
	return EXIT_SUCCESS;
	
}	//	main()


