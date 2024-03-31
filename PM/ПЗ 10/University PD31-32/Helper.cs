using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    static class Helper
    {
        public static int CheckIntInput(string message)
        {
            int result = default(int);
            bool isDone = false;
            do
            {
                Console.Write(message);
                isDone = int.TryParse(Console.ReadLine(), out result);
                if (isDone == false)
                {
                    Console.WriteLine("Wrong data");
                }
            } while (!isDone);
            return result;
        }
        public static void AddMore(Action Method)
        {
            bool isDone = false;
            do
            {
                Method();
                Console.Write("Add more (y/n)?: ");
                if (Console.ReadLine() == "n")
                {
                    isDone = true;
                }
            } while (!isDone);
        }
    }
}
