#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	cameraSource[0] = new CameraSource(1);
    cameraSource[1] = new CameraSource(2);
	piMapper.registerFboSource(*cameraSource[0]);
    piMapper.registerFboSource(*cameraSource[1]);
	piMapper.setup();
}

void ofApp::exit(){
//    cameraSource->exit();
}

void ofApp::update(){
	piMapper.update();
}

void ofApp::draw(){
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}
