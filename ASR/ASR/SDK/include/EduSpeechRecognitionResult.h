//
//  EduSpeechRecognitionResult.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EduTranscription;

// A recognized utterance, corresponding to a segment of recorded audio with speech and containing one or more transcriptions hypotheses
@interface EduSpeechRecognitionResult : NSObject

@property (nullable, nonatomic, readonly, strong) EduTranscription *bestTranscription;

// Hypotheses for possible transcriptions, sorted in decending order of confidence (more likely first)
@property (nonatomic, readonly, strong) NSArray<EduTranscription *> *transcriptions;

// True if the hypotheses will not change; speech processing is complete.
@property (nonatomic, readonly, getter=isFinal) BOOL final;

// The response time, from no audio input to final result
@property (nonatomic, readonly, assign) NSTimeInterval endSpeechToFinalResultTime;

@end
