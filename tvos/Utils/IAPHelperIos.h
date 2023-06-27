//
//  IAPHelperIos.h
//  In NewWindSoft Base
//
//  Created by LongNH on 26/4/15.
//  Copyright (c) 2015 NewWindSoftware. All rights reserved.
//

#import <StoreKit/StoreKit.h>

UIKIT_EXTERN NSString *const IAPHelperProductPurchasedNotification;
@protocol IAPHelperIosDelegate;
typedef void (^RequestProductsCompletionHandler)(BOOL success, NSArray * products);


@interface IAPHelperIos : NSObject

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;
- (void)requestProductsWithCompletionHandler:(RequestProductsCompletionHandler)completionHandler;
- (void)buyProduct:(SKProduct *)product;
- (BOOL)productPurchased:(NSString *)productIdentifier;
- (void)restoreCompletedTransactions;
@property (assign, nonatomic) id<IAPHelperIosDelegate> delegate;
@end
@protocol IAPHelperIosDelegate <NSObject>

-(void)finishPayment;
-(void)errorPayment:(NSString *)error;
@end