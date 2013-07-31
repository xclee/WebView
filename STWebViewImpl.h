//
//  STWebViewImpl.h
//  SheepTower
//
//  Created by Li xuechuan on 13-7-31.
//
//

#ifndef __SheepTower__STWebViewImpl__
#define __SheepTower__STWebViewImpl__

#include <iostream>
#include "cocos2d.h"

#include "ExtensionMacros.h"
#include "STWebView.h"

NS_CC_EXT_BEGIN



class STWebViewImpl{
public:
    //STWebViewImpl();
    STWebViewImpl(STWebView* webView) :m_pWebView(webView) {}
    virtual ~STWebViewImpl(void){}
    
    virtual bool loadURL(const char *url , cocos2d::CCRect rect) = 0;
    STWebView* getWebView() { return m_pWebView; };
protected:
    STWebView *m_pWebView;
};

extern STWebViewImpl* __createWebView(STWebView* webview);


NS_CC_EXT_END

#endif /* defined(__SheepTower__STWebViewImpl__) */


