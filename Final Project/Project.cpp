#include <iostream>
#include <string>
using namespace std;

class Medicine {
private:
    int medicineID;
    string medicineName;

public:
    Medicine(int id, const string& name);
    int getID();
    string getName();
};

class PPC;

class Person {
private:
    string name;
    int cnic, age;
    char gender;

public:
    Person(string nam, int cni, int ag, char gen);
    string getName();
    int getCNIC();
    int getAge();
    char getGender();
};

class Hospital;

class Doctor {
private:
    int Doc_ID;
    string Specialization;
    Hospital* hospital;

public:
    Doctor(Hospital* hosp, int doc, string spec);
    int getID();
    string getSpecialization();
};

class Patient {
private:
    int Pat_ID;
    string Disease;
    Medicine* medicine;

public:
    Patient(int pat, string dis);
    int getID();
    string getDisease();
    void setMedicine(Medicine* med);
    Medicine* getMedicine();
};

class Pharmacy;

class Pharmacist : public Person {
private:
    int Pharmacist_ID;

public:
    Pharmacist(int pharmID, string nam, int cni, int ag, char gen);
    int getID();
    void treatPatient(Patient* patient);
};

class PPC {
protected:
    int PPC_HQ_ID;
    string HQ;

public:
    PPC(int id);
    int getID();
};

class Supplier : public Person, public PPC {
private:
    int Supplier_ID;
    Medicine** suppliedMedicines;
    int numMedicines;

public:
    void addMedicine(Medicine* med);
    Medicine* getMedicine(int medicineID);
    Supplier(int supplier, int ppcID, string nam, int cni, int ag, char gen);
    int getID();
};

class Hospital : public PPC {
private:
    int Hosp_ID;
    string Hosp_Loc, Hosp_Name;
    Doctor** doctors;
    int numDoctors;
    Patient** patients;
    int numPatients;

public:
    Hospital(int hospID, int ppcID, string HospLoc, string HospName);
    int getID();
    void addPatient(Patient* patient);
    Patient* getPatientByCNIC(int cnic);
    string getHospLoc();
    string getHospName();
    void setDoctors(Doctor* doc);
    Doctor* getDoctor(int docID);
};

class Pharmacy : public PPC {
private:
    int Pharm_ID;
    string Pharm_Name, Pharm_Loc;
    Pharmacist** pharmacists;
    int numPharmacists;
    Medicine** availableMedicines;
    int numAvailableMedicines;

public:
    Pharmacy(int ppcID, int ID, string name, string loc);
    int getID();
    string getPharmName();
    string getPharmLoc();
    int getMedicineNumber();
    int getPharmacistNumber();
    void setPharmacists(Pharmacist* pharm);
    void addPharmacist(Pharmacist pharm);
    Pharmacist* getPharmacist(int pharmID);
    void addMedicine(Medicine* med);
    Medicine* getMedicine(int medicineID);
    void treatPatient(Patient* patient);
};

Person::Person(string nam, int cni, int ag, char gen) : name(nam), cnic(cni), age(ag), gender(gen) {}

string Person::getName() {
    return name;
}

int Person::getCNIC() {
    return cnic;
}

int Person::getAge() {
    return age;
}

char Person::getGender() {
    return gender;
}

Doctor::Doctor(Hospital* hosp, int doc, string spec) : hospital(hosp), Doc_ID(doc), Specialization(spec) {}

int Doctor::getID() {
    return Doc_ID;
}

string Doctor::getSpecialization() {
    return Specialization;
}

Hospital::Hospital(int hospID, int ppcID, string HospLoc, string HospName) : PPC(ppcID), Hosp_ID(hospID), Hosp_Loc(HospLoc), Hosp_Name(HospName) {
    doctors = new Doctor*[10];
    numDoctors = 0;
    patients = new Patient*[10];
    numPatients = 0;
}

int Hospital::getID() {
    return Hosp_ID;
}

void Hospital::addPatient(Patient* patient) {
    patients[numPatients++] = patient;
}

Patient* Hospital::getPatientByCNIC(int cnic) {
    for (int i = 0; i < numPatients; i++) {
        if (patients[i]->getID() == cnic) {
            return patients[i];
        }
    }
    return NULL;
}

string Hospital::getHospLoc() {
    return Hosp_Loc;
}

string Hospital::getHospName() {
    return Hosp_Name;
}

void Hospital::setDoctors(Doctor* doc) {
    doctors[numDoctors++] = doc;
}

Doctor* Hospital::getDoctor(int docID) {
    for (int i = 0; i < numDoctors; i++) {
        if (doctors[i]->getID() == docID) {
            return doctors[i];
        }
    }
    return NULL;
}

Pharmacy::Pharmacy(int ppcID, int ID, string name, string loc) : PPC(ppcID), Pharm_ID(ID), Pharm_Name(name), Pharm_Loc(loc) {
    pharmacists = new Pharmacist*[10];
    numPharmacists = 0;
    availableMedicines = new Medicine*[10];
    numAvailableMedicines = 0;
}

int Pharmacy::getID() {
    return Pharm_ID;
}
int Pharmacy::getMedicineNumber(){
    return numAvailableMedicines;
}

int Pharmacy::getPharmacistNumber(){
    return numPharmacists;
}

void Pharmacy::addPharmacist(Pharmacist pharm){
    
}

string Pharmacy::getPharmName() {
    return Pharm_Name;
}

string Pharmacy::getPharmLoc() {
    return Pharm_Loc;
}

void Pharmacy::setPharmacists(Pharmacist* pharm) {
    pharmacists[numPharmacists++] = pharm;
}

Pharmacist* Pharmacy::getPharmacist(int pharmID) {
    for (int i = 0; i < numPharmacists; i++) {
        if (pharmacists[i]->getID() == pharmID) {
            return pharmacists[i];
        }
    }
    return NULL;
}

void Pharmacy::addMedicine(Medicine* med) {
    availableMedicines[numAvailableMedicines++] = med;
}

Medicine* Pharmacy::getMedicine(int medicineID) {
    for (int i = 0; i < numAvailableMedicines; i++) {
        if (availableMedicines[i]->getID() == medicineID) {
            return availableMedicines[i];
        }
    }
    return NULL;
}

void Pharmacy::treatPatient(Patient* patient) {
    Medicine* medicine = patient->getMedicine();
    bool found = false;
    for (int i = 0; i < numAvailableMedicines; i++) {
        if (availableMedicines[i] == medicine) {
            found = true;
            break;
        }
    }
    if (found) {
        cout << "Pharmacist is treating patient with medicine: " << medicine->getName() << endl;
    } else {
        cout << "Pharmacist cannot treat the patient with the requested medicine." << endl;
    }
}

Pharmacist::Pharmacist(int pharmID, string nam, int cni, int ag, char gen)
    : Person(nam, cni, ag, gen), Pharmacist_ID(pharmID) {}

int Pharmacist::getID() {
    return Pharmacist_ID;
}

void Pharmacist::treatPatient(Patient* patient) {
    pharmacy->treatPatient(patient);
}

Patient::Patient(int pat, string dis) : Pat_ID(pat), Disease(dis), medicine(NULL) {}

int Patient::getID() {
    return Pat_ID;
}

string Patient::getDisease() {
    return Disease;
}

void Patient::setMedicine(Medicine* med) {
    medicine = med;
}

Medicine* Patient::getMedicine() {
    return medicine;
}

Medicine::Medicine(int id, const string& name) : medicineID(id), medicineName(name) {}

int Medicine::getID() {
    return medicineID;
}

string Medicine::getName() {
    return medicineName;
}

PPC::PPC(int id) : PPC_HQ_ID(id) {}

int PPC::getID() {
    return PPC_HQ_ID;
}

Supplier::Supplier(int supplier, int ppcID, string nam, int cni, int ag, char gen)
    : Person(nam, cni, ag, gen), PPC(ppcID), Supplier_ID(supplier) {
    suppliedMedicines = new Medicine*[10];
    numMedicines = 0;
}

void Supplier::addMedicine(Medicine* med) {
    suppliedMedicines[numMedicines++] = med;
}

Medicine* Supplier::getMedicine(int medicineID) {
    for (int i = 0; i < numMedicines; i++) {
        if (suppliedMedicines[i]->getID() == medicineID) {
            return suppliedMedicines[i];
        }
    }
    return NULL;
}

int Supplier::getID() {
    return Supplier_ID;
}
int main() {
    PPC ppc(1);
    Hospital hospital(1, ppc.getID(), "Hospital Location", "Hospital Name");
    Pharmacy pharmacy(ppc.getID(), 1, "Pharmacy Name", "Pharmacy Location");
    Supplier supplier(1, ppc.getID(), "Supplier Name", 12345, 35, 'M');
    Doctor doctor(&hospital, 1, "Specialization");
    Pharmacist pharmacist(&pharmacy, 1, "Pharmacist Name", 67890, 28, 'F');
    Medicine medicine1(1, "Brufen");
    Medicine medicine2(2, "Medicine 2");
    hospital.setDoctors(&doctor);
    pharmacy.setPharmacists(&pharmacist);
    // Add supplied medicines to the pharmacy
    supplier.addMedicine(&medicine1);
    supplier.addMedicine(&medicine2);
    pharmacy.addMedicine(&medicine2);
    int currentMenu = 0;
    int choice;
    while (true) {
        if (currentMenu == 0) {
            // Main menu
            cout << "--------- Menu ---------" << endl;
            cout << "1. Doctor Menu" << endl;
            cout << "2. Pharmacist Menu" << endl;
            cout << "3. Exit" << endl;
            cout << "-------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    currentMenu = 1; // Switch to doctor menu
                    break;
                }
                case 2: {
                    currentMenu = 2; // Switch to pharmacist menu
                    break;
                }
                case 3: {
                    cout << "Exiting program..." << endl;
                    return 0;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
        else if (currentMenu == 1) {
            // Doctor menu
            int doctorChoice;
            bool backToMainMenu = false;  // Flag to indicate if user wants to go back to the main menu

            while (!backToMainMenu) {
                cout << "--------- Doctor Menu ---------" << endl;
                cout << "1. Find a patient by CNIC" << endl;
                cout << "2. Add a patient" << endl;
                cout << "3. Back to main menu" << endl;
                cout << "-----------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> doctorChoice;

                switch (doctorChoice) {
                    case 1: {
                        // Existing code for finding a patient by CNIC
                        int patientID;
                        cout << "Enter patient ID: ";
                        cin >> patientID;
                        Patient* patient = hospital.getPatientByCNIC(patientID);
                        if (patient) {
                            cout << "Patient found. Patient ID: " << patient->getID() << endl;
                            cout << "Disease: " << patient->getDisease() << endl;
                            cout << "Assigned medicine: " << patient->getMedicine()->getName() << endl;
                        } else {
                            cout << "Patient not found." << endl;
                        }
                        break;
                    }
                    case 2: {
                        // Existing code for adding a patient
                        int patientID ,medID;
                        string disease;
                        cout << "Enter patient ID: ";
                        cin >> patientID;
                        cout << "Enter medID: ";
                        cin >> medID;
                        cout << "Enter disease: ";
                        cin.ignore();
                        getline(cin, disease);
                        Patient* patient = new Patient(patientID, disease);  // Allocate patient dynamically
                        Medicine* medicine = supplier.getMedicine(medID);
                        if (medicine) {
                            patient->setMedicine(medicine);
                            hospital.addPatient(patient);  // Store the patient pointer in the hospital
                            cout << "Patient added successfully." << endl;
                        } else {
                            cout << "Medicine not found for the patient." << endl;
                            delete patient;  // Cleanup memory in case medicine is not found
                        }
                        break;
                    }
                    case 3: {
                        cout << "Returning to the main menu." << endl;
                        backToMainMenu = true;  // Set the flag to true to exit the doctor menu
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            }
            currentMenu = 0;  // Switch back to the main menu
        }
        else if (currentMenu == 2) {
            // Pharmacist menu
            int pharmacistChoice;
            bool backToMainMenu = false;  // Flag to indicate if user wants to go back to the main menu
            while (!backToMainMenu) {
                cout << "--------- Pharmacist Menu ---------" << endl;
                cout << "1. Find Patient" << endl;
                cout << "2. Treat a Patient" << endl;
                cout << "3. Back to main menu" << endl;
                cout << "4.Add Medicine" << endl;
                cout << "-------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> pharmacistChoice;
                switch (pharmacistChoice) {
                    case 1: {
                        int patientID;
                        cout << "Enter patient ID: ";
                        cin >> patientID;
                        Patient* patient = hospital.getPatientByCNIC(patientID);
                        if (patient) {
                            cout << "Patient found. Patient ID: " << patient->getID() << endl;
                            cout << "Disease: " << patient->getDisease() << endl;
                            cout << "Assigned medicine: " << patient->getMedicine()->getName() << endl;
                        }
                        else {
                            cout << "Patient not found." << endl;
                        }
                        break;
                        break;
                    }
                    case 2: {
                        // Existing code for adding a medicine
                        int patientID;
                        cout << "Enter patient ID: ";
                        cin >> patientID;
                        Patient* patient = hospital.getPatientByCNIC(patientID);
                        if (patient) {
                            pharmacist.treatPatient(patient);
                        } else {
                            cout << "Patient not found." << endl;
                        }
                        break;
                    }
                    case 3: {
                        cout << "Returning to the main menu." << endl;
                        backToMainMenu = true;  // Set the flag to true to exit the pharmacist menu
                        break;
                    }
                    case 4: {
                        int medicineID;
                        cout << "Enter medicine ID: ";
                        cin >> medicineID;
                        Medicine* medicine = supplier.getMedicine(medicineID);
                        if (medicine) {
                            pharmacy.addMedicine(medicine);
                            cout << "Medicine added successfully." << endl;
                        } else {
                            cout << "Medicine not found." << endl;
                        }
                        break;
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            }
            currentMenu = 0;  // Switch back to the main menu
        }
        else if(currentMenu == 3) {
            int opt, num;
            Pharmacist** pharmacists;
            Medicine** availableMedicines;
            cout << "Select";
            cin >> opt;
            if (opt == 1){
                num = pharmacy.getPharmacistNumber();
                pharmacists = pharmacy.getPharmacist();
                for (int i = 0; i <= num; i++){
                    cout << i+1 << ". Name: " << pharmacists[i].getName() << "\nID: " << pharmacists.getID() << endl;
                }
            }
            else if (opt == 2){
                num = pharmacy.getMedicineNumber();
                availableMedicines = pharmacy.getMedicine();
                for (int i = 0; i <= num; i++){
                    cout << i+1 << ". Name: " << availableMedicines[i].getName() << "\t|\tID: " << availableMedicines.getID() << endl;
                }
            }
            else if (opt == 3){
                string name;
                int id, cni, ag;
                char gen;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter CNIC: ";
                cin >> cni;
                cout << "Enter Age: ";
                cin >> ag;
                cout << "Enter Gender (M/F): ";
                cin >> gen;
                Pharmacist pharmacistadded(id, nam, cni, ag, gen);
            }
        }
    }
	
    return 0;
}
