
#ifndef __STWebView_H__
#define __STWebView_H__

#include <iostream>
#include "cocos2d.h"
#include "ExtensionMacros.h"
//#if CC_LUA_ENGINE_ENABLED > 0
#include "CCLuaEngine.h"
//#endif
USING_NS_CC;

NS_CC_EXT_BEGIN

class STWebViewImpl;

class STWebView : public cocos2d::CCObject{
    
public:
    STWebView();
    ~STWebView();
    
    static STWebView *create();
    
    bool loadURL(const char *url , CCRect rect);
	bool init();
    void removeFromSuperview();
    
    /**
     * Registers a script function that will be called for STWebView events.
     *
     * @code
     * -- lua sample
     * local function webviewEventHandler(eventType)
     *     if eventType == "webViewDidStartLoad" then
     *        
     *     elseif eventType == "webViewDidFinishLoad" then
     *     elseif eventType == "didFailLoadWithError" then
     *     elseif eventType == "return" then
     *     end
     * end
     *
     * @param handler A number that indicates a lua function.
     */
    void registerScriptWebViewHandler(LUA_FUNCTION handler);
    
    /**
     * Unregisters a script function that will be called for EditBox events.
     */
    void unregisterScriptWebViewHandler(void);
    /**
     * get a script Handler
     */
    int  getScriptEditBoxHandler(void){ return m_nScriptWebViewHandler ;}
    void handleScriptEventHandler(const char *str);
    
private:
    int m_nScriptWebViewHandler;
    STWebViewImpl *m_webViewImpl;
    
};
NS_CC_EXT_END

#endif 
