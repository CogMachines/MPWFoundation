//
//  MPWBlockTargetStream.h
//  MPWFoundation
//
//  Created by Marcel Weiher on 4/2/15.
//
//

#import <MPWFoundation/MPWStream.h>

typedef void (^TargetBlock)( id );

@interface MPWBlockTargetStream : MPWStream

-(instancetype)initWithBlock:(TargetBlock)newBlock;
+(instancetype)streamWithBlock:(TargetBlock)newBlock;

@end
