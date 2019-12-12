#pragma once

#include "WebView.h"
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>


class Page : public Gtk::Box
{
public:
    Page(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~Page() override = default;

public:
    sigc::signal<void, Glib::ustring> signalTitleChanged();

private:
    void slotUriAccepted();
    void slotUriChanged(const Glib::ustring& uri);
    void slotLoadingChanged(bool loading);
    void slotTitleChanged(const Glib::ustring& title);

private:
    Glib::RefPtr<Gtk::Builder>        m_refBuilder;
    WebView                           m_webView;
    Gtk::Entry*                       m_searchBar;
    Gtk::Button*                      m_backButton;
    Gtk::Button*                      m_forwardButton;
    Gtk::Button*                      m_refreshButton;
    Gtk::Image*                       m_refreshImage;
    sigc::signal<void, Glib::ustring> m_signalTitleChanged;
};
