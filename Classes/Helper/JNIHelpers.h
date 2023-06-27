//
//  JniHelpers.h
//  gamebase
//
//  Created by NgocDiep on 7/8/15.
//
//
#ifndef __JniHelpers_H__
#define __JniHelpers_H__
#include <iostream>
#include "cocos2d.h"

using namespace std;

class JniHelpers {
public:
	static unsigned int 		jniCommonIntCall	(const char* methodName, const char* classPath, const char* arg0) ;
	static unsigned int 		jniCommonIntCall	(const char* methodName, const char* classPath) ;
	static unsigned int 		jniCommonIntCall	(const char* methodName, const char* classPath, const char* arg0, bool looping) ;
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath);

	static 			std::string jniCommonStringCall	(const char* methodName, const char* classPath, const char* arg0) ;

	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, const char* arg0);
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, const char* arg0, bool looping);	
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, const char* arg0, long score);
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, const char* arg0, int numSteps);
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, const char* arg0, const char* arg1);

	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, unsigned int arg0);
    static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, unsigned int level, unsigned long score, unsigned int obstacles);
	static 			float 		jniCommonFloatCall	(const char* methodName, const char* classPath ) ;
	static 			void 		jniCommonVoidCall	(const char* methodName, const char* classPath, float arg0);

	static 			bool	 	jniCommonBoolCall	(const char* methodName, const char* classPath) ;
	static 			bool	 	jniCommonBoolCall	(const char* methodName, const char* classPath, unsigned int arg0) ;
};

#endif /* defined(__JniHelpers_H__) */
