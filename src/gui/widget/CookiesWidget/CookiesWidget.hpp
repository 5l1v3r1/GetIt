#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/Request.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CookiesWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class CookiesWidget: public QWidget, public RequestWidget
    {
    public:
        explicit CookiesWidget(QWidget* parent = nullptr);
        ~CookiesWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        Ui::CookiesWidget* ui;

        void connectSignals();
    };
}