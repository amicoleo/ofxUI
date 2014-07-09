//#ifndef OFXUISCROLLABLERADIO_H
//#define OFXUISCROLLABLERADIO_H

#pragma once

#include "ofxUIRadio.h"

class ofxUIScrollableRadio: public ofxUIRadio
{
public:
    ofxUIScrollableRadio(string _name, vector<string> names, int _orientation, float wMaxRadio, float hMaxRadio, float w, float h, float x, float y, int _size);
	void setParent(ofxUIWidget *_parent);
	void triggerEvent(ofxUIWidget *child);


    protected:
        float wMaxRadio;
        float hMaxRadio;

        float xBeginTogglesArea, yBeginTogglesArea, xEndTogglesArea, yEndTogglesArea;

        ofxUIButton *downButton;
        ofxUIButton *upButton;
        bool bUpButton, bDownButton;


    private:
};

//#endif // OFXUISCROLLABLERADIO_H
