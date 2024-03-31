using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class Teacher : IId
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }

        public Teacher(string name, string surname)
        {
           
            Name = name;
            Surname = surname;
        }
        public override string ToString()
        {
            return $"{Id} {Name} {Surname}";
        }
    }
}
