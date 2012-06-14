//
//  MGWU.h
//  CrossPromoWidget
//
//  Created by Ashu Desai on 4/7/12.
//  Copyright (c) 2012 makegameswithus inc. All rights reserved.
//
//  Contains open source code from Crashlytics, Inc. (SecureUDID), Matej Bukovinski (MBProgressHUD), Stig Brautaset (SBJson), Facebook (FacebookConnect iOS), thank you to all!

#import <UIKit/UIKit.h>

@protocol MBProgressHUDDelegate;

@interface MGWU : UIViewController <UIWebViewDelegate, MBProgressHUDDelegate>


/////////////////////////////////////////////////////////////////////////////////
//
//General Setup:
//
//In XCode left bar (project navigator), go to Projectfiles-iOS -> Resources -> Info.plist
//Change the field corresponding to Bundle identifier to "com.yourname.appname" where yourname is your name and appname is the name of your app.
//Make up a secret key, for example, mine is "DesaiAshu", yours can also be your makegameswithus account name, or something else you choose.
//Make it unique and hard to guess, no special characters.
//Do not share your Bundle identifier or secret key with anyone, as they can use it to hack your high scores.
//Email ashu@makegameswith.us with your Bundle identifier and secret key (note: these are case sensitive) and whether your game uses high scores or low scores
//
//Unzip MGWU.zip
//Drag MGWU into your project, make sure you select copy files and add them to target!
//
//In AppDelegate.m:
//At the top add the line:
//#import "MGWU.h"
//In the method initializationComplete add the line:
//[MGWU loadMGWU:@"DesaiAshu"];
//Where instead of DesaiAshu you use your own secret key
+ (void)loadMGWU:(NSString*)dev;


/////////////////////////////////////////////////////////////////////////////////
//
//More Games:
//
//In the scene you use for your menu, at the top add the line:
//#import "MGWU.h"
//When the More Games button is clicked include the line:
//[MGWU display];
//Make sure this is only called once when the button is pressed
+ (void)display;


/////////////////////////////////////////////////////////////////////////////////
//
//Global High Scores:
//
//To submit a new high score to a leaderboard by using the line:
//[MGWU submitHighScore:10 byPlayer:@"ashu" forLeaderboard:@"level1"];
//Where level1 is whatever you want to name the leaderboard
//You probably want to allow users to input their name when they get a high score.
//If you call this method again with a lower score for the level, it will be ignored. With a higher score, it will replace the previous entry on the server.
+ (void)submitHighScore:(int)score byPlayer:(NSString*)player forLeaderboard:(NSString*)leaderboard;


//To retrieve scores, there are two parts, first a line of code that begins downloading the high scores, then a method which is called once download is complete.
//To begin download, use this line of code:
//[MGWU getHighScoresForLeaderboard:@"level1" withCallback:@selector(receivedScores:) onTarget:self]; 
//Then in the same class, add the following method:
//- (void)receivedScores:(NSArray*)scoreArray
//{
//	//Do stuff with scores in here! Display them!
//}
//
//scoreArray will be an array with up to 100 high scores. If there is no connection to the internet, scoreArray will be nil.
//The first element in the array will be a dictionary containing info on the local players high score with the following key value pairs:
//Key: @"name"
//Value: (NSString) name of local player, this will be @"Player" if no score has been submitted
//Key: @"score"
//Value: (NSNumber) high score, this will be 0 if no score has been submitted
//Key: @"rank"
//Value: (NSNumber) rank, this will be the number of players if no score has been submitted
//
//The rest of the elements in the array will be dictionaries containing the top scores with the following key value pairs:
//Key: @"name"
//Value: (NSString) name of player
//Key: @"score"
//Value: (NSNumber) high score
//
//Example of accessing this would be:
//for (int i = 1; i < [scoreArray count]; i++)
//{
//	NSDictionary *player = [scoreArray objectAtIndex:i];
//	NSString *name = [player objectForKey:@"name"];
//	NSNumber *s = [player objectForKey:@"score"];
//	int score = [s intValue];
//	//Do something with name and score
//}
+ (void)getHighScoresForLeaderboard:(NSString*)l withCallback:(SEL)m onTarget:(id)t;

//If you've created different levels you can retrieve multiple high score lists at once using the following code
//NSArray *leaderboards = [[NSArray alloc] initWithObjects:@"level1", @"level2", nil];
//Where level1 and level2 are the names you chose for the leaderboards
//To begin download use the line:
//[MGWU getHighScoresForMultipleLeaderboards:leaderboards withCallback:@selector(receivedAllScores:) onTarget:self];
//
//Then in the same class, add the following method:
//- (void)receivedAllScores:(NSDictionary*)scoreDictionary
//{
//	//Do stuff with scores in here! Display them!
//}
//
//Example of accessing this would be:
//NSArray *scoreArray1 = [scoreDictionary objectForKey:@"level1"];
//NSArray *scoreArray2 = [scoreDictionary objectForKey:@"level2"];
//for (int i = 1; i < [scoreArray1 count]; i++)
//{
//	NSDictionary *player = [scoreArray objectAtIndex:i];
//	NSString *name = [player objectForKey:@"name"];
//	NSNumber *s = [player objectForKey:@"score"];
//	int score = [s intValue];
//	//Do something with name and score for level1
//}
//for (int i = 1; i < [scoreArray2 count]; i++)
//{
//	NSDictionary *player = [scoreArray objectAtIndex:i];
//	NSString *name = [player objectForKey:@"name"];
//	NSNumber *s = [player objectForKey:@"score"];
//	int score = [s intValue];
//	//Do something with name and score for level2
//}
//Where level1 and level2 are the names you chose for the leaderboards
+ (void)getHighScoresForMultipleLeaderboards:(NSArray*)l withCallback:(SEL)m onTarget:(id)t;


/////////////////////////////////////////////////////////////////////////////////
//
//Analytics:
//
//Basic analytics of opening and closing the app are included by default.
//To log any additional events (such as completing the tutorial or completing a level) use this line of code:
//[MGWU logEvent:@"level1complete"];
//Where level1complete is replaced by any other event name, don't use special characters
+ (void)logEvent:(NSString*)eventName;

//Params is a dictionary of parameters you want to log
+ (void)logEvent:(NSString*)eventName withParams:(NSDictionary*)params;


/////////////////////////////////////////////////////////////////////////////////
//
//Methods for Push Notifications:
//
//Add these methods to AppDelegate.m:
//- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)tokenId {
//	[MGWU registerForPush:tokenId];
//}
//
//- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
//    [MGWU gotPush:userInfo];
//}
//
//
//- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error{
//    [MGWU failedPush:error];
//}
+ (void)registerForPush:(NSData *)tokenId;
+ (void)gotPush:(NSDictionary *)userInfo;
+ (void)failedPush:(NSError *)error;

@end
