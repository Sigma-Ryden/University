using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class SubjectTeacher : IId
    {
        public int Id { get; set; }
        public int SubjectId { get; set; }
        public int TeacherId { get; set; }

        public SubjectTeacher(int subjectId, int teacherId)
        {
            SubjectId = subjectId;
            TeacherId = teacherId;
        }

        public override string ToString()
        {
            return $"{Id} {SubjectId} {TeacherId}";
        }
    }
}
