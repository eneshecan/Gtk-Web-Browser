#pragma once

#include "Page.h"
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>


class Browser : public Gtk::Window
{
public:
    Browser(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    ~Browser() override = default;

private:
    void addPage(const int pos);

private:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Notebook*             m_notebook;
};
