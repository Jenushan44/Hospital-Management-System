#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dbManager.h>
#include <QSettings>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_dbManager("hospital.db")
{
    ui->setupUi(this);

    connect(ui->menuPageButton, &QPushButton::clicked, this, &MainWindow::on_btnMainPage_clicked);

    connect(ui->patientPageButton, &QPushButton::clicked, this, &MainWindow::on_btnPatientPage_clicked);
    connect(ui->addPatientPageButton, &QPushButton::clicked, this, &MainWindow::on_btnAddPatient_clicked);
    connect(ui->searchPatientPageButton, &QPushButton::clicked, this, &MainWindow::on_btnSearchPatient_clicked);
    connect(ui->viewPatientPageButton, &QPushButton::clicked, this, &MainWindow::on_btnViewPatient_clicked);
    connect(ui->deleteViewPatient, &QPushButton::clicked, this, &MainWindow::on_deletePatientViewButton_clicked);
    connect(ui->submitPatientButton, &QPushButton::clicked, this, &MainWindow::on_btnAddPatientInfo_clicked);
    connect(ui->searchPatientButton, &QPushButton::clicked, this, &MainWindow::on_btnViewPatients_clicked);
    connect(ui->searchPatientHealthCardButton, &QPushButton::clicked, this, &MainWindow::on_searchPatientButton_clicked);
    connect(ui->deletSearchPatient, &QPushButton::clicked, this, &MainWindow::on_deletePatientSearchButton_clicked);

    connect(ui->doctorPageButton, &QPushButton::clicked, this, &MainWindow::on_btnDoctorPage_clicked);
    connect(ui->addDoctorPageButton, &QPushButton::clicked, this, &MainWindow::on_btnAddDoctor_clicked);
    connect(ui->searchDoctorButton, &QPushButton::clicked, this, &MainWindow::on_searchDoctor_clicked);
    connect(ui->viewAllDoctorsButton, &QPushButton::clicked, this, &MainWindow::on_viewDoctor_clicked);
    connect(ui->submitDoctorButton, &QPushButton::clicked, this, &MainWindow::on_btnAddDoctorInfo_clicked);
    connect(ui->searchDoctorIdButton, &QPushButton::clicked, this, &MainWindow::on_searchDoctorButton_clicked);
    connect(ui->viewDoctorsButton, &QPushButton::clicked, this, &MainWindow::on_btnViewDoctors_clicked);

    connect(ui->emergencyPage, &QPushButton::clicked, this, &MainWindow::on_emergencyPage_clicked);
    connect(ui->addEmergencyInfoButton, &QPushButton::clicked, this, &MainWindow::on_btnAddEmergencyInfo_clicked);
    connect(ui->viewAllEmergenciesButton, &QPushButton::clicked, this, &MainWindow::on_btnViewEmergencies_clicked);

    connect(ui->roomPageButton, &QPushButton::clicked, this, &MainWindow::on_btnRoomPage_clicked);
    connect(ui->viewRoomPageButton, &QPushButton::clicked, this, &MainWindow::on_btnViewRooms_clicked);

    connect(ui->viewRoomTableButton, &QPushButton::clicked, this, &MainWindow::on_viewRoomTable_clicked);
    connect(ui->releaseRoomButton, &QPushButton::clicked, this, &MainWindow::on_releaseRoomButton_clicked);
    connect(ui->roomManagerAddButton, &QPushButton::clicked, this, &MainWindow::on_roomManagerAddButton_clicked);
    connect(ui->assignRoomPageButton, &QPushButton::clicked, this, &MainWindow::on_assignRoomPageButton_clicked);
    connect(ui->assignRoomActionButton, &QPushButton::clicked, this, &MainWindow::on_assignRoomActionButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnMainPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnPatientPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_btnAddPatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnSearchPatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_searchPatientButton_clicked()
{
    QString searchItem = ui->healthCardSearchLineEdit->text();
    m_dbManager.searchPatient(ui->tableWidgetSearchPatient, searchItem);
}

void MainWindow::on_btnViewPatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_btnViewPatients_clicked()
{
    m_dbManager.viewPatient(ui->tableWidgetViewPatient);
}

void MainWindow::on_btnDoctorPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_btnAddDoctor_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_searchDoctor_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_viewDoctor_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_btnViewEmergencies_clicked()
{
    m_dbManager.viewEmergencyPatient(ui->tableWidgetEmergency);
}

void MainWindow::on_emergencyPage_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_10);
}

void MainWindow::on_btnRoomPage_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_11);
}

void MainWindow::on_roomManagerAddButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_16);
}

void MainWindow::on_btnViewRooms_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_15);
}

void MainWindow::on_btnViewRoomStatus_clicked()
{
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::on_viewRoomTable_clicked()
{
    m_dbManager.viewRooms(ui->tableWidgetRooms);
}

void MainWindow::on_searchDoctorButton_clicked()
{
    QString searchItem = ui->doctorIdSearchLineEdit->text();
    m_dbManager.searchDoctor(ui->tableWidgetSearchDoctor, searchItem);
}

void MainWindow::on_btnViewDoctors_clicked()
{
    m_dbManager.viewDoctor(ui->tableWidgetViewDoctor);
}

void MainWindow::on_submitAddRoomButton_clicked()
{
    QString roomNumber = ui->roomNumberAddLineEdit->text();
    QString roomType = ui->roomTypeLineEdit->text();
    QString roomStatus = ui->roomStatusLineEdit->text();

    if (roomNumber.isEmpty() || roomType.isEmpty() || roomStatus.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    if (m_dbManager.addRoom(roomNumber, roomType, roomStatus)) {
        QMessageBox::information(this, "Success", "Room added successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to add room. Make sure room number is unique.");
    }

    ui->roomNumberAddLineEdit->clear();
    ui->roomTypeLineEdit->clear();
    ui->roomStatusLineEdit->clear();
}

void MainWindow::on_btnAddPatientInfo_clicked()
{
    QString addHealthCardNumber = ui->healthCardNumberLineEdit->text();
    QString addFirstName = ui->firstNamePatientLineEdit->text();
    QString addLastName = ui->lastNamePatientLineEdit->text();
    QString addDateOfBirth = ui->dateOfBirthPatientLineEdit->text();
    QString addGender = ui->genderPatientLineEdit->text();
    QString addBloodType = ui->bloodTypePatientLineEdit->text();
    QString addAddress = ui->addressPatientLineEdit->text();
    QString addPhoneNumber = ui->phoneNumberPatientLineEdit->text();
    QString addEmailAddress = ui->emailAddressPatientLineEdit->text();
    QString addInsuranceCompany = ui->insuranceCompanyPatientLineEdit->text();
    QString addPrimaryCarePhysician = ui->primaryCarePhysicianPatientLineEdit->text();

    qDebug() << "Health Card Number: " << addHealthCardNumber;
    qDebug() << "First name: " << addFirstName;
    qDebug() << "Last name: " << addLastName;
    qDebug() << "Date of Birth: " << addDateOfBirth;
    qDebug() << "Gender: " << addGender;
    qDebug() << "Blood Type: " << addBloodType;
    qDebug() << "Address: " << addAddress;
    qDebug() << "Phone Number: " << addPhoneNumber;
    qDebug() << "Email Address: " << addEmailAddress;
    qDebug() << "Insurance Company: " << addInsuranceCompany;
    qDebug() << "Primary Care Physician: " << addPrimaryCarePhysician;

    if (m_dbManager.addPatient(addHealthCardNumber, addFirstName, addLastName, addDateOfBirth, addGender, addBloodType, addAddress, addPhoneNumber, addEmailAddress, addInsuranceCompany, addPrimaryCarePhysician))
    {
        QMessageBox::information(this, "Success", "Patient successfully added!");
    }
    else
    {
        QMessageBox::warning(this, "Failiure", "Failed to add patient");
    }

    ui->healthCardNumberLineEdit->clear();
    ui->firstNamePatientLineEdit->clear();
    ui->lastNamePatientLineEdit->clear();
    ui->dateOfBirthPatientLineEdit->clear();
    ui->genderPatientLineEdit->clear();
    ui->bloodTypePatientLineEdit->clear();
    ui->addressPatientLineEdit->clear();
    ui->phoneNumberPatientLineEdit->clear();
    ui->emailAddressPatientLineEdit->clear();
    ui->insuranceCompanyPatientLineEdit->clear();
    ui->primaryCarePhysicianPatientLineEdit->clear();
}

void MainWindow::on_btnAddDoctorInfo_clicked()
{
    QString doctorIdNumber = ui->doctorIdNumberLineEdit->text();
    QString specialization = ui->specializationLineEdit->text();
    QString yearsOfExperience = ui->yearsOfExperienceLineEdit->text();
    QString firstName = ui->firstNameDoctorLineEdit->text();
    QString lastName = ui->lastNameDoctorLineEdit->text();
    QString dateOfBirth = ui->dateOfBirthDoctorLineEdit->text();
    QString gender = ui->genderDoctorLineEdit->text();
    QString phoneNumber = ui->phoneNumberDoctorLineEdit->text();
    QString email = ui->emailDoctorLineEdit->text();
    QString address = ui->addressDoctorLineEdit->text();

    qDebug() << "Doctor Id Number: " << doctorIdNumber;
    qDebug() << "Specialization: " << specialization;
    qDebug() << "Years Of Experience: " << yearsOfExperience;
    qDebug() << "First name: " << firstName;
    qDebug() << "Last name: " << lastName;
    qDebug() << "Date of Birth: " << dateOfBirth;
    qDebug() << "Gender: " << gender;
    qDebug() << "Phone Number: " << phoneNumber;
    qDebug() << "Email: " << email;
    qDebug() << "Address: " << address;

    if (m_dbManager.addDoctor(doctorIdNumber, specialization, yearsOfExperience, firstName, lastName, dateOfBirth, gender, phoneNumber, email, address))
    {
        QMessageBox::information(this, "Success", "Doctor successfully added!");
    }
    else
    {
        QMessageBox::warning(this, "Failiure", "Failed to add doctor");
    }

    ui->doctorIdNumberLineEdit->clear();
    ui->specializationLineEdit->clear();
    ui->yearsOfExperienceLineEdit->clear();
    ui->firstNameDoctorLineEdit->clear();
    ui->lastNameDoctorLineEdit->clear();
    ui->dateOfBirthDoctorLineEdit->clear();
    ui->genderDoctorLineEdit->clear();
    ui->emailDoctorLineEdit->clear();
    ui->addressDoctorLineEdit->clear();
    ui->phoneNumberDoctorLineEdit->clear();
}

void MainWindow::on_btnAddEmergencyInfo_clicked()
{
    QString emergencyHealthCardNumber = ui->healthCardNumberEmergencyLineEdit->text();
    QString emergencyFirstName = ui->firstNameEmergencyLineEdit->text();
    QString emergencyLastName = ui->lastNameEmergencyLineEdit->text();
    QString emergencyDateOfBirth = ui->birthdayEmergencyLineEdit->text();
    QString emergencyGender = ui->genderEmergencyLineEdit->text();
    QString emergencyBloodType = ui->bloodTypeEmergencyLineEdit->text();
    QString emergencyContactNumber = ui->emergencyContactNumberLineEdit->text();
    QString emergencyContactRelation = ui->emergencyContactRelationLineEdit->text();
    QString emergencyContactName = ui->emergencContactNameLineEdit->text();
    QString emergencyReason = ui->emergencyReasonLineEdit->text();
    QString emergencySymptoms = ui->emergencySymptomsLineEdit->text();
    QString emergencyCurrentMedicalConditions = ui->currentMedicalConditionsLineEdit->text();
    QString emergencyAllergies = ui->allergiesEmergencyLineEdit->text();
    QString emergencyMedication = ui->medicationEmergencyLineEdit->text();
    QString emergencyTime = ui->emergencyTimeLineEdit->text();

    qDebug() << "Health Card Number: " << emergencyHealthCardNumber;
    qDebug() << "First Name: " << emergencyFirstName;
    qDebug() << "Last Name: " << emergencyLastName;
    qDebug() << "Birthday: " << emergencyDateOfBirth;
    qDebug() << "Gender: " << emergencyGender;
    qDebug() << "Blood Type: " << emergencyBloodType;
    qDebug() << "Emergency Contact Name: " << emergencyContactName;
    qDebug() << "Emergency Contact Relation: " << emergencyContactRelation;
    qDebug() << "Emergency Contact Phone Number: " << emergencyContactNumber;
    qDebug() << "Emergency Reason: " << emergencyReason;
    qDebug() << "Symptoms: " << emergencyHealthCardNumber;
    qDebug() << "Current Medical Conditions: " << emergencyCurrentMedicalConditions;
    qDebug() << "Allergies: " << emergencyAllergies;
    qDebug() << "Medication: " << emergencyMedication;
    qDebug() << "Emergency Time: " << emergencyTime;

    if (m_dbManager.addEmergency(emergencyHealthCardNumber, emergencyFirstName, emergencyLastName, emergencyDateOfBirth, emergencyGender, emergencyBloodType, emergencyContactName, emergencyContactRelation, emergencyContactNumber, emergencyReason, emergencySymptoms, emergencyCurrentMedicalConditions, emergencyAllergies, emergencyMedication, emergencyTime))
    {
        QMessageBox::information(this, "Success", "Patient successfully added");
    }
    else
    {
        QMessageBox::warning(this, "Failiure", "Failed to add Patient");
    }

    ui->healthCardNumberEmergencyLineEdit->clear();
    ui->firstNameEmergencyLineEdit->clear();
    ui->lastNameEmergencyLineEdit->clear();
    ui->birthdayEmergencyLineEdit->clear();
    ui->genderEmergencyLineEdit->clear();
    ui->bloodTypeEmergencyLineEdit->clear();
    ui->emergencyContactNumberLineEdit->clear();
    ui->emergencyContactRelationLineEdit->clear();
    ui->emergencContactNameLineEdit->clear();
    ui->emergencyReasonLineEdit->clear();
    ui->emergencySymptomsLineEdit->clear();
    ui->currentMedicalConditionsLineEdit->clear();
    ui->allergiesEmergencyLineEdit->clear();
    ui->medicationEmergencyLineEdit->clear();
    ui->emergencyTimeLineEdit->clear();
}

void MainWindow::on_deletePatientViewButton_clicked()
{
    int selectedRow = ui->tableWidgetViewPatient->currentRow();

    if (selectedRow < 0)
    {
        QMessageBox::warning(this, "Delete", "Please select a patient to delete");
    }

    QString healthCardNumber = ui->tableWidgetViewPatient->item(selectedRow, 0)->text();

    if (m_dbManager.deletePatient(healthCardNumber))
    {
        ui->tableWidgetViewPatient->removeRow(selectedRow);
        QMessageBox::information(this, "Delete", "Patient deleted successfully");
    }
    else
    {
        QMessageBox::critical(this, "Delete", "Failed to delete patient");
    }
}

void MainWindow::on_deletePatientSearchButton_clicked()
{
    int selectedRow = ui->tableWidgetSearchPatient->currentRow();

    if (selectedRow < 0)
    {
        QMessageBox::warning(this, "Delete", "Please select a patient to delete");
    }

    QString healthCardNumber = ui->tableWidgetSearchPatient->item(selectedRow, 0)->text();

    if (m_dbManager.deletePatient(healthCardNumber))
    {
        ui->tableWidgetSearchPatient->removeRow(selectedRow);
        QMessageBox::information(this, "Delete", "Patient deleted successfully");
    }
    else
    {
        QMessageBox::critical(this, "Delete", "Failed to delete patient");
    }
}

void MainWindow::on_assignRoomPageButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_12);
}


void MainWindow::on_assignRoomActionButton_clicked()
{
    QString healthCardNumber = ui->assignHealthCardNumberLineEdit->text();
    QString roomNumber = ui->roomNumberLineEdit->text();

    if (healthCardNumber.isEmpty() || roomNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both Health Card Number and Room Number.");
        return;
    }

    if (m_dbManager.assignRoom(healthCardNumber, roomNumber)) {
        QMessageBox::information(this, "Success", "Room successfully assigned!");
    } else {
        QMessageBox::warning(this, "Failure", "Room is already occupied.");
    }

    ui->assignHealthCardNumberLineEdit->clear();
    ui->roomNumberLineEdit->clear();
}


void MainWindow::on_releaseRoomButton_clicked()
{
    QString healthCardNumber = ui->healthCardNumberReleaseLineEdit->text();
    QString roomNumber = ui->roomNumberReleaseLineEdit->text();

    if (healthCardNumber.isEmpty() || roomNumber.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please provide both the Health Card Number and Room Number");
    }

    if (m_dbManager.changeRoomStatus(healthCardNumber, roomNumber))
    {
        QMessageBox::information(this, "Success", "Room successfully released");
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to release room");
    }

    ui->healthCardNumberReleaseLineEdit->clear();
    ui->roomNumberReleaseLineEdit->clear();
}
