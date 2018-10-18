//
//  AudioBufferSpeechRecognition.swift
//  ASR
//
//  Created by 邱威 on 2018/9/4.
//  Copyright © 2018年 YYInc. All rights reserved.
//

import UIKit

class AudioBufferSpeechRecognition: NSObject {

    private let recognizer: EduSpeechRecognizer = EduSpeechRecognizer()

    private let audioEngine = AVAudioEngine()

    private var speechRecognitionTask: EduSpeechRecognitionTask?
    private var recognitionRequest: EduSpeechAudioBufferRecognitionRequest?

    private var capture: AVCaptureSession?

    private var resultHandler: (EduTranscription, Bool) -> Void = {_,_  in }

    func startRecognizer(resultHandler: (@escaping (EduTranscription, Bool)->Void)) {

        // sample buffer
        self.recognitionRequest = EduSpeechAudioBufferRecognitionRequest()
        self.speechRecognitionTask = self.recognizer.recognitionTask(with: self.recognitionRequest!, delegate: self)
        self.resultHandler = resultHandler
        DispatchQueue.main.async {
            self.startCapture();
        }
        return

        // pcm buffer
        let audioSession = AVAudioSession.sharedInstance()

        do {
            try audioSession.setCategory(AVAudioSessionCategoryRecord)
        } catch {
            fatalError("setCategory: \(error)")
        }

        do {
            try audioSession.setActive(true, with: AVAudioSessionSetActiveOptions.notifyOthersOnDeactivation)
        } catch {
            fatalError("setActive: \(error)")
        }

        let inputNode = audioEngine.inputNode

        self.recognitionRequest = EduSpeechAudioBufferRecognitionRequest()
        self.speechRecognitionTask = self.recognizer.recognitionTask(with: recognitionRequest!) { (result, error) in
            resultHandler((result?.bestTranscription)!, (result?.isFinal)!)
        }

        let recordingFormat = inputNode.outputFormat(forBus: 0)
        inputNode.removeTap(onBus: 0)
        inputNode.installTap(onBus: 0, bufferSize: 1024, format: recordingFormat) { (buffer, when) in
            self.recognitionRequest?.append(buffer)
        }

        audioEngine.prepare()
        do {
            try audioEngine.start()
        } catch {
            print("audioEngine.start()", error)
        }
    }

    func endRecognizer() {
        endCapture()

        audioEngine.stop()

        self.recognitionRequest?.endAudio()
    }

    func startCapture() {

        capture = AVCaptureSession()

        guard let audioDev = AVCaptureDevice.default(for: .audio) else {
            print("AVCaptureDevice初始化错误")
            return
        }

        guard let audioIn = try? AVCaptureDeviceInput(device: audioDev) else {
            print("不能创建 input device.")
            return
        }

        guard true == capture?.canAddInput(audioIn) else {
            print("不能添加 input device")
            return
        }

        capture?.addInput(audioIn)

        let audioOut = AVCaptureAudioDataOutput()
        audioOut.setSampleBufferDelegate(self, queue: DispatchQueue.main)

        guard true == capture?.canAddOutput(audioOut) else {
            print("不能添加 audio output")
            return
        }

        capture?.addOutput(audioOut)
        audioOut.connection(with: .audio)
        capture?.startRunning()

    }

    func endCapture() {

        if true == capture?.isRunning {
            capture?.stopRunning()
        }
    }
}

extension AudioBufferSpeechRecognition: AVCaptureAudioDataOutputSampleBufferDelegate {

    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        recognitionRequest?.appendAudioSampleBuffer(sampleBuffer)
    }
}

extension AudioBufferSpeechRecognition: EduSpeechRecognitionTaskDelegate {
    func speechRecognitionTask(_ task: EduSpeechRecognitionTask, didFinishRecognition recognitionResult: EduSpeechRecognitionResult) {

        speechRecognitionTask?.cancel()
        recognitionRequest?.endAudio()
        endCapture()
        audioEngine.stop()

        print("识别结果：", recognitionResult.bestTranscription.formattedString)
        print("transcriptions: ", recognitionResult.transcriptions)
//        for transcription in recognitionResult.transcriptions {
//            print("text: ", transcription.formattedString)
//        }
        resultHandler(recognitionResult.bestTranscription, true)
    }

    func speechRecognitionTask(_ task: EduSpeechRecognitionTask, didHypothesizeTranscription transcription: EduTranscription) {
//        print("接收：", transcription.formattedString)
        resultHandler(transcription, false)
    }

    func speechRecognitionTask(_ task: EduSpeechRecognitionTask, didFinishSuccessfully successfully: Bool) {
        print("识别完成: \(successfully), error: \(String(describing: task.error))")
    }
}
