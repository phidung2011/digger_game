//
//  RageIAPHelper.m
//  In App Rage
//
//  Created by Ray Wenderlich on 9/5/12.
//  Copyright (c) 2012 Razeware LLC. All rights reserved.
//

#import "NewWindBaseIAPHelper.h"

@implementation NewWindBaseIAPHelper

+ (NewWindBaseIAPHelper *)sharedInstance:(NSArray *)arrItems {
    static dispatch_once_t once;
    static NewWindBaseIAPHelper * sharedInstance;
    dispatch_once(&once, ^{
        NSSet * productIdentifiers = [NSSet setWithArray:arrItems];
        sharedInstance = [[self alloc] initWithProductIdentifiers:productIdentifiers];
    });
    return sharedInstance;
}

@end
