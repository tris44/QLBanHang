#include "../include/customer.hpp"
#include "../include/validator.hpp"
#include <iostream>
using namespace std;

// ==========================================
// Constructor
// ==========================================

Customer::Customer() {
    customerID = "";
    fullName   = "";
    phone      = "";
    address    = "";
}

Customer::Customer(string id, string fullName, string phone, string address) {
    this->customerID = id;
    this->fullName   = fullName;
    this->phone      = phone;
    this->address    = address;
}

// ==========================================
// Getter
// ==========================================

string Customer::getCustomerID() const { return customerID; }
string Customer::getFullName()   const { return fullName; }
string Customer::getPhone()      const { return phone; }
string Customer::getAddress()    const { return address; }

// ==========================================
// Setter - dung ham validate tu validator.hpp
// ==========================================

void Customer::setCustomerID(string id) {
    if (isValidCustomerID(id))
        customerID = id;
    else
        cout << "[Loi] Ma khach hang khong hop le. Dinh dang: KH + 3 chu so (vi du: KH001)" << endl;
}

void Customer::setFullName(string name) {
    if (!name.empty())
        fullName = name;
    else
        cout << "[Loi] Ho ten khach hang khong duoc de trong." << endl;
}

void Customer::setPhone(string phone) {
    if (isValidPhoneNumber(phone))
        this->phone = phone;
    else
        cout << "[Loi] So dien thoai khong hop le. Yeu cau: dung 10 chu so." << endl;
}

void Customer::setAddress(string address) {
    if (!address.empty())
        this->address = address;
    else
        cout << "[Loi] Dia chi khong duoc de trong." << endl;
}

// ==========================================
// Nghiep vu
// ==========================================

bool Customer::validatePhone(const string& phone) const {
    return isValidPhoneNumber(phone);
}

void Customer::displayInfo() const {
    cout << "-------------------------------------" << endl;
    cout << "Ma KH      : " << customerID << endl;
    cout << "Ho ten     : " << fullName << endl;
    cout << "Dien thoai : " << phone << endl;
    cout << "Dia chi    : " << address << endl;
    cout << "-------------------------------------" << endl;
}