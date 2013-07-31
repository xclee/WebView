//
//  STWebViewIOS.h
//  SheepTower
//
//  Created by Li xuechuan on 13-7-17.
//
//

#import <Foundation/Foundation.h>
#import "STWebViewImpl.h"
class STWebView;

@interface STWebViewIOS : NSObject<UIWebViewDelegate>{
    UIWebView* _webView;
    void* webview_;
}
@property(nonatomic, assign) void* webview;

- (bool)loadURL:(const char *)url frame:(CGRect)rect;
- (void)removeFromSuperview;


@end

#include "ExtensionMacros.h"

NS_CC_EXT_BEGIN
class STWebViewImplIOS : public STWebViewImpl
{
public:
    STWebViewImplIOS(STWebView* webView);
    virtual ~STWebViewImplIOS();
    bool loadURL(const char *url , cocos2d::CCRect rect);
   
private:
    STWebViewIOS *m_webView;
    
};
NS_CC_EXT_END

