using System;

namespace University_PD31_32
{
    class Program
    {
        static void Main(string[] args)
        {
            DBItem<Group> dbGroup = new DBItem<Group>();
            Group group1 = new Group("PD-31");
            dbGroup.AddItem(group1);
            Group group2 = new Group("PD-32");
            dbGroup.AddItem(group2);

            DBItem<Student> dbStudent = new DBItem<Student>();
            Student student1 = new Student("Steve", "Jobs", 42, 1);
            dbStudent.AddItem(student1);
            Student student2 = new Student("Vin", "Diesel", 62, 2);
            dbStudent.AddItem(student2);
            Student student3 = new Student("Jhonny", "Sins", 21, 1);
            dbStudent.AddItem(student3);

            DBItem<Teacher> dbTeacher = new DBItem<Teacher>();
            Teacher teacher1 = new Teacher("Jeff", "Bezos");
            dbTeacher.AddItem(teacher1);
            Teacher teacher2 = new Teacher("Elon", "Musk");
            dbTeacher.AddItem(teacher2);

            DBItem<Subject> dbSubject = new DBItem<Subject>();
            Subject subject1 = new Subject("SFD", 100);
            dbSubject.AddItem(subject1);
            Subject subject2 = new Subject("Assembler", 200);
            dbSubject.AddItem(subject2);

            DBItem<Address> dbAddress = new DBItem<Address>();
            Address address1 = new Address("Kyiv", 2);
            dbAddress.AddItem(address1);
            Address address2 = new Address("Odessa", 3);
            dbAddress.AddItem(address2);

            DBItem<SubjectTeacher> dbSubjectTeacher = new DBItem<SubjectTeacher>();
            SubjectTeacher subjectTeacher1 = new SubjectTeacher(1, 1);
            dbSubjectTeacher.AddItem(subjectTeacher1);
            SubjectTeacher subjectTeacher2 = new SubjectTeacher(2, 1);
            dbSubjectTeacher.AddItem(subjectTeacher2);
            SubjectTeacher subjectTeacher3 = new SubjectTeacher(2, 2);
            dbSubjectTeacher.AddItem(subjectTeacher3);

            DBItem<GroupSubject> dbGroupSubject = new DBItem<GroupSubject>();
            GroupSubject groupSubject1 = new GroupSubject(1, 1);
            dbGroupSubject.AddItem(groupSubject1);
            GroupSubject groupSubject2 = new GroupSubject(1, 2);
            dbGroupSubject.AddItem(groupSubject2);
            GroupSubject groupSubject3 = new GroupSubject(2, 1);
            dbGroupSubject.AddItem(groupSubject3);

            HR_Service hr_Service = new HR_Service(dbStudent, dbAddress);
            HR_UI hr_UI = new HR_UI(hr_Service);
            hr_UI.ShowStudentAddress();
            hr_UI.AddressCreate();
            hr_UI.ShowStudentAddress();
            Console.ReadLine();
            hr_UI.StudentCreate();

            foreach (Student s in dbStudent.Items)
            {
                Console.WriteLine(s.ToString());
                foreach (Address adr in dbAddress.Items)
                {
                    if (adr.StudentId == s.Id)
                    {
                        Console.WriteLine("\t"+adr.ToString());
                    }
                }
                foreach (Group g in dbGroup.Items)
                {
                    if (g.Id == s.GroupId)
                    {
                        Console.WriteLine("\t\t" + g);
                        foreach (GroupSubject gs in dbGroupSubject.Items)
                        {
                            if(g.Id == gs.GroupId)
                            {
                                foreach (Subject subj in dbSubject.Items)
                                {
                                    if(subj.Id == gs.SubjectId)
                                    {
                                        Console.WriteLine("\t\t\t"+subj);
                                        foreach(SubjectTeacher subjT in dbSubjectTeacher.Items)
                                        {
                                            if(subjT.SubjectId == subj.Id)
                                            {
                                                foreach(Teacher t in dbTeacher.Items)
                                                {
                                                    if(t.Id == subjT.TeacherId)
                                                    {
                                                        Console.WriteLine("\t\t\t\t" + t);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }          
        }
    }
}
