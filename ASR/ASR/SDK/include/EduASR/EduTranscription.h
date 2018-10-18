//
//  EduTranscription.h
//  EduASR
//
//  Created by 邱威 on 2018/10/9.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EduTranscriptionSegment: NSObject

@property (nonatomic, readonly, copy) NSString *substring;
@property (nonatomic, readonly, assign) NSRange substringRange;
@property (nonatomic, readonly, assign) NSTimeInterval timestamp;
@property (nonatomic, readonly, assign) NSTimeInterval duration;
@property (nonatomic, readonly, assign) float confidence;
@property (nonatomic, readonly, copy) NSArray *alternativeSubstrings;

@end

@interface EduTranscription : NSObject

@property (nonatomic, readonly, copy) NSString *formattedString;
@property (nonatomic, readonly, strong) NSArray<EduTranscriptionSegment *> *segments;

@end
