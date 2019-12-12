#include "WebView.h"


static void loadChanged(WebKitWebView* webView, WebKitLoadEvent loadEvent, gpointer userData)
{
    auto webViewWidget = reinterpret_cast<WebView*>(userData);
    if(!webViewWidget)
    {
        return;
    }

    switch(loadEvent)
    {
        case WEBKIT_LOAD_STARTED:
            webViewWidget->signalLoadingChanged().emit(true);
            break;
        case WEBKIT_LOAD_COMMITTED:
            webViewWidget->signalUriChanged().emit(webkit_web_view_get_uri(webView));
            break;
        case WEBKIT_LOAD_FINISHED:
            webViewWidget->signalTitleChanged().emit(webkit_web_view_get_title(webView));
            webViewWidget->signalLoadingChanged().emit(false);
            break;
        default: break;
    }
}

WebView::WebView() :
    Gtk::Widget(webkit_web_view_new())
{
    g_signal_connect(*this, "load-changed", G_CALLBACK(loadChanged), this);
}

WebView::operator WebKitWebView*()
{
    return WEBKIT_WEB_VIEW(gobj());
}

void WebView::loadUri(const Glib::ustring &uri)
{
    webkit_web_view_load_uri(*this, uri.c_str());
}

void WebView::goBack()
{
    webkit_web_view_go_back(*this);
}

void WebView::goForward()
{
    webkit_web_view_go_forward(*this);
}

void WebView::refresh()
{
    webkit_web_view_reload(*this);
}

sigc::signal<void, Glib::ustring> WebView::signalUriChanged()
{
    return m_signalUriChanged;
}

sigc::signal<void, bool>  WebView::signalLoadingChanged()
{
    return m_signalLoadingChanged;
}

sigc::signal<void, Glib::ustring> WebView::signalTitleChanged()
{
    return m_signalTitleChanged;
}
