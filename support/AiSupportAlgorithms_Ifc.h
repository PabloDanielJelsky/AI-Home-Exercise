//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportAlgorithms_Ifc.h
//
// Version:			01.00
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
//	27-02-2021	Pablo Daniel Jelsky		01			00			Initial
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
		typedef enum { A_START_SEARCH_4_PIXELS_MOVEMENT, A_START_SEARCH_8_PIXELS_MOVEMENT, A_START_SEARCH_12_PIXELS_MOVEMENT } aStarSearchPixelsMovementType;
		/*---- data declarations ---------------------------------------------------*/
		/*---- function prototypes -------------------------------------------------*/
		long AStarSearch(aStarSearchPixelsMovementType typeOfPixelMovement, bool possibilityOfNotMoving, DsmInformation& dsmInformation, 
						Location sourceLocation, Location destinationLocation, list <Location>& targetPathList, string csvTargetPathFilename);
	
	/*
		****************************************************************************
		* PUBLIC DECLARATIONS 
		****************************************************************************
	*/
		/*---- data declarations ---------------------------------------------------*/
	
#endif	// __AI_SUPPORT_ALGORITHMS_IFC_H__
