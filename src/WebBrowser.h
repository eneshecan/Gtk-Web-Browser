#pragma once


#include "WebView.h"
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>


class WebBrowser : public Gtk::Window
{
public:
    WebBrowser(BaseObjectType* cObject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~WebBrowser() override = default;

private:
    void slotUriAccepted();
    void slotUriChanged(const Glib::ustring& uri);
    void slotLoadingChanged(bool loading);

private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    WebView                    m_webView;
    Gtk::Entry*                m_searchBar;
    Gtk::Button*               m_backButton;
    Gtk::Button*               m_forwardButton;
    Gtk::Button*               m_refreshButton;
    Gtk::Image*                m_refreshImage;
};
