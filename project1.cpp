#include <iostream>
#include <string>

using namespace std;

// Abstract base class for Doctors
class Doctor {
public:
    virtual void displayTreatments() const = 0;
    virtual void displayAvailableSlots() const = 0;
    virtual void bookAppointment(const string& patientInfo, const string& treatment, int slot) = 0;
    virtual int getAvailableSlots() const = 0;
    virtual bool isSlotAvailable(int slot) const = 0;
    virtual ~Doctor() = default;
};

// Derived class representing Dr. Ali
class DrAli : public Doctor {
private:
    string name;
    int age;
    string gender;
    string phoneNumber;
    static bool slots[5];
    static string appointments[5];

public:
    DrAli(string name, int age, string gender, string phoneNumber)
        : name(name), age(age), gender(gender), phoneNumber(phoneNumber) {}

    void displayTreatments() const override {
        cout << "Available Skin Treatments (Dr. Ali):\n";
        cout << "1. Acne Treatment - 11000pkr\n";
        cout << "2. Skin Cancer Screening - 120,000pkr\n";
        cout << "3. Mole Removal - 15000pkr\n";
        cout << "4. Allergy Test - 5000pkr\n";
    }

    void displayAvailableSlots() const override {
        cout << "Available Slots (Dr. Ali):\n";
        for (int i = 0; i < 5; ++i) {
            if (!slots[i]) {
                cout << "Slot " << i + 1 << " is available.\n";
            }
        }
    }

    void bookAppointment(const string& patientInfo, const string& treatment, int slot) override {
        if (!slots[slot - 1]) {
            appointments[slot - 1] = "Slot " + to_string(slot) + ": " + patientInfo + " - " + treatment;
            slots[slot - 1] = true;
            cout << "Appointment booked successfully with Dr. Ali at slot " << slot << "!\n";
        } else {
            cout << "Slot " << slot << " is not available with Dr. Ali!\n";
        }
    }

    int getAvailableSlots() const override {
        int count = 0;
        for (int i = 0; i < 5; ++i) {
            if (!slots[i]) ++count;
        }
        return count;
    }

    bool isSlotAvailable(int slot) const override {
        return !slots[slot - 1];
    }
};

// Initialize static members
bool DrAli::slots[5] = { true, false, true, false, true }; // Slots 1, 3, 5 are unavailable
string DrAli::appointments[5];

// Derived class representing Dr. Salwa
class DrSalwa : public Doctor {
private:
    string name;
    int age;
    string gender;
    string phoneNumber;
    static bool slots[5];
    static string appointments[5];

public:
    DrSalwa(string name, int age, string gender, string phoneNumber)
        : name(name), age(age), gender(gender), phoneNumber(phoneNumber) {}

    void displayTreatments() const override {
        cout << "Available Skin Treatments (Dr. Salwa):\n";
        cout << "1. Acne Treatment - 10000pkr\n";
        cout << "2. Skin Cancer Screening - 100000pkr\n";
        cout << "3. Mole Removal - 13000pkr\n";
        cout << "4. Allergy Test - 4500pkr\n";
    }

    void displayAvailableSlots() const override {
        cout << "Available Slots (Dr. Salwa):\n";
        for (int i = 0; i < 5; ++i) {
            if (!slots[i]) {
                cout << "Slot " << i + 1 << " is available.\n";
            }
        }
    }

    void bookAppointment(const string& patientInfo, const string& treatment, int slot) override {
        if (!slots[slot - 1]) {
            appointments[slot - 1] = "Slot " + to_string(slot) + ": " + patientInfo + " - " + treatment;
            slots[slot - 1] = true;
            cout << "Appointment booked successfully with Dr. Salwa at slot " << slot << "!\n";
        } else {
            cout << "Slot " << slot << " is not available with Dr. Salwa!\n";
        }
    }

    int getAvailableSlots() const override {
        int count = 0;
        for (int i = 0; i < 5; ++i) {
            if (!slots[i]) ++count;
        }
        return count;
    }

    bool isSlotAvailable(int slot) const override {
        return !slots[slot - 1];
    }
};

// Initialize static members
bool DrSalwa::slots[5] = { false, true, false, true, false }; // Slots 2, 4 are unavailable
string DrSalwa::appointments[5];

// Class representing the Dermatology Clinic
class DermatologyClinic {
private:
    DrAli mainDoctor;
    DrSalwa assistingDoctor;
public:
    DermatologyClinic()
        : mainDoctor("Dr. Ali", 45, "Male", "123-456-7890"),
          assistingDoctor("Dr. Salwa", 30, "Female", "098-765-4321") {}

    void run() {
        cout << "==============================================\n";
        cout << "= Welcome to Online Appointment Scheduler    =\n";
        cout << "=                by                          =\n";
        cout << "=    javeria, rabia and umama                =\n";
        cout << "==============================================\n\n";

        string patientName;
        int patientAge;
        string patientGender;
        string patientPhoneNumber;

        cout << "Enter patient name: ";
        getline(cin, patientName);

        cout << "Enter patient age: ";
        while (!(cin >> patientAge) || patientAge <= 0) {
            cout << "Please enter a valid age: ";
            cin.clear();
            while (cin.get() != '\n'); // Clear invalid input from stream
        }
        cin.ignore(); // Ignore leftover newline

        cout << "Enter patient gender (male/female/costume): ";
        while (true) {
            getline(cin, patientGender);
            if (patientGender == "male" || patientGender == "female" || patientGender == "costume") {
                break;
            } else {
                cout << "Please enter a valid gender (male/female/costume): ";
            }
        }

        cout << "Enter patient phone number: ";
        getline(cin, patientPhoneNumber);

        cout << "Authenticated successfully!\n";

        mainDoctor.displayTreatments();

        string treatment;
        cout << "Enter treatment: ";
        getline(cin, treatment);

        string patientInfo = patientName + " (" + to_string(patientAge) + ", " + patientGender + ", " + patientPhoneNumber + ")";

        int slot;
        while (true) {
            mainDoctor.displayAvailableSlots();
            cout << "Enter preferred slot (1-5): ";
            if (!(cin >> slot) || slot < 1 || slot > 5) {
                cout << "Invalid slot! Slots are numbered 1 to 5. Please enter a valid slot.\n";
                cin.clear();
                while (cin.get() != '\n');
                continue;
            }
            cin.ignore();

            if (mainDoctor.isSlotAvailable(slot)) {
                mainDoctor.bookAppointment(patientInfo, treatment, slot);
                break;
            } else {
                cout << "Slot " << slot << " is not available with Dr. Ali.\n";
                assistingDoctor.displayTreatments();
                assistingDoctor.displayAvailableSlots();
                cout << "Would you like to book an appointment with Dr. Salwa instead? (yes/no): ";
                string response;
                getline(cin, response);
                if (response == "yes" || response == "Yes") {
                    cout << "Enter preferred slot (1-5): ";
                    if (!(cin >> slot) || slot < 1 || slot > 5) {
                        cout << "Invalid slot! Slots are numbered 1 to 5. Please enter a valid slot.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                        continue;
                    }
                    cin.ignore();
                    if (assistingDoctor.isSlotAvailable(slot)) {
                        assistingDoctor.bookAppointment(patientInfo, treatment, slot);
                    } else {
                        cout << "Slot " << slot << " is not available with Dr. Salwa either.\n";
                        cout << "Thanks, we will notify you when doctors are available.\n";
                    }
                } else {
                    cout << "No appointment booked.\n";
                }
                break;
            }
        }
    }
};

int main() {
    DermatologyClinic clinic;
    clinic.run();
    return 0;
}