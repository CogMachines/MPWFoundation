//
//  MPWSequentialStore.m
//  MPWFoundation
//
//  Created by Marcel Weiher on 9/3/18.
//

#import "MPWSequentialStore.h"
#import "AccessorMacros.h"
#import "MPWGenericReference.h"
#import "MPWByteStream.h"

@implementation MPWSequentialStore

CONVENIENCEANDINIT( store, WithStores:(NSArray*)newStores)
{
    self=[super init];
    self.stores = newStores;
    return self;
}

-(BOOL)isValidResult:result forReference:aReference
{
    return result != nil;
}

-(id)objectForReference:(id<MPWReferencing>)aReference
{
    for ( MPWAbstractStore *s in self.stores) {
        id result=s[aReference];
        if ( [self isValidResult:result forReference:aReference] ) {
            return result;
        }
    }
    return nil;
}

-(void)setObject:(id)theObject forReference:(id<MPWReferencing>)aReference
{
    self.stores.firstObject[aReference]=theObject;
}

-(void)deleteObjectForReference:(id<MPWReferencing>)aReference
{
    [self.stores.firstObject deleteObjectForReference:aReference];
}

-(void)mergeObject:(id)theObject forReference:(id<MPWReferencing>)aReference
{
    [self setObject:[self objectForReference:aReference] forReference:aReference];
    [self.stores.firstObject mergeObject:theObject forReference:aReference];
}

-(void)setSourceStores:(NSArray<MPWStorage> *)stores
{
    self.stores=stores;
}



-(void)graphViz:(MPWByteStream*)aStream
{
    for ( MPWAbstractStore *s in self.stores) {
        [aStream printFormat:@"%@ -> ",[self displayName]];
        [s graphViz:aStream];
    }
}


-(void)dealloc
{
    [_stores release];
    [super dealloc];
}

@end

#import "DebugMacros.h"
#import "MPWDictStore.h"


@implementation MPWSequentialStore(testing)

+(void)testBasicAccessCombinations
{
    MPWDictStore *d1=[MPWDictStore storeWithDictionary:(NSMutableDictionary*)
                      @{
                        @"key1": @"value11",
                        @"key2": @"value21",
                        @"key3": @"value3",

                        }];
    MPWDictStore *d2=[MPWDictStore storeWithDictionary:(NSMutableDictionary*)
                      @{
                        @"key1": @"value12",
                        @"key2": @"value22",
                        @"key4": @"value4",

                        }];
    MPWGenericReference *r1=[MPWGenericReference referenceWithPath:@"key1"];
    MPWGenericReference *r2=[MPWGenericReference referenceWithPath:@"key2"];
    MPWGenericReference *r3=[MPWGenericReference referenceWithPath:@"key3"];
    MPWGenericReference *r4=[MPWGenericReference referenceWithPath:@"key4"];

    MPWSequentialStore *onlyFirst=[self storeWithStores:@[d1]];
    IDEXPECT( onlyFirst[r1], @"value11", @"" );
    IDEXPECT( onlyFirst[r2], @"value21", @"" );
    IDEXPECT( onlyFirst[r3], @"value3", @"" );
    EXPECTNIL( onlyFirst[r4],@"" );

    MPWSequentialStore *firstThenSecond=[self storeWithStores:@[d1,d2]];
    IDEXPECT( firstThenSecond[r1], @"value11", @"" );
    IDEXPECT( firstThenSecond[r2], @"value21", @"" );
    IDEXPECT( firstThenSecond[r3], @"value3", @"" );
    IDEXPECT( firstThenSecond[r4], @"value4", @"" );

    MPWSequentialStore *secondThenFirst=[self storeWithStores:@[d2,d1]];
    IDEXPECT( secondThenFirst[r1], @"value12", @"" );
    IDEXPECT( secondThenFirst[r2], @"value22", @"" );
    IDEXPECT( secondThenFirst[r3], @"value3", @"" );
    IDEXPECT( secondThenFirst[r4], @"value4", @"" );


}

+(void)testStoreOnlyAffectsFirst
{
    MPWDictStore *d1=[MPWDictStore store];
    MPWDictStore *d2=[MPWDictStore storeWithDictionary:(NSMutableDictionary*)
                      @{
                        @"key1": @"value1",
                        
                        }];
    MPWGenericReference *r1=[MPWGenericReference referenceWithPath:@"key1"];
    MPWGenericReference *r2=[MPWGenericReference referenceWithPath:@"key2"];

    MPWSequentialStore *s=[self storeWithStores:@[d1,d2]];
    IDEXPECT( s[r1], @"value1", @"read");
    EXPECTNIL( s[r2],@"" );
    
    s[r2] = @"value2";
    IDEXPECT( s[r2], @"value2", @"read");
    IDEXPECT( d1[r2], @"value2", @"read");
    EXPECTNIL(d2[r2],@"" );

    s[r1] = @"value1-new";
    IDEXPECT( s[r1], @"value1-new", @"read");
    IDEXPECT( d1[r1], @"value1-new", @"d1 has overwritten value");
    IDEXPECT( d2[r1], @"value1", @"d2 still has original value");
}


+(void)testCanDelete
{
    let first = [MPWDictStore store];
    let second = [MPWDictStore store];
    let store = [MPWSequentialStore storeWithStores:@[first,second]];
    store[@"key"] = @"value";
    IDEXPECT( first[@"key"], @"value", @"did store");
    EXPECTNIL( second[@"key"],@"second");

    [store deleteObjectForReference:(id<MPWReferencing>)@"key"];
    EXPECTNIL(store[@"key"],@"after delete" );

}


+testSelectors
{
    return @[
             @"testBasicAccessCombinations",
             @"testStoreOnlyAffectsFirst",
             @"testCanDelete",
             ];
}

@end

