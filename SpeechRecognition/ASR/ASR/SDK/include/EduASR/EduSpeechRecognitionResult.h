//
//  EduSpeechRecognitionResult.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EduTranscription;
@interface EduSpeechRecognitionResult : NSObject

@property (nonatomic, readonly, strong) EduTranscription *bestTranscription;
@property (nonatomic, readonly, strong) NSArray<EduTranscription *> *transcriptions;
@property (nonatomic, readonly, getter=isFinal) BOOL final;

@end
