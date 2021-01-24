#include "Browser.h"


int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, {});

    auto refBuilder = Gtk::Builder::create_from_file("../styles/browser.ui");

    Browser* browser = nullptr;
    refBuilder->get_widget_derived("browser_window", browser);

    return app->run(*browser);
}