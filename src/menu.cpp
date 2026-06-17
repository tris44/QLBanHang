#include "../include/menu.hpp"
#include "../include/datamanager.hpp"
#include "../include/validator.hpp"
#include "../include/utilities.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

// Menu quản lý sản phẩm
void productMenu() {
    int choice;
    do {
        cout << "\n--- QUAN LY SAN PHAM ---\n";
        cout << "1. Them san pham moi\n";
        cout << "2. Cap nhat thong tin san pham\n";
        cout << "3. Xoa san pham\n";
        cout << "4. Tim kiem san pham\n";
        cout << "5. Hien thi danh sach san pham\n";
        cout << "6. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, name;
                double price, vatRate;
                int stock;

                cout << "Nhap ma SP (VD: SP001): "; cin >> id;
                if (!isValidProductID(id)) {
                    cout << "[Loi] Ma san pham khong hop le.\n";
                    break;
                }
                cout << "Nhap ten SP: "; cin.ignore(); getline(cin, name);
                cout << "Nhap don gia: "; cin >> price;
                cout << "Nhap so luong ton: "; cin >> stock;
                cout << "Nhap ti le VAT (vd 0.1): "; cin >> vatRate;

                productList.push_back(Product(id, name, price, stock, vatRate));
                cout << "Them san pham thanh cong!\n";
                break;
            }
            case 2: {
                string id;
                cout << "Nhap ma SP can cap nhat: "; cin >> id;
                bool found = false;
                for (auto& p : productList) {
                    if (p.getProductID() == id) {
                        found = true;
                        string name;
                        double price, vatRate;
                        int stock;
                        cout << "Nhap ten SP moi: "; cin.ignore(); getline(cin, name);
                        cout << "Nhap don gia moi: "; cin >> price;
                        cout << "Nhap so luong ton moi: "; cin >> stock;
                        cout << "Nhap ti le VAT moi: "; cin >> vatRate;
                        p.setName(name);
                        p.setUnitPrice(price);
                        p.setStock(stock);
                        p.setVatRate(vatRate);
                        cout << "Cap nhat thanh cong!\n";
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay san pham!\n";
                break;
            }
            case 3: {
                string id;
                cout << "Nhap ma SP can xoa: "; cin >> id;
                bool found = false;
                for (size_t i = 0; i < productList.size(); i++) {
                    if (productList[i].getProductID() == id) {
                        productList.erase(productList.begin() + i);
                        found = true;
                        cout << "Xoa thanh cong!\n";
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay san pham!\n";
                break;
            }
            case 4: {
                string keyword;
                cout << "Nhap ma hoac ten SP can tim: "; cin.ignore(); getline(cin, keyword);
                bool found = false;
                for (const auto& p : productList) {
                    if (p.getProductID() == keyword || p.getName().find(keyword) != string::npos) {
                        p.displayInfo();
                        found = true;
                    }
                }
                if (!found) cout << "Khong tim thay san pham phu hop!\n";
                break;
            }
            case 5: {
                cout << "\n=== DANH SACH SAN PHAM (" << productList.size() << ") ===\n";
                for (const auto& p : productList) {
                    p.displayInfo();
                }
                break;
            }
            case 6:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 6);
}

// Menu quản lý khách hàng
void customerMenu() {
    int choice;
    do {
        cout << "\n--- QUAN LY KHACH HANG ---\n";
        cout << "1. Them khach hang moi\n";
        cout << "2. Cap nhat thong tin khach hang\n";
        cout << "3. Xoa khach hang\n";
        cout << "4. Tim kiem khach hang\n";
        cout << "5. Hien thi danh sach khach hang\n";
        cout << "6. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, name, phone, address;
                cout << "Nhap ma KH (VD: KH001): "; cin >> id;
                if (!isValidCustomerID(id)) {
                    cout << "[Loi] Ma khach hang khong hop le.\n";
                    break;
                }
                cout << "Nhap ho ten: "; cin.ignore(); getline(cin, name);
                cout << "Nhap so dien thoai: "; cin >> phone;
                cout << "Nhap dia chi: "; cin.ignore(); getline(cin, address);

                customerList.push_back(Customer(id, name, phone, address));
                cout << "Them khach hang thanh cong!\n";
                break;
            }
            case 2: {
                string id;
                cout << "Nhap ma KH can cap nhat: "; cin >> id;
                bool found = false;
                for (auto& c : customerList) {
                    if (c.getCustomerID() == id) {
                        found = true;
                        string name, phone, address;
                        cout << "Nhap ho ten moi: "; cin.ignore(); getline(cin, name);
                        cout << "Nhap SDT moi: "; cin >> phone;
                        cout << "Nhap dia chi moi: "; cin.ignore(); getline(cin, address);
                        c.setFullName(name);
                        c.setPhone(phone);
                        c.setAddress(address);
                        cout << "Cap nhat thanh cong!\n";
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay khach hang!\n";
                break;
            }
            case 3: {
                string id;
                cout << "Nhap ma KH can xoa: "; cin >> id;
                bool found = false;
                for (size_t i = 0; i < customerList.size(); i++) {
                    if (customerList[i].getCustomerID() == id) {
                        customerList.erase(customerList.begin() + i);
                        found = true;
                        cout << "Xoa thanh cong!\n";
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay khach hang!\n";
                break;
            }
            case 4: {
                string keyword;
                cout << "Nhap ma hoac ten KH can tim: "; cin.ignore(); getline(cin, keyword);
                bool found = false;
                for (const auto& c : customerList) {
                    if (c.getCustomerID() == keyword || c.getFullName().find(keyword) != string::npos) {
                        c.displayInfo();
                        found = true;
                    }
                }
                if (!found) cout << "Khong tim thay khach hang phu hop!\n";
                break;
            }
            case 5: {
                cout << "\n=== DANH SACH KHACH HANG (" << customerList.size() << ") ===\n";
                for (const auto& c : customerList) {
                    c.displayInfo();
                }
                break;
            }
            case 6:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 6);
}

// Menu quản lý hóa đơn
void invoiceMenu() {
    int choice;
    do {
        cout << "\n--- QUAN LY HOA DON ---\n";
        cout << "1. Lap hoa don moi\n";
        cout << "2. Hien thi danh sach hoa don\n";
        cout << "3. Xem chi tiet hoa don\n";
        cout << "4. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (invoiceCount >= MAX_INVOICES) {
                    cout << "[Loi] Da dat so luong hoa don toi da!\n";
                    break;
                }

                string invID, custID, date;
                cout << "Nhap ma hoa don (VD: HD001): "; cin >> invID;
                if (!isValidInvoiceID(invID)) {
                    cout << "[Loi] Ma hoa don khong hop le.\n";
                    break;
                }
                cout << "Nhap ma khach hang: "; cin >> custID;
                cout << "Nhap ngay mua (YYYY-MM-DD): "; cin >> date;

                Invoice inv(invID, custID, date);

                double discountRate;
                cout << "Nhap ti le chiet khau hoa don (vd 0.05): "; cin >> discountRate;
                if (!isValidDiscountRate(discountRate)) {
                    cout << "[Loi] Ti le chiet khau khong hop le, dat ve 0.\n";
                    discountRate = 0.0;
                }
                inv.setDiscountRate(discountRate);

                char more = 'y';
                while (more == 'y' || more == 'Y') {
                    string prodID;
                    int qty;
                    cout << "Nhap ma san pham: "; cin >> prodID;

                    // Tìm sản phẩm trong productList để lấy giá và VAT
                    bool foundProd = false;
                    for (const auto& p : productList) {
                        if (p.getProductID() == prodID) {
                            foundProd = true;
                            cout << "Nhap so luong: "; cin >> qty;
                            if (!isValidQuantity(qty)) {
                                cout << "[Loi] So luong khong hop le.\n";
                                break;
                            }
                            InvoiceDetail detail(prodID, p.getName(), p.getUnitPrice(),
                                                  qty, 0.0, p.getVatRate());
                            inv.addProductDetail(detail);
                            cout << "Da them san pham vao hoa don.\n";
                            break;
                        }
                    }
                    if (!foundProd) cout << "[Loi] Khong tim thay san pham!\n";

                    cout << "Them san pham khac? (y/n): "; cin >> more;
                }

                inv.calculateTotal();
                invoiceList[invoiceCount++] = inv;
                cout << "Lap hoa don thanh cong!\n";
                inv.displayInfo();
                break;
            }
            case 2: {
                cout << "\n=== DANH SACH HOA DON (" << invoiceCount << ") ===\n";
                for (int i = 0; i < invoiceCount; i++) {
                    cout << invoiceList[i].getInvoiceID() << " | "
                         << invoiceList[i].getCustomerID() << " | "
                         << invoiceList[i].getPurchaseDate() << " | Tong: "
                         << invoiceList[i].getFinalTotal() << "\n";
                }
                break;
            }
            case 3: {
                string id;
                cout << "Nhap ma hoa don can xem: "; cin >> id;
                bool found = false;
                for (int i = 0; i < invoiceCount; i++) {
                    if (invoiceList[i].getInvoiceID() == id) {
                        invoiceList[i].displayInfo();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Khong tim thay hoa don!\n";
                break;
            }
            case 4:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 4);
}

// Menu thống kê
void statisticsMenu() {
    int choice;
    do {
        cout << "\n--- THONG KE ---\n";
        cout << "1. Doanh thu theo ngay\n";
        cout << "2. Doanh thu theo thang\n";
        cout << "3. Top 10 san pham ban chay\n";
        cout << "4. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string dates[MAX_INVOICES];
                double revenues[MAX_INVOICES];
                int count = revenueByDay(invoiceList, invoiceCount, dates, revenues, MAX_INVOICES);
                displayRevenueReport(dates, revenues, count, "DOANH THU THEO NGAY");
                break;
            }
            case 2: {
                string months[MAX_INVOICES];
                double revenues[MAX_INVOICES];
                int count = revenueByMonth(invoiceList, invoiceCount, months, revenues, MAX_INVOICES);
                displayRevenueReport(months, revenues, count, "DOANH THU THEO THANG");
                break;
            }
            case 3: {
                ProductSales topProducts[MAX_TOP];
                int count = top10BestSellingProducts(invoiceList, invoiceCount, topProducts, MAX_TOP);
                displayTopProducts(topProducts, count);
                break;
            }
            case 4:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 4);
}

// Menu chính
void mainMenu() {
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "       HE THONG QUAN LY BAN HANG\n";
        cout << "========================================\n";
        cout << "1. Quan ly san pham\n";
        cout << "2. Quan ly khach hang\n";
        cout << "3. Quan ly hoa don\n";
        cout << "4. Thong ke\n";
        cout << "5. Luu du lieu\n";
        cout << "6. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: productMenu();    break;
            case 2: customerMenu();   break;
            case 3: invoiceMenu();    break;
            case 4: statisticsMenu(); break;
            case 5:
                saveData();
                cout << "Da luu du lieu!\n";
                break;
            case 6:
                saveData();
                cout << "Da thoat chuong trinh!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 6);
}