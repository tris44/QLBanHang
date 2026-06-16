#include "../include/product.hpp"
#include "../include/validator.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// ==========================================
// Constructor
// ==========================================

Product::Product() {
    productID = "";
    name      = "";
    unitPrice = 0.0;
    stock     = 0;
    vatRate   = 0.0;
}

Product::Product(string id, string name, double price, int stock, double vatRate) {
    this->productID  = id;
    this->name       = name;
    this->unitPrice  = price;
    this->stock      = stock;
    this->vatRate    = vatRate;
}

// ==========================================
// Getter
// ==========================================

string Product::getProductID() const { return productID; }
string Product::getName()      const { return name; }
double Product::getUnitPrice() const { return unitPrice; }
int    Product::getStock()     const { return stock; }
double Product::getVatRate()   const { return vatRate; }

// ==========================================
// Setter - dung ham validate tu validator.hpp
// ==========================================

void Product::setProductID(string id) {
    if (isValidProductID(id))
        productID = id;
    else
        cout << "[Loi] Ma san pham khong hop le. Dinh dang: SP + 3 chu so (vi du: SP001)" << endl;
}

void Product::setName(string name) {
    if (!name.empty())
        this->name = name;
    else
        cout << "[Loi] Ten san pham khong duoc de trong." << endl;
}

void Product::setUnitPrice(double price) {
    if (isValidPrice(price))
        unitPrice = price;
    else
        cout << "[Loi] Don gia phai la so thuc duong." << endl;
}

void Product::setStock(int stock) {
    if (stock >= 0)
        this->stock = stock;
    else
        cout << "[Loi] So luong ton kho khong duoc am." << endl;
}

void Product::setVatRate(double rate) {
    if (isValidVATRate(rate))
        vatRate = rate;
    else
        cout << "[Loi] Ti le VAT phai nam trong khoang [0.0, 1.0]." << endl;
}

// ==========================================
// Nghiep vu
// ==========================================

void Product::displayInfo() const {
    cout << "-------------------------------------" << endl;
    cout << "Ma SP      : " << productID << endl;
    cout << "Ten SP     : " << name << endl;
    cout << fixed << setprecision(0);
    cout << "Don gia    : " << unitPrice << " VND" << endl;
    cout << "Ton kho    : " << stock << endl;
    cout << fixed << setprecision(1);
    cout << "VAT Rate   : " << vatRate * 100 << "%" << endl;
    cout << "-------------------------------------" << endl;
}