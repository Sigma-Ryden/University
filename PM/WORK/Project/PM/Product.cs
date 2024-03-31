namespace PM
{
    class Product
    {
        public int Id { get; private set; }
        public string Name { get; private set; }
        public double Price { get; private set; }
        public Description Description { get; private set; }

        public Product(int Id, string Name, double Price, Description Description)
        {
            this.Id = Id;
            this.Name = Name;
            this.Price = Price;
            this.Description = Description;
        }

        public void ChangeId(int Id)
        {
           this.Id = Id;
        }
        public void ChangeName(string Name)
        {
            this.Name = Name;
        }
        public void ChangePrice(int Price)
        {
            this.Price = Price;
        }
        public void ChangeDescription(string Title, string Text, string ExpirationDate, string Category)
        {
            this.Description = new Description(Title, Text, ExpirationDate, Category);
        }
        public void ChangeDescription(Description Description)
        {
            this.Description = Description;
        }
    }
}
