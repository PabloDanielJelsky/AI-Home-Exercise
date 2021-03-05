//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportAlgorithms.c
//
// Version:			01.00
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
		// Last update date		: 27-02-2021
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
		long AStarSearch(aStarSearchPixelsMovementType typeOfPixelMovement, bool possibilityOfNotMoving, 
							DsmInformation& dsmInformation, Location sourceLocation, 
							Location destinationLocation, list <Location>& targetPathList, 
							string csvTargetPathFilename)
		{
			int	targetPathSize					= 0;
			int	dsmQuantityOfColumns			= dsmInformation.Columns();
			int	dsmQuantityOfRows				= dsmInformation.Columns();
			
			//	To store the first enumerator, and the last one, depending in the quantity of pixels per each movement
			directionEnumerator	directionFirst	= (true == possibilityOfNotMoving) ? DIRECTION_SAME_PLACE : DIRECTION_NORTH;
			directionEnumerator directionLast;
			
			// If the source is out of range
			if (false == _IsValid(dsmInformation, sourceLocation)) 
			{
				printf("Source is invalid\n");
				return FAIL ;
			}
		 
			// If the destination is out of range
			if (false == _IsValid(dsmInformation, destinationLocation)) 
			{
				printf("Destination is invalid\n");
				return FAIL ;
			}
		 
			// Either the source or the destination is blocked
			if (false == _IsUnblocked(dsmInformation, sourceLocation) || false == _IsUnblocked(dsmInformation, destinationLocation)) 
			{
				printf("Source or the destination is not in 'ground' level\n");
				return FAIL;
			}
		 
			// If the destination cell is the same as source cell
			if (true == _IsDestination(sourceLocation, destinationLocation)) 
			{
				printf("We are already at the destination\n");
				return FAIL;
			}
			
			switch (typeOfPixelMovement)
			{
				case A_START_SEARCH_4_PIXELS_MOVEMENT:
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
							N -->  North			(column, row-1)
							S -->  South			(column, row+1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
					*/	
					
					//	Implying exactly moving 1 pixel each time
					directionLast	= DIRECTION_WEST;
					break;
				case A_START_SEARCH_8_PIXELS_MOVEMENT:	
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
							N -->  North			(column, row-1)
							S -->  South			(column, row+1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row-1)
							N.W--> North-West  		(column-1, row-1)
							S.E--> South-East  		(column+1, row+1)
							S.W--> South-West  		(column-1, row+1)
					*/	
					//	Implying moving to all adjacent pixels each time
					directionLast	= DIRECTION_SOUTH_WEST;
					break;
				case A_START_SEARCH_12_PIXELS_MOVEMENT:
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
							N -->  North			(column, row-1)
							S -->  South			(column, row+1)
							E -->  East				(column+1, row)
							W -->  West				(column-1, row)
							N.E--> North-East  		(column+1, row-1)
							N.W--> North-West  		(column-1, row-1)
							S.E--> South-East  		(column+1, row+1)
							S.W--> South-West  		(column-1, row+1)
							N.N--> North-North		(column, row-2)
							S.S--> South-South		(column, row+2)
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
			memset(pClosedList, false, *pClosedList);
		 
			// Declare a 2D array of structure to hold the details of that cell
			cell *pCellDetails	= new cell[dsmQuantityOfColumns * dsmQuantityOfRows];
		 
			int row, column;
			
			//	Create the .csv target path file
			std::ofstream csvTargetPathFile;
      		csvTargetPathFile.open (csvTargetPathFilename);
      		//	Create the header
      		csvTargetPathFile << "Column, Row, Step\n";
		 
			for (row = 0; row < dsmQuantityOfRows; row++) 
			{
				for (column = 0; column < dsmQuantityOfColumns; column++) 
				{
				    pCellDetails[row * dsmQuantityOfColumns + column].f		= FLT_MAX;
				    pCellDetails[row * dsmQuantityOfColumns + column].g		= FLT_MAX;
				    pCellDetails[row * dsmQuantityOfColumns + column].h		= FLT_MAX;
				    pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Modify(AI_SUPPORT_CLASSES_INVALID_COLUMN, AI_SUPPORT_CLASSES_INVALID_ROW);
				}
			}
		 
			// Initialising the parameters of the starting node
			row = sourceLocation.Row(), column = sourceLocation.Column();
			pCellDetails[row * dsmQuantityOfColumns + column].f				= 0.0;
			pCellDetails[row * dsmQuantityOfColumns + column].g				= 0.0;
			pCellDetails[row * dsmQuantityOfColumns + column].h				= 0.0;
			pCellDetails[row * dsmQuantityOfColumns + column].parentLocation.Modify(column, row);
		 
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
		 
			while (!openList.empty()) 
			{
				pPair p = *openList.begin();
		 
				// Remove this vertex from the open list
				openList.erase(openList.begin());
		 
				// Add this vertex to the closed list
				column												= p.second.first;
				row													= p.second.second;
				pClosedList[row * dsmQuantityOfColumns + column]	= true;
		 
		 
				// To store the 'g', 'h' and 'f' of the 8 successors
				double 				gNew, hNew, fNew;
				
				for (int direction = (int) directionFirst; direction <= (int) directionLast; direction++)
				{		
					DsmLocation temporalDsmLocation;
					
					switch (direction)
					{
						case DIRECTION_SAME_PLACE:
							// Stay at the same place, do NOT do anything
							temporalDsmLocation.Modify(column, row);
							break;
						case DIRECTION_NORTH:
							//----------- 1st Successor (North) ------------
							temporalDsmLocation.Modify(column, row - 1);
							break;
						case DIRECTION_SOUTH:
							//----------- 2nd Successor (South) ------------
							temporalDsmLocation.Modify(column, row + 1);
							break;
						case DIRECTION_EAST:
							//----------- 3rd Successor (East) ------------
							temporalDsmLocation.Modify(column + 1, row);
							break;
						case DIRECTION_WEST:
							//----------- 4th Successor (West) ------------
							temporalDsmLocation.Modify(column - 1, row);
							break;
						case DIRECTION_NORTH_EAST:
							//----------- 5th Successor (North-East) ------------
							temporalDsmLocation.Modify(column + 1, row - 1);
							break;
						case DIRECTION_NORTH_WEST:
							//----------- 6th Successor (North-West) ------------
							temporalDsmLocation.Modify(column - 1, row - 1);
							break;
						case DIRECTION_SOUTH_EAST:
							//----------- 7th Successor (South-East) ------------
							temporalDsmLocation.Modify(column + 1, row + 1);
							break;
						case DIRECTION_SOUTH_WEST:
							//----------- 8th Successor (South-West) ------------
							temporalDsmLocation.Modify(column - 1, row + 1);
							break;
						case DIRECTION_NORTH_NORTH:
							//----------- 9th Successor (North-North) ------------
							temporalDsmLocation.Modify(column, row - 2);
							break;
						case DIRECTION_SOUTH_SOUTH:
							//----------- 10th Successor (South-South) ------------
							temporalDsmLocation.Modify(column, row + 2);
							break;
						case DIRECTION_EAST_EAST:
							//----------- 11th Successor (East-East) ------------
							temporalDsmLocation.Modify(column + 2, row);
							break;
						case DIRECTION_WEST_WEST:
							//----------- 12th Successor (West-West) ------------
							temporalDsmLocation.Modify(column - 2, row);
							break;
						default:
							printf("The direction %d is not a valid one\n", direction);
							csvTargetPathFile.close();
							return FAIL;
							
					}	//	switch()
					
					// Only process this cell if this is a valid one
					if (_IsValid(dsmInformation, temporalDsmLocation)) 
					{
						// If the destination cell is the same as the
						// current successor
						if (_IsDestination(temporalDsmLocation, destinationLocation)) 
						{
							// Set the Parent of the destination cell
							pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].parentLocation.Modify(column, row);
							printf("The destination cell is found\n");
							_TracePath(dsmInformation, pCellDetails, destinationLocation, &targetPathSize, targetPathList, csvTargetPathFile);
							foundDest	= true;
							
							//	Deallocate the dynamic arrays created in this function
							delete [] pClosedList;
							delete [] pCellDetails;
							
							csvTargetPathFile.close();
							return (targetPathSize);
						}
						// If the successor is already on the closed
						// list or if it is blocked, then ignore it.
						// Else do the following
						else if (false == pClosedList[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()]
								 && true == _IsUnblocked(dsmInformation, temporalDsmLocation)) 
						{
							gNew	= pCellDetails[row * dsmQuantityOfColumns + column].g + 1.0;
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
							if (pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].f == FLT_MAX
								|| pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].f > fNew) 
							{
								openList.insert(make_pair(fNew, make_pair(temporalDsmLocation.Column(), temporalDsmLocation.Row())));
			 
								// Update the details of this cell
								pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].f	= fNew;
								pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].g = gNew;
								pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].h = hNew;
								pCellDetails[temporalDsmLocation.Row() * dsmQuantityOfColumns + temporalDsmLocation.Column()].parentLocation.Modify(column, row);
							}
						}
					}
				}
			}

			// When the destination cell is not found and the open
			// list is empty, then we conclude that we failed to
			// reach the destination cell. This may happen when 
			// there is no way to destination cell (due to
			// blockages)
			if (false == foundDest)
				printf("Failed to find the Destination Cell\n");
				
			//	Deallocate the dynamic arrays created in this function
			delete [] pClosedList;
			delete [] pCellDetails;
		 
		 	csvTargetPathFile.close();
			return (targetPathSize);
		}

	
	/*
		****************************************************************************
		* PRIVATE FUNCTION DEFINITIONS
		****************************************************************************
	*/	
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
			return ((true == dsmInformation.Obstacle(location.Column(), location.Row())) ? false : true);
			
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
				Location p		= Path.top();
				Path.pop();

				targetPathSize++;
				*pTargetPathSize	= targetPathSize;
				csvTargetPathFile << p.Column() << "," << p.Row() << "," << targetPathSize << "\n";
				targetPathList.push_back(p);
			}
 
			return;

		}	//	_TracePath()


	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/

	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/


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

