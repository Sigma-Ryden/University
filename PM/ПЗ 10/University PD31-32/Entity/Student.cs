using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class Student : IId
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public string Surname { get; set; }

        public int Age { get; set; }

        public int GroupId { get; set; }

        public Student(string name, string surname, int age, int groupId)
        {
            Name = name;
            Surname = surname;
            Age = age;
            GroupId = groupId;
        }

        public override string ToString()
        {
            return $"{Id} {Name} {Surname} {Age} {GroupId}";
        }
    }

}
