#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>

using namespace std;

template <typename KieuDuLieu>
class MangDong {
    private:
        KieuDuLieu *danhSach;
        int soLuong;

    public:
        MangDong () {
            soLuong = 0;
            danhSach = new KieuDuLieu [soLuong + 1];
        }

        ~MangDong () {
            delete [] danhSach;
        }

        KieuDuLieu &operator [] (int stt) {
            return danhSach[stt];
        }

        int getSoLuong () {
            return soLuong;
        }

        void themPhanTu (KieuDuLieu phanTuMoi) {
            soLuong ++;
            KieuDuLieu *danhSachMoi = new KieuDuLieu [soLuong + 1];
            
            for (int i = 0; i < soLuong; i++) danhSachMoi[i] = danhSach[i];
            danhSachMoi[soLuong] = phanTuMoi;
            
            delete [] danhSach;
            danhSach = danhSachMoi;
        }

        void xoaPhanTu (int stt) {
            --soLuong;
            KieuDuLieu *danhSachMoi = new KieuDuLieu [soLuong + 1];

            for (int i = 0; i <= soLuong; i++) {
                if (i < stt) danhSachMoi[i] = danhSach[i];
                else danhSachMoi[i] = danhSach[i+1];
            }

            delete [] danhSach;
            danhSach = danhSachMoi;
        }

};

void nhanEnterDeGiuNguyen (string &s) {
    string a;
    getline(cin, a);
    if (a != "") s = a;
}

void nhanEnterDeTiepTuc () {
    cout << "\nPress Enter to continue  . . .";
    string a; getline (cin, a);
}

class TaiKhoan {
private:
    string userName, passWord;
    int quyenTruyCap;
public:
    void setUserName (string UserName) {
        userName = UserName;
    }
    void setPassWord (string PassWord) {
        passWord = PassWord;
    }
    void setQuyenTruyCap (int QuyenTruyCap) {
        quyenTruyCap = QuyenTruyCap;
    }

    string getUserName () {
        return userName;
    }
    string getPassWord () {
        return passWord;
    }
    int getQuyenTruyCap () {
        return quyenTruyCap;
    }

    void nhapFile (ifstream &in) {
        getline (in, userName, ',');
        getline (in, passWord, ',');
        string QuyenTruyCap;
        getline (in, QuyenTruyCap);
        quyenTruyCap = stoi (QuyenTruyCap);
    }

    void  xuatFile (ofstream &out) {
        out << userName << ',' << passWord << ',' << quyenTruyCap;
    }

    void nhap () {
        cout << "Username: ";
        cin >> userName;
        cout << "Password: ";
        cin >> passWord;
    }

    bool operator == (TaiKhoan khac) {
        return (this->userName == khac.getUserName() && this->passWord == khac.getPassWord());
    }
};

class DanhSachTaiKhoan {
private:
    MangDong <TaiKhoan> danhSach;
    int soLuong;    
public:
    DanhSachTaiKhoan () {
        ifstream in ("acc.txt");
        in >> soLuong; in.ignore();
        for (int i= 1; i <= soLuong; i++) {
            TaiKhoan taiKhoanMoi;
            taiKhoanMoi.nhapFile(in);
            danhSach.themPhanTu(taiKhoanMoi);   
        }
        in.close ();
    }

    ~DanhSachTaiKhoan () {
        ofstream out ("acc.txt");
        out << soLuong;
        for (int i = 1; i <= soLuong; i++) {
            out << endl;
            danhSach[i].xuatFile(out);
        }
        out.close();
    }

    bool kiemTraTonTai (TaiKhoan &taiKhoanKhac) {
        for (int i = 1; i <= soLuong; i++)
            if (taiKhoanKhac.getUserName() == danhSach[i].getUserName()) return true;
        return false;
    }

    bool kiemTra (TaiKhoan &user) {  // kiểm tra có user trong danh sách không?
        for (int i = 1; i <= soLuong; i++)                                                      // nếu có thì trả về quyền truy cập
            if (user == danhSach[i]) {
                user = danhSach[i];
                return true;
            }
        return false;                                                                                              // không có thì trả về 0
    }

    void themTaiKhoan (TaiKhoan &taiKhoanMoi) {
        soLuong++;
        danhSach.themPhanTu(taiKhoanMoi);
    }

    void xoaTaiKhoan (string UserName) {
        int stt;
        for (int i = 1; i <= soLuong; i++)
            if (danhSach[i].getUserName() == UserName) {
                stt = i;
                break;
            }
        danhSach.xoaPhanTu(stt);
        soLuong --;

    }

};

class Sach {
private:
    string maSach, tenSach, tenTacGia, nhaXuatBan, namXuatBan, theLoai;
    int soLuong;
public:
    Sach () {
        soLuong = 0;
    }    

    void nhapThongTinTuFile (ifstream &in) {
        getline(in, maSach, ',');
        getline(in, tenSach, ',');
        getline(in, tenTacGia, ',');
        getline(in, nhaXuatBan, ',');
        getline(in, namXuatBan, ',');
        getline(in, theLoai, ',');
        string SoLuong;
        getline(in, SoLuong);
        soLuong = stoi(SoLuong);
    }

    void xuatThongTinRaFile (ofstream &out) {
        out << maSach << ',';
        out << tenSach << ',';
        out << tenTacGia << ',';
        out << nhaXuatBan << ',';
        out << namXuatBan << ',';
        out << theLoai << ','; 
        out << soLuong; 
    }

    void setTenSach (string TenSach) {
        tenSach = TenSach;
    }

    void  setMaSach(string MaSach) {
        maSach = MaSach;
    }

    void setTenTacGia (string TenTacGia) {
        tenTacGia = TenTacGia;
    }

    void setSoLuong (int SoLuong) {
        soLuong = SoLuong;
    }

    string getMaSach () {
        return maSach;
    }

    string getTenSach () {
        return tenSach;
    }

    int getSoLuong () {
        return soLuong;
    }


    void xemThongTinCoBan (){
        cout << left << setw (4) << soLuong;  
        cout <<  setw(20) << tenSach; 
        cout << setw(15) << tenTacGia; 
        cout << setw (10) << nhaXuatBan;
        cout << endl; 
    }

    void xemThongTinChiTiet () {
        cout << "Ma sach: " << maSach << endl;
        cout << "Ten sach: " << tenSach << endl;
        cout << "Ten tac gia: " << tenTacGia << endl;
        cout << "Nha xuat ban: " << nhaXuatBan << endl;
        cout << "Nam xuat ban: " << namXuatBan << endl;
        cout << "The loai: " << theLoai << endl; 
        cout << "So luong: " << soLuong << endl;
    }


    void capNhatThongTin () {
        cout << "Ma sach cu: " << maSach << endl;
        cout << "Ma sach moi: "; nhanEnterDeGiuNguyen(maSach);
        cout << "Ten sach cu: " << tenSach << endl;
        cout << "Ten sach moi: "; nhanEnterDeGiuNguyen(tenSach);
        cout << "Ten tac gia cu: " << tenTacGia << endl;
        cout << "Ten tac gia moi: "; nhanEnterDeGiuNguyen(tenTacGia);
        cout << "Nha xuat ban cu: " << nhaXuatBan << endl;
        cout << "Nha xuat ban moi: "; nhanEnterDeGiuNguyen(nhaXuatBan);
        cout << "Nam xuat ban cu: " << namXuatBan << endl;
        cout << "Nam xuat ban moi: "; nhanEnterDeGiuNguyen(namXuatBan);
        cout << "The loai cu: " << theLoai << endl;
        cout << "The loai moi: "; nhanEnterDeGiuNguyen(theLoai);        
    }
    
    void capNhatSoLuong () {
        cout << "Ten sach: " << tenSach << endl;
        cout << "So luong cu: " << soLuong << endl;
        cout << "So luong moi: ";
        do {
            cin >> soLuong; 
            cin.ignore();
        } while (soLuong < 0); 
    }

    void giamSoLuong (int SoLuong) {
        soLuong -= SoLuong;
    }

    bool operator == (string maSachKhac) {
        return this->maSach == maSachKhac;
    }

    bool operator == (Sach khac) {
        return this->maSach == khac.getMaSach();
    }

};

class KhoSach {
    private:
        MangDong <Sach> danhSach;
        int soLuong;
    public:
        KhoSach () {
            ifstream in ("sach.txt");
            in >> soLuong; in.ignore();
            for (int i = 1; i <= soLuong; i++) {
                Sach sachMoi;
                sachMoi.nhapThongTinTuFile(in);
                danhSach.themPhanTu(sachMoi);
            }
            in.close();
        }

        ~KhoSach () {
            ofstream out ("sach.txt");
            out << soLuong; 
            for (int i = 1; i <= soLuong; i++) {
                out << endl;
                danhSach[i].xuatThongTinRaFile(out);
            }
            out.close();
        }

        int getSoLuong () {
            return soLuong;
        }

        Sach getSach (string maSach) {
            for (int i = 1; i <= soLuong; i++) 
            if (danhSach[i] == maSach)
            return danhSach[i];
        }


        void xemDanhSach () {
            cout << left << setw (4) << "Stt " << setw (4) << "SL" << setw(20) << "Ten sach" << setw(15) << "Tac gia" << setw(10) << "Nha xuat ban" << endl;
            for (int i = 1; i <= soLuong; i++) {
                cout << left  << setw (4) << i;
                danhSach[i].xemThongTinCoBan();
            }
        }

        bool kiemTraTonTai (Sach sachMoi) {
            for (int i = 1; i <= soLuong; i++)
                if (danhSach[i] == sachMoi) return true;
            return false;
        }

        void themSach (Sach sachMoi) {
            if (kiemTraTonTai(sachMoi) == false) {
                soLuong++;
                danhSach.themPhanTu(sachMoi);
            }
            else {
                cout << "Them sach khong thanh cong. Ma sach da ton tai!\n";
                nhanEnterDeTiepTuc();
            };
        }
        
        void capNhatThongTinSach (int stt) {
            if (stt <= soLuong) danhSach[stt].capNhatThongTin();
        }

        void xoaSach(int stt) {
            cout << "Ten sach: " << danhSach[stt].getTenSach() << endl << endl;
            cout << "[1]: Dong y xoa\n[0]: Quay lai\n\n";
            while (true) {
                cout << "Nhap lua chon: ";
                int option; cin >> option; cin.ignore();
                if (option == 1) {
                    danhSach.xoaPhanTu(stt);
                    soLuong --;
                    break;
                }
                if (option == 0) break;

            }
        }

        void capNhatSoLuongSach (int stt) {
            danhSach[stt].capNhatSoLuong();
        }

        void giamSoLuongSach (string maSach, int soLuong) {
            for (int i = 1; i <= soLuong; i++) 
            if (danhSach[i].getMaSach() == maSach) {
                danhSach[i].giamSoLuong(soLuong);
                return;
            }
        }
        
        void tangSoLuongSach (string maSach, int soLuong) {
            for (int i = 1; i <= soLuong; i++) 
            if (danhSach[i].getMaSach() == maSach) {
                danhSach[i].giamSoLuong(-soLuong);
                return;
            }
        }
        // void Ca

        Sach& operator [] (int stt) {
            return danhSach[stt];
        }

        Sach& operator [] (string MaSach) {
            for (int i = 1; i <= soLuong; i++)
            if (danhSach[i].getMaSach() == MaSach)
            return danhSach[i];  
        }
};

class DonSach {
    private:
        string userNameBanDoc, tenBanDoc;
        string maSachMuon, tenSachMuon;
        int soLuong;
    public:
        void xuatThongTinRaFile (ofstream& out) {
            out << userNameBanDoc << ',' << tenBanDoc << ',' << maSachMuon << ',' << tenSachMuon << ',' << soLuong;
        }
        void nhapThongTinTuFile (ifstream& in) {
            getline (in, userNameBanDoc, ',');
            getline (in, tenBanDoc, ',');
            getline (in, maSachMuon, ',');
            getline (in, tenSachMuon, ',');
            in >> soLuong; in.ignore();
        }

        void taoDon (string UserName, string TenBanDoc, string MaSachMuon, string TenSachMuon, int SoLuong){
            userNameBanDoc = UserName;
            tenBanDoc = TenBanDoc;
            maSachMuon = MaSachMuon;
            tenSachMuon = TenSachMuon;
            soLuong = SoLuong;
        }
        
        void xemDon () {
            cout << left << setw(15) << tenBanDoc << setw(20) << tenSachMuon << setw(3) << soLuong <<endl;
        }

        string getTenSach () {
            return tenSachMuon;
        }
        string getUserNameNguoiMuon () {
            return userNameBanDoc;
        }
        string getMaSachMuon () {
            return maSachMuon;
        }

        int getSoLuong () {
            return soLuong;
        }
};

class DanhSachDon {
    protected:
        string tenFile;
        MangDong <DonSach> danhSach;
        int soLuong;
    public:
        DanhSachDon(string TenFile) {
            tenFile = TenFile;
            ifstream in (tenFile);
            in >> soLuong; in.ignore();
            for (int i = 1; i <= soLuong; i++) {
                DonSach donSachMoi;
                donSachMoi.nhapThongTinTuFile(in);
                danhSach.themPhanTu(donSachMoi); 
            }
        }

        ~DanhSachDon () {
            ofstream out (tenFile);
            out << soLuong;
            for (int i = 1; i <= soLuong; i++) {
                out << endl;
                danhSach[i].xuatThongTinRaFile(out);
            }
            out.close();
        }

        void themDon (DonSach donSachMoi) {
            soLuong ++;
            danhSach.themPhanTu(donSachMoi);
        }

        void xoaDon (int stt) {
            danhSach.xoaPhanTu(stt);
            soLuong --;
        }

        void xemDonSach () {
            cout << left << setw(4) << "STT" << setw(15) << "Ten ban doc" << setw(20) << "Ten sach muon" << setw(3) << "So luong" <<endl;
            for (int i = 1; i <= soLuong; i++) {
                cout << left << setw(4) << i;
                danhSach[i].xemDon();
            }
        }

        // int sttDonSachCuaBanDoc(BanDoc banDoc) {
        //     return
        // }

        DonSach operator [] (int stt) {
            return danhSach[stt];
        }

        int getSoLuong () {
            return soLuong;
        }
                
};

class DanhSachDonXinMuon : public DanhSachDon {
    public:
    DanhSachDonXinMuon() : DanhSachDon("donxinmuon.txt") {};
};

class DanhSachDonDaMuon : public DanhSachDon {
    public:
    DanhSachDonDaMuon() : DanhSachDon("dondamuon.txt") {};
};

class DanhSachDonXinTra : public DanhSachDon {
    public:
    DanhSachDonXinTra() : DanhSachDon("donxintra.txt") {};
};

class Nguoi {
protected:
    string userName;
    string hoTen, ngaySinh, noiSinh, cCCD, danToc, quocTich;
public:
    void nhapThongTinTuFile (ifstream& in) {
        getline (in, userName, ',');
        getline (in, hoTen, ',');
        getline (in, ngaySinh, ',');
        getline (in, noiSinh, ',');
        getline (in, cCCD, ',');
        getline (in, danToc, ',');
        getline (in, quocTich);
    }

    void capNhatThongTin () {
        cout << "Ho ten cu:    " << hoTen << endl;
        cout << "Ho ten moi:   "; nhanEnterDeGiuNguyen(hoTen);
        cout << "Ngay sinh cu:  " << ngaySinh << endl;
        cout << "Ngay sinh moi: "; nhanEnterDeGiuNguyen(ngaySinh);
        cout << "Noi sinh cu:   " << noiSinh << endl;
        cout << "Noi sinh moi:  "; nhanEnterDeGiuNguyen(noiSinh);
        cout << "CCCD cu:       " << cCCD << endl;
        cout << "CCCD moi:      "; nhanEnterDeGiuNguyen(cCCD);
        cout << "Dan toc cu:    " << danToc << endl;
        cout << "Dan toc moi:   "; nhanEnterDeGiuNguyen(danToc);
        cout << "Quoc tich cu:  " << quocTich << endl;
        cout << "Quoc tich moi: "; nhanEnterDeGiuNguyen(quocTich);
    }
    void xuatThongTinRaFile (ofstream& out) {
        out << userName << ',' << hoTen << ',' << ngaySinh << ',' << noiSinh << ',' << cCCD << ',' << danToc << ',' << quocTich;
    }

    void setUserName (string UserName) {
        userName = UserName;
    }

    void setHoTen (string HoTen) {
        hoTen = HoTen;
    }

    string getUserName () {
        return userName;
    }

    string getHoTen () {
        return hoTen;
    }

    bool operator == (Nguoi khac) {
        return this->userName == khac.getUserName();
    }
    void xemThongTinCoBan () {          // Xuất ra màn hình thông tin chung của cá nhân đó
        cout << left << setw (20) << hoTen << setw(12) << ngaySinh << setw(10) << noiSinh << endl;
    }

    void xemThongTinChiTiet () {
        cout << "Username:  " << userName << endl;
        cout << "Ho ten:    " << hoTen << endl;
        cout << "Ngay sinh: " << ngaySinh << endl;
        cout << "Noi sinh:  " << noiSinh << endl;
        cout << "CCCD:      " << cCCD << endl;
        cout << "Dan toc:   " << danToc << endl;
        cout << "Quoc tich: " << quocTich << endl;
    }

};

class QuanKho : public Nguoi {
    private:
    public:
        void xemKhoSach () {
            KhoSach khoSach;
            khoSach.xemDanhSach();
            while (true) {
                cout << "Nhap stt de xem chi tiet: ";
                int stt; cin >> stt; cin.ignore();
                if (stt == 0) break;
                if (stt <= khoSach.getSoLuong()) khoSach[stt].xemThongTinChiTiet();
            }
        }

        void capNhatThongTinSach () {
            KhoSach khoSach;
            cout << "Nhap stt: "; 
            int stt; cin >> stt; cin.ignore();
            khoSach.capNhatThongTinSach(stt);
        }
        
        void themThongTinSach () {
            Sach sachMoi;
            string maSachMoi, tenSachMoi, tenTacGiaMoi;
            cin.ignore();
            cout << "Nhap ma sach: "; getline(cin, maSachMoi);
            cout << "Nhap ten sach: "; getline(cin, tenSachMoi);
            cout << "Nhap ten tac gia: "; getline(cin, tenTacGiaMoi);
            
            sachMoi.setMaSach(maSachMoi);
            sachMoi.setTenSach(tenSachMoi);
            sachMoi.setTenTacGia(tenTacGiaMoi);
            KhoSach khoSach;
            khoSach.themSach(sachMoi);
        }

        void xoaThongTinSach () {
            cout << "Nhap STT sach can xoa:  ";
            int stt; cin >> stt; cin.ignore();
            KhoSach khoSach;
            khoSach.xoaSach(stt);
        }

        void capNhatSoLuongSach () {
            cout << "Nhap stt sach can cap nhat so luong: ";
            int stt; cin >> stt; cin.ignore();
            KhoSach khoSach;
            khoSach.capNhatSoLuongSach(stt);
        }
};

class DanhSachQuanKho {
private:
    MangDong <QuanKho> danhSach;   
    int soLuong;
public:
    DanhSachQuanKho () {
        ifstream in ("quankho.txt");
        in >> soLuong; in.ignore();
        for (int i= 1; i <= soLuong; i++) {
            QuanKho quanKhoMoi;
            quanKhoMoi.nhapThongTinTuFile(in);
            danhSach.themPhanTu(quanKhoMoi);
        }
        in.close();
    }

    ~DanhSachQuanKho () {
        ofstream out ("quankho.txt");
        out << soLuong;
        for (int i = 1; i <= soLuong; i++) {
            out << endl;
            danhSach[i].xuatThongTinRaFile(out);
        }
        out.close();
    }

    QuanKho kiemTra (TaiKhoan &user) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() == user.getUserName()) return danhSach[i];
    }

    void themQuanKho (QuanKho &quanKhoMoi) {
        soLuong ++;
        danhSach.themPhanTu(quanKhoMoi);
    }

    void xemDanhSach() {            // xuất ra thông tin chung của danh sách
        cout << left << setw(3) << "Stt" << setw (20) << "Ho ten" << setw(10) << "Ngay sinh" << setw(10) << "Noi sinh" << endl;
        for (int i = 1; i <= soLuong; i++) {
            cout << left << setw(3) << i;
            danhSach[i].xemThongTinCoBan();
        }
    }

    void capNhatQuanKho (int stt) {
        danhSach[stt].capNhatThongTin();
    }

    void xoaQuanKho(int stt) {
        if (stt > soLuong) return; 
        cout << "Quan kho: " << danhSach[stt].getHoTen() << endl << endl;
        cout << "[1]: Dong y xoa\n[0]: Quay lai\n\n";
        while (true) {
            cout << "Nhap lua chon: ";
            int option; cin >> option; cin.ignore();
            if (option == 1) {
                danhSach.xoaPhanTu(stt);
                soLuong --;
                break;
            }
            if (option == 0) break;

        }
    }
    int getSoThuTu(string userName) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() ==  userName)
        return i;
    }

    QuanKho& operator[] (int i) {
        return danhSach[i];
    }

    int getSoLuong () {
        return soLuong;
    }
};

class BanDoc : public Nguoi {
    public:
        void xemKhoSach() {
            KhoSach khoSach;
            khoSach.xemDanhSach();
            while (true) {
                cout << "Nhap stt de xem chi tiet: ";
                int stt; cin >> stt; cin.ignore();
                if (stt == 0) break;
                if (stt <= khoSach.getSoLuong()) khoSach[stt].xemThongTinChiTiet();
            }
        };

        void yeuCauMuonSach() {
            KhoSach khoSach;
            cout << "Nhap stt sach muon: ";
            int stt; cin >> stt; cin.ignore();
            if (stt <=0) return;
            if (stt > khoSach.getSoLuong()) {
                cout << "Stt khong hop le!\n";
                nhanEnterDeTiepTuc();
                return;
            }
            cout << "Ten sach: " << khoSach[stt].getTenSach() << endl;
            cout << "So luong: " << khoSach[stt].getSoLuong() << endl;

            cout << "\nSo luong muon: ";
            int soLuongMuon; cin >> soLuongMuon; cin.ignore();

            if (soLuongMuon <= 0) return;
            if (soLuongMuon > khoSach[stt].getSoLuong()) {
                cout << "Khong du so luong de muon!\n";
                nhanEnterDeTiepTuc();
                return;
            }

            DonSach donSachMoi;
            donSachMoi.taoDon(userName, hoTen, khoSach[stt].getMaSach(), khoSach[stt].getTenSach(), soLuongMuon);
            DanhSachDonXinMuon danhSachDonXinMuon;
            danhSachDonXinMuon.themDon(donSachMoi);
        }
        
        void yeuCauTraSach () {
            DanhSachDonDaMuon danhSachDonDaMuon;
            DanhSachDonXinTra danhSachDonXinTra;
            
            int sttDonDaMuon [10];
            int sLDonDaMuon = 0;
            cout << left << setw(4) << "STT " << setw(20) << "Ten sach" << setw(4) << "SL" <<  endl;
            for (int i = 1; i <= danhSachDonDaMuon.getSoLuong(); i++) {
                if (danhSachDonDaMuon[i].getUserNameNguoiMuon() == userName) {
                    sLDonDaMuon++;
                    sttDonDaMuon[sLDonDaMuon] = i;
                    DonSach donSach = danhSachDonDaMuon[i];
                    cout << left << setw(4) << sLDonDaMuon << setw(20) << donSach.getTenSach() << setw(4) << donSach.getSoLuong()  << endl;
                }
            }
            
            cout << "Nhap stt: ";
            int stt; cin >> stt; cin.ignore();
            if (stt <= 0) return;
            if (stt > sLDonDaMuon) {
                cout << "Stt khong hop le!\n";
                nhanEnterDeTiepTuc();
                return;
            }
            DonSach donSachCanTra = danhSachDonDaMuon[stt];
            danhSachDonDaMuon.xoaDon(sttDonDaMuon[stt]);
            danhSachDonXinTra.themDon(donSachCanTra);
             
        }
        void xemTinhTrangMuonSach () {
            DanhSachDonXinMuon donXinMuon;
            DanhSachDonDaMuon donDaMuon;
            DanhSachDonXinTra donXinTra;
            cout << left << setw(4) << "STT" << setw(20) << "Ten sach " << setw(3) << "SL" << "Tinh trang" << endl;
            int stt = 0;
            
            for (int i = 1; i <= donXinMuon.getSoLuong(); i++)
            if (donXinMuon[i].getUserNameNguoiMuon() == userName) {
                stt ++;
                DonSach donSach = donXinMuon[i];
                cout << left << setw(4) << stt << setw(20) << donSach.getTenSach() << setw(3) << donSach.getSoLuong() <<  "DANGXINMUON" << endl;
            }

            for (int i = 1; i <= donDaMuon.getSoLuong(); i++)
            if (donDaMuon[i].getUserNameNguoiMuon() == userName) {
                stt ++;
                DonSach donSach = donDaMuon[i];
                cout << left << setw(4) << stt << setw(20) << donSach.getTenSach() << setw(3) << donSach.getSoLuong() <<  "DAMUON" << endl;
            }

            for (int i = 1; i <= donXinTra.getSoLuong(); i++)
            if (donXinTra[i].getUserNameNguoiMuon() == userName) {
                stt ++;
                DonSach donSach = donXinTra[i];
                cout << left << setw(4) << stt << setw(20) << donSach.getTenSach() << setw(3) << donSach.getSoLuong() <<  "DANGXINTRA" << endl;
            }
            nhanEnterDeTiepTuc();
        }
        
};

class DanhSachBanDoc {
private:
    MangDong <BanDoc> danhSach;
    int soLuong;
public:
    DanhSachBanDoc () {
        ifstream in ("bandoc.txt");
        in >> soLuong; in.ignore();
        for (int i= 1; i <= soLuong; i++) {
            BanDoc banDocMoi;
            banDocMoi.nhapThongTinTuFile(in);
            danhSach.themPhanTu(banDocMoi);
        }
        in.close();
    }

    ~DanhSachBanDoc () {
        ofstream out ("bandoc.txt");
        out << soLuong;
        for (int i = 1; i <= soLuong; i++) {
            out << endl;
            danhSach[i].xuatThongTinRaFile(out);
        }
        out.close();
    }

    BanDoc kiemTra (TaiKhoan& user) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() == user.getUserName()) return danhSach[i];
    }

    void themBanDoc (BanDoc &banDocMoi) {
        soLuong ++;
        danhSach.themPhanTu(banDocMoi);
    }

    void xemDanhSach() {            // xuất ra thông tin chung của danh sách
        cout << left << setw(3) << "Stt" << setw (20) << "Ho ten" << setw(10) << "Ngay sinh" << setw(10) << "Noi sinh" << endl;
        for (int i = 1; i <= soLuong; i++) {
            cout << left << setw(3) << i;
            danhSach[i].xemThongTinCoBan();
        }
    }

    void capNhatBanDoc (int stt) {
        danhSach[stt].capNhatThongTin();
    }
    

    void xoaBanDoc(int stt) {
        if (stt > soLuong) return; 
        cout << "Ban doc: " << danhSach[stt].getHoTen() << endl << endl;
        cout << "[1]: Dong y xoa\n[0]: Quay lai\n\n";
        while (true) {
            cout << "Nhap lua chon: ";
            int option; cin >> option; cin.ignore();
            if (option == 1) {
                danhSach.xoaPhanTu(stt);
                soLuong --;
                break;
            }
            if (option == 0) break;

        }
    }
    int getSoThuTu(string userName) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() ==  userName)
        return i;
    }

    BanDoc& operator[] (int i) {
        return danhSach[i];
    }

    int getSoLuong () {
        return soLuong;
    }
};

class ThuNgan : public Nguoi {
    private:
                
    public:
        void xemBanDoc () {
            DanhSachBanDoc danhSachBanDoc;
            danhSachBanDoc.xemDanhSach();
            while (true) {
                cout << "Nhap stt de xem chi tiet: ";
                int stt;
                cin >> stt; cin.ignore();
                if (stt == 0) break;
                if (stt <= danhSachBanDoc.getSoLuong())
                    danhSachBanDoc[stt].xemThongTinChiTiet();
            }
        }

        void xemKhoSach () {
            KhoSach khoSach;
            khoSach.xemDanhSach();
            while (true) {
                cout << "Nhap stt de xem chi tiet: ";
                int stt; cin >> stt; cin.ignore();
                if (stt <= 0) break;
                if (stt <= khoSach.getSoLuong()) khoSach[stt].xemThongTinChiTiet();
            }
        }

        void xemSachDaMuon () {
            DanhSachDonDaMuon danhSachDaMuon;
            danhSachDaMuon.xemDonSach();
            nhanEnterDeTiepTuc();            
        }

        void duyetMuonSach () {
            DanhSachDonXinMuon danhSachDonXinMuon;
            DanhSachDonDaMuon danhSachDonDaMuon;
            KhoSach khoSach;

            danhSachDonXinMuon.xemDonSach();
            cout << "Nhap stt: "; int stt; cin >> stt; cin.ignore();
            
            if (stt <= 0) return;
            if (stt > danhSachDonXinMuon.getSoLuong()) {
                cout << "Stt khong hop le!\n";
                nhanEnterDeTiepTuc();
                return; 
            }
            DonSach  donSachMuon = danhSachDonXinMuon[stt];
 

            if (donSachMuon.getSoLuong() > khoSach.getSach(donSachMuon.getMaSachMuon()).getSoLuong()) {
                cout << "Khong du sach de cho muon!\n";
                nhanEnterDeTiepTuc();
                return;
            }

            danhSachDonDaMuon.themDon(donSachMuon);
            danhSachDonXinMuon.xoaDon(stt);
            khoSach.giamSoLuongSach(donSachMuon.getMaSachMuon(), donSachMuon.getSoLuong());
        }

        void duyetTraSach () {
            DanhSachDonXinTra danhSachDonXinTra;
            KhoSach khoSach;
            danhSachDonXinTra.xemDonSach();
            cout << "Nhap stt: "; 
            int stt; cin >> stt; cin.ignore();
            if (stt <= 0) return;
            if (stt > danhSachDonXinTra.getSoLuong()) {
                cout << "Stt khong hop le!\n";
                nhanEnterDeTiepTuc();
                return; 
            }

            khoSach.tangSoLuongSach(danhSachDonXinTra[stt].getMaSachMuon(), danhSachDonXinTra[stt].getSoLuong());
            danhSachDonXinTra.xoaDon(stt);

        }
};

class DanhSachThuNgan {
private:
    MangDong <ThuNgan> danhSach;
    int soLuong;
public:
    DanhSachThuNgan () {
        ifstream in ("thungan.txt");
        in >> soLuong; in.ignore();
        for (int i= 1; i <= soLuong; i++) {
            ThuNgan thuNganMoi;
            thuNganMoi.nhapThongTinTuFile(in);
            danhSach.themPhanTu(thuNganMoi);
        }
        in.close();
    }

    ~DanhSachThuNgan () {
        ofstream out ("thungan.txt");
        out << soLuong;
        for (int i = 1; i <= soLuong; i++) {
            out << endl;
            danhSach[i].xuatThongTinRaFile(out);
        }
        out.close();
    }

    void themThuNgan (ThuNgan &thuNganMoi) {
        soLuong ++;
        danhSach.themPhanTu(thuNganMoi);
    }

    void xemDanhSach() {            // xuất ra thông tin chung của danh sách
        cout << left << setw(4) << "Stt" << setw (20) << "Ho ten" << setw(12) << "Ngay sinh" << setw(10) << "Noi sinh" << endl;
        for (int i = 1; i <= soLuong; i++) {
            cout << left << setw(4) << i;
            danhSach[i].xemThongTinCoBan();
        }
    }

    void capNhatThuNgan (int stt) {
        if (0 < stt && stt <= soLuong) danhSach[stt].capNhatThongTin();
        else {
            cout << "Stt khong hop le!\n";
            nhanEnterDeTiepTuc();
        }
    }

    void capNhatThuNgan (string userName) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() == userName) {
            capNhatThuNgan(i);
            return;
        }
    }
    
    void xoaThuNgan(int stt) {
        if (stt > soLuong) return; 
        cout << "Thu ngan: " << danhSach[stt].getHoTen() << endl << endl;
        cout << "[1]: Dong y xoa\n[0]: Quay lai\n\n";
        while (true) {
            cout << "Nhap lua chon: ";
            int option; cin >> option; cin.ignore();
            if (option == 1) {
                danhSach.xoaPhanTu(stt);
                soLuong --;
                break;
            }
            if (option == 0) break;
        }
    }

    ThuNgan kiemTra (TaiKhoan &user) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() == user.getUserName()) return danhSach[i];
    }

    ThuNgan& operator[] (int i) {
        return danhSach[i];
    }

    int getSoThuTu(string userName) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() ==  userName)
        return i;
    }
    int getSoLuong () {
        return soLuong;
    }
};

class QuanLi : public Nguoi {
private:
public:
    
    void themTaiKhoan (TaiKhoan& taiKhoanMoi, int quyenTruyCap) {
        DanhSachTaiKhoan danhSachTaiKhoan;
        taiKhoanMoi.setQuyenTruyCap(quyenTruyCap);
        while (true) {
            taiKhoanMoi.nhap();
            if (danhSachTaiKhoan.kiemTraTonTai(taiKhoanMoi) == false) {
                danhSachTaiKhoan.themTaiKhoan(taiKhoanMoi);
                cout << "Them thanh cong!";
                break;
            }
            else cout << "Username da ton tai. Vui long nhap username khac!\n";
        }
    }

    void themQuanLi () {
        TaiKhoan taiKhoanMoi;
        themTaiKhoan(taiKhoanMoi,1);
    }

    void themThuNgan () {
        DanhSachThuNgan danhSachThuNgan;

        cout << "Nhap ho ten: ";
        string hoTenMoi;
        getline(cin, hoTenMoi);
        TaiKhoan taiKhoanMoi;
        themTaiKhoan(taiKhoanMoi,2);

        ThuNgan thuNganMoi;
        thuNganMoi.setUserName(taiKhoanMoi.getUserName());
        thuNganMoi.setHoTen(hoTenMoi);
        danhSachThuNgan.themThuNgan(thuNganMoi);
    }

    void xemThuNgan () {
        DanhSachThuNgan danhSachThuNgan;

        danhSachThuNgan.xemDanhSach();
        while (true) {
            cout << "\nNhap stt de xem chi tiet: ";
            int stt; cin >> stt; cin.ignore();
            if (stt == 0) break;
            if (stt <= danhSachThuNgan.getSoLuong())
                danhSachThuNgan[stt].xemThongTinChiTiet();
        }
    }

    void capNhatThuNgan () {
        DanhSachThuNgan danhSachThuNgan;

        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        if (stt <= 0) return;
        if (stt > danhSachThuNgan.getSoLuong()) {
            cout << "Stt khong hop le!\n";
            return;
        }
        danhSachThuNgan.capNhatThuNgan(stt);
    }

    void xoaThuNgan () {
        DanhSachTaiKhoan danhSachTaiKhoan;
        DanhSachThuNgan danhSachThuNgan;

        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        danhSachTaiKhoan.xoaTaiKhoan(danhSachThuNgan[stt].getUserName());
        danhSachThuNgan.xoaThuNgan(stt);

    }


    void themQuanKho () {
        DanhSachQuanKho danhSachQuanKho;

        cout << "Nhap ho ten: ";
        string hoTenMoi;
        getline(cin, hoTenMoi);
        TaiKhoan taiKhoanMoi;
        themTaiKhoan(taiKhoanMoi,3);

        QuanKho quanKhoMoi;
        quanKhoMoi.setUserName(taiKhoanMoi.getUserName());
        quanKhoMoi.setHoTen(hoTenMoi);
        danhSachQuanKho.themQuanKho(quanKhoMoi);
    }

    void xemQuanKho () {
        DanhSachQuanKho danhSachQuanKho;

        danhSachQuanKho.xemDanhSach();
        while (true) {
            cout << "\nNhap stt de xem chi tiet: ";
            int stt; cin >> stt; cin.ignore();
            if (stt == 0) break;
            if (stt <= danhSachQuanKho.getSoLuong())
                danhSachQuanKho[stt].xemThongTinChiTiet();
        }
    }

    void capNhatQuanKho () {
        DanhSachQuanKho danhSachQuanKho;

        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        if (stt <= 0) return;
        if (stt > danhSachQuanKho.getSoLuong()) {
            cout << "Stt khong hop le!\n";
            return;
        }
        
        danhSachQuanKho.capNhatQuanKho(stt);
    }

    void xoaQuanKho () {
        DanhSachTaiKhoan danhSachTaiKhoan;
        DanhSachQuanKho danhSachQuanKho;

        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        danhSachTaiKhoan.xoaTaiKhoan(danhSachQuanKho[stt].getUserName());
        danhSachQuanKho.xoaQuanKho(stt);

    }


    void themBanDoc () {
        DanhSachBanDoc danhSachBanDoc;

        cout << "Nhap ho ten: ";
        string hoTenMoi;
        getline(cin, hoTenMoi);
        TaiKhoan taiKhoanMoi;
        themTaiKhoan(taiKhoanMoi,4);

        BanDoc banDocMoi;
        banDocMoi.setUserName(taiKhoanMoi.getUserName());
        banDocMoi.setHoTen(hoTenMoi);
        danhSachBanDoc.themBanDoc(banDocMoi);
    }

    void xemBanDoc () {
        DanhSachBanDoc danhSachBanDoc;

        danhSachBanDoc.xemDanhSach();
        while (true) {
            cout << "\nNhap stt de xem chi tiet: ";
            int stt; cin >> stt; cin.ignore();
            if (stt == 0) break;
            if (stt <= danhSachBanDoc.getSoLuong())
                danhSachBanDoc[stt].xemThongTinChiTiet();
        }
    }

    void capNhatBanDoc () {
        DanhSachBanDoc danhSachBanDoc;

        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        if (stt <= 0) return;
        if (stt > danhSachBanDoc.getSoLuong()) {
            cout << "Stt khong hop le!\n";
            return;
        }
        
        danhSachBanDoc.capNhatBanDoc(stt);
    }

    void xoaBanDoc () {
        DanhSachTaiKhoan danhSachTaiKhoan;
        DanhSachBanDoc danhSachBanDoc;
        
        cout << "Nhap stt: ";
        int stt; cin >> stt; cin.ignore();
        danhSachTaiKhoan.xoaTaiKhoan(danhSachBanDoc[stt].getUserName());
        danhSachBanDoc.xoaBanDoc(stt);

    }

};

class DanhSachQuanLi {
private:
    MangDong <QuanLi> danhSach;
    int soLuong;
public:
    DanhSachQuanLi () {
        ifstream in ("quanli.txt");
        in >> soLuong; in.ignore();
        for (int i= 1; i <= soLuong; i++) {
            QuanLi quanLiMoi;
            quanLiMoi.nhapThongTinTuFile(in);
            danhSach.themPhanTu(quanLiMoi);        
        }
        in.close();
    }
    ~DanhSachQuanLi () {
        ofstream out ("quanli.txt");
        out << soLuong;
        for (int i = 1; i <= soLuong; i++) {
            out << endl;
            danhSach[i].xuatThongTinRaFile(out);
        }
        out.close();
    }

    QuanLi& operator[] (int i) {
        return danhSach[i];
    }

    int getSoThuTu(string userName) {
        for (int i = 1; i <= soLuong; i++)
        if (danhSach[i].getUserName() ==  userName)
        return i;
    }

    QuanLi kiemTra (TaiKhoan& user) {
        for (int i = 0; i <= soLuong; i++)
            if (danhSach[i].getUserName() == user.getUserName()) return danhSach[i];
    }

};

int dangNhap (TaiKhoan &user) {
    DanhSachTaiKhoan danhSachTaiKhoan;
    while (true) {
        system ("cls");
        user.nhap();
        if (danhSachTaiKhoan.kiemTra(user) == true) {
            cout << "Dang Nhap thanh cong \n";
            return user.getQuyenTruyCap();
        }
        else cout << "Dang nhap khong thanh cong. Kiem tra lai thong tin dang nhap!\n";
        cin.ignore();
        nhanEnterDeTiepTuc();
    }
}



void menuQuanLiThuNgan (QuanLi &quanLi) {
    while (true) {
        system("cls");
        cout << "Quan li: " << quanLi.getHoTen() << "\n1: Quan li thu ngan \n\n";
        cout << "[1]: Xem thu ngan\n[2]: Them thu ngan\n[3]: Cap nhat thu ngan\n[4]: Xoa thu ngan\n\nNhap lua chon: ";
        int option; cin >> option; cin.ignore();

        
        if (option == 0) break;
        if (option == 1) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n1: Quan li thu ngan \n";
            cout << "1.1: Danh sach thu ngan:\n\n";
            quanLi.xemThuNgan();
        }
        if (option == 2) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n1: Quan li thu ngan \n";
            cout << "1.2: Them thu ngan:\n\n";
            quanLi.themThuNgan();
        }
        if (option == 3) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n1: Quan li thu ngan \n";
            cout << "1.3: Cap nhat thu ngan:\n\n";
            quanLi.capNhatThuNgan();
        }
        if (option == 4) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n1: Quan li thu ngan \n";
            cout << "1.4: Xoa thu ngan:\n\n";
            quanLi.xoaThuNgan();
        }

    }
}

void menuQuanLiQuanKho (QuanLi &quanLi) {
    while (true) {
        system("cls");
        cout << "Quan li: " << quanLi.getHoTen() << "\n2: Quan li quan kho\n\n";
        
        cout << "[1]: Xem quan kho\n[2]: Them quan kho\n[3]: Cap nhat quan kho\n[4]: Xoa quan kho\n\nNhap lua chon:";
        int option; cin >> option; cin.ignore();
        
        
        if (option == 0) break; 
        if (option == 1) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n2: Quan li quan kho\n";
            cout << "2.1: Danh sach quan kho:\n\n";
            quanLi.xemQuanKho();
        }
        if (option == 2) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n2: Quan li quan kho\n";
            cout << "2.2: Them quan kho:\n\n";
            quanLi.themQuanKho();
        }
        if (option == 3) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n2: Quan li quan kho\n";
            cout << "2.3: Cap nhat quan kho:\n\n";
            quanLi.capNhatQuanKho();
        }
         if (option == 4) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n2: Quan li quan kho\n";
            cout << "2.4: Xoa quan kho:\n\n";
            quanLi.xoaQuanKho();
        }

    }
}

void menuQuanLiBanDoc (QuanLi &quanLi) {
    while (true) {
        system("cls");
        cout << "Quan li: " << quanLi.getHoTen() << "\n3: Quan li ban doc\n\n";
        
        cout << "[1]: Xem ban doc\n[2]: Them ban doc\n[3]: Cap nhat ban doc\n[4]: Xoa ban doc\n\nNhap lua chon:";
        int option; cin >> option; cin.ignore();

        if (option == 0) break;
        if (option == 1) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n3: Quan li ban doc\n";
            cout << "3.1: Xem ban doc\n\n";
            quanLi.xemBanDoc();
        }
        if (option == 2) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n3: Quan li ban doc\n";
            cout << "3.2: Them ban doc\n\n";
            quanLi.themBanDoc();
        }
        if (option == 3) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n3: Quan li ban doc\n";
            cout << "3.3: Cap nhat ban doc\n\n";
            quanLi.capNhatBanDoc();
        }              
        if (option == 4) {
            system("cls");
            cout << "Quan li: " << quanLi.getHoTen() << "\n3: Quan li ban doc\n\n";
            cout << "3.4: Xoa ban doc\n\n";
            quanLi.xoaBanDoc();
        }
    }
}

void menuQuanKho (TaiKhoan &user) {
    QuanKho quanKho;
    {
        DanhSachQuanKho danhSachQuanKho;
        quanKho = danhSachQuanKho.kiemTra(user);
    }
    while (true) {
        system("cls");
        cout << "Quan kho: " << quanKho.getHoTen() << "\n\n";
        cout << "[1]: Xem kho sach\n[2]: Them thong tin sach\n[3]: Cap nhat thong tin sach\n[4]: Cap nhat so luong sach\n[5]: Xoa thong tin sach\n[6]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";
        int option; cin >> option; cin.ignore();

        
        if (option == 0) break;
        if (option == 1) {
            system("cls");
            cout << "Quan kho: " << quanKho.getHoTen() << "\n1: Xem kho sach\n\n";
            quanKho.xemKhoSach();
        }
        if (option == 2) {
            system("cls");
            cout << "Quan kho: " << quanKho.getHoTen() << "\n2: Them thong tin sach\n\n";
            quanKho.themThongTinSach();
        }
        if (option == 3) {
            system("cls");
            cout << "Quan kho: " << quanKho.getHoTen() << "\n3: Cap nhat thong tin sach\n\n";
            quanKho.capNhatThongTinSach();
        }
        if (option == 4) {
            system("cls");
            cout << "Quan kho: " << quanKho.getHoTen() << "\n4: Cap nhat so luong sach\n\n";
            quanKho.capNhatSoLuongSach();
        }
        if (option == 5) {
            system("cls");
            cout << "Quan kho: " << quanKho.getHoTen() << "\n5: Xoa thong tin sach\n\n";
            quanKho.xoaThongTinSach();
        }
        if (option == 6) {
            while (true) {
            system("cls");
            cout << "Ban doc: " << quanKho.getHoTen() << "\n6: Quan li thong tin ca nhan\n";
            cout << "\n[1]: Xem thong tin ca nhan\n[2]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";

            int option; cin >> option; cin.ignore();
            if (option == 0) break;
            if (option == 1) {
                system("cls");
                cout << "Thu ngan: " << quanKho.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                cout << "5.1: Xem thong tin ca nhan\n\n";
                quanKho.xemThongTinChiTiet();
                nhanEnterDeTiepTuc();
            }
            if (option == 2) {
                system("cls");
                cout << "Thu ngan: " << quanKho.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                cout << "5.2: Cap nhat thong tin ca nhan\n\n";
                quanKho.capNhatThongTin();
            {
                DanhSachQuanKho danhSachQuanKho;
                danhSachQuanKho[danhSachQuanKho.getSoThuTu(quanKho.getUserName())] = quanKho;
            }
            }
        }
    }
   
    }
}

void menuBanDoc (TaiKhoan &user) {
    BanDoc banDoc;
    {
        DanhSachBanDoc danhSachBanDoc;
        banDoc = danhSachBanDoc.kiemTra(user);
    }
    while (true) {
        system("cls");
        cout << "Ban doc: " << banDoc.getHoTen() << "\n\n";
        cout << "[1]: Xem kho sach\n[2]: Xem tinh trang muon sach\n[3]: Dang ki muon sach\n[4]: Tra sach\n[5]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";
        int option; cin >> option; cin.ignore();

        
        if (option == 0) break;
        if (option == 1) {
            system("cls");
            cout << "Ban doc: " << banDoc.getHoTen() << "\n1: Xem kho sach\n\n";
            banDoc.xemKhoSach();
        }
        if (option == 2) {
            system("cls");
            cout << "Ban doc: " << banDoc.getHoTen() << "\n2: Xem tinh trang muon sach\n\n";
            banDoc.xemTinhTrangMuonSach();
        }
        if (option == 3) {
            system("cls");
            cout << "Ban doc: " << banDoc.getHoTen() << "\n3: Dang ki muon sach\n\n";
            banDoc.yeuCauMuonSach();
        }
        if (option == 4) {
            system("cls");
            cout << "Ban doc: " << banDoc.getHoTen() << "\n3: Tra sach\n\n";
            banDoc.yeuCauTraSach();
        }
        if (option == 5) {
            while (true) {
                system("cls");
                cout << "Ban doc: " << banDoc.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                cout << "\n[1]: Xem thong tin ca nhan\n[2]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";

                int option; cin >> option; cin.ignore();

                if (option == 0) break;
                if (option == 1) {
                    system("cls");
                    cout << "Thu ngan: " << banDoc.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.1: Xem thong tin ca nhan\n\n";
                    banDoc.xemThongTinChiTiet();
                    nhanEnterDeTiepTuc();
                }
                if (option == 2) {
                    system("cls");
                    cout << "Thu ngan: " << banDoc.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.2: Cap nhat thong tin ca nhan\n\n";
                    banDoc.capNhatThongTin();
                {
                    DanhSachBanDoc danhSachBanDoc;
                    danhSachBanDoc[danhSachBanDoc.getSoThuTu(banDoc.getUserName())] = banDoc;
                }
                }
            }
        }
    }

}

void menuThuNgan (TaiKhoan &user) {
        ThuNgan thuNgan;
        {
            DanhSachThuNgan danhSachThuNgan;
            thuNgan = danhSachThuNgan.kiemTra(user);
        }
    while (true) {
        system("cls");
        cout << "ThuNgan: " << thuNgan.getHoTen() << "\n\n";
        cout << "[1]: Xem ban doc\n[2]: Xem kho sach\n[3]: Xem sach dang muon\n[4]: Duyet muon sach\n[5]: Duyet tra sach\n[6]: Quan li thong tin ca nhan\n\nNhap lua chon: ";
        int option; cin >> option; cin.ignore();
        
        if (option == 0) break;
        if (option == 1) {
            system("cls");
            cout << "Thu ngan: " << thuNgan.getHoTen() << "\n1: Xem ban doc\n\n";
            thuNgan.xemBanDoc();
        }
        if (option == 2) {
            system("cls");
            cout << "Thu ngan: " << thuNgan.getHoTen() << "\n2: Xem kho sach\n\n";
            thuNgan.xemKhoSach();
        }
        if (option == 3) {
            system("cls");
            cout << "Thu ngan: " << thuNgan.getHoTen() << "\n3: Danh sach sach dang muon\n\n";
            thuNgan.xemSachDaMuon();
        }
        if (option == 4) {
            system("cls");
            cout << "Thu ngan: " << thuNgan.getHoTen() << "\n4: Duyet muon sach\n\n";
            thuNgan.duyetMuonSach();
        }
        if (option == 5) {
            system("cls");
            cout << "Thu ngan: " << thuNgan.getHoTen() << "\n5: Duyet tra sach\n\n";
            thuNgan.duyetTraSach();
        }
        if (option == 6) {
            while (true) {
                system("cls");
                cout << "Thu ngan: " << thuNgan.getHoTen() << "\n6: Quan li thong tin ca nhan\n";
                cout << "\n[1]: Xem thong tin ca nhan\n[2]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";

                int option; cin >> option; cin.ignore();

                if (option == 0) break;
                if (option == 1) {
                    system("cls");
                    cout << "Thu ngan: " << thuNgan.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.1: Xem thong tin ca nhan\n\n";
                    thuNgan.xemThongTinChiTiet();
                    nhanEnterDeTiepTuc();
                }
                if (option == 2) {
                    system("cls");
                    cout << "Thu ngan: " << thuNgan.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.2: Cap nhat thong tin ca nhan\n\n";
                    thuNgan.capNhatThongTin();
                {
                    DanhSachThuNgan danhSachThuNgan;
                    danhSachThuNgan[danhSachThuNgan.getSoThuTu(thuNgan.getUserName())] = thuNgan;
                }
                }
            }
        }
    }
}

void menuQuanLi (TaiKhoan user) {
    QuanLi quanLi;
    {
        DanhSachQuanLi danhSachQuanLi;
        quanLi = danhSachQuanLi.kiemTra(user);
    }

    while (true) {
        system("cls");
        cout << "Quan li: " << quanLi.getHoTen() << "\n\n";
        cout << "[1]: Quan li thu ngan\n[2]: Quan li quan kho\n[3]: Quan li nguoi doc\n[4]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";
        
        int option; cin >> option; cin.ignore();

        
        if (option == 0) break;
        if (option == 1) menuQuanLiThuNgan(quanLi);
        if (option == 2) menuQuanLiQuanKho(quanLi);
        if (option == 3) menuQuanLiBanDoc(quanLi);
        if (option == 4) {
             while (true) {
                system("cls");
                cout << "Quan li: " << quanLi.getHoTen() << "\n4: Quan li thong tin ca nhan\n";
                cout << "\n[1]: Xem thong tin ca nhan\n[2]: Cap nhat thong tin ca nhan\n\nNhap lua chon: ";

                int option; cin >> option; cin.ignore();

                if (option == 0) break;
                if (option == 1) {
                    system("cls");
                    cout << "Thu ngan: " << quanLi.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.1: Xem thong tin ca nhan\n\n";
                    quanLi.xemThongTinChiTiet();
                    nhanEnterDeTiepTuc();
                    
                }
                if (option == 2) {
                    system("cls");
                    cout << "Thu ngan: " << quanLi.getHoTen() << "\n5: Quan li thong tin ca nhan\n";
                    cout << "5.2: Cap nhat thong tin ca nhan\n\n";
                    quanLi.capNhatThongTin();
                {
                    DanhSachQuanLi danhSachQuanLi;
                    danhSachQuanLi[danhSachQuanLi.getSoThuTu(quanLi.getUserName())] = quanLi;
                }
                    
                }
            }
        }
        
    }

}


int main () {
    while (true) {
        system("cls");
        TaiKhoan user;
        int quyenTruyCap = dangNhap(user);
        if (quyenTruyCap == 1) menuQuanLi (user);
        if (quyenTruyCap == 2) menuThuNgan (user);

        if (quyenTruyCap == 3) menuQuanKho (user);
        if (quyenTruyCap == 4) menuBanDoc (user);
    }
}
