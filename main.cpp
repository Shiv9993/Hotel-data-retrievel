#include<iostream>
#include<string>
#include<iomanip> 
using namespace std;

// store information about a hotel room
struct roominfo{
    int roomnumber;
    string guestname;
    string checkindate;
    string checkoutdate;
    double roomrate; 
};

// Node structure
struct treenode{
    roominfo data;
    treenode* left;
    treenode* right;
    treenode(roominfo info):data(info),left(nullptr),right(nullptr){}
};

// binary search tree class
class hotelTree{
private:
    treenode* root;

    // insert a new node
    treenode* insert(treenode* node,roominfo info){
        if(node==nullptr){
            return new treenode(info);
        }
        if(info.roomnumber<node->data.roomnumber){
            node->left=insert(node->left,info);
        }else if(info.roomnumber>node->data.roomnumber){
            node->right=insert(node->right,info);
        }
        return node;
    }

    // search for a room
    treenode* search(treenode* node,int roomnumber){
        if(node==nullptr || node->data.roomnumber==roomnumber){
            return node;
        }
        if(roomnumber<node->data.roomnumber){
            return search(node->left,roomnumber);
        }else{
            return search(node->right,roomnumber);
        }
    }

    // update room information
    treenode* updateroom(treenode* node,int roomnumber,roominfo newinfo){
        if(node==nullptr){
            return nullptr;
        }
        if(roomnumber<node->data.roomnumber){
            node->left=updateroom(node->left,roomnumber,newinfo);
        }else if(roomnumber>node->data.roomnumber){
            node->right=updateroom(node->right,roomnumber,newinfo);
        }else{
            node->data=newinfo;
        }
        return node;
    }

    // print the tree in-order
    void inorderprint(treenode* node){
        if(node!=nullptr){
            inorderprint(node->left);
            cout<<"room number: "<<node->data.roomnumber
                 <<", guest name: "<<node->data.guestname
                 <<", check-in date: "<<node->data.checkindate
                 <<", check-out date: "<<node->data.checkoutdate
                 <<", room rate: rs."<<fixed<<setprecision(2)<<node->data.roomrate
                 <<endl;
            inorderprint(node->right);
        }
    }

    // display rooms by date range
    void printroomsbydaterange(treenode* node,string startdate,string enddate){
        if(node!=nullptr){
            printroomsbydaterange(node->left,startdate,enddate);
            if(node->data.checkindate<=enddate && node->data.checkoutdate>=startdate){
                cout<<"room number: "<<node->data.roomnumber
                     <<", guest name: "<<node->data.guestname
                     <<", check-in date: "<<node->data.checkindate
                     <<", check-out date: "<<node->data.checkoutdate
                     <<", room rate: rs."<<fixed<<setprecision(2)<<node->data.roomrate
                     <<endl;
            }
            printroomsbydaterange(node->right,startdate,enddate);
        }
    }

public:
    hotelTree():root(nullptr){}

    // insert a new room information
    void insertroom(roominfo info){
        root=insert(root, info);
    }

    // search for a room
    void searchroom(int roomnumber){
        treenode* result=search(root,roomnumber);
        if(result!=nullptr){
            cout<<"room number: "<<result->data.roomnumber
                 <<", guest name: "<<result->data.guestname
                 <<", check-in date: "<<result->data.checkindate
                 <<", check-out date: "<<result->data.checkoutdate
                 <<", room rate: rs."<<fixed<<setprecision(2)<<result->data.roomrate
                 <<endl;
        }else{
            cout<<"room number "<<roomnumber<<" not found."<<endl;
        }
    }

    // update room information
    void updateroominfo(int roomnumber,roominfo newinfo){
        root=updateroom(root,roomnumber,newinfo);
    }

    // print all rooms
    void printallrooms(){
        inorderprint(root);
    }

    // display room details based on a specific date range
    void printroomsbydaterange(string startdate, string enddate){
        cout<<"rooms available from "<<startdate<<" to "<<enddate<<":"<<endl;
        printroomsbydaterange(root,startdate,enddate);
    }
};

int main(){
    hotelTree hotel;

    // Insert initial room information
    hotel.insertroom({13,"Shivkumar","2024-08-01","2024-08-07",13});
    hotel.insertroom({205,"Abhishek","2024-08-05","2024-08-10",150});
    hotel.insertroom({303,"Satyam","2024-08-10","2024-08-15",180});
    hotel.insertroom({150,"Rohit","2024-08-01","2024-08-03",100});
    hotel.insertroom({404,"Himanshu","2024-08-15","2024-08-20",200});

    int choice;

    do{
        cout<<"\nhotel management system menu:\n";
        cout<<"1.insert room information\n";
        cout<<"2.search room\n";
        cout<<"3.update room information\n";
        cout<<"4.print all rooms\n";
        cout<<"5.print rooms by date range\n";
        cout<<"6.exit\n";
        cout<<"enter your choice: ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:{
                roominfo info;
                cout<<"enter room number: ";
                cin>>info.roomnumber;
                cin.ignore();
                cout<<"enter guest name: ";
                getline(cin,info.guestname);
                cout<<"enter check-in date (yyyy-mm-dd): ";
                getline(cin,info.checkindate);
                cout<<"enter check-out date (yyyy-mm-dd): ";
                getline(cin,info.checkoutdate);
                cout<<"enter room rate (in rs.): ";
                cin>>info.roomrate;
                cin.ignore();
                hotel.insertroom(info);
                break;
            }
            case 2:{
                int roomnumber;
                cout<<"enter room number to search: ";
                cin>>roomnumber;
                hotel.searchroom(roomnumber);
                break;
            }
            case 3:{
                int roomnumber;
                roominfo newinfo;
                cout<<"enter room number to update: ";
                cin>>roomnumber;
                cin.ignore();
                cout<<"enter new guest name: ";
                getline(cin,newinfo.guestname);
                cout<<"enter new check-in date (yyyy-mm-dd): ";
                getline(cin,newinfo.checkindate);
                cout<<"enter new check-out date (yyyy-mm-dd): ";
                getline(cin,newinfo.checkoutdate);
                cout<<"enter new room rate (in rs.): ";
                cin>>newinfo.roomrate;
                cin.ignore();
                newinfo.roomnumber=roomnumber;
                hotel.updateroominfo(roomnumber,newinfo);
                break;
            }
            case 4:{
                hotel.printallrooms();
                break;
            }
            case 5:{
                string startdate,enddate;
                cout<<"enter start date (yyyy-mm-dd): ";
                getline(cin,startdate);
                cout<<"enter end date (yyyy-mm-dd): ";
                getline(cin,enddate);
                hotel.printroomsbydaterange(startdate,enddate);
                break;
            }
            case 6:{
                cout<<"exiting the system."<<endl;
                break;
            }
            default:
                cout<<"invalid choice. please try again."<<endl;
                break;
        }
    }while(choice!=6);

    return 0;
}
