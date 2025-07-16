# Blood Bank Management System – C++ Based Application

A comprehensive Blood Bank Management System developed in C++ that provides efficient management of donor and receiver records, blood unit tracking, and administrative controls.

## 🩸 Features

### User Authentication
- **Admin Login**: Full system access with administrative privileges
- **User Login**: Limited access for viewing records
- **Secure Password Input**: Hidden password entry for enhanced security

### Donor Management
- Add new donor records with eligibility screening
- View all donor records
- Store donor information including:
  - Personal details (name, age, contact)
  - Blood group
  - Last donation date
  - Medical eligibility verification

### Receiver Management
- Add new receiver records
- View all receiver records
- Track receiver requirements and contact information

### Blood Inventory Management
- Track available blood units by blood group
- Update blood inventory
- Real-time blood unit availability display

### Data Management
- CSV-based data storage for persistence
- Record deletion capabilities (Admin only)
- Data validation and error handling

### Medical Eligibility Screening
The system includes comprehensive eligibility checks for donors:
- Diabetes screening
- Blood pressure evaluation
- Alcohol consumption assessment
- Smoking habits verification

## 🛠️ Technical Specifications

- **Language**: C++
- **Platform**: Windows
- **Data Storage**: CSV files
- **Dependencies**: Standard C++ libraries
- **Compiler**: Compatible with modern C++ compilers

## 📋 System Requirements

- Windows Operating System
- C++ Compiler (GCC, MSVC, or similar)
- Minimum 4MB disk space
- Console application environment

## 🚀 Installation & Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/Blood-Bank-Management-System.git
   cd Blood-Bank-Management-System
   ```

2. **Compile the application**:
   ```bash
   g++ -o BloodBank final.c++
   ```

3. **Run the application**:
   ```bash
   ./BloodBank
   ```

## 👥 Default Login Credentials

### Administrator Access
- **Username**: `admin`
- **Password**: `admin123`

### User Access
- **Username**: `user`
- **Password**: `user123`

## 📁 File Structure

```
Blood-Bank-Management-System/
│
├── final.c++              # Main application source code
├── README.md               # Project documentation
├── donors.csv             # Donor records (auto-generated)
├── receivers.csv          # Receiver records (auto-generated)
└── blood_units.csv        # Blood inventory (auto-generated)
```

## 💻 Usage Guide

### Getting Started
1. Launch the application
2. Login with appropriate credentials
3. Navigate through the menu options

### Admin Functions
- **Add Donors**: Register new donors with eligibility screening
- **Add Receivers**: Register new blood recipients
- **Manage Inventory**: Update blood unit availability
- **Delete Records**: Remove outdated or incorrect entries
- **View All Records**: Access complete database

### User Functions
- **View Donor Records**: Browse donor database
- **View Receiver Records**: Browse receiver database
- **Check Blood Availability**: View current blood unit inventory

## 🔧 Key Components

### Classes and Structures
- `BloodBank`: Main application class managing all operations
- `Donor`: Structure for donor information
- `Receiver`: Structure for receiver information

### Core Functions
- `authenticateUser()`: User login validation
- `addDonor()`: Donor registration with eligibility check
- `addReceiver()`: Receiver registration
- `checkEligibility()`: Medical screening for donors
- `updateBloodUnits()`: Inventory management
- `deleteRecord()`: Data deletion functionality

## 📊 Data Storage

The application uses CSV files for data persistence:
- **donors.csv**: Stores donor information
- **receivers.csv**: Stores receiver information  
- **blood_units.csv**: Tracks blood inventory by type

## 🔒 Security Features

- Password masking during input
- Role-based access control
- Data validation and sanitization
- Secure file handling

---

⭐ **Star this repository if you find it helpful!**
