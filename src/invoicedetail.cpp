#include "../include/invoicedetail.hpp"
#include <iostream>
#include <iomanip>

InvoiceDetail::InvoiceDetail()
    : productID(""), productName(""), unitPrice(0.0), quantity(0),
      discountRate(0.0), vatRate(0.0), lineTotal(0.0), lineVAT(0.0) {}

InvoiceDetail::InvoiceDetail(const std::string& productID, const std::string& productName,
                              double unitPrice, int quantity,
                              double discountRate, double vatRate)
    : productID(productID), productName(productName),
      unitPrice(unitPrice), quantity(quantity),
      discountRate(discountRate), vatRate(vatRate),
      lineTotal(0.0), lineVAT(0.0) {
    calculateLineTotal();
}

void InvoiceDetail::calculateLineTotal() {
    lineTotal = quantity * unitPrice;
    lineVAT   = lineTotal * (1.0 - discountRate) * vatRate;
}

void InvoiceDetail::displayInfo() const {
    std::cout << std::left
              << std::setw(10) << productID
              << std::setw(20) << productName
              << "SL: "     << std::setw(5)  << quantity
              << "Don gia: " << std::setw(12) << std::fixed << std::setprecision(2) << unitPrice
              << "T.tien: "  << std::setw(12) << lineTotal
              << "VAT: "     << lineVAT
              << std::endl;
}