#include <iostream>
#include <string>
#include <vector>
#define ID long long
using namespace std;
ID userId = 1;
ID messageId = 1;
class User {
public:
	ID id;
	string name;
	string surname;
	string username;
	string password;
	int age;
	vector<User*>friends;
};

class Message {
public:
	ID id;
	ID senderId;
	ID receiverId;
	time_t t;
	string text;
	

};
class UserDAO {
	vector<User*> users;
public:
	void save(User &u) {
		if (isUnique(u.username)) {
			User* user = new User();
			user->id = userId;
			userId++;
			user->age = u.age;
			user->name = u.name;
			user->surname = u.surname;
			user->username = u.username;
			user->password = u.password;
			user->friends = u.friends;
			users.push_back(user);
		}
		else {
			return;
		}
	}
	void remove(ID id) {
		long long int counter = 0;
		for (User* user:users)
		{
			if (user->id == id) {
				users.erase(users.begin() + counter);
				return;
			}
			counter++;
		}
	}
	void update(User &u) {
		long long int counter = 0;
		for (User* user : users) {
			if (user->id = u.id) {
				if (u.password != "") {
					//user->username = u.username;
					user->age = u.age;
					user->name = u.name;
					user->surname = u.surname;
					user->password = u.password;
					user->friends = u.friends;
					return;
				}
			}
		}
	}
	 User* findByUsername(string username) {
		for (User* user : users) {
			if (user->username == username) {
				return user;
			}
		}
		return nullptr;
	}
	 User* findById(ID id) {
		for (User* user : users) {
			if (user->id == id) {
				return user;
			}
		}
		return nullptr;
	}
	vector<User*> getUsersByName(string name) {
		vector<User*>vec;
		for (User* user : users) {
			if (user->name == name) {
				vec.push_back(user);
			}
		}
		return vec;
	}
private:
	bool isUnique(string username) {
		for (User* user : users) {
			if (user->username == username) {
				return false;
			}
		}
		return true;
	}

};
User *user;
class MessageDAO {

	vector<Message*>messages;
	public:
		void save(Message &m){
			Message *message=new Message();
			message->id=messageId;
			message->senderId=m.senderId;
			message->receiverId=m.receiverId;
			message->t=m.t;
			message->text=m.text;
			messageId++;
			messages.push_back(message);
			
		}
		
		
};
class AuthorizationController {
	UserDAO *dao;
	
public:
	void signUp() {
		string username, password, name, surname;
		int age;
		cout << "Username Daxil et" << endl;
		cin >> username;
		cout << "Password daxil et" << endl;
		cin >> password;
		cout << "Adini Daxil et" << endl;
		cin >> name;
		cout << "Soyadini daxil et" << endl;
		cin >> surname;
		cout << "Yashini Daxil et" << endl;
		cin >> age;
		User user;
		user.age = age;
		user.name = name;
		user.surname = surname;
		user.password = password;
		user.username = username;
		dao->save(user);
		
	}
	void signIn() {
		user = nullptr;
		string username, password;
		cout << "Username Daxil et" << endl;
		cin >> username;
		cout << "Password daxil et" << endl;
		cin >> password;
		User* u = dao->findByUsername(username);
		if (u == nullptr) {
			cout << "Wrong username or password" << endl;
			return;
		}
		if (u->password == password) {
			user = u;
		}

	}
	void signOut() {
		user = nullptr;
	}
	void setUserDAO(UserDAO *dao) {
		this->dao = dao;
	}
	
};

class FriendController{
	UserDAO *dao;
public:
	void add() {
		ID id;
		cout << "Dost olmaq istediyiniz userin id-ini daxil edin" << endl;
		cin >> id;
		if (id == user->id) {
			return;
		}
		User* _friend = dao->findById(id);
		if (_friend == nullptr) {
			return;
		}
		user->friends.push_back(_friend);
		_friend->friends.push_back(user);
		dao->update(*user);

	}
	
	void listAllFriends(){
		for(User* friendItem : user->friends){
			cout<<friendItem->name << " " << friendItem->surname << " " << friendItem->username << " " << friendItem->age<<" yas"<<endl;
		}
	}
	
	void search() {
		string name;
		cout << "Axtarish etmek istediyiniz adi yazin" << endl;
		cin >> name;
		vector<User*>search;
		search=dao->getUsersByName(name);
		if (search.size()) {
			for (User* searchItem : search) {
				cout <<"ID : " <<searchItem->id << " " << searchItem->name << " " << searchItem->surname << endl;
			}
		}
		else {
			cout << "Netice tapilmadi !!!" << endl;
		}
	}
	void removeFriend() {
		ID id;
		cout << "Silmek istediyiniz dostun ID-ini daxil edin" << endl;
		cin >> id;
		if (id == user->id) {
			return;
		}
		User* _friend = dao->findById(id);
		if (_friend == nullptr) {
			return;
		}
		for (User* friendItem : user->friends) {
			long long int counter = 0;
			if (friendItem == _friend) {
				user->friends.erase(user->friends.begin() + counter);
				return;
			}
			counter++;
		}
		
	}
	void setUserDAO(UserDAO *dao) {
		this->dao = dao;
	}
};



int main() {
	UserDAO  *dao = new UserDAO();
	AuthorizationController a1;
	a1.setUserDAO(dao);
	start:
	if(user==nullptr) {
		auth:
		system("CLS");
		cout<<"**** Qeydiyyat/Girish ****" << endl;
		cout<<"Qeydiyyatdan kechmek uchun 1" << endl;
		cout<<"Girish etmek uchun 2-ye basin" <<endl;
		char auth;
		cin>>auth;
		switch(auth){
			case '1':
				a1.signUp();
				goto auth;
				break;
			case '2':
				a1.signIn();
				goto start;
				break;
			default:
				cout<< "SECIM YANLISHDIR" << endl;
				goto auth;
		}
	}
	else {
		system("cls");
		main:
		system("cls");
		cout << "**** Cito-ya xosh geldiniz ****" << endl;
		cout << "Salam " << " " <<  user->name << "!" << endl;
		cout << "Ashagidaki menyudan bir bolmeni sechin." << endl;
		cout << "1 - Bashqa emeliyyatlar" << endl;
		cout << "2 - Log Out" <<endl;
		
		char menu;
		cin>> menu;
	
			
			if(menu=='2'){
				a1.signOut();
				goto start;
			}
			else if (menu == '1'){
						
					submenu:
					FriendController friendcontroller;
					friendcontroller.setUserDAO(dao);
					system("cls");
					cout << "1 - Profil melumatlarini gor" << endl;
					cout << "2 - Melumatlarini deyishdir" << endl;
					cout << "3 - Mesajlarina bax" << endl;
					cout << "4 - Profil axtar" << endl;
					cout << "5 - Dost elave et" << endl;
					cout << "6 - Butun dostlarini gor" << endl;
					cout << "7 - Mesaj yaz" << endl;
					cout << "8 - Geri Qayit" <<endl;
					char submenu;
					cin>>submenu;
				
					
			
					switch(submenu){
						case '1':
							system("cls");
							cout << "Melumatlariniz" << endl;
							cout << "Ad : " << user->name << endl;
							cout << "Soyad : " << user->surname << endl;
							cout << "Username :" << user->username << endl;
							cout << "Age :" << user->age << endl;
							cout << "Password : " << user->password <<endl;
							backpoint1:
							cout<< "Geri qayitmaq uchun 1 daxil edin." <<endl;
							char back;
							cin>>back;
							if(back=='1'){
								goto submenu;
							}
							else {
								goto backpoint1;
							}
							break;
						case '2': {
							system("cls");
							string name;
							string surname;
							string password;
							int age;
							cout<<"Ad" <<endl;
							cin>>name;
							cout<<"Soyad" <<endl;
							cin>>surname;
							cout<<"Parol"<<endl;
							cin>>password;
							cout<<"Yas"<<endl;
							cin>>age;
							User u;
							u.id=user->id;
							u.name=name;
							u.surname=surname;
							u.password=password;
							u.age=age;
							dao->update(u);
				
							user=nullptr;
							goto auth;
							break;
						}
							
							
						case '3':
							system("cls");
						
							break;
						
						case '4':
							system("cls");
							friendcontroller.search();
							backpoint2:
							cout<< "Geri qayitmaq uchun 1 daxil edin." <<endl;
							char friendback;
							cin>>friendback;
							if(friendback=='1'){
								goto submenu;
							}
							else {
								goto backpoint2;
							}
							break;
			
						case '5':
							system("cls");
							friendcontroller.add();
							backpoint3:
							cout<< "Geri qayitmaq uchun 1 daxil edin." <<endl;
							char friendaddback;
							cin>>friendaddback;
							if(friendaddback=='1'){
								goto submenu;
							}
							else {
								goto backpoint3;
							}
							break;
						case '6':
							system("cls");
							friendcontroller.listAllFriends();
							backpoint4:
							cout<< "Geri qayitmaq uchun 1 daxil edin." <<endl;
							char listback;
							cin>>listback;
							if(listback=='1'){
								goto submenu;
							}
							else {
								goto backpoint4;
							}
							break;
						case '7':
							
							break;
						case '8':
							goto main;
							break;
						default:
							cout << "YANLISH SECIM" <<endl;
					
				
				}
				
			}
			else{
				goto main;
			}
		
	}
	return 0;
}

 
