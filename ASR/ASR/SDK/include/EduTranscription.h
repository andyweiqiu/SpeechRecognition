//
//  EduTranscription.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EduTranscriptionSegment;

// A hypothesized text form of a speech recording
@interface EduTranscription : NSObject

// Contains the entire recognition, formatted into a single user-displayable string
@property (nonatomic, readonly, copy) NSString *formattedString;
@property (nonatomic, readonly, strong) NSArray<EduTranscriptionSegment *> *segments;

// debug
@property (nonatomic, copy) NSString *jsonString;

@end

// Substrings of a hypothesized transcription
@interface EduTranscriptionSegment: NSObject

@property (nonatomic, readonly, copy) NSString *substring;
@property (nonatomic, readonly, assign) NSRange substringRange;
@property (nonatomic, readonly, assign) NSTimeInterval timestamp;
@property (nonatomic, readonly, assign) NSTimeInterval duration;

// Confidence in the accuracy of transcription. Scale is 0 (least confident) to 1.0 (most confident)
@property (nonatomic, readonly, assign) float confidence;

// Other possible interpretations of this segment
@property (nonatomic, readonly, copy) NSArray *alternativeSubstrings;

@end
