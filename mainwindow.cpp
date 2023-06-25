#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_shared<Ui::MainWindow>())
{
    ui->setupUi(this);
    //this->setFixedSize(QSize(700, 550));
    //setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ui->CarList->setModel(&listSqlInteface.getAllCarListSqlModel());

    //connect(ui->CarList, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_clicked(QListWidgetItem*)));
}

void MainWindow::on_CarList_clicked(const QModelIndex &index)
{
    QString field = index.data().toString();
    ui->ItemName->setText(field);

    const QStringList fields = field.split(' ');
    const QString brand = fields.at(0);
    const QString model = fields.at(1);

    listSqlInteface.getCarSqlModel().select("*", QString("brand='%1' AND model='%2'").arg(brand, model));
}
