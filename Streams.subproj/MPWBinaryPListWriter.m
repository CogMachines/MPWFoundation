//
//  MPWBinaryPListWriter.m
//  MPWFoundation
//
//  Created by Marcel Weiher on 9/14/13.
//
//

#import "MPWBinaryPListWriter.h"
#import "AccessorMacros.h"
#import "MPWIntArray.h"

@implementation MPWBinaryPListWriter

objectAccessor(MPWIntArray, offsets, setOffsets)
objectAccessor(NSMutableArray, indexStack, setIndexStack)
objectAccessor(NSMutableArray, reserveIndexes, setResrveIndexes)
objectAccessor(MPWIntArray, currentIndexes, setCurrentIndexes)

-(id)initWithTarget:(id)aTarget
{
    self=[super initWithTarget:aTarget];
    [self setOffsets:[MPWIntArray array]];
    [self setIndexStack:[NSMutableArray array]];
    [self setResrveIndexes:[NSMutableArray array]];
    return self;
}


-(void)writeIntArray:(MPWIntArray*)array numBytes:(int)numBytes
{
    for (int i=0;i<[array count];i++) {
        NSLog(@"write array[%d]=%d",i,[array integerAtIndex:i]);
        [self writeInteger:[array integerAtIndex:i] numBytes:numBytes];
    }
}



-(MPWIntArray*)getIndexes
{
    MPWIntArray *result=[reserveIndexes lastObject];
    if ( result ) {
        [reserveIndexes removeLastObject];
    } else {
        result=[MPWIntArray array];
    }
    return result;
}

-(void)pushIndexStack
{
    if ( currentIndexes) {
        [indexStack addObject:currentIndexes];
    }
    [self setCurrentIndexes:[self getIndexes]];
}

-(MPWIntArray*)popIndexStack
{
    id lastObject=[currentIndexes retain];
    if ( lastObject) {
        [reserveIndexes addObject:lastObject];
    }
    id fromStack=[indexStack lastObject];
    [self setCurrentIndexes:fromStack];
    if ( fromStack) {
        [indexStack removeLastObject];
    }
    return [lastObject autorelease];
}

-(void)addIndex:(int)anIndex
{
    [currentIndexes addInteger:anIndex];
}

-(void)beginArray
{
    [self pushIndexStack];
    NSLog(@"currentIndexes after beginArray: %@",currentIndexes);
}

-(void)endArray
{
    @autoreleasepool {
        unsigned char header=0xa0;
        MPWIntArray *arrayIndexes=[self popIndexStack];
        NSLog(@"array indexes after popping: %@",arrayIndexes);
      int numOffsets=[arrayIndexes count];
        [self _recordByteOffset];
        if ( numOffsets <= 15 ) {
            header=header | numOffsets;
            TARGET_APPEND(&header, 1);
        } else {
            header=header | 0xf;
            TARGET_APPEND(&header, 1);
            [self writeInteger:numOffsets numBytes:4];
        }
        NSLog(@"write array indexes: %@",arrayIndexes);
        [self writeIntArray:arrayIndexes numBytes:[self inlineOffsetEntryByteSize]];
        NSLog(@"done with endArray");
    }
}


-(void)writeHeader
{
    TARGET_APPEND("bplist00", 8);
}

-(void)_recordByteOffset
{
    [currentIndexes addInteger:[offsets count]];
    [offsets addInteger:[self length]];
}

-(int)currentObjectIndex
{
    return [offsets count];
}

-(void)writeInteger:(long)anInt numBytes:(int)numBytes
{
    unsigned char buffer[16];
    for (int i=numBytes-1;i>=0;i--) {
        buffer[i]=anInt & 0xff;
        anInt>>=8;
    }
    TARGET_APPEND(buffer, numBytes);
}

-(void)writeAndRecordTaggedInteger:(long)anInt
{
    unsigned char buffer[16];
    int log2ofNumBytes=2;
    int numBytes=4;
    [self _recordByteOffset];
    buffer[0]=0x10 + log2ofNumBytes;
    for (int i=numBytes-1;i>=0;i--) {
        buffer[i+1]=anInt & 0xff;
        anInt>>=8;
    }
    TARGET_APPEND(buffer, numBytes+1);
}

-(int)offsetTableEntryByteSize
{
    return 4;
}

-(int)inlineOffsetEntryByteSize
{
    return 4;
}

-(void)writeOffsetTable
{
    offsetOfOffsetTable=[self length];
    NSLog(@"offsets: %@",offsets);
    [self writeIntArray:offsets numBytes:[self offsetTableEntryByteSize]];
}

-(long)count
{
    return [offsets count];
}

-(long)rootObjectIndex
{
    return [self currentObjectIndex]-1;
}

-(void)writeTrailer
{
    TARGET_APPEND("\0\0\0\0\0\0", 6);
    [self writeInteger:[self offsetTableEntryByteSize] numBytes:1];
    [self writeInteger:[self inlineOffsetEntryByteSize] numBytes:1];
    [self writeInteger:[self count] numBytes:8]; // num objs in table
    [self writeInteger:[self rootObjectIndex] numBytes:8];       // root
    [self writeInteger:offsetOfOffsetTable numBytes:8];       // root
}

-(void)flush
{
    NSLog(@"writeOffsetTable: %@",offsets);
    [self writeOffsetTable];
    NSLog(@"writeTrailer");
    [self writeTrailer];
}

@end


#import "DebugMacros.h"

@implementation MPWBinaryPListWriter(tests)

+_plistForStream:(MPWBinaryPListWriter*)aStream
{
    NSData *d=[aStream target];
    id plist=[NSPropertyListSerialization propertyListWithData:d options:0 format:NULL error:nil];
    return plist;
}

+(void)testWriteHeader
{
    MPWBinaryPListWriter *writer=[self stream];
    INTEXPECT( [[writer target] length],0,@"data written before");
    INTEXPECT([writer length], 0, @"bytes written before");
    [writer writeHeader];
    INTEXPECT([writer length], 8, @"bytes written after header");
}


+(void)testWriteSingleIntegerValue
{
    MPWBinaryPListWriter *writer=[self stream];
    [writer writeHeader];
    [writer writeAndRecordTaggedInteger:42];
    INTEXPECT([[writer offsets] count], 1, @"should have recored an offset");
    INTEXPECT([[writer offsets] integerAtIndex:0], 8, @"offset of first object");
    [writer flush];
//    [[writer target] writeToFile:@"/tmp/fourtytwo.plist" atomically:YES];
    NSNumber *n=[self _plistForStream:writer];
    INTEXPECT([n intValue], 42, @"encoded plist value");
}


+(void)testWriteArrayWithTwoElements
{
    MPWBinaryPListWriter *writer=[self stream];
    [writer writeHeader];
    [writer beginArray];
    [writer writeAndRecordTaggedInteger:31];
    [writer writeAndRecordTaggedInteger:42];
    [writer endArray];
    [writer flush];
    [[writer target] writeToFile:@"/tmp/fourtytwo-array.plist" atomically:YES];
    NSArray *a=[self _plistForStream:writer];
    NSLog(@"a: %@",a);
    INTEXPECT([a count], 2, @"array with 2 values");
    INTEXPECT([[a objectAtIndex:0] intValue], 31, @"array with 2 values");
    INTEXPECT([[a lastObject] intValue], 42, @"array with 2 values");
}


+testSelectors
{
    return @[
             @"testWriteHeader",
             @"testWriteSingleIntegerValue",
             @"testWriteArrayWithTwoElements",
             @"testWriteNestedArray",
             ];
}

@end

