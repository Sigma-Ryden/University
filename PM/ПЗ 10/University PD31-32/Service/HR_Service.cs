using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class HR_Service
    {
        private DBItem<Student> dbStudent;
        private DBItem<Address> dbAddress;

        public HR_Service(DBItem<Student> dbStudent, DBItem<Address> dbAddress)
        {
            this.dbStudent = dbStudent;
            this.dbAddress = dbAddress;
        }
        public void StudentCreate(string name, string surname, int age, int groupId)
        {
            Student student = new Student(name, surname, age, groupId);
            dbStudent.AddItem(student);
        }

        public void AdressCreate(string studentAdress, int studentId)
        {
            Address address = new Address(studentAdress, studentId);
            dbAddress.AddItem(address);
        }

        public string ShowStudentAddress()
        {
            string result = "";
            List<Student> StudentItems = dbStudent.Items;
            List<Address> AddressItems = dbAddress.Items;
            foreach(var studentItem in StudentItems)
            {
                result += studentItem.ToString() + "\n";
                foreach(var addressItem in AddressItems)
                {
                    if(studentItem.Id == addressItem.StudentId)
                    {
                        result += "\t" + addressItem.ToString() + "\n";
                    }
                }
            }
            return result;
        }
    }
}
