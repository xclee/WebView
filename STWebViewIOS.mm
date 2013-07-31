//
//  STWebViewIOS.m
//  SheepTower
//
//  Created by Li xuechuan on 13-7-17.
//
//

#import "STWebViewIOS.h"
#import "EAGLView.h"

#define getWebViewImplIOS() ((cocos2d::extension::STWebViewImplIOS*)webview_)


@implementation STWebViewIOS
@synthesize webview = webview_;

- (void)dealloc{
    [self removeFromSuperview];
    [super dealloc];
}
- (void)removeFromSuperview{
    [_webView removeFromSuperview];
    _webView = nil;
}
- (void)hiddenBackgroundView{
    
    for (UIView *view in [_webView subviews])
    {
        if ([view isKindOfClass:[UIScrollView class]])
        {
            for (UIView *shadowView in view.subviews)
            {
                if ([shadowView isKindOfClass:[UIImageView class]])
                {
                    shadowView.hidden = YES;
                }
            }
        }
    }
    
}
- (void)initWithWebView:(const char *)url frame:(CGRect )rect{
    if (!_webView)
    {
        _webView = [[UIWebView alloc] initWithFrame:rect];
        [_webView setDelegate:self];
        [[EAGLView sharedEGLView] addSubview:_webView];
        [_webView release];
        _webView.backgroundColor = [UIColor clearColor];
        _webView.opaque = NO;
    }
    [self hiddenBackgroundView];
}
- (bool)loadURL:(const char *)url frame:(CGRect)rect{
    [self initWithWebView:url frame:rect];
    //TO.DO 防止多次请求
    
    //[_webView stopLoading];
    NSString *request = [NSString stringWithUTF8String:url];
    [_webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request]
                                            cachePolicy:NSURLRequestReloadIgnoringLocalCacheData
                                        timeoutInterval:60]];
    return true;
}

#pragma mark - WebView
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return true;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    //NSLog(@"webViewDidStartLoad\n");
    if (webview_){
        
        cocos2d::extension::STWebViewImpl *stWebImpl = getWebViewImplIOS();
        cocos2d::extension::STWebView *web = stWebImpl->getWebView();
        //web->getScriptEditBoxHandler();
        if (NULL != web)
            web->handleScriptEventHandler("webViewDidStartLoad");
    }
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    //NSLog(@"webViewDidFinishLoad\n");
    cocos2d::extension::STWebViewImpl *stWebImpl = getWebViewImplIOS();
    cocos2d::extension::STWebView *web = stWebImpl->getWebView();
    if (NULL != web)
        web->handleScriptEventHandler("webViewDidFinishLoad");
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    //NSLog(@"didFailLoadWithError\n");
    cocos2d::extension::STWebViewImpl *stWebImpl = getWebViewImplIOS();
    cocos2d::extension::STWebView *web = stWebImpl->getWebView();
    if (NULL != web)
        web->handleScriptEventHandler("didFailLoadWithError");
}


@end

NS_CC_EXT_BEGIN
//////////////////////////////////////
STWebViewImpl* __createWebView(STWebView* webview){
    
    return new STWebViewImplIOS(webview);
}

bool STWebViewImplIOS::loadURL(const char *url , cocos2d::CCRect rect){
    
    return [m_webView loadURL:url frame:CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height)];

}
STWebViewImplIOS::STWebViewImplIOS(STWebView* webView)
: STWebViewImpl(webView)
{
    m_webView = [[STWebViewIOS alloc] init];
    m_webView.webview = this;
    
}
STWebViewImplIOS::~STWebViewImplIOS(){
    [m_webView release];
    m_webView = nil;
}
NS_CC_EXT_END


