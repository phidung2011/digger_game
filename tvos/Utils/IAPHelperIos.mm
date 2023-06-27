//
//  IAPHelperIos.m
//  In NewWindSoft Base
//
//  Created by LongNH on 26/4/15.
//  Copyright (c) 2015 NewWindSoftware. All rights reserved.
//

// 1
#import "IAPHelperIos.h"
#import <StoreKit/StoreKit.h>
#include "PlayGameSingleton.h"
#include "NativeUtils.h"
#include "GameSingleton.h"
#include "Constants.h"
#import "Contants_iOS.h"

NSString *const IAPHelperProductPurchasedNotification = @"IAPHelperProductPurchasedNotification";

// 2
@interface IAPHelperIos () <SKProductsRequestDelegate, SKPaymentTransactionObserver>
@end

// 3
@implementation IAPHelperIos {
    SKProductsRequest * _productsRequest;
    RequestProductsCompletionHandler _completionHandler;
    
    NSSet * _productIdentifiers;
    NSMutableSet * _purchasedProductIdentifiers;
}

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers {
    
    if ((self = [super init])) {
        
        // Store product identifiers
        _productIdentifiers = productIdentifiers;
        
        // Check for previously purchased products
        _purchasedProductIdentifiers = [[NSMutableSet alloc] init];
        for (NSString * productIdentifier in _productIdentifiers) {
            BOOL productPurchased = [[NSUserDefaults standardUserDefaults] boolForKey:productIdentifier];
            if (productPurchased) {
                [_purchasedProductIdentifiers addObject:productIdentifier];
                NSLog(@"Previously purchased: %@", productIdentifier);
            } else {
                NSLog(@"Not purchased: %@", productIdentifier);
            }
        }
        
        // Add self as transaction observer
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        
    }
    return self;
    
}

- (void)requestProductsWithCompletionHandler:(RequestProductsCompletionHandler)completionHandler {
    // 1
    _completionHandler = [completionHandler copy];
    
    // 2
    _productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers];
    _productsRequest.delegate = self;
    [_productsRequest start];
    
}

- (BOOL)productPurchased:(NSString *)productIdentifier {
    return [_purchasedProductIdentifiers containsObject:productIdentifier];
}

- (void)buyProduct:(SKProduct *)product {
    
    NSLog(@"Buying %@...", product.productIdentifier);
    
    SKPayment * payment = [SKPayment paymentWithProduct:product];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    
}

#pragma mark - SKProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
    NSLog(@"Loaded list of products...");
    _productsRequest = nil;
    
    NSArray * skProducts = response.products;
    for (SKProduct * skProduct in skProducts) {
        NSLog(@"Found product: %@ %@ %0.2f",
              skProduct.productIdentifier,
              skProduct.localizedTitle,
              skProduct.price.floatValue);
    }
    
    _completionHandler(YES, skProducts);
    _completionHandler = nil;
    
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    
    NSLog(@"Failed to load list of products.");
    _productsRequest = nil;
    
    _completionHandler(NO, nil);
    _completionHandler = nil;
    
}

#pragma mark SKPaymentTransactionOBserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    
    for (SKPaymentTransaction * transaction in transactions) {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
            default:
                break;
        }
    };
    
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    NSLog(@"completeTransaction...");
    
    NSString* productId = transaction.payment.productIdentifier;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"PaymentSuccsess" object:nil userInfo:nil];
    
    [self provideContentForProductIdentifier:productId];
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    NSLog(@"....you just bought: %@",transaction.payment.productIdentifier);
    
    if([productId isEqualToString:INAPP_ITEM5])
    {
        NativeUtils::updateData(USER_REMOVE_ADS, 1);
    }
    else if ([productId isEqualToString:INAPP_ITEM1])
    {
        int c = NativeUtils::getDataInt(USER_COIN);
        int coin = 500 + c;
        NativeUtils::updateData(USER_COIN, coin);
    }
    else if ([productId isEqualToString:INAPP_ITEM2])
    {
        int c = NativeUtils::getDataInt(USER_COIN);
        int coin = 1000 + c;
        NativeUtils::updateData(USER_COIN, coin);
    }
    else if ([productId isEqualToString:INAPP_ITEM3])
    {
        int c = NativeUtils::getDataInt(USER_COIN);
        int coin = 2000 + c;
        NativeUtils::updateData(USER_COIN, coin);
    }
    else if ([productId isEqualToString:INAPP_ITEM4])
    {
        int c = NativeUtils::getDataInt(USER_COIN);
        int coin = 5000 + c;
        NativeUtils::updateData(USER_COIN, coin);
    }
    
    
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    NSLog(@"restoreTransaction...");
    
    [self provideContentForProductIdentifier:transaction.originalTransaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
//    GameSingleton::getInstance()->_coin = PlayGameSingleton::sharedInstance()->_coins + GameSingleton::getInstance()->_coin;
//    NativeUtils::updateData(USER_COIN, GameSingleton::getInstance()->_coin);
    NSLog(@"failedTransaction...");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        NSLog(@"Transaction error: %@", transaction.error.localizedDescription);
    }
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void)provideContentForProductIdentifier:(NSString *)productIdentifier {
    
    [_purchasedProductIdentifiers addObject:productIdentifier];
    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:productIdentifier];
    [[NSUserDefaults standardUserDefaults] synchronize];
    [[NSNotificationCenter defaultCenter] postNotificationName:IAPHelperProductPurchasedNotification object:productIdentifier userInfo:nil];
}

- (void)restoreCompletedTransactions {
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

@end