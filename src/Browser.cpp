#include "Browser.h"


Browser::Browser(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::Window(cobject),
    m_refBuilder(refBuilder),
    m_notebook(nullptr)
{
    set_default_size(1280, 720);

    m_refBuilder->get_widget("notebook", m_notebook);

    auto pageBuilder = Gtk::Builder::create_from_file("../../styles/page.ui");

    Page* page = nullptr;
    pageBuilder->get_widget_derived("page", page);

    m_notebook->append_page(*page);

    maximize();
    show_all();
}
