//
//  EduSpeechRecognitionTask.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EduSpeechRecognitionRequest.h"

typedef NS_ENUM(NSUInteger, EduSpeechRecognitionTaskState){
    EduSpeechRecognitionTaskStateStarting = 0,       // Speech processing (potentially including recording) has not yet begun
    EduSpeechRecognitionTaskStateRunning = 1,        // Speech processing (potentially including recording) is running
    EduSpeechRecognitionTaskStateFinishing = 2,      // No more audio is being recorded, but more recognition results may arrive
    EduSpeechRecognitionTaskStateCanceling = 3,      // No more recognition reuslts will arrive, but recording may not have stopped yet
    EduSpeechRecognitionTaskStateCompleted = 4,      // No more results will arrive, and recording is stopped.
};

@class EduSpeechRecognitionTask;
@class EduSpeechRecognitionResult;
@class EduTranscription;
@protocol EduSpeechRecognitionTaskDelegate<NSObject>

@optional

// Called only for final recognitions of utterances. No more about the utterance will be reported
- (void)speechRecognitionTask:(EduSpeechRecognitionTask *)task didFinishRecognition:(EduSpeechRecognitionResult *)recognitionResult;

// Called for all recognitions, including non-final hypothesis
- (void)speechRecognitionTask:(EduSpeechRecognitionTask *)task didHypothesizeTranscription:(EduTranscription *)transcription;

// Called when recognition of all requested utterances is finished.
// If successfully is false, the error property of the task will contain error information
- (void)speechRecognitionTask:(EduSpeechRecognitionTask *)task didFinishSuccessfully:(BOOL)successfully;

@end

@class EduSpeechRecognitionResult;
typedef void (^EduSpeechRecognitionTaskResultHandler) (EduSpeechRecognitionResult* result, NSError *error);

@interface EduSpeechRecognitionTask : NSObject

@property (nonatomic, readonly, assign) EduSpeechRecognitionTaskState state;
// Reports error that occurred during recognition, if applicable
@property (nonatomic, readonly, copy, nullable) NSError *error;

@property (nonatomic, strong) EduSpeechRecognitionRequest *request;

@property (nonatomic, weak) id<EduSpeechRecognitionTaskDelegate> delegate;

@property (nonatomic, copy)EduSpeechRecognitionTaskResultHandler resultHandler;

- (void)cancel;


@end
