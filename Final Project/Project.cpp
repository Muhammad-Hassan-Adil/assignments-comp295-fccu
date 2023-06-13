#include "Project.hpp"
#include <iostream>
#include <fstream>
#include <string>

class PPC {
protected:
    int PPC_HQ_ID;
    string HQ;
public:
    int getID(){
        return PPC_HQ_ID;
    }
    string getHQ(){
        return HQ;
    }
    void setPPC_ID_HQ(int id){
        PPC_HQ_ID = id;
    }
    void setHQ(string hqq){
        HQ = hqq;
    }
};

class Hospital : public PPC {
protected:
    int Hosp_ID;
    string Hosp_Loc, Hosp_Name;
    Doctor** doctors;
    int Doc_Count;
public:
    Hospital (string HospLoc, string HospName, int hospID, int ppcID) : PPC (int ppcID), Hosp_ID(HospLoc), Hosp_Loc(HospLoc), Hosp_Name(HospName), Hosp_ID(hospID), doctors(NULL), Doc_Count(0) {}
    int getID(){
        return Hosp_ID;
    }
    string getHospLoc(){
        return Hosp_Loc;
    }
    string getHospName(){
        return Hosp_Name;
    }
    Doctors* getDoctors(){
        return doctors;
    }
    void setID(int hospid){
        ID = hospid;
    }
    void setHospLoc(string loc){
        Hosp_Loc = loc;
    }
    void setHospName(string name){
        Hosp_Name = name;
    }
    void setDoctors(Doctor& doc){
        doctors[Doc_Count] = doc;
        Doc_Count++;
    }
};

class Pharmacy : public PPC {
protected:
    int Pharm_ID;
    string Pharm_Name, Pharm_Loc;
    Pharmacist** pharmacists;
    int Pharmacist_Count;
public:
    Pharmacy (int ppc, int ID,string name, string loc) : PPC (int ppc), Pharm_ID(pharm), Pharm_ID(ID), Pharm_Name(name), Pharm_Loc(loc), pharmacists(NULL), Pharmacist_Count(0) {}
    int getID(){
        return Pharm_ID;
    }
    string getPharmName(){
        return Pharm_Name;
    }
    string getPharmLoc(){
        return Pharm_Loc;
    }
    Pharmacist* getPharmacists(){
        return pharmacists;
    }
    void setID(int idd){
        ID = idd;
    }
    void setPharmName(string name){
        Pharm_Name = name;
    }
    void setPharmLoc(string loc){
        Pharm_Loc = loc;
    }
    void setPharamacists(Pharmacist pharm){
        pharmacists[Pharmacist_Count] = pharm;
        Pharmacist_Count++;
    }
};

class Person {
protected:
    string name;
    int cnic, age;
    char gender;
public:
    Person (string nam, int cni, int ag, char gen) : name(nam), cnic(cni), age(ag), gender(gen){}
    string getName(){
        return name;
    }
    int getCNIC(){
        return cnic;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void setName(string N){
        name = N;
    }
    void setCNIC(int C){
        cnic = C;
    }
    void setAge(int A){
        age = A;
    }
    void setGender(char G){
        gender = G;
    }
};

class Doctor : public Person, public Hospital {
private:
    int Doc_ID;
    string Specialization;
public:
    Doctor (int hosp,string nam, int cni, int ag, char gen,int doc, string spec) : Hospital(int hosp), Person(string nam, int cni, int ag, char gen), doc_id(doc), Specialization(spec) {}
    int getID(){
        return Doc_ID;
    }
    int getHospID(){
        return Hosp_ID;
    }
    string getName(){
        return name;
    }
    int getCNIC(){
        return cnic;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void setID(int idd){
        Doc_ID = idd;
    }
    void setSpecialization(string spec){
        Specialization = spec;
    }
    void setName(string N){
        name = N;
    }
    void setCNIC(int C){
        cnic = C;
    }
    void setAge(int A){
        age = A;
    }
    void setGender(char G){
        gender = G;
    }
};

class Patient : public Person {
private:
    int Pat_ID;
    string Disease, Treatment;
public:
    Patient (string nam, int cni, int ag, char gen,int pat, string dis, string treat) : Person(string nam, int cni, int ag, char gen), pat_id(pat), Disease(dis), Treatment(treat) {}
    int getID(){
        return Pat_ID;
    }
    string getDisease(){
        return Disease;
    }
    string getTreatment(){
        return Treatment;
    }
    string getName(){
        return name;
    }
    int getCNIC(){
        return cnic;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void setID(int idd){
        Pat_ID = idd;
    }
    void setDisease(string dis){
        Disease = dis;
    }
    void setTreatment(string treat){
        Treatment = treat;
    }
    void setName(string N){
        name = N;
    }
    void setCNIC(int C){
        cnic = C;
    }
    void setAge(int A){
        age = A;
    }
    void setGender(char G){
        gender = G;
    }
};

class Pharmacist : public Person, public Pharmacy {
private:
    int Pharmacist_ID;
public:
    Pharmacist (int pharm_ID,string nam, int cni, int ag, char gen,int pharmacist) : Pharmacy(int pharm_ID),Person(string nam, int cni, int ag, char gen), pharmacist_id(pharmacist) {}
    int getID(){
        return Pharmacist_ID;
    }
    string getName(){
        return name;
    }
    int getCNIC(){
        return cnic;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void setID(int idd){
        Pharmacist_ID = idd;
    }
    void setName(string N){
        name = N;
    }
    void setCNIC(int C){
        cnic = C;
    }
    void setAge(int A){
        age = A;
    }
    void setGender(char G){
        gender = G;
    }
};

class Supplier : public Person, public PPC {
private:
    int Supplier_ID;
public:
    Supplier (string nam, int cni, int ag, char gen, int ppc,int supplier) : Person(string nam, int cni, int ag, char gen), PPC(int ppc), supplier_id(supplier) {}
    int getID(){
        return Supplier_ID;
    }
    string getName(){
        return name;
    }
    int getCNIC(){
        return cnic;
    }
    int getAge(){
        return age;
    }
    char getGender(){
        return gender;
    }
    void setID(int idd){
        Supplier_ID = idd;
    }
    void setName(string N){
        name = N;
    }
    void setCNIC(int C){
        cnic = C;
    }
    void setAge(int A){
        age = A;
    }
    void setGender(char G){
        gender = G;
    }
};

