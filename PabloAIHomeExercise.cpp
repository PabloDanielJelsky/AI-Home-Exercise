//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			PabloAiHomeExercise.c
//
// Version:			01.00
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
/*
//	locationDsm				targetInitialLocation, targetLocation, targetObjectiveLocation, targetNextLocation;
	const int				groundLevel = 3300;
	long int				simulationSeconds = 0;
	double					mTargetToObjectiveSlope;
	double					bTargetToObjectiveYCoordinatateWhileXIsZero;
	int						visibilityInMeterstemporalLocation = 5;

	
    class DsmInformation    DsmInformationObject;
    
	long					targetPathSize, agent1PathSize, agent2PathSize;
	list <Location> 		targetPathList, agent1PathList, agent2PathList;
    class Location			targetInitialLocation(0,0), targetObjectiveLocation(200, 200), targetLocation;
    class Location			agent1InitialLocation(10,0), agent1ObjectiveLocation(200, 200), agent1Location;
     
    //  GDAL driver initialization
    GdalDriverInitialization();
    
    // 	Analyze the input DSM file
    DsmInputFileAnalyze(DSM_FILE, DsmInformationObject);
    
    //	Create the output file
    DsmOutputFileCreation(OUT_FILE, DsmInformationObject);
   
 
    //	Set initial target and target objective locations
	targetLocation	= targetInitialLocation;
	targetPathSize	= AStarSearch(A_START_SEARCH_4_PIXELS_MOVEMENT, false, DsmInformationObject, targetInitialLocation, targetObjectiveLocation, targetPathList, "output/TargetPath.csv");
	list <Location>::iterator it = targetPathList.begin();
	
	simulationSeconds	= 0;
	while (targetLocation != targetObjectiveLocation)
    {
    	targetLocation.Modify((*it).Column(), (*it).Row());
 //    	cout << "[" << targetLocation.Column() << ", " << targetLocation.Row() << ", " << simulationSeconds << "]";
   
   		simulationSeconds++;
    	++it;	
//    	if (it != targetPathList.end())
//    		cout << " => ";
    }	


    //	Create the output file with target path
    DsmOutputFileCreationWithPath(PERSON_TYPE_TARGET, TARGET_PATH_FILE, DsmInformationObject, targetPathList, targetPathSize);

    //	Set initial target and target objective locations
	agent1Location	= agent1InitialLocation;
	agent1PathSize = AStarSearch(A_START_SEARCH_12_PIXELS_MOVEMENT, true, DsmInformationObject, agent1InitialLocation, agent1ObjectiveLocation, agent1PathList, "output/Agent1Path.csv");
	list <Location>::iterator it1 = agent1PathList.begin();
	
	simulationSeconds	= 0;
	while (agent1Location != agent1ObjectiveLocation)
    {
    	agent1Location.Modify((*it1).Column(), (*it1).Row());
 //    	cout << "[" << targetLocation.Column() << ", " << targetLocation.Row() << ", " << simulationSeconds << "]";
   
   		simulationSeconds++;
    	++it1;	
//    	if (it != targetPathList.end())
//    		cout << " => ";
    }	
    
    //	Create the output file with target path
    DsmOutputFileCreationWithPath(PERSON_TYPE_AGENT1, AGENT1_PATH_FILE, DsmInformationObject, agent1PathList, agent1PathSize);
 */   
    Location pointA(0,0);
    Location pointB(10,10);
    Location pointC(0,0);
    Location pointD(150,150);
    Location pointE(200,200);
    Location text(3,3);
    
 /*
    if (DsmInformationObject.LineOfSight(pointA, pointB) == true)
    	cout << "true\n";
    else
    	cout << "false\n";
    	
    if (DsmInformationObject.LineOfSight(pointC, pointD) == true)
    	cout << "true\n";
    else
    	cout << "false\n";
 */
   
   class Model	model(DSM_FILE, "Agent1");
   model.CurrentLocation(pointA);
   model.DestinationLocation(pointE);
   int modelPathLength = model.FindPath(A_START_SEARCH_4_PIXELS_MOVEMENT, false, "output/ModelPath.csv");
   cout << "Model path length = " << modelPathLength << "\n";
   model.GraphicOpen("output/Model", "Model graphic");
   model.GraphicPreparation(true);
   model.GraphicText(text, "Original cage6.tif");
   model.GraphicClose(GRAPHIC_TYPE_PNG);
   model.GraphicClose(GRAPHIC_TYPE_GEOTIFF);
   
	long int	simulationSeconds = 0;
  
	while (model.CurrentLocation() != model.DestinationLocation())
    {
		Location	currentLocation;
		currentLocation	= model.NextLocation();
		simulationSeconds++;
		cout << "[" << currentLocation.Column() << ", " << currentLocation.Row() << ", " << simulationSeconds << "]\n"; 
    }	
  
	return EXIT_SUCCESS;
	
}	//	main()


