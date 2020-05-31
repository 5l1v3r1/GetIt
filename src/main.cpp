#include <QApplication>
#include "gui/MainWindow/MainWindow.hpp"

#include "domain/RequestFactory.hpp"

int main(int argc, char** argv)
{
    const auto& requestFactory = std::make_shared<getit::domain::RequestFactory>("cpprestsdk");

    QApplication a(argc, argv);
    getit::gui::MainWindow w(requestFactory);
    w.show();

    return QApplication::exec();
}
