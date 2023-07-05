#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class Medicine
{
private:
    int medicineID;
    string medicineName;

public:
    Medicine(int id, const string &name);
    int getID();
    string getName();
};

class PPC;

class Person
{
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

class Doctor : public Person
{
private:
    int Doc_ID;
    string Specialization;
    Hospital *hospital;

public:
    Doctor(Hospital *hosp, int doc, string spec, string nam, int cni, int ag, char gen);
    int getID();
    Hospital *getHospital();
    string getSpecialization();
};

class Patient : public Person
{
private:
    int Pat_ID;
    string Disease;
    Medicine *medicine;

public:
    Patient(int pat, string dis, string nam, int cni, int ag, char gen);
    int getID();
    string getDisease();
    void setDisease(string dis);
    void setMedicine(Medicine *med);
    Medicine *getMedicine();
};

class Pharmacy;

class Pharmacist : public Person
{
private:
    int Pharmacist_ID;
    Pharmacy *pharmacy;

public:
    Pharmacist(Pharmacy *pharm, int pharmID, string nam, int cni, int ag, char gen);
    int getID();
    void treatPatient(Patient *patient);
};

class PPC
{
protected:
    int PPC_HQ_ID;
    string HQ;

public:
    PPC(int id);
    int getID();
};

class Supplier : public Person, public PPC
{
private:
    int Supplier_ID;

public:
    void addMedicine(Medicine *med);
    Medicine *getMedicine(int medicineID);
    Supplier(int supplier, int ppcID, string nam, int cni, int ag, char gen);
    int getID();
};

class Hospital : public PPC
{
private:
    int Hosp_ID;
    string Hosp_Loc, Hosp_Name;

public:
    Hospital(int hospID, int ppcID, string HospLoc, string HospName);
    int getID();
    void addPatient(Patient *patient);
    Patient *getPatientByCNIC(int cnic);
    string getHospLoc();
    string getHospName();
    Doctor *getDoctor(int docID);
    void addDoctor(Doctor *doc);
};

class Pharmacy : public PPC
{
private:
    int Pharm_ID;
    string Pharm_Name, Pharm_Loc;

public:
    Pharmacy(int ppcID, int ID, string name, string loc);
    int getID();
    string getPharmName();
    string getPharmLoc();
    Pharmacist *getPharmacist(int pharmID);
    void addMedicine(Medicine *med);
    void addPharmacist(Pharmacist *pharm);
    Medicine *getMedicine(int medicineID);
    void treatPatient(Patient *patient);
};

Person::Person(string nam, int cni, int ag, char gen) : name(nam), cnic(cni), age(ag), gender(gen) {}

string Person::getName()
{
    return name;
}

int Person::getCNIC()
{
    return cnic;
}

int Person::getAge()
{
    return age;
}

char Person::getGender()
{
    return gender;
}

Doctor::Doctor(Hospital *hosp, int doc, string spec, string nam, int cni, int ag, char gen) : Person(nam, cni, ag, gen), hospital(hosp), Doc_ID(doc), Specialization(spec) {}

int Doctor::getID()
{
    return Doc_ID;
}

Hospital *Doctor::getHospital()
{
    return hospital;
}

string Doctor::getSpecialization()
{
    return Specialization;
}

Hospital::Hospital(int hospID, int ppcID, string HospLoc, string HospName) : PPC(ppcID), Hosp_ID(hospID), Hosp_Loc(HospLoc), Hosp_Name(HospName) {}


int Hospital::getID()
{
    return Hosp_ID;
}

void Hospital::addPatient(Patient *patient)
{
    // add patient to file
    fstream file;
    file.open("Patients.txt", ios::app);
    file << patient->getID() << "\t";
    file << patient->getName() << "\t";
    file << patient->getCNIC() << "\t";
    file << patient->getAge() << "\t";
    file << patient->getGender() << "\t";
    file << patient->getDisease() << "\t";
    file << patient->getMedicine()->getID() << "\t";
    file << patient->getMedicine()->getName() << "\t";
    file << endl;
    file.close();
}

Patient *Hospital::getPatientByCNIC(int PatID)
{
    //retrive data from patient file and return patient object
    fstream file;
    //if file is not present, then return file not found
    file.open("Patients.txt", ios::in);
    int id, cni, age, medID;
    char gen;
    string name, dis, medName, inp;
    Medicine *med;
    do{
        getline(file, inp);
        istringstream iss(inp);
        iss >> id >> name >> cni >> age >> gen >> dis >> medID >> medName;
        if (id == PatID)
        {
            Patient *patient = new Patient(id, dis, name, cni, age, gen);
            if (medID != NULL)
            {
                med = new Medicine(medID, medName);
            }
            else
            {
                med = NULL;
            }
            patient->setMedicine(med);
            file.close();
            return patient;
        }
    }
    while(!file.eof());
    file.close();
    return NULL;
    
}

string Hospital::getHospLoc()
{
    return Hosp_Loc;
}

string Hospital::getHospName()
{
    return Hosp_Name;
}

Doctor *Hospital::getDoctor(int docID)
{
    //retrive data from doctor file and return doctor object
    fstream file;
    //if file is not present, then return file not found
    file.open("Doctor.txt", ios::in);
    int id, cni, age, hospID;
    char gen;
    string name, spec, hospLoc, hospName, inp;
    Hospital *hosp;
    do{
        getline(file, inp);
        istringstream iss(inp);
        iss >> id >> name >> cni >> age >> gen >> spec >> hospID >> hospLoc >> hospName;
        if (id == docID)
        {
            hosp = new Hospital(hospID, PPC_HQ_ID, hospLoc, hospName);
            Doctor *doc = new Doctor(hosp, id, spec, name, cni, age, gen);
            file.close();
            return doc;
        }
    }
    while(!file.eof());
    file.close();
    return NULL;
}

void Hospital::addDoctor(Doctor *doc)
{
    // add doctor to file
    fstream file;
    file.open("Doctor.txt", ios::app);
    file << doc->getID() << "\t";
    file << doc->getName() << "\t";
    file << doc->getCNIC() << "\t";
    file << doc->getAge() << "\t";
    file << doc->getGender() << "\t";
    file << doc->getSpecialization() << "\t";
    //file << doc->getHospital()->getID() << "\t";
    file << doc->getHospital()->getHospLoc() << "\t";
    file << doc->getHospital()->getHospName() << "\n";
    file.close();
}

Pharmacy::Pharmacy(int ppcID, int ID, string name, string loc) : PPC(ppcID), Pharm_ID(ID), Pharm_Name(name), Pharm_Loc(loc){}

int Pharmacy::getID()
{
    return Pharm_ID;
}

string Pharmacy::getPharmName()
{
    return Pharm_Name;
}

string Pharmacy::getPharmLoc()
{
    return Pharm_Loc;
}

Pharmacist *Pharmacy::getPharmacist(int pharmID)
{
    //retrive data from pharmacist file and return pharmacist object
    fstream file;
    file.open("Pharmacist.txt", ios::in);
    int id, cni, age;
    char gen;
    string name, pharmLoc, pharmName, inp;
    Pharmacy *pharm;
    do{
        getline(file, inp);
        istringstream iss(inp);
        iss >> id >> name >> cni >> age >> gen >> pharmLoc >> pharmName;
        if (id == pharmID)
        {
            pharm = new Pharmacy(PPC_HQ_ID, pharmID, pharmName, pharmLoc);
            Pharmacist *pharmacist = new Pharmacist(pharm, id, name, cni, age, gen);
            file.close();
            return pharmacist;
        }
    }
    while(!file.eof());
    file.close();
    return NULL;
}
void Pharmacy::addPharmacist(Pharmacist *pharm)
{
    // add pharmacist to file
    fstream file;
    file.open("Pharmacist.txt", ios::app);
    file << pharm->getID() << "\t";
    file << pharm->getName() << "\t";
    file << pharm->getCNIC() << "\t";
    file << pharm->getAge() << "\t";
    file << pharm->getGender() << "\t";
    file << getPharmLoc() << "\t";
    file << getPharmName() << "\n";
    file.close();
}
void Pharmacy::addMedicine(Medicine *med)
{
    // add medicine to file
    fstream file;
    file.open("MedicinePharmacy.txt", ios::app);
    file << med->getID() << "\t";
    file << med->getName() << "\t";
    //file << getID() << "\t";
    file << getPharmLoc() << "\t";
    file << getPharmName() << "\n";
    file.close();
}

Medicine *Pharmacy::getMedicine(int medicineID)
{
    //retrive data from medicine file and return medicine object
    fstream file;
    file.open("MedicinePharmacy.txt", ios::in);
    int id;
    string name, inp;
    do{
        getline(file, inp);
        istringstream iss(inp);
        iss >> id >> name;
        if (id == medicineID)
        {
            Medicine *medicine = new Medicine(id, name);
            file.close();
            return medicine;
        }
    }
    while(!file.eof());
    file.close();
    return NULL;
}

void Pharmacy::treatPatient(Patient *patient)
{
cout<<"Treating Patient..."<<endl;
 cout << "Patient treated successfully." << endl;
    // Retrieve the medicine from the patient object and check if it is available in the pharmacy
    // Medicine *medicine = patient->getMedicine();
    // bool found = false;
    // for (int i = 0; i < numAvailableMedicines; i++)
    // {
    //     if (availableMedicines[i] == medicine)
    //     {
    //         found = true;
    //         break;
    //     }
    // }
    // if (found)
    // {
    //     cout << "Pharmacist is treating patient with medicine: " << medicine->getName() << endl;
    // }
    // else
    // {
    //     cout << "Pharmacist cannot treat the patient with the requested medicine." << endl;
    // }
}

Pharmacist::Pharmacist(Pharmacy *pharm, int pharmID, string nam, int cni, int ag, char gen)
    : Person(nam, cni, ag, gen), pharmacy(pharm), Pharmacist_ID(pharmID) {}

int Pharmacist::getID()
{
    return Pharmacist_ID;
}

void Pharmacist::treatPatient(Patient *patient)
{
    pharmacy->treatPatient(patient);
}

Patient::Patient(int pat, string dis, string nam, int cni, int ag, char gen) : Person(nam, cni, ag, gen), Pat_ID(pat), Disease(dis) {}
int Patient::getID()
{
    return Pat_ID;
}

string Patient::getDisease()
{
    return Disease;
}

void Patient::setDisease(string dis)
{
    Disease = dis;
}

void Patient::setMedicine(Medicine *med)
{
    medicine = med;
}

Medicine *Patient::getMedicine()
{
    return medicine;
}

Medicine::Medicine(int id, const string &name) : medicineID(id), medicineName(name) {}

int Medicine::getID()
{
    return medicineID;
}

string Medicine::getName()
{
    return medicineName;
}

PPC::PPC(int id) : PPC_HQ_ID(id) {}

int PPC::getID()
{
    return PPC_HQ_ID;
}

Supplier::Supplier(int supplier, int ppcID, string nam, int cni, int ag, char gen)
    : Person(nam, cni, ag, gen), PPC(ppcID), Supplier_ID(supplier) {}

void Supplier::addMedicine(Medicine *med)
{
    // add medicine to file MedicineSupplier.txt
    fstream file;
    file.open("MedicineSupplier.txt", ios::app);
    file << med->getID() << "\t";
    file << med->getName() << "\t";
    file << getID() << "\n";
    file.close();
}

Medicine *Supplier::getMedicine(int medicineID)
{
    //retrive data from medicine file and return medicine object
    fstream file;
    file.open("MedicineSupplier.txt", ios::in);
    int id;
    string name, inp;
    do{
        getline(file, inp);
        istringstream iss(inp);
        iss >> id >> name;
        if (id == medicineID)
        {
            Medicine *medicine = new Medicine(id, name);
            file.close();
            return medicine;
        }
    }
    while(!file.eof());
    file.close();
    return NULL;
}

int Supplier::getID()
{
    return Supplier_ID;
}
int main()
{
    PPC ppc(1);
    Hospital hospital(1, ppc.getID(), "Shadman", "Fatima Memorial");
    Pharmacy pharmacy(ppc.getID(), 1, "Clinix", "Gulberg");
    Supplier supplier(1, ppc.getID(), "Supplier Name", 12345, 35, 'M');
    // create a doctor object
    Doctor doctor(&hospital, 1, "Pathologist", "Huzaifa", 12345, 35, 'M');
    // Doctor doctor(&hospital, 1, "Specialization");
    Pharmacist pharmacist(&pharmacy, 1, "Asad", 67890, 28, 'F');
    Medicine medicine1(1, "Brufen");
    Medicine medicine2(2, "Panadol");

    // Add doctors and pharmacists to the hospital and pharmacy files
    hospital.addDoctor(&doctor);
    pharmacy.addPharmacist(&pharmacist);
    // hospital.setDoctors(&doctor);
    // pharmacy.setPharmacists(&pharmacist);

    // Add supplied medicines to the pharmacy
    supplier.addMedicine(&medicine1);
    supplier.addMedicine(&medicine2);
    //pharmacy.addMedicine(&medicine2);
    int choice;

    while (true)
    {
        // Main menu
        cout << "--------- WELCOME TO HEALTHCARE MANAGEMENT SYSTEM -  BY HASSAN AND SHAHREZ ---------" << endl;
        cout << "--------- MAIN MENU ---------" << endl;
        cout << "--------- Choose your option below ---------" << endl;
        cout << "1. Doctor Menu" << endl;
        cout << "2. Pharmacist Menu" << endl;
        cout << "3. Pharmacy Menu" << endl;
        cout << "4. Hospital Menu" << endl;
        cout << "5. Exit" << endl;
        cout << "-------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Doctor menu
            int doctorChoice;
            bool backToMainMenu = false; // Flag to indicate if user wants to go back to the main menu

            while (!backToMainMenu)
            {
                cout << "---------  DOCTOR MENU ---------" << endl;
                cout << "--------- Choose your option below ---------" << endl;
                cout << "1. Find a patient by ID" << endl;
                cout << "2. Add a patient" << endl;
                cout << "3. Back to main menu" << endl;
                cout << "-----------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> doctorChoice;

                switch (doctorChoice)
                {
                case 1:
                {
                    // Existing code for finding a patient by CNIC
                    int patientID;
                    cout << "Enter patient ID: ";
                    cin >> patientID;
                    Patient *patient = hospital.getPatientByCNIC(patientID);
                    if (patient)
                    {
                        cout << "Patient found. Patient ID: " << patient->getID() << endl;
                        cout << "Name: " << patient->getName() << endl;
                        if (patient->getDisease() != "NULL")
                        {
                            cout << "Disease: " << patient->getDisease() << endl;
                            cout << "Assigned medicine: " << patient->getMedicine()->getName() << endl;
                        }
                        else
                        {
                            cout << "Patient not diagnosed yet." << endl;
                            // set disease
                            string disease;
                            cout << "Enter disease: ";
                            cin >> disease;
                            patient->setDisease(disease);
                            // set medicine
                            int medID;
                            cout << "Enter medID: ";
                            cin >> medID;
                            Medicine *med = supplier.getMedicine(medID);
                            if (med)
                            {
                                patient->setMedicine(med);
                                cout << "Medicine assigned." << endl;
                            }
                            else
                            {
                                cout << "Medicine not found." << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Patient not found." << endl;
                    }
                    break;
                }
                case 2:
                {
                    // Existing code for adding a patient

                    int medID;
                    cout << "Enter medID: ";
                    cin >> medID;
                    int patientID;
                    string name, disease;
                    int cnic;
                    int age;
                    char gender;
                    cout << "Enter Patient ID: ";
                    cin >> patientID;
                    cout << "Enter Patient Name: ";
                    cin >> name;
                    cout << "Enter Patient CNIC: ";
                    cin >> cnic;
                    cout << "Enter Patient Age: ";
                    cin >> age;
                    cout << "Enter Patient Gender: ";
                    cin >> gender;
                    cout << "Enter Patient Disease: ";
                    cin.ignore();
                    getline(cin, disease);
                    Patient *patient = new Patient(patientID, disease, name, cnic, age, gender);
                    Medicine *medicine = supplier.getMedicine(medID);
                    if (medicine)
                    {
                        patient->setMedicine(medicine);
                        hospital.addPatient(patient); // Store the patient pointer in the hospital
                        cout << "Patient added successfully." << endl;
                    }
                    else
                    {
                        cout << "Medicine not found for the patient." << endl;
                        delete patient; // Cleanup memory in case medicine is not found
                    }
                    break;
                }
                case 3:
                {
                    cout << "Returning to the main menu." << endl;
                    backToMainMenu = true; // Set the flag to true to exit the doctor menu
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
            break;
        }
        case 2:
        {
            // Pharmacist menu
            int pharmacistChoice;
            bool backToMainMenu = false; // Flag to indicate if user wants to go back to the main menu

            while (!backToMainMenu)
            {
                cout << "--------- PHARMACIST MENU ---------" << endl;
                   
        cout << "--------- Choose your option below ---------" << endl;
                cout << "1. Find Patient" << endl;
                cout << "2. Treat a Patient" << endl;
                cout << "3. Add Medicine" << endl;
                cout << "4. Back to main menu" << endl;
                cout << "-------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> pharmacistChoice;

                switch (pharmacistChoice)
                {
                case 1:
                {
                    int patientID;
                    cout << "Enter patient ID: ";
                    cin >> patientID;
                    Patient *patient = hospital.getPatientByCNIC(patientID);
                    if (patient)
                    {
                        cout << "Patient found. Patient ID: " << patient->getID() << endl;
                        cout << "Name: " << patient->getName() << endl;
                        cout << "Disease: " << patient->getDisease() << endl;
                        cout << "Assigned medicine: " << patient->getMedicine()->getName() << endl;
                    }
                    else
                    {
                        cout << "Patient not found." << endl;
                    }
                    break;
                    break;
                }
                case 2:
                {
                    // Existing code for adding a medicine
                    int patientID;
                    cout << "Enter patient ID: ";
                    cin >> patientID;
                    Patient *patient = hospital.getPatientByCNIC(patientID);
                    if (patient)
                    {		
                        	Medicine *med = pharmacy.getMedicine(patient->getMedicine()->getID());
                        	//cout<<"Patient found"<<endl;
                        	if (med){
							cout<<"Medicine Found"<<endl;
                            pharmacist.treatPatient(patient);
                           
                            
                        }
                        else{
                        	cout<<"Medicine not found!"<<endl;
                        	
						}
                        break;
                    }
                    else
                    {
                        cout << "Patient not found." << endl;
                    }
                    break;
                }
                case 3:
                {
                    int medicineID;
                    cout << "Enter medicine ID: ";
                    cin >> medicineID;
                    Medicine *medicine = supplier.getMedicine(medicineID);
                    if (medicine)
                    {
                        pharmacy.addMedicine(medicine);
                        cout << "Medicine added successfully." << endl;
                    }
                    else
                    {
                        cout << "Medicine not found." << endl;
                    }
                    break;
                }
                case 4:
                {
                    cout << "Returning to the main menu." << endl;
                    backToMainMenu = true; // Set the flag to true to exit the pharmacist menu
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
            break;
        }
        case 3:
        {
            // pharmacy menu
            int pharmacyChoice;
            bool backToMainMenu = false; // Flag to indicate if user wants to go back to the main menu
            // get input from user to display pharmacy name if input = 1
            while (!backToMainMenu)
            {
                cout << "--------- PHARMACY MENU ---------" << endl;
                cout << "--------- Choose your option below ---------" << endl;
                cout << "1. Display Pharmacy Name" << endl;
                cout << "2. Display Pharmacy Location" << endl;
                cout << "3. Add Medicine" << endl;
                cout << "4. Treat Patient" << endl;
                cout << "5. Add Pharmacist" << endl;
                cout << "6. Display Pharmacist Name" << endl;
                cout << "7. Back to main menu" << endl;
                cout << "---------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> pharmacyChoice;

                switch (pharmacyChoice)
                {
                case 1:
                {
                    cout << "Pharmacy Name: " << pharmacy.getPharmName() << endl;
                    break;
                }
                case 2:
                {
                    cout << "Pharmacy Location: " << pharmacy.getPharmLoc() << endl;
                    break;
                }
                case 3:
                {
                    int medicineID;
                    cout << "Enter medicine ID: ";
                    cin >> medicineID;
                    Medicine *medicine = supplier.getMedicine(medicineID);
                    if (medicine)
                    {
                        pharmacy.addMedicine(medicine);
                        cout << "Medicine added successfully." << endl;
                    }
                    else
                    {
                        cout << "Medicine not found." << endl;
                    }
                    break;
                }
                case 4:
                {
                     // Existing code for adding a medicine
                    int patientID;
                    cout << "Enter patient ID: ";
                    cin >> patientID;
                    Patient *patient = hospital.getPatientByCNIC(patientID);
                    if (patient)
                    {		
                        	Medicine *med = pharmacy.getMedicine(patient->getMedicine()->getID());
                        	//cout<<"Patient found"<<endl;
                        	if (med){
							cout<<"Medicine Found"<<endl;
                            pharmacist.treatPatient(patient);
                           
                            
                        }
                        else{
                        	cout<<"Medicine not found!"<<endl;
                        	
						}
                        break;
                    }
                    else
                    {
                        cout << "Patient not found." << endl;
                    }
                }
                // case 6 to add pharmacist
                case 5:
                {
                    // pharmiscist object from user input to the pharmacy
                    int Pharmacist_ID;
                    string name;
                    int cnic;
                    int age;
                    char gender;
                    cout << "Enter Pharmacist ID: ";
                    cin >> Pharmacist_ID;
                    cout << "Enter Pharmacist Name: ";
                    cin >> name;
                    cout << "Enter Pharmacist CNIC: ";
                    cin >> cnic;
                    cout << "Enter Pharmacist Age: ";
                    cin >> age;
                    cout << "Enter Pharmicist Gender: ";
                    cin >> gender;
                    Pharmacist *pharmacist = new Pharmacist(&pharmacy, Pharmacist_ID, name, cnic, age, gender); // Allocate pharmacist dynamically
                    pharmacy.addPharmacist(pharmacist);                                                         // Store the pharmacist pointer in the pharmacy
                    cout << "Pharmacist added successfully." << endl;
                    break;
                }
                case 6:
                {
                    // get input from user to display pharmacist name if input = 1
                    int Pharmacist_ID;
                    cout << "Enter Pharmacist ID: ";
                    cin >> Pharmacist_ID;
                    Pharmacist *pharmacist = pharmacy.getPharmacist(Pharmacist_ID);
                    if (pharmacist)
                    {
                        cout << "Pharmacist found. Pharmacist ID: " << pharmacist->getID() << endl;
                        cout << "Pharmacist Name: " << pharmacist->getName() << endl;
                    }
                    else
                    {
                        cout << "Pharmacist not found." << endl;
                    }
                    break;
                }
                case 7:
                {
                    cout << "Returning to the main menu." << endl;
                    backToMainMenu = true; // Set the flag to true to exit the pharmacist menu
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
            break;
        }
        case 4:
        {
            // Hospital Menu
            int hospitalChoice;
            bool backToMainMenu = false; // Flag to indicate if user wants to go back to the main menu
            // get input from user to display hospital name if input = 1
            while (!backToMainMenu)
            {
                cout << "--------- HOSPITAL MENU  ---------" << endl;
                cout << "--------- Choose your option below ---------" << endl;
                cout << "1. Display Hospital Name" << endl;
                cout << "2. Display Hospital Location" << endl;
                cout << "3. Add Patient" << endl;
                cout << "4. Display Patient Name" << endl;
                cout << "5. Add Doctor" << endl;
                cout << "6. Display Doctor Name" << endl;
                cout << "7. Back to main menu" << endl;
                cout << "---------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> hospitalChoice;
                switch (hospitalChoice)
                {
                case 1:
                {
                    cout << "Hospital Name: " << hospital.getHospName() << endl;
                    break;
                }
                case 2:
                {
                    cout << "Hospital Location: " << hospital.getHospLoc() << endl;
                    break;
                }
                case 3:
                {
                    // Patient object from user input to the hospital
                   int medID;
                    cout << "Enter medID: ";
                    cin >> medID;
                    int patientID;
                    string name, disease;
                    int cnic;
                    int age;
                    char gender;
                    cout << "Enter Patient ID: ";
                    cin >> patientID;
                    cout << "Enter Patient Name: ";
                    cin >> name;
                    cout << "Enter Patient CNIC: ";
                    cin >> cnic;
                    cout << "Enter Patient Age: ";
                    cin >> age;
                    cout << "Enter Patient Gender: ";
                    cin >> gender;
                    cout << "Enter Patient Disease: ";
                    cin.ignore();
                    getline(cin, disease);
                    Patient *patient = new Patient(patientID, disease, name, cnic, age, gender);
                    Medicine *medicine = supplier.getMedicine(medID);
                    if (medicine)
                    {
                        patient->setMedicine(medicine);
                        hospital.addPatient(patient); // Store the patient pointer in the hospital
                        cout << "Patient added successfully." << endl;
                    }
                    else
                    {
                        cout << "Medicine not found for the patient." << endl;
                        delete patient; // Cleanup memory in case medicine is not found
                    }
                    break;
                }
                case 4:
                {
                    // get input from user to display patient name if input = 1
                    int patientID;
                    cout << "Enter Patient ID: ";
                    cin >> patientID;
                    Patient *patient = hospital.getPatientByCNIC(patientID);
                    if (patient)
                    {
                        cout << "Patient found. Patient ID: " << patient->getID() << endl;
                        cout << "Patient Name: " << patient->getName() << endl;
                    }
                    else
                    {
                        cout << "Patient not found." << endl;
                    }
                    break;
                }
                case 5:
                {
                    // Doctor object from user input to the hospital
                    int Doctor_ID;
                    string name, specialization;
                    int cnic;
                    int age;
                    char gender;
                    cout << "Enter Doctor ID: ";
                    cin >> Doctor_ID;
                    cout << "Enter Doctor Name: ";
                    cin >> name;
                    cout << "Enter Doctor CNIC: ";
                    cin >> cnic;
                    cout << "Enter Doctor Age: ";
                    cin >> age;
                    cout << "Enter Doctor Gender: ";
                    cin >> gender;
                    cout << "Enter Doctor Specialization: ";
                    cin >> specialization;
                    Doctor *doctor = new Doctor(&hospital, Doctor_ID, specialization, name, cnic, age, gender); // Allocate doctor dynamically
                    hospital.addDoctor(doctor);                                                                 // Store the doctor pointer in the hospital
                    cout << "Doctor added successfully." << endl;
                    break;
                }
                case 6:
                {
                    // get input from user to display doctor name if input = 1
                    int Doctor_ID;
                    cout << "Enter Doctor ID: ";
                    cin >> Doctor_ID;
                    Doctor *doctor = hospital.getDoctor(Doctor_ID);
                    if (doctor)
                    {
                        cout << "Doctor found. Doctor ID: " << doctor->getID() << endl;
                        cout << "Doctor Name: " << doctor->getName() << endl;
                    }
                    else
                    {
                        cout << "Doctor not found." << endl;
                    }
                    break;
                }
                case 7:
                {
                    cout << "Returning to the main menu." << endl;
                    backToMainMenu = true; // Set the flag to true to exit the hospital menu
                    break;
                }
                }
            }
            break;
        }
        case 5:
        {
            cout << "Exiting program..." << endl;
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}
