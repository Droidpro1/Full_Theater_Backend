//Ritvik Divanji RXD170003

#include <iostream>
#include <cctype>
#include <iomanip>
#include "theaterSeat.h"
#include "programData.h"

using namespace std;

bool isNum(string);
int login(programData*);
void mainMenu(programData*);
int subMenu(programData*);
void reserveNewOrder(programData*,auditorium*);
void viewOrder(orderData*);
bool reserveExistingOrder(auditorium*,orderData*);
void updateOrder(programData*);
bool viewOrders(programData*);
void refreshFS(programData*);
void adminMenu(programData*);
void displayReceipt(programData*);
void printReport(programData*);

void refreshFS(programData* p){
    //writes the auditoriums back to their respective files
    p->getAuditorium("a1")->writeBack();
    p->getAuditorium("a2")->writeBack();
    p->getAuditorium("a3")->writeBack();
}

int login(programData* p){
    //login function
    p->clearUsername();
    cout<<"Username: ";
    std::string username;
    cin>>username;
    while(p->getDB()->find(username)==p->getDB()->end()){
        cout<<"Sorry, that username does not exist."<<endl;
        cout<<"Username: ";
        cin>>username;
    }
    p->setUsername(username);
    cout<<"Password: ";
    std::string password;
    cin>>password;
    int tries=0;
    while(tries<2 && p->getDB()->at(username)->getPassword()!=password){
        cout<<"Sorry, that is not the correct password. "<<2-tries<<" tries left" <<endl;
        cin>>password;
        tries++;
    }
    if(p->getDB()->at(username)->getPassword()==password) {
        if(username=="admin")
            adminMenu(p);
        else
            mainMenu(p);
    }
    else
        login(p);
}

void mainMenu(programData* p){
    //main non-admin/regular user menu
    string input;
    cout<<"1. Reserve Seats\n2. View Orders\n3. Update Order\n4. Display Receipt\n5. Log Out"<<endl;
    cin>>input;
    while(!isNum(input) || stoi(input)<1 || stoi(input)>5){
        cout<<"Invalid input"<<endl;
        cout<<"1. Reserve Seats\n2. View Orders\n3. Update Order\n4. Display Receipt\n5. Log Out"<<endl;
        cin>>input;
    }

    switch(stoi(input)){
        case(1): {
            int auditorium = subMenu(p);
            switch (auditorium) {
                case (1):
                    reserveNewOrder(p, p->getAuditorium("a1"));
                    break;
                case (2):
                    reserveNewOrder(p, p->getAuditorium("a2"));
                    break;
                case (3):
                    reserveNewOrder(p, p->getAuditorium("a3"));
                    break;
            }
            mainMenu(p);
            break;
        }
        case(2):
            viewOrders(p);
            mainMenu(p);
            break;
        case(3):
            updateOrder(p);
            mainMenu(p);
            break;
        case(4):
            displayReceipt(p);
            mainMenu(p);
            break;
        case(5):
            login(p);
            return;
    }
}

int subMenu(programData* p){
    //a sub-menu for choosing an auditorium
    string input;
    cout<<"1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3"<<endl;
    cin>>input;
    while(!isNum(input) || stoi(input)<1 || stoi(input)>3){
        cout<<"Invalid input!"<<endl;
        cout<<"1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3"<<endl;
        cin>>input;
    }
    switch(stoi(input)){
        case(1): {
            p->getAuditorium("a1")->displayAuditorium();
            return 1;
        }
        case(2): {
            p->getAuditorium("a2")->displayAuditorium();
            return 2;
        }
        case(3): {
            p->getAuditorium("a3")->displayAuditorium();
            return 3;
        }
    }
}

bool viewOrders(programData* p){
    //view all the user's orders
    if(p->getDB()->at(p->getUsername())->getNumOrders()==0) {
        cout << "You have no orders." << endl;
        return false;
    }
    for(int i =0;i<p->getDB()->at(p->getUsername())->getNumOrders();i++){
        cout<<"Order "<<i+1<<" (Auditorium "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getAuditoriumNumber()<<"):"<<endl;
        cout<<setw(26)<<"Seats in the order: "<<endl;
        for(auto seat : p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getOrderedSeats()){
            cout<<setw(12)<<seat->getRow()<<seat->getSeat()<<endl;
        }
        cout<<setw(29)<<"Number of Child seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getChildSeats()<<endl;
        cout<<setw(29)<<"Number of Adult seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getAdultSeats()<<endl;
        cout<<setw(30)<<"Number of Senior seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getSeniorSeats()<<endl;
    }
    return true;
}

void updateOrderHelper(programData* p,string orderNumber){
    cout<<"1. Add tickets\n2. Delete tickets\n3. Cancel order"<<endl;
    string input;
    cin>>input;
    while(!isNum(input) || stoi(input)<1 || stoi(input)>3){
        cout<<"Invalid input!"<<endl;
        cout<<"1.Add tickets\n2. Delete tickets\n3. Cancel order"<<endl;
        cin>>input;
    }
    switch(stoi(input)){
        case(1): {
            //add tickets to an existing order
            //if they cannot be added then return to the menu
            int auditorium = p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))->getAuditoriumNumber();
            switch (auditorium) {
                case (1):
                    p->getAuditorium("a1")->displayAuditorium();
                    if(reserveExistingOrder(p->getAuditorium("a1"), p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))))
                        mainMenu(p);
                    else
                        updateOrderHelper(p,orderNumber);
                    break;
                case (2):
                    p->getAuditorium("a2")->displayAuditorium();
                    if(reserveExistingOrder(p->getAuditorium("a2"), p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))))
                        mainMenu(p);
                    else
                        updateOrderHelper(p,orderNumber);
                    break;
                case (3):
                    p->getAuditorium("a3")->displayAuditorium();
                    if(reserveExistingOrder(p->getAuditorium("a3"), p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))))
                        mainMenu(p);
                    else
                        updateOrderHelper(p,orderNumber);
                    break;
            }
            break;
        }
        case(2): {
            //delete tickets from an order
            //if the order is then empty,
            //remove the order
            viewOrder(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1)));
            int row;
            string col;
            cout << "Which row is the seat you'd like to remove in?" << endl;
            cin >> row;
            while (!isNum(to_string(row))) {
                cout << "Invalid input!" << endl;
                cout << "Which row is the seat you'd like to remove in?" << endl;
                cin >> row;
            }
            cout << "Which column is the seat you'd like to remove in?" << endl;
            cin >> col;
            while (col.length() != 1 && isNum(col)) {
                cout << "Which column is the seat you'd like to remove in?" << endl;
                cout << "Invalid input!" << endl;
                cin >> col;
            }
            if(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))->removeSeat(col[0],row)) {
                cout<<"The seat has been removed"<<endl;
                if(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))->getNumSeats()==0){
                    p->getDB()->at(p->getUsername())->cancelOrder(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1)));
                    cout<<"All seats from the order have been removed. The order has been cancelled."<<endl;
                }
                mainMenu(p);
            }
            else {
                cout<<"That seat does not exist in the order"<<endl;
                updateOrderHelper(p,orderNumber);
            }
            break;
        }
        case(3):
            //cancel the order:
            //unreserve the seats in the order
            //remove the order from the list
            for(auto seat : p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))->getOrderedSeats()){
                p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1))->removeSeat(seat);
            }
            p->getDB()->at(p->getUsername())->cancelOrder(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(stoi(orderNumber)-1)));
            cout<<"The order has been cancelled."<<endl;
            mainMenu(p);
            break;
    }
}

void updateOrder(programData* p){
    //this is the menu to update orders
    //also includes the code to all the menu options
    if(!viewOrders(p))
        return;
    cout<<"Which order would you like to edit?"<<endl;
    string orderNumber;
    cin>>orderNumber;
    while(!isNum(orderNumber) || stoi(orderNumber)<1 || stoi(orderNumber)>p->getDB()->at(p->getUsername())->getNumOrders()){
        cout<<"Invalid input!"<<endl;
        cout<<"Which order would you like to edit?"<<endl;
        cin>>orderNumber;
    }
    updateOrderHelper(p,orderNumber);
}

void displayReceipt(programData* p){
    //view all the user's orders
    double totalCost=0.0;
    double cost=0.0;
    if(p->getDB()->at(p->getUsername())->getNumOrders()==0) {
        cout << "You have no orders." << endl;
        return;
    }
    for(int i =0;i<p->getDB()->at(p->getUsername())->getNumOrders();i++){
        cout<<"Order "<<i+1<<" (Auditorium "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getAuditoriumNumber()<<"):"<<endl;
        cout<<setw(26)<<"Seats in the order: "<<endl;
        for(auto seat : p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getOrderedSeats()){
            cout<<setw(12)<<seat->getRow()<<seat->getSeat()<<endl;
        }
        cout<<setw(29)<<"Number of Child seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getChildSeats()<<endl;
        cout<<setw(29)<<"Number of Adult seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getAdultSeats()<<endl;
        cout<<setw(30)<<"Number of Senior seats: "<<p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getSeniorSeats()<<endl;
        cost=((p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getChildSeats()*5.0)+(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getAdultSeats()*10.0)+(p->getDB()->at(p->getUsername())->getOrders().at(static_cast<size_t>(i))->getSeniorSeats()*7.5));
        cout<<setw(12)<<"Cost: "<<setprecision(2)<<fixed<<"$"<<cost<<endl;
        totalCost+=cost;
    }
    cout<<"Total cost: "<<setprecision(2)<<fixed<<"$"<<totalCost<<endl;
}

void adminMenu(programData* p){
    //main menu for the admins
    cout<<"1. Print report\n2. Logout\n3. Exit"<<endl;
    string input;
    cin>>input;
    while(input.length()!=1 || !isNum(input) || stoi(input)<1 || stoi(input)>3){
        cout<<"Invalid input"<<endl;
        cout<<"1. Print report\n2. Logout\n3. Exit"<<endl;
        cin>>input;
    }
    switch(stoi(input)){
        case(1):
            printReport(p);
            adminMenu(p);
            break;
        case(2):
            login(p);
            break;
        case(3):
            refreshFS(p);
            exit(0);
    }
}

void printReport(programData* p){
    cout<<setw(26)<<"Open Seats"<<setw(16)<<"Reserved Seats"<<setw(13)<<"Adult Seats"<<setw(13)<<"Child Seats"<<setw(14)<<"Senior Seats"<<setw(14)<<"Ticket Sales"<<endl;
    cout<<"Auditorium 1:"<<setw(9)<<p->getAuditorium("a1")->getNumOpenSeats()<<setw(15)<<p->getAuditorium("a1")->getNumReservedSeats()<<setw(14)<<p->getAuditorium("a1")->getNumSeatType('A')<<setw(13)<<p->getAuditorium("a1")->getNumSeatType('C')<<setw(13)<<p->getAuditorium("a1")->getNumSeatType('S')<<setw(10)<<setprecision(2)<<fixed<<"$"<<p->getAuditorium("a1")->getTotalSales()<<endl;
    cout<<"Auditorium 2:"<<setw(9)<<p->getAuditorium("a2")->getNumOpenSeats()<<setw(15)<<p->getAuditorium("a2")->getNumReservedSeats()<<setw(14)<<p->getAuditorium("a2")->getNumSeatType('A')<<setw(13)<<p->getAuditorium("a2")->getNumSeatType('C')<<setw(13)<<p->getAuditorium("a2")->getNumSeatType('S')<<setw(10)<<setprecision(2)<<fixed<<"$"<<p->getAuditorium("a2")->getTotalSales()<<endl;
    cout<<"Auditorium 3:"<<setw(9)<<p->getAuditorium("a3")->getNumOpenSeats()<<setw(15)<<p->getAuditorium("a3")->getNumReservedSeats()<<setw(14)<<p->getAuditorium("a3")->getNumSeatType('A')<<setw(13)<<p->getAuditorium("a3")->getNumSeatType('C')<<setw(13)<<p->getAuditorium("a3")->getNumSeatType('S')<<setw(10)<<setprecision(2)<<fixed<<"$"<<p->getAuditorium("a3")->getTotalSales()<<endl;
    cout<<"Total:"<<setw(16)<<p->getAuditorium("a1")->getNumOpenSeats()+p->getAuditorium("a2")->getNumOpenSeats()+p->getAuditorium("a3")->getNumOpenSeats()<<setw(15)<<p->getAuditorium("a1")->getNumReservedSeats()+p->getAuditorium("a2")->getNumReservedSeats()+p->getAuditorium("a3")->getNumReservedSeats()<<setw(14)<<p->getAuditorium("a1")->getNumSeatType('A')+p->getAuditorium("a2")->getNumSeatType('A')+p->getAuditorium("a3")->getNumSeatType('A')<<setw(13)<<p->getAuditorium("a1")->getNumSeatType('C')+p->getAuditorium("a2")->getNumSeatType('C')+p->getAuditorium("a3")->getNumSeatType('C')<<setw(13)<<p->getAuditorium("a1")->getNumSeatType('S')+p->getAuditorium("a2")->getNumSeatType('S')+p->getAuditorium("a3")->getNumSeatType('S')<<setw(10)<<setprecision(2)<<fixed<<"$"<<p->getAuditorium("a1")->getTotalSales()+p->getAuditorium("a2")->getTotalSales()+p->getAuditorium("a3")->getTotalSales()<<endl;
}

void viewOrder(orderData* order){
    //view a specific order
    cout<<"Auditorium "<<order->getAuditoriumNumber()<<endl;
    cout<<"Seats in the order: "<<endl;
    for(auto seat : order->getOrderedSeats()){
        cout<<setw(5)<<seat->getRow()<<seat->getSeat()<<endl;
    }
    cout<<endl;
}



bool reserveExistingOrder(auditorium* a,orderData* order){
    //add tickets to an existing order
    //returns whether or not there were tickets to be added
    string r;
    string col;
    string adult;
    string child;
    string senior;
    cout<<"Which row would you like to reserve a seat in?"<<endl;
    cin>>r;
    while(r.length()!=1 || !isNum(r) || (stoi(r)>a->getRows()|| stoi(r)<=0)){
        cout<<"Invalid input"<<endl;
        cout<<"Which row would you like to reserve a seat in?"<<endl;
        cin>>r;
    }
    cout<<"\nWhich column would you like to reserve a seat in?"<<endl;
    cin>>col;
    while(col.length()!=1 || isNum(col) || (a->getColumnHeader()).find(static_cast<char>(toupper(col[0])))==static_cast<size_t>(-1)){
        cout<<"Invalid input"<<endl;
        cout<<"\nWhich column would you like to reserve a seat in?"<<endl;
        cin>>col;
    }
    do{
        cout<<"\nHow many adult seats would you like to reserve?"<<endl;
        cin>>adult;
        while(!isNum(adult) || stoi(adult)<0 || stoi(adult)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many adult seats would you like to reserve?"<<endl;
            cin>>adult;
        }
        cout<<"\nHow many child seats would you like to reserve?"<<endl;
        cin>>child;
        while(col.length()!=1 || !isNum(child) || stoi(child)<0 || stoi(child)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many child seats would you like to reserve?"<<endl;
            cin>>child;
        }
        cout<<"\nHow many senior seats would you like to reserve?"<<endl;
        cin>>senior;
        while(!isNum(senior) || stoi(senior)<0 || stoi(senior)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many senior seats would you like to reserve?"<<endl;
            cin>>senior;
        }
        if(stoi(adult)+stoi(child)+stoi(senior)>a->getCols() || stoi(adult)+stoi(child)+stoi(senior)<=0)
            cout<<"Those seats don't add up..."<<endl;
    }while(stoi(adult)+stoi(child)+stoi(senior)>a->getCols() || stoi(adult)+stoi(child)+stoi(senior)<=0);
    col[0]= static_cast<char>(toupper(col[0]));
    if(a->checkAvailable(stoi(r), col[0], stoi(adult)+stoi(child)+stoi(senior))){
        a->reserveSeats(stoi(r), col[0], stoi(adult), stoi(child), stoi(senior),order);
        return true;
    }
    else{
        cout<<"Those seats aren't available, sorry :("<<endl;
        return false;
    }
}

void reserveNewOrder(programData* p,auditorium* a){
    //create a new order, add seats to it, and add it to the order vector
    string r;
    string col;
    string adult;
    string child;
    string senior;
    auto order = new orderData();
    switch(a->getFileName()[1]){
        case('1'):
            order->setAuditoriumNumber(1);
            break;
        case('2'):
            order->setAuditoriumNumber(2);
            break;
        case('3'):
            order->setAuditoriumNumber(3);
            break;
    }
    cout<<"Which row would you like to reserve a seat in?"<<endl;
    cin>>r;
    while(r.length()!=1 || !isNum(r) || (stoi(r)>a->getRows()|| stoi(r)<=0)){
        cout<<"Invalid input"<<endl;
        cout<<"Which row would you like to reserve a seat in?"<<endl;
        cin>>r;
    }
    cout<<"\nWhich column would you like to reserve a seat in?"<<endl;
    cin>>col;
    while(col.length()!=1 || isNum(col) || (a->getColumnHeader()).find(static_cast<char>(toupper(col[0])))==static_cast<size_t>(-1)){
        cout<<"Invalid input"<<endl;
        cout<<"\nWhich column would you like to reserve a seat in?"<<endl;
        cin>>col;
    }
    do{
        cout<<"\nHow many adult seats would you like to reserve?"<<endl;
        cin>>adult;
        while(!isNum(adult) || stoi(adult)<0 || stoi(adult)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many adult seats would you like to reserve?"<<endl;
            cin>>adult;
        }
        cout<<"\nHow many child seats would you like to reserve?"<<endl;
        cin>>child;
        while(col.length()!=1 || !isNum(child) || stoi(child)<0 || stoi(child)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many child seats would you like to reserve?"<<endl;
            cin>>child;
        }
        cout<<"\nHow many senior seats would you like to reserve?"<<endl;
        cin>>senior;
        while(!isNum(senior) || stoi(senior)<0 || stoi(senior)>a->getCols()){
            cout<<"Invalid input"<<endl;
            cout<<"\nHow many senior seats would you like to reserve?"<<endl;
            cin>>senior;
        }
        if(stoi(adult)+stoi(child)+stoi(senior)>a->getCols() || stoi(adult)+stoi(child)+stoi(senior)<=0)
            cout<<"Those seats don't add up..."<<endl;
    }while(stoi(adult)+stoi(child)+stoi(senior)>a->getCols() || stoi(adult)+stoi(child)+stoi(senior)<=0);
    bool reserved=false;
    col[0]= static_cast<char>(toupper(col[0]));
    if(a->checkAvailable(stoi(r), col[0], stoi(adult)+stoi(child)+stoi(senior))){
        order=a->reserveSeats(stoi(r), col[0], stoi(adult), stoi(child), stoi(senior),order);
        p->getDB()->at(p->getUsername())->addOrder(order);
        reserved=true;
    }
    if(!reserved) {
        theaterSeat *seat = a->bestAvailable(stoi(adult) + stoi(child) + stoi(senior));
        if (!seat)
            cout << "No best seats are available.\nSorry :(" << endl;
        else {
            cout << "\nThose seats aren't available\nWould you like to reserve the best available seats starting with "
                 << seat->getRow() << seat->getSeat() << "?" << endl;
            cout << "Y/N:" << endl;
            string input;
            cin >> input;
            input[0]= static_cast<char>(toupper(input[0]));
            while (input.length()!=1 || (input[0] != 'Y' && input[0] != 'N')) {
                input[0]= static_cast<char>(toupper(input[0]));
                cout << "Invalid input!" << endl;
                cout << "Y/N:" << endl;
                cin >> input;
                input[0]= static_cast<char>(toupper(input[0]));
            }
            input[0]= static_cast<char>(toupper(input[0]));
            if (input == "Y") {
                order = a->reserveSeats(seat->getRow(), seat->getSeat(), stoi(adult), stoi(child), stoi(senior), order);
                p->getDB()->at(p->getUsername())->addOrder(order);
            }
            else
                mainMenu(p);
        }
    }
    mainMenu(p);
}

bool isNum(string r){
    //function for input validation to check if a string is a number
    for (auto c : r) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main(){
    //create the dataBase and programData object
    //the programData object exists to help passing multiple things from one function to another


    auto db = new unordered_map<string,userData*>;
    auto p = new programData(db);

    ifstream inData("userdb.dat");
    string sLine,username,password;
    //read and fill the dataBase from the file
    while(!inData.eof()){
        getline(inData,sLine);
        if(!sLine.empty()){
            stringstream ss; //converts string to an input stream
            ss<<sLine;
            ss>>username;
            ss.get();
            ss>>password;
            userData* u = new userData(password);
            p->getDB()->insert({username,u});
        }
    }

    /*All input will be a string, then will be casted/changed to the proper datatype after validation
    Validation will take into account length, range, and type depending on the input
    For example, if the input requires a letter, use the isletter function
    Length of ALL input should only be 1
    If the program expects a char and gets a string of chars, it would loop the input statement until it gets ONE character.*/

    login(p);
    return 0;
}