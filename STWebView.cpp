//
//  STWebView.cpp
//  SheepTower
//
//  Created by Li xuechuan on 13-7-17.
//
//

#include "STWebView.h"
#include "STWebViewImpl.h"


USING_NS_CC;
NS_CC_EXT_BEGIN


STWebView::STWebView(void)
: m_webViewImpl(NULL)
{
    
}

STWebView::~STWebView()
{
    if (m_webViewImpl){
        delete m_webViewImpl;
        m_webViewImpl = NULL;
    }
    unregisterScriptWebViewHandler();
//        [m_webView release];
//        m_webView = NULL;
}
bool STWebView::loadURL(const char *url , CCRect rect){
    
    if(!m_webViewImpl){
        m_webViewImpl = __createWebView(this);
    }
    return m_webViewImpl->loadURL(url, rect);
    
//    if(!m_webView){
//        m_webView = [[STWebViewIOS alloc] init];
//    }
//    return [m_webView loadURL:url frame:CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height)];
    
}

bool STWebView::init()
{
    m_nScriptWebViewHandler = 0;
	return true;
}
STWebView *STWebView::create(){
    
    STWebView *webView = new STWebView();
    if (webView && webView->init())
    {
        webView->autorelease();
        return webView;
    }
    CC_SAFE_DELETE(webView);
    return NULL;
}
void STWebView::removeFromSuperview(){
    if (m_webViewImpl){
        delete m_webViewImpl;
        m_webViewImpl = NULL;
    }
}

void STWebView::registerScriptWebViewHandler(int handler){
    unregisterScriptWebViewHandler();
    m_nScriptWebViewHandler = handler;
}

/**
 * Unregisters a script function that will be called for EditBox events.
 */
void STWebView::unregisterScriptWebViewHandler(void){
    if(0 != m_nScriptWebViewHandler )
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptWebViewHandler);
        m_nScriptWebViewHandler = 0;
    }
}
void STWebView::handleScriptEventHandler(const char *str){
    CCLog("---handleScriptEventHandler %s \n",str);
    
    if (NULL != str && 0 != m_nScriptWebViewHandler)
    {
        cocos2d::CCScriptEngineProtocol* pEngine = cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine();
        //pEngine->executeEvent(m_nScriptWebViewHandler, str,this);
        
//        CCLuaValueDict dict;
//        dict["name"] = CCLuaValue::stringValue("failed");
//        dict["request"] = CCLuaValue::ccobjectValue(this, "CCHTTPRequest");
//
        //TO.DO after 2.1.4 use CCScriptEngineProtocol 
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->clean();
        //stack->pushCCLuaValueDict(dict);
        stack->pushString(str);
        
        stack->executeFunctionByHandler(m_nScriptWebViewHandler, 1);
        
        
    }
    
}

NS_CC_EXT_END