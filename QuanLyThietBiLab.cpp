#include <bits/stdc++.h>
using namespace std;

struct dsthietbi {
    string tenthietbi;
    string maso;
    string hangmuc;
    long double giatri;
    bool tinhtrang;
    int ngay, thang, nam, a;     //a: so du an da duoc mang ra su dung
    dsthietbi* next;
};

typedef dsthietbi* node;

#define HASH_SIZE 1000
node hash_table[HASH_SIZE];

//ham bam
int ham_bam(string tenthietbi) {
    int j = 9;
    for (int i = 0; i < tenthietbi.size(); i++) {
        j = (31 * j + tenthietbi[i]) % HASH_SIZE;
    }
    return abs(j);
}

//Xem thiet bi duoc muon hay chua?
void tinhtrangTB(node n){
	if(n->tinhtrang == true) {
        cout << "Thiet bi dang duoc muon!\nHan tra: " << n->ngay << "/" << n->thang << "/" << n->nam << endl;
    }
	else cout << "Thiet bi chua duoc muon!" << endl;
	return;
}

//ham insert vao file
void insert(string tenthietbi, dsthietbi device) {
    int index = ham_bam(tenthietbi); 
    node new_node = new dsthietbi(device);
    new_node->next = hash_table[index];  
    hash_table[index] = new_node;  
}

//Luu vao file
void save_to_file(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < HASH_SIZE; ++i) {
            node current = hash_table[i];
            while (current != nullptr) {
                file << current->maso << "," 
                     << current->tenthietbi << ","
                     << current->hangmuc << ","
                     << current->giatri << ","
                     << current->tinhtrang << ","
                     << current->ngay << "/"
                     << current->thang << "/"
                     << current->nam << ","
                     << current->a << endl;
                current = current->next;
            }
        }
        file.close();
    }
}

//Tai file
void load_from_file(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            dsthietbi device;
            string tinhtrang_str;
            getline(ss, device.maso, ',');
            getline(ss, device.tenthietbi, ',');
            getline(ss, device.hangmuc, ',');
            ss >> device.giatri;
            ss.ignore(1, ','); 
            getline(ss, tinhtrang_str, ',');
            device.tinhtrang = (tinhtrang_str == "1"); 
            ss >> device.ngay;
            ss.ignore(1, '/');
            ss >> device.thang;
            ss.ignore(1, '/');
            ss >> device.nam;
            ss.ignore(1, ',');
            ss >> device.a;
            insert(device.tenthietbi, device);
        }
        file.close();
    }
}

//Muon thiet bi
bool muonthietbi(node n){
	n->tinhtrang = true;
	int m;
	cout << "Nhap ngay tra: "; 
    do {
        while (!(cin >> m)) {
            cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nhap lai ngay cua ban: ";
        }
        if(m<=0 || m>32){
	    	cout << "Gia tri ban nhap khong hop le!";
	    }
    } while(m<=0 || m>32);
    n->ngay = m;
	cout << "Nhap thang tra: "; 
    do {
        while (!(cin >> m)) {
            cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nhap lai thang cua ban: ";
        }
        if(m<=0 || m>12){
		    cout << "Gia tri ban nhap khong hop le!";
	    }
    } while(m<=0 || m>12);
	n->thang = m;
	cout << "Nhap nam tra: "; 
    do {
        while (!(cin >> m)) {
            cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nhap lai nam cua ban: ";
        }
        if(m<2024){
		    cout << "Gia tri ban nhap khong hop le! hay nhap lai ";
	    }
    } while(m<2024);
	n->nam = m;
	return 1;
}

//Ham tra thiet bi
void trathietbi(node n){
	n->tinhtrang = false;
	n->ngay = n->thang = n->nam = 0;
	return;
}

//In ra 1 thiet bi
void display(node n){
    cout << setw(22) << left << n->tenthietbi << "| "
        << setw(14) << n->hangmuc << " | "
        << setw(11) <<n->maso << " | "
        << setw(13) << fixed << setprecision(2) << n->giatri << " | "
        << setw(10) << n->a << " | " << endl;        //a: so du an da duoc mang ra su dung 
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl; 
    return;
}

//Tim kiem bang ma so
node search_by_maso(string maso) {
    node temp;
    for (int i = 0; i < HASH_SIZE; i++) {
        temp = hash_table[i];
        while (temp != NULL) {
            if (temp->maso == maso) return temp;
            temp = temp->next;
        }
    }
    return temp;
}

//Tim kiem thiet bi theo ten
bool search_by_ten() {
    cin.ignore();
    cout << "\nNhap ten thiet bi ban muon tim kiem: ";
    string ten;
    getline(cin, ten);
    int n = ham_bam(ten);
    if (hash_table[n] == NULL) {
        cout << "\nKhong tim thay thiet bi nao co ten \"" << ten << "\"!" << endl;
        return false;
    }
    queue<node> st;
    node temp = hash_table[n];
    while (temp != NULL) {
        if (temp->tenthietbi == ten) {
            st.push(temp);
        }
        temp = temp->next;
    }
    int k = 1;
    if (st.empty()) {
        cout << "\nKhong tim thay thiet bi nao co ten \"" << ten << "\"!" << endl;
        return false;
    } else {
        cout << "\nCac thiet bi co ten \"" << ten << "\":" << endl;
        cout << "LIST OF DIVICE" << endl;
        cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
        cout << "| NUM  |     DEVICE NAME       |    CATEGORY    |     ID      |  PRICE (VND)  | USED TIMES |" << endl;
        cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
        while (!st.empty()) {
            node current = st.front();
            cout << "| " << setw(4) << left << k << " | ";  //Can le va chinh sua cho phu hop voi bang
            k++;
            display(current);
            st.pop(); 
        }
        return true;
    }
}

//Ham dung de nhap
void nhap_ds() {  
    int z;       //nhap so thiet bi
    cout << "Nhap vao so thiet bi: ";
    while (!(cin >> z)) {
        cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Nhap so thiet bi cua ban: ";
    }
    for(int i=0; i<z; i++) {
        int c;
        node n = new dsthietbi;
        cout << "Nhap ten thiet bi " << i+1 << " : ";
        cin.ignore();
        getline(cin, n->tenthietbi);
        cout << "Nhap hang muc: ";
        getline(cin, n->hangmuc);
        cout << "Nhap ma so: ";
        do {
            cin >> n->maso;
            if (search_by_maso(n->maso) != NULL) {
                cout << "Thiet bi co ma so " << n->maso << " da ton tai. Hay nhap lai: ";
            }
        }
        while (search_by_maso(n->maso) != NULL);
        cout << "Nhap gia tri: ";
        do {
            while (!(cin >> n->giatri)) {
            cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nhap lai gia tri cua ban: ";
        }
            if(n->giatri <= 0){
        	    cout << "Gia tri ban nhap khong hop le. Hay nhap lai: ";	
	        }
        }
        while (n->giatri < 0);
        cout << "Nhap so du an da duoc mang ra su dung: ";
        do { 
            while (!(cin >> n->a)) {
            cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Nhap lua chon cua ban: ";
        }
            if(n->a < 0){
        	    cout << "Gia tri ban nhap khong hop le. Hay nhap lai: ";
	        }
        }
        while (n->a < 0);
        n->tinhtrang = 0;
        n->ngay = 0;
        n->thang = 0;
        n->nam = 0;
        n->next = NULL;
        int idx = ham_bam(n->tenthietbi);
        n->next = hash_table[idx];
        hash_table[idx] = n;
        cout << "Thiet bi nay da duoc muon chua [1:yes/0:no]: ";
        do {
            while (!(cin >> c)) {
                cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Thiet bi nay da duoc muon chua [1:yes/0:no]: ";
                if(c != 0 && c != 1) {
                    cout << "Hay nhap lai: "; 
                }
            }
        } while(c != 0 && c != 1);
            if(c == 1) {
            muonthietbi(n);
        } 
        else continue;
    }
    cout << "Da them thiet bi thanh cong!" << endl;
}


node remove() {         //xoa thiet bi
    string id, traloi;
    cout << "Nhap ma so cua thiet bi ban muon xoa: ";
    cin.ignore();
    getline(cin, id);
    node target = search_by_maso(id);
    if (target == NULL) {
        cout << "Khong tim thay thiet bi co ma so " << id << "!" << endl;
        return NULL;
    }
    cout << "Ban co muon xoa thiet bi co ma so " << target->maso << " khong? [yes/no]: ";
    cin >> traloi;
    if (traloi != "yes") return NULL;
    int idx = ham_bam(target->tenthietbi);
    node prev = NULL, current = hash_table[idx];
    while (current != NULL && current->maso != id) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) return NULL;

    if (prev == NULL) {
        hash_table[idx] = current->next;
    }    
    else {
        prev->next = current->next;
    }
    delete current;
    cout << "Da xoa thiet bi thanh cong!" << endl;
    return NULL;
}

node chinhsua() {
    string id;
    cout << "Nhap ma so cua thiet bi ban muon sua thong tin: ";
    cin.ignore();
    getline(cin, id);
    node target = search_by_maso(id);
    if (target == NULL) {
        cout << "Khong tim thay thiet bi co ma so " << id << "!" << endl;
        return NULL;
    }
    //Xoa thiet bi tu bang bam
    int old_idx = ham_bam(target->tenthietbi);
    node prev = NULL, current = hash_table[old_idx];
    while (current != NULL && current != target) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        hash_table[old_idx] = current->next;
    } else {
        prev->next = current->next;
    }

    cout << "Nhap thong tin moi (de trong neu khong muon thay doi):\n";
    
    cout << "Nhap ten thiet bi (Hien tai: " << target->tenthietbi << "): ";
    string new_tenthietbi;
    getline(cin, new_tenthietbi);
    if (!new_tenthietbi.empty()) {
        target->tenthietbi = new_tenthietbi;
    }

    cout << "Nhap ma so thiet bi (Hien tai: " << target->maso << "): ";
    string new_maso;
    getline(cin, new_maso);
    if (!new_maso.empty()) {
        target->maso = new_maso;
    }

    cout << "Nhap hang muc (Hien tai: " << target->hangmuc << "): ";
    string input;
    getline(cin, input);
    if (!input.empty()) target->hangmuc = input;

    cout << "Nhap gia tri (Hien tai: " << target->giatri << "): ";
    getline(cin, input);
    if (!input.empty()) {
        long double n = stold(input);
        if (n >= 0) {
            target->giatri = n;
        } else {
            cout << "Gia tri nhap khong hop le!" << endl;
        }
    }

    cout << "Nhap so du an da duoc mang ra su dung (Hien tai: " << target->a << "): ";
    getline(cin, input);
    if (!input.empty()) {
        int m = stoi(input);
        if (m > 0) {
            target->a = m;
        } else {
            cout << "Gia tri nhap khong hop le!" << endl;
        }
    }
    //Cai lai thiet bi vao bang bam
    int new_idx = ham_bam(target->tenthietbi);
    target->next = hash_table[new_idx];
    hash_table[new_idx] = target;

    return target;
}

void display_all() {        //in ra man hinh
	node temp;
    cout << "LIST OF DIVICE" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    cout << "| NUM  |     DEVICE NAME       |    CATEGORY    |     ID      |  PRICE (VND)  | USED TIMES |" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    int k = 1;
    for (int j = 0; j < HASH_SIZE; j++) {
        temp = hash_table[j];
        while (temp != NULL) { 
            cout << "| " << setw(4) << left << k << " | "  //Can le va chinh sua cho phu hop voi bang
                << setw(22) << temp->tenthietbi << "| "
                << setw(14) << temp->hangmuc << " | "
                << setw(11) << temp->maso << " | "
                << setw(13) << fixed << setprecision(2) << temp->giatri << " | "
                << setw(10) << temp->a << " | " << endl;        //a: so du an da duoc mang ra su dung 
            cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;     
            temp = temp->next;    
            k++;
        }
    }   
}

void ds_muonTB() {
    node temp;
    cout << "LIST OF BORROW DIVICE" << endl;
    cout << "|------|-----------------------|-------------|---------------------------|--------------------------|" << endl;
    cout << "| NUM  |     DEVICE NAME       |     ID      |          STATUS           |   BORROW DATE(DD/MM/YY)  |" << endl;
    cout << "|------|-----------------------|-------------|---------------------------|--------------------------|" << endl;
    int k = 1;
    for (int j = 0; j < HASH_SIZE; j++) {
        temp = hash_table[j];
        while (temp != NULL) {                   
            cout << "| " << setw(4) << left << k << " | "  //Can le va chinh sua cho phu hop voi bang
                << setw(22) << temp->tenthietbi << "| "
                << setw(11) << temp->maso << " | ";
            if (temp->ngay == 0) {
                cout << " Thiet bi chua duoc muon! | _                        |" << endl;
            }
            else {
                cout << "  Thiet bi da duoc muon!  |       " 
                    << setw(2) << right << temp->ngay << "/" 
                    << setw(2) << temp->thang << "/"  
                    << setw(12) << left << temp->nam << " | " << endl;
            }
            cout << "|------|-----------------------|-------------|---------------------------|--------------------------|" << endl;     
            temp = temp->next;  
            k++;   
        }
    }    
}
// tinhtrangTB(temp);  :tinh trang thiet bi

//In ra thiet bi theo muc do su dung
bool display_mdsd(){
	vector<node> allDevices;
    for (int i = 0; i < HASH_SIZE; i++) {
        node temp = hash_table[i];
        while (temp != NULL) {
            allDevices.push_back(temp);
            temp = temp->next;
        }
    }
    if (allDevices.empty()) {
        cout << "\nKhong co thiet bi nao trong danh sach de sap xep!" << endl;
        return false;
    }
    sort(allDevices.begin(), allDevices.end(), [](node a, node b) {
        return a->a < b->a;
    });
    int k = 1;
    cout << "\nDanh sach thiet bi da sap xep theo muc do su dung tang dan:" << endl;
    cout << "LIST OF DIVICE" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    cout << "| NUM  |     DEVICE NAME       |    CATEGORY    |     ID      |  PRICE (VND)  | USED TIMES |" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    for (node device : allDevices) {
        cout << "| " << setw(4) << left << k << " | ";  //Can le va chinh sua cho phu hop voi bang
        k++;
        display(device);
    }
    return true;
}

//In ra theo gia tri
bool display_giatri(){
	vector<node> allDevices;
    for (int i = 0; i < HASH_SIZE; i++) {
        node temp = hash_table[i];
        while (temp != NULL) {
            allDevices.push_back(temp);
            temp = temp->next;
        }
    }
    if (allDevices.empty()) {
        cout << "\nKhong co thiet bi nao trong danh sach de sap xep!" << endl;
        return false;
    }
    sort(allDevices.begin(), allDevices.end(), [](node a, node b) {
        return a->giatri < b->giatri;
    });
    int k = 1;
    cout << "\nDanh sach thiet bi da sap xep theo gia tri tang dan:" << endl;
    cout << "LIST OF DIVICE" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    cout << "| NUM  |     DEVICE NAME       |    CATEGORY    |     ID      |  PRICE (VND)  | USED TIMES |" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    for (node device : allDevices) {
        cout << "| " << setw(4) << left << k << " | ";  //Can le va chinh sua cho phu hop voi bang
        k++;
        display(device);
    }
    return true;
}

void display_hangmuc() {
    map<string, vector<node>> hangmuc_map;
    for (int i = 0; i < HASH_SIZE; i++) {
        node temp = hash_table[i];
        while (temp != NULL) {
            hangmuc_map[temp->hangmuc].push_back(temp);
            temp = temp->next;
        }
    }
    int k = 1;
    cout << "LIST OF DIVICE" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    cout << "| NUM  |     DEVICE NAME       |    CATEGORY    |     ID      |  PRICE (VND)  | USED TIMES |" << endl;
    cout << "|------|-----------------------|----------------|-------------|---------------|------------|" << endl;
    for (const auto& pair : hangmuc_map) {
        for (node device : pair.second) {
            cout << "| " << setw(4) << left << k << " | ";  //Can le va chinh sua cho phu hop voi bang
            k++;
            display(device);
        }
    }
}

int main() {
    char ch;
    cout << "Nhap vao mat khau: ";
    string mk;
    getline(cin, mk);
        if(mk == "1234567") {
            load_from_file("QuanLyThietBiLab.txt");
            while (true) {
                system("cls");
                cout << endl << "Quan ly thiet bi phong thi nghiem" << endl;
                cout << "<=====================>" << endl;
                cout << "1. Them thiet bi" << endl;
                cout << "2. Chinh sua thiet bi" << endl;
                cout << "3. Xoa thiet bi" << endl;
                cout << "4. Muon thiet bi" << endl;
                cout << "5. Tra thiet bi" << endl;
                cout << "6. Tim kiem theo ten" << endl;
                cout << "7. Tim kiem theo ma so" << endl;
                cout << "8. Hien thi tat ca thiet bi" << endl;
                cout << "9. Danh sach muon, tra thiet bi" << endl;
                cout << "10. In ra danh sach theo muc do su dung" << endl;
                cout << "11. In ra danh sach theo theo gia tri" << endl;
                cout << "12. In ra danh sach theo hang muc" << endl;
                cout << "13. Luu va thoat" << endl;
                int choice;
                cout << "Moi ban nhap: ";
                while (!(cin >> choice)) {
                    cout << "Lua chon khong hop le! Vui long nhap mot so nguyen.\n";
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Nhap lua chon cua ban: ";
                }
                    if(choice == 1) {
                        nhap_ds();
                    }    
                    else if(choice == 2) {
                        chinhsua();
                    }    
                    else if(choice == 3) {
                        remove();    
                    }   
                    else if(choice == 4) {
                        string idmuon;
                    	cout<<"Nhap ma so thiet bi muon muon: ";
                        cin.ignore();
                    	getline(cin, idmuon);
                    	muonthietbi(search_by_maso(idmuon));
                        cout << "Muon thiet bi thanh cong!" << endl;
                    } 
                    else if(choice == 5) {
                        string idtra;
						cout<<"Nhap id thiet bi muon tra: ";
						cin.ignore();
						getline(cin, idtra);
						trathietbi(search_by_maso(idtra));
                    }
                    else if(choice == 6) {
                        search_by_ten();
                    }
                    else if(choice == 7) {
                        string maso;
                        cout << "Nhap ma so thiet bi ban muon tim kiem: ";
                        cin.ignore();
                        getline(cin, maso);
                        node target = search_by_maso(maso);
                        if (target == NULL) {
                            cout << "Khong tim thay thiet bi co ma so " << maso << "!" << endl;
                        } else {
                            display(target);
                        } 
                    }
                    else if(choice == 8) {
                        display_all();

                    }  
                    else if(choice == 9) {
                        ds_muonTB();
                    }    
                    else if(choice == 10) {
                        display_mdsd(); 
                    }
                    else if(choice == 11) {
                        display_giatri(); 
                    }
                    else if(choice == 12) {
                        display_hangmuc();
                    }
                    else if(choice == 13) {
                        save_to_file("QuanLyThietBiLab.txt");
                        return 0;        
                    }
                    fflush(stdin);
                    cout << "\nBam phim bat ki de tro lai menu chinh\n";
                    scanf("\n%ch", &ch);
            }    
        } else {
            cout << endl << "Mat khau nhap sai!";
        } return 0;
}   



