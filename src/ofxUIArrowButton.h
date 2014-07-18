#pragma once

#include "ofxUIWidget.h"

class ofxUIArrowButton : public ofxUIWidget
{
public:
    ofxUIArrowButton();
    ofxUIArrowButton(string _name, ofxUIArrowOrientation _arrowOrientation, bool _value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ofxUIArrowButton(string _name, ofxUIArrowOrientation _arrowOrientation, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);
    ~ofxUIArrowButton();
    virtual void init(string _name, ofxUIArrowOrientation _arrowOrientation, bool *_value, float w, float h, float x = 0, float y = 0, int _size = OFX_UI_FONT_SMALL);

    virtual void drawFill();
    virtual void drawBack();
    virtual void drawOutline();
    virtual void drawFillHighlight();
    virtual void drawOutlineHighlight();

    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void stateChange();
	virtual void setParent(ofxUIWidget *_parent);
	bool getValue();
    virtual void setValue(bool _value);
    virtual void setValuePtr(bool *_value);
	void toggleValue();
    virtual bool isHit(float x, float y);
    virtual bool hasState(){ return false; };

    virtual void keyPressed(int key);
    virtual void keyReleased(int key);

protected:
    ofxUIArrowOrientation arrowOrientation;
    void drawArrow(float x, float y, float w, float h, ofxUIArrowOrientation orientation = OFX_UI_ARROW_UP);
    bool *value;
    bool useReference;
};
