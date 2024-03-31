using System.Collections.Generic;

namespace PM
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee employee = new Employee(21018771, "John", "Kart", "380953454532", "Kyiv", 2000.0);

            List<Customer> customerList = new List<Customer>();

            Customer customer1 = new Customer(72641214, "Tom", "Jerry", "380542121371", 500.0);
            Customer customer2 = new Customer(92302458, "John", "Konor", "380512838313", 100.0);

            customerList.Add(customer1);
            customerList.Add(customer2);

            foreach(Customer customer in customerList)
            {
                System.Console.WriteLine($"Customer #{customer.Id} personal account before buy products: {customer.PersonalAccount}", 0, 1);
            }

            Order order1 = new Order(12320194);
            Order order2 = new Order(82401924);
            Order order3 = new Order(98738901);

            Product milk = new Product(45004127, "Milk", 20.0, new Description("Milk", "The best milk", "21.12.2021", "latex"));
            Product meet = new Product(23019054, "Meet", 45.0, new Description("Pork", "The best meet", "03.01.2022", "meat"));
            Product apple = new Product(35201127, "Apple", 5.0, new Description("Apple", "The best apple", "19.12.2021", "fruit"));
            Product bread = new Product(20910234, "Bread", 15.0, new Description("Bread", "The best bread", "16.12.2021", "bread"));

            order1.AddToList(milk);
            order1.AddToList(meet);
            order1.AddToList(apple);
            order2.AddToList(bread);

            System.Console.WriteLine("Order list:");
            System.Console.WriteLine($"Order1 #{order1.Id} total price: {order1.TotalPrice}", 0, 1);
            System.Console.WriteLine($"Order2 #{order2.Id} total price: {order2.TotalPrice}", 0, 1);
            System.Console.WriteLine($"Order3 #{order3.Id} total price: {order3.TotalPrice}", 0, 1);

            order1.DeleteToList(meet);
            order3.AddToList(meet);

            System.Console.WriteLine("Order list after change:");
            System.Console.WriteLine($"Order1 #{order1.Id} total price: {order1.TotalPrice}", 0, 1);
            System.Console.WriteLine($"Order2 #{order2.Id} total price: {order2.TotalPrice}", 0, 1);
            System.Console.WriteLine($"Order3 #{order3.Id} total price: {order3.TotalPrice}", 0, 1);

            employee.AddToList(order1);
            employee.AddToList(order2);
            employee.AddToList(order3);

            customer1.BuyOrder(employee.OrderList[0]);
            customer1.BuyOrder(employee.OrderList[2]);
            customer2.BuyOrder(employee.OrderList[1]);

            foreach (Customer customer in customerList)
            {
                System.Console.WriteLine($"Customer #{customer.Id} personal account after buy products: {customer.PersonalAccount}", 0, 1);
            }

            employee.OrderList.Clear();
        }
    }
}
