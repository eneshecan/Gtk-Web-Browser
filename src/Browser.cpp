#include "Browser.h"


Browser::Browser(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder) :
    Gtk::Window(cobject),
    m_refBuilder(refBuilder),
    m_notebook(nullptr)
{
    set_default_size(1280, 720);

    m_refBuilder->get_widget("notebook", m_notebook);

    addPage(0);

    auto newPage = Gtk::make_managed<Gtk::Box>();
    m_notebook->append_page(*newPage);

    auto buttonBuilder = Gtk::Builder::create_from_file("../../styles/page.ui");
    Gtk::Button* addPageButton = nullptr;
    buttonBuilder->get_widget("add_page_button", addPageButton);

    m_notebook->set_tab_label(*newPage, *addPageButton);

    addPageButton->signal_clicked().connect([this]()
    {
        addPage(m_notebook->get_n_pages() - 1);
    });

    maximize();
    show_all();
}

void Browser::addPage(const int pos)
{
    auto pageBuilder = Gtk::Builder::create_from_file("../../styles/page.ui");
    Page* page = nullptr;
    pageBuilder->get_widget_derived("page_box", page);
    m_notebook->insert_page(*page, pos);
    m_notebook->set_current_page(pos);

    auto tabBuilder = Gtk::Builder::create_from_file("../../styles/page.ui");
    Gtk::Box* tab = nullptr;
    tabBuilder->get_widget("tab_box", tab);

    auto tabLabel = dynamic_cast<Gtk::Label*>(tab->get_children()[0]);
    page->signalTitleChanged().connect(sigc::mem_fun(*tabLabel, &Gtk::Label::set_text));
    page->signalTitleChanged().connect(sigc::mem_fun(*tabLabel, &Gtk::Label::set_tooltip_text));

    auto closeTabButton = dynamic_cast<Gtk::Button*>(tab->get_children()[1]);
    closeTabButton->signal_clicked().connect([this, page]()
    {
        if(m_notebook->get_n_pages() > 2)
        {
            m_notebook->remove_page(*page);
            if(m_notebook->get_current_page() == (m_notebook->get_n_pages() - 1))
            {
                m_notebook->prev_page();
            }
        }
    });

    m_notebook->set_tab_label(*page, *tab);
}
