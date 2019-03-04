//
//  EduSpeechRecognitionRequest.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

// A request for a speech recognition from an audio source
@interface EduSpeechRecognitionRequest : NSObject

// If true, partial (non-final) results for each utterance will be reported.
// Default is true
@property (nonatomic) BOOL shouldReportPartialResults;

// Whether to start the process or not
// The processing is mainly noise reduction and sound gain
@property (nonatomic, assign) BOOL audioProcess;

// Text which you want to speak
@property (nonatomic, copy) NSString *speechText;

// The header parameter of the request
// Current fields to include:
// "user-id"
// "device-id"
@property (nonatomic, copy) NSDictionary *headerParameter;

@property (nonatomic, assign) NSTimeInterval responseTimeout;

@property (nonatomic, copy) NSString *host;
@property (nonatomic, copy) NSString *port;

// Default is true
@property (nonatomic, assign) BOOL openVad;

// This vad is end of speech
// Default is 0.8 seconds
@property (nonatomic, assign) NSTimeInterval vadInterval;

// This vad is no audio input from start service
// Default is 3 seconds
@property (nonatomic, assign) NSTimeInterval frontVadInterval;

@property (nonatomic, assign) NSTimeInterval sendPackageInterval;

@end

// A request to recognize speech from a recorded audio file
@interface EduSpeechURLRecognitionRequest: EduSpeechRecognitionRequest

@property (nonatomic, readonly, copy) NSURL *url;

- (instancetype)initWithUrl:(NSURL *)url;

@end

// A request to recognize speech from arbitrary audio buffers
@interface EduSpeechAudioBufferRecognitionRequest: EduSpeechRecognitionRequest

// Append audio to the end of the recognition stream. Must currently be in native format.
- (void)appendAudioPCMBuffer:(AVAudioPCMBuffer *)audioPCMBuffer;

- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)appendPCMData:(NSData *)pcmData;

- (NSData *)getPCMData;

- (void)endAudio;

@end
