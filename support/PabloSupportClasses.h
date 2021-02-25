#ifndef __PABLO_AI_SUPPORT_CLASSES_H__
#define	__PABLO_AI_SUPPORT_CLASSES_H__

#include <iostream>
// using ofstream constructors.
#include <fstream> 
#include <string>

using namespace std;

class Logger
{
	public:
		bool setFilename(string sFilename);
		void write(string sString);
		void write(int iInteger);
		void write(long lLong);
		void write(float fFloat);
		void write(double dDouble);
		void writeLine(string sLine);
		
		friend Logger& operator << (Logger& logger, const int& iInteger);
		friend Logger& operator << (Logger& logger, const long& lLong);
		friend Logger& operator << (Logger& logger, const float& fFloat);
		friend Logger& operator << (Logger& logger, const double& dDouble);
		friend Logger& operator << (Logger& logger, const string& sString);
	
		//	Default Constructor 
		Logger(); 

		//	Parametrized Constructor 
		Logger(string sFilename);
 
		//	Destructor
		~Logger();

	private:
		bool    	bInitialized 	= false;
		string		sFilename		= "";
		ofstream	outfile;

};	//	class Logger

class DsmInformation
{ 
	public:
		int rows(void);
		int columns(void);
		void rows(int iRows);
		void columns(int iColumns);
		double pixelValue(int row, int column);

		//	Default Constructor 
		DsmInformation();

		//	Parametrized Constructor 
		DsmInformation(int iColumns, int iRows); 

		//	Destructor
		~DsmInformation();
	    
	private: 
		bool    		bInitialized = false;
		double  		*pdPixelValue = NULL; 
		int     		iColumns = 0, iRows = 0;
		class Logger	logger;
	    
};  //  class DsmInformation

#endif	// __PABLO_AI_SUPPORT_CLASSES_H__
