//
//  ParseUtils.h
//  gamebase
//
//  Created by Phi Dzung on 10/1/15.
//
//

#import <Foundation/Foundation.h>
#import <Parse/Parse.h>



@interface ParseUtils : NSObject
{
}

+ (void) userLogin;
+ (void) createUserMaster: (NSString*)deviceID;
+ (void) createUserDevice: (NSString*)deviceID : (NSString*)userID;
+ (void) updateDataString: (NSString*)colObj : (NSString*)value;
+ (void) updateDataInt: (NSString*)colObj : (int)value;
+ (NSInteger) getDataInt: (NSString*) key;
+ (NSString*) getDataString: (NSString*) key;
+ (void) initParse;

+ (void) reload;



@end
