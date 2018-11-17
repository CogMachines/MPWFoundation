/* MPWScanner.h Copyright (c) 1998-2017 by Marcel Weiher, All Rights Reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in
	the documentation and/or other materials provided with the distribution.

	Neither the name Marcel Weiher nor the names of contributors may
	be used to endorse or promote products derived from this software
	without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.

*/


#import <Foundation/Foundation.h>
#import <MPWFoundation/AccessorMacros.h>
#import <MPWFoundation/MPWObject.h>

typedef id (*IDIMP0)(id, SEL);


@interface MPWScanner : NSObject
{
    NSData *data;
    id	dataSource;
    const char *start,*end,*pos,*probe;
    NSMutableDictionary		*handlers;
    id defaultHandler;
    IDIMP0	  charSwitch[260];
    id textCache;
    IMP0 getObject;
    IMP0 initData;
    IMPINT1 makeText;
    IMP1 setScanPosition;
    long	headRoom;
    id bufferCache;
}
idAccessor_h( dataSource, setDataSource )
-sourceNextObject;
-(void)_initCharSwitch;			//---	only for subclasses
+(NSArray*)scan:(NSData*)data;
+scannerWithDataSource:aDataSource;
+scannerWithData:(NSData*)aData;
-initWithData:(NSData*)aData;
-(void)addData:(NSData*)newData;
-initWithDataSource:aDataSource;
-(void)addHandler:aHandler forKey:(NSString*)aKey;
-handlerForKey:(NSString*)aKey;
-makeText:(long)length;
-makeString:(long)length;
-(void)skipTo:(NSString*)aString;
-(void)skipEOL;
-nextLine;
-nextObject;


-(void)setScanPosition:(const  char*)newPos;
-(const char*)position;
-(long)bufLen;
-(BOOL)reserve:(long)roomNeeded;
-(long)offset;

#define UPDATEPOSITION(newPos)		setScanPosition(self, @selector(setScanPosition:), (void*)newPos )
#define MAKE_PROBE_CURRENT		UPDATEPOSITION(probe)
#define SCANINBOUNDS(ptr)		((ptr)<end)
#define RESERVE(room)			((pos+(room)<end) ? YES : [self reserve:(room)])

@end

@interface NSObject(TestSupport)

+(void)testFile:(NSString*)filename;
+(void)test:(NSString*)filename;
+(void)test;

@end
