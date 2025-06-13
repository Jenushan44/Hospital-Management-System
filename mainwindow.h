#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbManager.h"
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QMessageBox>
#include <QString>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPatientPage_clicked();
    void on_btnDoctorPage_clicked();
    void on_btnMainPage_clicked();
    void on_btnAddPatient_clicked();
    void on_btnSearchPatient_clicked();
    void on_btnViewPatient_clicked();
    void on_btnAddPatientInfo_clicked();
    void on_btnAddDoctorInfo_clicked();
    void on_btnAddDoctor_clicked();
    void on_btnViewPatients_clicked();
    void on_searchDoctor_clicked();
    void on_viewDoctor_clicked();
    void on_emergencyPage_clicked();
    void on_btnAddEmergencyInfo_clicked();
    void on_btnViewEmergencies_clicked();
    void on_searchPatientButton_clicked();
    void on_deletePatientViewButton_clicked();
    void on_deletePatientSearchButton_clicked();
    void on_btnRoomPage_clicked();
    void on_btnViewRooms_clicked();
    void on_btnViewRoomStatus_clicked();
    void on_viewRoomTable_clicked();
    void on_releaseRoomButton_clicked();
    void on_searchDoctorButton_clicked();
    void on_btnViewDoctors_clicked();

    void on_submitAddRoomButton_clicked();
    void on_assignRoomPageButton_clicked();
    void on_roomManagerAddButton_clicked();
    void on_assignRoomActionButton_clicked();

private:
    Ui::MainWindow *ui;
    DbManager m_dbManager;

    void setupConnections();
};

#endif // MAINWINDOW_H
