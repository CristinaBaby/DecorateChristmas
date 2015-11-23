
#include "ExpandScrollView.h"
ExpandScrollView::ExpandScrollView()
{
    m_bIsScrolling = false;
    onExpandScrollViewCallback = nullptr;
}

ExpandScrollView::~ExpandScrollView()
{
    
}

ExpandScrollView* ExpandScrollView::create()
{
    ExpandScrollView* widget = new ExpandScrollView();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool ExpandScrollView::init()
{
    if ( !ScrollView::init() )
    {
        return false;
    }
    return true;
}

bool ExpandScrollView::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    m_bIsScrolling = false;
    if (onExpandScrollViewCallback) {
        onExpandScrollViewCallback(this,eBeginScroll);
    }
    return ScrollView::onTouchBegan(touch, unusedEvent);
}

void ExpandScrollView::onTouchMoved(Touch *touch, Event *unusedEvent)
{
    Vec2 offset = Vec2(_touchBeganPosition, _touchMovePosition);
    switch (_direction)
    {
        case Direction::VERTICAL:
        {
            if (fabs(offset.y)>10) {
                m_bIsScrolling = true;
            }
            break;
        }
        case Direction::HORIZONTAL:
        {
            if (fabs(offset.x)>10) {
                m_bIsScrolling = true;
            }
            break;
        }
        case Direction::BOTH:
        {
            if (fabs(offset.y)>10.0f || fabs(offset.x)>10) {
                m_bIsScrolling = true;
            }
            break;
        }
        default:
            break;
    }
    if (onExpandScrollViewCallback) {
        onExpandScrollViewCallback(this,eScrolling);
    }
    ScrollView::onTouchMoved(touch, unusedEvent);
}

void ExpandScrollView::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    if (onExpandScrollViewCallback) {
        onExpandScrollViewCallback(this,eEndedScroll);
    }
    ScrollView::onTouchEnded(touch, unusedEvent);
    
}

void ExpandScrollView::onTouchCancelled(Touch* touch, Event* event)
{
    if (onExpandScrollViewCallback) {
        onExpandScrollViewCallback(this,eEndedScroll);
    }
    
    ScrollView::onTouchCancelled(touch, event);
}