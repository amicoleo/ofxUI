#include "ofxUICarouselRadio.h"

ofxUICarouselRadio::ofxUICarouselRadio(string _name, vector<string> names, int _orientation, float w, float h, float x, float y, int _size){
    init(_name, names, _orientation, w, h, x, y, _size);

    bDownButton = false;
    bUpButton = false;
    upButton = new ofxUIButton("up", &bUpButton, w, h);
    downButton = new ofxUIButton("down", &bDownButton, w, h);
    addEmbeddedWidget(upButton);
    addEmbeddedWidget(downButton);
}
void ofxUICarouselRadio::init(string _name, vector<string> names, int _orientation, float w, float h, float x, float y, int _size) {
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_CAROUSELRADIO;

    draw_back = false;
    orientation = _orientation;

    if(names.size() == 0)
    {
        setEmbedded(true); //?!?
    }

    else
    {
        for(unsigned int i = 0; i < names.size(); i++)
        {
            string lname = names[i];
            ofxUILabel *label = new ofxUILabel(0, 0, lname,lname, _size);
            addEmbeddedWidget(label);
            labels.push_back(label);
        }
    }
}
void ofxUICarouselRadio::setVisible(bool _visible){
    //TODO
}
void ofxUICarouselRadio::triggerSelf(){
    if(parent != NULL){
        parent->triggerEvent(this);
//        parent->triggerEvent(activeL);
    }
}
void ofxUICarouselRadio::triggerEvent(ofxUIWidget *child){
    if (bUpButton && labels[0]->getRect()->y < upButton->getPaddingRect()->getHeight()) {
        for(unsigned int i = 0; i < labels.size(); i++)
        {
            ofxUILabel *l = labels[i];
            if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
            {
                //
            }
            else
            {
                l->getRect()->y+=l->getPaddingRect()->getHeight();
                if (l->getRect()->y > upButton->getRect()->getHeight() && l->getRect()->y + l->getRect()->getHeight() < downButton->getRect()->getMinY() ){
                    l->setVisible(true);
                    activeLabel = l;
                    triggerSelf();
                }
                else {
                    l->setVisible(false);
                }
            }
        }
    }

    if (bDownButton && labels[labels.size()-1]->getRect()->y > downButton->getRect()->y - 1) {
        for(unsigned int i = 0; i < labels.size(); i++)
        {
            ofxUILabel *l = labels[i];
            if(orientation == OFX_UI_ORIENTATION_HORIZONTAL){
                //
            }
            else{
                l->getRect()->y-=l->getPaddingRect()->getHeight();
                if (l->getRect()->y > upButton->getRect()->getHeight() and l->getRect()->y + l->getRect()->getHeight() < downButton->getRect()->getMinY()){
                    l->setVisible(true);
                    activeLabel = l;
                    triggerSelf();
                }
                else
                    l->setVisible(false);
            }
        }
    }

    //

    //

//    ofxUIWidget::triggerEvent(child); //




}
void ofxUICarouselRadio::setParent(ofxUIWidget *_parent) {
    parent = _parent;

    float lWidth = 0;
    float lHeight = 0;

    float xl = 0;
    float yl = 0;

    //Up button
    upButton->setParent(this);
    upButton->setRectParent(this->getRect());
    upButton->getRect()->x = 0;
    upButton->getRect()->y = 0;

    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
    }
    else
    {
        yl = upButton->getPaddingRect()->getHeight();
        if(upButton->getPaddingRect()->width > lWidth){
            lWidth = upButton->getPaddingRect()->width;//?!?
        }
        lHeight+= upButton->getPaddingRect()->height;
    }

    for(unsigned int i = 0; i < labels.size(); i++)
    {
        ofxUILabel* l = labels[i];
        l->setParent(this);
        l->setRectParent(this->getRect());
        if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
        {
        }
        else
        {
            l->getRect()->x = 0;
            l->getRect()->y = yl;
            yl +=l->getPaddingRect()->getHeight();
            if (i == 0){
                activeLabel = l;
                lHeight+= l->getPaddingRect()->height;
                l->setColorBack(ofColor::white);
                l->setColorFill(ofColor::white);
                l->setColorFillHighlight(ofColor::white);
                l->setColorOutline(ofColor::white);
                cout<<l->getName()<<endl<<endl<<endl<<endl<<endl; //NO
                l->setVisible(true); //NO
            }

            else
                l->setVisible(false);

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
        downButton->getRect()->y = upButton->getPaddingRect()->getHeight() +  activeLabel->getPaddingRect()->getHeight();
        lHeight+= downButton->getPaddingRect()->height;
        if(downButton->getPaddingRect()->width > lWidth)
        {
            lWidth = downButton->getPaddingRect()->width;
        }
    }

    //
    if(orientation == OFX_UI_ORIENTATION_HORIZONTAL)
    {
        if(xl > lWidth)
        {
            lWidth = xl;
        }
    }

    rect->setWidth(lWidth);
    rect->setHeight(lHeight);
    calculatePaddingRect();

}
string ofxUICarouselRadio::getActiveName(){
    return activeLabel->getName();
}
void ofxUICarouselRadio::addLabelName(string labelName){
    ofxUILabel *label = new ofxUILabel(0, 0, labelName,labelName, activeLabel->getSize());
    addEmbeddedWidget(label);
    labels.push_back(label);
}
