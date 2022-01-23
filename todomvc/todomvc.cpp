#include "todomvc.h"
#include "ui_todomvc.h"
#include <QMessageBox>
#include <QDebug>
#include <QStandardItem>
#include <QStringListModel>

QStandardItemModel *model= new QStandardItemModel;
QStandardItemModel * model3 = new QStandardItemModel();
QSqlQueryModel *model2 = new QSqlQueryModel();
QList<QStandardItem *> listItem;
QList<QStandardItem *> listItem2;


todomvc::todomvc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::todomvc)
{

    QPixmap bkgnd(":/ba.png");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);

         ui->setupUi(this);

        //QSqlQueryModel * model = new QSqlQueryModel();
        connOpen();
        auto qry =new QSqlQuery(database);
        qry->prepare("select * from done");
        qry->exec();

        int idName = qry->record().indexOf("name");
        while (qry->next())
        {
          QStandardItem *item2 = new QStandardItem();
          QString name = qry->value(idName).toString();
          item2->setText(name);
          item2->setIcon(QIcon(":/done.png"));

          if(item2->text()!=""){
          model->appendRow(item2);
          listItem << item2;
        }
             ui->listView->setModel(model);
        }



              auto qry1 =new QSqlQuery(database);
           qry1->prepare("select * from tasks");
           qry1->exec();

           int idName1 = qry1->record().indexOf("name");
           while (qry1->next())
           {
             QStandardItem *item2 = new QStandardItem();
             QString name = qry1->value(idName).toString();
             item2->setText(name);
             item2->setIcon(QIcon(":/done.png"));
             listItem << item2;

             model3->appendRow(item2);

           }

              ui->listView_2->setModel(model3);

        connClose();


     connect(ui->clearSelect, SIGNAL(clicked()), this, SLOT(on_clearSelect_clicked));
     ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

     ui->pushButton->setObjectName("NewTask");

     ui->pushButton->setStyleSheet("#NewTask { color: white; background-color: #b91043; border-color: #ff2264 ; }  #NewTask:hover{  color :black ; background-color: white ; border-color: #ff2264; }");

   //  ui->pushButton_2->setObjectName("NewTask");

     //ui->pushButton_2->setStyleSheet("#NewTask { color: white; background-color: #b91043; border-color: #ff2264 ; }  #NewTask:hover{ background-color: black ; border-color: #ff2264; }");
     ui->pushButton_3->setObjectName("NewTask");
     ui->pushButton_3->setStyleSheet("#NewTask { color: white; background-color: #b91043; border-color: #ff2264 ; }  #NewTask:hover{ background-color: black ; border-color: #ff2264; }");

     ui->clearSelect->setObjectName("NewTask");
     ui->clearSelect->setStyleSheet("#NewTask { color: white; background-color: #b91043; border-color: #ff2264 ; }  #NewTask:hover{ background-color: black ; border-color: #ff2264; }");





     ui->listView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
     ui->listView_2->dragDropOverwriteMode();
     ui->listView_2->setDragEnabled(true);
     ui->listView_2->setAcceptDrops(true);
     ui->listView_2->setDropIndicatorShown(true);
     //ui->listView_2->setModel(model3);
     ui->listView_2->setDefaultDropAction(Qt::MoveAction);


     ui->listView->setSelectionMode(QAbstractItemView::ExtendedSelection);
     ui->listView->dragDropOverwriteMode();
     ui->listView->setDragEnabled(true);
     ui->listView->setAcceptDrops(true);
     ui->listView->setDropIndicatorShown(true);
     //ui->listView_2->setModel(model3);
     ui->listView->setDefaultDropAction(Qt::MoveAction);


}

todomvc::~todomvc()
{
    delete ui;
}


void todomvc::on_pushButton_clicked()
{
    QString text =ui->lineEdit->text();
       connOpen();
    if(ui->checkBox->isChecked()){

          QStandardItem *item2 = new QStandardItem();
          item2->setText(text);
          item2->setIcon(QIcon(":/done.png"));
          listItem << item2;

          model->appendRow(item2);

          ui->listView->setModel(model);

           }

     else {

          QStandardItem *item2 = new QStandardItem();
          item2->setText(text);
          item2->setIcon(QIcon(":/done.png"));
          listItem2 << item2;

          model3->appendRow(item2);

          ui->listView_2->setModel(model3);

}
     connClose();
}



void todomvc::on_pushButton_3_clicked()

{    connOpen();

     QStringList list;
             QModelIndexList indexes = ui->listView_2->selectionModel()->selectedIndexes();
              QVariant elementSelectionne = model3->data(indexes[0] ,Qt::DisplayRole);
              list << elementSelectionne.toString();
               while(indexes.size()) {
                 model3->removeRow(indexes.first().row());
                 indexes = ui->listView_2->selectionModel()->selectedIndexes();
                 QModelIndex indexElementSelectionne = ui->listView_2->selectionModel()->currentIndex();
                   QVariant elementSelectionne = model3->data(indexElementSelectionne, Qt::DisplayRole);
                   list << elementSelectionne.toString();
                 }

        for(int i=0;i<list.size();i++){
             QSqlQuery query;
            query.prepare("DELETE FROM tasks WHERE name='"+list[i]+"'");
            query.exec();
        }
         connClose();

}


void todomvc::on_clearSelect_clicked()
{

    QStringList list;
            QModelIndexList indexes = ui->listView->selectionModel()->selectedIndexes();
             QVariant elementSelectionne = model->data(indexes[0] ,Qt::DisplayRole);
             list << elementSelectionne.toString();
              while(indexes.size()) {
                model->removeRow(indexes.first().row());
                indexes = ui->listView->selectionModel()->selectedIndexes();
                QModelIndex indexElementSelectionne = ui->listView->selectionModel()->currentIndex();
                  QVariant elementSelectionne = model->data(indexElementSelectionne, Qt::DisplayRole);
                  list << elementSelectionne.toString();
                }
         connOpen();
       for(int i=0;i<list.size();i++){
            QSqlQuery query;
           query.prepare("DELETE FROM done WHERE name='"+list[i]+"'");
           query.exec();
       }
        connClose();
}

void todomvc::saving(){

    connOpen();
    auto qry =new QSqlQuery(database);
    for(int i=0;i<listItem.size();i++){
        if(listItem[i]->text()!=""){
     qry->prepare("INSERT INTO done(name) VALUES(?)");
     qry->addBindValue(listItem[i]->text());
    }
}
    for(int i=0;i<listItem2.size();i++){
     qry->prepare("INSERT INTO tasks(name) VALUES(?)");
     qry->addBindValue(listItem2[i]->text());
    }

     qry->exec();
}

void todomvc::closeEvent(QCloseEvent *e)
{
    saving();


}
