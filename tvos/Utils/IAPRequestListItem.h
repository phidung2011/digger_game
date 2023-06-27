//
//  IAPRequestListItem.h
//  menhera
//
//  Created by NGOCDIEP on 4/26/15.
//
//

#import <Foundation/Foundation.h>
#include "NewWindBaseIAPHelper.h"

@interface IAPRequestListItem : NSObject
{
    NSMutableArray *_arrOfProduct;
    int _buyItem;
}
+(IAPRequestListItem *)getInstance;
- (void) registerIAPHelper;
- (void) requestGetListOfItemPurchase:(NSArray *)arrItems;
- (void) buyItem:(int) num;
- (void) restorePurchase;
- (bool) isPurchased;
@end
