//
//  URLSpeechRecognition.swift
//  ASR
//
//  Created by 邱威 on 2018/9/4.
//  Copyright © 2018年 YYInc. All rights reserved.
//

import UIKit

class URLSpeechRecognition: NSObject {

    private let recognizer: EduSpeechRecognizer = EduSpeechRecognizer()

    private var resultHandler: (EduTranscription) -> Void = {_ in }

    func startRecognizer(resultHandler: (@escaping (EduTranscription)->Void)) {
        let url = Bundle.main.url(forResource: "howareyou.flac", withExtension: .none)!
        let request = EduSpeechURLRecognitionRequest(url: url)

        // delegate
        recognizer.recognitionTask(with: request, delegate: self)
        self.resultHandler = resultHandler

        // block
//        recognizer.recognitionTask(with: request) { (result, error) in
//            print("识别结果：", result?.bestTranscription.formattedString ?? "")
//            resultHandler((result?.bestTranscription)!)
//        }
    }
}

extension URLSpeechRecognition: EduSpeechRecognitionTaskDelegate {

    func speechRecognitionTask(_ task: EduSpeechRecognitionTask, didFinishRecognition recognitionResult: EduSpeechRecognitionResult) {
        resultHandler(recognitionResult.bestTranscription)
    }

    func speechRecognitionTask(_ task: EduSpeechRecognitionTask, didHypothesizeTranscription transcription: EduTranscription) {

    }
}
