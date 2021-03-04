//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File:			AiModel.c
//
// Version:			01.00
//
// Description:		Model classes the AI home excercise source file
//
// Author:			Pablo Daniel Jelsky
//
// Copyright:		
//
// Remarks:			In this module the objective is to create model base class that will be derived as agent or target classes
//
//	DEVELOPMENT HISTORY:
//
//	Date		Author					Release		Change Id	Description of change
//	----------- -----------------------	-----------	----------- ---------------------
//	02-03-2021	Pablo Daniel Jelsky		01			00			Initial
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	========
//	========
//	Model // 
//	========
//	========
//	The model class will use composition between internal structures and classes like: DsmInformation, and use of A* algorithm function, or
//	libraries like GDAL (to read and write GeoTIFF files)
//
//	The libraries used by this module:
//	GDAL
//	====
//		This library is used to read and create GetoTIFF files
//			GDAL is a translator library for raster and vector geospatial data formats that is released under an X/MIT style Open Source License by the Open Source Geospatial Foundation. 
//			As a library, it presents a single raster abstract data model and single vector abstract data model to the calling application for all supported formats. 
//			It also comes with a variety of useful command line utilities for data translation and processing.
//				Web site: https://gdal.org/
//				library is located in /usr/lib/libgdal.a (called by g++ linker with -lgdal), for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/gdal/, for simplicity the library will be copied inside the "include" directory in the project
//	PNGwriter
//	=========
//		This "library" is included as two files that will wrap the png library, pngwriter.cc and pngwriter.h
//		This module will use of libraries, the png library (for creating and reading .png files) and the freetype library to write text inside the .png files
//			PNGwriter is a very easy to use open source graphics library that uses PNG as its output format. The interface has been designed to be as simple and intuitive as possible. 
//			It supports plotting and reading pixels in the RGB (red, green, blue), HSV (hue, saturation, value/brightness) and CMYK (cyan, magenta, yellow, black) colour spaces, 
//			basic shapes, scaling, bilinear interpolation, full TrueType antialiased and rotated text support, bezier curves, opening existing PNG images and more.
//				Web site: http://pngwriter.sourceforge.net/
//				source and include files are located under the "support" directory inside the project and are compiled and linked with the help of the Makefile
//	libpng
//	======
//		This library is used by PNGWriter module
//			libpng is the official PNG reference library. It supports almost all PNG features, is extensible, and has been extensively tested for over 23 years. 
//			The home site for development versions (i.e., may be buggy or subject to change or include experimental features) is https://libpng.sourceforge.io/, 
//			and the place to go for questions about the library is the png-mng-implement mailing list.
//				Web site: http://libpng.org/pub/png/libpng.html
//				library is located in /usr/lib/x86_64-linux-gnu/libpng.a (link to /usr/lib/x86_64-linux-gnu/libpng16.a) (called by g++ linker with -lpng), 
//					for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/libpng (link to /usr/include/libpng16), for simplicity the library will be copied inside the "include" directory in the project
//	FreeType2
//	=========
//		This library is used by PNGWriter module		
//			FreeType is a freely available software library to render fonts.
//			It is written in C, designed to be small, efficient, highly customizable, and portable while capable of producing high-quality output (glyph images) of most vector and bitmap font formats.	
//				Web site: https://www.freetype.org/
//				library is located in /usr/lib/x86_64-linux-gnu/libfreetype.a (called by g++ linker with -lfreetype), for simplicity the library will be copied inside the "libraries" directory in the project
//				include files are located under /usr/include/freetype2, for simplicity the library will be copied inside the "include" directory in the project	
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
		#include <string>	// for strings
		/*---- library files -------------------------------------------------------*/
		/*---- program files -------------------------------------------------------*/
		#include "AiModel.h"
	
	/*
		****************************************************************************
		* EXTERNAL REFERENCE    
		****************************************************************************
	*/
		/*---- name spaces declarations --------------------------------------------*/
		using namespace std;
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
	
	/*
		****************************************************************************
		* PRIVATE FUNCTION DEFINITIONS
		****************************************************************************
	*/	


	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/
	/*
		****************************************************************************
		* PUBLIC CLASS CONSTRUCTORS AND DESTRUCTORS DEFINITIONS
		****************************************************************************
	*/
	
		// Class name		: Model
		// Programmer name	: Pablo Daniel Jelsky
		// Last update date	: 02-03-2021
		// Description		: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Default constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This constructor will create a non valid object
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Model::Model()
		{
			this->initialized	= false;
			
		}	//	Model::Model()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Parametrized constructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This constructors take as parameter GeoTIFF file that
		//							will be the base of the DSM information map
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: string geoTiffFilename (name of the GeoTIFF file)
		//						 string modelName (name that will be used for logger and .csv files)
		/////////////////////////////////////////////////////////////////////////////////
		Model::Model(string geoTiffFilename, string modelName)
		{
			string	loggerDirectory	= "output/";
			string	loggerSuffix	= ".txt";
			
			this->geoTiffFilename	= geoTiffFilename;
			this->modelName			= modelName;
			//	Creating the logger object
			this->logger.Filename(loggerDirectory + this->modelName + loggerSuffix);
			//	Registering the GDAL drivers
			this->_GdalDriverInitialization();
			//	Raster the GeoTIFF input file inside the object for further use
			if (false == _DsmInputFileRaster())
			{
				this->initialized	= false;
				return;
			}
			
			this->graphic.Rows(this->dsmMapInfo.Rows());
			this->graphic.Columns(this->dsmMapInfo.Columns());
			
			this->initialized	= true;
			
		}	//	Model::Model()
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: Destructor
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This destructor destroys the array data created with CPLMalloc()
		// Remarks         		: 
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////
		Model::~Model()
		{
			if (NULL != this->pafScanline)
				CPLFree(this->pafScanline);
			
		}	//	Model::~Model()
			
		
	/*
		****************************************************************************
		* PUBLIC CLASS MEMBER FUNCTION DEFINITIONS
		****************************************************************************
	*/
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: GraphicCreation
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 03-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This public member function creates an output graphic
		//							file based on the raster information in it
		// Remarks         		: Currently supported formats (.png and GeoTIFF)
		//							returns true if the graphic was created,
		//							false otherwise
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: graphic type (.png or GeoTIFF)
		//							graphic name
		/////////////////////////////////////////////////////////////////////////////////	
		bool Model::GraphicCreation(graphicType typeOfGraphic, string filename)
		{
			this->graphic.Filename(filename);
			this->graphic.Create(typeOfGraphic);
			
		}	//	Model::GraphicCreation()
		

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
		// Class name			: Model
		// Function				: _GdalDriverInitialization
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This private member function that will register the
		//							GDAL drivers for reading/creating GeoTIFF files
		// Remarks         		: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		void Model::_GdalDriverInitialization(void)
		{
			//  Register all the GDAL drivers
			GDALAllRegister();
			
			this->logger.WriteLine("*** GDAL Driver Initialization ***");
			this->logger.WriteLine("\tThe following format drivers are configured and support output:");
			
			for (int iDriverFormat = 0; iDriverFormat < GDALGetDriverCount(); iDriverFormat++)
			{
				string		loggerString;
				GDALDriverH hDriver = GDALGetDriver(iDriverFormat);

				if (GDALGetMetadataItem(hDriver, GDAL_DCAP_RASTER, nullptr) != nullptr &&
				    (GDALGetMetadataItem(hDriver, GDAL_DCAP_CREATE, nullptr ) != nullptr
				    || GDALGetMetadataItem(hDriver, GDAL_DCAP_CREATECOPY, nullptr ) != nullptr))
				{
					loggerString	= "\t\t" + (string) GDALGetDriverShortName(hDriver) + ":  " + (string) GDALGetDriverLongName(hDriver) + "\n";
					this->logger << loggerString;
				}
			}
			   
		}   //	Model::_GdalDriverInitialization(void)
		
		/////////////////////////////////////////////////////////////////////////////////
		// Class name			: Model
		// Function				: _DsmInputFileRaster
		// Programmer name		: Pablo Daniel Jelsky
		// Last update date		: 02-03-2021
		// Class description	: This base class represents the model that will be derived
		//						as a person (class) that could be an agent, a target, etc
		// Function description	: This private member function read the GeoTIFF file and 
		//							raster it inside the object for further use
		// Remarks         		: The Geospatial Data Abstraction Library (GDAL) is a computer 
		//							software library for reading and writing raster and vector 
		//							geospatial data formats
		/////////////////////////////////////////////////////////////////////////////////
		// Arguments			: None
		/////////////////////////////////////////////////////////////////////////////////	
		bool Model::_DsmInputFileRaster(void)
		{
			this->logger.WriteLine("*** GeoTIFF DSM Input File Raster Operation ***");
			  
			//  Opening the File        
			this->poDataset = (GDALDataset *) GDALOpen(this->geoTiffFilename.c_str(), GA_ReadOnly);
			
			if (NULL == poDataset)
			{
				this->logger << "\t" <<  this->geoTiffFilename << " file could not be opened...\n";
			}
			else
			{
				this->logger << "\t" <<  this->geoTiffFilename << " file was successfully opened...\n";

				//  Getting Dataset Information
				double        adfGeoTransform[6];
				
				this->logger << "\tDriver: " << this->poDataset->GetDriver()->GetDescription() << "/" <<  this->poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME) << "\n";
				this->logger << "\tDSM file size is: " << this->poDataset->GetRasterXSize() << " columns by " << this->poDataset->GetRasterYSize() << " rows by " << this->poDataset->GetRasterCount() << " pixel" << "\n";
				
				//	Create the DSM map info object with the GeoTIFF size
				this->dsmMapInfo.Rows(poDataset->GetRasterYSize());
				this->dsmMapInfo.Columns(poDataset->GetRasterXSize());

				{     	
					//  Fetching a Raster Band
					GDALRasterBand  *poBand;
					int             nBlockXSize, nBlockYSize;
					int             bGotMin, bGotMax;
					double          adfMinMax[2];
					poBand = this->poDataset->GetRasterBand(1);
					poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
					this->logger << "\nDSM file block is " << nBlockXSize << " by " << nBlockYSize << " type is " << GDALGetDataTypeName(poBand->GetRasterDataType()) 
								<< " and color interpretation is " << GDALGetColorInterpretationName(poBand->GetColorInterpretation()) << "\n";

					adfMinMax[0]	= poBand->GetMinimum(&bGotMin);
					adfMinMax[1]	= poBand->GetMaximum(&bGotMax);
					
					if (!(bGotMin && bGotMax))
					{
					    GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
					    this->logger << "\t\tMinimum = " << adfMinMax[0] << ", maximum = " << adfMinMax[1] << "\n";
					}
					if (poBand->GetOverviewCount() > 0)
					{
						this->logger << "\t\tBand has " << poBand->GetOverviewCount() << " overviews.\n";
					}

					if (NULL != poBand->GetColorTable())
					{
						this->logger << "\t\tBand has a color table with " << poBand->GetColorTable()->GetColorEntryCount() << " entries.\n";
					}
					
					//  Reading Raster Data
					//  Reading Raster Data
					//  Reading Raster Data
					int   nXSize = poBand->GetXSize();
					int	  nYSize = poBand->GetYSize();
					
					this->pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize*nYSize);
					if (NULL == this->pafScanline)
					{
						this->logger << "\tThe raster data array could NOT be created.\n";
						return false;
					}
					else
					{
						this->logger << "\tThe raster data array was successfully created.\n";
					}

					poBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize,
					                this->pafScanline, nXSize, nYSize, GDT_Float32,
					                0, 0 );        	        
							 			
		 			//	Insert the array information into the DSM map object
		 			{
		 				int	column, row;
		 				
		 				for (row = 0; row < nYSize; row++)
		 					for (column = 0; column < nXSize; column++)
		 						this->dsmMapInfo.Elevation(column, row, this->pafScanline[row * nXSize + column]);
		 			
		 			}
				}
			}
			
			return true;
			
		}   //  Model::_DsmInputFileRaster()
	
	
