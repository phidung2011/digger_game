/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#include "SettingGame.h"
#import "cocos2d.h"
#import "CCEAGLView-tvos.h"
#include "GameSingleton.h"
#include "MainGameScene.h"
#import <Parse/Parse.h>
#import "ParseUtils.h"
#import "PlayGameSingleton.h"

@implementation RootViewController


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reachabilityChanged:) name:kReachabilityChangedNotification object:nil];
        self.internetReachability = [Reachability reachabilityForInternetConnection];
        [self.internetReachability startNotifier];

    }
    
    return self;
}

- (void) reachabilityChanged:(NSNotification *)note
{
    Reachability* curReach = [note object];
    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
}

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	
	/*// Create a view of the standard size at the top of the screen.
	// Available AdSize constants are explained in GADAdSize.h.
	bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
	
	// Specify the ad unit ID.
	bannerView.adUnitID = @"ca-app-pub-2031028175261677/6947343943";
	
	// Let the runtime know which UIViewController to restore after taking
	// the user wherever the ad goes and add it to the view hierarchy.
	bannerView.rootViewController = self;
	[self.view addSubview:bannerView];
	
	// Initiate a generic request to load it with an ad.
	[bannerView loadRequest:[GADRequest request]];*/
    
//    UITapGestureRecognizer *tapGestureRec = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTap:)];
//    tapGestureRec.allowedPressTypes = @[@(UIPressTypeMenu)];
//    [self.view addGestureRecognizer:tapGestureRec];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	
	//[bannerView release];

    [super dealloc];
}

//- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
//    switch ([alertView tag]) {
//        case 1:
//            if (buttonIndex == 1)
//            {
//                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
//            }
//            break;
//        case 2:
//            PlayGameSingleton::sharedInstance()->reload();
//            break;
//    }
//    
//}

- (void) showAlertConnection
{
    UIAlertController * alert=   [UIAlertController
                                  alertControllerWithTitle:@"Connection error"
                                  message:@"Unable to connect with the server. Please check your internet connection and try again"
                                  preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* ok = [UIAlertAction
                         actionWithTitle:@"OK"
                         style:UIAlertActionStyleDefault
                         handler:^(UIAlertAction * action)
                         {
                             [alert dismissViewControllerAnimated:YES completion:nil];
                             
                             
                             
                             PlayGameSingleton::sharedInstance()->reload();
                             
                         }];
    
    
    [alert addAction:ok];
    
    [self presentViewController:alert animated:YES completion:nil];
    
    
    
    
//    UIAlertView *alerView = [[UIAlertView alloc] initWithTitle:@"Connection error" message:@"Unable to connect with the server. Please check your internet connection and try again" delegate:self cancelButtonTitle:@"Try again" otherButtonTitles:nil];
//    
//    [alerView setTag:2];
//    [alerView show];
}

-(void)pressesBegan:(NSSet*)presses withEvent:(UIPressesEvent *)event {
    
    UIPress* p = [presses anyObject];
//
    if (GameSingleton::getInstance()->isStartGame && cocos2d::Director::getInstance()->getEventDispatcher()->isEnabled() && p.type == UIPressTypeMenu)
    {
        // comment this if you don't want menu button to close the app
        [super pressesBegan:presses withEvent:event];
    }
//
//    switch (p.type) {
//        case UIPressTypeDownArrow:
//            GameSingleton::getInstance()->isTouchDown = true;
//            break;
//        default:
//            GameSingleton::getInstance()->isTouchDown = false;
//            break;
//    }
}

-(void)pressesEnded:(NSSet*)presses withEvent:(UIPressesEvent *)event {
    
    UIPress* p = [presses anyObject];
    
    if (GameSingleton::getInstance()->isStartGame && cocos2d::Director::getInstance()->getEventDispatcher()->isEnabled() && p.type == UIPressTypeMenu)
    {
        // comment this if you don't want menu button to close the app
        [super pressesEnded:presses withEvent:event];
    }
    
    if (GameSingleton::getInstance()->inSetting)
    {
        switch (p.type) {
            case UIPressTypeDownArrow:
                SettingGame::getInstance()->down();
                break;
            case UIPressTypeUpArrow:
                SettingGame::getInstance()->up();
                break;
            case UIPressTypeLeftArrow:
                SettingGame::getInstance()->left();
                break;
            case UIPressTypeRightArrow:
                SettingGame::getInstance()->right();
                break;
            default:
                break;
        }
    }


}

@end
