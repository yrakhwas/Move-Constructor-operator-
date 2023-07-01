#include <iostream>
#include <string>
using namespace std;

enum Genres
{
    none,
    History,
    Adventure,
    Drama,
    Novel,
    Fantasy,
    ScienceFiction,
    Programming,
    Political
};

class Book
{
private:
    string title;
    int year;
    string author;
    int pages;
    Genres genre;
public:
    Book()
    {
        title = "no title";
        year = 0;
        author = "no author";
        pages = 0;
        genre = (Genres)0;
    }
    Book(string t, string a, int y, int p, Genres g) :title(t), year(y), author(a), pages(p), genre(g) {}

    void ShowShortInfo()const
    {
        cout << "Book - " << title << endl;
        cout << "Author - " << author << endl;
        cout << "Year - " << year << endl; 
        cout << "Pages - " << pages << endl;
        cout << "Genre : ";
        switch (genre)
        {
        case none: cout << "None"; break;
        case History:cout << "History"; break;            
        case Adventure:cout << "Adventure"; break;           
        case Drama:cout << "Drama"; break;            
        case Novel:cout << "Novel"; break;
        case Fantasy:cout << "Fantasy"; break;            
        case ScienceFiction:cout << "ScienceFiction"; break; 
        case Programming:cout << "Programming"; break;
        case Political:cout << "Political"; break;
        }
        cout << "\n_____________________________________________" << endl;
}

};
class Library
{
private:
    string name;
    string adress;
    Book* books;
    int bookCount;
public:
    Library()
    {
        name = "no name";
        adress = "no adress";
        books = nullptr;
        bookCount = 0;
    }
    Library(string name, string adress)
    {
        this->name = name;
        this->adress = adress;
        books = nullptr;
        bookCount = 0;
    }
    //copy
    Library(const Library& other)
    {
        this->name = other.name;
        this->adress = other.adress;
        this->bookCount = other.bookCount;
        this->books = new Book[bookCount];
        for (size_t i = 0; i < bookCount; i++)
        {
            books[i] = other.books[i];
        }
        cout << "Copy constructor" << endl;
    }
    //Move
    Library(Library&& other)
    {
        name = other.name;
        adress = other.adress;
        bookCount = other.bookCount;
        books = other.books;
        other.books = nullptr;

        cout << "Move constructor" << endl;
    }
    void AddBook(Book b)
    {
        Book* newarr = new Book[bookCount + 1];
        for (int i = 0; i < bookCount; i++)
        {
            newarr[i] = books[i];
        }
        newarr[bookCount] = b;
        if(books!=nullptr)
            delete[]books;
        books = newarr;
        ++bookCount;
    }
    Book GetBookCountByIndex(int index)const
    {
        if (index >= 0 && index < bookCount)
        {
            return books[index];
        }
        return Book();

        //if (index < 0 || index >= bookCount)return;
    }
    
    Book operator[](int index)const
    {
        if (index >= 0 && index < bookCount)
        {
            return books[index];
        }
        return Book();

        //if (index < 0 || index >= bookCount)return;
    }
    Library& operator=(const Library& other)
    {
        this->name = other.name;
        this->adress = other.adress;
        this->bookCount = other.bookCount;

        //так як обєкт вже існує, чистимо старий масив
        if (books != nullptr)
            delete[]books;

        this->books = new Book[bookCount];
        for (size_t i = 0; i < bookCount; i++)
        {
            books[i] = other.books[i];
        }
        cout << "operator [=]" << endl;
        return *this;//return result for for exloring =
    }
    operator string()
    {
        return "Library : " + name + " - " +to_string(bookCount) + " books";
   }
    operator int()
    {
        return bookCount;
    }
    ~Library()
    {
        if(books!=nullptr)
            delete[]books;
    }
    friend ostream& operator <<(ostream& out, const Library& lib);
};
ostream& operator <<(ostream& out, const Library& lib)
{
    out << lib.adress << lib.bookCount << lib.name << endl;
    return out;
}
Library TestLibrary(Library lib)//copy ctor
{
    Library temp;//default ctor
    return temp;//copy ctor
}

int main()
{
    Book b1;
    Book b2("C++ for Proffessianal","Steven Prata",2012,1340,Genres::Programming);
    Book b3("Dead souls","Nikolay Gogol", 1842,154, Political);
    Book b4("Taras Bulba", "Nikolay Gogol", 1835, 780, Genres::Novel);
    b4.ShowShortInfo();
    Library lib("Super library", "Dragomanova");
    lib.AddBook(b4);
    lib.AddBook(b2);
    cout << (string)lib << endl;
    int n = lib;
    cout << n << endl;
    Book book = lib.GetBookCountByIndex(1);
    Book book1 = lib[1];
    book1.ShowShortInfo();
    TestLibrary(lib);
    cout << lib << endl;

    Library lib2 = lib;//copy ctor
    lib2 = lib;//
    //lib2.operator=(lib);
}
