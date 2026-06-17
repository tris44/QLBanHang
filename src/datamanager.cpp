#include "../include/datamanager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

/*
 * Định nghĩa các danh sách dữ liệu dùng chung
 */
std::vector<Product>  productList;
std::vector<Customer> customerList;
Invoice invoiceList[MAX_INVOICES];
int     invoiceCount = 0;

// Hàm phụ: tách chuỗi theo dấu '|' 
static int splitLine(const std::string& line, std::string tokens[], int maxTokens, char delim = '|') {
    int count = 0;
    std::string token;
    std::stringstream ss(line);
    while (std::getline(ss, token, delim) && count < maxTokens) {
        tokens[count++] = token;
    }
    return count;
}

// Đọc dữ liệu
void loadProducts() {
    productList.clear();
    std::ifstream fin("data/products.txt");
    if (!fin.is_open()) {
        std::cout << "[Loi] Khong mo duoc file data/products.txt" << std::endl;
        return;
    }

    std::string line;
    std::string tokens[10];
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        int n = splitLine(line, tokens, 10);
        if (n < 5) continue;

        try {
            std::string id    = tokens[0];
            std::string name  = tokens[1];
            double price      = std::stod(tokens[2]);
            int stock         = std::stoi(tokens[3]);
            double vatRate    = std::stod(tokens[4]);

            productList.push_back(Product(id, name, price, stock, vatRate));
        } catch (...) {
            continue; 
        }
    }
    fin.close();
}

void loadCustomers() {
    customerList.clear();
    std::ifstream fin("data/customers.txt");
    if (!fin.is_open()) {
        std::cout << "[Loi] Khong mo duoc file data/customers.txt" << std::endl;
        return;
    }

    std::string line;
    std::string tokens[10];
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        int n = splitLine(line, tokens, 10);
        if (n < 4) continue;

        customerList.push_back(Customer(tokens[0], tokens[1], tokens[2], tokens[3]));
    }
    fin.close();
}

// Ghi dữ liệu
void saveProducts() {
    std::ofstream fout("data/products.txt");
    if (!fout.is_open()) {
        std::cout << "[Loi] Khong the ghi vao data/products.txt" << std::endl;
        return;
    }
    for (const auto& p : productList) {
        fout << p.getProductID() << "|" << p.getName() << "|"
             << p.getUnitPrice() << "|" << p.getStock() << "|"
             << p.getVatRate() << "\n";
    }
    fout.close();
}

void saveCustomers() {
    std::ofstream fout("data/customers.txt");
    if (!fout.is_open()) {
        std::cout << "[Loi] Khong the ghi vao data/customers.txt" << std::endl;
        return;
    }
    for (const auto& c : customerList) {
        fout << c.getCustomerID() << "|" << c.getFullName() << "|"
             << c.getPhone() << "|" << c.getAddress() << "\n";
    }
    fout.close();
}

void saveInvoices() {
    std::ofstream foutInv("data/invoices.txt");
    std::ofstream foutDet("data/invoicedetails.txt");
    if (!foutInv.is_open() || !foutDet.is_open()) {
        std::cout << "[Loi] Khong the ghi du lieu hoa don" << std::endl;
        return;
    }

    for (int i = 0; i < invoiceCount; i++) {
        const Invoice& inv = invoiceList[i];
        foutInv << inv.getInvoiceID() << "|" << inv.getCustomerID() << "|"
                << inv.getPurchaseDate() << "|" << inv.getDiscountRate() << "\n";

        for (int j = 0; j < inv.getDetailCount(); j++) {
            const InvoiceDetail& d = inv.getDetail(j);
            foutDet << inv.getInvoiceID() << "|" << d.productID << "|"
                    << d.productName << "|" << d.unitPrice << "|"
                    << d.quantity << "|" << d.discountRate << "|"
                    << d.vatRate << "\n";
        }
    }
    foutInv.close();
    foutDet.close();
}


// Hàm tổng
void loadData() {
    loadProducts();
    loadCustomers();
    invoiceCount = loadInvoicesFromFile("data/invoices.txt", "data/invoicedetails.txt",
                                          invoiceList, MAX_INVOICES);

    std::cout << "Da tai du lieu: " << productList.size() << " san pham, "
              << customerList.size() << " khach hang, "
              << invoiceCount << " hoa don." << std::endl;
}

void saveData() {
    saveProducts();
    saveCustomers();
    saveInvoices();
    std::cout << "Da luu du lieu thanh cong." << std::endl;
}