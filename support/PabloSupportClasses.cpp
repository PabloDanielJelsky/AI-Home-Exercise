#include "PabloSupportClasses.h"

//	Default Constructor 
Logger::Logger() 
{ 
	this->bInitialized  = false;
	
}	//	Logger::Logger() 

//	Parametrized Constructor 
Logger::Logger(string sFilename) 
{ 
	setFilename(sFilename);	
	
}	//	Logger::Logger()      

//	Destructor
Logger::~Logger() 
{ 
	this->outfile.close();
	
}	//	Logger::~Logger() 

Logger& operator << (Logger& logger, const string& sString)
{
	logger.write(sString);
	
	return logger;
	
}	//	Logger& operator <<

Logger& operator << (Logger& logger, const int& iInteger)
{
	logger.write(iInteger);
	
	return logger;
	
}	//	Logger& operator <<

Logger& operator << (Logger& logger, const long& lLong)
{
	logger.write(lLong);
	
	return logger;
	
}	//	Logger& operator <<

Logger& operator << (Logger& logger, const float& fFloat)
{
	logger.write(fFloat);
	
	return logger;
	
}	//	Logger& operator <<

Logger& operator << (Logger& logger, const double& dDouble)
{
	logger.write(dDouble);
	
	return logger;
	
}	//	Logger& operator <<


void Logger::write(string sString)
{
	this->outfile << sString;
		
}	//	Logger::write()

void Logger::write(int iInteger)
{
	this->outfile << iInteger;
	
}	//	Logger::write()

void Logger::write(long lLong)
{
	this->outfile << lLong;
	
}	//	Logger::write()

void Logger::write(float fFloat)
{
	this->outfile << fFloat;
	
}	//	Logger::write()

void Logger::write(double dDouble)
{
	this->outfile << dDouble;
	
}	//	Logger::write()

void Logger::writeLine(string sLine)
{
	this->outfile << sLine << endl;
	
}	//	Logger::writeLine()

bool Logger::setFilename(string sFilename)
{
    if (this->bInitialized == false && this->sFilename == "")
    {
		this->bInitialized  = true;
		this->sFilename		= sFilename;
		this->outfile.open(sFilename);	 
    }
    
}	//	Logger::setFilename()

//	Default Constructor 
DsmInformation::DsmInformation() 
{ 
	logger.setFilename("output/DsmInformation.txt");
	logger.writeLine("Default Constructor called"); 
	this->bInitialized  = false; 
	this->iColumns      = 0;
	this->iRows         = 0;
	
}	//	DsmInformation::DsmInformation()

//	Parametrized Constructor 
DsmInformation::DsmInformation(int iColumns, int iRows) 
{ 
	logger.writeLine("Parametrized Constructor called"); 

	this->bInitialized  = true;
	this->iColumns      = iColumns;
	this->iRows         = iRows;

	pdPixelValue  = new double[iColumns * iRows];
	
}	//	DsmInformation::DsmInformation()

//	Destructor
DsmInformation::~DsmInformation() 
{
	logger.writeLine("Destructor called for cleanup");  
	
	if (pdPixelValue != NULL)
	{
		logger.writeLine("Internal array is deallocated");  
		delete [] pdPixelValue; 
	}
	else
	{
		logger.writeLine("The internal array was NOT initialized and therefore there is no need to deallocate it");
	}
	
}	//	DsmInformation::~DsmInformation()

int DsmInformation::rows(void)
{
    return (this->iRows);
    
}   //  DsmInformation::rows()
 
int DsmInformation::columns(void)
{
    return (this->iColumns);
    
}   //  DsmInformation::columns()

void DsmInformation::rows(int iRows)
{
	logger.write("Called rows(");
	logger.write(iRows);
	logger.writeLine(")");

    this->iRows = iRows;
    
    if (this->bInitialized == false && this->columns() != 0)
    {
    	logger.write("Initializing internal array (");
    	logger.write(this->columns());
    	logger.write("x");
    	logger.write(iRows);
    	logger.writeLine(")");
        this->pdPixelValue  = new double[this->columns() * iRows];   
        this->bInitialized  = true; 
    }
    
}   //  DsmInformation::rows()

void DsmInformation::columns(int iColumns)
{
	logger.write("Called columns(");
	logger.write(iColumns);
	logger.writeLine(")");
	
    this->iColumns  = iColumns;
    
    if (this->bInitialized == false && this->rows() != 0)
    {
    	logger.write("Initializing internal array (");
    	logger.write(iColumns);
    	logger.write("x");
    	logger.write(this->rows());
    	logger.writeLine(")");
        this->pdPixelValue  = new double[iColumns * this->rows()];  
        this->bInitialized  = true; 
    }
    
}   //  DsmInformation::columns()

double DsmInformation::pixelValue(int row, int column)
{
    return (this->pdPixelValue[row*this->columns()+column]);
    
}   //  DsmInformation::pixelValue()

