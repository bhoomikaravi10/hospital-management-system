#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

// ENUM
enum Gender
{
    MALE,
    FEMALE,
    OTHER
};

// BASE CLASS
class Person
{
protected:
    int id;
    char name[50];
    int age;
    char phone[15];

public:

    // DEFAULT CONSTRUCTOR
    Person()
    {
        id = 0;
        strcpy(name, "");
        age = 0;
        strcpy(phone, "");
    }

    // PARAMETERIZED CONSTRUCTOR
    Person(int i, const char n[], int a, const char p[])
    {
        id = i;
        strcpy(name, n);
        age = a;
        strcpy(phone, p);
    }

    void displayPerson()
    {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nPhone: " << phone;
    }

    int getId()
    {
        return id;
    }

    const char* getName()
    {
        return name;
    }

    void updatePerson(const char n[], int a, const char p[])
    {
        strcpy(name, n);
        age = a;
        strcpy(phone, p);
    }
};

// PATIENT CLASS
class Patient : public Person
{
private:
    char disease[50];
    Gender gender;

public:

    Patient() : Person()
    {
        strcpy(disease, "");
        gender = MALE;
    }

    Patient(int i, const char n[], int a,
            const char p[], const char d[], Gender g)
        : Person(i, n, a, p)
    {
        strcpy(disease, d);
        gender = g;
    }

    void displayPatient()
    {
        cout << "\n--- PATIENT DETAILS ---";

        displayPerson();

        cout << "\nDisease: " << disease;

        cout << "\nGender: ";

        switch (gender)
        {
            case MALE:
                cout << "Male";
                break;

            case FEMALE:
                cout << "Female";
                break;

            case OTHER:
                cout << "Other";
                break;
        }

        cout << "\n";
    }

    void updateDisease(const char d[])
    {
        strcpy(disease, d);
    }

    void updatePatient(const char n[], int a,
                       const char p[], const char d[])
    {
        updatePerson(n, a, p);
        strcpy(disease, d);
    }
};

// DOCTOR CLASS
class Doctor : public Person
{
private:
    char specialization[50];

public:

    Doctor() : Person()
    {
        strcpy(specialization, "");
    }

    Doctor(int i, const char n[], int a,
           const char p[], const char s[])
        : Person(i, n, a, p)
    {
        strcpy(specialization, s);
    }

    void displayDoctor()
    {
        cout << "\n--- DOCTOR DETAILS ---";

        displayPerson();

        cout << "\nSpecialization: "
             << specialization << "\n";
    }

    void updateDoctor(const char n[], int a,
                      const char p[], const char s[])
    {
        updatePerson(n, a, p);
        strcpy(specialization, s);
    }
};

// STRUCTURE
struct Appointment
{
    int patientId;
    int doctorId;
    char date[20];
    char time[20];
};

// HOSPITAL CLASS
class Hospital
{
private:

    Patient patients[50];
    Doctor doctors[20];
    Appointment appointments[50];

    int patientCount;
    int doctorCount;
    int appointmentCount;

    // GENERATE NEXT PATIENT ID
    int nextPatientId()
    {
        int maxId = 0;

        for (int i = 0; i < patientCount; i++)
        {
            if (patients[i].getId() > maxId)
                maxId = patients[i].getId();
        }

        return maxId + 1;
    }

    // GENERATE NEXT DOCTOR ID
    int nextDoctorId()
    {
        int maxId = 0;

        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getId() > maxId)
                maxId = doctors[i].getId();
        }

        return maxId + 1;
    }

    // FUNCTION OVERLOADING
    Patient* searchPatient(int id)
    {
        for (int i = 0; i < patientCount; i++)
        {
            if (patients[i].getId() == id)
                return &patients[i];
        }

        return nullptr;
    }

    Patient* searchPatient(const char name[])
    {
        for (int i = 0; i < patientCount; i++)
        {
            if (strcmp(patients[i].getName(), name) == 0)
                return &patients[i];
        }

        return nullptr;
    }

    Doctor* searchDoctor(int id)
    {
        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getId() == id)
                return &doctors[i];
        }

        return nullptr;
    }

public:

    // CONSTRUCTOR
    Hospital()
    {
        patientCount = 0;
        doctorCount = 0;
        appointmentCount = 0;

        // SAMPLE PATIENT
        patients[patientCount++] =
            Patient(1, "Rahul", 25, "9876543210",
                    "Fever", MALE);

        // SAMPLE DOCTOR
        doctors[doctorCount++] =
            Doctor(1, "Dr. Arun", 40, "9876501234",
                   "General Medicine");
    }

    // ADMIN: ADD PATIENT
    void addPatient()
    {
        if (patientCount >= 50)
        {
            cout << "Patient limit reached!\n";
            return;
        }

        char name[50], phone[15], disease[50];
        int age, gender;

        cout << "\nEnter Patient Name: ";
        cin >> ws;
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Phone: ";
        cin >> ws;
        cin.getline(phone, 15);

        cout << "Enter Disease: ";
        cin.getline(disease, 50);

        cout << "Gender (0-Male, 1-Female, 2-Other): ";
        cin >> gender;

        if (age <= 0 || gender < 0 || gender > 2)
            throw invalid_argument("Invalid patient details!");

        int id = nextPatientId();

        patients[patientCount++] =
            Patient(id, name, age, phone, disease,
                    static_cast<Gender>(gender));

        cout << "\nPatient Added Successfully!";
        cout << "\nPatient ID: " << id << "\n";
    }

    // ADMIN: DISPLAY PATIENTS
    void displayPatients()
    {
        if (patientCount == 0)
        {
            cout << "\nNo Patient Records Found!\n";
            return;
        }

        for (int i = 0; i < patientCount; i++)
            patients[i].displayPatient();
    }

    // ADMIN: UPDATE PATIENT
    void updatePatient()
    {
        int id;

        cout << "\nEnter Patient ID to Update: ";
        cin >> id;

        Patient *ptr = searchPatient(id);

        if (ptr == nullptr)
        {
            cout << "Patient Not Found!\n";
            return;
        }

        char name[50], phone[15], disease[50];
        int age;

        cout << "Enter New Name: ";
        cin >> ws;
        cin.getline(name, 50);

        cout << "Enter New Age: ";
        cin >> age;

        cout << "Enter New Phone: ";
        cin >> ws;
        cin.getline(phone, 15);

        cout << "Enter New Disease: ";
        cin.getline(disease, 50);

        if (age <= 0)
            throw invalid_argument("Invalid age!");

        ptr->updatePatient(name, age, phone, disease);

        cout << "\nPatient Updated Successfully!\n";
    }

    // ADMIN: DELETE PATIENT
    void deletePatient()
    {
        int id;

        cout << "\nEnter Patient ID to Delete: ";
        cin >> id;

        int index = -1;

        for (int i = 0; i < patientCount; i++)
        {
            if (patients[i].getId() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Patient Not Found!\n";
            return;
        }

        for (int i = index; i < patientCount - 1; i++)
            patients[i] = patients[i + 1];

        patientCount--;

        // Remove related appointments
        for (int i = 0; i < appointmentCount; )
        {
            if (appointments[i].patientId == id)
            {
                for (int j = i; j < appointmentCount - 1; j++)
                    appointments[j] = appointments[j + 1];

                appointmentCount--;
            }
            else
            {
                i++;
            }
        }

        cout << "\nPatient Deleted Successfully!\n";
    }

    // SEARCH PATIENT
    void searchPatientById()
    {
        int id;

        cout << "\nEnter Patient ID: ";
        cin >> id;

        Patient *ptr = searchPatient(id);

        if (ptr != nullptr)
            ptr->displayPatient();
        else
            cout << "Patient Not Found!\n";
    }

    void searchPatientByName()
    {
        char name[50];

        cout << "\nEnter Patient Name: ";
        cin >> ws;
        cin.getline(name, 50);

        Patient *ptr = searchPatient(name);

        if (ptr != nullptr)
            ptr->displayPatient();
        else
            cout << "Patient Not Found!\n";
    }

    // ADMIN: ADD DOCTOR
    void addDoctor()
    {
        if (doctorCount >= 20)
        {
            cout << "Doctor limit reached!\n";
            return;
        }

        char name[50], phone[15], specialization[50];
        int age;

        cout << "\nEnter Doctor Name: ";
        cin >> ws;
        cin.getline(name, 50);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Phone: ";
        cin >> ws;
        cin.getline(phone, 15);

        cout << "Enter Specialization: ";
        cin.getline(specialization, 50);

        if (age <= 0)
            throw invalid_argument("Invalid doctor age!");

        int id = nextDoctorId();

        doctors[doctorCount++] =
            Doctor(id, name, age, phone, specialization);

        cout << "\nDoctor Added Successfully!";
        cout << "\nDoctor ID: " << id << "\n";
    }

    // ADMIN: DISPLAY DOCTORS
    void displayDoctors()
    {
        if (doctorCount == 0)
        {
            cout << "\nNo Doctor Records Found!\n";
            return;
        }

        for (int i = 0; i < doctorCount; i++)
            doctors[i].displayDoctor();
    }

    // ADMIN: UPDATE DOCTOR
    void updateDoctor()
    {
        int id;

        cout << "\nEnter Doctor ID to Update: ";
        cin >> id;

        Doctor *ptr = searchDoctor(id);

        if (ptr == nullptr)
        {
            cout << "Doctor Not Found!\n";
            return;
        }

        char name[50], phone[15], specialization[50];
        int age;

        cout << "Enter New Name: ";
        cin >> ws;
        cin.getline(name, 50);

        cout << "Enter New Age: ";
        cin >> age;

        cout << "Enter New Phone: ";
        cin >> ws;
        cin.getline(phone, 15);

        cout << "Enter New Specialization: ";
        cin.getline(specialization, 50);

        if (age <= 0)
            throw invalid_argument("Invalid age!");

        ptr->updateDoctor(name, age, phone, specialization);

        cout << "\nDoctor Updated Successfully!\n";
    }

    // ADMIN: DELETE DOCTOR
    void deleteDoctor()
    {
        int id;

        cout << "\nEnter Doctor ID to Delete: ";
        cin >> id;

        int index = -1;

        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getId() == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Doctor Not Found!\n";
            return;
        }

        for (int i = index; i < doctorCount - 1; i++)
            doctors[i] = doctors[i + 1];

        doctorCount--;

        // Remove related appointments
        for (int i = 0; i < appointmentCount; )
        {
            if (appointments[i].doctorId == id)
            {
                for (int j = i; j < appointmentCount - 1; j++)
                    appointments[j] = appointments[j + 1];

                appointmentCount--;
            }
            else
            {
                i++;
            }
        }

        cout << "\nDoctor Deleted Successfully!\n";
    }

    // BOOK APPOINTMENT
    void bookAppointment(int patientId)
    {
        if (appointmentCount >= 50)
        {
            cout << "Appointment limit reached!\n";
            return;
        }

        if (searchPatient(patientId) == nullptr)
        {
            cout << "Patient Account Not Available!\n";
            return;
        }

        int doctorId;

        displayDoctors();

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;

        if (searchDoctor(doctorId) == nullptr)
        {
            cout << "Doctor Not Found!\n";
            return;
        }

        Appointment &a = appointments[appointmentCount];

        a.patientId = patientId;
        a.doctorId = doctorId;

        cout << "Enter Appointment Date: ";
        cin >> ws;
        cin.getline(a.date, 20);

        cout << "Enter Appointment Time: ";
        cin.getline(a.time, 20);

        appointmentCount++;

        cout << "\nAppointment Booked Successfully!\n";
    }

    // DISPLAY ALL APPOINTMENTS
    void displayAppointments()
    {
        if (appointmentCount == 0)
        {
            cout << "\nNo Appointments Found!\n";
            return;
        }

        for (int i = 0; i < appointmentCount; i++)
        {
            cout << "\n--- APPOINTMENT ---";

            cout << "\nPatient ID: "
                 << appointments[i].patientId;

            cout << "\nDoctor ID: "
                 << appointments[i].doctorId;

            cout << "\nDate: "
                 << appointments[i].date;

            cout << "\nTime: "
                 << appointments[i].time << "\n";
        }
    }

    // PATIENT: VIEW OWN PROFILE
    void viewOwnProfile(int id)
    {
        Patient *ptr = searchPatient(id);

        if (ptr != nullptr)
            ptr->displayPatient();
        else
            cout << "Patient Record Not Found!\n";
    }

    // PATIENT: VIEW OWN APPOINTMENTS
    void viewOwnAppointments(int id)
    {
        bool found = false;

        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].patientId == id)
            {
                found = true;

                cout << "\nDoctor ID: "
                     << appointments[i].doctorId;

                cout << "\nDate: "
                     << appointments[i].date;

                cout << "\nTime: "
                     << appointments[i].time << "\n";
            }
        }

        if (!found)
            cout << "\nNo Appointments Found!\n";
    }

    // DOCTOR: UPDATE PATIENT DISEASE
    void updateMedicalDetails()
    {
        int id;

        cout << "\nEnter Patient ID: ";
        cin >> id;

        Patient *ptr = searchPatient(id);

        if (ptr == nullptr)
        {
            cout << "Patient Not Found!\n";
            return;
        }

        char disease[50];

        cout << "Enter Updated Medical Condition: ";
        cin >> ws;
        cin.getline(disease, 50);

        ptr->updateDisease(disease);

        cout << "\nMedical Details Updated Successfully!\n";
    }

    // FUNCTION OVERLOADING - BILL
    void generateBill(int consultationFee)
    {
        cout << "\nConsultation Fee: Rs. "
             << consultationFee << "\n";
    }

    void generateBill(int consultationFee, int medicineFee)
    {
        cout << "\n--- HOSPITAL BILL ---";

        cout << "\nConsultation Fee: Rs. "
             << consultationFee;

        cout << "\nMedicine Fee: Rs. "
             << medicineFee;

        cout << "\nTotal Amount: Rs. "
             << consultationFee + medicineFee << "\n";
    }
};

// ADMIN MENU
void adminMenu(Hospital &h)
{
    int choice;

    do
    {
        cout << "\n\n========== ADMIN MENU ==========";
        cout << "\n1. Add Patient";
        cout << "\n2. View Patients";
        cout << "\n3. Update Patient";
        cout << "\n4. Delete Patient";
        cout << "\n5. Search Patient By ID";
        cout << "\n6. Search Patient By Name";
        cout << "\n7. Add Doctor";
        cout << "\n8. View Doctors";
        cout << "\n9. Update Doctor";
        cout << "\n10. Delete Doctor";
        cout << "\n11. View Appointments";
        cout << "\n12. Generate Bill";
        cout << "\n0. Logout";

        cout << "\nEnter Choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
                case 1: h.addPatient(); break;
                case 2: h.displayPatients(); break;
                case 3: h.updatePatient(); break;
                case 4: h.deletePatient(); break;
                case 5: h.searchPatientById(); break;
                case 6: h.searchPatientByName(); break;
                case 7: h.addDoctor(); break;
                case 8: h.displayDoctors(); break;
                case 9: h.updateDoctor(); break;
                case 10: h.deleteDoctor(); break;
                case 11: h.displayAppointments(); break;

                case 12:
                {
                    int c, m;

                    cout << "Consultation Fee: ";
                    cin >> c;

                    cout << "Medicine Fee: ";
                    cin >> m;

                    if (c < 0 || m < 0)
                        throw invalid_argument("Invalid fee!");

                    h.generateBill(c, m);
                    break;
                }

                case 0:
                    cout << "Admin Logged Out!\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }

    } while (choice != 0);
}

// DOCTOR MENU
void doctorMenu(Hospital &h)
{
    int choice;

    do
    {
        cout << "\n\n========== DOCTOR MENU ==========";
        cout << "\n1. View All Patients";
        cout << "\n2. Search Patient By ID";
        cout << "\n3. Search Patient By Name";
        cout << "\n4. Update Medical Details";
        cout << "\n5. View Appointments";
        cout << "\n0. Logout";

        cout << "\nEnter Choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
                case 1: h.displayPatients(); break;
                case 2: h.searchPatientById(); break;
                case 3: h.searchPatientByName(); break;
                case 4: h.updateMedicalDetails(); break;
                case 5: h.displayAppointments(); break;

                case 0:
                    cout << "Doctor Logged Out!\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }

    } while (choice != 0);
}

// PATIENT MENU
void patientMenu(Hospital &h, int patientId)
{
    int choice;

    do
    {
        cout << "\n\n========== PATIENT MENU ==========";
        cout << "\n1. View My Profile";
        cout << "\n2. Book Appointment";
        cout << "\n3. View My Appointments";
        cout << "\n0. Logout";

        cout << "\nEnter Choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
                case 1:
                    h.viewOwnProfile(patientId);
                    break;

                case 2:
                    h.bookAppointment(patientId);
                    break;

                case 3:
                    h.viewOwnAppointments(patientId);
                    break;

                case 0:
                    cout << "Patient Logged Out!\n";
                    break;

                default:
                    cout << "Invalid Choice!\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }

    } while (choice != 0);
}

// AUTHENTICATION
void login(Hospital &h)
{
    char username[30];
    char password[30];

    cout << "\nEnter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // ADMIN AUTHENTICATION
    if (strcmp(username, "admin") == 0 &&
        strcmp(password, "admin123") == 0)
     {
        cout << "\nAdmin Login Successful!\n";
        adminMenu(h);
    }
    // ADMIN AUTHENTICATION
    else if (strcmp(username, "doctor") == 0 &&
        strcmp(password, "doctor123") == 0)
     {
        cout << "\ndoctor Login Successful!\n";
        doctorMenu(h);
    }


    // PATIENT AUTHENTICATION
    else if (strcmp(username, "patient") == 0 &&
             strcmp(password, "patient123") == 0)
    {
        cout << "\nPatient Login Successful!\n";
        patientMenu(h, 1);
    }

    else
    {
        cout << "\nInvalid Username or Password!\n";
    }
}

// MAIN FUNCTION
int main()
{
    Hospital h;
    int choice;

    do
    {
        cout << "\n\n====================================";
        cout << "\n       HOSPITAL MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Login";
        cout << "\n0. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
         {
            case 1:
                login(h);
                break;

            case 0:
                cout << "\nThank You For Using The System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 0);

    return 0;
}
