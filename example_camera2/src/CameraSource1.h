//
//  CameraSource1.h
//  example_camera
//
//  Created by Stephan Schulz on 2018-03-27.
//

#ifndef CameraSource1_h
#define CameraSource1_h

/* 
 * CameraSource
 * Camera source for ofxPiMapper
 * Created by Krisjanis Rijnieks on 25/01/2016
 */

#pragma once

#include "ofMain.h"
#include "FboSource.h"

#ifdef TARGET_RASPBERRY_PI
#include "ofxRPiCameraVideoGrabber.h"
#endif

class CameraSource1 : public ofx::piMapper::FboSource {
public:
    
    CameraSource1(int _id){
        name = "Camera SourceA";
        
        _cameraWidth = 1920;
        _cameraHeight = 1080;
        
#ifdef TARGET_RASPBERRY_PI
        _omxCameraSettings.width = _cameraWidth;
        _omxCameraSettings.height = _cameraHeight;
        _omxCameraSettings.framerate = 30;
        _omxCameraSettings.enableTexture = true;
        _omxCameraSettings.doRecording = false;
        
        _videoGrabber.setup(_omxCameraSettings);
#else
        std::vector<ofVideoDevice> devices = _videoGrabber.listDevices();
        _cameraFound = false;
        
        for(int i = 0; i < devices.size(); i++){
            if(devices[i].bAvailable){
                ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
                _cameraFound = true;
                break;
            }
        }
        
        if(_cameraFound){
            _videoGrabber.setDeviceID(_id);
            _videoGrabber.setup(_cameraWidth, _cameraHeight);
        }
#endif
        
        allocate(_cameraWidth, _cameraHeight);
    }
    
    void exit(){
        _videoGrabber.close();
    }
    void update(){
#ifndef TARGET_RASPBERRY_PI
        if(_videoGrabber.isInitialized()){
            _videoGrabber.update();
        }
#endif
    }
    
    void draw(){
        ofClear(0);
        ofSetHexColor(0xffffff);
#ifdef TARGET_RASPBERRY_PI
        ofDisableNormalizedTexCoords();
        _videoGrabber.draw(0, 0);
        ofEnableNormalizedTexCoords();
#else
        if(_videoGrabber.isInitialized()){
            ofDisableNormalizedTexCoords();
            _videoGrabber.draw(0, 0);
            ofEnableNormalizedTexCoords();
        }else{
            ofDrawBitmapString("no camera", _cameraWidth / 2.0f - 40.0f, _cameraHeight / 2.0f + 10.0f);
        }
#endif
    }
    
    
private:
    
#ifdef TARGET_RASPBERRY_PI
    OMXCameraSettings _omxCameraSettings;
    ofxRPiCameraVideoGrabber _videoGrabber;
#else
    ofVideoGrabber _videoGrabber;
#endif
    int _cameraWidth;
    int _cameraHeight;
    bool _cameraFound;
};

#endif /* CameraSource1_h */
