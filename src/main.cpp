#include <QApplication>
#include "gui/MainWindow/MainWindow.hpp"

#include "domain/RequestFactory.hpp"


// REMOVE
#include "domain/FormdataRequestBody.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    const auto& requestFactory = std::make_shared<getit::domain::RequestFactory>("cpprestsdk");

    QApplication a(argc, argv);
    getit::gui::MainWindow w(requestFactory);
    w.show();

    return QApplication::exec();


//    const auto& request = requestFactory->getRequest("POST", "http://localhost:5000");
//    const auto& body = new getit::domain::FormdataRequestBody("123456");
//
//    body->addElement("key", "value");
//
//    request->setBody(body);
//
//    request->send([](getit::domain::Response* resp) {
//       std::cout << resp->body << std::endl;
//    });
//
//    sleep(5);
//
//    return 0;
}
