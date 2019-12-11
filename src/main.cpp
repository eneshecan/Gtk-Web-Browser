#include "WebBrowser.h"


int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, {});

    auto refBuilder = Gtk::Builder::create_from_file("../../styles/web_browser.ui");

    WebBrowser* browser = nullptr;
    refBuilder->get_widget_derived("web_browser", browser);

    return app->run(*browser);
}