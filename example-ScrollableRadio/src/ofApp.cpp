#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(10);
	setGUI();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.getName();
	int kind = e.getKind();
	cout << "got event from: " << name << endl;
}

//--------------------------------------------------------------
void ofApp::exit()
{
	delete gui;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}


void ofApp::setGUI()
{
	gui = new ofxUISuperCanvas("SCROLLABLE RADIO");
    gui->addSpacer();

    vector<string> names;
    names.resize(0);
	names.push_back("RAD1");
	names.push_back("RAD2");
	names.push_back("RAD3");
	names.push_back("RAD4");
	names.push_back("RAD5");
	names.push_back("RAD6");
	names.push_back("RAD7");
	names.push_back("RAD8");
	names.push_back("RAD9");
	names.push_back("RAD10");
	names.push_back("RAD11");
	names.push_back("RAD12");

	ofxUIScrollableRadio* radVer = new ofxUIScrollableRadio("RADIO", names, OFX_UI_ORIENTATION_VERTICAL, 140, 70, 10, 10, 0, 0, OFX_UI_FONT_SMALL);
	gui->addWidgetDown(radVer);

    gui->setDrawBack(false);
    for (int i=0; i< gui->getWidgets().size(); i++){
        ofxUIWidget* w = gui->getWidgets()[i];
        w->setColorFill(ofColor::red);
        w->setColorBack(ofColor::yellow);
    }

    gui->autoSizeToFitWidgets();

	ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
