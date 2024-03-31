using System;
using System.Collections.Generic;
using System.Text;

namespace University_PD31_32
{
    class DBItem<T> where T : IId
    {
        private int _count = 1;
        public List<T> Items { get; set; }

        public DBItem()
        {
            Items = new List<T>();
        }

        public void AddItem(T item)
        {
            item.Id = _count++;
            Items.Add(item);
        }
    }
}
