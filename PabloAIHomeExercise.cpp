//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloAiHomeExercise.cpp
//
// Version:			01.02
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
//	07-03-2021	Pablo Daniel Jelsky		01			02			Addition of use of new SwissArmyKnife class that provides decisions on
//																	different situations for agent.
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
//
//	-	2)	Solution help tools
//	-		-------------------
//	-	2.1)	Map for every pixel at ground-level all the pixel that have LOS with it
//	-	2.2)	Take a number of DSM locations and display the LOS between them
//
//	-	3)	Working with "only" one agent
//	-		-----------------------------
//	-	3.1)	Write a function that will return the progress command to the agent given his and the "target" current locations: 
//					CalculateNextLocation(TargetCurrentLocation, AgentCurrentLocation)__
//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time
//
//	-	4)	Working with a couple of agents - Central calculation
//	-		-----------------------------------------------------
//	-	4.1)	Like in the previous section, but the function should give guidance to both agents: CalculateNextLocationForAgent2(TargetCurrentLocation, AgentCurrentLocation)__
//	-	4.2)	It is desirable that there will be some kind of coordination between both commands so that one agent will complement the other
//
//	-	5)	Working with a couple of agents - Distributed calculation
//	-		------------------------------------------------------------
//	-	5.1)	Write a function that will return the progress command to a_single agent given his, the second agent and the "target" current locations:
//					CalculateNextLocation3(TargetCurrentLocation, OtherAgentCurrentLocation, AgentCurrentLocation)__
//	-	5.2)	The function (for each agent) are not related between them
//	-	5.3)	The function will give guidance every 2 seconds, once the function will work with agent1, and the next second will work with agent2, 
//					therefore the function(s) won't work with the same input
//	-	5.4)	It is desirable that there will be some kind of coordination between both commands so that one agent will complement the other
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
		#include <iostream>
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
		#define DSM_FILE	"../Input/cage6.tif"
		
		/*---- data declarations ---------------------------------------------------*/
		//	Logger support object created to log all the relevant events of this simulation
		class Logger		LoggerObject("output/PabloAIHomeExercise.txt");
		/*---- function prototypes -------------------------------------------------*/
		
		static string _LosText(Location from, Location to);
		static bool _DrawLineOfSightBetweenTwoLocationsInDsmMap(class Model &model, Location from, Location to, int exampleNumber);
		static bool _CommandLineParameters(int argc, char *argv[], class Target &target, class Location &targetStart, class Location &targetObjective, class Location &agent1Start);
		static void _TargetAloneSimulation
		(
			class Location targetStart, 
			class Location targetObjective,
			class Location textLocation
		);
		static void _AgentAloneSimulation
		(
			class Location agentStart, 
			class Location agentObjective,
			class Location textLocation
		);
		static void _LonelyAgentSimulation
		(
			class Target& target, 
			class Location targetStart, 
			class Location targetObjective,
			class Location agentStart,
			class SwissArmyKnife targetAlgorithm,
			class Location textLocation,
			class Location noLosTextLocation,
			string modelName,
			bool usingLastLocationAlgorithmAsRankingFirst = false
		);
		static void _TwoAgentsSimulationCentralCalculation
		(
			class Target& target, 
			class Location targetStart, 
			class Location targetObjective, 
			class Location firstAgentStart,
			class Location secondAgentStart,
			class SwissArmyKnife targetAlgorithm,
			class Location textLocation,
			class Location noLosTextLocation,
			string modelName
		);

	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/

	/*
		************************************************************************************
		************************************************************************************
		************************************************************************************
		* MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM *
		* MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM *
		* MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM --- MAIN PROGRAM *
		************************************************************************************
		************************************************************************************
		************************************************************************************
	*/
	int main(int argc, char *argv[])
	{
		//	Delete all the previous runs PNG files
		system("rm -r output/target/*.*");
		system("rm -r output/agent/*.*");
		system("rm -r output/lonelyAgent/*.*");
		system("rm -r output/lonelyAgent_LastLocation/*.*");
		system("rm -r output/losExample/*.*");

		//	"Algorithms" tools for target
		class SwissArmyKnife	targetAlgorithm(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
		
		//	Text location for PNG files
		class Location			textLocation(20, 3);
		class Location			noLosTextLocation(100, 3);
		//	Initial and objective locations (by default)
		class Location			targetStart(5, 5);
		class Location			targetObjective(300,100);
		class Location			agent1Start(5,40);
		class Location			agent2Start(15,80);
		//	Target class and path length
		class Target			target(DSM_FILE, "Target");
		long					targetPathLength;
		
		//	Check if there are parameters from command line to modify initial and objective locations
		if (!_CommandLineParameters(argc, argv, target, targetStart, targetObjective, agent1Start))
			return EXIT_FAILURE;
		
		//	Set target (current and objective locations)
		target.CurrentLocation(targetStart);
		target.DestinationLocation(targetObjective);
		
//	-	1.2.1)		Create the "target" path given start and objective points - Begin
		targetPathLength		= target.FindPath("output/TargetPath.csv");
//	-	1.2.1)		Create the "target" path given start and objective points - End

//	-	Creating a .csv file with the obstacles information of the DSM map	- Begin
		targetAlgorithm.Obstacles2Csv(target.DsmMap(), "output/DsmMapObstacles.csv");
//	-	Creating a .csv file with the obstacles information of the DSM map	- End

		cout << "DSM input map file dimensions are " << target.DsmMapFileColumns() << " columns by " << target.DsmMapFileRows() << " rows\n";
		cout << "Target path length = " << targetPathLength << "\n";

//	-	1.1)	Display the DSM file in Python / Matlab (in this case as .png file) - Begin
		target.GraphicOpen("output/1_1_DsmOriginalFile", "DSM original input");
		target.GraphicPreparation(true);
		target.GraphicText(textLocation, "Original cage6.tif");
		target.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		target.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF);
//	-	1.1)	Display the DSM file in Python / Matlab (in this case as .png file) - End

//	-	2.2)	Take a number of DSM locations and display the LOS between them - Begin
		long unsigned int		losPointBeingTested;
		Location				losPointsToBeTested[] = {{10, 10}, {20, 10}, {30, 30}, {150, 150}, {300, 100}, {300, 300}, {10, 150}, {20, 180}, {30, 190}, {1, 1}, {20, 5}, {5, 20}, {5, 5}};
		for (losPointBeingTested = 0; losPointBeingTested < (sizeof(losPointsToBeTested)/sizeof(losPointsToBeTested[0])); losPointBeingTested++)
		_DrawLineOfSightBetweenTwoLocationsInDsmMap(target, targetStart, losPointsToBeTested[losPointBeingTested], losPointBeingTested+1);
//	-	2.2)	Take a number of DSM locations and display the LOS between them - End

//	-	1.2.2)		Display "target" path progress over time on map - Begin
		_TargetAloneSimulation(targetStart, targetObjective, textLocation);
//	-	1.2.2)		Display "target" path progress over time on map - End

//	-	Bonus)		Display "agent alone" path progress over time on map - Begin
		_AgentAloneSimulation(targetStart, targetObjective, textLocation);
//	-	Bonus)		Display "agent alone" path progress over time on map - End

//	-	3)	Working with "only" one agent - Begin
		_LonelyAgentSimulation(target, targetStart, targetObjective, agent1Start, targetAlgorithm, textLocation, noLosTextLocation, "lonelyAgent");
//		_LonelyAgentSimulation(target, targetStart, targetObjective, agent1Start, targetAlgorithm, textLocation, noLosTextLocation, "lonelyAgent_LastLocation", true);
//	-	3)	Working with "only" one agent - End
		_TwoAgentsSimulationCentralCalculation(target, targetStart, targetObjective, agent1Start, agent2Start, targetAlgorithm, textLocation, noLosTextLocation, "twoAgentsWithCentralCalculation");
		
		//	Create animated GIFs for R
		system("gifski -o output/target/target.gif output/target/*.png");
		system("gifski -o output/agent/agent.gif output/agent/*.png");
		system("gifski -o output/lonelyAgent/lonelyAgent.gif output/lonelyAgent/*.png");
		system("gifski -o output/lonelyAgent_LastLocation/lonelyAgent_LastLocation.gif output/lonelyAgent_LastLocation/*.png");
		system("gifski -o output/losExample/losExample.gif --fps 1 output/losExample/*.png");
		
		return EXIT_SUCCESS;
		
	}	//	main()
	
	/*
		****************************************************************************
		* PRIVATE FUNCTION DEFINITIONS
		****************************************************************************
	*/
	static string _LosText(Location from, Location to)
	{
		string	losText;
		
		losText	= "[" + std::to_string(from.Column()) + ", " + std::to_string(from.Row()) + "] => " + "[" + std::to_string(to.Column()) + ", " + std::to_string(to.Row()) + "]";
		return losText;
		
	}	//	_LosText()
	
	static bool _DrawLineOfSightBetweenTwoLocationsInDsmMap(class Model &model, Location from, Location to, int exampleNumber)
	{
		Location 	lostextLocation(30,3);
		bool		locationsHaveLos;
		char 		cString[10];
		sprintf(cString, "%04d", exampleNumber);
		std::string	cppString(cString);
		
		model.GraphicOpen("output/losExample/LOS example " + cppString, _LosText(from, to), true);
		
		model.GraphicCross(from, AI_SUPPORT_CLASSES_COLOR_TOMATO, false);
		model.GraphicCross(to, AI_SUPPORT_CLASSES_COLOR_WHITE, false);
		
		locationsHaveLos	= model.LineOfSight(from, to);
		if (locationsHaveLos)
		{
			model.GraphicText(lostextLocation, _LosText(from, to), AI_SUPPORT_CLASSES_COLOR_WHITE, 10);
			model.GraphicArrow(from, to, AI_SUPPORT_CLASSES_COLOR_WHITE, false);
		}
		else
		{
			model.GraphicText(lostextLocation, "There is not LOS between " + _LosText(from, to), AI_SUPPORT_CLASSES_COLOR_WHITE, 10);
		}
		model.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		
		return locationsHaveLos;
		
	}	//	_DrawLineOfSightBetweenTwoLocationsInDsmMap()
	
	static bool _CommandLineParameters(int argc, char *argv[], class Target &target, class Location &targetStart, class Location &targetObjective, class Location &agent1Start)
	{
		switch (argc)
		{
			case 1:
			//	Default case: takes "hard-coded" arguments from inside the SW
				break;
			case 2:
			default:
		   // Tell the user how to run t//	Update the .csv DSM map for lonely agent and target file with the current informationhe program
				std::cerr << "usage: " << argv[0] << " <target_start_column> <target_start_row> {target objective column} {target objective row} [agent start column] [agent start row]" << std::endl;
				/* "Usage messages" are a conventional way of telling the user
				* how to run a program if they enter the command incorrectly.
				*/
				return false;
			case 3:
				{
					int commandLineTargetStartColumn		= atoi(argv[1]);
					int commandLineTargetStartRow			= atoi(argv[2]);
					Location commandLineTargetStartLocation(commandLineTargetStartColumn, commandLineTargetStartRow);

					if (!target.CurrentLocation(commandLineTargetStartLocation))
					{
						std::cerr << "error while selecting new target start location" << std::endl;
						return false;
					}
					targetStart	= commandLineTargetStartLocation;
					std::cout << "new target start location selected" << std::endl;
					break;
				}
			case 5:
				{
					int commandLineTargetStartColumn		= atoi(argv[1]);
					int commandLineTargetStartRow			= atoi(argv[2]);
					int commandLineTargetObjectiveColumn	= atoi(argv[3]);
					int commandLineTargetObjectiveRow		= atoi(argv[4]);
					Location commandLineTargetStartLocation(commandLineTargetStartColumn, commandLineTargetStartRow);
					Location commandLineTargetObjectiveLocation(commandLineTargetObjectiveColumn, commandLineTargetObjectiveRow);

					if (!target.CurrentLocation(commandLineTargetStartLocation))
					{
						std::cerr << "error while selecting new target start location" << std::endl;
						return false;
					}
					targetStart	= commandLineTargetStartLocation;
					std::cout << "new target start location selected" << std::endl;
					
					if (!target.CurrentLocation(commandLineTargetObjectiveLocation))
					{
						std::cerr << "error while selecting new target objective location" << std::endl;
						return false;
					}
					targetObjective	= commandLineTargetObjectiveLocation;
					std::cout << "new target objective location selected" << std::endl;
					break;
				}
			case 7:
				{
					int commandLineTargetStartColumn		= atoi(argv[1]);
					int commandLineTargetStartRow			= atoi(argv[2]);
					int commandLineTargetObjectiveColumn	= atoi(argv[3]);
					int commandLineTargetObjectiveRow		= atoi(argv[4]);
					int commandLineAgent1StartColumn		= atoi(argv[5]);
					int commandLineAgent1StartRow			= atoi(argv[6]);
					Location commandLineTargetStartLocation(commandLineTargetStartColumn, commandLineTargetStartRow);
					Location commandLineTargetObjectiveLocation(commandLineTargetObjectiveColumn, commandLineTargetObjectiveRow);
					Location commandLineAgent1StartLocation(commandLineAgent1StartColumn, commandLineAgent1StartRow);

					if (!target.CurrentLocation(commandLineTargetStartLocation))
					{
						std::cerr << "error while selecting new target start location" << std::endl;
						return false;
					}
					targetStart	= commandLineTargetStartLocation;
					std::cout << "new target start location selected" << std::endl;
					
					if (!target.CurrentLocation(commandLineTargetObjectiveLocation))
					{
						std::cerr << "error while selecting new target objective location" << std::endl;
						return false;
					}
					targetObjective	= commandLineTargetObjectiveLocation;
					std::cout << "new target objective location selected" << std::endl;
					
					if ((!target.DsmMap().IsInDsmMap(commandLineAgent1StartLocation)) || (target.DsmMap().Obstacle(commandLineAgent1StartLocation)))
					{
						std::cerr << "error while selecting new agent start location" << std::endl;
						return false;
					}
					agent1Start	= commandLineAgent1StartLocation;
					std::cout << "new agent start location selected" << std::endl;
					
					if (!target.LineOfSight(commandLineTargetStartLocation, commandLineAgent1StartLocation))
					{
						std::cerr << "error because there is no LOS between agent and target" << std::endl;
						return false;
					}
					break;
				}
		}		
		return true;
		
	}	//	_CommandLineParameters()
	
	static void _TargetAloneSimulation
	(
		class Location targetStart, 
		class Location targetObjective,
		class Location textLocation
	)
	{
		bool					targetArrived		= false;
		int						simulationSeconds	= 0;
		
		class Target			targetAlone(DSM_FILE, "target");
		
		//	Set target (current and objective locations)
		targetAlone.CurrentLocation(targetStart);
		targetAlone.DestinationLocation(targetObjective);
		
		targetAlone.FindPath("output/TargetAlonePath.csv");

		targetAlone.GraphicOpen("output/1_2 2_DsmOriginalFile Target", "DSM original input");
		targetAlone.GraphicPreparation(true);
		targetAlone.GraphicText(textLocation, "Original cage6.tif");
		targetAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		targetAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF);
		//	Draws a cross at the target objective
		targetAlone.GraphicCross(targetObjective, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
		
		//	Create the .csv DSM map for target file
		std::ofstream csvTargetFile;
		csvTargetFile.open ("output/Target.csv");
		//	Create the header
		csvTargetFile << "Column, Row, Elevation\n";

		while (!targetArrived)
		{
			Location	targetCurrentLocation	= targetAlone.CurrentLocation(), targetNextLocation;
			
			string		target_base_filename	= "output/target/1_2_2_TargetOverTime_";
			string		target_base_text		= "Target path progress over time on map second = ";
			string		steps_base_text			= "Step = ";
			string		filename, text, steps_text;

			cout << "Target: " << targetCurrentLocation << endl;

			targetNextLocation					= targetAlone.NextLocation();

			simulationSeconds++;

			steps_text							= steps_base_text;
			steps_text							+= std::to_string(simulationSeconds);
			
			//	Update the .csv DSM map for target file with the current information
			csvTargetFile << targetNextLocation.Column() << "," << targetNextLocation.Row() << "," << "," << targetAlone.DsmMap().Elevation(targetNextLocation) << endl;

			char cString[10];
			sprintf(cString, "%04d", simulationSeconds);
			std::string	cppString(cString);

//	-	1.2.2)		Display "target" path progress over time on map - Begin
			filename							= target_base_filename;
			filename							+= cppString;
			text								= target_base_text;
			text								+= std::to_string(simulationSeconds);

			targetAlone.GraphicOpen(filename, text, true);
			targetAlone.GraphicText(textLocation, steps_text);
			targetAlone.GraphicLine(targetCurrentLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
			//	Draws a cross at the target
			targetAlone.GraphicCross(textLocation, AI_SUPPORT_CLASSES_COLOR_PURPLE, false);

			targetAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);

//	-	1.2.2)		Display "target" path progress over time on map - End

			if (targetAlone.CurrentLocation() == targetAlone.DestinationLocation())
			{
				targetArrived	= true;
			}

			//	In case of some error
			if (simulationSeconds > 1000)
				break;
		}  

		//	Close the .csv DSM map for target file
		csvTargetFile.close();

	}	//	_TargetAloneSimulation()
	
	static void _AgentAloneSimulation
	(
		class Location agentStart, 
		class Location agentObjective,
		class Location textLocation
	)
	{
		bool					agentArrived		= false;
		int						simulationSeconds	= 0;
		
		class Agent				agentAlone(DSM_FILE, "agent");
		
		//	Set agent (current and objective locations)
		agentAlone.CurrentLocation(agentStart);
		agentAlone.DestinationLocation(agentObjective);
		
		agentAlone.FindPath("output/AgentAlonePath.csv");

		agentAlone.GraphicOpen("output/DsmOriginalFile Agent", "DSM original input");
		agentAlone.GraphicPreparation(true);
		agentAlone.GraphicText(textLocation, "Original cage6.tif");
		agentAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		agentAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF);
		//	Draws a cross at the agent objective
		agentAlone.GraphicCross(agentObjective, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
		
		//	Create the .csv DSM map for agent file
		std::ofstream csvAgentFile;
		csvAgentFile.open ("output/Agent.csv");
		//	Create the header
		csvAgentFile << "Column, Row, Elevation\n";

		while (!agentArrived)
		{
			Location	agentCurrentLocation	= agentAlone.CurrentLocation(), agentNextLocation;
			
			string		agent_base_filename		= "output/agent/AgentOverTime_";
			string		agent_base_text			= "Agent path progress over time on map second = ";
			string		steps_base_text			= "Step = ";
			string		filename, text, steps_text;
			
			cout << "Agent: " << agentCurrentLocation << endl;
	
			agentNextLocation					= agentAlone.NextLocation();

			simulationSeconds++;
			
			steps_text							= steps_base_text;
			steps_text							+= std::to_string(simulationSeconds);
			
			//	Update the .csv DSM map for agent file with the current information
			csvAgentFile << agentNextLocation.Column() << "," << agentNextLocation.Row() << "," << "," << agentAlone.DsmMap().Elevation(agentNextLocation) << endl;

			char cString[10];
			sprintf(cString, "%04d", simulationSeconds);
			std::string	cppString(cString);

			filename								= agent_base_filename;
			filename								+= cppString;
			text									= agent_base_text;
			text									+= std::to_string(simulationSeconds);

			agentAlone.GraphicOpen(filename, text, true);
			agentAlone.GraphicText(textLocation, steps_text);
			agentAlone.GraphicLine(agentCurrentLocation, agentNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
			
			//	Draws a cross at the agent
			agentAlone.GraphicCross(textLocation, AI_SUPPORT_CLASSES_COLOR_PURPLE, false);

			agentAlone.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);


			if (agentAlone.CurrentLocation() == agentAlone.DestinationLocation())
			{
				agentArrived	= true;
			}

			//	In case of some error
			if (simulationSeconds > 1000)
				break;
		}  
		
		//	Close the .csv DSM map for agent file
		csvAgentFile.close();
		
	}	//	_AgentAloneSimulation()
	
	static void _LonelyAgentSimulation
	(
		class Target& target, 
		class Location targetStart, 
		class Location targetObjective, 
		class Location agentStart,
		class SwissArmyKnife targetAlgorithm,
		class Location textLocation,
		class Location noLosTextLocation,
		string modelName,
		bool usingLastLocationAlgorithmAsRankingFirst
	)
	{
		bool					targetArrived		= false;
		int						simulationSeconds	= 0;
		bool					targetLossMode		= false;
		Location				lastSeenTargetLocation;
		int						quantityOfLosLoss	= 0;
		
		class SwissArmyKnife	agentAlgorithm(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, true);
		
		list <class Location>	targetPotentialMovements;
		list <class Location>	agentPotentialMovements;

		//	Set target (current and objective locations)
		target.CurrentLocation(targetStart);
		target.DestinationLocation(targetObjective);
		target.FindPath("output/" + modelName + "_TargetPath.csv");
		
		class Agent				lonelyAgent(DSM_FILE, modelName);
		//	Set agent current location
		//	Set target (current and objective locations)
		lonelyAgent.CurrentLocation(agentStart);

		lonelyAgent.GraphicOpen("output" + modelName, "DSM original input");
		lonelyAgent.GraphicPreparation(true);
		lonelyAgent.GraphicText(textLocation, "Original cage6.tif");
		lonelyAgent.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		lonelyAgent.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF);
		//	Draws a cross at the target objective
		lonelyAgent.GraphicCross(targetObjective, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
		
		//	Create the .csv DSM map for lonely agent and target file
		std::ofstream csvLonelyAgentFile;
		csvLonelyAgentFile.open ("output/" + modelName + ".csv");
		//	Create the header
		csvLonelyAgentFile << "Target Column, Target Row, Agent Column, Agent Row, Distance, LOS\n";

		while (!targetArrived)
		{
			Location								targetCurrentLocation			= target.CurrentLocation(), targetNextLocation;
			Location								lonelyAgentCurrentLocation		= lonelyAgent.CurrentLocation(), lonelyAgentNextLocation;

			AI_SUPPORT_ALGORITHMS_losInfo			losInfo;
			int										quantityOfLosPotentialLocationsForObserver;
			list <AI_SUPPORT_ALGORITHMS_losInfo>	lonelyAgentLosInfoList;
			
			double									distanceBetweenTargetAndAgent;
			bool 									losBetweenAgentAndTarget;

			string		agent_and_target_base_filename	= "output/lonelyAgent/3_2_LonelyAgentFollowsTargetOverTime_";
			string		agent_and_target_base_text		= "Lonely agent and target path progress over time on map second = ";
			string		steps_base_text					= "Step = ";
			string		filename, text, steps_text;
			
			if (usingLastLocationAlgorithmAsRankingFirst)
				agent_and_target_base_filename	= "output/lonelyAgent_LastLocation/3_2_LonelyAgentFollowsTargetOverTime_";
			
			cout << "Agent: " << lonelyAgentCurrentLocation << ", target: " << targetCurrentLocation << endl;
			
//	-	3.1)	Write a function that will return the progress command to the agent given his and the "target" current locations: 
//					CalculateNextLocation(TargetCurrentLocation, AgentCurrentLocation)
//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- Begin

			//	Agent algorithm
			if (targetLossMode)
			{
				//	Add one case to the total number of LOS loss cases
				quantityOfLosLoss++;
				
				//	Do NOT let the agent stay in place
				agentAlgorithm.MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, false);
				
				//	Calculate target potential movement according to last SEEN position
				targetAlgorithm.PossibleMovements(targetPotentialMovements, lastSeenTargetLocation, target.DsmMap());
			}
			else
			{
				//	Calculate target potential movement according to last position
				targetAlgorithm.PossibleMovements(targetPotentialMovements, targetCurrentLocation, target.DsmMap());
			}
			
			//	Calculate agent potential movements
			agentAlgorithm.PossibleMovements(agentPotentialMovements, lonelyAgentCurrentLocation, target.DsmMap());
			
			//	Filter only the potential movements that still mantain LOS between agent and target
			if (targetLossMode)
			{
				quantityOfLosPotentialLocationsForObserver	= agentAlgorithm.PossibleLineOfSightLocations
				(
					agentPotentialMovements, 
					targetPotentialMovements, 
					target.DsmMap(), 
					lonelyAgentLosInfoList,
					10,
					lastSeenTargetLocation
				);
			}
			else
			{
				quantityOfLosPotentialLocationsForObserver	= agentAlgorithm.PossibleLineOfSightLocations
				(
					agentPotentialMovements, 
					targetPotentialMovements, 
					target.DsmMap(), 
					lonelyAgentLosInfoList,
					10
				);
			}
			
			//	Order the list
			agentAlgorithm.Ranking(lonelyAgentLosInfoList);

		
			//	Set the ranking according to distance from agent to target and if there is LOS or not between them
			//	Improve, but works
			if (targetCurrentLocation.Distance(lonelyAgentCurrentLocation) > 20)
			{
				//	Give preference to potential movements that will reduce the distance between agent and target
				if (targetLossMode)
					agentAlgorithm.RankingOrder(lonelyAgentLosInfoList, 0, 10, 0, 0, 10);
				else
					agentAlgorithm.RankingOrder(lonelyAgentLosInfoList, 0, 10, 0, 0);
			}
			else
			{
				//	Give preference to potential movements that will increase the distance between agent and closest obstacle
				if (targetLossMode)
					agentAlgorithm.RankingOrder(lonelyAgentLosInfoList, 0, 1, 0, 10, 10);
				else
					agentAlgorithm.RankingOrder(lonelyAgentLosInfoList, 0, 1, 0, 10);
			}

if (1)
{
			cout << "Potential observer locations with LOS to observed = " << quantityOfLosPotentialLocationsForObserver << endl;
			std::list<AI_SUPPORT_ALGORITHMS_losInfo>::iterator it = lonelyAgentLosInfoList.begin();
			while (it != lonelyAgentLosInfoList.end()) 
			{
				cout << "[" << (*it).location.Column() << ", " << (*it).location.Row() << "]\n";
				cout << "Minimum/Maximum [" << (*it).minimumLosDistance << ", " << (*it).maximumLosDistance << "]\n";
				cout << "Obstacle distance = " << (*it).closestObstacleDistance << endl;
				cout << "Specific location distance = " << (*it).minimumDistanceToSpecificLocation << endl;
				cout << "Quantity LOS = " << (*it).losToPotentialLocations << endl;
				cout << "Ranking = " << (*it).importance << endl;
				it++;
			}
}

			//	Take the best possible movement according to criteria
			losInfo	= lonelyAgentLosInfoList.front();
			
//	-	3.1)	Write a function that will return the progress command to the agent given his and the "target" current locations: 
//					CalculateNextLocation(TargetCurrentLocation, AgentCurrentLocation)
//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- End

			targetNextLocation						= target.NextLocation();
			
			if (0 != quantityOfLosPotentialLocationsForObserver)
			{
				lonelyAgentNextLocation				= losInfo.location;
				lonelyAgent.CurrentLocation(lonelyAgentNextLocation);
			}

			simulationSeconds++;

			steps_text								= steps_base_text;
			steps_text								+= std::to_string(simulationSeconds);
		
			//	Update the .csv DSM map for lonely agent and target file with the current information
			distanceBetweenTargetAndAgent			= lonelyAgentNextLocation.Distance(targetNextLocation);
			losBetweenAgentAndTarget				= target.DsmMap().LineOfSight(lonelyAgentNextLocation, targetNextLocation);
			csvLonelyAgentFile << targetNextLocation.Column() << "," << targetNextLocation.Row() << "," << lonelyAgentNextLocation.Column() << "," << lonelyAgentNextLocation.Row() << "," << distanceBetweenTargetAndAgent << "," << losBetweenAgentAndTarget << endl;
			
			if (targetLossMode && losBetweenAgentAndTarget)
			{
				//	Bring back original configuration for agent
				agentAlgorithm.MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, true);
				targetLossMode				= false;
			}

			if (!losBetweenAgentAndTarget)
			{
				cout << "LOS between agent and target LOST\n";
				if (!targetLossMode)
				{
					lastSeenTargetLocation	= targetCurrentLocation;
					targetLossMode			= true;
				}
			}

			char cString[10];
			sprintf(cString, "%04d", simulationSeconds);
			std::string	cppString(cString);
				
//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- Begin
			filename								= agent_and_target_base_filename;
			filename								+= cppString; // std::to_string(cString);//std::to_string(simulationSeconds);
			text									= agent_and_target_base_text;
			text									+= std::to_string(simulationSeconds);

			lonelyAgent.GraphicOpen(filename, text, true);
			lonelyAgent.GraphicText(textLocation, steps_text);
			lonelyAgent.GraphicLine(targetCurrentLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);
			//	Draws a cross at the agent
			lonelyAgent.GraphicCross(lonelyAgentNextLocation, AI_SUPPORT_CLASSES_COLOR_PURPLE, false);
			
			if (losBetweenAgentAndTarget)
			{
				//	Draws a gray line for LOS between agent and target
				lonelyAgent.GraphicLine(lonelyAgentNextLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_GRAY, false);
			}
			else
			{
				//	Shows a text "LOS lost"
				lonelyAgent.GraphicText(noLosTextLocation, "LOS lost");
			}
			lonelyAgent.GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
				
//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- End

			if (target.CurrentLocation() == target.DestinationLocation())
			{
				targetArrived	= true;
			}
			

			//	In case of some error
			if (simulationSeconds > 1000)
				break;
		}  


		//	Print the number of total LOS loss cases
		cout << "There were " << quantityOfLosLoss << " loss of LOS cases" << endl;

		//	Close the .csv DSM map for lonely agent and target file
		csvLonelyAgentFile.close();

	}	// _LonelyAgentSimulation()


	static void _TwoAgentsSimulationCentralCalculation
	(
		class Target& target, 
		class Location targetStart, 
		class Location targetObjective, 
		class Location firstAgentStart,
		class Location secondAgentStart,
		class SwissArmyKnife targetAlgorithm,
		class Location textLocation,
		class Location noLosTextLocation,
		string modelName
	)
	{
		#define	QUANTITY_OF_AGENTS	2
		int						agentCounter;

		bool					targetArrived							= false;
		int						simulationSeconds						= 0;
		bool					targetLossMode[QUANTITY_OF_AGENTS];
		Location				lastSeenTargetLocation;
		int						quantityOfLosLoss[QUANTITY_OF_AGENTS+1];

		class SwissArmyKnife	*agentAlgorithm;
		class Agent				*agent;
		agentAlgorithm			= new class SwissArmyKnife[QUANTITY_OF_AGENTS];
		agent					= new class Agent[QUANTITY_OF_AGENTS];

		list <class Location>	targetPotentialMovements;
		list <class Location>	agentPotentialMovements[QUANTITY_OF_AGENTS];
		
		bool					masterAgent	= -1, slaveAgent = -1;

		for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
		{
			targetLossMode[agentCounter]								= false;
			quantityOfLosLoss[agentCounter]								= 0;
			agentAlgorithm[agentCounter].MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, true);
			agent[agentCounter].Initialize(DSM_FILE, modelName + std::to_string(agentCounter));
		}
		quantityOfLosLoss[QUANTITY_OF_AGENTS]							= 0;

		//	Set target (current and objective locations)
		target.CurrentLocation(targetStart);
		target.DestinationLocation(targetObjective);
		target.FindPath("output/" + modelName + "_TargetPath.csv");

		//	Set both agents current location
		agent[0].CurrentLocation(firstAgentStart);
		agent[1].CurrentLocation(secondAgentStart);

		agent[0].GraphicOpen("output" + modelName, "DSM original input");
		agent[0].GraphicPreparation(true);
		agent[0].GraphicText(textLocation, "Original cage6.tif");
		agent[0].GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
		agent[0].GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_GEOTIFF);
		
		//	Draws a cross at the target objective
		agent[0].GraphicCross(targetObjective, AI_SUPPORT_CLASSES_COLOR_WHITE, true);

		//	Create the .csv DSM map for lonely agent and target file
		std::ofstream csvTwoAgentsSimulationCentralCalculationFile;
		csvTwoAgentsSimulationCentralCalculationFile.open ("output/" + modelName + ".csv");
		//	Create the header
		csvTwoAgentsSimulationCentralCalculationFile << "Target column, Target row, Agent0 column, Agent0 row, Agent0 to target distance, Agent0 LOS, Agent1 column, Agent1 row, Agent1 to target distance, Agent1 LOS\n";

		while (!targetArrived)
		{
			Location								targetCurrentLocation		= target.CurrentLocation(), targetNextLocation;
			Location								*agentCurrentLocation;
			Location								*agentNextLocation;
			Location								slaveAgentSpecificLocation;

			agentCurrentLocation												= new class Location[QUANTITY_OF_AGENTS];
			agentNextLocation													= new class Location[QUANTITY_OF_AGENTS];
			AI_SUPPORT_ALGORITHMS_losInfo			losInfo[QUANTITY_OF_AGENTS];
			int										quantityOfLosPotentialLocationsForObserver[QUANTITY_OF_AGENTS];
			list <AI_SUPPORT_ALGORITHMS_losInfo>	agentLosInfoList[QUANTITY_OF_AGENTS];

			double									distanceBetweenTargetAndAgent[QUANTITY_OF_AGENTS];
			bool 									losBetweenAgentAndTarget[QUANTITY_OF_AGENTS];

			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				agentCurrentLocation[agentCounter]								= agent[agentCounter].CurrentLocation();
			}

			string		agent_and_target_base_filename	= "output/twoAgentsCentralized/4_1_TwoAgentsCentralizedFollowTargetOverTime_";
			string		agent_and_target_base_text		= "Two agents (centralized) and target path progress over time on map second = ";
			string		steps_base_text					= "Step = ";
			string		filename, text, steps_text;

			cout << "Agent0: " << agentCurrentLocation[0] << ", agent1: " << agentCurrentLocation[1] << ", target: " << targetCurrentLocation << endl;

//	-	4.1)	Like in the previous section, but the function should give guidance to both agents: CalculateNextLocationForAgent2(TargetCurrentLocation, AgentCurrentLocation)__
//	-	4.2)	It is desirable that there will be some kind of coordination between both commands so that one agent will complement the other	- Begin

			//	Agent algorithm
			if (targetLossMode[0] || targetLossMode[1])
			{
				//	Add one case to the total number of LOS loss cases (of both agents at the same time)
				quantityOfLosLoss[QUANTITY_OF_AGENTS]++;

				for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
				{
					//	Do NOT let the agent stay in place
					agentAlgorithm[agentCounter].MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, false);
				}
				//	Calculate target potential movement according to last SEEN position
				targetAlgorithm.PossibleMovements(targetPotentialMovements, lastSeenTargetLocation, target.DsmMap());
			}
			else
			{
				if (targetLossMode[0])
				{
					//	Add one case to the total number of LOS loss cases
					quantityOfLosLoss[0]++;
				
					//	Do NOT let the agent stay in place
					agentAlgorithm[0].MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, false);
				} else if (targetLossMode[1])
				{
					//	Add one case to the total number of LOS loss cases
					quantityOfLosLoss[1]++;
				
					//	Do NOT let the agent stay in place
					agentAlgorithm[1].MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, false);
				}
				
				//	Calculate target potential movement according to last position (at least the other agent knows the target position)
				targetAlgorithm.PossibleMovements(targetPotentialMovements, targetCurrentLocation, target.DsmMap());
			}

			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				//	Calculate agents' potential movements
				agentAlgorithm[agentCounter].PossibleMovements(agentPotentialMovements[agentCounter], agentCurrentLocation[agentCounter], target.DsmMap());
				
				//	Filter only the potential movements that still mantain LOS between agent and target
				if (targetLossMode[0] && targetLossMode[1])
				{
					quantityOfLosPotentialLocationsForObserver[agentCounter]	= agentAlgorithm[agentCounter].PossibleLineOfSightLocations
					(
						agentPotentialMovements[agentCounter], 
						targetPotentialMovements, 
						target.DsmMap(), 
						agentLosInfoList[agentCounter],
						10,
						lastSeenTargetLocation
					);
					//	None of the agents is master, because both of them have lost LOS with target
					masterAgent	= -1;
					slaveAgent	= -1;
				}
				else
				{
					quantityOfLosPotentialLocationsForObserver[agentCounter]	= agentAlgorithm[agentCounter].PossibleLineOfSightLocations
					(
						agentPotentialMovements[agentCounter], 
						targetPotentialMovements, 
						target.DsmMap(), 
						agentLosInfoList[agentCounter],
						10
					);
				}
			}
			
			if (!(targetLossMode[0] && targetLossMode[1]))
			{
				//	If at least one of the agents has not lost LOS with target
				masterAgent	= (quantityOfLosPotentialLocationsForObserver[0] > quantityOfLosPotentialLocationsForObserver[1]) ? 0 : 1;
				slaveAgent	= (masterAgent == 0) ? 1 : 0;
				
				//	Choose the opposite location to anothe agent (being the central point the target)
				slaveAgentSpecificLocation	= agentCurrentLocation[masterAgent].Opposite(targetCurrentLocation);
				//	Filter only the potential movements that still mantain LOS between agent and target but insert distance to slave agent specific location
				quantityOfLosPotentialLocationsForObserver[slaveAgent]	= agentAlgorithm[slaveAgent].PossibleLineOfSightLocations
				(
					agentPotentialMovements[slaveAgent], 
					targetPotentialMovements, 
					target.DsmMap(), 
					agentLosInfoList[slaveAgent],
					10,
					slaveAgentSpecificLocation
				);
			}

			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				if (targetLossMode[0] && targetLossMode[1])
				{
					//	If both agents have lost LOS with target
					if (targetCurrentLocation.Distance(agentCurrentLocation[agentCounter]) > 20)
					{
						//	Give preference to potential movements that will reduce the distance between agent and target
						agentAlgorithm[agentCounter].RankingOrder(agentLosInfoList[agentCounter], 0, 10, 0, 0, 10);
					}
					else
					{
						//	Give preference to potential movements that will increase the distance between agent and closest obstacle
						agentAlgorithm[agentCounter].RankingOrder(agentLosInfoList[agentCounter], 0, 1, 0, 10, 10);
					}
				}
				else
				{
					if (agentCounter == masterAgent)
					{
						//	If this agent is the master
						if (targetCurrentLocation.Distance(agentCurrentLocation[agentCounter]) > 20)
						{
							//	Give preference to potential movements that will reduce the distance between agent and target
							agentAlgorithm[agentCounter].RankingOrder(agentLosInfoList[agentCounter], 0, 10, 0, 0);
						}
						else
						{
							//	Give preference to potential movements that will increase the distance between agent and closest obstacle
							agentAlgorithm[agentCounter].RankingOrder(agentLosInfoList[agentCounter], 0, 1, 0, 10);
						}
					}
					else
					{
						//	If this agent is the slave (should be opposite to master agent)
						//	Give preference to potential movements that will reduce the distance between the slave agent and the opposite location to master agent
						agentAlgorithm[agentCounter].RankingOrder(agentLosInfoList[agentCounter], 0, 0, 0, 0, 10);
					}
				}
			}

if (0)
{
//			cout << "Potential observer locations with LOS to observed = " << quantityOfLosPotentialLocationsForObserver << endl;
//			std::list<AI_SUPPORT_ALGORITHMS_losInfo>::iterator it = lonelyAgentLosInfoList.begin();
//			while (it != lonelyAgentLosInfoList.end()) 
//			{
//				cout << "[" << (*it).location.Column() << ", " << (*it).location.Row() << "]\n";
//				cout << "Minimum/Maximum [" << (*it).minimumLosDistance << ", " << (*it).maximumLosDistance << "]\n";
//				cout << "Obstacle distance = " << (*it).closestObstacleDistance << endl;
//				cout << "Specific location distance = " << (*it).minimumDistanceToSpecificLocation << endl;
//				cout << "Quantity LOS = " << (*it).losToPotentialLocations << endl;
//				cout << "Ranking = " << (*it).importance << endl;
//				it++;
//			}
}
			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				//	Take the best possible movement according to criteria
				losInfo[agentCounter]	= agentLosInfoList[agentCounter].front();
			}

//	-	4.1)	Like in the previous section, but the function should give guidance to both agents: CalculateNextLocationForAgent2(TargetCurrentLocation, AgentCurrentLocation)__
//	-	4.2)	It is desirable that there will be some kind of coordination between both commands so that one agent will complement the other	- End

			targetNextLocation						= target.NextLocation();
			
			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				if (0 != quantityOfLosPotentialLocationsForObserver[agentCounter])
				{
					agentNextLocation[agentCounter]				= losInfo[agentCounter].location;
					agent[agentCounter].CurrentLocation(agentNextLocation[agentCounter]);
				}
			}

			simulationSeconds++;

			steps_text									= steps_base_text;
			steps_text									+= std::to_string(simulationSeconds);

			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				distanceBetweenTargetAndAgent[agentCounter]	= agentNextLocation[agentCounter].Distance(targetNextLocation);
				losBetweenAgentAndTarget[agentCounter]		= target.DsmMap().LineOfSight(agentNextLocation[agentCounter], targetNextLocation);
			}

			//	Update the .csv DSM map for lonely agent and target file with the current information
			csvTwoAgentsSimulationCentralCalculationFile << targetNextLocation.Column() << "," << targetNextLocation.Row() << "," <<
															agentNextLocation[0].Column() << "," << agentNextLocation[0].Row() << "," << 
															distanceBetweenTargetAndAgent[0] << "," << losBetweenAgentAndTarget[0] << 
															agentNextLocation[1].Column() << "," << agentNextLocation[1].Row() << "," << 
															distanceBetweenTargetAndAgent[1] << "," << losBetweenAgentAndTarget[1] << endl;
															
			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				if (targetLossMode[agentCounter] && losBetweenAgentAndTarget[agentCounter])
				{
					//	Bring back original configuration for agent
					agentAlgorithm[agentCounter].MovementType(AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT, true);
					targetLossMode[agentCounter]				= false;
				}

				if (!losBetweenAgentAndTarget[agentCounter])
				{
					cout << "LOS between agent" << agentCounter << " and target LOST\n";
					if (!targetLossMode[agentCounter])
					{
						lastSeenTargetLocation					= targetCurrentLocation;
						targetLossMode[agentCounter]			= true;
					}
				}
			}

			char cString[10];
			sprintf(cString, "%04d", simulationSeconds);
			std::string	cppString(cString);

//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- Begin
			filename								= agent_and_target_base_filename;
			filename								+= cppString; // std::to_string(cString);//std::to_string(simulationSeconds);
			text									= agent_and_target_base_text;
			text									+= std::to_string(simulationSeconds);

			agent[0].GraphicOpen(filename, text, true);
			agent[0].GraphicText(textLocation, steps_text);
			agent[0].GraphicLine(targetCurrentLocation, targetNextLocation, AI_SUPPORT_CLASSES_COLOR_WHITE, true);


			for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
			{
				//	Draws a cross at the agent
				agent[0].GraphicCross(agentNextLocation[agentCounter], AI_SUPPORT_CLASSES_COLOR_PURPLE, false);
				if (losBetweenAgentAndTarget[agentCounter])
				{
					//	Draws a gray line for LOS between agent and target
					agent[0].GraphicLine(agentNextLocation[agentCounter], targetNextLocation, AI_SUPPORT_CLASSES_COLOR_GRAY, false);
				}
				else
				{
					//	Shows a text "LOS lost"
					agent[0].GraphicText(noLosTextLocation, "agent" +  std::to_string(agentCounter) + " LOS lost");
				}
				agent[0].GraphicClose(AI_SUPPORT_CLASSES_GRAPHIC_TYPE_PNG);
			}

//	-	3.2)	Progress command will take in account the potential next location of both the "target" and the "agent" so that will have LOS 
//					between "agent" and "target" as much as possible time	- End

			if (target.CurrentLocation() == target.DestinationLocation())
			{
				targetArrived	= true;
			}


			//	In case of some error
			if (simulationSeconds > 1000)
				break;
		}  


		//	Print the number of total LOS loss cases
		for (agentCounter = 0; agentCounter < QUANTITY_OF_AGENTS; agentCounter++)
		{
			cout << "There were " << quantityOfLosLoss[agentCounter] << " loss of LOS cases between agent" << agentCounter << " and target" << endl;
		}
		cout << "There were " << quantityOfLosLoss[QUANTITY_OF_AGENTS] << " loss of LOS cases between agent0/agent1 (at the same time) and target" << endl;

		//	Close the .csv DSM map for two agents and target file
		csvTwoAgentsSimulationCentralCalculationFile.close();
		
		delete [] agentAlgorithm;
		delete [] agent;

	}	// _TwoAgentsSimulationCentralCalculation()
