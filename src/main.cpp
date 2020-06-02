#include <QApplication>
#include "gui/MainWindow/MainWindow.hpp"

#include "domain/RequestFactory.hpp"

int main(int argc, char** argv)
{
    const auto& appName = "GetIt";
    const auto& requestFactory = std::make_shared<getit::domain::RequestFactory>("cpprestsdk");

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    getit::gui::MainWindow window(requestFactory);
    window.show();

    return QApplication::exec();
}
