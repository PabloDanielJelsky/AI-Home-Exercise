//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloSupportAlgorithms.h
//
// Version:			01.00
//
// Description:		Support algorithms for the AI home excercise interface file
//
// Author:			Pablo Daniel Jelsky
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

#ifndef __PABLO_AI_SUPPORT_ALGORITHMS_H__
#define	__PABLO_AI_SUPPORT_ALGORITHMS_H__

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
		#include <list>		// for lists
		/*---- program files -------------------------------------------------------*/
		#include "PabloSupportClasses.h"
	
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;		
		/*---- data declarations ---------------------------------------------------*/
		/*---- function prototypes -------------------------------------------------*/
		long AStarSearch(DsmInformation& dsmInformation, DsmLocation sourceLocation, DsmLocation destinationLocation, Location* pTargetPath, list <Location>& targetPathList);
	
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
		#define	FAIL	-1
		#define	FLT_MAX	99999999999
		/*---- data declarations ---------------------------------------------------*/	
		typedef enum {DIRECTION_NORTH, DIRECTION_SOUTH, DIRECTION_EAST, DIRECTION_WEST } directionEnumerator;

		// Creating a shortcut for pair<int, pair<int, int>> type
		typedef pair <double, pair<int, int> > pPair;
		
		// A structure to hold the neccesary parameters for A* algorithm
		struct cell
		{
			DsmLocation	location;
			Location	parentLocation;
			
			// f = g + h
			double 		f, g, h;
						
		};	//	struct cell

		
		/*---- function prototypes -------------------------------------------------*/	
		bool _IsValid(DsmInformation& dsmInformation, DsmLocation location);
		bool _IsUnblocked(DsmInformation& dsmInformation, DsmLocation location);
		bool _IsDestination(DsmLocation currentLocation, DsmLocation destinationLocation);
		double _CalculateHValueForAiHomeExercise(DsmLocation currentLocation, DsmLocation destinationLocation);
		void _TracePath(DsmInformation& dsmInformation, cell *pCellDetails, Location destinationLocation, Location* pTargetPath, int *pTargetPathSize, list <Location>& targetPathList);


	

#endif	// __PABLO_AI_SUPPORT_ALGORITHMS_H__
