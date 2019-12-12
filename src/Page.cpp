#include "Page.h"


Page::Page(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refBuilder) :
    Gtk::Box(cobject),
    m_refBuilder(refBuilder),
    m_searchBar(nullptr),
    m_backButton(nullptr),
    m_forwardButton(nullptr),
    m_refreshButton(nullptr),
    m_refreshImage(nullptr)
{
    m_refBuilder->get_widget("search_bar", m_searchBar);
    m_refBuilder->get_widget("back_button", m_backButton);
    m_refBuilder->get_widget("forward_button", m_forwardButton);
    m_refBuilder->get_widget("refresh_button", m_refreshButton);
    m_refBuilder->get_widget("refresh_image", m_refreshImage);

    m_searchBar->set_text("https://old.reddit.com");
    m_webView.loadUri(m_searchBar->get_text());

    m_searchBar->signal_activate().connect(sigc::mem_fun(this, &Page::slotUriAccepted));
    m_backButton->signal_clicked().connect(sigc::mem_fun(&m_webView, &WebView::goBack));
    m_forwardButton->signal_clicked().connect(sigc::mem_fun(&m_webView, &WebView::goForward));
    m_refreshButton->signal_clicked().connect(sigc::mem_fun(&m_webView, &WebView::refresh));
    m_webView.signalUriChanged().connect(sigc::mem_fun(this, &Page::slotUriChanged));
    m_webView.signalLoadingChanged().connect(sigc::mem_fun(this, &Page::slotLoadingChanged));
    m_webView.signalTitleChanged().connect(sigc::mem_fun(this, &Page::slotTitleChanged));

    pack_end(m_webView);

    show_all();
}

sigc::signal<void, Glib::ustring> Page::signalTitleChanged()
{
    return m_signalTitleChanged;
}

void Page::slotUriAccepted()
{
    m_webView.loadUri(m_searchBar->get_text());
}

void Page::slotUriChanged(const Glib::ustring &uri)
{
    m_searchBar->set_text(uri);
}

void Page::slotLoadingChanged(bool loading)
{
    m_refreshImage->set_from_icon_name(loading ? "window-close" : "view-refresh", Gtk::IconSize{Gtk::ICON_SIZE_BUTTON});
}

void Page::slotTitleChanged(const Glib::ustring &title)
{
    m_signalTitleChanged.emit(title);
}
