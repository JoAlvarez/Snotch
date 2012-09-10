#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2009";
	static const double UBUNTU_VERSION_STYLE = 9.01;
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 2;
	static const long BUILD = 874;
	static const long REVISION = 4500;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1943;
	#define RC_FILEVERSION 1,2,874,4500
	#define RC_FILEVERSION_STRING "1, 2, 874, 4500\0"
	static const char FULLVERSION_STRING[] = "1.2.874.4500";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //VERSION_h
