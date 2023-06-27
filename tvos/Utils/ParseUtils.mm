//
//  ParseUtils.m
//  gamebase
//
//  Created by NGOCDIEP on 10/1/15.
//
//

#import "ParseUtils.h"
#import "PlayGameSingleton.h"
#import "Contants_iOS.h"
#import <AdSupport/AdSupport.h>
#include "GameSingleton.h"
#include "DataManager.h"
#include "NativeUtils.h"

#define CLASS_USER_MASTER   @"UserMaster"
#define CLASS_USER_DEVICE   @"UserDevice"

#define COL_OBJECT_ID       @"objectId"

	// UserMaster
#define COL_MASTER_USER_ID      @"userID"
#define COL_MASTER_USER_NAME    @"userName"
#define COL_MASTER_COINS        @"coins"
#define COL_MASTER_SCORES       @"scores"
#define COL_MASTER_TYPEOS       @"typeOS"
#define COL_MASTER_USER_DATA    @"userData"
#define COL_MASTER_VERSION      @"version"
#define COL_MASTER_REMOVEADS    @"removeAds"
#define COL_MASTER_TOKEN        @"token"

	// UserDevice
#define COL_DEVICE_USER_ID      @"userID"
#define COL_DEVICE_DEVICE_ID    @"deviceID"


//static NSString* col_device_id;
static NSString* col_user_object_id = @"";
static PFObject* dataString = nil;
static PFObject* userDeviceObj = nil;

@implementation ParseUtils

+ (void)initParse{
    
    // Enable Local Datastore.
    
//    [Parse enableLocalDatastore];
    
    [Parse setApplicationId:APPLICATION_ID clientKey:CLIENT_KEY];
    
//    [PFUser enableAutomaticUser];
    
    // Set default ACLs
    PFACL *defaultACL = [PFACL ACL];
    [defaultACL setPublicReadAccess:YES];
    [defaultACL setPublicWriteAccess:YES];
    [PFACL setDefaultACL:defaultACL withAccessForCurrentUser:YES];
    
    
}

+ (void) createUserMaster:(NSString *)deviceID{
    
    NSString *uuid = [[NSUUID UUID] UUIDString];
    
    PFObject* pObject =  [PFObject objectWithClassName:CLASS_USER_MASTER];
    pObject[COL_MASTER_USER_ID] = uuid;
    pObject[COL_MASTER_USER_NAME] = [uuid substringToIndex:8];
    pObject[COL_MASTER_COINS] = @1000;
    pObject[COL_MASTER_SCORES] = @0;
    pObject[COL_MASTER_USER_DATA] = @"";
    pObject[COL_MASTER_REMOVEADS] = @0;
    pObject[COL_MASTER_TOKEN] = @"";

    [pObject saveInBackgroundWithBlock:^(BOOL succeeded, NSError * _Nullable error) {
        
        if (succeeded)
        {
            GameSingleton::getInstance()->setCurrentState(GameState::sCreateUserDevice);
            
        }
        else
        {
            NSLog(@" createUserMaster failed with error: @%@",[error description]);
//            PlayGameSingleton::sharedInstance()->showAlertConnection();
        }
    }];
    [ParseUtils createUserDevice:deviceID :uuid];
//    [pObject saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
//        if (succeeded) {
//            
//            [ParseUtils createUserDevice:deviceID :uuid];
//            
//            
//            
//        } else {
//            NSLog(@" createUserMaster error ");
//        }
//    }];
//    [ParseUtils createUserDevice:deviceID :uuid];
    
}

+ (void) createUserDevice:(NSString *)deviceID :(NSString *)userID{
    PFObject* pObject =  [PFObject objectWithClassName:CLASS_USER_DEVICE];
    pObject[COL_DEVICE_DEVICE_ID] = deviceID;
    pObject[COL_DEVICE_USER_ID] = userID;
    [pObject saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        if (succeeded) {
            GameSingleton::getInstance()->setCurrentState(GameState::sLoadUserMasterFromCreate);
            
            PFQuery *query1 = [PFQuery queryWithClassName:CLASS_USER_MASTER];
            [query1 whereKey:COL_MASTER_USER_ID equalTo:userID];
            [query1 getFirstObjectInBackgroundWithBlock:^(PFObject * obj1, NSError * error1) {
                if (obj1 != nil)
                {
                    col_user_object_id = [[NSString alloc] initWithString:obj1.objectId];
                    
//                    if (dataString)
//                    {
//                        [dataString release];
//                    }
                    dataString = obj1;
                    [dataString retain];
                    PlayGameSingleton::sharedInstance()->_login = 1;
                    GameSingleton::getInstance()->setCurrentState(GameState::sLoginSucceed);
                    
                }
                else
                {
//                    PlayGameSingleton::sharedInstance()->showAlertConnection();
                }
            }];

        } else {
            NSLog(@" createUserDevice error ");
//            PlayGameSingleton::sharedInstance()->showAlertConnection();
        }
    }];
}

+ (void) updateDataString:(NSString *)colObj :(NSString *)value{
    PFQuery *query = [PFQuery queryWithClassName:CLASS_USER_MASTER];
    [query getObjectInBackgroundWithId:col_user_object_id block:^(PFObject *object, NSError *error) {
        if(error == nil){
            object[colObj] = value;
            dataString = object;
            [dataString retain];
            [object saveInBackgroundWithBlock:^(BOOL succeeded, NSError * _Nullable error) {
                if (succeeded)
                {
                    
                }
                else
                {
//                    PlayGameSingleton::sharedInstance()->showAlertConnection();
                }
            }];
        }
    }];
}

+ (void) updateDataInt:(NSString *)colObj :(int) value{
    PFQuery *query = [PFQuery queryWithClassName:CLASS_USER_MASTER];
    NSLog(@"updateDataInt %@  %d",colObj, value);
    [query getObjectInBackgroundWithId:col_user_object_id block:^(PFObject *object, NSError *error) {
        if(error == nil){
            object[colObj] = @(value);
            dataString = object;
            [dataString retain];
            [object saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
                if(succeeded)
                {
                    
                    NSLog(@"thanh cong %@",colObj);
                }
                else
                {
                    NSLog(@"khong thanh cong %@", error);
//                    PlayGameSingleton::sharedInstance()->showAlertConnection();
                }
            }];
        }
    }];
}

+ (NSInteger) getDataInt:(NSString *)key{
    
    if (dataString) {
        NSString *tg = dataString[key];
        return tg.integerValue;
    }
    
    return -1;
}

+ (NSString*) getDataString:(NSString *)key{
    if (dataString) {
        return dataString[key];
    }
 
    return @"";
}

+ (void) userLogin {

    PlayGameSingleton::sharedInstance()->_login = 0;
    
//    NSString* deviceId = [[UIDevice currentDevice].identifierForVendor UUIDString];
    NSString* deviceId = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
    
//    NSLog(@"-------ASID---%@",);

    NSLog(@"-------------- device id: %@",deviceId);
    
//    62832E15-2494-496F-BEF7-07467A7A9263
    
    
    GameSingleton::getInstance()->setCurrentState(GameState::sLoadUserDevice);
    
    PFQuery *query = [PFQuery queryWithClassName:CLASS_USER_DEVICE];
    [query whereKey:COL_DEVICE_DEVICE_ID equalTo:deviceId];
    
    [query getFirstObjectInBackgroundWithBlock:^(PFObject *object, NSError *error) {
        if (object == nil) {
            // Chua co tai khoan
            // Sẽ yêu cầu kết nối mạng để tạo tài khoản mới hoặc là đồng
            // bộ dữ liệu với server

            if(PlayGameSingleton::sharedInstance()->isOnline()){
                // Dữ liệu local không có sẽ tiến hành lấy dữ liệu trên
                // server về và đồng bộ với client. Nếu không có dữ liệu
                // trên server thì sẽ tạo mới User.
                
                PFQuery *query = [PFQuery queryWithClassName:CLASS_USER_DEVICE];
                
                [query whereKey:COL_DEVICE_DEVICE_ID equalTo:deviceId];
                [query getFirstObjectInBackgroundWithBlock:^(PFObject *object, NSError *error) {
                    if(object == nil){
                        GameSingleton::getInstance()->setCurrentState(GameState::sCreateUserMaster);
                        [ParseUtils createUserMaster:deviceId];
                    }else{
                        GameSingleton::getInstance()->setCurrentState(GameState::sLoadUserMaster);
                        
                        PFQuery *qr = [PFQuery queryWithClassName:CLASS_USER_MASTER];
                        [qr whereKey:COL_MASTER_USER_ID equalTo:object[COL_DEVICE_USER_ID]];
                        [qr getFirstObjectInBackgroundWithBlock:^(PFObject *obj1, NSError *error) {
                            if(obj1 != nil){
                                col_user_object_id = [[NSString alloc] initWithString:obj1.objectId];
                                dataString = obj1;
                                [dataString retain];
                                PlayGameSingleton::sharedInstance()->_login = 1;
                                GameSingleton::getInstance()->setCurrentState(GameState::sLoginSucceed);
                            }
                            else
                            {
//                                PlayGameSingleton::sharedInstance()->showAlertConnection();
                            }
                        }];
                    }
                }];
                
            }else{
                PlayGameSingleton::sharedInstance()->_login = -1;
//                PlayGameSingleton::sharedInstance()->showAlertConnection();
            }
            
        } else {
            
            GameSingleton::getInstance()->setCurrentState(GameState::sLoadUserMaster);
            
            
            PFQuery *query1 = [PFQuery queryWithClassName:CLASS_USER_MASTER];
            [query1 whereKey:COL_MASTER_USER_ID equalTo:object[COL_DEVICE_USER_ID]];
            [query1 getFirstObjectInBackgroundWithBlock:^(PFObject * obj1, NSError * error1) {
                if (obj1 == nil)
                {
//                    PlayGameSingleton::sharedInstance()->showAlertConnection();
                }
                else
                {
                    
                    col_user_object_id = [[NSString alloc] initWithString:obj1.objectId];
                    dataString = obj1;
                    [dataString retain];
                    PlayGameSingleton::sharedInstance()->_login = 1;
                    GameSingleton::getInstance()->setCurrentState(GameState::sLoginSucceed);

                }
            }];
            
        }
    }];
}


+ (void) reload
{
}

@end
