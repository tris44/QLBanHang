#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
using namespace std;

class Product {
private:
    string productID;   // Dinh dang: SP + 3 chu so, vi du SP001
    string name;
    double unitPrice;
    int stock;
    double vatRate;     // Ti le VAT rieng theo tung san pham (vi du: 0.08 = 8%)

public:
    // ========== Constructor ==========
    Product();
    Product(string id, string name, double price, int stock, double vatRate);

    // ========== Getter ==========
    string getProductID() const;
    string getName() const;
    double getUnitPrice() const;
    int getStock() const;
    double getVatRate() const;

    // ========== Setter ==========
    void setProductID(string id);
    void setName(string name);
    void setUnitPrice(double price);
    void setStock(int stock);
    void setVatRate(double rate);

    // ========== Nghiep vu ==========
    // Hien thi thong tin san pham ra man hinh
    void displayInfo() const;

    // Kiem tra ma san pham hop le:
    // - Dinh dang: SP + 3 chu so (vi du: SP001)
    // (Goi isValidProductID() tu validator.hpp)
    bool validateProductID(const string& id) const;
};

#endif // PRODUCT_HPP