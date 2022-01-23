#ifndef TODOMVC_H
#define TODOMVC_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <dialog.h>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class todomvc; }
QT_END_NAMESPACE

class todomvc : public QMainWindow
{
    Q_OBJECT

public :
    void connClose(){
        database.close();
        database.removeDatabase(QSqlDatabase::defaultConnection);
    };

    bool connOpen(){

        database = QSqlDatabase::addDatabase("QSQLITE");

        database.setDatabaseName("C://Users//PC//Documents//todomvc//todo.db");

        //check connection

        if(database.open()){
         return true;
        }else {
            QMessageBox::information(this,"failed", "connection failed");
           return false;
        }
    };
    QSqlDatabase database;
    void saving();


public:
    todomvc(QWidget *parent = nullptr);
    ~todomvc();
     int count =0;


private slots:
    void on_pushButton_clicked();



    void on_pushButton_3_clicked();


    void on_clearSelect_clicked();
protected :
    void closeEvent(QCloseEvent *e) override;


private:
    Ui::todomvc *ui;



    QSqlTableModel *tableModel;

};
#endif // TODOMVC_H
