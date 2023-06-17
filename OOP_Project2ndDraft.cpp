#include <bits/stdc++.h>

using namespace std;

class Person
{
	char Name[50], Gender[10];
	int Age;
	char Address[50], Blood_Group[5];
	
	public:
		
		void Person_Info(void)
		{
			cout<<"Enter the Name :\n";
			cin.clear();
			cin.ignore();
			cin.getline(Name, 50);
			
			cout<<"Enter the Gender :\n";
			cin>>Gender;
			
			cout<<"Enter the Age :\n";
			cin>>Age;
			
			cout<<"Enter the Address :\n";
			cin.clear();
			cin.ignore();
			cin.getline(Address, 50);
			
			
			cout<<"Enter the Blood Group :\n";
			cin>>Blood_Group;
		}
		
		void Display_Info (void)
		{
			cout<<"\nName: "<<Name;
			cout<<"\nGender: "<<Gender;
			cout<<"\nAge: "<<Age;
			cout<<"\nAddress: "<<Address;
			cout<<"\nBlood Group: "<<Blood_Group;
		}
};

class Staff: public Person
{
	int Salary;
	char From[30], To[30];
	
	public:
		
		void Staff_Info(void)
		{
			Person_Info();
			cout<<"\nEnter the Salary: \n";
			cin>>Salary;
			
			cout<<"\nEnter the Duty time:\n";
			cout<<"\nFrom:\n";
			cin>>From;
			cout<<"\nTo:\n";
			cin>>To;
			
		}
		
		void Show_Staff(void)
		{
			Display_Info();
			cout<<"\nSalary: "<<Salary;
			cout<<"\nDuty Time: "<<From<<"--"<<To<<endl;
			
		}
};

class Patient : public Person
{
	int Reg_No, Bill, Total;
	char Occupation[30], Date_Admit[20], Date_Discharge[20];
	
	public:
		
		char Medicine[100];
		void Patient_Bill (void);
		void Get_Data(void);
		void Show_Data(void);
		int Return_ID_No(void);
		void Modify_Medicine(int n);
		void Write_Patient(void);
		void Display_All(void);
		void Display_Patient(int n);
		void Modify_Patient(int n);
		void Delete_Patient(int n);
};

void Patient::Patient_Bill()
{
	system("cls");
	
	cout<<"*********************************************************";
	cout<<"\n\n\t\t\t\tPatient Fee Charge\n\n ";
	cout<<"*********************************************************";
	
	cout<<"\nHospital Room Charge                  :\t 1000";
	cout<<"\nCare Charges                          :\t 500";
	cout<<"\nMaintainance Charges                  :\t 500";
	cout<<"\nPatient Individual Bill               :\t "<<Bill;
	
	Total=1000+500+500+Bill;
	cout<<"\nTotal Charge                          :\t" <<Total<<"\n";
	cout<<"*********************************************************";
	
}

void Patient::Get_Data()
{
	Person_Info();
	
	cout<<"\nEnter the Registration number of the patient: ";
	cin>>Reg_No;
	
	cout<<"\nEnter the Patient's Occupation: ";
	cin>>Occupation;
	
	cout<<"\nEnter the Patient's bill: ";
	cin>>Bill;
	
	cout<<"\nEnter the date of admission(dd/mm/yyyy):";
	cin>>Date_Admit;
	
	cout<<"\nEnter the date of Discharge(dd/mm/yyyy): ";
	cin>>Date_Discharge;
	
	Patient_Bill();
	strncpy(Medicine, "", sizeof(Medicine)-1);
	Medicine[sizeof(Medicine)-1]=0;
}

void Patient::Show_Data()
{
	cout<<"\nEnter the Registration number of the patient: "<<Reg_No<<"\n";
	Display_Info();
	
	cout<<"\nOccupation : "<<Occupation;
	cout<<"\nAdmit Date : "<<Date_Admit;
	cout<<"\nDischarge Date : "<<Date_Discharge;
	cout<<"\nBill : "<<Total;
	cout<<"\nMedicine : "<<Medicine;

}

int Patient::Return_ID_No()
{
	return Reg_No;
}

void Patient::Modify_Medicine(int n)
{
	bool Found = false;
	Patient P;
	fstream File;
	
	File.open("Patient.dat", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"File not available !! Press any Key to continue..";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&P), sizeof(Patient));
		
		if(P.Return_ID_No()==n)
		{
			P.Show_Data();
			cout<<"\nEnter the Prescribed Medicine for the Patient: ";
			cin>>P.Medicine;
			
			int pos =(-1)*static_cast<int> (sizeof(P));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast <char *> (&P), sizeof(Patient));
			Found=true;
		}
	}
	
	File.close();
	
	if(Found==false)
	{
		cout<<"\nRecord not found!!";
	}
	cin.ignore();
	cin.get();
}

void Patient::Write_Patient()
{
	Patient P;
	ofstream OutFile;
	OutFile.open("Patient.dat", ios::binary|ios::app);
	
	P.Get_Data();
	OutFile.write(reinterpret_cast <char *> (&P), sizeof(Patient));
	OutFile.close();
	
	cout<<"Patient record has been created.";
	cin.ignore();
	cin.get();
}

void Patient::Display_All()
{
	Patient P;
	ifstream InFile;
	InFile.open("Patient.dat",ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";
	
	while(InFile.read(reinterpret_cast <char *> (&P), sizeof(Patient)))
	{
		P.Show_Data();
		cout<<"\n";
		cout<<"\n===============================================================";
		cout<<"\n";
	}
	
	InFile.close();
	cin.ignore();
	cin.get();
}

void Patient::Display_Patient(int n)
{
	Patient P;
	ifstream InFile;
	InFile.open("Patient.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available !! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	bool Flag = false;
	
	while(InFile.read(reinterpret_cast <char *> (&P), sizeof(Patient)))
	{
		if(P.Return_ID_No()==n)
		{
			P.Show_Data();
			Flag=true;
		}
	}
	
	InFile.close();
	
	if(Flag==false)
	{
		cout<<"\nRecord not found!!";
	}
	cin.ignore();
	cin.get();
}

void Patient::Modify_Patient(int n)
{
	bool Found = false;
	Patient P;
	fstream File;
	File.open("Patient.dat", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&P), sizeof(Patient));
		
		if(P.Return_ID_No()==n)
		{
			P.Show_Data();
			cout<<"\nPlease Enter the new details of the Patient";
			P.Get_Data();
			
			int pos=(-1)*static_cast<int> (sizeof(P));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast <char *> (&P), sizeof(Patient));
			
			cout<<"\n\n\t Record Updated!";
			Found = true;
		}
	}
	
	File.close();
	if(Found==false)
	{
		cout<<"\nRecord not Found!";

	}
	cin.ignore();
	cin.get();
}

void Patient::Delete_Patient(int n)
{
	Patient P;
	ifstream InFile;
	InFile.open("Patient.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	ofstream OutFile;
	OutFile.open("Temp.dat", ios::out);
	InFile.seekg(0,ios::beg);
	
	while(InFile.read(reinterpret_cast <char *> (&P), sizeof(Patient)))
	{
		if(P.Return_ID_No()!=n)
		{
			OutFile.write(reinterpret_cast <char *> (&P), sizeof(Patient));
		}
	}
	
	OutFile.close();
	InFile.close();
	remove("Patient.dat");
	rename("Temp.dat", "Patient.dat");
	
	cout<<"\n\n\tRecord Deleted!!";
	cin.ignore();
	cin.get();
}

class Doctor: public Staff
{
	int Doc_ID;
	Patient P;
	char Specialization[300];
	
	public:
		bool Check_Reg_No(int n);
		void Doctor_Info(void);
		void Show_Doctor(void);
		int Return_Doctor_ID(void);
		void Prescribe_Medicine(void);
		void Write_Doctor(void);
		void Display_All_Doctor(void);
		void Display_Doctor(int n);
		void Modify_Doctor(int n);
		void Delete_Doctor(int n);
		void Doctor_Choice(void);
		void Doctor_Menu(void);
};

bool Doctor::Check_Reg_No(int n)
{
	bool Found = false;
	Doctor D;
	fstream File;
	File.open("Doctor.dat", ios::binary|ios::in);
	
	if(!File)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&D), sizeof(Doctor));
		
		if(D.Doc_ID==n)
		{
			Found = true;
		}
	}
	
	File.close();
	return Found;
	cin.ignore();
	cin.get();
}

void Doctor::Doctor_Info()
{
	Staff_Info();
	id:
	cout<<"\nEnter Doctor ID(1-100): ";
	int m;
	cin>>m;
	
	if(Check_Reg_No(m)==false)
	{
		Doc_ID = m;
	}
	else
	{
		cout<<"\nID already taken\n";
		goto id;
	}
	
	cout<<"\nEnter the Specialization of the Doctor: ";
	cin>>Specialization;
	system("pause");
}

void Doctor::Show_Doctor()
{
	cout<<"\nDoctor ID:"<<Doc_ID;
	Show_Staff();
	cout<<"Specialization: "<<Specialization;
}

int Doctor::Return_Doctor_ID()
{
	return Doc_ID;
}

void Doctor::Prescribe_Medicine()
{
	int n;
	cout<<"\n\n\tEnter the Registration number of the Patient : ";
	cin>>n;
	P.Modify_Medicine(n);
}

void Doctor::Write_Doctor()
{
	Doctor D;
	ofstream OutFile;
	OutFile.open("Doctor.dat", ios::binary|ios::app);
	D.Doctor_Info();
	
	OutFile.write(reinterpret_cast <char *> (&D), sizeof(Doctor));
	cout<<"\n\nDoctor record has been created!";
	
	OutFile.close();
	cin.ignore();
	cin.get();
}

void Doctor::Display_All_Doctor()
{
	Doctor D;
	ifstream InFile;
	InFile.open("Doctor.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";
	
	while(InFile.read(reinterpret_cast <char *> (&D), sizeof(Doctor)))
	{
		D.Show_Doctor();
		cout<<"\n";
		cout<<"\n===============================================================";
		cout<<"\n";
	}
	
	InFile.close();
	cin.ignore();
	cin.get();
}

void Doctor::Display_Doctor(int n)
{
	Doctor D;
	ifstream InFile;
	InFile.open("Doctor.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	bool Flag=false;
	while(InFile.read(reinterpret_cast <char *> (&D), sizeof(Doctor)))
	{
		if(D.Doc_ID==n)
		{
			D.Show_Doctor();
			Flag=true;
		}
	}
	
	InFile.close();
	if(Flag==false)
	{
		cout<<"Record does not exist!!";
	}
	cin.ignore();
	cin.get();
}

void Doctor::Modify_Doctor(int n)
{
	bool Found = false;
	Doctor D;
	fstream File;
	File.open("Doctor.dat", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&D), sizeof(Doctor));
		
		if(D.Doc_ID==n)
		{
			D.Show_Doctor();
			cout<<"\n\nPlease Enter the new Details: ";
			D.Doctor_Info();
			
			int pos=(-1)*static_cast <int> (sizeof(D));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast <char *> (&D), sizeof(Doctor));
			
			cout<<"\n\n\tRecord Updated!!";
			Found =true;
		}
	}
	
	File.close();
	if(Found==false)
	{
		cout<<"\n\nRecord not found!!";
	}
	cin.ignore();
	cin.get();
}

void Doctor::Delete_Doctor(int n)
{
	
	Doctor D;
	ifstream InFile;
	InFile.open("Doctor.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	ofstream OutFile;
	OutFile.open("Temp1.dat", ios::out);
	InFile.seekg(0,ios::beg);
	
	while(InFile.read(reinterpret_cast <char *> (&D), sizeof(Doctor)))
	{
		if(D.Return_Doctor_ID()!=n)
		{
			OutFile.write(reinterpret_cast <char *> (&D), sizeof(Doctor));
		}
	}
	
	OutFile.close();
	InFile.close();
	remove("Doctor.dat");
	rename("Temp1.dat", "Doctor.dat");
	
	cout<<"\n\n\tRecord Deleted!!";
	cin.ignore();
	cin.get();
}

void Doctor::Doctor_Choice()
{
	char ch;
	
	do
	{
		int n;
		system("cls");
		
		cout<<"\n\n\t1. Prescribe Medicine for Patient ";
		cout<<"\n\n\t2. Find Doctor ";
		cout<<"\n\n\t3.EXIT..";
		cout<<"\n\n\tPlease Select any Option (1-3) ";
		cin>>ch;
		system("cls");
		
		switch(ch)
		{
			case '1':
			Prescribe_Medicine();
			break;
			
			case '2':
			cout<<"Enter Doctor ID :";
			cin>>n;
			Display_Doctor(n);
			break;
				
		}
	}
	while(ch!='3');
}

void Doctor::Doctor_Menu()
{
	char ch;
	
	do
	{
		int n;
		system("cls");
		
		cout<<"\n\n\t1.INSERT Doctor Data";
		cout<<"\n\n\t2.SEARCH Doctor ";
		cout<<"\n\n\t3.SHOW ALL Doctors";
		cout<<"\n\n\t4.MODIFY Doctor Data";
		cout<<"\n\n\t5.DELETE Doctor";
		cout<<"\n\n\t6.EXIT";
		cout<<"\n\n\tPlease Select an Option (1-6)\n";
		cin>>ch;
		
		system("cls");
		switch(ch)
		{
			case '1':
			Write_Doctor();
			break;
			
			case '2':
			cout<<"\nEnter the Doctor ID: ";
			cin>>n;
			Display_Doctor(n);
			break;
			
			case '3':
			Display_All_Doctor();
			break;
			
			case '4':
			cout<<"\nEnter the Doctor ID: ";
			cin>>n;
			Modify_Doctor(n);
			break;
			
			case '5':
			cout<<"\nEnter the Doctor ID: ";
			cin>>n;
			Delete_Doctor(n);
			break;	
			
		}
	}
	
	while (ch!='6');
}

class Nurse: public Staff
{
	int Nurse_ID;
	char Duty_Room [50];
	Patient P;
	
	public:
		void Get_Nurse_Info(void);
		void Display_Nurse_Info(void);
		void Write_Nurse_Info(void);
		void Display_Nurse(int m);
		void Modify_Nurse(int m);
		void Display_All_Nurse(void);
		void Nurse_Menu(void);
};

void Nurse::Get_Nurse_Info()
{
	cout<<"-------------------------------"<<endl;
	Staff_Info();
	
	cout<<"\nEnter the Nurse ID: ";
	cin>>Nurse_ID;
	cout<<"\nEnter the Nurse's Duty Room: ";
	cin>>Duty_Room;
}

void Nurse::Display_Nurse_Info()
{
	cout<<"\nNurse ID: "<<Nurse_ID;
	Show_Staff();
	cout<<"\n"<<"Duty in Room: "<<Duty_Room;
	cout<<endl;
}


void Nurse::Write_Nurse_Info()
{
	Nurse N;
	ofstream OutFile;
	OutFile.open("Nurse.dat", ios::binary|ios::app);
	N.Get_Nurse_Info();
	
	OutFile.write(reinterpret_cast <char *> (&N), sizeof(Nurse));
	OutFile.close();
	
	cout<<"\n\nRecord has been created!!";
	cin.ignore();
	cin.get();
}


void Nurse::Display_Nurse(int m)
{
	Nurse N;
	ifstream InFile;
	InFile.open("Nurse.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	bool Flag=false;
	while(InFile.read(reinterpret_cast <char *> (&N), sizeof(Nurse)))
	{
		if(N.Nurse_ID==m)
		{
			N.Display_Nurse_Info();
			Flag=true;
		}
	}
	
	InFile.close();
	if(Flag==false)
	{
		cout<<"\n\nRecord not found!!";
	}
	cin.ignore();
	cin.get();
	
}

void Nurse::Modify_Nurse(int m)
{
	bool Found=false;
	Nurse N;
	fstream File;
	File.open("Nurse.dat", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&N), sizeof(Nurse));
		if(N.Nurse_ID==m)
		{
			N.Display_Nurse_Info();
			cout<<"\nPlease enter the new details :";
			N.Get_Nurse_Info();
			
			int pos = (-1)*static_cast <int> (sizeof(N));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast <char *> (&N), sizeof(Nurse));
			
			cout<<"\n\n\tRecord Updated!!";
			Found=true;
		}
	}
	
	File.close();
	if(Found==false)
	{
		cout<<"Record not found!!";
	}
	cin.ignore();
	cin.get();
}

void Nurse::Display_All_Nurse()
{
	Nurse N;
	ifstream InFile;
	InFile.open("Nurse.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";
	while(InFile.read(reinterpret_cast <char *> (&N), sizeof(Nurse)))
	{
		N.Display_Nurse_Info();
		cout<<"\n";
		cout<<"\n===============================================================";
		cout<<"\n";
	}
	
	InFile.close();
	cin.ignore();
	cin.get();
}

void Nurse::Nurse_Menu()
{
	char ch;
	
	do
	{
		int n;
		system("cls");
		
		cout<<"\n\n\t1.INSERT Nurse Data";
		cout<<"\n\n\t2.SEARCH Nurse";
		cout<<"\n\n\t3.DISPLAY ALL Nurse";
		cout<<"\n\n\t4.MODIFY Nurse Data";
		cout<<"\n\n\t5.EXIT";
		cin>>ch;
		system("cls");
		
		switch(ch)
		{
			case'1':
			Write_Nurse_Info();
			break;
			
			case '2':
			cout<<"\nEnter the Nurse ID: ";
			cin>>n;
			Display_Nurse(n);
			break;
			
			case '3':
			Display_All_Nurse();
			break;
			
			case '4':
			cout<<"\nEnter the Nurse ID: ";
			cin>>n;
			Modify_Nurse(n);
			break;
			
		}
	}
	
	while(ch!='5');
}


class Receptionist : public Staff
{
	Patient P;
	int Receptionist_ID;
	
	public:
		void Receptionist_Info(void);
		void Show_Receptionist(void);
		void Enter_Patient(void);
		void Write_Receptionist(void);
		void Display_All_Receptionists(void);
		void Display_Receptionist(int n);
		void Modify_Receptionist(int n);
		void Receptionist_Menu(void);
};

void Receptionist::Receptionist_Info()
{
	Staff_Info();
	cout<<"\nEnter the Receptionist ID: ";
	cin>>Receptionist_ID;
}

void Receptionist::Show_Receptionist()
{
	Show_Staff();
	cout<<"\nReceptionist ID: "<<Receptionist_ID;
}

void Receptionist::Enter_Patient()
{
	char ch;
	int n;
	
	do
	{
		system("cls");
		cout<<"\n\n\n\tENTRY MENU";
		cout<<"\n\n\t1.CREATE Patient Record";
		cout<<"\n\n\t2.DISPLAY ALL Patients Records";
		cout<<"\n\n\t3.SEARCH Patient Record";
		cout<<"\n\n\t4.MODIFY Patient Record";
		cout<<"\n\n\t5.DELETE Patient Record";
		cout<<"\n\n\t6.EXIT";
		cout<<"\n\n\tPlease Select an Option (1-6)\n";
		cin>>ch;
		system("cls");
		
		switch(ch)
		{
			case '1':
			P.Write_Patient();
			break;
			
			case '2':
			P.Display_All();
			break;
			
			case '3':
			cout<<"\n\n\tPlease Enter the Registration number: ";
			cin>>n;
			P.Display_Patient(n);
			break;
			
			case '4':
			cout<<"\n\n\tPlease Enter the Registration number: ";
			cin>>n;
			P.Modify_Patient(n);
			break;
			
			case '5':
			cout<<"\n\n\tPlease Enter the Registration number: ";
			cin>>n;
			P.Delete_Patient(n);
			break;
			
			default:
			break;
		
			
		}
	}
	
	while(ch!='6');
}

void Receptionist::Write_Receptionist()
{
	Receptionist R;
	ofstream OutFile;
	OutFile.open("Receptionist.dat", ios::binary|ios::app);
	R.Receptionist_Info();
	
	OutFile.write(reinterpret_cast <char *> (&R), sizeof(Receptionist));
	OutFile.close();
	cout<<"Record has been created!!";
	cin.ignore();
	cin.get();
}

void Receptionist::Display_All_Receptionists()
{
	Receptionist R;
	ifstream InFile;
	InFile.open("Receptionist.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";
	while(InFile.read(reinterpret_cast <char *> (&R), sizeof(Receptionist)))
	{
		R.Show_Receptionist();
		cout<<"\n";
		cout<<"\n===============================================================";
		cout<<"\n";
	}
	
	InFile.close();
	cin.ignore();
	cin.get();
}

void Receptionist::Display_Receptionist(int n)
{
	Receptionist R;
	ifstream InFile;
	InFile.open("Receptionist.dat", ios::binary);
	
	if(!InFile)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	bool Flag=false;
	while(InFile.read(reinterpret_cast <char *> (&R), sizeof(Receptionist)))
	{
		if(R.Receptionist_ID==n)
		{
			R.Show_Receptionist();
			Flag=true;
		}
	}
	
	InFile.close();
	if(Flag==false)
	{
		cout<<"\n\nRecord does not exist!!";
	}
	cin.ignore();
	cin.get();
}

void Receptionist::Modify_Receptionist(int n)
{
	bool Found=false;
	Receptionist R;
	fstream File;
	File.open("Receptionist.dat", ios::binary|ios::in|ios::out);
	
	if(!File)
	{
		cout<<"File not available!! Press any Key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(!File.eof() && Found==false)
	{
		File.read(reinterpret_cast <char *> (&R), sizeof(Receptionist));
		
		if(R.Receptionist_ID==n)
		{
			cout<<"\n\nPlease enter the new details: ";
			R.Receptionist_Info();
			
			int pos = (-1)* static_cast <int> (sizeof(R));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast <char *> (&R), sizeof(Receptionist));
			
			cout<<"\n\n\tRecord Updated!!";
			Found=true;
		}
	}
	
	File.close();
	if(Found==false)
	{
		cout<<"\n\nRecord not found!!";
	}
	cin.ignore();
	cin.get();
}

void Receptionist::Receptionist_Menu()
{
	char ch;
	do
	{
		int n;
		system("cls");
		
		cout<<"\n\n\t1.INSERT Receptionist Data ";
		cout<<"\n\n\t2.SEARCH Receptionist";
		cout<<"\n\n\t3.SHOW ALL Receptionists";
		cout<<"\n\n\t4.MODIFY Receptionist Data";
		cout<<"\n\n\t5.EXIT";
		cout<<"\n\n\tPlease Select an Option (1-5)\n";
		cin>>ch;
	    system("cls");
		
		switch(ch)
		{
			case '1':
			Write_Receptionist();
			break;
			
			case '2':
			cout<<"\nEnter the Receptionist ID: ";
			cin>>n;
			Display_Receptionist(n);
			break;
			
			case '3':
			Display_All_Receptionists();
			break;
			
			case '4':
			cout<<"\nEnter the Receptionist ID: ";
			cin>>n;
			Modify_Receptionist(n);
			break;
			

		}
	}
	
	while(ch!='5');
}




class Admin
{
	Doctor D;
	Patient P;
	Receptionist R;
	Nurse N;
	
	public:
		void Staff_Menu()
		{
			char ch;
			
			do
			{
				system("cls");
				
				cout<<"\n\n\tSTAFF MENU";
				cout<<"\n\n\t1.DOCTOR";
				cout<<"\n\n\t2.NURSE";
				cout<<"\n\n\t3.RECEPTIONIST";
				cout<<"\n\n\t4.EXIT";
				cout<<"\n\n\tPlease Enter your choice (1-4)\n";
				cin>>ch;
			    system("cls");
			
			switch(ch)
			{
				case '1':
				D.Doctor_Menu();
				break;
				
				case '2':
				N.Nurse_Menu();
				break;
				
				case '3':
				R.Receptionist_Menu();
				break;
				
				default:
				break;	
				
			}
			
		}
		while(ch!='4');
		
}
};


int main(void)

{
	Admin A;
	Receptionist R;
	Doctor D;
	Nurse N;
	int n;
	char password[20];
	
	do
	{   system("cls");
		cout<<"\t\t\n\n\n";
		cout<<"\n\n\n\tHOSPITAL MANAGEMENT SYSTEM\n\n";
		cout<<"\n\t\t1.ADMIN";
		cout<<"\n\t\t2.RECEPTIONIST";
		cout<<"\n\t\t3.DOCTOR";
		cout<<"\n\t\t4.EXIT";
		cout<<"\n";
		cin>>n;
		
		switch(n)
		{
			case 1:
			admin1:
			{
			cout<<"\nEnter the password: ";
			cin>>password;
			
			if(strcmp(password, "admin")==0)
			{
				A.Staff_Menu();
			}
			
			else 
			{
				cout<<"\nINVALID PASSWORD!!\n";
				goto admin1;
			}
			}
			break;
			
			case 2:
			receptionist1:	
			{
			cout<<"\nEnter the password: ";
			cin>>password;
			
			if(strcmp(password, "receptionist")==0)
			{
				R.Enter_Patient();
		    }
		    
		    else
		    {
		    	cout<<"\nINVALID PASSWORD!!\n";
				goto receptionist1;
			}
			}
			break;
			
			
			case 3:
			doctor1:
			{
			cout<<"\nEnter the password: ";
			cin>>password;
			
			if(strcmp(password, "doctor")==0)
			{
				D.Doctor_Choice();
		    }
		    
		    
		    else
		    {
		    	cout<<"\nINVALID PASSWORD!!\n";
				goto doctor1;
			}
			}
			break;
				
		}
	}
	while(n!=4);
	
	return 0;
}	


