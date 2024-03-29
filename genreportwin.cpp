#include "genreportwin.h"
#include "ui_genreportwin.h"
#include "mapwinctrl.h"

GenReportWin::GenReportWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenReportWin)
{
    ui->setupUi(this);

    this->setPalette(Qt::white);

    connect(ui->cancelBtn, SIGNAL(pressed()), this, SLOT(cancelBtn_clicked()));
    connect(ui->genBtn,SIGNAL(pressed()), this, SLOT(genBtn_clicked()));
    connect(ui->totalRadio, SIGNAL(toggled(bool)), this, SLOT(bedInfoRadio_selected()));
    connect(ui->occRadio, SIGNAL(toggled(bool)), this, SLOT(bedInfoRadio_selected()));
    connect(ui->acuteCheck, SIGNAL(toggled(bool)), this, SLOT(bedInfoCheck_selected()));
    connect(ui->cccCheck, SIGNAL(toggled(bool)), this, SLOT(bedInfoCheck_selected()));
    connect(ui->ltcCheck, SIGNAL(toggled(bool)), this, SLOT(bedInfoCheck_selected()));
    connect(ui->WLTime, SIGNAL(toggled(bool)), this, SLOT(patientInfoCheck_selected()));
    connect(ui->numCCCInAcute, SIGNAL(toggled(bool)), this, SLOT(patientInfoCheck_selected()));
    connect(ui->numLTCInAcute, SIGNAL(toggled(bool)), this, SLOT(patientInfoCheck_selected()));
    connect(ui->numLTCInCCC, SIGNAL(toggled(bool)), this, SLOT(patientInfoCheck_selected()));
    connect(ui->waitingCheck, SIGNAL(toggled(bool)), this, SLOT(waitingCheck_selected()));
    connect(ui->facListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(facilityList_selected()));

    setScheme();

    setUpList();
}

void GenReportWin::setUpList(){

    for(int i = 0; i < MapWinCtrl::getInstance()->listOfFacility.size(); i++){
        QListWidgetItem *newItem = new QListWidgetItem;
        QString list;
        QString id;
        id = id.setNum(MapWinCtrl::getInstance()->listOfFacility.at(i)->getId());
        list.append(id);
        list.append(",");
        list.append(MapWinCtrl::getInstance()->listOfFacility.at(i)->getName());
        qDebug() << list;
        newItem->setText(list);
        ui->facListWidget->addItem(newItem);
        ui->facListWidget->setAutoScroll(true);
        ui->facListWidget->sortItems();
    }
}

GenReportWin::~GenReportWin(){delete ui;}

void GenReportWin::cancelBtn_clicked(){this->close();}


void GenReportWin::genBtn_clicked()
{


    qDebug() << facilities;


    if (ui->startDate->text().size() != 10 ||ui->endDate->text().size() != 10)
    {
        qDebug() <<"USE CORRECT DATE";
    }
    else
    {
        QList<QListWidgetItem*> listName = ui->facListWidget->selectedItems();

        QString facilities;

        for (int i = 0;i< listName.size();i++)
        {
            facilities.append(listName.at(i)->text());
            facilities.append(",");
        }

        //    qDebug() <<"works ??? " << facilities.at(0);

        if (ui->acuteCheck->checkState() == 2 && ui->cccCheck->checkState() ==0  && ui->ltcCheck->checkState() == 0)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"1","0","0");
        }
        if (ui->acuteCheck->checkState() == 0 && ui->cccCheck->checkState() ==2  && ui->ltcCheck->checkState() == 0)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"0","1","0");
        }
        if (ui->acuteCheck->checkState() == 0 && ui->cccCheck->checkState() ==0  && ui->ltcCheck->checkState() == 2)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"0","0","1");
        }
        if (ui->acuteCheck->checkState() == 2 && ui->cccCheck->checkState() ==2  && ui->ltcCheck->checkState() == 0)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"1","1","0");
        }
        if (ui->acuteCheck->checkState() == 2 && ui->cccCheck->checkState() ==0  && ui->ltcCheck->checkState() == 2)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"1","0","1");
        }
        if (ui->acuteCheck->checkState() == 2 && ui->cccCheck->checkState() ==2  && ui->ltcCheck->checkState() == 2)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"1","1","1");
        }
        if (ui->acuteCheck->checkState() == 0 && ui->cccCheck->checkState() ==2  && ui->ltcCheck->checkState() == 2)
        {
            GenReportCtrl::getInstance()->occRateAC(facilities,ui->startDate->text(),ui->endDate->text(),"0","1","1");
        }

        if (ui->numLTCInCCC->checkState() == 2)
        {
            GenReportCtrl::getInstance()->mismatchCCCLTC(facilities,ui->startDate->text(),ui->endDate->text());
        }

        if (ui->numLTCInAcute->checkState() == 2)
        {
            GenReportCtrl::getInstance()->mismatchACLTC(facilities,ui->startDate->text(),ui->endDate->text());
        }

        if (ui->waitingCheck->checkState() == 2)
        {
            GenReportCtrl::getInstance()->sizeWL(facilities,ui->startDate->text(),ui->endDate->text());
        }

        if (ui->WLTime->checkState() == 2 )
        {
            GenReportCtrl::getInstance()->waitingTime(facilities,ui->startDate->text(),ui->endDate->text());
        }
  //  this->close();
}

}

void GenReportWin::bedInfoRadio_selected(){}
void GenReportWin::bedInfoCheck_selected(){}
void GenReportWin::patientInfoCheck_selected(){}
void GenReportWin::waitingCheck_selected(){}
void GenReportWin::facilityList_selected(){

    ui->facListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void GenReportWin::setScheme(){

    QImage cross("red_cross2.png");

    ui->crossImg->setScaledContents(TRUE);
    ui->crossImg->setPixmap(QPixmap::fromImage(cross));

    QPalette btnPal(Qt::white);
    btnPal.setColor(QPalette::ButtonText, QColor(255, 255, 255));

    ui->cancelBtn->setStyleSheet("background-color: red");
    ui->genBtn->setStyleSheet("background-color: red");

    ui->cancelBtn->setPalette(btnPal);
    ui->genBtn->setPalette(btnPal);

}
