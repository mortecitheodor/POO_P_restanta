using namespace System;

public ref class User {
public:
	int id;
	String^ name;
	String^ email;
	String^ password;

	User() {
		id = 0;
		name = "1";
		email = "2";
		password = "3";
	}

};