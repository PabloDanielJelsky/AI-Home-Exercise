//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportAlgorithms.cpp
//
// Version:			01.02
//
// Description:		Support algorithms for the AI home excercise source file
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
//	27-02-2021	Pablo Daniel Jelsky		01			00			Initial
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	=================
//	=================
//	A* Explanation // 
//	================
//	================
//		Consider a square grid having many obstacles and we are given a starting cell and a target cell. We want to reach the target cell 
//			(if possible) from the starting cell as quickly as possible. Here A* Search Algorithm comes to the rescue.
//		What A* Search Algorithm does is that at each step it picks the node according to a value-‘f’ which is a parameter equal to the sum 
//			of two other parameters – ‘g’ and ‘h’. 
//		At each step it picks the node/cell having the lowest ‘f’, and process that node/cell.
//		We define ‘g’ and ‘h’ as simply as possible below
//			g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there. 
//			h = the estimated movement cost to move from that given square on the grid to the final destination. 
//				This is often referred to as the heuristic, which is nothing but a kind of smart guess. We really don’t know the actual
//				distance until we find the path, because all sorts of things can be in the way (walls, water, etc.). 
//				There can be many ways to calculate this ‘h’ which are discussed in the later sections.
//
//	================
//	================
//	A* Algorithm  //
//	===============
//	===============
//		We create two lists – Open List and Closed List (just like Dijkstra Algorithm) 
//		1.  Initialize the open list
//		2.  Initialize the closed list put the starting node on the open list (you can leave its f at zero)
//		3.  while the open list is not empty
//				a) find the node with the least f on the open list, call it "q"
//				b) pop q off the open list
//				c) generate q's 8 successors and set their parents to q
//				d) for each successor
//						i) if successor is the goal, stop search
//							successor.g = q.g + distance between successor and q
//							successor.h = distance from goal to 
//							successor (This can be done using many ways, we will discuss three heuristics- Manhattan, Diagonal and Euclidean Heuristics)
//							successor.f = successor.g + successor.h
//						ii) if a node with the same position as successor is in the OPEN list which has a lower f than successor, skip this successor
//						iii) if a node with the same position as successor  is in the CLOSED list which has a lower f than successor, skip this successor
//							otherwise, add  the node to the open list 
//					end (for loop)
//				 e) push q on the closed list
//			end (while loop)
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
		#include "AiSupportAlgorithms.h"
	
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
		/*---- function prototypes -------------------------------------------------*/



	/*
		****************************************************************************
		* PUBLIC FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: AStarSearch
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		:05-03-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Finds the shortest path between a given source cell to a 
		//							destination cell according to A* Search Algorithm
		// Remarks				: Returns the number of steps in the returning path and 
		//							a list with the path
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: Type of pixel movement (4, 8, 12 pixels per cycle),
		//							possibility of not moving (staying at place) (as moving),
		//							DSM map information (as DsmInformation) and 
		//							source and destination locations (as DsmLocation)
		//							and the CSV target path filen name
		/////////////////////////////////////////////////////////////////////////////////
		long AStarSearch(AI_SUPPORT_ALGORITHMS_pixelsMovementType typeOfPixelMovement, bool possibilityOfNotMoving, 
							DsmInformation& dsmInformation, Location sourceLocation, 
							Location destinationLocation, list <Location>& targetPathList, 
							string csvTargetPathFilename)
		{
			int	targetPathSize					= 0;
			int	dsmQuantityOfColumns			= dsmInformation.Columns();
			int	dsmQuantityOfRows				= dsmInformation.Rows();
			
			//	To store the first enumerator, and the last one, depending in the quantity of pixels per each movement
			directionEnumerator	directionFirst	= (possibilityOfNotMoving) ? DIRECTION_SAME_PLACE : DIRECTION_NORTH;
			directionEnumerator directionLast;
			
			// If the source is out of range
			if (!_IsValid(dsmInformation, sourceLocation)) 
			{
				printf("Source is invalid\n");
				return EXIT_FAILURE;
			}
		 
			// If the destination is out of range
			if (!_IsValid(dsmInformation, destinationLocation)) 
			{
				printf("Destination is invalid\n");
				return EXIT_FAILURE;
			}
		 
			// Either the source or the destination is blocked
			if (!_IsUnblocked(dsmInformation, sourceLocation) || !_IsUnblocked(dsmInformation, destinationLocation)) 
			{
				printf("Source or the destination is not in 'ground' level\n");
				return EXIT_FAILURE;
			}
		 
			// If the destination cell is the same as source cell
			if (_IsDestination(sourceLocation, destinationLocation)) 
			{
				printf("We are already at the destination\n");
				return EXIT_FAILURE;
			}
			
			switch (typeOfPixelMovement)
			{
				case AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT:
					/*
						 Generating all the 4 successor of this cell
				 
									N 
									| 
									|
							  W----Cell----E
									| 
									|
									S
				 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
					*/	
					
					//	Implying exactly moving 1 pixel each time
					directionLast	= DIRECTION_WEST;
					break;
				case AI_SUPPORT_ALGORITHMS_8_PIXELS_MOVEMENT:
					/*
						 Generating all the 8 successor of this cell
				 
							N.W		N		N.E
								|	|	  | 
								  |	|  |
							  W----Cell----E
								  |	|  |
								|	|	  |
							S.W		S		S.E
				 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row+1)
							N.W--> North-West  		(column-1, row+1)
							S.E--> South-East  		(column+1, row-1)
							S.W--> South-West  		(column-1, row-1)
					*/	
					//	Implying moving to all adjacent pixels each time
					directionLast	= DIRECTION_SOUTH_WEST;
					break;
				case AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT:
					/*
						 Generating all the 12 successor of this cell
						 
						 
						 			N
						 			|
									|
							N.W		N		N.E
								|	|	  | 
								  |	|  |
						W----W----Cell----E----E
								  |	|  |
								|	|	  |
							S.W		S		S.E
									|
									|
									S 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row+1)
							N.W--> North-West  		(column-1, row+1)
							S.E--> South-East  		(column+1, row-1)
							S.W--> South-West  		(column-1, row-1)
							N.N--> North-North		(column, row+2)
							S.S--> South-South		(column, row-2)
							E.E--> East-East		(column+2, row)
							W.W--> West-West		(column-2, row)
					*/	
					//	Implying moving up to two pixels each time
					directionLast	= DIRECTION_WEST_WEST;
					break;
				default:
					break;
			}
	 
			// Create a closed list and initialise it to false which
			// means that no cell has been included yet This closed
			// list is implemented as a boolean 2D array
			bool *pClosedList	= new bool[dsmQuantityOfColumns * dsmQuantityOfRows];
			memset(pClosedList, false, sizeof(*pClosedList) * dsmQuantityOfColumns * dsmQuantityOfRows);
			
			// Declare a 2D array of structure to hold the details of that cell
			cell *pCellDetails	= new cell[dsmQuantityOfColumns * dsmQuantityOfRows];
		 
			int row, column;
			
			//	Create the .csv target path file
			std::ofstream csvTargetPathFile;
			csvTargetPathFile.open (csvTargetPathFilename);
			//	Create the header
			csvTargetPathFile << "Column, Row, Step, Elevation\n";
		 
			for (row = 0; row < dsmQuantityOfRows; row++) 
			{
				for (column = 0; column < dsmQuantityOfColumns; column++) 
				{
				    pCellDetails[(row * dsmQuantityOfColumns) + column].f		= FLT_MAX;
				    pCellDetails[(row * dsmQuantityOfColumns) + column].g		= FLT_MAX;
				    pCellDetails[(row * dsmQuantityOfColumns) + column].h		= FLT_MAX;
				    pCellDetails[(row * dsmQuantityOfColumns) + column].parentLocation.Modify(AI_SUPPORT_CLASSES_INVALID_COLUMN, AI_SUPPORT_CLASSES_INVALID_ROW);
				}
			}
		 
			// Initialising the parameters of the starting node
			row 																= sourceLocation.Row();
			column 																= sourceLocation.Column();
			pCellDetails[(row * dsmQuantityOfColumns) + column].f				= 0.0;
			pCellDetails[(row * dsmQuantityOfColumns) + column].g				= 0.0;
			pCellDetails[(row * dsmQuantityOfColumns) + column].h				= 0.0;
			pCellDetails[(row * dsmQuantityOfColumns) + column].parentLocation.Modify(column, row);
		 
			/*
			 Create an open list having information as-
			 <f, <Location>>
			 where f = g + h,
			 and Location.Row(), Location.Column() are the row and column index of that cell
			 Note that 0 <= Location.Row() <= dsmQuantityOfRows-1 & 0 <= Location.Column() <= dsmQuantityOfColumns-1
			 This open list is implenented as a set of pair of
			 pair.*/
			set <pPair> openList;
		 
			// Put the starting cell on the open list and set its
			// 'f' as 0
			openList.insert(make_pair(0.0, make_pair(column, row)));
		 
			// We set this boolean value as false as initially
			// the destination is not reached.
			bool foundDest = false;
			
			// To store the 'g', 'h' and 'f' of the successors
			double 	gNew, hNew, fNew;
		 
			while (!openList.empty()) 
			{
				pPair p = *openList.begin();
		 
				// Remove this vertex from the open list
				openList.erase(openList.begin());
		 
				// Add this vertex to the closed list
				column															= p.second.first;
				row																= p.second.second;
				pClosedList[(row * dsmQuantityOfColumns) + column]				= true;
		 
				for (int direction = (int) directionFirst; direction <= (int) directionLast; direction++)
				{		
					Location	temporalDsmLocation;
					double		distanceBetweenSuccessorAndCurrentCell;
					
					switch (direction)
					{
						case DIRECTION_SAME_PLACE:
							// Stay at the same place, do NOT do anything
							temporalDsmLocation.Modify(column, row);
							distanceBetweenSuccessorAndCurrentCell	= 0;
							break;
						case DIRECTION_NORTH:
							//----------- 1st Successor (North) ------------
							temporalDsmLocation.Modify(column, row + 1);
							distanceBetweenSuccessorAndCurrentCell	= 1;
							break;
						case DIRECTION_SOUTH:
							//----------- 2nd Successor (South) ------------
							temporalDsmLocation.Modify(column, row - 1);
							distanceBetweenSuccessorAndCurrentCell	= 1;
							break;
						case DIRECTION_EAST:
							//----------- 3rd Successor (East) ------------
							temporalDsmLocation.Modify(column + 1, row);
							distanceBetweenSuccessorAndCurrentCell	= 1;
							break;
						case DIRECTION_WEST:
							//----------- 4th Successor (West) ------------
							temporalDsmLocation.Modify(column - 1, row);
							distanceBetweenSuccessorAndCurrentCell	= 1;
							break;
						case DIRECTION_NORTH_EAST:
							//----------- 5th Successor (North-East) ------------
							temporalDsmLocation.Modify(column + 1, row + 1);
							distanceBetweenSuccessorAndCurrentCell	= 1.4142;
							break;
						case DIRECTION_NORTH_WEST:
							//----------- 6th Successor (North-West) ------------
							temporalDsmLocation.Modify(column - 1, row + 1);
							distanceBetweenSuccessorAndCurrentCell	= 1.4142;
							break;
						case DIRECTION_SOUTH_EAST:
							//----------- 7th Successor (South-East) ------------
							temporalDsmLocation.Modify(column + 1, row - 1);
							distanceBetweenSuccessorAndCurrentCell	= 1.4142;
							break;
						case DIRECTION_SOUTH_WEST:
							//----------- 8th Successor (South-West) ------------
							temporalDsmLocation.Modify(column - 1, row - 1);
							distanceBetweenSuccessorAndCurrentCell	= 1.4142;
							break;
						case DIRECTION_NORTH_NORTH:
							//----------- 9th Successor (North-North) ------------
							temporalDsmLocation.Modify(column, row + 2);
							distanceBetweenSuccessorAndCurrentCell	= 2;
							break;
						case DIRECTION_SOUTH_SOUTH:
							//----------- 10th Successor (South-South) ------------
							temporalDsmLocation.Modify(column, row - 2);
							distanceBetweenSuccessorAndCurrentCell	= 2;
							break;
						case DIRECTION_EAST_EAST:
							//----------- 11th Successor (East-East) ------------
							temporalDsmLocation.Modify(column + 2, row);
							distanceBetweenSuccessorAndCurrentCell	= 2;
							break;
						case DIRECTION_WEST_WEST:
							//----------- 12th Successor (West-West) ------------
							temporalDsmLocation.Modify(column - 2, row);
							distanceBetweenSuccessorAndCurrentCell	= 2;
							break;
						default:
							printf("The direction %d is not a valid one\n", direction);
							
							if ("" != csvTargetPathFilename)
								csvTargetPathFile.close();
								
							return EXIT_FAILURE;
							
					}	//	switch()
					
					// Only process this cell if this is a valid one
					if (_IsValid(dsmInformation, temporalDsmLocation)) 
					{
						// If the destination cell is the same as the
						// current successor
						if (_IsDestination(temporalDsmLocation, destinationLocation)) 
						{
							// Set the Parent of the destination cell
							pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].parentLocation.Modify(column, row);
							printf("The destination cell is found\n");
							_TracePath(dsmInformation, pCellDetails, destinationLocation, &targetPathSize, targetPathList, csvTargetPathFile);
							foundDest	= true;
							
							//	Deallocate the dynamic arrays created in this function
							delete [] pClosedList;
							delete [] pCellDetails;
							
							csvTargetPathFile.close();
								
							return (targetPathSize-1);
						}
						// If the successor is already on the closed
						// list or if it is blocked, then ignore it.
						// Else do the following
						else if (!pClosedList[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()]
								 && _IsUnblocked(dsmInformation, temporalDsmLocation)) 
						{
							gNew	= pCellDetails[(row * dsmQuantityOfColumns) + column].g + distanceBetweenSuccessorAndCurrentCell;
							hNew	= _CalculateHValueForAiHomeExercise(temporalDsmLocation, destinationLocation);
							fNew	= gNew + hNew;

							// If it isn’t on the open list, add it to
							// the open list. Make the current square
							// the parent of this square. Record the
							// f, g, and h costs of the square cell
							//                OR
							// If it is on the open list already, check
							// to see if this path to that square is
							// better, using 'f' cost as the measure.
							if ((FLT_MAX == pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].f)
								|| (pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].f > fNew)) 
							{
								openList.insert(make_pair(fNew, make_pair(temporalDsmLocation.Column(), temporalDsmLocation.Row())));
			 
								// Update the details of this cell
								pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].f	= fNew;
								pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].g	= gNew;
								pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].h	= hNew;
								pCellDetails[(temporalDsmLocation.Row() * dsmQuantityOfColumns) + temporalDsmLocation.Column()].parentLocation.Modify(column, row);
							}
						}
					}
				}
			}

			//	Deallocate the dynamic arrays created in this function
			delete [] pClosedList;
			delete [] pCellDetails;
			
			//	Closing CSV file
			csvTargetPathFile.close();
			
			// When the destination cell is not found and the open
			// list is empty, then we conclude that we failed to
			// reach the destination cell. This may happen when 
			// there is no way to destination cell (due to
			// blockages)
			if (!foundDest)
			{
				printf("Failed to find the Destination Cell\n");
				return EXIT_FAILURE;
			}
			
			return (targetPathSize-1);
		}

	
	/*
		****************************************************************************
		* PRIVATE FUNCTION DEFINITIONS
		****************************************************************************
	*/	
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareLosQuantityOfPossibleLocations
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 09-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info quantity of possible locations and decides
		//							which has more
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareLosQuantityOfPossibleLocations(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if first goes first in returned list, false otherwise

			return (first.losToPotentialLocations > second.losToPotentialLocations);
			
		}	//	_CompareLosQuantityOfPossibleLocations()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareMinimumDistanceFirst
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 09-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info minimum distance and returns true if first one
		//							has minimum LOS, false otherwise
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareMinimumDistanceToObservedFirst(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if first goes first in returned list, false otherwise
		
			return (first.minimumLosDistance < second.minimumLosDistance);
			
		}	//	_CompareMinimumDistanceToObservedFirst()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareMinimumDistanceToObservedLast
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 09-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info minimum distance and returns true if second one
		//							has minimum LOS, false otherwise
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareMinimumDistanceToObservedLast(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if second goes first in returned list, false otherwise
		
			return (first.minimumLosDistance > second.minimumLosDistance);
			
		}	//	_CompareMinimumDistanceToObservedLast()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareMinimumDistanceToObstacleFirst
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info minimum distance to obstacle and returns true 
		//							if first has minimum distance to obstacle, otherwise
		//							false
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareMinimumDistanceToObstacleFirst(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if first goes first in returned list, false otherwise
		
			return (first.closestObstacleDistance < second.closestObstacleDistance);
			
		}	//	_CompareMinimumDistanceToObstacleFirst()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareMinimumDistanceToObstacleLast
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info minimum distance to obstacle and returns true 
		//							if second has minimum distance to obstacle, otherwise
		//							false
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareMinimumDistanceToObstacleLast(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if second goes first in returned list, false otherwise
		
			return (first.closestObstacleDistance > second.closestObstacleDistance);
			
		}	//	_CompareMinimumDistanceToObstacleLast()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: SwissArmyKnife
		// Function				: _CompareRanking
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Module description	: This module implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This private member function compares between two 
		//							LOS info rankings and returns true if first one
		//							has better ranking, false otherwise
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: two LOS info structures
		//
		/////////////////////////////////////////////////////////////////////////////////
		static bool _CompareRanking(const AI_SUPPORT_ALGORITHMS_losInfo& first, const AI_SUPPORT_ALGORITHMS_losInfo& second)
		{
			//	Returns true if first goes first in returned list, false otherwise
			return (first.importance > second.importance);
			
		}	//	_CompareRanking()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: _IsValid
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Checks whether given cell is a valid cell or not 
		//							(if it is in the range of the graph)
		// Remarks				: Returns true if the cell is in the graph,
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map information (as DsmInformation) and 
		//							location (as Location)
		/////////////////////////////////////////////////////////////////////////////////
		bool _IsValid(DsmInformation& dsmInformation, Location location)
		{
			// Returns true if row number and column number
			// is in range
			return (location.Row() >= 0) && (location.Row() < dsmInformation.Rows()) && (location.Column() >= 0)
				   && (location.Column() < dsmInformation.Columns());
				   
		}	//	_IsValid()	
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: _IsUnblocked
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Checks whether the given cell is blocked or not
		// Remarks				: Returns true if the cell is unblock (could be transversed),
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map information (as DsmInformation) and 
		//							location (as Location)
		/////////////////////////////////////////////////////////////////////////////////
		bool _IsUnblocked(DsmInformation& dsmInformation, Location location)
		{
			// Returns true if the cell is not blocked else false
			return ((dsmInformation.Obstacle(location)) ? false : true);
			
		}	//	_IsUnblocked()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: _IsDestination
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Checks whether destination cell has been reached or not
		// Remarks				: Returns true if the destination cell has been reached,
		//							false, otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: current and destination locations (as DsmLocation)
		/////////////////////////////////////////////////////////////////////////////////
		bool _IsDestination(Location currentLocation, Location destinationLocation)
		{
			return (currentLocation == destinationLocation);
				
		}	//	_IsDestination()
			
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: _CalculateHValueForAiHomeExercise
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Calculates the 'h' heuristics
		// Remarks				: Returns the 'h' heuristics as a double
		//							This function was 'adapted' to the limitations of 
		//								the home exercise where the speed is one 
		//								meter for second (and one meter is one pixel),
		//								therefore we could only move up/down, right/left
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: current and destination locations (as DsmLocation)
		/////////////////////////////////////////////////////////////////////////////////
		double _CalculateHValueForAiHomeExercise(Location currentLocation, Location destinationLocation)
		{
			int	differenceInColumns, differenceInRows;
			
			differenceInColumns	= abs(destinationLocation.Column()-currentLocation.Column());
			differenceInRows	= abs(destinationLocation.Row()-currentLocation.Row());
			
			return (differenceInColumns + differenceInRows);
			
		}	//	_CalculateHValueForAiHomeExercise()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Module name			: A* (pronounced "A-star")
		// Function				: _TracePath
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 27-02-2021
		// Module description	: This module is a graph traversal and path search algorithm
		// Function description	: Traces the path from the source to destination
		// Remarks				: Returns a list with the  target path and the target 
		//							path size until now
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			:  DSM map information (as DsmInformation),  
		//							pointer to cell details (as struct cell)
		//							, destination location (as DsmLocation),
		//							and the CSV target path file
		/////////////////////////////////////////////////////////////////////////////////
		void _TracePath(DsmInformation& dsmInformation, cell *pCellDetails, Location destinationLocation, int *pTargetPathSize, list <Location>& targetPathList, std::ofstream& csvTargetPathFile)
		{
			int	dsmQuantityOfColumns	= dsmInformation.Columns();
			int column					= destinationLocation.Column();
			int row						= destinationLocation.Row();
			int	targetPathSize			= *pTargetPathSize;
	 
			stack <Location> Path;
		 
			while (!(pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Row() == row
				     && pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Column() == column)) 
			{
				Path.push(Location(column, row));
				int temp_column	= pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Column();
				int temp_row	= pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Row();
				column			= temp_column;
				row 			= temp_row;
			}
		 
			Path.push(Location(column, row));
			while (!Path.empty()) 
			{
				Location p			= Path.top();
				Path.pop();

				targetPathSize++;
				*pTargetPathSize	= targetPathSize;
				csvTargetPathFile << p.Column() << "," << p.Row() << "," << targetPathSize-1 << ","  << dsmInformation.Elevation(p) << "\n";
				targetPathList.push_back(p);
			}
 
			return;

		}	//	_TracePath()


	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithm
		// Function description	:
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		SwissArmyKnife::SwissArmyKnife() 
		{ 
			this->MovementType(AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT, false);
			
		}	//	SwissArmyKnife::SwissArmyKnife() 

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithm
		// Function description	: This constructor takes as parameter the characteristics
		//							of pixel movement
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: pixel movement type and if the object could also
		//							stay in place (not moving)
		/////////////////////////////////////////////////////////////////////////////////
		SwissArmyKnife::SwissArmyKnife(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace)
		{ 
			this->MovementType(pixelMovementType, couldStayInPlace);
			
		}	//	SwissArmyKnife::SwissArmyKnife()      

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	:
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		SwissArmyKnife::~SwissArmyKnife() 
		{ 
		}	//	SwissArmyKnife::~SwissArmyKnife()
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Astar
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements the A* algorithm
		// Function description	:
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Astar::Astar() 
		{ 
			this->_Init();
			
		}	//	Astar::Astar() 

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Astar
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements the A* algorithm
		// Function description	: This constructor takes as parameter the characteristics
		//							of pixel movement
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: pixel movement type and if the object could also
		//							stay in place (not moving)
		/////////////////////////////////////////////////////////////////////////////////
		Astar::Astar(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace)
		{ 
			this->_Init();
			
			this->pixelMovementType						= pixelMovementType;
			this->couldStayInPlace						= couldStayInPlace;
			
		}	//	Astar::Astar()      

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Astar
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements the A* algorithm
		// Function description	:
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Astar::~Astar() 
		{ 
			if ("" != this->csvSource2DestinationPathFilename)
				this->csvSource2DestinationPathFile.close();
			
		}	//	Astar::~Astar()
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: MovementType
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function sets the pixel movement
		//							characteristics of the object
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: pixel movement type and boolean deciding if the object
		//							has the capability of also stay in place (not moving)
		/////////////////////////////////////////////////////////////////////////////////
		bool SwissArmyKnife::MovementType(AI_SUPPORT_ALGORITHMS_pixelsMovementType pixelMovementType, bool couldStayInPlace)
		{
			this->pixelMovementType		= pixelMovementType;
			this->couldStayInPlace		= couldStayInPlace;
			
			return true;
		
		}	//	SwissArmyKnife::MovementType()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: ClosestObstacleDistance
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function returns the distance to
		//							the closest obstacle from the current location
		// Remarks				: Do it more efficient in the future
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: current location and DSM map info
		/////////////////////////////////////////////////////////////////////////////////
		double SwissArmyKnife::ClosestObstacleDistance(Location &currentLocation, DsmInformation &dsmMapInfo)
		{
			int		column, row;
			double	distanceFromCurrentLocationToObstacle	= DBL_MAX;
			
			for (column = 0; column < dsmMapInfo.Columns(); column++)
			{
				for (row = 0; row < dsmMapInfo.Rows(); row++)
				{
					Location	location(column, row);
					
					if (dsmMapInfo.Obstacle(location))
					{
						//	If the locations is an obstacle, calculate the distance to current location
						double	distance						= location.Distance(currentLocation);
						distanceFromCurrentLocationToObstacle	= min(distanceFromCurrentLocationToObstacle, distance);
					}
				}
			}
			
			return distanceFromCurrentLocationToObstacle;
			
		}	//	 SwissArmyKnife::ClosestObstacleDistance()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: PossibleMovements
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function returns back all the
		//							possible movements of an object given its location
		// Remarks				: There is no DSM constraints because there is no
		//							DSM file as a parameter
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: list to be return with possible movements locations,
		//							current location
		/////////////////////////////////////////////////////////////////////////////////
		bool SwissArmyKnife::PossibleMovements(list <Location>& locationsList, Location &currentLocation)
		{	
			//	Clear the list of locations
			locationsList.clear();
			
			int				column 	= currentLocation.Column();
			int				row		= currentLocation.Row();

			//	To store the first enumerator, and the last one, depending in the quantity of pixels per each movement
			directionEnumerator	directionFirst	= (this->couldStayInPlace) ? DIRECTION_SAME_PLACE : DIRECTION_NORTH;
			directionEnumerator directionLast;
			
			switch (this->pixelMovementType)
			{
				case AI_SUPPORT_ALGORITHMS_4_PIXELS_MOVEMENT:
					/*
						 Generating all the 4 successor of this cell
				 
									N 
									| 
									|
							  W----Cell----E
									| 
									|
									S
				 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
					*/	
					
					//	Implying exactly moving 1 pixel each time
					directionLast	= DIRECTION_WEST;
					break;
				case AI_SUPPORT_ALGORITHMS_8_PIXELS_MOVEMENT:
					/*
						 Generating all the 8 successor of this cell
				 
							N.W		N		N.E
								|	|	  | 
								  |	|  |
							  W----Cell----E
								  |	|  |
								|	|	  |
							S.W		S		S.E
				 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row+1)
							N.W--> North-West  		(column-1, row+1)
							S.E--> South-East  		(column+1, row-1)
							S.W--> South-West  		(column-1, row-1)
					*/	
					//	Implying moving to all adjacent pixels each time
					directionLast	= DIRECTION_SOUTH_WEST;
					break;
				case AI_SUPPORT_ALGORITHMS_12_PIXELS_MOVEMENT:
					/*
						 Generating all the 12 successor of this cell
						 
						 
						 			N
						 			|
									|
							N.W		N		N.E
								|	|	  | 
								  |	|  |
						W----W----Cell----E----E
								  |	|  |
								|	|	  |
							S.W		S		S.E
									|
									|
									S 
							Cell-->Popped Cell		(column, row)
							N -->  North			(column, row+1)
							S -->  South			(column, row-1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row+1)
							N.W--> North-West  		(column-1, row+1)
							S.E--> South-East  		(column+1, row-1)
							S.W--> South-West  		(column-1, row-1)
							N.N--> North-North		(column, row+2)
							S.S--> South-South		(column, row-2)
							E.E--> East-East		(column+2, row)
							W.W--> West-West		(column-2, row)
					*/	
					//	Implying moving up to two pixels each time
					directionLast	= DIRECTION_WEST_WEST;
					break;
				default:
					break;
			}
			
			for (int direction = (int) directionFirst; direction <= (int) directionLast; direction++)
			{		
				Location	possibleLocation;

				switch (direction)
				{
					case DIRECTION_SAME_PLACE:
						// Stay at the same place, do NOT do anything
						possibleLocation.Modify(column, row);
						break;
					case DIRECTION_NORTH:
						//----------- 1st Successor (North) ------------
						possibleLocation.Modify(column, row + 1);
						break;
					case DIRECTION_SOUTH:
						//----------- 2nd Successor (South) ------------
						possibleLocation.Modify(column, row - 1);
						break;
					case DIRECTION_EAST:
						//----------- 3rd Successor (East) ------------
						possibleLocation.Modify(column + 1, row);
							break;
					case DIRECTION_WEST:
						//----------- 4th Successor (West) ------------
						possibleLocation.Modify(column - 1, row);
						break;
					case DIRECTION_NORTH_EAST:
						//----------- 5th Successor (North-East) ------------
						possibleLocation.Modify(column + 1, row + 1);
						break;
					case DIRECTION_NORTH_WEST:
						//----------- 6th Successor (North-West) ------------
						possibleLocation.Modify(column - 1, row + 1);
						break;
					case DIRECTION_SOUTH_EAST:
						//----------- 7th Successor (South-East) ------------
						possibleLocation.Modify(column + 1, row - 1);
						break;
					case DIRECTION_SOUTH_WEST:
						//----------- 8th Successor (South-West) ------------
						possibleLocation.Modify(column - 1, row - 1);
						break;
					case DIRECTION_NORTH_NORTH:
						//----------- 9th Successor (North-North) ------------
						possibleLocation.Modify(column, row + 2);
						break;
					case DIRECTION_SOUTH_SOUTH:
						//----------- 10th Successor (South-South) ------------
						possibleLocation.Modify(column, row - 2);
						break;
					case DIRECTION_EAST_EAST:
						//----------- 11th Successor (East-East) ------------
						possibleLocation.Modify(column + 2, row);
						break;
					case DIRECTION_WEST_WEST:
						//----------- 12th Successor (West-West) ------------
						possibleLocation.Modify(column - 2, row);
						break;
					default:
						cout << "The direction " << direction << " is not a valid one\n";
						return false;

				}	//	switch()
				
				//	do not enter into the list the locations with column or row less than 0
				if (possibleLocation.Column() >= 0 && possibleLocation.Row() >= 0)
				{
					locationsList.push_back(possibleLocation);
				}
			}
			
			return true;
			
		}	//	SwissArmyKnife::PossibleMovements()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: PossibleMovements
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function returns back all the
		//							possible movements of an object given its location
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: list to be return with possible movements locations,
		//							DSM map, current location
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::PossibleMovements(list <Location>& locationsList, Location &currentLocation, DsmInformation &dsmMapInfo)
		{
			//	Clear the list of locations
			locationsList.clear();
			
			//	First bring ALL the possible movements list without DSM constraints
			this->PossibleMovements(locationsList, currentLocation);
			
			//	And now "fine-tune" with DSM map info
			
			// Iterate over the list using Iterators and erase elements
			// that are not in the DSM map or the locations that are an
			//	obstacle while iterating through list
			std::list<Location>::iterator it = locationsList.begin();
			while (it != locationsList.end()) 
			{
				// Remove elements while iterating
				if ((!dsmMapInfo.IsInDsmMap(*it)) || (dsmMapInfo.Obstacle(*it)))
				{
					//	Remove from the list location that are not in the DSM map or the locations that are an obstacle
					// erase() makes the passed iterator invalid
					// But returns the iterator to the next of deleted element
					it	= locationsList.erase(it);
				}
				else
					it++;
			}

		}	//	SwissArmyKnife::PossibleMovements()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: PossibleMovements
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function returns back the information
		//							regarding LOS "quality" of potential observed person
		//							next movements
		// Remarks				: The function returns also the quantity of possible LOS
		//							potential observer locations
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: observer "potential" locations, observed "potential"
		//							locations, DSM map information, and the function
		//							brings back the information about the LOS positions
		//					Default parameters:
		//							minimum potential distance from observer to observed
		//							(if the minimum distance is less that this one,
		//							then, this location won't  be inserted in the list
		//							of potential observer locations)
		//
		/////////////////////////////////////////////////////////////////////////////////
		int SwissArmyKnife::PossibleLineOfSightLocations(
				list <Location>& observerLocationsList, 
				list <Location>& observedLocationsList, 
				DsmInformation &dsmMapInfo, 
				list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList,
				double minimumPotentialDistanceFromObserverToObserved)
		{
			AI_SUPPORT_ALGORITHMS_losInfo	observerLosInfo;
			std::list<Location>::iterator 	observerLocationIterator;
			std::list<Location>::iterator 	observedLocationIterator;
			int								observerPotentialLocationsWithLos = 0;
			int								losBetweenObserverAndObserved;
			double							minimumLosDistance;
			double							maximumLosDistance;
			
			//	Clear the list for observer locations
			observerLosInfoList.clear();
			
			//	Iterate between all the observer possible locations
			observerLocationIterator = observerLocationsList.begin();
			while (observerLocationIterator != observerLocationsList.end()) 
			{
				losBetweenObserverAndObserved	= 0;
				minimumLosDistance				= -1.0;
				maximumLosDistance				= -1.0;
				
				//	And also iterate between all the observed possible locations
				observedLocationIterator = observedLocationsList.begin();
				while (observedLocationIterator != observedLocationsList.end()) 
				{
					if (dsmMapInfo.LineOfSight(*observerLocationIterator, *observedLocationIterator))
					{
						double	distanceBetweenObserverAndObserved;
						

						//	If there exists a LOS between observer and observed,
						//	calculate the distance between these two points
						distanceBetweenObserverAndObserved	= (*observerLocationIterator).Distance((*observedLocationIterator));

						if (!losBetweenObserverAndObserved)
						{
							//	If it was the first observation, then, maximum and minimum are the same
							minimumLosDistance	=	maximumLosDistance	= distanceBetweenObserverAndObserved;
						}
						else
						{
							//	If it is not the first observation, then calculate the maximum and the minimum
							minimumLosDistance	= std::min(minimumLosDistance, distanceBetweenObserverAndObserved);
							maximumLosDistance	= std::max(maximumLosDistance, distanceBetweenObserverAndObserved);
						}
						
						//	Increment number of points with LOS for this observer location
						losBetweenObserverAndObserved++;
					}
					observedLocationIterator++;
				}
				
				if (losBetweenObserverAndObserved)
				{
					//	If there was at least one potential LOS between the observer location and "potentials" observed locations
					if (minimumPotentialDistanceFromObserverToObserved <= minimumLosDistance)
					{
						//	If the minimum LOS distance calculated for this "potential" observer location
						//	was greater than the minimum defined by the decision
						
						//	Fill the LOS info structure
						observerLosInfo.location.Modify(((*observerLocationIterator)).Column(), ((*observerLocationIterator)).Row());
						observerLosInfo.losToPotentialLocations	= losBetweenObserverAndObserved;
						observerLosInfo.minimumLosDistance		= minimumLosDistance;
						observerLosInfo.maximumLosDistance		= maximumLosDistance;
						observerLosInfo.closestObstacleDistance	= this->ClosestObstacleDistance(observerLosInfo.location, dsmMapInfo);
						//	Insert the strucure into the LOS info list for observer locations
						observerLosInfoList.push_back(observerLosInfo);
						//	Increment the quantity of potential LOS locations for observer
						observerPotentialLocationsWithLos++;
					}
				}
				
				observerLocationIterator++;
			}
			
			return observerPotentialLocationsWithLos;
			
		}	//	SwissArmyKnife::PossibleLineOfSightLocations()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: OrderInfoListByLos
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 09-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function sorts the LOS info list by
		//							LOS "quality" of potential observed person
		//							next movements (maximum potential LOS locations)
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: LOS info list of locations
		//
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::OrderInfoListByLos(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList)
		{
			observerLosInfoList.sort(_CompareLosQuantityOfPossibleLocations);
			
		}	//	SwissArmyKnife::OrderInfoListByLos()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: OrderInfoListByMinimumDistanceToObserved
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 09-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function sorts the LOS info list by
		//							minimum potential distance to observed
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: LOS info list of locations
		//					Default argument: order by minimum distance first
		//
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::OrderInfoListByMinimumDistanceToObserved(
									list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList, 
									bool orderByMinimumDistanceFirst)
		{
			if (orderByMinimumDistanceFirst)
				observerLosInfoList.sort(_CompareMinimumDistanceToObservedFirst);
			else
				observerLosInfoList.sort(_CompareMinimumDistanceToObservedLast);
			
		}	//	SwissArmyKnife::OrderInfoListByMinimumDistanceToObserved()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: OrderInfoListByMinimumDistanceToObstacle
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function sorts the LOS info list by
		//							minimum distance to obstacle
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: LOS info list of locations
		//					Default argument: order by minimum distance first
		//
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::OrderInfoListByMinimumDistanceToObstacle(
									list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList, 
									bool orderByMinimumDistanceFirst)
		{
			if (orderByMinimumDistanceFirst)
				observerLosInfoList.sort(_CompareMinimumDistanceToObstacleFirst);
			else
				observerLosInfoList.sort(_CompareMinimumDistanceToObstacleLast);
			
		}	//	SwissArmyKnife::OrderInfoListByMinimumDistanceToObstacle()

		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: Ranking
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function ranks the observer info list
		//							by setting the percentage of the element into the
		//							minimum and maximum values
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: LOS info list of locations
		//
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::Ranking(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList)
		{
			int		minLosBetweenObserverAndObserved 		= INT_MAX;
			int		maxLosBetweenObserverAndObserved		= 0;
			double	minMinimumLosDistance					= DBL_MAX;
			double	maxMinimumLosDistance					= -1.0;
			double	minMaximumLosDistance					= DBL_MAX;
			double	maxMaximumLosDistance					= -1.0;
			double	minClosestObstacleDistance				= DBL_MAX;
			double	maxClosestObstacleDistance				= -1.0;
			int		rangeLosBetweenObserverAndObserved;
			double	rangeMinimumLosDistance;
			double	rangeMaximumLosDistance;
			double	rangeClosestObstacleDistance;
			

			//	Calculate minimum and maximum values in the list
			std::list<AI_SUPPORT_ALGORITHMS_losInfo>::iterator	it = observerLosInfoList.begin();
			while (it != observerLosInfoList.end()) 
			{
				minLosBetweenObserverAndObserved			= std::min(minLosBetweenObserverAndObserved, (*it).losToPotentialLocations);
				maxLosBetweenObserverAndObserved			= std::max(maxLosBetweenObserverAndObserved, (*it).losToPotentialLocations);
				
				minMinimumLosDistance						= std::min(minMinimumLosDistance, (*it).minimumLosDistance);
				maxMinimumLosDistance						= std::max(maxMinimumLosDistance, (*it).minimumLosDistance);
				
				minMaximumLosDistance						= std::min(minMaximumLosDistance, (*it).maximumLosDistance);
				maxMaximumLosDistance						= std::max(maxMaximumLosDistance, (*it).maximumLosDistance);
				
				minClosestObstacleDistance					= std::min(minClosestObstacleDistance, (*it).closestObstacleDistance);
				maxClosestObstacleDistance					= std::max(maxClosestObstacleDistance, (*it).closestObstacleDistance);
				
				it++;
			}
			
			//	Compute the ranges
			rangeLosBetweenObserverAndObserved				= maxLosBetweenObserverAndObserved - minLosBetweenObserverAndObserved;
			rangeMinimumLosDistance							= maxMinimumLosDistance - minMinimumLosDistance;
			rangeMaximumLosDistance							= maxMaximumLosDistance - minMaximumLosDistance;
			rangeClosestObstacleDistance					= maxClosestObstacleDistance - minClosestObstacleDistance;
				
			//	Ranking every element in the list according to percentage of minimum and maximum values, and calculate the percentage with respect to maximum
			it	= observerLosInfoList.begin();
			while (it != observerLosInfoList.end()) 
			{
				(*it).ranking.losToPotentialLocations		= (0 == rangeLosBetweenObserverAndObserved) ? 100 : (((*it).losToPotentialLocations-minLosBetweenObserverAndObserved) * 100 / rangeLosBetweenObserverAndObserved);
				(*it).ranking.minimumLosDistance			= (0.0 == rangeMinimumLosDistance) ? 100 : (int) (((*it).minimumLosDistance-minMinimumLosDistance) * 100 / rangeMinimumLosDistance);
				(*it).ranking.maximumLosDistance			= (0.0 == rangeMaximumLosDistance) ? 100 : (int) (((*it).maximumLosDistance-minMaximumLosDistance) * 100 / rangeMaximumLosDistance);
				(*it).ranking.closestObstacleDistance		= (0.0 == rangeClosestObstacleDistance) ? 100 : (int) (((*it).closestObstacleDistance-minClosestObstacleDistance) * 100 / rangeClosestObstacleDistance);
				
				it++;
			}

		}	//	SwissArmyKnife::Ranking()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: RankingOrder
		// Function				: Ranking
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function order the list of locations
		//							according to various parameters for criteria
		// Remarks				: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: LOS info list of locations
		//							relative importance of more LOS locations to observed
		//							relative importance of minimum distance to observed
		//							relative importance of maximum distance to observed
		//							relative importance of distance to obstacle	
		//					Default arguments:
		//							better more LOS locations to observed
		//							better closest minimum distance to observed
		//							better closest maximum distance to observed
		//							better closest distance to obstacle
		//
		/////////////////////////////////////////////////////////////////////////////////
		void SwissArmyKnife::RankingOrder(list <AI_SUPPORT_ALGORITHMS_losInfo>& observerLosInfoList,
						unsigned short relativeImportanceMoreLosLocations,
						unsigned short relativeImportanceClosestMinimumDistanceToObserved,
						unsigned short relativeImportanceClosestMaximumDistanceToObserved,
						unsigned short relativeImportanceClosestDistanceToObstacle,
						bool betterMoreLosLocations,
						bool betterClosestMinimumDistanceToObserved,
						bool betterClosestMaximumDistanceToObserved,
						bool betterClosestDistanceToObstacle
		)
		{
			unsigned int	relativeImportanceSum;
			
			//	Calculate the sum of the relative importances
			relativeImportanceSum							= relativeImportanceMoreLosLocations + relativeImportanceClosestMinimumDistanceToObserved 
															+ relativeImportanceClosestMaximumDistanceToObserved + relativeImportanceClosestDistanceToObstacle;
															
			//	Calculate the importance of the specific element according to criteria
			std::list<AI_SUPPORT_ALGORITHMS_losInfo>::iterator it	= observerLosInfoList.begin();
			while (it != observerLosInfoList.end()) 
			{
				if (!betterMoreLosLocations)
					(*it).ranking.losToPotentialLocations	= 100 - (*it).ranking.losToPotentialLocations;
				if (betterClosestMinimumDistanceToObserved)
					(*it).ranking.minimumLosDistance		= 100 - (*it).ranking.minimumLosDistance;
				if (betterClosestMaximumDistanceToObserved)
					(*it).ranking.maximumLosDistance		= 100 - (*it).ranking.maximumLosDistance;
				if (betterClosestDistanceToObstacle)
					(*it).ranking.closestObstacleDistance	= 100 - (*it).ranking.closestObstacleDistance;
					
				(*it).importance							= ((((*it).ranking.losToPotentialLocations * relativeImportanceMoreLosLocations) +
																((*it).ranking.minimumLosDistance * relativeImportanceClosestMinimumDistanceToObserved) +
																((*it).ranking.maximumLosDistance * relativeImportanceClosestMaximumDistanceToObserved) +
																((*it).ranking.closestObstacleDistance * relativeImportanceClosestDistanceToObstacle)) / relativeImportanceSum);

				it++;
			}
			
			//	Sort by better ranking
			observerLosInfoList.sort(_CompareRanking);

		}	//	SwissArmyKnife::RankingOrder()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: SwissArmyKnife
		// Function				: Obstacles2Csv
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 10-03-2021
		// Class description	: This class implements many tools that will help us with
		//							the decision in the high-level algorithmm
		// Function description	: This public member function creates a .csv file with
		//							the information of all the obstacles in the DSM map
		// Remarks				: In the future we need to care about possible failures,
		//							and return false in that case
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: DSM map info, and .csv file name
		//
		/////////////////////////////////////////////////////////////////////////////////
		bool SwissArmyKnife::Obstacles2Csv(DsmInformation &dsmMapInfo, string csvObstaclesFilename)
		{
			int	column,  row;
			
			//	Create the .csv DSM map obstacles file
			std::ofstream csvObstaclesFile;
			csvObstaclesFile.open (csvObstaclesFilename);
			//	Create the header
			csvObstaclesFile << "Column, Row, Elevation\n";
			
			for (row = 0; row < dsmMapInfo.Rows(); row++)
			{
				for (column = 0; column < dsmMapInfo.Columns(); column++)
				{
					if (dsmMapInfo.Obstacle(column, row))
					{
						csvObstaclesFile << column << "," << row << "," << dsmMapInfo.Elevation(column, row) << endl;
					}
					
				}
			}
			
			//	Close the .csv DSM map obstacles file
			csvObstaclesFile.close();
			
			return true;
			
		}	//	SwissArmyKnife::Obstacles2Csv()

	/*
		****************************************************************************
		* PUBLIC CLASS OPERATOR DEFINITIONS
		****************************************************************************
	*/

	/*
		****************************************************************************
		* PRIVATE CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/	
	
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Astar
		// Function				: _Init
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 07-03-2021
		// Class description	: This class implements the A* algorithm
		// Function description	: This private member function initiates the object and
		//							will be used by the constructors
		// Remarks				:
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		void Astar::_Init(void) 
		{ 
			this->initialized							= false;
			this->csvSource2DestinationPathFilename		= "";
			dsmInformation								= nullptr;
			
		}	//	Astar::_Init() 

