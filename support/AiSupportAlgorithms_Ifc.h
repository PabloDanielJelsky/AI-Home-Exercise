//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportAlgorithms_Ifc.h
//
// Version:			01.02
//
// Description:		Support algorithms for the AI home excercise interface file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
//
// Copyright:
//
// Remarks:			The A* algorithm was adapted from https://www.geeksforgeeks.org/a-search-algorithm/
//
//	DEVELOPMENT HISTORY:
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	27-02-2021	Pablo Daniel Jelsky		01			00			
//	05-03-2021	Pablo Daniel Jelsky		01			01			Modification of internal representation
//																	of pixels.
//																The internal representation of the DSM map in the DsmInformation class is that 
//																the south-west (down-left) pixel is (0,0), and all the pixels are positive, 
//																and therefore, pixel in the north-east (up-right) is (Columns-1, Rows-1), where 
//																Columns is the total number of columns of the DSM file, and Rows is the total
//																number of rows of the DSM file
//	07-02-2021	Pablo Daniel Jelsky		01			02			Addition of new SwissArmyKnife class that provides new decisions for different
//																	algorithms. Also new class Astar that should have inside the functions for
//																	A* algorithm
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __AI_SUPPORT_ALGORITHMS_IFC_H__
#define	__AI_SUPPORT_ALGORITHMS_IFC_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <list>		// for lists
		#include <utility>	// for pairs
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
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
		typedef enum 
		{ 
			AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, 
			AI_SUPPORT_ALGORITHMS_8_PIXELS_MOVEMENT, 
			AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT 
						
		} AI_SUPPORT_ALGORITHMS_pixelsMovementType;

		/*---- data declarations ---------------------------------------------------*/
		typedef struct
		{
			int				losToPotentialLocations;
			int				minimumLosDistance;
			int				maximumLosDistance;
			int				closestObstacleDistance;
			int				minimumDistanceToSpecificLocation;
			
		}	AI_SUPPORT_ALGORITHMS_ranking;
		
		typedef struct
		{
			class Location					location;
			int								losToPotentialLocations;
			double							minimumLosDistance;
			double							maximumLosDistance;
			double							closestObstacleDistance;
			double							minimumDistanceToSpecificLocation;
			AI_SUPPORT_ALGORITHMS_ranking	ranking;
			int								importance;

		}	AI_SUPPORT_ALGORITHMS_losInfo;
		
		/*---- function prototypes -------------------------------------------------*/
		long AStarSearch(AI_SUPPORT_ALGORITHMS_pixelsMovementType typeOfPixelMovement, bool possibilityOfNotMoving, DsmInformation& dsmInformation, 
						Location sourceLocation, Location destinationLocation, list <Location>& targetPathList, string csvTargetPathFilename);
	
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
		// Class name		: SwissArmyKnife
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 07-03-2021
		// Description		: This class implements many tools that will help us with
		//						the decision in the high-level algorithm
		//
		/////////////////////////////////////////////////////////////////////////////////
		class SwissArmyKnife
		{
			public:
				//	Public member functions
				double ClosestObstacleDistance(Location &currentLocation, DsmInformation &dsmMapInfo);
				bool MovementType(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace);
				
				//	Information function members
				bool PossibleMovements(list <Location>& locationsList, Location &currentLocation);
				void PossibleMovements(list <Location>& locationsList, Location &currentLocation, DsmInformation &dsmMapInfo);
				int PossibleLineOfSightLocations(
								list <Location>& observerLocationsList, 
								list <Location>& observedLocationsList, 
								DsmInformation &dsmMapInfo, 
								list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList,
								Location& specificLocation,
								double minimumPotentialDistanceFromObserverToObserved = 0);
								
				//	Order function members
				void OrderInfoListByLos(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList);
				void OrderInfoListByMinimumDistanceToObserved(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList, bool orderByMinimumDistanceFirst = true);
				void OrderInfoListByMinimumDistanceToObstacle(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList, bool orderByMinimumDistanceFirst = false);
				
				//	Ranking function members
				void Ranking(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList);
				void RankingOrder(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList,
								unsigned short relativeImportanceMoreLosLocations,
								unsigned short relativeImportanceClosestMinimumDistanceToObserved,
								unsigned short relativeImportanceClosestMaximumDistanceToObserved,
								unsigned short relativeImportanceClosestDistanceToObstacle,
								unsigned short relativeImportanceClosestMinimumDistanceToSpecificLocation = 0,
								bool betterMoreLosLocations = true,
								bool betterClosestMinimumDistanceToObserved = true,
								bool betterClosestMaximumDistanceToObserved = true,
								bool betterClosestDistanceToObstacle = false);
								
				//	Logs function members
				bool Obstacles2Csv(DsmInformation &dsmMapInfo, string csvObstaclesFilename);
				
				//	Default Constructor 
				SwissArmyKnife(); 
				//	Parametrized Constructor 
				SwissArmyKnife(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace);
				//	Destructor
				~SwissArmyKnife();

			protected:
				//	Protected member functions
				//	Protected variables
				
			private:
				//	Private member functions
				//	Private variables
				AI_SUPPORT_ALGORITHMS_pixelsMovementType	pixelMovementType;
				bool										couldStayInPlace;		//	If the algorithm also allows the object to stay in place (not moving)
				Timer										timer;

		};	//	class SwissArmyKnife
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name		: Astar
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 07-03-2021
		// Description		: This class implements the A* algorithm
		// Remarks			: A* (pronounced "A-star") is a graph traversal and path search 
		//						algorithm, which is often used in many fields of computer 
		//						science due to its completeness, optimality, and optimal efficiency.
		//						One major practical drawback is its space complexity, 
		//						as it stores all generated nodes in memory. 
		//						Thus, in practical travel-routing systems, it is generally 
		//						outperformed by algorithms which can pre-process the graph 
		//						to attain better performance, as well as memory-bounded 
		//						approaches; however, A* is still the best solution in many cases.
		//
		/////////////////////////////////////////////////////////////////////////////////
		class Astar
		{
			public:
				//	Public member functions

				
				//	Default Constructor 
				Astar(); 
				//	Parametrized Constructor 
				Astar(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace);
				//	Destructor
				~Astar();

			protected:
				//	Protected member functions
				//	Protected variables
				
			private:
				//	Private member functions
				void _Init(void);
				//	Private variables
				bool										initialized = false;
				AI_SUPPORT_ALGORITHMS_pixelsMovementType	pixelMovementType;
				bool										couldStayInPlace;		//	If the algorithm also allows the object to stay in place (not moving)
				DsmInformation								*dsmInformation	= nullptr;
				Location 									sourceLocation;
				Location 									destinationLocation;
				list <Location> 							source2DestinationPath;
				string 										csvSource2DestinationPathFilename;
				ofstream									csvSource2DestinationPathFile;
				Timer										timer;

		};	//	class Astar
	
#endif	// __AI_SUPPORT_ALGORITHMS_IFC_H__
