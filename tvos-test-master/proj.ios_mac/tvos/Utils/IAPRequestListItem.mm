//
//  IAPRequestListItem.m
//  menhera
//
//  Created by Phi Dzung on 4/26/15.
//
//

#import "IAPRequestListItem.h"
#import <StoreKit/StoreKit.h>
#import "Contants_iOS.h"

static IAPRequestListItem * _shareInstance;

@implementation IAPRequestListItem

+(IAPRequestListItem *)getInstance {
    if (!_shareInstance) {
        _shareInstance = [[IAPRequestListItem alloc] init];
    }
    return _shareInstance;
}

- (void) registerIAPHelper {
    //[NewWindBaseIAPHelper sharedInstance];
    _buyItem = 0;
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(productPurchased:) name:IAPHelperProductPurchasedNotification object:nil];
}

- (void) requestGetListOfItemPurchase:(NSArray *)arrItems {
    _arrOfProduct = [[NSMutableArray alloc] init];
    [[NewWindBaseIAPHelper sharedInstance:arrItems] requestProductsWithCompletionHandler:^(BOOL success, NSArray *products) {
        if (success) {
            NSLog(@"products: %@", products);
            [_arrOfProduct removeAllObjects];
            [_arrOfProduct addObjectsFromArray:products];
            NSLog(@"GET LIST PRODUCT DONE");
        }
        [[NSNotificationCenter defaultCenter] postNotificationName:@"ShowLoadingHide" object:_arrOfProduct];
    }];
}

- (void)productPurchased:(NSNotification *)notification {
    NSString * productIdentifier = notification.object;
    [_arrOfProduct enumerateObjectsUsingBlock:^(SKProduct *product, NSUInteger idx, BOOL *stop) {
        if ([product.productIdentifier isEqualToString:productIdentifier]) {
            NSLog(@"Reload purchase: %@", product.productIdentifier);
            [[NSNotificationCenter defaultCenter] postNotificationName:@"POST_BUY_ITEM_SUCCES" object:[NSNumber numberWithInt:_buyItem]];
            *stop = YES;
        }
    }];
}

- (void)provideContentForProductIdentifierDidFinished:(NSString *)productIdentifier {
    [_arrOfProduct enumerateObjectsUsingBlock:^(SKProduct *product, NSUInteger idx, BOOL *stop) {
        if ([product.productIdentifier isEqualToString:productIdentifier]) {
            NSLog(@"Reload purchase: %@", product.productIdentifier);
            [[NSNotificationCenter defaultCenter] postNotificationName:@"POST_BUY_ITEM_SUCCES" object:[NSNumber numberWithInt:_buyItem]];
            *stop = YES;
        }
    }];
}

- (void) buyItem:(int) num {
    if (_arrOfProduct.count) {
        _buyItem = num;
        SKProduct *product = _arrOfProduct[num];
        NSLog(@"Buying %@...", product.productIdentifier);
        [[NewWindBaseIAPHelper sharedInstance:_arrOfProduct] buyProduct:product];
    }
}

- (void) restorePurchase
{
    [[NewWindBaseIAPHelper sharedInstance:_arrOfProduct] restoreCompletedTransactions];
}

- (bool) isPurchased
{
    return [[NewWindBaseIAPHelper sharedInstance:_arrOfProduct] productPurchased:INAPP_ITEM5];
}

@end
