//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiSupportClasses.h
//
// Version:			01.01
//
// Description:		Support classes for the AI home excercise include file
//
// Author:			Pablo Daniel Jelsky <PabloDanielJelsky@Gmail.com>
//
// Copyright:		
//
//	DEVELOPMENT HISTORY:
//
// Remarks:			
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	24-02-2021	Pablo Daniel Jelsky		01			00			Initial
//	27-02-2021	Pablo Daniel Jelsky		01			01			Working with Logger, Location, DsmLocation and DsmInformation classes
//	01-03-2021	Pablo Daniel Jelsky		01			02			Added LineOfSight() member function to DsmInformation class and added template use
//	02-03-2021	Pablo Daniel Jelsky		01			03			Added Graphic class
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __AI_SUPPORT_CLASSES_H__
#define	__AI_SUPPORT_CLASSES_H__

	/*
		****************************************************************************
		* INCLUDE FILES
		****************************************************************************
	*/
		/*---- system and platform files -------------------------------------------*/
		#include <string>
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "AiSupportClasses_Ifc.h"
	
	/*
		****************************************************************************
		* INTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/		
		/*---- data declarations ---------------------------------------------------*/
		/*---- function prototypes -------------------------------------------------*/
	
	/*
		****************************************************************************
		* PRIVATE DECLARATIONS  
		****************************************************************************
	*/	
		/*---- context -------------------------------------------------------------*/
		/*---- macros --------------------------------------------------------------*/
		/*---- defines --------------------------------------------------------------*/
		#define	DEFAULT_DSM_INFORMATION_FILE_NAME		"output/DsmInformation.txt"
		#define	MAXIMUM_COLOR							255
		#define	HALF_COLOR								128
		#define	NO_COLOR								0
		#define	CONVERSION_FROM_8_BIT_TO_16_BIT_COLOR	257
		#define	PNG_COLUMN_OFFSET_FROM_DSM_MAP			1	// DSM map starts at (0,0) whereas .png file in (1,1)
		#define	PNG_ROW_OFFSET_FROM_DSM_MAP				1	// DSM map starts at (0,0) whereas .png file in (1,1)
		/*---- data declarations ---------------------------------------------------*/
		typedef struct
		{
			int	red;
			int	green;
			int	blue;
			
		}	rgb;
			
		/*---- function prototypes -------------------------------------------------*/	

	

#endif	// __AI_SUPPORT_CLASSES_H__
