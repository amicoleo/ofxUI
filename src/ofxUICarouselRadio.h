#pragma once

#include "ofxUIWidgetWithLabel.h"
#include "ofxUILabel.h"
#include "ofxUIDefines.h"
#include "ofxUIToggle.h"

class ofxUICarouselRadio : public ofxUIWidget
{
public:
    ofxUICarouselRadio(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    void init(string _name, vector<string> names, int _orientation, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    void setVisible(bool _visible);
    void triggerSelf();
    void triggerEvent(ofxUIWidget *child);
	void setParent(ofxUIWidget *_parent);
	void setActiveName(string labelName);
	string getActiveName();

	//TODO - the method below works - but if the widget is updated after it has been added to the
	//gui, it doesn't get drawn
    void addLabelName(string labelName);

protected:
    string activeName;
	int orientation;
	vector<ofxUILabel *> labels;
    ofxUILabel *activeLabel;

    ofxUIButton *downButton;
    ofxUIButton *upButton;
    bool bUpButton, bDownButton;
};
