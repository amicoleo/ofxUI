
#include "ofxUIArrowButton.h"
#include "ofxUI.h"

ofxUIArrowButton::ofxUIArrowButton() : ofxUIWidget()
{

}

ofxUIArrowButton::ofxUIArrowButton(string _name, ofxUIArrowOrientation _arrowOrientation, bool _value, float w, float h, float x, float y, int _size) : ofxUIWidget()
{
    useReference = false;
    init(_name, _arrowOrientation, &_value, w, h, x, y, _size);
}

ofxUIArrowButton::ofxUIArrowButton(string _name, ofxUIArrowOrientation _arrowOrientation,  bool *_value, float w, float h, float x, float y, int _size) : ofxUIWidget()
{
    useReference = true;
    init(_name, _arrowOrientation, _value, w, h, x, y, _size);
}

ofxUIArrowButton::~ofxUIArrowButton()
{
    if(!useReference)
    {
        delete value;
    }
}

void ofxUIArrowButton::init(string _name, ofxUIArrowOrientation _arrowOrientation, bool *_value, float w, float h, float x, float y, int _size)
{
    arrowOrientation = _arrowOrientation;
    initRect(x,y,w,h);
    name = string(_name);
    kind = OFX_UI_WIDGET_BUTTON;//TODO update

    if(useReference)
    {
        value = _value;
    }
    else
    {
        value = new bool();
        *value = *_value;
    }

    setValue(*_value);
}

void ofxUIArrowButton::drawFill()
{
    if(*value)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
//        rect->draw();
        //TODO - here should consider also if there's a rect parent - as the rect->draw() method does
        drawArrow(rect->x, rect->y, rect->width, rect->height, arrowOrientation);
    }
}
void ofxUIArrowButton::drawBack(){
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        drawArrow(rect->x, rect->y, rect->width, rect->height, arrowOrientation);
    }
}
void ofxUIArrowButton::drawOutline(){
    if(draw_outline) {
        ofxUINoFill();
        ofxUISetColor(color_outline);
        drawArrow(rect->x, rect->y, rect->width, rect->height, arrowOrientation);
    }
}
void ofxUIArrowButton::drawFillHighlight(){
    if(draw_fill_highlight) {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        drawArrow(rect->x, rect->y, rect->width, rect->height, arrowOrientation);
    }

}
void ofxUIArrowButton::drawOutlineHighlight(){
    if(draw_outline_highlight) {
        ofxUINoFill();
        ofxUISetColor(color_outline_highlight);
        drawArrow(rect->x, rect->y, rect->width, rect->height, arrowOrientation);
    }
}

void ofxUIArrowButton::mouseMoved(int x, int y)
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIArrowButton::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_DOWN;
        }
        else
        {
            hit = false;
            state = OFX_UI_STATE_NORMAL;
            toggleValue();
            if(triggerType & OFX_UI_TRIGGER_END)
            {
                triggerEvent(this);
            }
        }
        stateChange();
    }
}

void ofxUIArrowButton::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        toggleValue();
        if(triggerType & OFX_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUIArrowButton::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef OFX_UI_TARGET_TOUCH
        state = OFX_UI_STATE_NORMAL;
#else
        if(rect->inside(x, y))
        {
            state = OFX_UI_STATE_OVER;
        }
        else
        {
            state = OFX_UI_STATE_NORMAL;
        }
#endif
        toggleValue();
        if(triggerType & OFX_UI_TRIGGER_END)
        {
            triggerEvent(this);
        }
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUIArrowButton::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = false;
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
        }
            break;

        default:
            break;
    }
}

void ofxUIArrowButton::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
}

bool ofxUIArrowButton::getValue()
{
    return *value;
}
void ofxUIArrowButton::setValue(bool _value)
{
    *value = _value;
    draw_fill = *value;
}

void ofxUIArrowButton::setValuePtr(bool *_value)
{
    if(!useReference)
    {
        delete value;
        useReference = true;
    }
    value = _value;
    setValue(*value);
}

void ofxUIArrowButton::toggleValue()
{
    setValue(!(*value));
}

bool ofxUIArrowButton::isHit(float x, float y)
{
    if(visible)
    {
        return (rect->inside(x, y));
    }
    else
    {
        return false;
    }
}


void ofxUIArrowButton::keyPressed(int key)
{
    if(getIsBindedToKey(key) && !bKeyHit)
    {
        bKeyHit = true;
        toggleValue();
        if(triggerType & OFX_UI_TRIGGER_BEGIN)
        {
            triggerEvent(this);
        }
    }
}

void ofxUIArrowButton::keyReleased(int key)
{
    if(getIsBindedToKey(key) && bKeyHit)
    {
        bKeyHit = false;
        toggleValue();
        if(triggerType & OFX_UI_TRIGGER_END)
        {
            triggerEvent(this);
        }
    }
}

void ofxUIArrowButton::drawArrow(float x, float y, float w, float h, ofxUIArrowOrientation orientation){
    ofBeginShape();
    if (orientation == OFX_UI_ARROW_UP){
        ofVertex(x + w*.5, y);
        ofVertex(x + w, y + h);
        ofVertex(x, y + h);
    }
    else if (orientation == OFX_UI_ARROW_RIGHT){
        ofVertex(x, y);
        ofVertex(x + w, y + h*.5);
        ofVertex(x, y + h);
    }
    else if (orientation == OFX_UI_ARROW_DOWN){
        ofVertex(x, y);
        ofVertex(x + w, y);
        ofVertex(x + w*.5, y + h);

    }
    else if (orientation == OFX_UI_ARROW_LEFT){
        ofVertex(x + w, y);
        ofVertex(x + w, y + h);
        ofVertex(x, y + h*.5);
    }
    ofEndShape();
}
