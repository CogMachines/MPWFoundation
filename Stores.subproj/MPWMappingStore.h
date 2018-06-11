//
//  MPWMappingStore.h
//  MPWFoundation
//
//  Created by Marcel Weiher on 5/28/18.
//

#import <MPWFoundation/MPWAbstractStore.h>

@interface MPWMappingStore : MPWAbstractStore

@property (nonatomic, strong) NSObject<MPWStorage,MPWHierarchicalStorage>* source;

-(instancetype)initWithSource:(NSObject<MPWStorage,MPWHierarchicalStorage>*)newSource;
+(instancetype)storeWithSource:(NSObject<MPWStorage,MPWHierarchicalStorage>*)newSource;

-(MPWReference*)mapReference:(MPWReference*)aReference;
-mapRetrievedObject:anObject;
-mapObjectToStore:anObject;

@end