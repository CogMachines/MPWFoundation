/* MPWFoundation.h Copyright (c) 1998-2017 by Marcel Weiher, All Rights Reserved.


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
#import "MPWFoundation/AccessorMacros.h"
#import "MPWFoundation/CodingAdditions.h"
#import "MPWFoundation/DebugMacros.h"
#import "MPWFoundation/MPWObject.h"
#import "MPWFoundation/NSInvocationAdditions.h"
#import "MPWFoundation/MPWFastInvocation.h"
#import "MPWFoundation/MPWObjectCache.h"
#import "MPWFoundation/MPWBlockInvocation.h"
#import "MPWFoundation/MPWRUsage.h"
#import "MPWFoundation/MPWMessageCatcher.h"
#import "MPWFoundation/MPWBoxerUnboxer.h"
#import "MPWFoundation/MPWRuntimeAdditions.h"
#import "MPWFoundation/MPWMsgExpression.h"
#import "MPWFoundation/NSStringAdditions.h"
#import "MPWFoundation/NSObjectAdditions.h"
#import "MPWFoundation/MPWNumber.h"
#import "MPWFoundation/MPWFloat.h"
#import "MPWFoundation/MPWInteger.h"
#import "MPWFoundation/MPWValueAccessor.h"
#import "MPWFoundation/MPWObject_fastrc.h"

#import "MPWFoundation/MPWBlockInvocable.h"
#import "MPWFoundation/NSNil.h"



#import "MPWFoundation/MPWWriteStream.h"
#import "MPWFoundation/MPWFilter.h"
#import "MPWFoundation/MPWArrayFlattenStream.h"
#import "MPWFoundation/MPWFlattenStream.h"
#import "MPWFoundation/MPWByteStream.h"
#import "MPWFoundation/MPWPipeline.h"
#import "MPWFoundation/MPWThreadSwitchStream.h"
#import "MPWFoundation/MPWConvertFromJSONStream.h"
#import "MPWFoundation/MPWJSONWriter.h"
#import "MPWFoundation/MPWObjectCreatorStream.h"
#import "MPWFoundation/MPWURLFetchStream.h"
#import "MPWFoundation/MPWURLStreamingStream.h"
#import "MPWFoundation/MPWASCII85Stream.h"
#import "MPWFoundation/MPWURLCall2StoreStream.h"
#import "MPWFoundation/MPWNotificationStream.h"
#import "MPWFoundation/MPWMapFilter.h"

#import "MPWFoundation/MPWBlockTargetStream.h"
#import "MPWFoundation/MPWCombinerStream.h"
#import "MPWFoundation/MPWDelayStream.h"
#import "MPWFoundation/MPWURLCall.h"
#import "MPWFoundation/MPWSocketStream.h"
#import "MPWFoundation/MPWScatterStream.h"
#import "MPWFoundation/MPWActionStreamAdapter.h"
#import "MPWFoundation/MPWBinaryPListWriter.h"
#import "MPWFoundation/MPWPListBuilder.h"
#import "MPWFoundation/MPWLZWStream.h"
#import "MPWFoundation/MPWFDStreamSource.h"
#import "MPWFoundation/MPWExternalFilter.h"
#import "MPWFoundation/MPWRESTCopyStream.h"


#import "MPWFoundation/NSThreadWaiting.h"
#import "MPWFoundation/MPWFuture.h"
#import "MPWFoundation/MPWTrampoline.h"
#import "MPWFoundation/MPWIgnoreTrampoline.h"
#import "MPWFoundation/NSObjectFiltering.h"
#import "MPWFoundation/MPWEnumeratorEnumerator.h"
#import "MPWFoundation/MPWEnumeratorSource.h"
#import "MPWFoundation/MPWRealArray.h"
#import "MPWFoundation/MPWUniqueString.h"
#import "MPWFoundation/MPWUShortArray.h"
#import "MPWFoundation/MPWFakedReturnMethodSignature.h"
#import "MPWFoundation/MPWKVCSoftPointer.h"
#import "MPWFoundation/MPWSoftPointerProxy.h"
#import "MPWFoundation/NSArrayFiltering.h"

#if !__has_feature(objc_arc)
#import "MPWFoundation/MPWObjectCache.h"
#endif

#import "MPWFoundation/MPWSubData.h"
#import "MPWFoundation/MPWBinaryPlist.h"
#import "MPWFoundation/MPWDelimitedTable.h"
#import "MPWFoundation/MPWSmallStringTable.h"
#import "MPWFoundation/MPWCaseInsensitiveSmallStringTable.h"
#import "MPWFoundation/MPWScanner.h"
#import "MPWFoundation/MPWPoint.h"
#import "MPWFoundation/MPWRect.h"
#import "MPWFoundation/NSDictAdditions.h"
#import "MPWFoundation/MPWIdentityDictionary.h"
#import "MPWFoundation/MPWObjectReference.h"

#import "MPWFoundation/NSThreadInterThreadMessaging.h"
#import "MPWFoundation/bytecoding.h"
#import "MPWFoundation/NSRectAdditions.h"
#import "MPWFoundation/NSBundleConveniences.h"
#import "MPWFoundation/MPWIntArray.h"
#import "MPWFoundation/NSNumberArithmetic.h"

#import "MPWFoundation/NSObject+MPWNotificationProtocol.h"

#import "MPWFoundation/MPWAbstractStore.h"
#import "MPWFoundation/MPWBinding.h"
#import "MPWFoundation/MPWCachingStore.h"
#import "MPWFoundation/MPWCompositeStore.h"
#import "MPWFoundation/MPWDictStore.h"
#import "MPWFoundation/MPWDiskStore.h"
#import "MPWFoundation/MPWGenericReference.h"
#import "MPWFoundation/MPWLoggingStore.h"
#import "MPWFoundation/MPWMappingStore.h"
#import "MPWFoundation/MPWMergingStore.h"
#import "MPWFoundation/MPWPathRelativeStore.h"
#import "MPWFoundation/MPWReference.h"
#import "MPWFoundation/MPWSequentialStore.h"
#import "MPWFoundation/MPWSwitchingStore.h"
#import "MPWFoundation/MPWURLBasedStore.h"
#import "MPWFoundation/MPWURLReference.h"
#import "MPWFoundation/MPWWriteBackCache.h"


