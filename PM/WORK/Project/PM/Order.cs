using System.Collections.Generic;

namespace PM
{
    class Order
    {
        public int Id { get; private set; }
        public double TotalPrice { get; private set; }
        public List<Product> ProductList { get; private set; }
        
        public Order(int Id)
        {
            this.Id = Id;
            this.TotalPrice = 0.0;
            this.ProductList = new List<Product>();
        }

        public void ChangeId(int Id)
        {
            this.Id = Id;
        }
        public void ChangeTotalPrice(double TotalPrice)
        {
            this.TotalPrice = TotalPrice;
        }

        public void AddToList(Product Product)
        {
            this.ProductList.Add(Product);
            this.TotalPrice += Product.Price;
        }
        public void DeleteToList(Product Product)
        {
            this.ProductList.Remove(Product);
            this.TotalPrice -= Product.Price;
        }
    }
}
