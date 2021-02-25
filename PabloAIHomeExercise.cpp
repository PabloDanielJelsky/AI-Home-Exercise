#include "support/PabloSupportClasses.h"
#include "support/pngwriter.h"

#include "/usr/include/gdal/gdal.h"
#include "/usr/include/gdal/gdal_priv.h"
#include "/usr/include/gdal/gdal_utils.h"
#include "/usr/include/gdal/cpl_conv.h"
#include "/usr/include/gdal/cpl_string.h"



#define DSM_FILE        "../Input/cage6.tif"
#define OUT_FILE        "output/cage6.png"




class Logger	LoggerObject("output/PabloAIHomeExercise.txt");

static void generate_png (void)
{
   /* one.png
    * This will be a 300x300 image with a black background, called one.png
    * */
   pngwriter one(300,300,0,"one.png");

   LoggerObject.writeLine("Generating one.png...");

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




   LoggerObject.writeLine(" done. Writing to disk...");
   one.close();
   LoggerObject.writeLine(" done.");
}


static void GdalDriverInitialization(void)
{
    //  Register all the GDAL drivers
    GDALAllRegister();
    
    LoggerObject.writeLine("The following format drivers are configured and support output:");
    
    for(int iDriverFormat = 0; iDriverFormat < GDALGetDriverCount(); iDriverFormat++)
    {
        GDALDriverH hDriver = GDALGetDriver(iDriverFormat);

        if( GDALGetMetadataItem( hDriver, GDAL_DCAP_RASTER, nullptr) != nullptr &&
            (GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATE, nullptr ) != nullptr
            || GDALGetMetadataItem( hDriver, GDAL_DCAP_CREATECOPY, nullptr ) != nullptr) )
        {
            cout << "\t" << GDALGetDriverShortName(hDriver) << ":  " << GDALGetDriverLongName(hDriver) << endl;
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
        cout << *pszFilename << " file could not be opened..." << endl;
    }
    else
    {
        cout << pszFilename << " file was successfully opened..." << endl;

        //  Getting Dataset Information
        double        adfGeoTransform[6];
        
        cout << "Driver: " << poDataset->GetDriver()->GetDescription() << "/" <<  poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME) << endl;
        cout << "DSM file size is: " << poDataset->GetRasterXSize() << " columns by " << poDataset->GetRasterYSize() << " rows by " << poDataset->GetRasterCount() << " pixel" << endl;
        
        DsmInformationObject.rows(poDataset->GetRasterYSize());
        DsmInformationObject.columns(poDataset->GetRasterXSize());

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
            printf( "Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1] );
            if( poBand->GetOverviewCount() > 0 )
                printf( "Band has %d overviews.\n", poBand->GetOverviewCount() );
            if( poBand->GetColorTable() != NULL )
                printf( "Band has a color table with %d entries.\n",
                        poBand->GetColorTable()->GetColorEntryCount() );
            

            //  Reading Raster Data
            //  Reading Raster Data
            //  Reading Raster Data
            float *pafScanline;
            int   nXSize = poBand->GetXSize();
            pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize);
            
//            printf ("nXSize = %d\n", nXSize);
            std::cout << "nXSize = " << nXSize << "\n" ;
      
            
            
            poBand->RasterIO( GF_Read, 0, 0, nXSize, 1,
                            pafScanline, nXSize, 1, GDT_Float32,
                            0, 0 );        
 //           printf ("First cell = %d\n", pafScanline[0];
            std::cout << "First cell value = " << pafScanline[0] << "\n\n";
            
             CPLFree(pafScanline);
             
             
             
        }
    }
    
}   //  DsmInputFileAnalyze()

int main()
{
    class DsmInformation    DsmInformationObject;
    
    LoggerObject.writeLine("Pablo");
    LoggerObject << "Hola a todos" << 1 << " o todas " << 2.03 << "\n";

    //  GDAL driver initialization
    GdalDriverInitialization();
    
    // Analyze the input DSM file
    DsmInputFileAnalyze(DSM_FILE, DsmInformationObject);
    
    cout << "Quantity of rows: " << DsmInformationObject.rows();
    
    generate_png();
    
	return 0;
}
