#include <iostream>                                                         // Trương Nhật Hoàng
using namespace std;                                                        // 23KTMT1

enum loai {VIP, THANTHIET, VANGLAI};                                        // Định nghĩa kiểu dữ liệu liệt kê "loại" chứa các loại khách
struct hoadon {                                                             // Định nghĩa kiểu dữ liệu cấu trúc "Hoá đơn"
    char hoTen [50];                                                        //      gồm thành phần "họ tên" kiểu chuỗi
    float khuyenMai, thanhTien, thanhToan;                                  //      gồm thành phần "khuyến mại", "thành tiền", "thanh toán" kiểu số thực
    loai khach;                                                             //      gồm thành phần "khách" kiểu "loại"
};                                                                          // Kết thúc định nghĩa kiểu cấu "Hóa đơn"

void nhap (hoadon& hoaDon) {                                                // Định nghĩa hàm "nhập" truyền tham chiếu cho biến kiểu "Hóa đơn"
    cout << "Nhập tên: "; cin >> hoaDon.hoTen;                              //      Xuất ra màn hình yêu cầu nhập tên và gán vào thành phần "tên" của biến tham chiếu
    
    cout << "Nhập loại khách (0: VIP, 1: Thân thiết, 2: Vãng lai): ";       //      Xuất ra màn hình yêu cầu nhập loại khách hành bằng số
    int x; cin >> x; hoaDon.khach = (loai) x;                               //      Nhập vào số nguyên x và ép kiểu để gán vào thành phần "khách" của biến tham chiếu
    
    cout << "Nhập thành tiền: "; cin >> hoaDon.thanhTien;                   //      Xuất ra màn hình yêu cầu nhập "thành tiền" và gán vào thành phần "thành tiền" của biến tham chiếu

    if (hoaDon.khach == 0) hoaDon.khuyenMai = 0.5;                          //      Gán giá trị thành phần "khuyến mại" dựa theo giá trị thành phần "khách" của biến tham chiếu
    else if (hoaDon.khach == 1) hoaDon.khuyenMai = 0.25;                     
    else hoaDon.khuyenMai = 0.1;
    
    hoaDon.thanhToan = hoaDon.thanhTien * (1 - hoaDon.khuyenMai);           //      Gán giá trị thành phần "thanh toán" của biến tham chiếu
}                                                                           // Kết thúc định nghĩa hàm "nhập"

void xuat (hoadon hoaDon) {                                                 // Định nghĩa hàm "xuất" truyền tham số cho biến kiểu "Hóa đơn"
    cout << "Tên khách hàng: "; cout << hoaDon.hoTen << endl;               //      Xuất ra màn hình tên khách hàng là giá trị thành phần "họ tên" của biến tham số
    
    if (hoaDon.khach == 0) cout << "Khách VIP" << endl;                     //      Xuất ra màn hình loại khách hàng dựa theo giá trị thành phần "khách" của biến tham số
    else if (hoaDon.khach == 1) cout << "Khách thân thiết" << endl;
    else cout << "Khách vãng lai" << endl;
    
    cout << "Thanh toán: " << hoaDon.thanhToan << endl;                     //      Xuất ra màn hình tiền thanh toán là giá trị thành phần "thanh toán" của biến tham số   
}                                                                           // Kết thúc định nghĩa hàm "xuất"

int main () {                                                               // Bắt đầu hàm chính
    hoadon hoaDon;                                                          //      Khởi tạo biến "hóa đơn" có kiểu dữ liệu "Hóa đơn"
    nhap(hoaDon);                                                           //      Gọi hàm "nhập" và truyền vào hàm biến "hóa đơn"
    cout << endl;                                                           //      Xuống dòng 
    xuat(hoaDon);                                                           //      Gọi hàm "xuất" và truyền vào hàm biến "hóa đơn"
    return 0;                                                               //      Trả về giá trị 0 cho hàm chính
}                                                                           // Kết thúc hàm chính. Kết thúc chương trình
