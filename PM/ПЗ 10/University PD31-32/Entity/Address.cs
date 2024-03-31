using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class Address : IId
    {
        public int Id { get; set; }

        public string StudentAdress { get; set; }

        public int StudentId { get; set; }

        public Address(string studentAdress, int studentId)
        {
            StudentAdress = studentAdress;
            StudentId = studentId;
        }

        public override string ToString()
        {
            return $"{Id} {StudentAdress} {StudentId}";
        }
    }
}
