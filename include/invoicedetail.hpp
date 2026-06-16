#ifndef INVOICEDETAIL_HPP
#define INVOICEDETAIL_HPP

#include <string>

struct InvoiceDetail {
    std::string productID;
    std::string productName;
    double unitPrice;
    int quantity;
    double discountRate; // Tỷ lệ chiết khấu riêng của dòng (nếu có), mặc định 0
    double vatRate;     
    double lineTotal;    // = quantity * unitPrice
    double lineVAT;      // = lineTotal * (1 - discountRate) * vatRate

    // Constructor
    InvoiceDetail();
    InvoiceDetail(const std::string& productID, const std::string& productName,
                   double unitPrice, int quantity,
                   double discountRate = 0.0, double vatRate = 0.0);

    void calculateLineTotal();

    // Hiển thị thông tin dòng hóa đơn
    void displayInfo() const;
};

#endif