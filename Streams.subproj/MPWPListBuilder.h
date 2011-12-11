//
//  MPWPListBuilder.h
//  MPWFoundation
//
//  Created by Marcel Weiher on 1/3/11.
//  Copyright 2011 metaobject ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MPWPlistStreaming

-(void)beginArray;
-(void)endArray;
-(void)beginDict;
-(void)endDict;
-(void)writeKey:aKey;
-(void)writeString:aString;
-(void)writeNumber:aNumber;
-(void)writeObject:anObject forKey:aKey;


@end



@interface MPWPListBuilder : NSObject <MPWPlistStreaming> {
	id	plist;
	id  containerStack[1000];
	id  *tos;
	id	key;
}

-result;

@end