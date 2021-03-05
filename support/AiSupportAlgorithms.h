//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportAlgorithms.h
//
// Version:			01.01
//
// Description:		Support algorithms for the AI home excercise include file
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
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __AI_SUPPORT_ALGORITHMS_H__
#define	__AI_SUPPORT_ALGORITHMS_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <cstdlib>	// for abs() and realloc()
		#include <stack>	// for stacks
		#include <utility>	// for pairs
		#include <set>		// for sets
		#include <cstring>	// for memset
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "AiSupportAlgorithms_Ifc.h"
		#include "AiSupportClasses.h"
	
	/*
		****************************************************************************
		* INTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;		
		
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
		#define	FLT_MAX	99999999999
		/*---- data declarations ---------------------------------------------------*/
		typedef enum {DIRECTION_SAME_PLACE, 
						DIRECTION_NORTH, DIRECTION_SOUTH, DIRECTION_EAST, DIRECTION_WEST,
						DIRECTION_NORTH_EAST, DIRECTION_NORTH_WEST, DIRECTION_SOUTH_EAST, DIRECTION_SOUTH_WEST,
						DIRECTION_NORTH_NORTH, DIRECTION_SOUTH_SOUTH, DIRECTION_EAST_EAST, DIRECTION_WEST_WEST
					} directionEnumerator;

		// Creating a shortcut for pair<double, pair<int, int>> type
		typedef pair <double, pair<int, int> > pPair;
		
		// A structure to hold the neccesary parameters for A* algorithm
		struct cell
		{
			Location	parentLocation;
			
			// f = g + h
			double 		f, g, h;
						
		};	//	struct cell

		
		/*---- function prototypes -------------------------------------------------*/	
		bool _IsValid(DsmInformation& dsmInformation, Location location);
		bool _IsUnblocked(DsmInformation& dsmInformation, Location location);
		bool _IsDestination(Location currentLocation, Location destinationLocation);
		double _CalculateHValueForAiHomeExercise(Location currentLocation, Location destinationLocation);
		void _TracePath(DsmInformation& dsmInformation, cell *pCellDetails, Location destinationLocation, int *pTargetPathSize, list <Location>& targetPathList, std::ofstream& csvTargetPathFile);
	

#endif	// __AI_SUPPORT_ALGORITHMS_H__
