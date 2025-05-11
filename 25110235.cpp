#include <iostream>
using namespace std;

class StoreUser
{
private:
    string name;
    string identifier;
    string email;
    string password;

public:
    StoreUser();                                                                      // default constructor
    StoreUser(string name_1, string identifier_1, string email_1, string password_1); // parametarised constructor
    // setter functions
    void setName(string name_1);
    void setIdentifier(string identifier_1);
    void setEmail(string email_1);
    void setPassword(string password_1);
    // getter functions
    string getName();
    string getIdentifier();
    string getEmail();
    string getPassword();
    // friend functions
    friend ostream &operator<<(ostream &out, const StoreUser &a);
    friend istream &operator>>(istream &in, StoreUser &b);
};

// Class 2

class Authentication
{
private:
    StoreUser *size;
    StoreUser *deleted_arr;
    int current = 1; // initialised with 1 to account for admin's account
    int total_deleted = 0;
    int deleted_size = 20; // starting capacity as given in the question
    string admin_identifier = "usama";
    string admin_pw = "12345";
    int total = 20; // starting capacity as given in the question
    StoreUser *CurrUser;
    StoreUser *loggedInUser = NULL;

public:
    StoreUser *getUserByIdentifier(string id)
    {
        for (int i = 0; i < current; i++)
        {
            if (size[i].getIdentifier() == id)
            {
                return &size[i];
            }
        }
        return NULL;
    }
    StoreUser *getUserByPass(string pw)
    {
        for (int i = 0; i < current; i++)
        {
            if (size[i].getPassword() == pw)
            {
                return &size[i];
            }
        }
        return NULL;
    }
    Authentication();
    Authentication(StoreUser *);
    StoreUser *morememory(int, StoreUser *);
    StoreUser *morememory(int, StoreUser *, int);
    StoreUser *deleter(StoreUser *, string);

    // utility functions
    bool checkName(string &name);
    bool checkEmail(string &email);
    bool checkPassword(string &password);
    void changeEmail();
    void changePassword();
    int adminMenu();
    int userMenu();
    void addUser(StoreUser *size, int &current, int &total);
    void deleteUser(StoreUser *size, int &current, const string &admin_identifier);
    void displayUsers(StoreUser *size, int &current, StoreUser *deleted_arr, int &total_deleted);
    string encrypt_pass(string pw);
    string decrypt_pass(string pw);
    void login();
    void signup();
    // friend functions
    friend ostream &operator<<(ostream &out, const Authentication &a);
    friend istream &operator>>(istream &in, Authentication &b);
};

// Class 1 definitions

StoreUser::StoreUser()
{
    name = "";
    identifier = "";
    email = "";
    password = "";
}
StoreUser::StoreUser(string name_1, string identifier_1, string email_1, string password_1)
{
    name = name_1;
    identifier = identifier_1;
    email = email_1;
    password = password_1;
}
void StoreUser::setName(string name_1)
{
    name = name_1;
}
void StoreUser::setIdentifier(string identifier_1)
{
    identifier = identifier_1;
}
void StoreUser::setEmail(string email_1)
{
    email = email_1;
}
void StoreUser::setPassword(string password_1)
{
    password = password_1;
}
string StoreUser::getName()
{
    return name;
}
string StoreUser::getIdentifier()
{
    return identifier;
}
string StoreUser::getEmail()
{
    return email;
}
string StoreUser::getPassword()
{
    return password;
}
ostream &operator<<(ostream &out, const StoreUser &a)
{
    out << a.name;
    return out;
}
istream &operator>>(istream &in, StoreUser &b)
{
    in >> b.name;
    return in;
}

// Class 2 definitions

Authentication::Authentication(StoreUser *arr1)
{
    size = arr1;
    deleted_arr = new StoreUser[20];
}
Authentication::Authentication()
{
    StoreUser *deleted_arr;
    int total_deleted = 0;
    int deleted_size = 20;
    size = NULL;
    current = 1;
    total = 20;
    loggedInUser = NULL;
}
bool Authentication::checkName(string &name)
{
    bool letters_only = false;
    for (int i = 0; i < name.size(); i++)
    {
        char n = name[i];
        if (n >= 'A' && n <= 'Z' || n >= 'a' && n <= 'z')
        {
            letters_only = true;
        }
        else
        {
            letters_only = false;
        }
    }
    if (letters_only)
        return true;
    else
        return false;
}
bool Authentication::checkEmail(string &email)
{

    bool has_at = false;
    bool has_dot = false;
    bool has_char = false;
    int at_times = 0, dot_times = 0;
    int at_pos = -1, dot_before_at_pos = -1, dot_after_at_pos = -1;

    for (int i = 0; i < email.size(); i++)
    {
        char c = email[i];
        if (c == '@')
        {
            has_at = true;
            at_times += 1;
            at_pos = i;
        }
        else if (c == '.')
        {
            if (has_at = true)
            {
                has_dot = true;
                dot_times += 1;
                dot_after_at_pos = i;
            }
            else if (has_at = false)
            {
                has_dot = true;
                dot_times += i;
                dot_before_at_pos = -1;
            }
        }
        else if (c == '!' || c == '-' || c == '+' || c == '&' || c == '$' || c == '%' || c == '^' || c == '*')
        {
            has_char = true;
        }
    }
    if (!has_char && has_at && has_dot && at_times == 1 && dot_times >= 1 && at_pos != 0 && dot_after_at_pos != email.size() - 1 && dot_before_at_pos != 0 && dot_after_at_pos > 1 + at_pos)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Authentication::checkPassword(string &password)
{

    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;
    bool size = false;
    bool strong = false;
    bool weak = false;
    bool medium = false;
    if (password.size() > 8)
    {
        size = true;
    }
    for (int i = 0; i < password.size(); i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            has_uppercase = true;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            has_digit = true;
        }
        else if (password[i] >= ' ' && password[i] <= '/' || password[i] >= ':' && password[i] <= '@')
        {
            has_special = true;
        }
    }
    if (has_uppercase == false && has_digit == false && has_special == false && size == false)
    {
        weak = true;
        cout << "weak";
        return false;
    }
    else if (has_uppercase != true || has_digit != true || has_special != true || size != true)
    {
        medium = true;
        cout << "medium";
        return false;
    }
    else if (has_uppercase == true && has_digit == true && has_special == true && size == true)
    {
        strong = true;
        cout << "strong" << endl;
        return true;
    }
}
void Authentication::changeEmail()
{
    cout << "Enter new email: ";
    string newemail;
    cin >> newemail;

    while (true)
    {
        if (!checkEmail(newemail))
        {
            cout << "Invalid Email!\n Please Try Again:\n";
            cin >> newemail;
        }
        else
        {
            cout << "Email is changed!\nYour new email is: " << newemail << endl;
            break;
        }
    }

    loggedInUser->setEmail(newemail);
}
void Authentication::changePassword()
{
    cout << "Enter new password";
    string newpassword;
    fflush(stdin);
    cin >> newpassword;
    while (true)
    {
        cout << "Password is ";
        if (!checkPassword(newpassword))
        {
            cout << endl
                 << "Enter password again: \n";
            cin >> newpassword;
        }
        else
        {
            break;
        }
    }
    loggedInUser->setPassword(newpassword);
}
int Authentication::adminMenu()
{
    int option;
    cout << "Enter 1 to change email\nEnter 2 to change password\nEnter 3 to log out\nEnter 4 to add a user\nEnter 5 to delete a user\nEnter 6 to change password of a user\nEnter 7 to change email of user\nEnter 8 to display records" << endl;
    cin >> option;
    return option;
}
int Authentication::userMenu()
{
    int option;
    cout << "Enter 1 to change email\nEnter 2 to change password\nEnter 3 to log out\nEnter 4 to Un-Subscribe\n";
    cin >> option;
    return option;
}
void Authentication::addUser(StoreUser *size, int &current, int &total)
{
    cout << "Adding...." << endl;
    string name, id, email, pw, confirmpw;
    cout << "Enter name: \n";
    // getline(cin, name);
    cin >> name;
    cout << "Enter identifier: \n";
    // getline(cin, id);
    cin >> id;
    if (getUserByIdentifier(id) != NULL)
    {
        cout << "Error: User already exists with this identifier." << endl;
        return;
    }
    cout << "Enter email: ";
    // getline(cin, email);
    cin >> email;
    while (true)
    {
        if (!checkEmail(email))
        {
            cout << "Invalid Email!!";
            cout << endl
                 << "Try Again: ";
            cin >> email;
        }
        else
        {
            break;
        }
    }

    cout << "Enter password: ";
    // getline(cin, pw);
    cin >> pw;
    while (true)
    {
        cout << "Password is ";
        if (!checkPassword(pw))
        {
            cout << endl
                 << "Enter password again: ";
            cin >> pw;
        }
        else
        {
            break;
        }
    }

    cout << "Confirm password: ";
    cin >> confirmpw;
    // getline(cin, confirmpw);
    while (true)
    {
        if (pw != confirmpw)
        {
            cout << "Error: Passwords do not match." << endl;
            cout << "Try Again: ";
            cin >> confirmpw;
        }
        else
        {
            break;
        }
    }
    if (current > 0 && (current - 1) == total)
    {
        size = morememory(current, size);
    }

    StoreUser newUser(name, id, email, pw);
    size[current] = newUser;
    cout << endl;
    current++;
    cout << "User Added" << endl;
}
void Authentication::deleteUser(StoreUser *size, int &current, const string &admin_identifier)
{
    cout << "Deleting...." << endl;
    cout << "Enter identifier: \n";
    string id2;
    fflush(stdin);
    getline(cin, id2);
    if (id2 == admin_identifier)
    {
        cout << "Admin can not be deleted!" << endl;
    }
    else
    {
        StoreUser *user2 = getUserByIdentifier(id2);
        if (user2 == NULL)
        {
            cout << "Error: User not found." << endl;
        }
        else
        {
            size = deleter(size, id2);
            current--;
            cout << "User Deleted" << endl;
        }
    }
}
void Authentication::displayUsers(StoreUser *size, int &current, StoreUser *deleted_arr, int &total_deleted)
{
    cout << "Current Users: " << endl;
    cout << "------------------------------------------------------" << endl;
    for (int i = 0; i < current; i++)
    {

        cout << "Name:     " << size[i].getName() << endl;
        cout << "Id:       " << size[i].getIdentifier() << endl;
        cout << "Password: " << size[i].getPassword() << endl;
        cout << "Email:    " << size[i].getEmail() << endl;
        cout << "------------------------------------------------------" << endl;
    }
    cout << "Deleted Users: " << endl;
    cout << "------------------------------------------------------" << endl;
    for (int i = 0; i < total_deleted; i++)
    {

        cout << "Name:     " << deleted_arr[i].getName() << endl;
        cout << "Id:       " << deleted_arr[i].getIdentifier() << endl;
        cout << "Password: " << deleted_arr[i].getPassword() << endl;
        cout << "Email:    " << deleted_arr[i].getEmail() << endl;
        cout << "------------------------------------------------------" << endl;
    }
}
string Authentication::encrypt_pass(string pw)
{
    string encrypt_password = "";
    for (int i = 0; i < pw.size(); i++)
    {
        char e = pw[i];
        e = e + 2;
        encrypt_password = encrypt_password + e;
    }
    return encrypt_password;
}
string Authentication::decrypt_pass(string pw)
{
    string decrypt_password = "";
    for (int i = 0; i < pw.size(); i++)
    {
        char d = pw[i];
        d = d + 2;
        decrypt_password = decrypt_password + d;
    }
    return decrypt_password;
}
void Authentication::login()
{
    fflush(stdin);
    string id, pw;
    cout << "Enter identifier: \n";
    getline(cin, id);
    StoreUser *user = getUserByIdentifier(id);
    if (user == NULL)
    {
        cout << "Error: User not found." << endl;
        return;
    }
    cout << "Enter password: \n";
    getline(cin, pw);
    int count = 3;
    while (true)
    {
        if (count <= 1)
        {
            cout << "Try logging in again!\n";
            return;
        }
        if (user->getPassword() != pw)
        {
            count--;
            cout << "Error: Incorrect password." << endl;
            cout << "Try Again!. You have " << count << " attempts left: \n";
            fflush(stdin);
            getline(cin, pw);
        }
        else
        {
            break;
        }
    }
    loggedInUser = user;
    int option;
    cout << "Welcome " << loggedInUser->getIdentifier() << "! You're now logged in." << endl;
    while (true)
    {
        if (id == admin_identifier && pw == admin_pw)
        {
            int option = adminMenu();
            if (option == 1)
            {
                changeEmail();
            }
            else if (option == 2)
            {
                cout << "Your old password is " << pw << endl;
                changePassword();
            }
            else if (option == 3)
            {
                cout << "logging out" << endl;
                break;
            }
            else if (option == 4)
            {
                addUser(size, current, total);
            }
            else if (option == 5)
            {
                deleteUser(size, current, admin_identifier);
            }
            else if (option == 6)
            {
                cout << "Changing Password...." << endl;
                // cout << " Enter password: \n";
                // string pw2;
                // fflush(stdin);
                // getline(cin, pw2);
                cout << "Enter identifier: \n";
                string id2;
                fflush(stdin);
                getline(cin, id2);
                StoreUser *user2 = getUserByIdentifier(id2);
                if (user2 == NULL)
                {
                    cout << "Error: User not found." << endl;
                }
                else
                {
                    cout << "The old(encrypted) password for the user is "<< getUserByPass(pw) <<endl;
                    cout << "Enter new password\n";
                    string newpassword;
                    fflush(stdin);
                    cin >> newpassword;
                    while (true)
                    {
                        cout << "Password is ";
                        if (!checkPassword(newpassword))
                        {
                            cout << endl
                                 << "Enter password again: ";
                            cin >> newpassword;
                        }
                        else
                        {
                            break;
                        }
                    }
                    user2->setPassword(newpassword);
                    cout << "Password changed...\n";
                }
            }
            else if (option == 7)
            {
                cout << "Changing email...." << endl;
                // cout << "Enter new email: ";
                // string newemail;
                // fflush(stdin);
                // cin >> newemail;
                cout << "Enter identifier: \n";
                string id2;
                fflush(stdin);
                getline(cin, id2);
                StoreUser *user2 = getUserByIdentifier(id2);
                if (user2 == NULL)
                {
                    cout << "Error: User not found." << endl;
                }
                else
                {
                    cout << "Enter new email: ";
                    string newemail;
                    cin >> newemail;

                    while (true)
                    {
                        if (!checkEmail(newemail))
                        {
                            cout << "Invalid Email!\n Please Try Again:\n";
                            cin >> newemail;
                        }
                        else
                        {
                            cout << "Email is changed!\nYour new email is: " << newemail << endl;
                            break;
                        }
                    }

                    user2->setEmail(newemail);
                    cout << "Email changed...\n";
                }
            }
            else if (option == 8)
            {
                displayUsers(size, current, deleted_arr, total_deleted);
            }
        }
        else
        {
            int option = userMenu();
            if (option == 1)
            {
                changeEmail();
            }
            else if (option == 2)
            {
                decrypt_pass(pw);
                cout << "Your old password is " << pw << endl;
                changePassword();
            }
            else if (option == 3)
            {
                cout << "logging out" << endl;
                break;
            }
            else if (option == 4)
            {
                cout << "Unsubscribing" << endl;
                size = deleter(size, id);
                current--;
                break;
                //To Delete user
            }
        }
    }
}
void Authentication::signup()
{
    string name, id, email, pw, confirmpw;
    cout << "Enter name: \n";
    // getline(cin, name);
    cin >> name;
    while (true)
    {
        if (!checkName(name))
        {
            cout << "Please enter a valid name\n";
            cin >> name;
        }
        else
            break;
    }
    cout << "Enter identifier: \n";
    // getline(cin, id);
    cin >> id;
    if (getUserByIdentifier(id) != NULL)
    {
        cout << "Error: This identifier is already taken by another user.\n";
        return;
    }
    cout << "Enter email:\n";
    // getline(cin, email);
    cin >> email;
    while (true)
    {
        if (!checkEmail(email))
        {
            cout << "Invalid Email!\n";
            cout << "Try Again: ";
            cin >> email;
        }
        else
        {
            break;
        }
    }

    cout << "Enter password:\n";
    // getline(cin, pw);
    cin >> pw;
    while (true)
    {
        cout << "Password is ";
        if (!checkPassword(pw))
        {
            cout << endl
                 << "Enter password again: ";
            cin >> pw;
        }
        else
        {
            break;
        }
    }

    cout << "Confirm password:\n";
    cin >> confirmpw;
    // getline(cin, confirmpw);
    while (true)
    {
        if (pw != confirmpw)
        {
            cout << "Error: Passwords do not match." << endl;
            cout << "Try Again: ";
            cin >> confirmpw;
        }
        else
        {
            break;
        }
    }
    encrypt_pass(pw);
    if (current > 0 && (current - 1) == total)
    {
        size = morememory(current, size);
    }

    StoreUser newUser(name, id, email, pw);
    size[current] = newUser;
    cout << endl;
    current++;
    cout << "Your signup was successful. You may now login." << endl;
    login();
}
StoreUser *Authentication::morememory(int current, StoreUser *arr1)
{
    StoreUser *newArr = new StoreUser[2 * total];
    total = 2 * total;
    for (int i = 0; i < current; i++)
    {
        newArr[i] = arr1[i];
    }
    delete[] arr1;
    arr1 = NULL;
    return newArr;
}
StoreUser *Authentication::morememory(int current, StoreUser *arr1, int total)
{
    StoreUser *newArr = new StoreUser[2 * total];
    total = 2 * total;
    for (int i = 0; i < current; i++)
    {
        newArr[i] = arr1[i];
    }
    delete[] arr1;
    arr1 = NULL;
    return newArr;
}
StoreUser *Authentication::deleter(StoreUser *arr1, string id)
{
    if (total_deleted > 0 && (total_deleted - 1) == deleted_size)
    {
        deleted_arr = morememory(total_deleted, deleted_arr, deleted_size);
    }
    for (int i = 0; i < current; i++)
    {
        if (arr1[i].getIdentifier() == id)
        {
            deleted_arr[total_deleted] = arr1[i];
            for (int j = i; j < current - 1; j++)
            {
                arr1[j] = arr1[j + 1];
            }
            break;
        }
    }
    total_deleted++;
    return arr1;
}
ostream &operator<<(ostream &out, const Authentication &a)
{
    out << a.current;
    return out;
}
istream &operator>>(istream &in, Authentication &b)
{
    in >> b.current;
    return in;
}

int main()
{
    // making an object of the first class and saving admin's info
    StoreUser *AllUser = new StoreUser[20];
    AllUser[0].setName("Usama");
    AllUser[0].setEmail("habibusama999@gmail.com");
    AllUser[0].setIdentifier("usama");
    AllUser[0].setPassword("12345");
    Authentication ap1(AllUser);
    int option;
    do
    {
        cout << "enter 1 to log in " << endl
             << "enter 2 sign up" << endl
             << "enter 3 to end this program" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            ap1.login();
            break;
        case 2:
            ap1.signup();
            break;
        case 3:
            exit(3);
        default:
            cout << "Enter a valid number" << endl;
            break;
        }

    } while (true);

    return 0;
}