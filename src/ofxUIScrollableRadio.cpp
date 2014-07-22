#include "ofxUIScrollableRadio.h"

ofxUIScrollableRadio::ofxUIScrollableRadio(string name, vector<string> names, int _orientation, float _wRadio, float _hRadio, float w, float h, float x, float y, int _size)
//:ofxUIRadio(_name,names,_orientation, w, h, x, y, _size)
:ofxUIRadio(name,names,OFX_UI_ORIENTATION_VERTICAL, w, h, x, y, _size) //TODO - for now just vertical
{
    kind = OFX_UI_WIDGET_SCROLLABLERADIO; //TODO - make new define

    wMaxRadio = _wRadio;
    hMaxRadio = _hRadio;

    bDownButton = false;
    bUpButton = false;
    upButton = new ofxUIArrowButton("up", OFX_UI_ARROW_UP, &bUpButton, w, h);
    downButton = new ofxUIArrowButton("down", OFX_UI_ARROW_DOWN, &bDownButton, w, h);
    addEmbeddedWidget(upButton);
    addEmbeddedWidget(downButton);

}

void ofxUIScrollableRadio::triggerEvent(ofxUIWidget *child)
{
    if (child->getKind() ==OFX_UI_WIDGET_TOGGLE) {
        activateToggle(child->getName().c_str());
        triggerSelf();
    }
    else {
        if (bUpButton && toggles[0]->getRect()->y < yBeginTogglesArea) {
            ofxUIArrowButton* b = (ofxUIArrowButton*) child;
            if(b->getValue()) {
                for(unsigned int i = 0; i < toggles.size(); i++)
                {
                    ofxUIToggle *t = toggles[i];
                    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
                    {
                        //
                    }
                    else
                    {
                        t->getRect()->y+=t->getPaddingRect()->getHeight();
                        if (t->getRect()->y > yBeginTogglesArea && t->getRect()->y + t->getRect()->getHeight() < yEndTogglesArea ){
                            t->setVisible(true);
                        }
                        else {
                            t->setVisible(false);
                        }
                    }
                }
            }
        }
        if (bDownButton && toggles[toggles.size()-1]->getRect()->y + toggles[toggles.size()-1]->getRect()->getHeight() > yEndTogglesArea) {
            ofxUIArrowButton* b = (ofxUIArrowButton*) child;
            if(b->getValue()) {
                for(unsigned int i = 0; i < toggles.size(); i++)
                {
                    ofxUIToggle *t = toggles[i];
                    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL){
                        //
                    }
                    else{
                        t->getRect()->y-=t->getPaddingRect()->getHeight();
                        if (t->getRect()->y > yBeginTogglesArea && t->getRect()->y + t->getRect()->getHeight() < yEndTogglesArea){
                            t->setVisible(true);
                        }
                        else
                            t->setVisible(false);
                    }
                }
            }
        }
        ofxUIWidget::triggerEvent(child); //
    }
}

void ofxUIScrollableRadio::setParent(ofxUIWidget *_parent){
    parent = _parent;

    float tWidth = 0;
    float tHeight = 0;

    int hMaxRadioRound = 0;
    int nRectHeight = 0;
    do {
        hMaxRadioRound+=nRectHeight*downButton->getPaddingRect()->getHeight();
        nRectHeight++;
    } while (hMaxRadioRound + downButton->getPaddingRect()->getHeight()< hMaxRadio);


    float xt = 0;
    float yt = 0;


    //Up button
    upButton->setParent(this);
    upButton->setRectParent(this->getRect());

    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
    }
    else
    {
        yt = upButton->getPaddingRect()->getHeight();
        xBeginTogglesArea = 0;
        yBeginTogglesArea = upButton->getRect()->getHeight();

        if(upButton->getPaddingRect()->width > tWidth){
            tWidth = upButton->getPaddingRect()->width;
        }
        tHeight+= upButton->getPaddingRect()->height;
    }


    //Toggles
    for(unsigned int i = 0; i < toggles.size(); i++)
    {
        ofxUIToggle *t = toggles[i];
        t->setParent(this);
        t->setRectParent(this->getRect());
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {
        }
        else
        {
            t->getRect()->x = 0;
            t->getRect()->y = yt;
            yt +=t->getPaddingRect()->getHeight();
            if (yt > hMaxRadioRound - 1)
                t->setVisible(false);
            else
                tHeight+=t->getPaddingRect()->getHeight();
        }
    }

    //Down button
    downButton->setParent(this);
    downButton->setRectParent(this->getRect());

     if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
    }
    else
    {
        downButton->getRect()->x = 0;
        downButton->getRect()->y = hMaxRadioRound - downButton->getPaddingRect()->getHeight();
        if(downButton->getPaddingRect()->width > tWidth)
        {
            tWidth = downButton->getPaddingRect()->width;
        }
        tHeight+=downButton->getPaddingRect()->getHeight();

        xEndTogglesArea = 0;
        yEndTogglesArea = hMaxRadioRound - downButton->getPaddingRect()->getHeight();
    }


    //
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        if(xt > tWidth)
        {
            tWidth = xt;
        }
    }

    rect->setWidth(tWidth - padding);
    rect->setHeight(tHeight - padding*2.0);
    calculatePaddingRect();
}


