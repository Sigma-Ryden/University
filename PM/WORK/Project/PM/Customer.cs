namespace PM
{
    class Customer
    {
        public int Id { get; private set; }
        public string Name { get; private set; }
        public string Surname { get; private set; }
        public string Telephone { get; private set; }
        public double PersonalAccount { get; private set; }

        public Customer(int Id, string Name, string Surname, string Telephone, double PersonalAccount)
        {
            this.Id = Id;
            this.Name = Name;
            this.Surname = Surname;
            this.Telephone = Telephone;
            this.PersonalAccount = PersonalAccount;
        }

        public void BuyOrder(Order Order)
        {
            if (this.PersonalAccount >= Order.TotalPrice)
            {
                this.PersonalAccount -= Order.TotalPrice;
                System.Console.WriteLine($"Operation #{Order.Id} for customer #{this.Id} complated successfully!", 0, 1);
            }
            else
            {
                System.Console.WriteLine($"Operation #{Order.Id} for customer #{this.Id} failed!", 0, 1);
            }
        }
    }
}
