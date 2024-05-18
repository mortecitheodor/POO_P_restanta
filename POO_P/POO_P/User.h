#pragma once
using namespace System;

public ref class User {
public:
    int id;
    String^ name;
    String^ email;
    String^ password;
    User() : id(0), name(nullptr), email(nullptr), password(nullptr) {
    }
};
