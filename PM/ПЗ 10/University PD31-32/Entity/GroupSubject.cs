using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class GroupSubject : IId
    {
        public int Id { get; set; }
        public int GroupId { get; set; }
        public int SubjectId { get; set; }

        public GroupSubject(int groupId, int subjectId)
        {
            GroupId = groupId;
            SubjectId = subjectId;
        }
        public override string ToString()
        {
            return $"{Id} {GroupId} {SubjectId}";
        }
    }
}
