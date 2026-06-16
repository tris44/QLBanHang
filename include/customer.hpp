#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
using namespace std;

class Customer {
private:
    string customerID;  // Dinh dang: KH + 3 chu so, vi du KH001
    string fullName;
    string phone;       // 10 chu so, bat dau bang 0
    string address;

public:
    // ========== Constructor ==========
    Customer();
    Customer(string id, string fullName, string phone, string address);

    // ========== Getter ==========
    string getCustomerID() const;
    string getFullName()   const;
    string getPhone()      const;
    string getAddress()    const;

    // ========== Setter ==========
    void setCustomerID(string id);
    void setFullName(string name);
    void setPhone(string phone);
    void setAddress(string address);

    // ========== Nghiep vu ==========
    // Hien thi thong tin khach hang ra man hinh
    void displayInfo() const;

    // Kiem tra so dien thoai hop le:
    // - Dung 10 chu so
    // - Khong chua ky tu khac
    // (Goi isValidPhoneNumber() tu validator.hpp)
    bool validatePhone(const string& phone) const;
};

#endif // CUSTOMER_HPP