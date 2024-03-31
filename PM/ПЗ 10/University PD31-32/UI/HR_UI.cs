using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class HR_UI
    {
        HR_Service hr_Service;
        public HR_UI(HR_Service hr_Service)
        {
            this.hr_Service = hr_Service;
        }
        public void StudentCreate()
        {
            Helper.AddMore(CreateStudent);
        }

        /*public void StudentDelete()
        {
            Console.WriteLine("Delete Student Id?: ");
            int idToDelete = Helper.CheckIntInput();
        }*/
        private void CreateStudent()
        {
            Console.Write("CreateStudent Name?: ");
            string name = Console.ReadLine();

            Console.Write("CreateStudent Surname?: ");
            string surname = Console.ReadLine();

            Console.Write("CreateStudent Age?: ");
            int age = int.Parse(Console.ReadLine());

            int groupId = Helper.CheckIntInput("CreateStudent GroupId?: ");
            
            hr_Service.StudentCreate(name, surname, age, groupId);
        }
        
        public void AddressCreate()
        {
            Helper.AddMore(CreateAddress);
        }

        private void CreateAddress()
        {
            Console.Write("CreateAddress Address?: ");
            string address = Console.ReadLine();

            int studentId = Helper.CheckIntInput("CreateAddress StudentId?: ");
            hr_Service.AdressCreate(address, studentId);
        }

        public void ShowStudentAddress()
        {
            string result = hr_Service.ShowStudentAddress();

            Console.WriteLine(result);
        }
    }
}
