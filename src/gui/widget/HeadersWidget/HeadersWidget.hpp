#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "domain/Request.hpp"
#include "gui/widget/RequestWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class HeadersWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class HeadersWidget: public QWidget, public RequestWidget
    {
        Q_OBJECT

    public:
        explicit  HeadersWidget(QWidget* parent = nullptr);
        ~HeadersWidget() override;

        void addToRequest(std::shared_ptr<domain::Request> request) override;

    private:
        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        Ui::HeadersWidget* ui;

        void connectSignals();
    };
}