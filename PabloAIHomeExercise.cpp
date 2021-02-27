///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// 
// File:				HW_C64xx_Support.c
//
// Version:			SURF Release	1.06		27 FEB 2005
//
// Description:	HW Division TMS320C64xx General Support & HDIM Functions
//							Source File
//
// Author:			Pablo Daniel Jelsky
//
// Copyright:		(c) Copyright 2005		SURF Communication Solutions
//						All Rights Reserved.		Duplication Strictly Prohibited.
//
//	DEVELOPMENT HISTORY:
//
//	Date			Author					Release	Change Id	Description of change
//	----------- -------------------- -------- ----------- ---------------------
//	05-02-2002	Pablo Daniel Jelsky	1			00				Initial
//	13-05-2002	Pablo Daniel Jelsky	1			05				Added Interrupt Handling
//	27-02-2005	Pablo Daniel Jelsky	1			06				Added new Two Step paradigm
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/*
	****************************************************************************
	* INCLUDE FILES
	****************************************************************************
*/
	/*---- system and platform files -------------------------------------------*/
		/*---- system and platform files -------------------------------------------*/
		
		/*---- program files -------------------------------------------------------*/
			//	HW Division TMS320C64xx General Support & HDIM Functions Include File
			
			
	/*---- program files -------------------------------------------------------*/
//#define USE_PROFILER
/*
	****************************************************************************
	* EXTERNAL REFERENCE    
	****************************************************************************
*/
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
	/*---- data declarations ---------------------------------------------------*/
	/*---- function prototypes -------------------------------------------------*/
			
/*
	****************************************************************************
	* PUBLIC FUNCTION DEFINITIONS
	****************************************************************************
*/


/////////////////////////////////////////////////////////////////////////////////
// Function name   : HdimGetDMACounter
// Programmer name : Pablo Daniel Jelsky
// Last update date: February 06th, 2002
// Description     : This function returns the frame count / element count field
//								of the transmit EDMA.
// Return value    : None.
// Remarks         : 
/////////////////////////////////////////////////////////////////////////////////
// Arguments:			None.
/////////////////////////////////////////////////////////////////////////////////







	
	






/*
 * PabloAIHomeExercise.cpp - Target simulation home exercise for AI
 * Created: 2021-02-23
 * Author:  Pablo Daniel Jelsky <PabloDanielJelsky@gmail.com>
 */
 
 /**
 * @file PabloAIHomeExercise.cpp
 * @brief Target simulation home exercise for AI main function and high-level modules
 *
 * Trie is a kind of digital search tree, an efficient indexing method with
 * O(1) time complexity for searching. Comparably as efficient as hashing,
 * trie also provides flexibility on incremental matching and key spelling
 * manipulation. This makes it ideal for lexical analyzers, as well as
 * spelling dictionaries.
 *
 * This library is an implementation of double-array structure for representing
 * trie, as proposed by Junichi Aoe. The details of the implementation can be
 * found at http://linux.thai.net/~thep/datrie/datrie.html
 *
 * A Trie is associated with an AlphaMap, a map between actual alphabet
 * characters and the raw characters used to walk through trie.
 * You can define the alphabet set by adding ranges of character codes
 * to it before associating it to a trie. And the keys to be added to the trie
 * must comprise only characters in such ranges. Note that the size of the
 * alphabet set is limited to 256 (TRIE_CHAR_MAX + 1), and the AlphaMap
 * will map the alphabet characters to raw codes in the range 0..255
 * (0..TRIE_CHAR_MAX). The alphabet character ranges need not be continuous,
 * but the mapped raw codes will be continuous, for the sake of compactness
 * of the trie.
 *
 * A new Trie can be created in memory using trie_new(), saved to file using
 * trie_save(), and loaded later with trie_new_from_file().
 * It can even be embeded in another file using trie_fwrite() and read back
 * using trie_fread().
 * After use, Trie objects must be freed using trie_free().
 *
 * Operations on trie include:
 *
 * - Add/delete entries with trie_store() and trie_delete()
 * - Retrieve entries with trie_retrieve()
 * - Walk through trie stepwise with TrieState and its functions
 *   (trie_root(), trie_state_walk(), trie_state_rewind(),
 *   trie_state_clone(), trie_state_copy(),
 *   trie_state_is_walkable(), trie_state_walkable_chars(),
 *   trie_state_is_single(), trie_state_get_data().
 *   And do not forget to free TrieState objects with trie_state_free()
 *   after use.)
 * - Enumerate all keys using trie_enumerate()
 * - Iterate entries using TrieIterator and its functions
 *   (trie_iterator_new(), trie_iterator_next(), trie_iterator_get_key(),
 *   trie_iterator_get_data().
 *   And do not forget to free TrieIterator objects with trie_iterator_free()
 *   after use.)
 */

/**
 * @brief Trie enumeration function
 *
 * @param key  : the key of the entry
 * @param data : the data of the entry
 * @param user_data : the user-supplied data on enumerate call
 *
 * @return TRUE to continue enumeration, FALSE to stop
 */
 
 /* Note about libpng version numbers:
 *
 *    Due to various miscommunications, unforeseen code incompatibilities
 *    and occasional factors outside the authors' control, version numbering
 *    on the library has not always been consistent and straightforward.
 *    The following table summarizes matters since version 0.89c, which was
 *    the first widely used release:
 *
 *    source                 png.h  png.h  shared-lib
 *    version                string   int  version
 *    -------                ------ -----  ----------
 *    0.89c "1.0 beta 3"     0.89      89  1.0.89
 *    0.90  "1.0 beta 4"     0.90      90  0.90  [should have been 2.0.90]
 *    0.95  "1.0 beta 5"     0.95      95  0.95  [should have been 2.0.95]
 *    0.96  "1.0 beta 6"     0.96      96  0.96  [should have been 2.0.96]
 *    0.97b "1.00.97 beta 7" 1.00.97   97  1.0.1 [should have been 2.0.97]
 *    0.97c                  0.97      97  2.0.97
 *    0.98                   0.98      98  2.0.98
 */
 
 /* png_info contains information read from or to be written to a PNG file.  One
 * or more of these must exist while reading or creating a PNG file.  The
 * information is not used by libpng during read but is used to control what
 * gets written when a PNG file is created.  "png_get_" function calls read
 * information during read and "png_set_" functions calls write information
 * when creating a PNG.
 * been moved into a separate header file that is not accessible to
 * applications.  Read libpng-manual.txt or libpng.3 for more info.
 */
 




// SPDX-License-Identifier: GPL-2.0-only
/*
 * kernel/power/hibernate.c - Hibernation (a.k.a suspend-to-disk) support.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2004 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2009 Rafael J. Wysocki, Novell Inc.
 * Copyright (C) 2012 Bojan Smojver <bojan@rexursive.com>
 */
 
 /**
 * platform_pre_snapshot - Call platform to prepare the machine for hibernation.
 * @platform_mode: Whether or not to use the platform driver.
 *
 * Use the platform driver to prepare the system for creating a hibernate image,
 * if so configured, and return an error code if that fails.
 */
 
/**
 * swsusp_show_speed - Print time elapsed between two events during hibernation.
 * @start: Starting event.
 * @stop: Final event.
 * @nr_pages: Number of memory pages processed between @start and @stop.
 * @msg: Additional diagnostic message to print.
 */
/*
void swsusp_show_speed(ktime_t start, ktime_t stop,
		      unsigned nr_pages, char *msg)
*/


/*
 * Account a tick to a process and cpustat
 * @p: the process that the CPU time gets accounted to
 * @user_tick: is the tick from userspace
 * @rq: the pointer to rq
 *
 * Tick demultiplexing follows the order
 * - pending hardirq update
 * - pending softirq update
 * - user_time
 * - idle_time
 * - system time
 *   - check for guest_time
 *   - else account as system_time
 *
 * Check for hardirq is done both for system and user time as there is
 * no timer going off while we are on hardirq and hence we may never get an
 * opportunity to update it solely in system time.
 * p->stime and friends are only updated on system time and not on irq
 * softirq as those do not count in task exec_runtime any more.
 */
/*
static void irqtime_account_process_tick(struct task_struct *p, int user_tick,
					 struct rq *rq, int ticks)
*/

#include "support/PabloSupportClasses.h"
#include "support/pngwriter.h"

#include "/usr/include/gdal/gdal.h"
#include "/usr/include/gdal/gdal_priv.h"
#include "/usr/include/gdal/gdal_utils.h"
#include "/usr/include/gdal/cpl_conv.h"
#include "/usr/include/gdal/cpl_string.h"


#define DSM_FILE        "../Input/cage6.tif"
#define OUT_FILE        "output/cage6.png"

//	Logger support object created to log all the relevant events of this simulation
class Logger	LoggerObject("output/PabloAIHomeExercise.txt");

static void generate_png (void)
{
   /* one.png
    * This will be a 300x300 image with a black background, called one.png
    * */
   pngwriter one(300,300,0,"one.png");

   LoggerObject.WriteLine("Generating one.png...");

   /* Purple rectangle (filled)
    * Make a purple filled retangle. Notice we are using
    * int colour levels, e.g. 65535 is the max level of green.
    * */
   one.filledsquare(30,5,45,295,65535,0,65535);

   /* Blue rectangle
    * Make a blue rectangle over the green one.
    * Notice that we are using colour coefficcients of type double.
    * */
   one.square(20,10,40,290,0.0,0.0,1.0);

   /* Yellow circle (filled) and Grey Circle
    * Using colour coefficcients of type double.
    * */
   one.filledcircle(250,250,40,1.0,1.0,0.0);
   one.circle(250,70,30,20000,20000,50000);

   /* Lines
    * Draw 16 lines to test all general directions of line().
    * All start from the centre and radiate outwards.
    * The colour is varied to be able to distinguish each line.
    * */
   //Top row
   one.line(150,150,0,300,0,65535,4000);
   one.line(150,150,75,300,0,65535,8000);
   one.line(150,150,150,300,0,65535,12000);
   one.line(150,150,225,300,0,65535,16000);
   one.line(150,150,300,300,0,65535,20000);
   //Right side
   one.line(150,150,300,225,0,65535,24000);
   one.line(150,150,300,150,0,65535,28000);
   one.line(150,150,300,75,0,65535,32000);
   one.line(150,150,300,0,0,65535,36000);
   //Bottom row
   one.line(150,150,225,0,0,65535,40000);
   one.line(150,150,150,0,0,65535,44000);
   one.line(150,150,75,0,0,65535,48000);
   one.line(150,150,0,0,0,65535,52000);
   //Left side
   one.line(150,150,0,75,0,65535,56000);
   one.line(150,150,0,150,0,65535,60000);
   one.line(150,150,0,225,0,65535,64000);

   /*Change the text information in the PNG header
    * */
   one.settext("one.png", "John Cleese", "Test PNG", "pngtest");
   
   /* Set text */
   //This is the text that says PNG in pink, rotated.
   one.plot_text_utf8("/usr/share/fonts/truetype/ubuntu/Ubuntu-M.ttf",60,25,25,0.0, "Pablo",0.0,0.0,255.0);
/*
   void plot_text(	char * face_path, int fontsize,

				int x_start, int y_start, 	double angle,

				char * text,

				double red, double green, double blue);
*/




   LoggerObject.WriteLine(" done. Writing to disk...");
   one.close();
   LoggerObject.WriteLine(" done.");
}

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
        LoggerObject << (string) pszFilename << " file could not be opened...\n";
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
 //           std::cout << "First cell value = " << pafScanline[0] << "\n\n";
 			LoggerObject << "First cell value = " << pafScanline[0] << "\n";
 			
 			{
 				int	column, row;
 				
 				for (row = 0; row < nYSize; row++)
 					for (column = 0; column < nXSize; column++)
 						DsmInformationObject.Value(column, row, pafScanline[row * nXSize + column]);
 			
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
			switch ((int) DsmInformationObject.Value(column, row))
			{
				case 3300:
					LoggerObject << "[" << column << "," << row << "] = 3300\n";
					outputFile.plot(column+1, rows - (row+1), 0, 0, 0); 
					break;
				case 3325:
					LoggerObject << "[" << column << "," << row << "] = 3325\n";
					outputFile.plot(column+1, rows - (row+1), 65535, 0, 0); 
					break;
				case 3335:
					LoggerObject << "[" << column << "," << row << "] = 3335\n";
					outputFile.plot(column+1, rows - (row+1), 0, 65535, 0); 
					break;
				case 3370:
					LoggerObject << "[" << column << "," << row << "] = 3370\n";
					outputFile.plot(column+1, rows - (row+1), 0, 0, 65535); 
					break;
				default:
					LoggerObject << "[" << column << "," << row << "] = " << (int) DsmInformationObject.Value(column, row) << "\n";
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

/*
bool DirectMovementWithVisibility(const class DsmInformation DsmInformationObject, const locationDsm currentLocation, const locationDsm objectivelocation, locationDsm *nextLocation_ptr, const int visibility)
{
	double					mTargetToObjectiveSlope;
	double					bTargetToObjectiveYCoordinatateWhileXIsZero;
	
	//	y = mx + b, y2-y1/x2-x1 = m, b = y2 - mx2
	mTargetToObjectiveSlope						= (objectivelocation.y - currentLocation.y) / (objectivelocation.x - currentLocation.x)
	bTargetToObjectiveYCoordinatateWhileXIsZero	= objectivelocation.y - (mTargetToObjectiveSlope * objectivelocation.x)
	
	
	return false;

}	//	DirectMovementWithVisibility()
*/

int main()
{
//	locationDsm				targetInitialLocation, targetLocation, targetObjectiveLocation, targetNextLocation;
	const int				groundLevel = 3300;
	long int				simulationSeconds = 0;
	double					mTargetToObjectiveSlope;
	double					bTargetToObjectiveYCoordinatateWhileXIsZero;
	int						visibilityInMeters = 5;
	
    class DsmInformation    DsmInformationObject;
     
    //  GDAL driver initialization
    GdalDriverInitialization();
    
    // 	Analyze the input DSM file
    DsmInputFileAnalyze(DSM_FILE, DsmInformationObject);
    
    //	Create the output file
    DsmOutputFileCreation(OUT_FILE, DsmInformationObject);
    
    //	Set initial target and target objective locations
//    targetLocation.x	= targetInitialLocation.x	= 0;
  //  targetLocation.y	= targetInitialLocation.y	= 0;
  //  targetObjectiveLocation.x						= 339;
  //  targetObjectiveLocation.y						= 150;

      
//    while (targetLocation != targetObjectiveLocation)
    {
/*
    	if (DirectMovementWithVisibility(DsmInformationObject, targetLocation, targetObjectiveLocation, &targetNextLocation, visibilityInMeters) == true)
    	{
    	}
*/    
    	
    	simulationSeconds++;	
    }	
    
   
 //   generate_png();
    
	return 0;
}
