namespace PM
{
    class Description
    {
        public string Title { get; private set; }
        public string Text { get; private set; }
        public string ExpirationDate { get; private set; }
        public string Category { get; private set; }

        public Description(string Title, string Text, string ExpirationDate, string Category)
        {
            this.Title = Title;
            this.Text = Text;
            this.ExpirationDate = ExpirationDate;
            this.Category = Category;
        }

        public void ChangeTitle(string Title)
        {
            this.Title = Title;
        }
        public void ChangeDescription(string Text)
        {
            this.Text = Text;
        }
        public void ChangeExpirationDate(string ExpirationDate)
        {
            this.ExpirationDate = ExpirationDate;
        }
        public void ChangeCategory(string Category)
        {
            this.Category = Category;
        }
    }
}
