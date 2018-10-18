//
//  EduSpeechRecognitionRequest.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@interface EduSpeechRecognitionRequest : NSObject

- (NSData *)getSampleData;
- (void)clear;

@end

@interface EduSpeechURLRecognitionRequest: EduSpeechRecognitionRequest

@property (nonatomic, strong) NSURL *url;

- (instancetype)initWithUrl:(NSURL *)url;

@end

@interface EduSpeechAudioBufferRecognitionRequest: EduSpeechRecognitionRequest

// Append audio to the end of the recognition stream. Must currently be in native format.
- (void)appendAudioPCMBuffer:(AVAudioPCMBuffer *)audioPCMBuffer;
- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)endAudio;

@end
