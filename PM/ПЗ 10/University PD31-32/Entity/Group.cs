using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class Group : IId
    {
        public int Id { get; set; }
        public string GroupName { get; set; }
        public Group(string groupName)
        {
            GroupName = groupName;
        }

        public override string ToString()
        {
            return $"{Id} {GroupName}";
        }
    }
}
