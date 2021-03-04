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
// Author:			Pablo Daniel Jelsky
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
		static void GdalDriverInitialization(void);
		static void DsmInputFileAnalyze(char *pszFilename, class DsmInformation &DsmInformationObject);
		static void DsmOutputFileCreation(char *pszFilename, class DsmInformation &DsmInformationObject);
		static void DsmOutputFileCreationWithPath(personType typeOfPerson, char *pszFilename, class DsmInformation &DsmInformationObject, list <Location>& pathList, int pathSize);


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

	//	The Geospatial Data Abstraction Library (GDAL) is a computer software library for reading and writing raster and vector geospatial data formats
	//	The following function performs the driver initialization
	static void GdalDriverInitialization(void)
	{
		//  Register all the GDAL drivers
		GDALAllRegister();
		
		LoggerObject.WriteLine("The following format drivers are configured and support output:");
		
		for(int iDriverFormat = 0; iDriverFormat < GDALGetDriverCount(); iDriverFormat++)
		{
			string		loggerString;
		    GDALDriverH hDriver = GDALGetDriver(iDriverFormat);

		    if( GDALGetMetadataItem( hDriver, GDAL_DCAP_RASTER, nullptr) != nullptr &&
		        (GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATE, nullptr ) != nullptr
		        || GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATECOPY, nullptr ) != nullptr) )
		    {
		    	loggerString	= "\t" + (string) GDALGetDriverShortName(hDriver) + ":  " + (string) GDALGetDriverLongName(hDriver) + "\n";
		    	LoggerObject << loggerString;
		    }
		}
		   
	}   // GdalDriverInitialization()

	static void DsmInputFileAnalyze(char *pszFilename, class DsmInformation &DsmInformationObject)
	{
		GDALDataset  *poDataset;
		  
		//  Opening the File        
		poDataset = (GDALDataset *) GDALOpen(pszFilename, GA_ReadOnly);
		if (NULL == poDataset)
		{
		    LoggerObject << pszFilename << " file could not be opened...\n";
		}
		else
		{
		    LoggerObject << (string) pszFilename << " file was successfully opened...\n";

		    //  Getting Dataset Information
		    double        adfGeoTransform[6];
		    
		    LoggerObject << "Driver: " << poDataset->GetDriver()->GetDescription() << "/" <<  poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME) << "\n";
		    LoggerObject << "DSM file size is: " << poDataset->GetRasterXSize() << " columns by " << poDataset->GetRasterYSize() << " rows by " << poDataset->GetRasterCount() << " pixel" << "\n";
		    
		    DsmInformationObject.Rows(poDataset->GetRasterYSize());
		    DsmInformationObject.Columns(poDataset->GetRasterXSize());

		    {     	
			    //  Fetching a Raster Band
			    GDALRasterBand  *poBand;
			    int             nBlockXSize, nBlockYSize;
			    int             bGotMin, bGotMax;
			    double          adfMinMax[2];
			    poBand = poDataset->GetRasterBand( 1 );
			    poBand->GetBlockSize( &nBlockXSize, &nBlockYSize );
			    printf( "Block=%dx%d Type=%s, ColorInterp=%s\n",
			            nBlockXSize, nBlockYSize,
			            GDALGetDataTypeName(poBand->GetRasterDataType()),
			            GDALGetColorInterpretationName(
			                poBand->GetColorInterpretation()) );
			    adfMinMax[0] = poBand->GetMinimum( &bGotMin );
			    adfMinMax[1] = poBand->GetMaximum( &bGotMax );
			    if( ! (bGotMin && bGotMax) )
			        GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
			       LoggerObject << "Minimum = " << adfMinMax[0] << ", maximum = " << adfMinMax[1] << "\n";
	//            printf( "Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1] );
			    if( poBand->GetOverviewCount() > 0 )
			    	LoggerObject << "Band has " << poBand->GetOverviewCount() << " overviews.\n";
	//                printf( "Band has %d overviews.\n", poBand->GetOverviewCount() );
			    if( poBand->GetColorTable() != NULL )
			    	LoggerObject << "Band has a color table with " << poBand->GetColorTable()->GetColorEntryCount() << " entries.\n";
	//                printf( "Band has a color table with %d entries.\n",
	//                        poBand->GetColorTable()->GetColorEntryCount() );
			    

			    //  Reading Raster Data
			    //  Reading Raster Data
			    //  Reading Raster Data
			    float *pafScanline;
			    int   nXSize = poBand->GetXSize();
			    int	  nYSize = poBand->GetYSize();
	//	        pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize);
				pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize*nYSize);

			    
				LoggerObject << "nXSize = " << nXSize << "\n";
		  

			    poBand->RasterIO( GF_Read, 0, 0, nXSize, nYSize,
			                    pafScanline, nXSize, nYSize, GDT_Float32,
			                    0, 0 );        	        
			    
	//	        poBand->RasterIO( GF_Read, 0, 0, nXSize, 1,
	//	                        pafScanline, nXSize, 1, GDT_Float32,
	//	                        0, 0 );        
	 //           printf ("First cell = %d\n", pafScanline[0];
	 //           std::cout << "First cell elevation = " << pafScanline[0] << "\n\n";
	 			LoggerObject << "First cell elevation = " << pafScanline[0] << "\n";
	 			
	 			{
	 				int	column, row;
	 				
	 				for (row = 0; row < nYSize; row++)
	 					for (column = 0; column < nXSize; column++)
	 						DsmInformationObject.Elevation(column, row, pafScanline[row * nXSize + column]);
	 			
	 			}
			    
			     CPLFree(pafScanline);
		    }
		}
		
	}   //  DsmInputFileAnalyze()

	static void DsmOutputFileCreation(char *pszFilename, class DsmInformation &DsmInformationObject)
	{
		int	rows, columns;
		int	row, column;
		int	fontSize	= 12;
		
		rows	= DsmInformationObject.Rows();
		columns	= DsmInformationObject.Columns();

	  /* one.png
		* This will be a 300x300 image with a black background, called one.png
		* */	
		pngwriter outputFile(columns, rows, 0, pszFilename);
		
		for (row = 0; row < rows; row++)
			for (column = 0; column < columns; column++)
			{
				switch ((int) DsmInformationObject.Elevation(column, row))
				{
					case 3300:
						LoggerObject << "[" << column << "," << row << "] = 3300\n";
						outputFile.plot(column+1, rows - (row+1), 0, 0, 0); 
						DsmInformationObject.Obstacle(column, row, false);
						break;
					case 3325:
						LoggerObject << "[" << column << "," << row << "] = 3325\n";
						outputFile.plot(column+1, rows - (row+1), 65535, 0, 0); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					case 3335:
						LoggerObject << "[" << column << "," << row << "] = 3335\n";
						outputFile.plot(column+1, rows - (row+1), 0, 65535, 0); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					case 3370:
						LoggerObject << "[" << column << "," << row << "] = 3370\n";
						outputFile.plot(column+1, rows - (row+1), 0, 0, 65535); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					default:
						LoggerObject << "[" << column << "," << row << "] = " << (int) DsmInformationObject.Elevation(column, row) << "\n";
				}
			}

	   /*Change the text information in the PNG header
		* */

	   outputFile.settext((const char *) pszFilename, (const char *) "Pablo Daniel Jelsky", (const char *) "Original 'cage6.tif' GTiff file converted to png", (const char *) "PabloAIHomeExercise");
	 /*
	 void settext(	const char * title, const char * author,

				const char * description, const char * software);
	 
	 */  
	   /* Set text */
	   //This is the text that says PNG in pink, rotated.
	   outputFile.plot_text_utf8("/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf", fontSize , 1, rows-(2*fontSize) , 0.0, "Original 'cage6.tif'", 65535 , 65535 , 65535);
	/*
	void plot_text_utf8_blend(char * face_path, int fontsize, 

						  int x_start, int y_start, double angle, char * text,

	 					  double opacity, 

						  int red, int green, int blue);
	*/




	   LoggerObject << "Finished creating " << (string) pszFilename << " file...\n";

	   outputFile.close();

	}	//	DsmOutputFileCreation()

	static void DsmOutputFileCreationWithPath(personType typeOfPerson, char *pszFilename, class DsmInformation &DsmInformationObject, list <Location>& pathList, int pathSize)
	{
		int	rows, columns;
		int	row, column;
		int	fontSize	= 12;
		int	targetStep;
		int xfrom, yfrom, xto, yto;
		int	redLine, greenLine, blueLine;
		
		switch (typeOfPerson)
		{
			case PERSON_TYPE_TARGET:
				redLine		= 0;
				greenLine	= 65535;
				blueLine	= 65535;
				break;
			case PERSON_TYPE_AGENT1:
				redLine		= 65535;
				greenLine	= 0;
				blueLine	= 65535;
				break;
			case PERSON_TYPE_AGENT2:
				redLine		= 65535;
				greenLine	= 65535;
				blueLine	= 0;
				break;
			default:
				redLine		= 65535;
				greenLine	= 65535;
				blueLine	= 65535;
		}
		Location	locationTemporal;
		
		rows	= DsmInformationObject.Rows();
		columns	= DsmInformationObject.Columns();

	  /* one.png
		* This will be a 300x300 image with a black background, called one.png
		* */	
		pngwriter outputFile(columns, rows, 0, pszFilename);
		
		for (row = 0; row < rows; row++)
			for (column = 0; column < columns; column++)
			{
				switch ((int) DsmInformationObject.Elevation(column, row))
				{
					case 3300:
						LoggerObject << "[" << column << "," << row << "] = 3300\n";
						outputFile.plot(column+1, rows - (row+1), 0, 0, 0); 
						DsmInformationObject.Obstacle(column, row, false);
						break;
					case 3325:
						LoggerObject << "[" << column << "," << row << "] = 3325\n";
						outputFile.plot(column+1, rows - (row+1), 65535, 0, 0); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					case 3335:
						LoggerObject << "[" << column << "," << row << "] = 3335\n";
						outputFile.plot(column+1, rows - (row+1), 0, 65535, 0); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					case 3370:
						LoggerObject << "[" << column << "," << row << "] = 3370\n";
						outputFile.plot(column+1, rows - (row+1), 0, 0, 65535); 
						DsmInformationObject.Obstacle(column, row, true);
						break;
					default:
						LoggerObject << "[" << column << "," << row << "] = " << (int) DsmInformationObject.Elevation(column, row) << "\n";
				}
			}
		
		locationTemporal	= pathList.front();
		pathList.pop_front();
		xfrom				= locationTemporal.Column()+1;
		yfrom				= rows - (locationTemporal.Row()+1);
		
		// void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int red, int green, int blue);
		
		//	outputFile.triangle(xfrom, yfrom, xfrom + 2, yfrom - 1, xfrom + 1, yfrom, 0, 65535, 4000);



		int loop = 0;
		for (list <Location>::iterator it = pathList.begin(); it != pathList.end(); ++it, loop++)
		{
			xto				= (*it).Column()+1;
			yto				= rows - ((*it).Row()+1);
				
			outputFile.line(xfrom, yfrom, xto, yto, redLine, greenLine, blueLine);
			
			xfrom			= xto;
			yfrom			= yto;	
			
			if (0 == loop)
			{
				//	void arrow( int x1,int y1,int x2,int y2,int size, double head_angle, int red, int green, int blue);
	//			outputFile.arrow(xfrom ,yfrom , xto, yto, 8, 0.0, 0, 65535, 4000);
			}	
			
		}
	//	outputFile.arrow(xfrom ,yfrom , xto, yto, 8, 0.0, 0, 65535, 4000);
		// void circle(int xcentre, int ycentre, int radius, int red, int green, int blue);
		//	outputFile.circle(xto, yto, 2, 0, 65535, 4000);
	/*
		for (targetStep = 0; targetStep < targetPathSize-1; targetStep++)
		{
			
			xfrom	= pTargetPath[targetStep].Column()+1;
			xto		= pTargetPath[targetStep+1].Column()+1;
			yfrom	= pTargetPath[targetStep].Row()+1;
			yto		= pTargetPath[targetStep+1].Row()+1;
			
			printf ("G%d, %d, %d ", xfrom, yfrom, targetStep);
					
			//	void line(int xfrom, int yfrom, int xto, int yto, int red, int green,int  blue);
			outputFile.line(xfrom, yfrom, xto, yto, 0, 65535, 4000);
		}
	*/

	   /*Change the text information in the PNG header
		* */

	   outputFile.settext((const char *) pszFilename, (const char *) "Pablo Daniel Jelsky", (const char *) "'cage6.tif' GTiff file with path", (const char *) "PabloAIHomeExercise");
	 /*
	 void settext(	const char * title, const char * author,

				const char * description, const char * software);
	 
	 */  
	   /* Set text */
	   //This is the text that says PNG in pink, rotated.
	   outputFile.plot_text_utf8("/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf", fontSize , 1, rows-(2*fontSize) , 0.0, "'cage6.tif' GTiff file with path'", 65535 , 65535 , 65535);
	/*
	void plot_text_utf8_blend(char * face_path, int fontsize, 

						  int x_start, int y_start, double angle, char * text,

	 					  double opacity, 

						  int red, int green, int blue);
	*/




	   LoggerObject << "Finished creating " << (string) pszFilename << " file...\n";

	   outputFile.close();

	}	//	DsmOutputFileCreationWithPath()


int main()
{
//	locationDsm				targetInitialLocation, targetLocation, targetObjectiveLocation, targetNextLocation;
	const int				groundLevel = 3300;
	long int				simulationSeconds = 0;
	double					mTargetToObjectiveSlope;
	double					bTargetToObjectiveYCoordinatateWhileXIsZero;
	int						visibilityInMeterstemporalLocation = 5;

	
    class DsmInformation    DsmInformationObject;
    
	long					targetPathSize, agent1PathSize, agent2PathSize;
	list <Location> 		targetPathList, agent1PathList, agent2PathList;
    class DsmLocation		targetInitialLocation(0,0), targetObjectiveLocation(200, 200), targetLocation;
    class DsmLocation		agent1InitialLocation(10,0), agent1ObjectiveLocation(200, 200), agent1Location;
     
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
    
    Location pointA(0,0);
    Location pointB(10,10);
    Location pointC(0,0);
    Location pointD(150,150);
    
    if (DsmInformationObject.LineOfSight(pointA, pointB) == true)
    	cout << "true\n";
    else
    	cout << "false\n";
    	
    if (DsmInformationObject.LineOfSight(pointC, pointD) == true)
    	cout << "true\n";
    else
    	cout << "false\n";
   
   class Model	model(DSM_FILE, "Agent1");
   model.GraphicCreation(GRAPHIC_TYPE_PNG, "test");
   model.GraphicCreation(GRAPHIC_TYPE_GEOTIFF, "test");
    	
    
	return EXIT_SUCCESS;
	
}	//	main()


