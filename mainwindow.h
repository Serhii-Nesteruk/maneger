#pragma once

#include "qcarlistsqlinterface.h"

#include <memory>
#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void on_CarList_clicked(const QModelIndex &index);
private:
    std::shared_ptr<Ui::MainWindow> ui;
    QCarListSqlInterface listSqlInteface;
};
