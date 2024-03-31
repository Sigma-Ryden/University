using System.Collections.Generic;

namespace PM
{
    class Employee
    {
        public int Id { get; private set; }
        public string Name { get; private set; }
        public string Surname { get; private set; }
        public string Telephone { get; private set; }
        public string HomeAddress { get; private set; }
        public double Salary { get; private set; }
        public List<Order> OrderList { get; private set; }

        public Employee(int Id, string Name, string Surname, string Telephone, string HomeAddress, double Salary)
        {
            this.Id = Id;
            this.Name = Name;
            this.Surname = Surname;
            this.Telephone = Telephone;
            this.HomeAddress = HomeAddress;
            this.Salary = Salary;
            this.OrderList = new List<Order>();
        }

        public void ChangeId(int Id)
        {
            this.Id = Id;
        }
        public void ChangeName(string Name)
        {
            this.Name = Name;
        }
        public void ChangeSurname(string Surname)
        {
            this.Surname = Surname;
        }
        public void ChangeTelephone(string Telephone)
        {
            this.Telephone = Telephone;
        }
        public void ChangehomeAddress(string HomeAddress)
        {
            this.HomeAddress = HomeAddress;
        }
        public void ChangeSalary(double Salary)
        {
            this.Salary = Salary;
        }

        public void AddToList(Order Order)
        {
            this.OrderList.Add(Order);
        }
        public void DeleteToList(int Id)
        {
            this.OrderList.RemoveAt(Id);
        }
    }
}
