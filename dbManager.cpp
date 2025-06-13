#include "dbManager.h"
#include <QFile>

DbManager::DbManager(const QString& path) {

    QFile dbFile(path);
    bool dbExists = dbFile.exists();

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: Connection with database failed";
    } else {
        qDebug() << "Database: connect ok";
        if (!dbExists) {
            createTables();
    }
    }
}

bool DbManager::addPatient(const QString& addHealthCardNumber, const QString& addFirstName, const QString& addLastName, const QString& addDateOfBirth, const QString& addGender, const QString& addBloodType, const QString& addAddress, const QString& addPhoneNumber, const QString& addEmailAddress, const QString& addInsuranceCompany, const QString& addPrimaryCarePhysician) {

    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO patients (health_card_number, first_name, last_name, date_of_birth, gender, blood_type, address, phone_number, email_address, insurance_company, primary_care_physician) "
                  "VALUES (:healthCardNumber, :firstName, :lastName, :dateOfBirth, :gender, :bloodType, :address, :phoneNumber, :emailAddress, :insuranceCompany, :primaryCarePhysician)");
    queryAdd.bindValue(":healthCardNumber", addHealthCardNumber);
    queryAdd.bindValue(":firstName", addFirstName);
    queryAdd.bindValue(":lastName", addLastName);
    queryAdd.bindValue(":dateOfBirth", addDateOfBirth);
    queryAdd.bindValue(":gender", addGender);
    queryAdd.bindValue(":bloodType", addBloodType);
    queryAdd.bindValue(":address", addAddress);
    queryAdd.bindValue(":phoneNumber", addPhoneNumber);
    queryAdd.bindValue(":emailAddress", addEmailAddress);
    queryAdd.bindValue(":insuranceCompany", addInsuranceCompany);
    queryAdd.bindValue(":primaryCarePhysician", addPrimaryCarePhysician);

    if(queryAdd.exec()) {
        qDebug() << "Patient added successfully";
        return true;
    } else {
        qDebug() << "Error: Patient not added: " << queryAdd.lastError();
        return false;
    }
}

bool DbManager::searchPatient(QTableWidget* tableWidget, const QString searchItem) {
    QSqlQuery query;

    query.prepare("SELECT * FROM patients WHERE health_card_number = :healthCardNumber "
                               "OR first_name LIKE :searchPattern "
                               "OR last_name LIKE :searchPattern");

    query.bindValue(":healthCardNumber", searchItem);
    query.bindValue(":searchPattern", "%" + searchItem + "%");

    if (!query.exec()) {
        qDebug() << "Error: search failed: " << query.lastError();
        return false;
    }

    tableWidget->setColumnCount(11);

    QStringList headers;
    headers << "Health Card" << "First Name" << "Last name" << "Birthday" << "Gender" << "Blood Type" << "Address" << "Phone Number" << "Email" << "Insurance Company" << "Primary Care Physician";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while(query.next()) {
        tableWidget->insertRow(row);

        QString healthCardNumber = query.value("health_card_number").toString();
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString dateOfBirth = query.value("date_of_birth").toString();
        QString gender = query.value("gender").toString();
        QString bloodType = query.value("blood_type").toString();
        QString address = query.value("address").toString();
        QString phoneNumber = query.value("phone_number").toString();
        QString emailAddress = query.value("email_address").toString();
        QString insuranceCompany = query.value("insurance_company").toString();
        QString primaryCarePhysician = query.value("primary_care_physician").toString();

        tableWidget->setItem(row, 0, new QTableWidgetItem(healthCardNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(firstName));
        tableWidget->setItem(row, 2, new QTableWidgetItem(lastName));
        tableWidget->setItem(row, 3, new QTableWidgetItem(dateOfBirth));
        tableWidget->setItem(row, 4, new QTableWidgetItem(gender));
        tableWidget->setItem(row, 5, new QTableWidgetItem(bloodType));
        tableWidget->setItem(row, 6, new QTableWidgetItem(address));
        tableWidget->setItem(row, 7, new QTableWidgetItem(phoneNumber));
        tableWidget->setItem(row, 8, new QTableWidgetItem(emailAddress));
        tableWidget->setItem(row, 9, new QTableWidgetItem(insuranceCompany));
        tableWidget->setItem(row, 10, new QTableWidgetItem(primaryCarePhysician));

        row++;
    }
    return true;
}

bool DbManager::viewPatient(QTableWidget* tableWidget) {
    QSqlQuery query("SELECT * FROM patients");

    if (!query.exec()) {
        qDebug() << "Error: execution failed: " << query.lastError();
        return false;
    }

    tableWidget->setColumnCount(11);

    QStringList headers;
    headers << "Health Card" << "First Name" << "Last Name" << "Birthday" << "Gender" << "Blood Type" << "Address" << "Phone Number" << "Email Address" << "Insurance Company" << "Primary Care Physician";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while(query.next()) {
        tableWidget->insertRow(row);

        QString healthCardNumber = query.value("health_card_number").toString();
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString dateOfBirth = query.value("date_of_birth").toString();
        QString gender = query.value("gender").toString();
        QString bloodType = query.value("blood_type").toString();
        QString address = query.value("address").toString();
        QString phoneNumber = query.value("phone_number").toString();
        QString emailAddress = query.value("email_address").toString();
        QString insuranceCompany = query.value("insurance_company").toString();
        QString primaryCarePhysician = query.value("primary_care_physician").toString();


        tableWidget->setItem(row, 0, new QTableWidgetItem(healthCardNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(firstName));
        tableWidget->setItem(row, 2, new QTableWidgetItem(lastName));
        tableWidget->setItem(row, 3, new QTableWidgetItem(dateOfBirth));
        tableWidget->setItem(row, 4, new QTableWidgetItem(gender));
        tableWidget->setItem(row, 5, new QTableWidgetItem(bloodType));
        tableWidget->setItem(row, 6, new QTableWidgetItem(address));
        tableWidget->setItem(row, 7, new QTableWidgetItem(phoneNumber));
        tableWidget->setItem(row, 8, new QTableWidgetItem(emailAddress));
        tableWidget->setItem(row, 9, new QTableWidgetItem(insuranceCompany));
        tableWidget->setItem(row, 10, new QTableWidgetItem(primaryCarePhysician));

        row++;
    }
    return true;
}

bool DbManager::deletePatient(const QString &healthCardNumber) {
    QSqlQuery query;

    query.prepare("DELETE FROM patients WHERE health_card_number = :healthCardNumber");
    query.bindValue(":healthCardNumber", healthCardNumber);

    if(!query.exec()) {
        qDebug() << "Error: Delete Failed: " << query.lastError();
        return false;
    }
    return true;
}

bool DbManager::addDoctor(const QString& doctorIdNumber, const QString& specialization, const QString& yearsOfExperience, const QString& firstName,  const QString& lastName, const QString& dateOfBirth, const QString& gender, const QString& phoneNumber, const QString& email, const QString& address) {

    QSqlQuery query;
    query.prepare("INSERT INTO doctors (doctor_id, specialization, years_experience, first_name,  last_name, date_of_birth, gender, phone_number, email, address)"
                  "VALUES (:doctorIdNumber, :specialization, :yearsOfExperience, :firstName, :lastName, :dateOfBirth, :gender, :phoneNumber, :email, :address)");
    query.bindValue(":doctorIdNumber", doctorIdNumber);
    query.bindValue(":specialization", specialization);
    query.bindValue(":yearsOfExperience", yearsOfExperience);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":dateOfBirth", dateOfBirth);
    query.bindValue(":gender", gender);
    query.bindValue(":phoneNumber", phoneNumber);
    query.bindValue(":email", email);
    query.bindValue(":address", address);

    if(query.exec()) {
        qDebug() << "Doctor added successfully";
        return true;
    } else {
        qDebug() << "Error: Doctor not added: " << query.lastError();
        return false;
    }
}

bool DbManager::searchDoctor(QTableWidget* tableWidget, const QString searchItem) {

    tableWidget->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT * FROM doctors WHERE doctor_id = :doctorIdNumber "
                               "OR first_name LIKE :searchPattern "
                               "OR last_name LIKE :searchPattern");

    query.bindValue(":doctorIdNumber", searchItem);
    query.bindValue(":searchPattern", "%" + searchItem + "%");

    if (!query.exec()) {
        qDebug() << "Error: search failed: " << query.lastError();
        return false;
    }

    tableWidget->setColumnCount(10);

    QStringList headers;
    headers << "Doctor Id" << "Specialization" << "Years Of Experience" << "First Name" << "Last name" << "Birthday" << "Gender" << "Phone Number" << "Email" << "Address";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while(query.next()) {
        tableWidget->insertRow(row);

        QString doctorIdNumber = query.value("doctor_id").toString();
        QString specialization = query.value("specialization").toString();
        QString yearsOfExperience = query.value("years_experience").toString();
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString dateOfBirth = query.value("date_of_birth").toString();
        QString gender = query.value("gender").toString();
        QString phoneNumber = query.value("phone_number").toString();
        QString email = query.value("email").toString();
        QString address = query.value("address").toString();

        tableWidget->setItem(row, 0, new QTableWidgetItem(doctorIdNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(specialization));
        tableWidget->setItem(row, 2, new QTableWidgetItem(yearsOfExperience));
        tableWidget->setItem(row, 3, new QTableWidgetItem(firstName));
        tableWidget->setItem(row, 4, new QTableWidgetItem(lastName));
        tableWidget->setItem(row, 5, new QTableWidgetItem(dateOfBirth));
        tableWidget->setItem(row, 6, new QTableWidgetItem(gender));
        tableWidget->setItem(row, 7, new QTableWidgetItem(phoneNumber));
        tableWidget->setItem(row, 8, new QTableWidgetItem(email));
        tableWidget->setItem(row, 9, new QTableWidgetItem(address));

        row++;
    }
    return true;
}

bool DbManager::viewDoctor(QTableWidget* tableWidget) {

    QSqlQuery query("SELECT * FROM doctors");
    if (!query.exec()) {
        qDebug() << "Error: execution failed: " << query.lastError();
        return false;
    }

    tableWidget->setColumnCount(10);

    QStringList headers;
    headers << "Doctor Id" << "Specialization" << "Years Of Experience" << "First Name" << "Last name" << "Birthday" << "Gender" << "Phone Number" << "Email" << "Address";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while(query.next()) {
        tableWidget->insertRow(row);

        QString doctorIdNumber = query.value("doctor_id").toString();
        QString specialization = query.value("specialization").toString();
        QString yearsOfExperience = query.value("years_experience").toString();
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString dateOfBirth = query.value("date_of_birth").toString();
        QString gender = query.value("gender").toString();
        QString phoneNumber = query.value("phone_number").toString();
        QString email = query.value("email").toString();
        QString address = query.value("address").toString();

        tableWidget->setItem(row, 0, new QTableWidgetItem(doctorIdNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(specialization));
        tableWidget->setItem(row, 2, new QTableWidgetItem(yearsOfExperience));
        tableWidget->setItem(row, 3, new QTableWidgetItem(firstName));
        tableWidget->setItem(row, 4, new QTableWidgetItem(lastName));
        tableWidget->setItem(row, 5, new QTableWidgetItem(dateOfBirth));
        tableWidget->setItem(row, 6, new QTableWidgetItem(gender));
        tableWidget->setItem(row, 7, new QTableWidgetItem(phoneNumber));
        tableWidget->setItem(row, 8, new QTableWidgetItem(email));
        tableWidget->setItem(row, 9, new QTableWidgetItem(address));

        row++;
    }
    return true;
}

bool DbManager::addEmergency(const QString& healthCardNumber, const QString& firstName, const QString& lastName, const QString& dateOfBirth, const QString& gender, const QString& bloodType, const QString& emergencyContactName, const QString& emergencyContactRelation, const QString& emergencyContactNumber, const QString& emergencyReason, const QString& symptoms, const QString& currentMedicalConditions, const QString& allergies, const QString& medication, const QString& emergencyTime) {

    QSqlQuery queryAddEmergency;
    queryAddEmergency.prepare("INSERT INTO emergencies (health_card_number, first_name, last_name, date_of_birth, gender, blood_type, emergency_contact_number, emergency_contact_relation, emergency_contact_name, emergency_reason, symptoms, current_medical_conditions, allergies, medication, emergency_time) "
                  "VALUES(:healthCardNumber, :firstName, :lastName, :dateOfBirth, :gender, :bloodType, :emergencyContactNumber, :emergencyContactRelation, :emergencyContactName, :emergencyReason, :symptoms, :currentMedicalConditions, :allergies, :medication, :emergencyTime)");
    queryAddEmergency.bindValue(":healthCardNumber", healthCardNumber);
    queryAddEmergency.bindValue(":firstName", firstName);
    queryAddEmergency.bindValue(":lastName", lastName);
    queryAddEmergency.bindValue(":dateOfBirth", dateOfBirth);
    queryAddEmergency.bindValue(":gender", gender);
    queryAddEmergency.bindValue(":bloodType", bloodType);
    queryAddEmergency.bindValue(":emergencyContactNumber", emergencyContactNumber);
    queryAddEmergency.bindValue(":emergencyContactRelation", emergencyContactRelation);
    queryAddEmergency.bindValue(":emergencyContactName", emergencyContactName);
    queryAddEmergency.bindValue(":emergencyReason", emergencyReason);
    queryAddEmergency.bindValue(":symptoms", symptoms);
    queryAddEmergency.bindValue(":currentMedicalConditions", currentMedicalConditions);
    queryAddEmergency.bindValue(":allergies", allergies);
    queryAddEmergency.bindValue(":medication", medication);
    queryAddEmergency.bindValue(":emergencyTime", emergencyTime);

    if(queryAddEmergency.exec()) {
        qDebug() << "Emergency Patient added successfully";
        return true;
    } else {
        qDebug() << "Error: Emergency Patient not added" << queryAddEmergency.lastError().text();
        return false;
    }
}

bool DbManager::viewEmergencyPatient(QTableWidget* tableWidget) {
    QSqlQuery queryEmergency("SELECT * FROM emergencies");

    if (!queryEmergency.exec()) {
        qDebug() << "Error: execution failed" << queryEmergency.lastError();
        return false;
    }

    tableWidget->setColumnCount(15);

    QStringList headers;
    headers << "Health Card" << "First Name" << "Last Name" << "Birthday" << "Gender" << "Blood Type" << "Emergency Contact Name" << "Emergency Contact #" << "Emergency Contact Relation" << "Emergency Reason" << "Symptoms" << "Current Medical Conditions" << "Allergies" << "Medication" << "Time of Emergency";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while (queryEmergency.next()) {
        tableWidget->insertRow(row);

        QString healthCardNumber = queryEmergency.value("health_card_number").toString();
        QString firstName = queryEmergency.value("first_name").toString();
        QString lastName = queryEmergency.value("last_name").toString();
        QString birthday = queryEmergency.value("date_of_birth").toString();
        QString gender = queryEmergency.value("gender").toString();
        QString bloodType = queryEmergency.value("blood_type").toString();
        QString emergencyContactNumber = queryEmergency.value("emergency_contact_number").toString();
        QString emergencyContactRelation = queryEmergency.value("emergency_contact_relation").toString();
        QString emergencyContactName = queryEmergency.value("emergency_contact_name").toString();
        QString emergencyReason = queryEmergency.value("emergency_reason").toString();
        QString symptoms = queryEmergency.value("symptoms").toString();
        QString currentMedicalConditions = queryEmergency.value("current_medical_conditions").toString();
        QString allergies = queryEmergency.value("allergies").toString();
        QString medication = queryEmergency.value("medication").toString();
        QString emergencyTime = queryEmergency.value("emergency_time").toString();

        tableWidget->setItem(row, 0, new QTableWidgetItem(healthCardNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(firstName));
        tableWidget->setItem(row, 2, new QTableWidgetItem(lastName));
        tableWidget->setItem(row, 3, new QTableWidgetItem(birthday));
        tableWidget->setItem(row, 4, new QTableWidgetItem(gender));
        tableWidget->setItem(row, 5, new QTableWidgetItem(bloodType));
        tableWidget->setItem(row, 6, new QTableWidgetItem(emergencyContactName));
        tableWidget->setItem(row, 7, new QTableWidgetItem(emergencyContactNumber));
        tableWidget->setItem(row, 8, new QTableWidgetItem(emergencyContactRelation));
        tableWidget->setItem(row, 9, new QTableWidgetItem(emergencyReason));
        tableWidget->setItem(row, 10, new QTableWidgetItem(symptoms));
        tableWidget->setItem(row, 11, new QTableWidgetItem(currentMedicalConditions));
        tableWidget->setItem(row, 12, new QTableWidgetItem(allergies));
        tableWidget->setItem(row, 13, new QTableWidgetItem(medication));
        tableWidget->setItem(row, 14, new QTableWidgetItem(emergencyTime));

        row++;
    }
    return true;
}


bool DbManager::assignRoom(const QString& healthCardNumber, const QString& roomNumber) {

    QSqlQuery checkRoomQuery;
    checkRoomQuery.prepare("SELECT status FROM rooms WHERE room_number = :roomNumber");
    checkRoomQuery.bindValue(":roomNumber", roomNumber);

    if (!checkRoomQuery.exec()) {
        qDebug() << "Error checking room status: " << checkRoomQuery.lastError();
        return false;
    }

    if (checkRoomQuery.next()) {
        QString status = checkRoomQuery.value(0).toString();
        if (status != "Available") {
            QMessageBox::information(NULL, "Room Assignment", "Room is already occupied.");
            return false;
        }
    } else {
        QMessageBox::critical(NULL, "Error", "Room not found");
        return false;
    }

    QSqlQuery updatePatientQuery;
    updatePatientQuery.prepare("UPDATE patients SET room_number = :roomNumber WHERE health_card_number = :healthCardNumber");
    updatePatientQuery.bindValue(":roomNumber", roomNumber);
    updatePatientQuery.bindValue(":healthCardNumber", healthCardNumber);

    if (!updatePatientQuery.exec()) {
        qDebug() << "Error assigning room: " << updatePatientQuery.lastError();
        return false;
    }

    QSqlQuery insertAssignedRoomQuery;
    insertAssignedRoomQuery.prepare("INSERT INTO room_assignments(room_number, health_card_number, assigned_date) "
                                    "VALUES (:roomNumber, :healthCardNumber, :assignedDate)");
    insertAssignedRoomQuery.bindValue(":roomNumber", roomNumber);
    insertAssignedRoomQuery.bindValue(":healthCardNumber", healthCardNumber);
    insertAssignedRoomQuery.bindValue(":assignedDate", QDate::currentDate().toString("yyyy-MM-dd"));

    if (!insertAssignedRoomQuery.exec()) {
        qDebug() << "Error assigning room: " << insertAssignedRoomQuery.lastError();
        return false;
    }

    QSqlQuery updateStatusQuery;
    updateStatusQuery.prepare("UPDATE rooms SET status = 'Occupied' WHERE room_number = :roomNumber");
    updateStatusQuery.bindValue(":roomNumber", roomNumber);

    if (!updateStatusQuery.exec()) {
        qDebug() << "Error updating status of room: " << updateStatusQuery.lastError();
        return false;
    }

    QMessageBox::information(NULL, "Room Assignment", "Room assigned Successfully");
    return true;
}

bool DbManager::viewRooms(QTableWidget* tableWidget) {

    QSqlQuery query;
    query.prepare("SELECT * FROM rooms");

    if (!query.exec()) {
        qDebug() << "Error: execution failed: " << query.lastError();
        return false;
    }

    tableWidget->setColumnCount(3);
    QStringList headers;
    headers << "Room Number" << "Room Type" << "Status";
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setRowCount(0);
    int row = 0;

    while(query.next()) {
        tableWidget->insertRow(row);

        QString roomNumber = query.value("room_number").toString();
        QString roomType = query.value("room_type").toString();
        QString roomStatus = query.value("status").toString();

        tableWidget->setItem(row, 0, new QTableWidgetItem(roomNumber));
        tableWidget->setItem(row, 1, new QTableWidgetItem(roomType));
        tableWidget->setItem(row, 2, new QTableWidgetItem(roomStatus));

        row++;
    }
    return true;
}

bool DbManager::addRoom(const QString &roomNumber, const QString &roomType, const QString &status)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO rooms (room_number, room_type, status) "
                  "VALUES (:roomNumber, :roomType, :status)");
    query.bindValue(":roomNumber", roomNumber);
    query.bindValue(":roomType", roomType);
    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Add room failed:" << query.lastError().text();
        return false;
    }

    return true;
}


bool DbManager::changeRoomStatus(const QString& healthCardNumber, const QString& roomNumber) {

    QSqlQuery updatePatientQuery;
    updatePatientQuery.prepare("UPDATE patients SET room_number = NULL WHERE health_card_number = :healthCardNumber");
    updatePatientQuery.bindValue(":healthCardNumber", healthCardNumber);

    if (!updatePatientQuery.exec()) {
        qDebug() << "Error updating patients record: " << updatePatientQuery.lastError();
        return false;
    }

    QSqlQuery updateRoomQuery;
    updateRoomQuery.prepare("UPDATE rooms SET status = 'Available' WHERE room_number = :roomNumber");
    updateRoomQuery.bindValue(":roomNumber", roomNumber);

    if (!updateRoomQuery.exec()) {
        qDebug() << "Error updating room status: " << updateRoomQuery.lastError();
        return false;
    }

    QSqlQuery deleteAssignedRoomQuery;
    deleteAssignedRoomQuery.prepare("DELETE FROM room_assignments WHERE room_number = :roomNumber AND health_card_number = :healthCardNumber");
    deleteAssignedRoomQuery.bindValue(":roomNumber", roomNumber);
    deleteAssignedRoomQuery.bindValue(":healthCardNumber", healthCardNumber);

    if (!deleteAssignedRoomQuery.exec()) {
        qDebug() << "Error deleting room assignments: " << deleteAssignedRoomQuery.lastError();
        return false;
    }
    return true;
}

void DbManager::createTables() {
    QSqlQuery query(m_db);

    query.exec("CREATE TABLE IF NOT EXISTS patients ("
               "health_card_number TEXT PRIMARY KEY,"
               "first_name TEXT,"
               "last_name TEXT,"
               "date_of_birth TEXT,"
               "gender TEXT,"
               "blood_type TEXT,"
               "address TEXT,"
               "phone_number TEXT,"
               "email_address TEXT,"
               "insurance_company TEXT,"
               "primary_care_physician TEXT,"
               "room_number TEXT"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS doctors ("
               "doctor_id TEXT PRIMARY KEY,"
               "specialization TEXT,"
               "years_experience TEXT,"
               "first_name TEXT,"
               "last_name TEXT,"
               "date_of_birth TEXT,"
               "gender TEXT,"
               "phone_number TEXT,"
               "email TEXT,"
               "address TEXT"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS emergencies ("
               "health_card_number TEXT PRIMARY KEY,"
               "first_name TEXT,"
               "last_name TEXT,"
               "date_of_birth TEXT,"
               "gender TEXT,"
               "blood_type TEXT,"
               "emergency_contact_number TEXT,"
               "emergency_contact_relation TEXT,"
               "emergency_contact_name TEXT,"
               "emergency_reason TEXT,"
               "symptoms TEXT,"
               "current_medical_conditions TEXT,"
               "allergies TEXT,"
               "medication TEXT,"
               "emergency_time TEXT"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS rooms ("
               "room_number TEXT PRIMARY KEY,"
               "room_type TEXT,"
               "status TEXT"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS room_assignments ("
               "room_number TEXT,"
               "health_card_number TEXT,"
               "assigned_date TEXT"
               ");");
}

