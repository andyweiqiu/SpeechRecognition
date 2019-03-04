//
//  EduSpeechRecognizer.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EduSpeechRecognitionTask;
@class EduSpeechRecognitionRequest;
@class EduSpeechRecognitionResult;

@protocol EduSpeechRecognitionTaskDelegate;

@interface EduSpeechRecognizer : NSObject

// Recognize speech utterance with a request
// repeatedly with partial results, then finally with a final result or an error.
- (EduSpeechRecognitionTask *)recognitionTaskWithRequest:(EduSpeechRecognitionRequest *)request
                                           resultHandler:(void (^)(EduSpeechRecognitionResult * __nullable result, NSError * __nullable error))resultHandler;

// Recognize a custom request with with a delegate
// The delegate will be weakly referenced by the returned task
- (EduSpeechRecognitionTask *)recognitionTaskWithRequest:(EduSpeechRecognitionRequest *)request
                                                delegate:(id <EduSpeechRecognitionTaskDelegate>)delegate;

- (void)endRecognition;

@end
