//
//  ViewController.swift
//  ASR
//
//  Created by 邱威 on 2018/10/15.
//  Copyright © 2018年 qiuwei. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    let audioBufferSR = AudioBufferSpeechRecognition()

    @IBOutlet weak var startButton: UIButton!

    @IBOutlet weak var resultTV: UITextView!
    override func viewDidLoad() {
        super.viewDidLoad()

        startButton.layer.cornerRadius = 60
        startButton.layer.masksToBounds = true
    }

    @IBAction func startButtonClicked(_ sender: Any) {
        startButton.isEnabled = false
        startButton.setTitle("正在识别", for: .disabled)
        audioBufferSR.startRecognizer { [weak self] (transcription, isFinal) in
            guard let strongSelf = self  else { return }
            DispatchQueue.main.async {
                if isFinal {
                    strongSelf.startButton.isEnabled = true
                } else {
                    strongSelf.startButton.isEnabled = false
                }

                strongSelf.resultTV.text = transcription.formattedString.lowercased()
            }
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

