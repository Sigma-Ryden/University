using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class Subject : IId
    {
        public int Id { get; set; }
        public string SubjectName { get; set; }
        public int Hours { get; set; }

        public Subject(string subjectName, int hours)
        {
          
            SubjectName = subjectName;
            Hours = hours;
        }

        public override string ToString()
        {
            return $"{Id} {SubjectName} {Hours}";
        }
    }
}
